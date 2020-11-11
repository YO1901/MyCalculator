/// inplace_cedit.h заголовочный файл
/// Объявление класса CInplaceCedit, который наследуется от класса CEdit
/// и реализует логику добавления редактируемого элемента  при нажатии ЛВМ на элемент списка
#pragma once
#include <afxwin.h>
#define WM_NOTIFY_DESCRIPTION_EDITED (WM_USER + 100)
class CInplaceCEdit :
    public CEdit
{
public:
    CInplaceCEdit(int iItem, int iSubItem, CString sInitText);

    //{{AFX_VIRTUAL(CInplaceCEdit)   
public: virtual BOOL PreTranslateMessage(MSG* pMsg);
      //}}AFX_VIRTUAL

public: virtual ~CInplaceCEdit();

      // Generated message map functions
protected:
    //{{AFX_MSG(CInplaceCEdit)   
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnNcDestroy();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG     

    DECLARE_MESSAGE_MAP()

private:
    int m_iItem;
    int m_iSubItem;
    CString m_sInitText;
    BOOL    m_bESC;
};

