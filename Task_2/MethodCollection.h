#pragma once
#include <afxcoll.h>
#include "GroundWaterMethod.h"
#include "ThermalMethod.h"

namespace Models
{
class MethodCollection
{
public:
	MethodCollection(GroundWaterMethod& groundWaterMethod,
		ThermalMethod& thermalMethod)
		: m_groundWaterMethod(groundWaterMethod),
		m_thermalMethod(thermalMethod) {};
	~MethodCollection() = default;

	GroundWaterMethod::Value	GetGroundWaterMethod() const { return m_groundWaterMethod.Get(); };
	void						SetGroundWaterMethod(GroundWaterMethod::Value method) { m_groundWaterMethod.Set(method); };

	ThermalMethod::Value	GetThermalMethod() const { return m_thermalMethod.Get(); };
	void					SetThermalMethod(ThermalMethod::Value method) { m_thermalMethod.Set(method); };

private:
	GroundWaterMethod& m_groundWaterMethod;
	ThermalMethod& m_thermalMethod;
};
}