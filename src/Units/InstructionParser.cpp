#include "Units/InstructionParser.hpp"
#include "Types/Wire.hpp"
#include "BitUtils.hpp"
#include "RISCV-constants.hpp"

#include <iostream>

InstructionParser::InstructionParser() :
	Node(1, 7)
{
}

void InstructionParser::ProcessInternal()
{
	std::cout << "GetWireData..." << std::endl;

	WireData lInstruction = GetWireData(InstructionIndex);

	std::cout << "Logic..." << std::endl;

	// Logic
	WireData opcode = BitUtils::TruncateBits(lInstruction, 6, 0);
	WireData rs1 = 0u;
	WireData rs2 = 0u;
	WireData rd = 0u;
	WireData funct3 = 0u;
	WireData funct7 = 0u;
	WireData imm = 0u;

	if(opcode == Opcode_R_type)
	{
		// R-type instructions
		rd = BitUtils::TruncateBits(lInstruction, 11, 7);
		funct3 = BitUtils::TruncateBits(lInstruction, 14, 12);
		rs1 = BitUtils::TruncateBits(lInstruction, 19, 15);
		rs2 = BitUtils::TruncateBits(lInstruction, 24, 20);
		funct7 = BitUtils::TruncateBits(lInstruction, 31, 25);
	}
	else if(
		opcode == 0b0010011 /*Immediate arithmetic*/ ||
		opcode == 0b0000011 /*Load instructions*/ ||
		opcode == 0b1100111 /*JALR*/ ||
		opcode == 0b0001111 /*FENCE*/)
	{
		// I-type instructions
		rd = BitUtils::TruncateBits(lInstruction, 11, 7);
		funct3 = BitUtils::TruncateBits(lInstruction, 14, 12);
		rs1 = BitUtils::TruncateBits(lInstruction, 19, 15);
		BitUtils::SetBits(imm, 11, 0, BitUtils::TruncateBits(lInstruction, 31, 20));
	}
	else if(opcode == Opcode_S_type)
	{
		// S-type instructions
		funct3 = BitUtils::TruncateBits(lInstruction, 14, 12);
		rs1 = BitUtils::TruncateBits(lInstruction, 19, 15);
		rs2 = BitUtils::TruncateBits(lInstruction, 24, 20);
		BitUtils::SetBits(imm, 4, 0, BitUtils::TruncateBits(lInstruction, 11, 7));
		BitUtils::SetBits(imm, 11, 5, BitUtils::TruncateBits(lInstruction, 31, 25));
	}
	else if(opcode == Opcode_J_type)
	{
		// J-type instructions
		rd = BitUtils::TruncateBits(lInstruction, 11, 7);
		BitUtils::SetBits(imm, 10, 1, BitUtils::TruncateBits(lInstruction, 30, 21));
		BitUtils::SetBits(imm, 11, 11, BitUtils::TruncateBits(lInstruction, 20, 20));
		BitUtils::SetBits(imm, 19, 12, BitUtils::TruncateBits(lInstruction, 19, 12));
		BitUtils::SetBits(imm, 20, 20, BitUtils::TruncateBits(lInstruction, 31, 31));
	}
	else if(opcode == Opcode_B_type)
	{
		// B-type instruction
		// Branch operations
		funct3 = BitUtils::TruncateBits(lInstruction, 14, 12);
		rs1 = BitUtils::TruncateBits(lInstruction, 19, 15);
		rs2 = BitUtils::TruncateBits(lInstruction, 24, 20);
		BitUtils::SetBits(imm, 4, 1, BitUtils::TruncateBits(lInstruction, 11, 8));
		BitUtils::SetBits(imm, 10, 5, BitUtils::TruncateBits(lInstruction, 30, 25));
		BitUtils::SetBits(imm, 11, 11, BitUtils::TruncateBits(lInstruction, 7, 7));
		BitUtils::SetBits(imm, 12, 12, BitUtils::TruncateBits(lInstruction, 31, 31));
	}
	else if(
		opcode == 0b0110111 /*LUI*/ ||
		opcode == 0b0010111 /*AUIPC*/)
	{
		// U-type instructions
		// Upper immediate operations
		rd = BitUtils::TruncateBits(lInstruction, 11, 7);
		BitUtils::SetBits(imm, 31, 12, BitUtils::TruncateBits(lInstruction, 31, 12));
	}
	else
	{
		// Unknown opcode
	}

	SetWireData(OpcodeIndex, opcode);
	SetWireData(RDIndex, rd);
	SetWireData(RS1Index, rs1);
	SetWireData(RS2Index, rs2);
	SetWireData(Funct3Index, funct3);
	SetWireData(Funct7Index, funct7);
	SetWireData(ImmIndex, imm);
}
