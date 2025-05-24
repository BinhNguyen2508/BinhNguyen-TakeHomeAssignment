#include "pch.h"
#include "Converter.h"

namespace
{
constexpr uint8_t INITIALIZED_ENUM_RETURN = 99;
constexpr int MATCHED = 0;
}

namespace Utilities
{
std::map<Models::GroundWaterMethod::Value, LPCWSTR> mapGroundWaterMethod = {
{Models::GroundWaterMethod::Value::StaticWater, L"Static Water"},
{Models::GroundWaterMethod::Value::SteadyFEA, L"Steady FEA"},
{Models::GroundWaterMethod::Value::TransientFEA, L"Transient FEA"} };

std::map<Models::ThermalMethod::Value, LPCWSTR> mapThermalMethod = {
	{Models::ThermalMethod::Value::StaticTemperature, L"Static Temperature"},
	{Models::ThermalMethod::Value::SteadyThermalFEA, L"Steady Thermal FEA"},
	{Models::ThermalMethod::Value::TransientThermalFEA, L"Transient Thermal FEA"} };

CString ToString(Models::GroundWaterMethod::Value method)
{
	return mapGroundWaterMethod.at(method);
}

CString ToString(Models::ThermalMethod::Value method)
{
	return mapThermalMethod.at(method);
}

uint8_t ToEnum(const CString& methodString)
{
	uint8_t matchedEnum = INITIALIZED_ENUM_RETURN;

	if (methodString.Compare(L"Static Water") == MATCHED ||
		methodString.Compare(L"Static Temperature") == MATCHED)
	{
		matchedEnum = 0;
	}
	else if (methodString.Compare(L"Steady FEA") == MATCHED ||
		methodString.Compare(L"Steady Thermal FEA") == MATCHED)
	{
		matchedEnum = 1;
	}
	else if (methodString.Compare(L"Transient FEA") == MATCHED ||
		methodString.Compare(L"Transient Thermal FEA") == MATCHED)
	{
		matchedEnum = 2;
	}
	else
		throw("Invalid methodString!");

	return matchedEnum;
}
}