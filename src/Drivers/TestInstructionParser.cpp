#include "Types/Wire.hpp"
#include "Units/InstructionParser.hpp"

#include <iostream>
#include <memory>
#include <sstream>

struct ParsedInstruction
{
	WireData opcode;
	WireData rd;
	WireData rs1;
	WireData rs2;
	WireData funct3;
	WireData sign_bit;
	WireData imm;

	std::string ToString()
	{
		std::stringstream ss;
		ss << "opcode: " << opcode << ", rd: " << rd << ", rs1: " << rs1 << "\nrs2: " << rs2
		   << ", funct3: " << funct3 << ", sign_bit: " << sign_bit << "\nimm: " << imm << std::endl;
		return ss.str();
	}
};

int main()
{
	// clang-format off
	auto lInstructionParser = std::make_shared<InstructionParser>();

	// Input instruction
	auto lInstructionWire	= Node::CreateInputWire(lInstructionParser, InstructionParser::InstructionIndex);

	// Output wires
	auto lOpcodeWire	= Node::CreateOutputWire(lInstructionParser, InstructionParser::OpcodeIndex);
	auto lRDWire	= Node::CreateOutputWire(lInstructionParser, InstructionParser::RDIndex);
	auto lRS1Wire	= Node::CreateOutputWire(lInstructionParser, InstructionParser::RS1Index);
	auto lRS2Wire	= Node::CreateOutputWire(lInstructionParser, InstructionParser::RS2Index);
	auto lFunct3Wire	= Node::CreateOutputWire(lInstructionParser, InstructionParser::Funct3Index);
	auto lSignBitWire	= Node::CreateOutputWire(lInstructionParser, InstructionParser::SignBitIndex);
	auto lImmWire	= Node::CreateOutputWire(lInstructionParser, InstructionParser::ImmIndex);

	auto lTestInstructionFunc = [&](WireData pInstruction) -> ParsedInstruction
	{
		lInstructionWire->SetData(pInstruction);
		lInstructionWire->SetDataReady();
		// The instruction should automatically run on SetDataReady()
		ParsedInstruction lParsed;
		lParsed.opcode = lOpcodeWire->GetData();
		lParsed.rd = lRDWire->GetData();
		lParsed.rs1 = lRS1Wire->GetData();
		lParsed.rs2 = lRS2Wire->GetData();
		lParsed.funct3 = lFunct3Wire->GetData();
		lParsed.sign_bit = lSignBitWire->GetData();
		lParsed.imm = lImmWire->GetData();
		return lParsed;
	};

	// LUI
	auto lParsed = lTestInstructionFunc(0b10101010101010101010110110110111);
	std::cout << lParsed.ToString();

	// JAL
	lParsed = lTestInstructionFunc(0b10101010101010101000100111101111);
	std::cout << lParsed.ToString();

	// ADDI
	lParsed = lTestInstructionFunc(0b11111110000011111000100010110011);
	std::cout << lParsed.ToString();

	// clang-format on

	//...

	return 0;
}
