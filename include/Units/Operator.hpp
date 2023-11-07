#pragma once

#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

#include <functional>

// Class defining a Node that does a operation defined in the given Lambda
// function which has a compile-time given number of inputs and outputs
template <size_t NInputs, size_t NOutputs>
class Operator : public Node
{
public:
	template <size_t i>
	constexpr size_t GetOutputIndex()
	{
		static_assert(i < NOutputs);
		return i;
	}
	template <size_t i>
	constexpr size_t GetInputIndex()
	{
		static_assert(i < NInputs);
		return i;
	}

	typedef std::function<std::array<WireData, NOutputs>(std::array<WireData, NInputs>)> WireFunctionNxM;

	Operator(WireFunctionNxM pWireFunction, std::string pName = "Operator") :
		Node(NInputs, NOutputs, pName), mWireFunction(pWireFunction)
	{
	}

	std::string GetInputPortName(unsigned int pIndex) const override
	{
		if(pIndex < GetNumberOfInputWires())
		{
			return "In " + std::to_string(pIndex);
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
		std::array<WireData, NInputs> lInputs;
		for (size_t i = 0; i < NInputs; ++i)
		{
			lInputs[i] = GetWireData(i);
		}

		auto lOutputs = mWireFunction(lInputs);
		for (size_t i = 0; i < NOutputs; ++i)
		{
			SetWireData(i, lOutputs[i]);
		}
	}

private:
	WireFunctionNxM mWireFunction;
};
