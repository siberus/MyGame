// COptionDialog.cpp: файл реализации
//

#include "pch.h"
#include "MyGame.h"
#include "afxdialogex.h"
#include "COptionDialog.h"


// Диалоговое окно COptionDialog

IMPLEMENT_DYNAMIC(COptionDialog, CDialog)

COptionDialog::COptionDialog(bool bRowColumn, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_nValue1(0)
	, m_nValue2(0)
	, m_bRowColumnDialog(bRowColumn)
{

}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, m_nValue1);
	DDX_Text(pDX, IDC_EDIT_VALUE_2, m_nValue2);
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, 
		& COptionDialog::OnBnClickedButtonDefaults)
END_MESSAGE_MAP()

void COptionDialog::OnBnClickedButtonDefaults() 
{ 
	
	// Отдельно рассматриваем два варианта 
	if(m_bRowColumnDialog) 
		m_nValue1 = m_nValue2 = 15; // размер доски 15x15 
	else 
		m_nValue1 = m_nValue2 = 35; // размер блоков 35x35 

	// Обновляем параметры элементов до новых значений 
	UpdateData(false); 
}

// Обработчики сообщений COptionDialog


BOOL COptionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	if (m_bRowColumnDialog) 
	{ 
		// Сначала обновляем заголовок диалогового окна 
		SetWindowText(_T("Update Block Count")); 
		// Затем обновляем элементы «Static Text» 
		m_ctrlStaticText1.SetWindowText(_T("Строк"));
		m_ctrlStaticText2.SetWindowText(_T("Столбцов")); 
	} 
	else
	{
		// Сначала обновляем заголовок диалогового окна 
		SetWindowText(_T("Update Block Size"));

		// Затем обновляем элементы «Static Text» 
		m_ctrlStaticText1.SetWindowText(_T("Ширина блока"));
		m_ctrlStaticText2.SetWindowText(_T("Высота блока"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
