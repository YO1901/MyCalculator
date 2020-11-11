/// matrix_dialog.cpp: файл реализации
/// Определяет поведение диалогового окна перемножения матриц

#include "pch.h"
#include "simple_calculator.h"
#include "matrix_dialog.h"
#include "afxdialogex.h"
#include "Matrix.h"

CString sSize = L"4";
UINT iDelimeter = 0;
const double minVal = -1.3e+7;
const double maxVal = 1.3e+7;

/// Диалоговое окно matrix_dialog

IMPLEMENT_DYNAMIC(MatrixDialog, CDialogEx)

MatrixDialog::MatrixDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWDIALOG, pParent) {

}

MatrixDialog::~MatrixDialog() { }

/// Обмен данными
void MatrixDialog::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST_A, aListCtrlMatA);  /// Элемент управления матрицы А
  DDX_Control(pDX, IDC_LIST_B, aListCtrlMatB);  /// Элемент управления матрицы В
  DDX_Control(pDX, IDC_LIST_C, aListCtrlMatC);  /// Элемент управления матрицы С
  DDX_Control(pDX, IDC_EDIT1, m_EditMatAM);  /// Количество строк матрицы А
  DDX_Control(pDX, IDC_EDIT2, m_EditMatAN);  /// Количество столбцов матрицы А
  DDX_Control(pDX, IDC_EDIT3, m_EditMatBM);  /// Количество строк матрицы В
  DDX_Control(pDX, IDC_EDIT4, m_EditMatBN);  /// Количество столбцов матрицы В
}

/// Инициализация диалогового окна 
BOOL MatrixDialog::OnInitDialog() {
    CDialog::OnInitDialog();
    m_EditMatAM.SetWindowText(sSize);
    m_EditMatAN.SetWindowText(sSize);
    m_EditMatBM.SetWindowText(sSize);
    m_EditMatBN.SetWindowText(sSize);

    /// Инициализация значений матриц в окне
    SetInitialCListCtrlMatrices(_wtoi(sSize), _wtoi(sSize), _wtoi(sSize), _wtoi(sSize));
    
    return TRUE;
}

/// Инициализация элементов управления матриц заданного размера
void MatrixDialog::SetInitialCListCtrlMatrices(int nMatAM, int nMatAN, int nMatBM, int nMatBN) {
    CString sInit = L"0";   /// Начальное значение
    CString sName;          /// Имя столбца
    int nColSize = 25;      /// Начальный размер столбцов

    /// Получение текущего размера управляющих элементов
    CHeaderCtrl* pHeaderCtrlA = aListCtrlMatA.GetHeaderCtrl();
    CHeaderCtrl* pHeaderCtrlB = aListCtrlMatB.GetHeaderCtrl();
    int nCurrAN = pHeaderCtrlA->GetItemCount();
    int nCurrBN = pHeaderCtrlB->GetItemCount();
    int nCurrAM = aListCtrlMatA.GetItemCount();
    int nCurrBM = aListCtrlMatB.GetItemCount();

    /// Создание недостающих строк и столбцов, удаление лишних строк и столбцов, заполнение управляющих элементов
    if (nMatBN > nCurrBN) {
        for (int k = nCurrBN; k < nMatBN; k++) {
            sName.Format(L"%d", k);
            aListCtrlMatB.InsertColumn(k, sName, LVCFMT_LEFT, nColSize);
            aListCtrlMatC.InsertColumn(k, sName, LVCFMT_LEFT, nColSize);
            for (int i = 0; i < nCurrBM; i++) {
                aListCtrlMatB.SetItemText(i, k, sInit);
                aListCtrlMatB.SetColumnWidth(k, LVSCW_AUTOSIZE_USEHEADER);
            }
            for (int i = 0; i < nCurrAM; i++) {
                aListCtrlMatC.SetItemText(i, k, sInit);
                aListCtrlMatC.SetColumnWidth(k, LVSCW_AUTOSIZE_USEHEADER);
            }
        }
    } else if (nMatBN < nCurrBN){
        for (int k = nCurrBN - 1; k > nMatBN - 1; k--) {
            aListCtrlMatB.DeleteColumn(k);
            aListCtrlMatC.DeleteColumn(k);
        }
    }

    if (nMatAN > nCurrAN) {
        for (int j = nCurrAN; j < nMatAN; j++) {
            sName.Format(L"%d", j);
            aListCtrlMatA.InsertColumn(j, sName, LVCFMT_LEFT, nColSize);
            aListCtrlMatB.InsertItem(j, sInit, -1);
            for (int k = 0; k < nMatBN; k++) {
                aListCtrlMatB.SetItemText(j, k, sInit);
                aListCtrlMatB.SetColumnWidth(k, LVSCW_AUTOSIZE_USEHEADER);
            }
            for (int k = 0; k < nCurrAM; k++) {
                aListCtrlMatA.SetItemText(k, j, sInit);
                aListCtrlMatA.SetColumnWidth(j, LVSCW_AUTOSIZE_USEHEADER);
            }
        }
    } else if (nMatAN < nCurrAN) {
        for (int k = nCurrAN - 1; k > nMatAN - 1; k--) {
            aListCtrlMatA.DeleteColumn(k);
            aListCtrlMatB.DeleteItem(k);
        }
    }

    if (nMatAM > nCurrAM) {
        for (int i = nCurrAM; i < nMatAM; i++) {
            aListCtrlMatA.InsertItem(i, sInit, -1);
            aListCtrlMatC.InsertItem(i, sInit, -1);
            for (int j = 0; j < nMatAN; j++) {
                aListCtrlMatA.SetItemText(i, j, sInit);
                aListCtrlMatA.SetColumnWidth(j, LVSCW_AUTOSIZE_USEHEADER);
            }

            for (int k = 0; k < nMatBN; k++) {
                aListCtrlMatB.SetItemText(i, k, sInit);
                aListCtrlMatC.SetItemText(i, k, sInit);
                aListCtrlMatB.SetColumnWidth(k, LVSCW_AUTOSIZE_USEHEADER);
                aListCtrlMatC.SetColumnWidth(k, LVSCW_AUTOSIZE_USEHEADER);
            }
        }
    } else if (nMatAM < nCurrAM) {
        for (int k = nCurrAM - 1; k > nMatAM - 1; k--) {
            aListCtrlMatA.DeleteItem(k);
            aListCtrlMatC.DeleteItem(k);
        }
    }
}

