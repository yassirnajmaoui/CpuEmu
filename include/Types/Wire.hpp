#pragma once

#include "Types/WireForward.hpp"
#include "Types/Port.hpp"

#include <memory>

class Node;

class Wire
{
public:
	Wire(std::shared_ptr<Port> ppSendingPort, std::shared_ptr<Port> ppReceivingPort, unsigned int pNumBits = 32u);
	Wire(const Wire &) = delete;

	WireData GetData() const;
	void SetData(WireData pWireData);

	virtual void SetDataReady( bool pDataReady = true );
	virtual bool IsDataReady() const { return mDataReady; }

	int GetSendingPortId() const;
	int GetReceivingPortId() const;

	virtual unsigned int GetNumBits() const {return mNumBits;}

protected:
	WireData mData;
	std::shared_ptr<Port> mpSendingPort;
	std::shared_ptr<Port> mpReceivingPort;
	bool mDataReady;
	unsigned int mNumBits;
};

// Useful for some input ports
class AlwaysReadyWire : public Wire
{
public:
	AlwaysReadyWire(std::shared_ptr<Port> ppReceivingPort, unsigned int pNumBits = 32u);

	virtual bool IsDataReady() const { return true; }
};
