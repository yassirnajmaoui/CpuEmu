#pragma once

#include "Types/WireForward.hpp"

#include <memory>

class Node;

class Wire
{
public:
	Wire(std::shared_ptr<Node> ppReceivingNode = nullptr);
	Wire(const Wire&) = delete;

	WireData GetData() const;
	void SetData(WireData pWireData);

	virtual void SetDataReady(bool pDataReady = true);
	virtual bool IsDataReady() const { return mDataReady; }

protected:
	WireData mData;
	std::shared_ptr<Node> mpReceivingNode;
	bool mDataReady;
};
