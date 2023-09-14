#include "Types/Node.hpp"
#include "Types/Wire.hpp"

void Node::Process()
{
    ProcessInternal();
    ProcessDone();
}

void Node::ProcessDone()
{
    for(auto lpOutputWire : mOutputWires)
    {
        lpOutputWire->SetDataReady();
    }
}

void Node::AddInput(std::shared_ptr<Wire> ppWire)
{
    mInputWires.push_back(ppWire);
}

void Node::AddOutput(std::shared_ptr<Wire> ppWire)
{
    mOutputWires.push_back(ppWire);
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
    Process();
}

std::shared_ptr<Wire> Node::ConnectNodes(std::shared_ptr<Node> ppSendingNode, std::shared_ptr<Node> ppReceivingNode)
{
	auto pWire = std::make_shared<Wire>(ppReceivingNode);
	ppReceivingNode->AddInput(pWire);
	ppSendingNode->AddOutput(pWire);
	return pWire;
}

std::shared_ptr<Wire> Node::CreateInputWire(std::shared_ptr<Node> ppReceivingNode)
{
	auto pWire = std::make_shared<Wire>(ppReceivingNode);
	ppReceivingNode->AddInput(pWire);
	return pWire;
}

std::shared_ptr<Wire> Node::CreateOutputWire(std::shared_ptr<Node> ppSendingNode)
{
	auto pWire = std::make_shared<Wire>();
	ppSendingNode->AddOutput(pWire);
	return pWire;
}
