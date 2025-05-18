// CReusableDialog.cpp : implementation file
//

#include "pch.h"
#include "Task_2.h"
#include "afxdialogex.h"
#include "CReusableDialog.h"


// CReusableDialog dialog

IMPLEMENT_DYNAMIC(CReusableDialog, CDialogEx)

CReusableDialog::CReusableDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REUSABLE_DIALOG, pParent)
{

}

CReusableDialog::~CReusableDialog()
{
}

void CReusableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReusableDialog, CDialogEx)
END_MESSAGE_MAP()


// CReusableDialog message handlers
