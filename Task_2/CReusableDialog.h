#pragma once
#include "afxdialogex.h"
#include "MethodCollection.h"

// CReusableDialog dialog
// Marked final as the assignment scope is fixed, no more extension needed.

class CReusableDialog final : public CDialogEx
{
	DECLARE_DYNAMIC(CReusableDialog)

public:
	enum class Type : uint8_t
	{
		GroundWaterSetting = 0,
		ThermalSetting = 1
	};

	CReusableDialog(Type dialogType,
					Models::MethodCollection& methodData,
					CWnd* pParent = nullptr);   // standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REUSABLE_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()

private:
	Type				m_dialogType;

	CComboBox			m_comboBox;
	CStatic				m_label;

	Models::MethodCollection& m_methodData;

	void AdjustComboBoxDropHeight();

	afx_msg void OnCbnSelchangeCombobox();
};
