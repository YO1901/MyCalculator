/// matrix_dialog.h заголовочный файл
/// Объявление класса MatrixDialog для работы с окном вычисления матриц

#pragma once
#include "editable_clist.h"
#define WM_NOTIFY_DESCRIPTION_EDITED (WM_USER + 100)

// Диалоговое окно MatrixDialog
class MatrixDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MatrixDialog)

public:
	MatrixDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~MatrixDialog();
    virtual BOOL OnInitDialog();
    CPoint InterviewListCursorPosition(UINT id) const;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
       public:
        CEditableCListCtrl aListCtrlMatA;   /// Матрица А
        CEditableCListCtrl aListCtrlMatB;   /// Матрица В
        CEditableCListCtrl aListCtrlMatC;   /// Матрица С
        afx_msg void OnBtnClickedSetSize(); /// Обработчик нажатия на кнопку задания размера
        afx_msg void OnBtnClickedCalculate();   /// Обработчик нажатия на кнопку расчета матрицы
        afx_msg LRESULT OnNotifyDescriptionEdited(WPARAM wParam, LPARAM lParam);    /// Обработчик события редактирования поля матрицы
        afx_msg BOOL OnNMClickList(UINT id, NMHDR* pNMHDR, LRESULT* pResult);   /// Обработчик события нажатия ЛВМ на поле матрицы
        CEdit m_EditMatAM;   /// поле ввода количества строк матрицы А
        CEdit m_EditMatAN;   /// поле ввода количества столбцов матрицы А
        CEdit m_EditMatBM;   /// поле ввода количества строк матрицы В
        CEdit m_EditMatBN;   /// поле ввода количества столбцов матрицы В
        
private:
    void SetInitialCListCtrlMatrices(int nMatAM, int nMatAN, int nMatBM, int nMatBN);   /// задание и инициализация матриц
    BOOL CheckDimensions(int nMatAM, int nMatAN, int nMatBM, int nMatBN);   /// Проверка введенных размерностей матриц
    BOOL CheckMatrixInput(LPWSTR& sInput);  /// Проверка введеных числовых значений
};