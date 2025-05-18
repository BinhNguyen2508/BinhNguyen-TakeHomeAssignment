#pragma once
#include "afxdialogex.h"


// CReusableDialog dialog

class CReusableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CReusableDialog)

public:
	CReusableDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CReusableDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REUSABLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
