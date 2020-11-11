//// inplace_cedit.cpp файл реализации
//// методы 
#include "pch.h"
#include "inplace_cedit.h"

CInplaceCEdit::CInplaceCEdit(int iItem, int iSubItem, CString sInitText) :m_sInitText(sInitText) {
    m_iItem = iItem;
    m_iSubItem = iSubItem;
    m_bESC = FALSE;
}

CInplaceCEdit::~CInplaceCEdit() { }

BEGIN_MESSAGE_MAP(CInplaceCEdit, CEdit) 
    ON_WM_KILLFOCUS()
    ON_WM_NCDESTROY()
    ON_WM_CHAR()
    ON_WM_CREATE()
END_MESSAGE_MAP()

////CInplaceCEdit обработчики сообщений

/// Перевод оконных сообщений перед отправкой в TranslateMessage и DispatchMessage Windows
BOOL CInplaceCEdit::PreTranslateMessage(MSG* pMsg) {
    if (pMsg->message == WM_KEYDOWN)
    {
        if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || pMsg->wParam == VK_ESCAPE || GetKeyState(VK_CONTROL))
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return TRUE;
        }
    }

    return CEdit::PreTranslateMessage(pMsg);
}

/// Вызывается непосредственно перед потерей фокуса ввода
void CInplaceCEdit::OnKillFocus(CWnd* pNewWnd) {
    CEdit::OnKillFocus(pNewWnd);
    CString str;
    GetWindowText(str);

    DestroyWindow();
}

/// Вызывается, когда уничтожается неклиентская область
void CInplaceCEdit::OnNcDestroy() {
    CEdit::OnNcDestroy();
    delete this;
}

/// Вызывается при нажатии клавиш несистемными символами
void CInplaceCEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
    if (nChar == VK_ESCAPE || nChar == VK_RETURN) {
        if (nChar == VK_ESCAPE) {
            m_bESC = TRUE;
        }

        GetParent()->SetFocus();
        return;
    }

    CEdit::OnChar(nChar, nRepCnt, nFlags);

    /// Изменение размера при необходимости
    CString str;
    GetWindowText(str);
    CWindowDC dc(this);
    CFont* pFont = GetParent()->GetFont();
    CFont* pFontDC = dc.SelectObject(pFont);
    CSize size = dc.GetTextExtent(str);
    dc.SelectObject(pFontDC);
    size.cx += 5;

    /// Захват прямоугольника клиента
    CRect rect, parentrect;
    GetClientRect(&rect);
    GetParent()->GetClientRect(&parentrect);

    /// Преобразование прямоугольника в родительскую с.к.    
    ClientToScreen(&rect);
    GetParent()->ScreenToClient(&rect);

    ///Проверка на необходимость изменения размера
    if (size.cx > rect.Width()) {
        if (size.cx + rect.left < parentrect.right) {
            rect.right = rect.left + size.cx;
        } else {
            rect.right = parentrect.right;
        }

        MoveWindow(&rect);
    }

    /// Создание элемента управления списком
    LV_DISPINFO dispinfo;
    dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
    dispinfo.hdr.idFrom = GetDlgCtrlID();
    dispinfo.hdr.code = LVN_ENDLABELEDIT;
    dispinfo.item.mask = LVIF_TEXT;
    dispinfo.item.iItem = m_iItem;
    dispinfo.item.iSubItem = m_iSubItem;
    dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str);
    dispinfo.item.cchTextMax = str.GetLength();

    /// Отправка уведомления родителю ListViewСtrl    
    CWnd* pWndViewAttachmentsDlg = GetParent()->GetParent();

    if (pWndViewAttachmentsDlg) {
        pWndViewAttachmentsDlg->SendMessage(WM_NOTIFY_DESCRIPTION_EDITED,
            GetParent()->GetDlgCtrlID(),
            (LPARAM)&dispinfo);
    }
}

/// Вызывается, когда приложение запрашивает создание окна Windows путем вызова функции-члена Create / CreateEx
int CInplaceCEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CEdit::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    /// Задание шрифта
    CFont* font = GetParent()->GetFont();
    SetFont(font);
    SetWindowText(m_sInitText);
    SetFocus();
    SetSel(0, -1);
    return 0;
}