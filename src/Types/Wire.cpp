#include "Types/Wire.hpp"
#include "Types/Node.hpp"

Wire::Wire(std::shared_ptr<Node> ppReceivingNode) :
	mpReceivingNode(ppReceivingNode),
	mDataReady(false)
{

}

WireData Wire::GetData() const
{
	return mData;
}

void Wire::SetData(WireData pWireData)
{
	mData = pWireData;
}

void Wire::SetDataReady()
{
	mDataReady = true;
	if(mpReceivingNode != nullptr)
	{
		mpReceivingNode->NotifyDataReady();
	}
}
