#include "Units/Multiplexer.hpp"
#include "Types/Wire.hpp"

void Multiplexer::ProcessInternal() const
{
	WireData lControl = mInputWires[0]->GetData();
	if(lControl + 1 < mInputWires.size())
	{
		mOutputWires[0]->SetData(mInputWires[lControl+1]->GetData());
	}
}
