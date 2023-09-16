#include "Units/Multiplexer.hpp"
#include "Types/Wire.hpp"

Multiplexer::Multiplexer(size_t pNumberOfInputs) :
	Node(pNumberOfInputs + 1, 1)
{
}


void Multiplexer::ProcessInternal()
{
	// Note: The first input has to always be the Control
	WireData lControl = mInputWires[InputSelectionIndex]->GetData();
	if(lControl + 1 < mInputWires.size())
	{
		mOutputWires[InputSelectionIndex]->SetData(mInputWires[lControl + 1]->GetData());
	}
}
