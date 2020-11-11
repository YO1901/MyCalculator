/// editable_clist.h заголовочный файл
/// ќбъ€вление класса CEditableCListCtrl, который наследуетс€ от CListCtrl, и реализует редактируемый список
#pragma once
#include <afxcmn.h>
class CEditableCListCtrl :
    public CListCtrl
{
public:
    int GetRowFromPoint(CPoint& point, int* col) const;
    CEdit* EditSubLabel(int nItem, int nColm);

    void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
    void OnLButtonDown(UINT nFlags, CPoint point);
};

