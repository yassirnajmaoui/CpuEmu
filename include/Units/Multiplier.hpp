#pragma once

#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

// Class defining a Node that does a operation defined in the given Lambda
// function which has a compile-time given number of inputs and outputs
template <size_t NOutputs>
class Multiplier : public Node
{
public:
	static constexpr size_t InputIndex = 0;

	template <size_t i>
	constexpr size_t GetOutputIndex()
	{
		static_assert(i < NOutputs);
		return i;
	}

	Multiplier(std::string pName = "Multiplier") : Node(1, NOutputs, pName) {}

	std::string GetInputPortName(unsigned int pIndex) const override
	{
		if(pIndex == InputIndex)
		{
			return "In";
		}
		return "";
	}

	std::string GetOutputPortName(unsigned int pIndex) const override
	{
		if(pIndex < GetNumberOfOutputWires())
		{
			return "Out " + std::to_string(pIndex);
		}
		return "";
	}

protected:
	void ProcessInternal() override
	{
		WireData lInput = GetWireData(InputIndex);
		for (size_t i = 0; i < NOutputs; ++i)
		{
			SetWireData(i, lInput);
		}
	}
};
