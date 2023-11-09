#include "BinToString.hpp"
#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

#include <bitset>
#include <string>

Node::Node(size_t pNumberOfInputWires, size_t pNumberOfOutputWires, std::string pName) : mName(pName)
{
	mInputPorts.resize(pNumberOfInputWires);
	mOutputPorts.resize(pNumberOfOutputWires);
}

void Node::NotifyDataReady()
{
	// Check if all the input wires are ready
	for (size_t i = 0; i < mInputPorts.size(); i++)
	{
		auto lpInputWire = mInputPorts[i]->GetWire();
		ASSERT(lpInputWire != nullptr, ("Input wire " + std::to_string(i) + " is undefined").c_str());
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
	for (int i = 0; i < mInputPorts.size(); i++)
	{
		std::cout << "Input  " << i << ": "
				  << BitUtils::ToBinString(mInputPorts[i]->GetWire()->GetData(),
										   mInputPorts[i]->GetWire()->GetNumBits())
				  << std::endl;
	}
}

void Node::DisplayOutputs() const
{
	// std::cout << "For node \"" << mName << "\" :\n";
	for (int i = 0; i < mOutputPorts.size(); i++)
	{
		std::cout << "Output " << i << ": "
				  << BitUtils::ToBinString(mOutputPorts[i]->GetWire()->GetData(),
										   mOutputPorts[i]->GetWire()->GetNumBits())
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
	for (auto lpInputWire : mInputPorts)
	{
		lpInputWire->GetWire()->SetDataReady(false);
	}

	// Set data read for all output wires, this will notify the corresponding
	// nodes
	for (auto lpOutputWire : mOutputPorts)
	{
		lpOutputWire->GetWire()->SetDataReady();
	}
}

WireData Node::GetWireData(size_t pIndex) const
{
	auto lpInputPort = mInputPorts[pIndex];
	ASSERT(lpInputPort != nullptr, ("Input port " + std::to_string(pIndex) + " is undefined").c_str());
	return lpInputPort->GetWire()->GetData();
}

void Node::SetWireData(size_t pIndex, WireData pWireData)
{
	auto lpOutputPort = mOutputPorts[pIndex];
	ASSERT(lpOutputPort != nullptr, ("Output port " + std::to_string(pIndex) + " is undefined").c_str());
	lpOutputPort->GetWire()->SetData(pWireData);
}

std::shared_ptr<Wire> Node::ConnectNodes(std::shared_ptr<Node> ppSendingNode,
										 size_t pSendingNodeOutputIndex,
										 std::shared_ptr<Node> ppReceivingNode,
										 size_t pReceivingNodeInputIndex,
										 unsigned int pNumBits)
{
	ASSERT(pSendingNodeOutputIndex < ppSendingNode->GetNumberOfOutputWires(),
		   "Sending node output index out of bounds");
	ASSERT(pReceivingNodeInputIndex < ppReceivingNode->GetNumberOfInputWires(),
		   "Receiving node input index out of bounds");

	auto lpOutputPort = std::make_shared<Port>(ppSendingNode->GetOutputPortName(pSendingNodeOutputIndex));
	auto lpInputPort = std::make_shared<Port>(ppReceivingNode->GetInputPortName(pReceivingNodeInputIndex));
	auto lpWire = std::make_shared<Wire>(lpOutputPort, lpInputPort, pNumBits);

	lpOutputPort->SetWire(lpWire);
	lpOutputPort->SetNode(ppSendingNode);
	lpInputPort->SetWire(lpWire);
	lpInputPort->SetNode(ppReceivingNode);

	ppSendingNode->mOutputPorts[pSendingNodeOutputIndex] = lpOutputPort;
	ppReceivingNode->mInputPorts[pReceivingNodeInputIndex] = lpInputPort;

	return lpWire;
}

std::shared_ptr<Wire> Node::CreateInputWire(std::shared_ptr<Node> ppReceivingNode,
											size_t pReceivingNodeInputIndex,
											unsigned int pNumBits,
											bool pAlwaysReady)
{
	ASSERT(pReceivingNodeInputIndex < ppReceivingNode->GetNumberOfInputWires(),
		   "Receiving node input index out of bounds");

	auto lpInputPort = std::make_shared<Port>(ppReceivingNode->GetInputPortName(pReceivingNodeInputIndex));

	auto lpWire = pAlwaysReady ? std::make_shared<AlwaysReadyWire>(lpInputPort, pNumBits)
							   : std::make_shared<Wire>(nullptr, lpInputPort, pNumBits);

	lpInputPort->SetWire(lpWire);
	lpInputPort->SetNode(ppReceivingNode);

	ppReceivingNode->mInputPorts[pReceivingNodeInputIndex] = lpInputPort;

	return lpWire;
}

std::shared_ptr<Wire>
Node::CreateOutputWire(std::shared_ptr<Node> ppSendingNode, size_t pSendingNodeOutputIndex, unsigned int pNumBits)
{
	ASSERT(pSendingNodeOutputIndex < ppSendingNode->GetNumberOfOutputWires(),
		   "Sending node output index out of bounds");

	auto lpOutputPort = std::make_shared<Port>(ppSendingNode->GetOutputPortName(pSendingNodeOutputIndex));

	auto lpWire = std::make_shared<Wire>(lpOutputPort, nullptr, pNumBits);

	lpOutputPort->SetWire(lpWire);
	lpOutputPort->SetNode(ppSendingNode);

	ppSendingNode->mOutputPorts[pSendingNodeOutputIndex] = lpOutputPort;

	return lpWire;
}

const Port& Node::GetInputPort(unsigned int pInputPortId) const
{
	return *mInputPorts[pInputPortId];
}

const Port& Node::GetOutputPort(unsigned int pOutputPortId) const
{
	return *mOutputPorts[pOutputPortId];
}

std::shared_ptr<Port> Node::GetInputPort(unsigned int pInputPortId)
{
	return mInputPorts[pInputPortId];
}

std::shared_ptr<Port> Node::GetOutputPort(unsigned int pOutputPortId)
{
	return mOutputPorts[pOutputPortId];
}

std::string Node::GetName() const
{
	return mName;
}
