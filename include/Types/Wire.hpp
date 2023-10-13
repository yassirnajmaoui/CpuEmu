#pragma once

#include "Types/WireForward.hpp"

#include <memory>

class Node;

class Wire
{
public:
	Wire(std::shared_ptr<Node> ppReceivingNode = nullptr, unsigned int pNumBits = 32u);
	Wire(const Wire &) = delete;

	WireData GetData() const;
	void SetData(WireData pWireData);

	virtual void SetDataReady(bool pDataReady = true);
	virtual bool IsDataReady() const { return mDataReady; }

	virtual unsigned int GetNumBits() const {return mNumBits;}

protected:
	WireData mData;
	std::shared_ptr<Node> mpReceivingNode;
	bool mDataReady;
	unsigned int mNumBits;
};

class AlwaysReadyWire : public Wire
{
public:
	AlwaysReadyWire(std::shared_ptr<Node> ppReceivingNode = nullptr, unsigned int pNumBits = 32u);

	virtual bool IsDataReady() const { return true; }
};
