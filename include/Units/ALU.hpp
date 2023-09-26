#pragma once

#include "Types/Node.hpp"
#include "Utils.hpp"

class ALU : public Node
{
public:
	// Inputs
	static constexpr size_t RD1Index = 0;
	static constexpr size_t RD2Index = 1;
	static constexpr size_t ALUSelectIndex = 2;

	// Outputs
	static constexpr size_t ALUResultIndex = 0;
	static constexpr size_t ALUZeroIndex = 1;

	ALU();
	
protected:
	void ProcessInternal();
};
