
// Task_2Dlg.h : header file
//

#pragma once
#include "MethodCollection.h"

// CTask2Dlg dialog
// Marked final as the assignment scope is fixed, no more extension needed.

class CTask2Dlg final : public CDialogEx
{
// Construction
public:
	CTask2Dlg(Models::MethodCollection& methodData, CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_2_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	BOOL OnInitDialog() override;
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

private:
	CStatic				m_groundWaterMethodLabel;
	CStatic				m_thermalMethodLabel;

	Models::MethodCollection&	m_methodData;
};
