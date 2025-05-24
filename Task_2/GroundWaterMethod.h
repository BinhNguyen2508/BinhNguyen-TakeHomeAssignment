#pragma once
#include <afxcoll.h>

namespace Models
{
class GroundWaterMethod final
{
public:
	enum class Value : uint8_t
	{
		StaticWater = 0,
		SteadyFEA,
		TransientFEA,
	};

	GroundWaterMethod(Value method = Value::StaticWater)
		: m_value(method) {};
	~GroundWaterMethod() = default;

	Value	Get() const { return m_value; };
	void	Set(Value setValue) { m_value = setValue; };

private:
	Value m_value;
};
}