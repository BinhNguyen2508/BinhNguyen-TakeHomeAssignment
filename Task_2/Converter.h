#pragma once
#include <map>
#include "GroundWaterMethod.h"
#include "ThermalMethod.h"

namespace Utilities
{
extern const std::map<Models::GroundWaterMethod::Value, LPCWSTR> mapGroundWaterMethod;
extern const std::map<Models::ThermalMethod::Value, LPCWSTR> mapThermalMethod;

extern CString ToString(Models::GroundWaterMethod::Value method);
extern CString ToString(Models::ThermalMethod::Value method);
extern uint8_t ToEnum(const CString& methodString);
}