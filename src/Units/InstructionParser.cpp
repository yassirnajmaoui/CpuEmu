#include "Units/InstructionParser.hpp"

#include "BitUtils.hpp"
#include "RISCV-Constants.hpp"
#include "Types/Wire.hpp"

InstructionParser::InstructionParser() : Node(1, 7, "Instruction parser") {}

void InstructionParser::ProcessInternal()
{
	WireData lInstruction = GetWireData(InstructionIndex);

	// Logic
	WireData opcode = BitUtils::TruncateBits(lInstruction, 6, 0);
	WireData rs1 = 0u;
	WireData rs2 = 0u;
	WireData rd = 0u;
	WireData funct3 = 0u;
	WireData sign_bit = 0u;
	WireData imm = 0u;

	if (opcode == OPCODE_R_TYPE)
	{
		// R-type instructions
		rd = BitUtils::TruncateBits(lInstruction, 11, 7);
		funct3 = BitUtils::TruncateBits(lInstruction, 14, 12);
		rs1 = BitUtils::TruncateBits(lInstruction, 19, 15);
		rs2 = BitUtils::TruncateBits(lInstruction, 24, 20);
		sign_bit = BitUtils::TruncateBits(lInstruction, 30, 30);
	}
	else if (opcode == OPCODE_I_TYPE /*Immediate arithmetic*/ || opcode == OPCODE_LOAD_TYPE /*Load instructions*/ ||
			 opcode == OPCODE_JALR /*for JALR*/ || opcode == OPCODE_FENCE /*for FENCE*/)
	{
		// I-type instructions
		rd = BitUtils::TruncateBits(lInstruction, 11, 7);
		funct3 = BitUtils::TruncateBits(lInstruction, 14, 12);
		rs1 = BitUtils::TruncateBits(lInstruction, 19, 15);
		BitUtils::SetBits(imm, 11, 0, BitUtils::TruncateBits(lInstruction, 31, 20));
		imm = BitUtils::SignExtend(imm, 12, 32);
	}
	else if (opcode == OPCODE_S_TYPE)
	{
		// S-type instructions
		funct3 = BitUtils::TruncateBits(lInstruction, 14, 12);
		rs1 = BitUtils::TruncateBits(lInstruction, 19, 15);
		rs2 = BitUtils::TruncateBits(lInstruction, 24, 20);
		BitUtils::SetBits(imm, 4, 0, BitUtils::TruncateBits(lInstruction, 11, 7));
		BitUtils::SetBits(imm, 11, 5, BitUtils::TruncateBits(lInstruction, 31, 25));
		imm = BitUtils::SignExtend(imm, 12, 32);
	}
	else if (opcode == OPCODE_J_TYPE)
	{
		// J-type instructions
		rd = BitUtils::TruncateBits(lInstruction, 11, 7);
		BitUtils::SetBits(imm, 10, 1, BitUtils::TruncateBits(lInstruction, 30, 21));
		BitUtils::SetBits(imm, 11, 11, BitUtils::TruncateBits(lInstruction, 20, 20));
		BitUtils::SetBits(imm, 19, 12, BitUtils::TruncateBits(lInstruction, 19, 12));
		BitUtils::SetBits(imm, 20, 20, BitUtils::TruncateBits(lInstruction, 31, 31));
		imm = BitUtils::SignExtend(imm, 20, 32);
	}
	else if (opcode == OPCODE_B_TYPE)
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
		imm = BitUtils::SignExtend(imm, 13, 32);
	}
	else if (opcode == OPCODE_LUI || opcode == OPCODE_AUIPC)
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
	SetWireData(SignBitIndex, sign_bit);
	SetWireData(ImmIndex, imm);
}

std::string InstructionParser::GetInputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case InstructionIndex:
		return "Instruction";
	default:
		return "";
	}
}

std::string InstructionParser::GetOutputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case OpcodeIndex:
		return "opcode";
	case RDIndex:
		return "rd";
	case RS1Index:
		return "rs1";
	case RS2Index:
		return "rs2";
	case Funct3Index:
		return "funct3";
	case SignBitIndex:
		return "sign_bit";
	case ImmIndex:
		return "imm";
	default:
		return "";
	}
}