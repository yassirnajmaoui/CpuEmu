#pragma once

#include "Types/Node.hpp"
#include "Utils.hpp"

class Wire;

constexpr WireData ALUOP_ADD = 0b000;
constexpr WireData ALUOP_SLL = 0b001;
constexpr WireData ALUOP_XOR = 0b100;
constexpr WireData ALUOP_SRL = 0b101;
constexpr WireData ALUOP_SRA = 0b1101;//?
constexpr WireData ALUOP_OR = 0b110;
constexpr WireData ALUOP_AND = 0b111;

class ALU : public Node
{
public:
	// Inputs
	static constexpr size_t RD1Index = 0;
	static constexpr size_t RD2Index = 1;
	static constexpr size_t ALUControlIndex = 2;

	// Outputs
	static constexpr size_t ALUResultIndex = 0;
	static constexpr size_t ALUZeroIndex = 1;

	ALU();
protected:
	void ProcessInternal();
};
