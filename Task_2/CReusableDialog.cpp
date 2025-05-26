// CReusableDialog.cpp : implementation file
//

#include "pch.h"
#include "Task_2.h"
#include "afxdialogex.h"
#include "CReusableDialog.h"
#include "Converter.h"

#include <map>

namespace Dialogs
{
// CReusableDialog dialog

IMPLEMENT_DYNAMIC(CReusableDialog, CDialogEx)

	CReusableDialog::CReusableDialog(Type dialogType,
									Models::MethodCollection& methodData,
									CWnd* pParent /*=nullptr*/)
									: m_dialogType(dialogType),
									m_methodData(methodData),
									CDialogEx(IDD_REUSABLE_DIALOG, pParent)
{
}

void CReusableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOBOX, m_comboBox);
	DDX_Control(pDX, IDC_LABEL, m_label);
}


BEGIN_MESSAGE_MAP(CReusableDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBOBOX, &CReusableDialog::OnCbnSelchangeCombobox)
END_MESSAGE_MAP()

BOOL CReusableDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	switch (m_dialogType)
	{
	case CReusableDialog::Type::GroundWaterSetting:
		m_label.SetWindowTextW(CString("Ground Water Method:"));

		for (auto entry : Utilities::mapGroundWaterMethod)
			m_comboBox.AddString(entry.second);

		m_comboBox.SetCurSel(static_cast<int>(m_methodData.GetGroundWaterMethod()));
		break;
	case CReusableDialog::Type::ThermalSetting:
		m_label.SetWindowTextW(CString("Thermal Method:"));

		for (auto entry : Utilities::mapThermalMethod)
			m_comboBox.AddString(entry.second);

		m_comboBox.SetCurSel(static_cast<int>(m_methodData.GetThermalMethod()));
		break;
	}

	AdjustComboBoxDropHeight();
	return true;
}

// CReusableDialog message handlers
void CReusableDialog::OnCbnSelchangeCombobox()
{
	switch (m_dialogType)
	{
	case CReusableDialog::Type::GroundWaterSetting:
		m_methodData.SetGroundWaterMethod(static_cast<Models::GroundWaterMethod::Value>(m_comboBox.GetCurSel()));
		break;
	case CReusableDialog::Type::ThermalSetting:
		m_methodData.SetThermalMethod(static_cast<Models::ThermalMethod::Value>(m_comboBox.GetCurSel()));
		break;
	}
}

void CReusableDialog::AdjustComboBoxDropHeight()
{
	// Get the item height (height of one list item)
	int comboBoxHeight = m_comboBox.GetItemHeight(-1);  // -1 = Get height of the combobox
	int dropItemHeight = m_comboBox.GetItemHeight(0);  // Get height of dropdown item

	// Get current size and position
	CRect rect;
	m_comboBox.GetWindowRect(&rect);
	ScreenToClient(&rect);

	// Calculate total height: combobox control's height + ((number of visible items + 1) * item height)
	int totalHeight = comboBoxHeight + ((m_comboBox.GetCount() + 1) * dropItemHeight);

	// Resize the control (width and position stay the same)
	m_comboBox.MoveWindow(rect.left, rect.top, rect.Width(), totalHeight);
}
}