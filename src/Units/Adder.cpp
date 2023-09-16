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

	WireData lInput0 = mInputWires[0]->GetData();
	WireData lInput1 = mInputWires[1]->GetData();

	WireData lOutput = lInput0 + lInput1;
	
	mOutputWires[OutputIndex]->SetData(lOutput);
}
