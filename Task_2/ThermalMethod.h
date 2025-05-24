#pragma once
#include <afxcoll.h>

namespace Models
{
class ThermalMethod final
{
public:
	enum class Value : uint8_t
	{
		StaticTemperature = 0,
		SteadyThermalFEA,
		TransientThermalFEA
	};

	ThermalMethod(Value method = Value::StaticTemperature)
		: m_value(method) {};
	~ThermalMethod() = default;

	Value	Get() const { return m_value; };
	void	Set(Value setValue) { m_value = setValue; };

private:
	Value m_value;
};
}