#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

#include <bitset>
#include <string>

Node::Node(size_t pNumberOfInputWires, size_t pNumberOfOutputWires, std::string pName)
    : mNumberOfInputWires(pNumberOfInputWires),
      mNumberOfOutputWires(pNumberOfOutputWires),
      mName(pName)
{
	mInputWires.resize(mNumberOfInputWires);
	mOutputWires.resize(mNumberOfOutputWires);
}

void Node::NotifyDataReady()
{
	// Check if all the input wires are ready
	for (size_t i = 0; i < mInputWires.size(); i++)
	{
		auto lpInputWire = mInputWires[i];
		ASSERT(lpInputWire != nullptr,
		       ("Input wire " + std::to_string(i) + " is undefined").c_str());
		if (!lpInputWire->IsDataReady())
		{
			return;
		}
	}
	// All the input wires are ready, we can process
	// Potentially, this can be asynchronous, have a thread for each node
	Process();
}

void Node::DisplayInputs() const
{
	std::cout << "For node \"" << mName << "\" :\n";
	for (int i = 0; i < mInputWires.size(); i++)
	{
		std::cout << "Input " << i << ": " << std::bitset<32>{mInputWires[i]->GetData()}
		          << std::endl;
	}
}

void Node::DisplayOutputs() const
{
	// std::cout << "For node \"" << mName << "\" :\n";
	for (int i = 0; i < mOutputWires.size(); i++)
	{
		std::cout << "Output " << i << ": " << std::bitset<32>{mOutputWires[i]->GetData()}
		          << std::endl;
	}
}

void Node::Process()
{
	if (IsVerbose)
	{
		DisplayInputs();
	}

	ProcessInternal();

	if (IsVerbose)
	{
		DisplayOutputs();
	}

	ProcessDone();
}

void Node::ProcessDone()
{
	// Set the input wire's data as no longer ready since it has already been
	// processed
	for (auto lpInputWire : mInputWires)
	{
		lpInputWire->SetDataReady(false);
	}

	// Set data read for all output wires, this will notify the corresponding
	// nodes
	for (auto lpOutputWire : mOutputWires)
	{
		lpOutputWire->SetDataReady();
	}
}

WireData Node::GetWireData(size_t pIndex) const
{
	auto lpInputWire = mInputWires[pIndex];
	ASSERT(lpInputWire != nullptr,
	       ("Input wire " + std::to_string(pIndex) + " is undefined").c_str());
	return lpInputWire->GetData();
}

void Node::SetWireData(size_t pIndex, WireData pWireData)
{
	auto lpInputWire = mOutputWires[pIndex];
	ASSERT(lpInputWire != nullptr,
	       ("Input wire " + std::to_string(pIndex) + " is undefined").c_str());
	lpInputWire->SetData(pWireData);
}

std::shared_ptr<Wire> Node::ConnectNodes(std::shared_ptr<Node> ppSendingNode,
                                         size_t pSendingNodeOutputIndex,
                                         std::shared_ptr<Node> ppReceivingNode,
                                         size_t pReceivingNodeInputIndex)
{
	ASSERT(pSendingNodeOutputIndex < ppSendingNode->mNumberOfOutputWires,
	       "Sending node output index out of bounds");
	ASSERT(pReceivingNodeInputIndex < ppReceivingNode->mNumberOfInputWires,
	       "Receiving node input index out of bounds");

	auto lpWire = std::make_shared<Wire>(ppReceivingNode);
	ppSendingNode->mOutputWires[pSendingNodeOutputIndex] = lpWire;
	ppReceivingNode->mInputWires[pReceivingNodeInputIndex] = lpWire;
	return lpWire;
}

std::shared_ptr<Wire> Node::CreateInputWire(std::shared_ptr<Node> ppReceivingNode,
                                            size_t pReceivingNodeInputIndex)
{
	ASSERT(pReceivingNodeInputIndex < ppReceivingNode->mNumberOfInputWires,
	       "Receiving node input index out of bounds");

	auto lpWire = std::make_shared<Wire>(ppReceivingNode);
	ppReceivingNode->mInputWires[pReceivingNodeInputIndex] = lpWire;
	return lpWire;
}

std::shared_ptr<Wire> Node::CreateOutputWire(std::shared_ptr<Node> ppSendingNode,
                                             size_t pSendingNodeOutputIndex)
{
	ASSERT(pSendingNodeOutputIndex < ppSendingNode->mNumberOfOutputWires,
	       "Sending node output index out of bounds");

	auto lpWire = std::make_shared<Wire>();
	ppSendingNode->mOutputWires[pSendingNodeOutputIndex] = lpWire;
	return lpWire;
}
