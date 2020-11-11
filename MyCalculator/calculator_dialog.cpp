
/// calculator_dialog.cpp: файл реализации
/// определяет поведения диалогового окна калькулятора

#include "pch.h"
#include "framework.h"
#include "simple_calculator.h"
#include "calculator_dialog.h"
#include "afxdialogex.h"
#include "matrix_dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString sEnter;
bool bDelimeter = false;
double fRHS = 0;
double fLHS = 0;
char cOperation = ' ';
bool bOperation = false;
bool bInAction = false;

/// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

/// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    /// поддержка DDX/DDV

/// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


/// Диалоговое окно CMyCalculatorDlg



CMyCalculatorDlg::CMyCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

/// Обмен данными с элементами контроля

void CMyCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, CEditBox);
	DDX_Control(pDX, IDC_BUTTON12, mPlusBtn);
	SetBtnColor();
	DDX_Control(pDX, IDC_BUTTON13, mMinusBtn);
	DDX_Control(pDX, IDC_BUTTON14, mMultiplyBtn);
	DDX_Control(pDX, IDC_BUTTON15, mDivideBtn);
	DDX_Control(pDX, IDC_BUTTON16, mClearBtn);
	DDX_Control(pDX, IDC_BUTTON20, mDeleteBtn);
	DDX_Control(pDX, IDC_BUTTON18, mEqualsBtn);
	DDX_Control(pDX, IDC_BUTTON19, mMatricesBtn);
}

/// Обработка событий

BEGIN_MESSAGE_MAP(CMyCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMyCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMyCalculatorDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMyCalculatorDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CMyCalculatorDlg::OperationPlus)
	ON_BN_CLICKED(IDC_BUTTON13, &CMyCalculatorDlg::OperationMinus)
	ON_BN_CLICKED(IDC_BUTTON14, &CMyCalculatorDlg::OperationMultiply)
	ON_BN_CLICKED(IDC_BUTTON15, &CMyCalculatorDlg::OperationDivide)
	ON_BN_CLICKED(IDC_BUTTON16, &CMyCalculatorDlg::OperationClear)
	ON_BN_CLICKED(IDC_BUTTON18, &CMyCalculatorDlg::OperationEquals)
	ON_BN_CLICKED(IDC_BUTTON19, &CMyCalculatorDlg::OperationOpen)
	ON_BN_CLICKED(IDC_BUTTON20, &CMyCalculatorDlg::OperationDelete)
	ON_BN_CLICKED(IDC_BUTTON21, &CMyCalculatorDlg::OperationChangeSign)
END_MESSAGE_MAP()


/// Обработчики сообщений CMyCalculatorDlg

BOOL CMyCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/// Добавление пункта "О программе..." в системное меню.

	/// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	/// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	///  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			/// Крупный значок
	SetIcon(m_hIcon, FALSE);		/// Мелкий значок

	/// TODO: добавьте дополнительную инициализацию

	return TRUE;  /// возврат значения TRUE, если фокус не передан элементу управления
}

void CMyCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

/// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
///  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
///  это автоматически выполняется рабочей областью.

void CMyCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); /// контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		/// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		/// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

/// Система вызывает эту функцию для получения отображения курсора при перемещении
///  свернутого окна.
HCURSOR CMyCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/// <summary>
/// Обработчик нажатия на кнопку
/// </summary>
/// <param name="button"></param>
void CMyCalculatorDlg::OnBnClickedDigits(CString button) 
{
	if ((sEnter == L"0" && button != "." ) || bOperation)
	{
		sEnter = button;
		bOperation = false;
	}
	else
	{
		sEnter.Append(button);
	}
	CEditBox.SetWindowTextW(sEnter);
}

/// <summary>
/// Обработчик нажатия на кнопку операции
/// </summary>
/// <param name="operation"></param>
void CMyCalculatorDlg::SetOperation(char operation)
{
	if (bInAction) 
	{
		OperationEquals();
	}
	else
	{
		fLHS = _wtof(sEnter);
	}
	
	bOperation = true;
	cOperation = operation;
	bDelimeter = false;
	bInAction = true;
}

/// <summary>
/// Вычисление выражения
/// </summary>
/// <param name="x"></param>
/// <param name="operation"></param>
/// <param name="y"></param>
/// <returns></returns>
double CMyCalculatorDlg::Calculate(double x, char operation, double y)
{
	switch (operation)
	{
	case '+':
		return x + y;
	case '-':
		return x - y;
	case '*':
		return x * y;
	case '/':
		if (fabs(y) < 1e-6)
		{
			AfxMessageBox(L"Деление на ноль невозможно!");
		}
		else
		{
			return x / y;
		}
	default:
		return x;
	}
}

