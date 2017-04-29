// OpenGLDialogDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "MFCOpenGL.h"
#include "OpenGLDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// диалоговое окно COpenGLDialogDlg

IMPLEMENT_DYNAMIC(COpenGLDialogDlg, CDialog) //	?

COpenGLDialogDlg::COpenGLDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenGLDialogDlg::IDD, pParent)
	, length(1)
	, width(1)
	, height(1)
	, delta_x(0)
	, delta_y(0)
	, delta_z(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

COpenGLDialogDlg::~COpenGLDialogDlg()
{
}

void COpenGLDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_LENGTH, length);
	DDX_Text(pDX, IDC_EDIT_LENGTH, length);
	DDX_Text(pDX, IDC_EDIT_WIDTH, width);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, height);
	DDX_Text(pDX, IDC_EDIT_DELTA_X, delta_x);
	DDX_Text(pDX, IDC_EDIT_DELTA_Y, delta_y);
	DDX_Text(pDX, IDC_EDIT_DELTA_Z, delta_z);
}


BEGIN_MESSAGE_MAP(COpenGLDialogDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_APPLY_CHANGES, &COpenGLDialogDlg::OnBnClickedButtonApplyChanges)
	ON_BN_CLICKED(IDC_BUTTON_FILL_IN, &COpenGLDialogDlg::OnBnClickedButtonFillIn)
END_MESSAGE_MAP()


// обработчики сообщений COpenGLDialogDlg

BOOL COpenGLDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Установка иконки приложения
	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE); 
	
	// Получение параметров окна для openGL
	CRect rect;

	GetDlgItem(IDC_OPENGL_WINDOW)->GetWindowRect(rect);
	
	ScreenToClient(rect);

	openGLControl.oglCreate(rect,this);

	openGLControl.m_unpTimer = openGLControl.SetTimer(1, 1, 0);

	return TRUE;
}

void COpenGLDialogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR COpenGLDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COpenGLDialogDlg::OnBnClickedButtonApplyChanges()
{
	// Обрабатывает нажатие кнопки "Применить"
	// Изменяет параметры отображаемого объекта в openGL
	UpdateData(true); //Разрешаем считывать информацию
	//Передаём инфу в класс и тем самым изменяем
	openGLControl.m_length = length;
	openGLControl.m_width = width;
	openGLControl.m_height = height;
	openGLControl.oglRecalculate(); // изменяем размер
}


void COpenGLDialogDlg::OnBnClickedButtonFillIn()
{
	// Обрабатывает нажатие кнопки "Вписать"
	openGLControl.oglFillIn();
}

