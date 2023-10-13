#include "Types/Node.hpp"
#include "Types/Wire.hpp"

#include "BitUtils.hpp"

Wire::Wire(std::shared_ptr<Node> ppReceivingNode, unsigned int pNumBits) :
	mpReceivingNode(ppReceivingNode), mDataReady(false), mNumBits(pNumBits)
{
}

WireData Wire::GetData() const
{
	return mData;
}

void Wire::SetData(WireData pWireData)
{
	mData = BitUtils::TruncateBits(pWireData, mNumBits - 1, 0);
}

void Wire::SetDataReady(bool pDataReady)
{
	mDataReady = pDataReady;
	if (mpReceivingNode != nullptr && pDataReady)
	{
		mpReceivingNode->NotifyDataReady();
	}
}

AlwaysReadyWire::AlwaysReadyWire(std::shared_ptr<Node> ppReceivingNode, unsigned int pNumBits) :
	Wire(ppReceivingNode, pNumBits)
{
}