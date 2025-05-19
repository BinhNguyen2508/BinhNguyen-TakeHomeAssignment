#pragma once
#include "afxdialogex.h"
#include "DialogDataModel.h"

// CReusableDialog dialog

class CReusableDialog final : public CDialogEx
{
	DECLARE_DYNAMIC(CReusableDialog)

public:
	CReusableDialog(DialogDataModel& model, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CReusableDialog() = default;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REUSABLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	DialogDataModel&	m_model;
	CComboBox			m_comboBox;
	CStatic				m_label;

	void AdjustComboBoxDropHeight(CComboBox& comboBox, int visibleItems);

	afx_msg void OnCbnSelchangeCombobox();
};
