#include "Units/Multiplexer.hpp"
#include "Types/Wire.hpp"

Multiplexer::Multiplexer(size_t pNumberOfInputs) :
	Node(pNumberOfInputs + 1, 1)
{
}


void Multiplexer::ProcessInternal()
{
	// Note: The first input has to always be the Control
	WireData lControl = GetWireData(InputSelectionIndex);
	if(lControl + 1 < mInputWires.size())
	{
		SetWireData(OutputIndex, GetWireData(lControl + 1));
	}
}
