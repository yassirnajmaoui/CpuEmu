#include "Types/Wire.hpp"

#include "BitUtils.hpp"

Wire::Wire(std::shared_ptr<Port> ppSendingPort, std::shared_ptr<Port> ppReceivingPort, unsigned int pNumBits):
	mpSendingPort(ppSendingPort), mpReceivingPort(ppReceivingPort), mDataReady(false), mNumBits(pNumBits)
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
	if (mpReceivingPort != nullptr && pDataReady)
	{
		mpReceivingPort->NotifyDataReady();
	}
}

int Wire::GetSendingPortId() const
{
	if(mpSendingPort==nullptr)
	{
		return -1;
	}
	return mpSendingPort->GetId();
}

int Wire::GetReceivingPortId() const
{
	if(mpReceivingPort==nullptr)
	{
		return -1;
	}
	return mpReceivingPort->GetId();
}

AlwaysReadyWire::AlwaysReadyWire(std::shared_ptr<Port> ppReceivingPort, unsigned int pNumBits) :
	Wire(nullptr, ppReceivingPort, pNumBits)
{
}