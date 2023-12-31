#pragma once

#include "Types/Node.hpp"

class Relay : public Node
{
public:
	// Inputs
	static constexpr size_t InputIndex = 0;
	static constexpr size_t SignalIndex = 1;

	// Outputs
	static constexpr size_t OutputIndex = 0;

	Relay(std::string pName = "Relay");

	std::string GetInputPortName(unsigned int pIndex) const override;
	std::string GetOutputPortName(unsigned int pIndex) const override;

protected:
	void ProcessInternal() override;
};
