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
protected:
	void ProcessInternal() const;

private:
	std::weak_ptr<Wire> mpReadData1;//input
	std::weak_ptr<Wire> mpReadData2;//input

	std::weak_ptr<Wire> mpZero;//output
	std::weak_ptr<Wire> mpALUResut;//output

	std::weak_ptr<Wire> mpALUControl;//input
};
