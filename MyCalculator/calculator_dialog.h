/// MyCalculatorDlg.h: файл заголовка
/// Объявление класса CMyCalulatorDlg для работы с диалоговым окном калькулятора

#pragma once


/// Диалоговое окно CMyCalculatorDlg
class CMyCalculatorDlg : public CDialogEx
{
/// Создание
public:
	CMyCalculatorDlg(CWnd* pParent = nullptr);	/// стандартный конструктор

/// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	/// поддержка DDX/DDV


/// Реализация
protected:
	HICON m_hIcon;

	/// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit CEditBox;	///	Поле ввода чисел
	/// Обрабочтики нажатия кнопок
	afx_msg void OnBnClickedButton1();	/// 1
	afx_msg void OnBnClickedButton2();	/// 2
	afx_msg void OnBnClickedButton3();	/// 3
	afx_msg void OnBnClickedButton4();	/// 4
	afx_msg void OnBnClickedButton5();	/// 5
	afx_msg void OnBnClickedButton6();	/// 6
	afx_msg void OnBnClickedButton7();	/// 7
	afx_msg void OnBnClickedButton8();	/// 8
	afx_msg void OnBnClickedButton9();	/// 9
	afx_msg void OnBnClickedButton10();	/// 0
private:
	void OnBnClickedDigits(CString button);	/// Регистрация введенной цифры
	void SetOperation(char operation);	/// Регистрация запрошенной операции
	double Calculate(double x, char operation, double y);	/// Вычисление результата
	void SetBtnColor();	/// Установка определенных цветов для кнопок
public:
	afx_msg void OnBnClickedButton11();	/// .
	afx_msg void OperationPlus();		/// +
	afx_msg void OperationMinus();		/// -
	afx_msg void OperationMultiply();	/// *
	afx_msg void OperationDivide();		/// /
	afx_msg void OperationClear();		/// С
	afx_msg void OperationEquals();		/// =
	afx_msg void OperationOpen();		/// Открытие второго диалогового окна для расчета матриц
	afx_msg void OperationDelete();		///	<-
	afx_msg void OperationChangeSign();	///	+/-
	CMFCButton mPlusBtn;		/// кнопка +
	CMFCButton mMinusBtn;		/// кнопка -
	CMFCButton mMultiplyBtn;	///	кнопка *
	CMFCButton mDivideBtn;		/// кнопка /
	CMFCButton mClearBtn;		///	кнопка С
	CMFCButton mDeleteBtn;		/// кнопка <-
	CMFCButton mEqualsBtn;		/// кнопка =
	CMFCButton mMatricesBtn;	/// кнопка для открытия диалогового окна
};
