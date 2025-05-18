
// Task_2Dlg.h : header file
//

#pragma once
#include "CReusableDialog.h"

// CTask2Dlg dialog
class CTask2Dlg : public CDialogEx
{
// Construction
public:
	CTask2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

private:
	CReusableDialog* m_pSettingDialog;
};
