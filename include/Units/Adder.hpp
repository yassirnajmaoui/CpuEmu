#pragma once

#include "Types/Node.hpp"

class Adder : public Node
{
public:
	// Inputs
	static constexpr size_t Input1Index = 0;
	static constexpr size_t Input2Index = 1;

	// Outputs
	static constexpr size_t OutputIndex = 0;

	Adder();

	std::string GetInputPortName(unsigned int pIndex) const override;
	std::string GetOutputPortName(unsigned int pIndex) const override;

protected:
	void ProcessInternal() override;
};
