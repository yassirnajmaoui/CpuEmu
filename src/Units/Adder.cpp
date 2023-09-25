#include "Units/Adder.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

Adder::Adder() :
	Node(2, 1)
{
}

void Adder::ProcessInternal()
{
	ASSERT(mInputWires[0] != nullptr, "Input wire 0 not set for AdderNode");
	ASSERT(mInputWires[1] != nullptr, "Input wire 1 not set for AdderNode");
	ASSERT(mOutputWires[0] != nullptr, "Output wire 0 not set for AdderNode");

	WireData lInput1 = GetWireData(Input1Index);
	WireData lInput2 = GetWireData(Input2Index);

	WireData lOutput = lInput1 + lInput2;
	
	mOutputWires[OutputIndex]->SetData(lOutput);
}
