#include "Gui/NodesDisplay.hpp"

#include "imnodes.h"

#include "Systems/System.hpp"

#include <string>

void NodesDisplay::DisplayNode(const Node& prNode, int pId)
{
	size_t lNumInputs = prNode.GetNumberOfInputWires();
	size_t lNumOutputs = prNode.GetNumberOfOutputWires();
	ImNodes::BeginNode(pId);
	ImNodes::BeginNodeTitleBar();
	ImGui::TextUnformatted(prNode.GetName().c_str());
	ImNodes::EndNodeTitleBar();
	size_t id = 0;
	for (size_t i = 0; i < lNumInputs; i++)
	{
		auto lrInputPort = prNode.GetInputPort(i);
		ImNodes::BeginInputAttribute(lrInputPort.GetId());
		ImGui::Text(lrInputPort.GetName().c_str());
		ImNodes::EndInputAttribute();
	}
	for (size_t i = 0; i < lNumOutputs; i++)
	{
		auto lrOutputPort = prNode.GetOutputPort(i);
		ImNodes::BeginOutputAttribute(lrOutputPort.GetId());
		ImGui::Text(lrOutputPort.GetName().c_str());
		ImNodes::EndOutputAttribute();
	}
	ImNodes::EndNode();
}

void NodesDisplay::DisplayWire(const Wire& prWire, int pId)
{
	int lSendingPortId = prWire.GetSendingPortId();
	int lReceivingPortId = prWire.GetReceivingPortId();
	if (lSendingPortId >= 0 && lReceivingPortId >= 0)
	{
		ImNodes::Link(pId, lSendingPortId, lReceivingPortId);
	}
}

void NodesDisplay::DisplaySystem(const System& prSystem)
{
	const size_t lNumNodes = prSystem.GetNumNodes();
	const size_t lNumWires = prSystem.GetNumWires();
	for (int i = 0; i < lNumNodes; ++i)
	{
		NodesDisplay::DisplayNode(prSystem.GetNode(i), i + 15);
	}
	for (int i = 0; i < lNumWires; ++i)
	{
		NodesDisplay::DisplayWire(prSystem.GetWire(i), i + 15 + lNumNodes);
	}
}