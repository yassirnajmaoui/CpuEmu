#include "Units/Relay.hpp"

#include "Types/Wire.hpp"

Relay::Relay(std::string pName) : Node(2, 1, pName) {}

void Relay::ProcessInternal()
{
	SetWireData(OutputIndex, GetWireData(InputIndex));
}

std::string Relay::GetInputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case InputIndex:
		return "Input";
	case SignalIndex:
		return "Signal";
	default:
		return "";
	}
}

std::string Relay::GetOutputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case OutputIndex:
		return "Output";
	default:
		return "";
	}
}
