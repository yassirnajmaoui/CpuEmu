#pragma once

#include <memory>

class Node;

typedef unsigned long long WireData;

class Wire
{
public:
	Wire(std::shared_ptr<Node> pReceivingNode = nullptr);
	Wire(const Wire&) = delete;

	WireData GetData() const;
	void SetData(WireData pWireData);
	virtual void SetDataReady();

	bool IsDataReady() const {return mDataReady;}

protected:
	WireData mData;
	std::shared_ptr<Node> mpReceivingNode;
	bool mDataReady;
};
