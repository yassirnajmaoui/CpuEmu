#include "Units/Adder.hpp"

#include "Types/Wire.hpp"
#include "Utils.hpp"

Adder::Adder() : Node(2, 1, "Adder") {}

void Adder::ProcessInternal()
{
	ASSERT(mInputPorts[Input1Index] != nullptr, "Input wire 1 not set for AdderNode");
	ASSERT(mInputPorts[Input2Index] != nullptr, "Input wire 2 not set for AdderNode");
	ASSERT(mOutputPorts[OutputIndex] != nullptr, "Output wire not set for AdderNode");

	WireData lInput1 = GetWireData(Input1Index);
	WireData lInput2 = GetWireData(Input2Index);

	WireData lOutput = lInput1 + lInput2;

	SetWireData(OutputIndex, lOutput);
}

std::string Adder::GetInputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case Input1Index:
		return "Input 1";
	case Input2Index:
		return "Input 2";
	default:
		return "";
	}
}

std::string Adder::GetOutputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case OutputIndex:
		return "Output";
	default:
		return "";
	}
}