/// Проверка размерностей матриц
BOOL MatrixDialog::CheckDimensions(int nMatAM, int nMatAN, int nMatBM, int nMatBN) {
    if (nMatAN != nMatBM) {
        AfxMessageBox(L"Количество столбцов первой матрицы должно совпадать с количеством строк второй матрицы!");
        return false;
    }
    else if (nMatAM * nMatAN * nMatBN < 1) {
        AfxMessageBox(L"Количество строк и столбцов матрицы должно быть больше 0");
        return false;
    }
    
    return true;
}

/// Проверка ввода элементов матрицы
BOOL MatrixDialog::CheckMatrixInput(LPWSTR& sInput) {
    int k = int(sInput[0]);
    UINT delimeter = 0;

    /// Первый элемент либо "-", либо цифра
    if ((k != 45 && k < 48) || k > 57) {
        return FALSE;
    }

    /// Последующие символы цифры или разделитель (строго один)
    for (int i = 1; i < wcslen(sInput); i++) {
        k = int(sInput[i]);
        if (k == 46) {
            delimeter++;
        } else if (k > 57 || k < 48) {
            return FALSE;
        }
    }

    if (delimeter > 1) {
        return FALSE;
    }

    /// Записываем в глобальную переменную какого типа у нас матрица int или double
    iDelimeter = max(iDelimeter, delimeter);
    return TRUE;
}

BEGIN_MESSAGE_MAP(MatrixDialog, CDialogEx)
ON_BN_CLICKED(IDC_BUTTON1, &MatrixDialog::OnBtnClickedSetSize)
ON_BN_CLICKED(IDC_BUTTON2, &MatrixDialog::OnBtnClickedCalculate)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_NOTIFY_EX_RANGE(NM_CLICK, IDC_LIST_A, IDC_LIST_B, OnNMClickList)
ON_MESSAGE(WM_NOTIFY_DESCRIPTION_EDITED, OnNotifyDescriptionEdited)
END_MESSAGE_MAP()


/// Обработчики сообщений MatrixDialog
/// Задание размеров матриц по нажатию кнопки
void MatrixDialog::OnBtnClickedSetSize() { 
	int nMatAM, nMatAN, nMatBM, nMatBN;

	m_EditMatAM.GetWindowTextW(sSize);
    nMatAM = _wtoi(sSize);
    m_EditMatAN.GetWindowTextW(sSize);
    nMatAN = _wtoi(sSize);
    m_EditMatBM.GetWindowTextW(sSize);
    nMatBM = _wtoi(sSize);
    m_EditMatBN.GetWindowTextW(sSize);
    nMatBN = _wtoi(sSize);
    
    if (CheckDimensions(nMatAM, nMatAN, nMatBM, nMatBN)) {
        SetInitialCListCtrlMatrices(nMatAM, nMatAN, nMatBM, nMatBN);
    }
 }

