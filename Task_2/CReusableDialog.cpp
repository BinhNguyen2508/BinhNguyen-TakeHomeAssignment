// CReusableDialog.cpp : implementation file
//

#include "pch.h"
#include "Task_2.h"
#include "afxdialogex.h"
#include "CReusableDialog.h"


// CReusableDialog dialog

IMPLEMENT_DYNAMIC(CReusableDialog, CDialogEx)

CReusableDialog::CReusableDialog(DialogDataModel& model, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REUSABLE_DIALOG, pParent), m_model(model)
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

	m_label.SetWindowTextW(m_model.GetSettingLabelText());
	
	CStringArray* modelComboBoxOptions = m_model.GetSettingComboBoxOptions();

	if (modelComboBoxOptions) {
		for (int i = 0; i < modelComboBoxOptions->GetCount(); i++)
			m_comboBox.AddString(modelComboBoxOptions->GetAt(i));

		AdjustComboBoxDropHeight(m_comboBox, modelComboBoxOptions->GetCount());
		m_comboBox.SetCurSel(m_model.GetSelectedOptionIndex());
	}

	return true;
}

// CReusableDialog message handlers
void CReusableDialog::OnCbnSelchangeCombobox()
{
	m_model.SetSelectedOptionIndex(m_comboBox.GetCurSel());
}

void CReusableDialog::AdjustComboBoxDropHeight(CComboBox& comboBox, int visibleItems)
{
	// Get the item height (height of one list item)
	int comboBoxHeight = comboBox.GetItemHeight(-1);  // -1 = Get height of the combobox
	int dropItemHeight = comboBox.GetItemHeight(0);  // Get height of dropdown item

	// Get current size and position
	CRect rect;
	comboBox.GetWindowRect(&rect);
	ScreenToClient(&rect);

	// Calculate total height: combobox control's height + ((number of visible items + 1) * item height)
	int totalHeight = comboBoxHeight + ((visibleItems + 1) * dropItemHeight);

	// Resize the control (width and position stay the same)
	comboBox.MoveWindow(rect.left, rect.top, rect.Width(), totalHeight);
}
