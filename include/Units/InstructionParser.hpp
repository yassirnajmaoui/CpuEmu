#pragma once

#include "Types/Node.hpp"

class InstructionParser : public Node
{
public:
	// Inputs
	static constexpr size_t InstructionIndex = 0;

	// Outputs
	static constexpr size_t OpcodeIndex = 0;
	static constexpr size_t RDIndex = 1;
	static constexpr size_t RS1Index = 2;
	static constexpr size_t RS2Index = 3;
	static constexpr size_t Funct3Index = 4;
	static constexpr size_t SignBitIndex = 5;
	static constexpr size_t ImmIndex = 6;

	InstructionParser();

	std::string GetInputPortName(unsigned int pIndex) const override;
	std::string GetOutputPortName(unsigned int pIndex) const override;

protected:
	void ProcessInternal() override;
};
