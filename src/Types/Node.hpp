#pragma once

#include "Utils.hpp"

#include <vector>
#include <memory>

class Wire;

class Node
{
public:
	Node(size_t pNumberOfInputWires, size_t pNumberOfOutputWires);
	Node(const Node&) = delete;

	void Process();
	void ProcessDone();

	void NotifyDataReady();

	size_t GetNumberOfInputWires() const { return mNumberOfInputWires; }
	size_t GetNumberOfOutputWires() const { return mNumberOfOutputWires; }

	static std::shared_ptr<Wire> ConnectNodes(	std::shared_ptr<Node> ppSendingNode,
												size_t pSendingNodeOutputIndex,
												std::shared_ptr<Node> ppReceivingNode,
												size_t pReceivingNodeInputIndex );

	static std::shared_ptr<Wire> CreateInputWire(	std::shared_ptr<Node> ppReceivingNode,
													size_t pReceivingNodeInputIndex );

	static std::shared_ptr<Wire> CreateOutputWire(	std::shared_ptr<Node> ppSendingNode,
													size_t pSendingNodeOutputIndex );
	
protected:
	virtual void ProcessInternal() = 0;

	WireData GetWireData(size_t pIndex) const;
	void SetWireData(size_t pIndex, WireData pWireData);

protected:
	std::vector<std::shared_ptr<Wire>> mInputWires;
	std::vector<std::shared_ptr<Wire>> mOutputWires;
	size_t mNumberOfInputWires;
	size_t mNumberOfOutputWires;
};
