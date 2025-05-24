#pragma once
#include <map>
#include "GroundWaterMethod.h"
#include "ThermalMethod.h"

namespace Utilities
{
extern std::map<Models::GroundWaterMethod::Value, LPCWSTR> mapGroundWaterMethod;
extern std::map<Models::ThermalMethod::Value, LPCWSTR> mapThermalMethod;

CString ToString(Models::GroundWaterMethod::Value method);
CString ToString(Models::ThermalMethod::Value method);
uint8_t ToEnum(const CString& methodString);
}