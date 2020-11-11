/// editable_clist.cpp ���� ����������
/// ���������� ������ ��� �������������� ������
/// 
#include "pch.h"
#include "editable_clist.h"
#include "inplace_cedit.h"

/// ��������� ������ ������ � �������, �� ������� ����� ������
int CEditableCListCtrl::GetRowFromPoint(CPoint& point, int* col) const {
    int column = 0;
    int row = HitTest(point, NULL);

    if (col) *col = 0;

    /// ��������� ���������� ListView � LVS_REPORT 
    if ((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT) {
        return row;
    }

    /// ��������� ������� � ���������� ������� ����� 
    row = GetTopIndex();
    int bottom = row + GetCountPerPage();

    if (bottom > GetItemCount()) {
        bottom = GetItemCount();
    }

    /// ��������� ���������� �������� 
    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();

    /// ���� �� ������� �������  
    for (; row <= bottom; row++) {
        ///  �������� �������������, �������������� �������,  � ���������, �������� �� � ���� �����
        CRect rect;
        GetItemRect(row, &rect, LVIR_BOUNDS);

        if (rect.PtInRect(point)) {
            /// ����� �������    
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

/// ������� � ������ ������� Edit Control
CEdit* CEditableCListCtrl::EditSubLabel(int nItem, int nCol) {
    /// �������� ��������� ��������
    if (!EnsureVisible(nItem, TRUE)) return NULL;

    /// �������� ������ �������   
    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if (nCol >= nColumnCount || GetColumnWidth(nCol) < 5) return NULL;

    /// ��������� ������� �������       
    int offset = 0;
    for (int i = 0; i < nCol; i++) {
        offset += GetColumnWidth(i);
    }

    CRect rect;
    GetItemRect(nItem, &rect, LVIR_BOUNDS);

    /// ��������� �� ����������� ���� ����� ������� ������� 
    CRect rcClient;
    GetClientRect(&rcClient);

    if (offset + rect.left < 0 || offset + rect.left > rcClient.right) {
        CSize size;
        size.cx = offset + rect.left;
        size.cy = 0;
        Scroll(size);
        rect.left -= size.cx;
    }

    /// �������������� ������� 
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

/// �������� Edit Control � ������ ����� �� ������ ����� �����
void CEditableCListCtrl::OnLButtonDown(UINT nFlags, CPoint point) {
    int index;
    CListCtrl::OnLButtonDown(nFlags, point);

    ModifyStyle(0, LVS_EDITLABELS);

    int colnum;

    if ((index = GetRowFromPoint(point, &colnum)) != -1) {
        UINT flag = LVIS_FOCUSED;

        if ((GetItemState(index, flag) & flag) == flag /*&& colnum == 2*/) {
            /// �������� ��� LVS_EDITLABELS         
            if (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS) {
                EditSubLabel(index, colnum);
            }
        } else {
            SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
        }
    }
}