#include "pch.h"
#include "Converter.h"

namespace
{
constexpr uint8_t INITIALIZED_ENUM_RETURN = 99;
constexpr int IDENTICAL = 0;
}

namespace Utilities
{
const std::map<Models::GroundWaterMethod::Value, LPCWSTR> mapGroundWaterMethod = {
{Models::GroundWaterMethod::Value::StaticWater, L"Static Water"},
{Models::GroundWaterMethod::Value::SteadyFEA, L"Steady FEA"},
{Models::GroundWaterMethod::Value::TransientFEA, L"Transient FEA"} };

const std::map<Models::ThermalMethod::Value, LPCWSTR> mapThermalMethod = {
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

	if (methodString.Compare(L"Static Water") == IDENTICAL ||
		methodString.Compare(L"Static Temperature") == IDENTICAL)
	{
		matchedEnum = 0;
	}
	else if (methodString.Compare(L"Steady FEA") == IDENTICAL ||
		methodString.Compare(L"Steady Thermal FEA") == IDENTICAL)
	{
		matchedEnum = 1;
	}
	else if (methodString.Compare(L"Transient FEA") == IDENTICAL ||
		methodString.Compare(L"Transient Thermal FEA") == IDENTICAL)
	{
		matchedEnum = 2;
	}
	else
		throw("Invalid methodString!");

	return matchedEnum;
}
}