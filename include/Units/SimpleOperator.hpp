#pragma once

#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

#include <functional>

// Class defining a Node that does a simple operation defined in the given
// Lambda function
class SimpleOperator : public Node
{
public:
	typedef std::function<WireData(WireData)> WireFunction1x1;

	// Inputs
	static constexpr size_t InputIndex = 0;

	// Outputs
	static constexpr size_t OutputIndex = 0;

	SimpleOperator(WireFunction1x1 pWireFunction,
	               std::string pName = "Simple Operator")
	    : Node(1, 1, pName), mWireFunction(pWireFunction)
	{
	}

protected:
	void ProcessInternal() override
	{
		SetWireData(OutputIndex, mWireFunction(GetWireData(InputIndex)));
	}

private:
	WireFunction1x1 mWireFunction;
};
