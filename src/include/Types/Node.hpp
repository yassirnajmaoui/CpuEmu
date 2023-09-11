#pragma once

#include <vector>
#include <memory>

class Wire;

class Node
{
public:
	Node() = default;
	Node(const Node&) = delete;

	void Process();
	void ProcessDone();

	void AddInput(std::shared_ptr<Wire> ppWire);
	void AddOutput(std::shared_ptr<Wire> ppWire);

	void NotifyDataReady();

	static std::shared_ptr<Wire> ConnectNodes(std::shared_ptr<Node> ppSendingNode, std::shared_ptr<Node> ppReceivingNode);
	static std::shared_ptr<Wire> CreateInputWire(std::shared_ptr<Node> ppReceivingNode);
	static std::shared_ptr<Wire> CreateOutputWire(std::shared_ptr<Node> ppSendingNode);

protected:
	virtual void ProcessInternal() const = 0;

protected:
	std::vector<std::shared_ptr<Wire>> mInputWires;
	std::vector<std::shared_ptr<Wire>> mOutputWires;
};
