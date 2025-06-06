
// Task_2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Task_2.h"
#include "Task_2Dlg.h"
#include "Converter.h"
#include "CReusableDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTask2Dlg dialog



CTask2Dlg::CTask2Dlg(Models::MethodCollection& methodData, CWnd* pParent /*=nullptr*/)
	: m_methodData(methodData), CDialogEx(IDD_TASK_2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTask2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL1, m_groundWaterMethodLabel);
	DDX_Control(pDX, IDC_LABEL2, m_thermalMethodLabel);
}

BEGIN_MESSAGE_MAP(CTask2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTask2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTask2Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTask2Dlg message handlers

BOOL CTask2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTask2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTask2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTask2Dlg::OnBnClickedButton1()
{
	//Construct CReusableDialog
	Dialogs::CReusableDialog settingDialog(Dialogs::CReusableDialog::Type::GroundWaterSetting, m_methodData, this);

	//Launch CReusableDialog
	settingDialog.DoModal();

	//Post launch CReusableDialog 
	m_groundWaterMethodLabel.SetWindowTextW(Utilities::mapGroundWaterMethod.at(m_methodData.GetGroundWaterMethod()));
}


void CTask2Dlg::OnBnClickedButton2()
{
	//Construct CReusableDialog
	Dialogs::CReusableDialog settingDialog(Dialogs::CReusableDialog::Type::ThermalSetting, m_methodData, this);

	//Launch CReusableDialog
	settingDialog.DoModal();

	//Post launch CReusableDialog 
	m_thermalMethodLabel.SetWindowTextW(Utilities::mapThermalMethod.at(m_methodData.GetThermalMethod()));
}
