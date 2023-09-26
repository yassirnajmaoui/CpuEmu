#pragma once

#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

#include <functional>

// Class defining a Node that does a operation defined in the given Lambda function which has a
// compile-time given number of inputs and outputs
template<size_t NInputs, size_t NOutputs>
class Operator : public Node
{
public:
	typedef std::function< std::array<WireData, NOutputs>(std::array<WireData, NInputs>) > WireFunctionNxM;

	Operator(WireFunctionNxM pWireFunction) :
		Node(NInputs, NOutputs),
		mWireFunction(pWireFunction)
	{
	}

	void ProcessInternal() override
	{
		std::array<WireData, NInputs> lInputs;
		for(size_t i = 0; i < NInputs; ++i)
		{
			lInputs[i] = GetWireData(i);
		}

		auto lOutputs = mWireFunction(lInputs);
		for(size_t i = 0; i < NOutputs; ++i)
		{
			SetWireData(i, lOutputs[i]);
		}
	}
private:
	WireFunctionNxM mWireFunction;
};