/// <summary>
/// Обработчики нажатия на кнопки с "1" по "0", а также "."
/// </summary>
void CMyCalculatorDlg::OnBnClickedButton1()
{
	OnBnClickedDigits(L"1");
}

void CMyCalculatorDlg::OnBnClickedButton2()
{
	OnBnClickedDigits(L"2");
}


void CMyCalculatorDlg::OnBnClickedButton3()
{
	OnBnClickedDigits(L"3");
}


void CMyCalculatorDlg::OnBnClickedButton4()
{
	OnBnClickedDigits(L"4");
}


void CMyCalculatorDlg::OnBnClickedButton5()
{
	OnBnClickedDigits(L"5");
}


void CMyCalculatorDlg::OnBnClickedButton6()
{
	OnBnClickedDigits(L"6");
}


void CMyCalculatorDlg::OnBnClickedButton7()
{
	OnBnClickedDigits(L"7");
}


void CMyCalculatorDlg::OnBnClickedButton8()
{
	OnBnClickedDigits(L"8");
}


void CMyCalculatorDlg::OnBnClickedButton9()
{
	OnBnClickedDigits(L"9");
}


void CMyCalculatorDlg::OnBnClickedButton10()
{
	OnBnClickedDigits(L"0");
}

void CMyCalculatorDlg::OnBnClickedButton11()
{
	if (sEnter.GetLength() != 0 && !bDelimeter)
	{
		OnBnClickedDigits(L".");
		bDelimeter = true;
	}
}

/// <summary>
/// Обработчики нажатия на кнопки операций "+", "-", "*", "/", "С", "=", "<-", "+/-"
/// </summary>

void CMyCalculatorDlg::OperationPlus()
{
	SetOperation('+');
}


void CMyCalculatorDlg::OperationMinus()
{
	SetOperation('-');
}


void CMyCalculatorDlg::OperationMultiply()
{
	SetOperation('*');
}

void CMyCalculatorDlg::OperationDivide()
{
	SetOperation('/');
}

void CMyCalculatorDlg::OperationClear()
{
	cOperation = ' ';
	sEnter = L"";
	fRHS = 0;
	fLHS = 0;
	bDelimeter = false;
	CEditBox.SetWindowTextW(L"0");
}

void CMyCalculatorDlg::OperationEquals()
{
	fRHS = _wtof(sEnter);
	fLHS = Calculate(fLHS, cOperation, fRHS);
	sEnter.Format(L"%g", fLHS);
	CEditBox.SetWindowTextW(sEnter);

	bInAction = false;
}

void CMyCalculatorDlg::OperationDelete()
{
	sEnter.Delete(sEnter.GetLength() - 1);
	if (sEnter.GetLength() == 0)
	{
		sEnter = L"0";
	}
	CEditBox.SetWindowTextW(sEnter);
}

void CMyCalculatorDlg::OperationChangeSign()
{
	if (sEnter.GetLength() > 0 && sEnter != L"0")
	{
		double temp = _wtof(sEnter);
		temp *= -1;
		sEnter.Format(L"%g", temp);
		CEditBox.SetWindowTextW(sEnter);
	}
}

/// <summary>
/// Обработчик кнопки для диалогового окна матриц
/// </summary>
void CMyCalculatorDlg::OperationOpen()
{
	MatrixDialog nMatrices;
	nMatrices.DoModal();
}

/// <summary>
/// Установка определенных цветов кнопок
/// </summary>
void CMyCalculatorDlg::SetBtnColor()
{
	mPlusBtn.EnableWindowsTheming(FALSE);      

	mPlusBtn.SetFaceColor(RGB(255, 160, 122));    
	
	mMinusBtn.SetFaceColor(RGB(135, 206, 235));     

	mMultiplyBtn.SetFaceColor(RGB(255, 69, 0));     
	
	mDivideBtn.SetFaceColor(RGB(95, 158, 160));    

	mEqualsBtn.SetFaceColor(RGB(255, 140, 0));     

	mClearBtn.SetFaceColor(RGB(128, 128, 0));     

	mDeleteBtn.SetFaceColor(RGB(60, 179, 113));     

	mMatricesBtn.SetFaceColor(RGB(0, 191, 255));
}