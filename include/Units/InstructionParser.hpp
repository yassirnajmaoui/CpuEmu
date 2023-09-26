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
	static constexpr size_t Funct7Index = 5;
	static constexpr size_t ImmIndex = 6;

	InstructionParser();

private:
	void ProcessInternal() override;
};