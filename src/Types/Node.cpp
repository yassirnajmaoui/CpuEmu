#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

Node::Node(size_t pNumberOfInputWires, size_t pNumberOfOutputWires) :
	mNumberOfInputWires(pNumberOfInputWires),
	mNumberOfOutputWires(pNumberOfOutputWires)
{
	mInputWires.resize(mNumberOfInputWires);
	mOutputWires.resize(mNumberOfOutputWires);
}

void Node::NotifyDataReady()
{
	// Check if all the input wires are ready
	for(auto& lInputWire : mInputWires)
	{
		if(!lInputWire->IsDataReady())
		{
			return;
		}
	}
	// All the input wires are ready, we can process
	// Potentially, this can be asynchronous, have a thread for each node
	Process();
}

void Node::Process()
{
	ProcessInternal();
	ProcessDone();
}

void Node::ProcessDone()
{
	// Set data read for all output wires, this will notify the corresponding nodes
	for(auto lpOutputWire : mOutputWires)
	{
		lpOutputWire->SetDataReady();
	}

	// Set the input wire's data as no longer ready since it has already been processed
	for(auto lpInputWire : mInputWires)
	{
		lpInputWire->SetDataReady(false);
	}	
}

WireData Node::GetWireData(size_t pIndex) const
{
	return mInputWires[pIndex]->GetData();
}

void Node::SetWireData(size_t pIndex, WireData pWireData)
{
	mOutputWires[pIndex]->SetData(pWireData);
}

std::shared_ptr<Wire> Node::ConnectNodes(	std::shared_ptr<Node> ppSendingNode,
											size_t pSendingNodeOutputIndex,
											std::shared_ptr<Node> ppReceivingNode,
											size_t pReceivingNodeInputIndex )
{
	ASSERT(pSendingNodeOutputIndex < ppSendingNode->mNumberOfOutputWires, "Sending node output index out of bounds" );
	ASSERT(pReceivingNodeInputIndex < ppReceivingNode->mNumberOfInputWires, "Receiving node input index out of bounds" );

	auto lpWire = std::make_shared<Wire>(ppReceivingNode);
	ppSendingNode->mOutputWires[pSendingNodeOutputIndex] = lpWire;
	ppReceivingNode->mInputWires[pReceivingNodeInputIndex] = lpWire;
	return lpWire;
}

std::shared_ptr<Wire> Node::CreateInputWire(	std::shared_ptr<Node> ppReceivingNode,
												size_t pReceivingNodeInputIndex )
{
	ASSERT(pReceivingNodeInputIndex < ppReceivingNode->mNumberOfInputWires, "Receiving node input index out of bounds" );

	auto lpWire = std::make_shared<Wire>(ppReceivingNode);
	ppReceivingNode->mInputWires[pReceivingNodeInputIndex] = lpWire;
	return lpWire;
}

std::shared_ptr<Wire> Node::CreateOutputWire(	std::shared_ptr<Node> ppSendingNode,
												size_t pSendingNodeOutputIndex )
{
	ASSERT(pSendingNodeOutputIndex < ppSendingNode->mNumberOfOutputWires, "Sending node output index out of bounds" );

	auto lpWire = std::make_shared<Wire>();
	ppSendingNode->mOutputWires[pSendingNodeOutputIndex] = lpWire;
	return lpWire;
}