/// Обработчик нажатия кнопки расчета матриц
void MatrixDialog::OnBtnClickedCalculate() {
    CHeaderCtrl* pHeaderCtrlA = aListCtrlMatA.GetHeaderCtrl();
    CHeaderCtrl* pHeaderCtrlB = aListCtrlMatB.GetHeaderCtrl();
    int i_col_a = pHeaderCtrlA->GetItemCount();
    int i_col_b = pHeaderCtrlB->GetItemCount();
    int i_row_a = aListCtrlMatA.GetItemCount();
    int i_row_b = aListCtrlMatB.GetItemCount();

    /// создание объектов матриц для расчета
    Matrix mat_a(i_row_a, i_col_a);
    Matrix mat_b(i_row_b, i_col_b);
    Matrix mat_c(i_row_a, i_col_b);

    CString s_element;
    
    /// Заполнение матриц
    for (int j = 0; j < i_col_a; j++) {
        for (int i = 0; i < i_row_a; i++) {
            mat_a[i][j] = _wtof(aListCtrlMatA.GetItemText(i, j));
        }
        for (int k = 0; k < i_col_b; k++) {
            mat_b[j][k] = _wtof(aListCtrlMatB.GetItemText(j, k));
        }
    }
    
    mat_c = mat_a * mat_b;

    /// Вывод в дилоговое окно
    for (int i = 0; i < i_row_a; i++) {
        for (int j = 0; j < i_col_b; j++) {
            if (iDelimeter == 1) {
                s_element.Format(L"%5.2lf", mat_c[i][j]);
            } else {
                s_element.Format(L"%5.0lf", mat_c[i][j]);
            }
            aListCtrlMatC.SetItemText(i, j, s_element);
            aListCtrlMatC.SetColumnWidth(j, LVSCW_AUTOSIZE_USEHEADER);
        }
    }
}

/// Обработка клика ЛВМ по управляющему элементу списка
BOOL MatrixDialog::OnNMClickList(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{

    switch (id)
    {
    case IDC_LIST_A:
        aListCtrlMatA.OnLButtonDown(MK_LBUTTON, InterviewListCursorPosition(id));
        break;
    case IDC_LIST_B:
        aListCtrlMatB.OnLButtonDown(MK_LBUTTON, InterviewListCursorPosition(id));
        break;
    default:
        return FALSE;
    }
   
    *pResult = 0;

    return TRUE;
}

/// Обновление значение матриц при вводе
LRESULT MatrixDialog::OnNotifyDescriptionEdited(WPARAM wParam, LPARAM lParam)
{
    LV_DISPINFO* dispinfo = reinterpret_cast<LV_DISPINFO*>(lParam);
    if (!CheckMatrixInput(dispinfo->item.pszText)) {
        AfxMessageBox(L"Можно ввести только вещественное число");
        return -1;
    }

    switch (wParam){
        case IDC_LIST_A:
            aListCtrlMatA.SetItemText(dispinfo->item.iItem, dispinfo->item.iSubItem, dispinfo->item.pszText);
            aListCtrlMatA.SetColumnWidth(dispinfo->item.iSubItem, LVSCW_AUTOSIZE_USEHEADER);
            break;
        case IDC_LIST_B:
            aListCtrlMatB.SetItemText(dispinfo->item.iItem, dispinfo->item.iSubItem, dispinfo->item.pszText);
            aListCtrlMatB.SetColumnWidth(dispinfo->item.iSubItem, LVSCW_AUTOSIZE_USEHEADER);
            break;
        default:
            return -1;
    }  

    return 0;
}

/// Получение положения курсора
CPoint MatrixDialog::InterviewListCursorPosition(UINT id) const
{
    DWORD pos = GetMessagePos();
    CPoint pt(LOWORD(pos), HIWORD(pos));
    ScreenToClient(&pt);

    CRect rect;
    CWnd* pWnd = GetDlgItem(id);
    pWnd->GetWindowRect(&rect);
    ScreenToClient(&rect);

    pt.x -= rect.left;
    pt.y -= rect.top;
    return pt;
}

