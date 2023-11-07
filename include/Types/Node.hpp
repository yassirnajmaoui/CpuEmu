#pragma once

#include "Types/Port.hpp"

#include <memory>
#include <string>
#include <vector>

class Node
{
public:
	static constexpr bool IsVerbose = true;

	Node(size_t pNumberOfInputWires, size_t pNumberOfOutputWires, std::string pName = "Unnamed node");
	Node(const Node &) = delete;

	void Process();
	void ProcessDone();

	void NotifyDataReady();

	void DisplayInputs() const;
	void DisplayOutputs() const;

	size_t GetNumberOfInputWires() const { return mInputPorts.size(); }
	size_t GetNumberOfOutputWires() const { return mOutputPorts.size(); }

	std::string GetName() const;

	static std::shared_ptr<Wire> ConnectNodes(std::shared_ptr<Node> ppSendingNode,
											  size_t pSendingNodeOutputIndex,
											  std::shared_ptr<Node> ppReceivingNode,
											  size_t pReceivingNodeInputIndex,
											  unsigned int pNumBits = 32);

	static std::shared_ptr<Wire>
	CreateInputWire(std::shared_ptr<Node> ppReceivingNode, size_t pReceivingNodeInputIndex, unsigned int pNumBits = 32, bool pAlwaysReady = false);

	static std::shared_ptr<Wire>
	CreateOutputWire(std::shared_ptr<Node> ppSendingNode, size_t pSendingNodeOutputIndex, unsigned int pNumBits = 32);

protected:
	virtual void ProcessInternal() = 0;

	WireData GetWireData(size_t pIndex) const;
	void SetWireData(size_t pIndex, WireData pWireData);

protected:
	// TODO: create a vector of input ports and a vector of output ports
	// TODO: create a class InputPort that would have a name, an id, and a wire (same for OutputPort)
	// a Wire should connect an OutputPort to an InputPort
	std::vector<std::shared_ptr<Port>> mInputPorts;
	std::vector<std::shared_ptr<Port>> mOutputPorts;

	std::string mName;
};
