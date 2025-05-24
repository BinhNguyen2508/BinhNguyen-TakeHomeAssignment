#pragma once
#include "afxdialogex.h"
#include "DialogDataModel.h"

// CReusableDialog dialog
// Marked final as the assignment scope is fixed, no more extension needed.

class CReusableDialog final : public CDialogEx
{
	DECLARE_DYNAMIC(CReusableDialog)

public:
	CReusableDialog(DialogDataModel& model, CWnd* pParent = nullptr);   // standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REUSABLE_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()

private:
	DialogDataModel&	m_model;
	CComboBox			m_comboBox;
	CStatic				m_label;

	void AdjustComboBoxDropHeight(CComboBox& comboBox, int visibleItems);

	afx_msg void OnCbnSelchangeCombobox();
};
