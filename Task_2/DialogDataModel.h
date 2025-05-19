#pragma once
#include <afxcoll.h>

class DialogDataModel
{
public:
	enum SettingType
	{
		GroundWaterMethod,
		ThermalMethod
	};

	DialogDataModel(SettingType type, const CString& labelText, CStringArray* comboBoxOptions, int comboBoxSelectedIndex = 0)
		: m_settingType(type), m_labelText(labelText), m_pComboBoxOptions(comboBoxOptions), m_comboBoxSelectedIndex(comboBoxSelectedIndex) {};
	~DialogDataModel() = default;

	int				GetSettingType() const						{ return m_settingType; };
	CString			GetSettingLabelText() const					{ return m_labelText; };
	CStringArray*	GetSettingComboBoxOptions()					{ return m_pComboBoxOptions; };
	void			SetSelectedOptionIndex(int selectedIndex)	{ m_comboBoxSelectedIndex = selectedIndex; };
	int				GetSelectedOptionIndex() const				{ return m_comboBoxSelectedIndex; };

private:
	SettingType		m_settingType;
	CString			m_labelText;
	CStringArray*	m_pComboBoxOptions;
	int				m_comboBoxSelectedIndex;
};