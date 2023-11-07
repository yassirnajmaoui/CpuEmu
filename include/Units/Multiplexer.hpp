#pragma once

#include "Types/Node.hpp"

template <size_t NInputs>
class Multiplexer : public Node
{
public:
	// Inputs
	static constexpr size_t InputSelectionIndex = 0;
	template <size_t i>
	constexpr size_t GetInputIndex()
	{
		static_assert(i < NInputs);
		return i + 1;
	}

	// Outputs
	static constexpr size_t OutputIndex = 0;

	Multiplexer(std::string pName = "Multiplexer") : Node(NInputs + 1, 1, pName) {}

	std::string GetInputPortName(unsigned int pIndex) const override
	{
		if(pIndex == InputSelectionIndex)
		{
			return "Select";
		}
		else if(pIndex < GetNumberOfInputWires())
		{
			return "Input " + std::to_string(pIndex + 1);
		}
		return "";
	}

	std::string GetOutputPortName(unsigned int pIndex) const override
	{
		if(pIndex == OutputIndex)
		{
			return "Output";
		}
		return "";
	}

protected:
	void ProcessInternal() override
	{
		// Note: The first input has to always be the Control
		WireData lControl = GetWireData(InputSelectionIndex);
		if (lControl + 1 < GetNumberOfInputWires() )
		{
			SetWireData(OutputIndex, GetWireData(lControl + 1));
		}
	}
};
