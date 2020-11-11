/// editable_clist.cpp файл реализации
/// Реализация класса для редактирования списка
/// 
#include "pch.h"
#include "editable_clist.h"
#include "inplace_cedit.h"

/// Получение номера строки и столбца, на которые попал курсор
int CEditableCListCtrl::GetRowFromPoint(CPoint& point, int* col) const {
    int column = 0;
    int row = HitTest(point, NULL);

    if (col) *col = 0;

    /// Проверяем нахождение ListView в LVS_REPORT 
    if ((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT) {
        return row;
    }

    /// Получение первого и последнего видимых строк 
    row = GetTopIndex();
    int bottom = row + GetCountPerPage();

    if (bottom > GetItemCount()) {
        bottom = GetItemCount();
    }

    /// Получение количества столбцов 
    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();

    /// Цикл по видимым строкам  
    for (; row <= bottom; row++) {
        ///  Получает прямоугольник, ограничивающий элемент,  и проверяет, попадает ли в него точка
        CRect rect;
        GetItemRect(row, &rect, LVIR_BOUNDS);

        if (rect.PtInRect(point)) {
            /// Поиск столбца    
            for (column = 0; column < nColumnCount; column++) {
                int colwidth = GetColumnWidth(column);

                if (point.x >= rect.left && point.x <= (rect.left + colwidth)) {
                    if (col) *col = column;
                    return row;
                }

                rect.left += colwidth;
            }
        }
    }

    return -1;
}

/// Создает и делает видимым Edit Control
CEdit* CEditableCListCtrl::EditSubLabel(int nItem, int nCol) {
    /// Проверка видимости элемента
    if (!EnsureVisible(nItem, TRUE)) return NULL;

    /// Проверка номера столбца   
    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if (nCol >= nColumnCount || GetColumnWidth(nCol) < 5) return NULL;

    /// Получения отступа столбца       
    int offset = 0;
    for (int i = 0; i < nCol; i++) {
        offset += GetColumnWidth(i);
    }

    CRect rect;
    GetItemRect(nItem, &rect, LVIR_BOUNDS);

    /// Прокрутка по горизонтали если нужно увидеть столбец 
    CRect rcClient;
    GetClientRect(&rcClient);

    if (offset + rect.left < 0 || offset + rect.left > rcClient.right) {
        CSize size;
        size.cx = offset + rect.left;
        size.cy = 0;
        Scroll(size);
        rect.left -= size.cx;
    }

    /// Форматирование столбца 
    LV_COLUMN lvcol;
    lvcol.mask = LVCF_FMT;
    GetColumn(nCol, &lvcol);
    DWORD dwStyle;

    if ((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT) {
        dwStyle = ES_LEFT;
    } else if ((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT) {
        dwStyle = ES_RIGHT;
    } else {
        dwStyle = ES_CENTER;
    }

    rect.left += offset + 4;
    rect.right = rect.left + GetColumnWidth(nCol) - 3;

    if (rect.right > rcClient.right) {
        rect.right = rcClient.right;
    }

    dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

    CEdit* pEdit = new CInplaceCEdit(nItem, nCol, GetItemText(nItem, nCol));
    pEdit->Create(dwStyle, rect, this, 1);

    return pEdit;
}

/// Создание Edit Control в нужном месте по левому клику мышки
void CEditableCListCtrl::OnLButtonDown(UINT nFlags, CPoint point) {
    int index;
    CListCtrl::OnLButtonDown(nFlags, point);

    ModifyStyle(0, LVS_EDITLABELS);

    int colnum;

    if ((index = GetRowFromPoint(point, &colnum)) != -1) {
        UINT flag = LVIS_FOCUSED;

        if ((GetItemState(index, flag) & flag) == flag /*&& colnum == 2*/) {
            /// Проверка для LVS_EDITLABELS         
            if (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS) {
                EditSubLabel(index, colnum);
            }
        } else {
            SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
        }
    }
}