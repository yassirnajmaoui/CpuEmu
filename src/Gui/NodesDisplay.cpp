#include "Gui/NodesDisplay.hpp"
#include "imnodes.h"

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
		ImNodes::BeginInputAttribute(id++);
		ImGui::Text((std::string("Input ") + std::to_string(i)).c_str());
		ImNodes::EndInputAttribute();
	}
	for (size_t i = 0; i < lNumOutputs; i++)
	{
		ImNodes::BeginOutputAttribute(id++);
		ImGui::Text((std::string("Output ") + std::to_string(i)).c_str());
		ImNodes::EndOutputAttribute();
	}
	ImNodes::EndNode();
}

void NodesDisplay::DisplaySystem(const System& prSystem)
{
	size_t lNumNodes = prSystem.GetNumNodes();
	for(int i=0;i<lNumNodes;++i)
	{
		NodesDisplay::DisplayNode(prSystem.GetNode(i), i+15);
	}
}