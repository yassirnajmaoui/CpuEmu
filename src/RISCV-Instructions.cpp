#include "RISCV-Instructions.hpp"

#include "BitUtils.hpp"

#include "RISCV-Constants.hpp"

namespace Instructions
{

	WireData GenerateRType(WireData rd, WireData rs1, WireData rs2, WireData funct3, WireData funct7)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 25, funct7);
		BitUtils::SetBits(lInstruction, 24, 20, rs2);
		BitUtils::SetBits(lInstruction, 19, 15, rs1);
		BitUtils::SetBits(lInstruction, 14, 12, funct3);
		BitUtils::SetBits(lInstruction, 11, 7, rd);
		BitUtils::SetBits(lInstruction, 6, 0, OPCODE_R_TYPE);
		return lInstruction;
	}

	WireData GenerateIType(WireData imm, WireData rs1, WireData funct3, WireData rd, WireData opcode)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 20, imm);
		BitUtils::SetBits(lInstruction, 19, 15, rs1);
		BitUtils::SetBits(lInstruction, 14, 12, funct3);
		BitUtils::SetBits(lInstruction, 11, 7, rd);
		BitUtils::SetBits(lInstruction, 6, 0, opcode);
		return lInstruction;
	}

	WireData GenerateSType(WireData imm, WireData rs2, WireData rs1, WireData funct3)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 25, BitUtils::TruncateBits(imm, 11, 5));
		BitUtils::SetBits(lInstruction, 24, 20, rs2);
		BitUtils::SetBits(lInstruction, 19, 15, rs1);
		BitUtils::SetBits(lInstruction, 14, 12, funct3);
		BitUtils::SetBits(lInstruction, 11, 7, BitUtils::TruncateBits(imm, 4, 0));
		BitUtils::SetBits(lInstruction, 6, 0, OPCODE_S_TYPE);
		return lInstruction;
	}

	WireData GenerateBType(WireData imm, WireData rs2, WireData rs1, WireData funct3)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 31, BitUtils::TruncateBits(imm, 12, 12));
		BitUtils::SetBits(lInstruction, 30, 25, BitUtils::TruncateBits(imm, 10, 5));
		BitUtils::SetBits(lInstruction, 24, 20, rs2);
		BitUtils::SetBits(lInstruction, 19, 15, rs1);
		BitUtils::SetBits(lInstruction, 14, 12, funct3);
		BitUtils::SetBits(lInstruction, 11, 8, BitUtils::TruncateBits(imm, 4, 1));
		BitUtils::SetBits(lInstruction, 7, 7, BitUtils::TruncateBits(imm, 11, 11));
		BitUtils::SetBits(lInstruction, 6, 0, OPCODE_B_TYPE);
		return lInstruction;
	}

	WireData GenerateUType(WireData imm, WireData rd, WireData opcode)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 12, imm);
		BitUtils::SetBits(lInstruction, 11, 7, rd);
		BitUtils::SetBits(lInstruction, 6, 0, opcode);
		return lInstruction;
	}

	WireData GenerateJType(WireData imm, WireData rd)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 31, BitUtils::TruncateBits(imm, 20, 20));
		BitUtils::SetBits(lInstruction, 30, 21, BitUtils::TruncateBits(imm, 10, 1));
		BitUtils::SetBits(lInstruction, 20, 20, BitUtils::TruncateBits(imm, 11, 11));
		BitUtils::SetBits(lInstruction, 19, 12, BitUtils::TruncateBits(imm, 19, 12));
		BitUtils::SetBits(lInstruction, 11, 7, rd);
		BitUtils::SetBits(lInstruction, 6, 0, OPCODE_J_TYPE);
		return lInstruction;
	}

	WireData LUI(WireData imm, WireData rd)
	{
		return GenerateUType(imm, rd, OPCODE_LUI);
	}
	WireData AUIPC(WireData imm, WireData rd)
	{
		return GenerateUType(imm, rd, OPCODE_AUIPC);
	}

	WireData JAL(WireData imm, WireData rd)
	{
		return GenerateJType(imm, rd);
	}

	WireData JALR(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_JALR, rd, OPCODE_JALR);
	}

	WireData BEQ(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, FUNCT3_BEQ);
	}
	WireData BNE(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, FUNCT3_BNE);
	}
	WireData BLT(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, FUNCT3_BLT);
	}
	WireData BGE(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, FUNCT3_BGE);
	}
	WireData BLTU(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, FUNCT3_BLTU);
	}
	WireData BGEU(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, FUNCT3_BGEU);
	}

	WireData LB(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_LB, rd, OPCODE_LOAD_TYPE);
	}
	WireData LH(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_LH, rd, OPCODE_LOAD_TYPE);
	}
	WireData LW(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_LW, rd, OPCODE_LOAD_TYPE);
	}
	WireData LBU(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_LBU, rd, OPCODE_LOAD_TYPE);
	}
	WireData LHU(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_LHU, rd, OPCODE_LOAD_TYPE);
	}

	WireData SB(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateSType(imm, rs2, rs1, FUNCT3_SB);
	}
	WireData SH(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateSType(imm, rs2, rs1, FUNCT3_SH);
	}
	WireData SW(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateSType(imm, rs2, rs1, FUNCT3_SW);
	}

	WireData ADDI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_ADD_SUB, rd, OPCODE_I_TYPE);
	}
	WireData SLTI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_SLT, rd, OPCODE_I_TYPE);
	}
	WireData SLTIU(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_SLTU, rd, OPCODE_I_TYPE);
	}
	WireData XORI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_XOR, rd, OPCODE_I_TYPE);
	}
	WireData ORI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_OR, rd, OPCODE_I_TYPE);
	}
	WireData ANDI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, FUNCT3_AND, rd, OPCODE_I_TYPE);
	}

	WireData SLLI(WireData rd, WireData rs1, WireData shamt)
	{
		return GenerateIType(shamt, rs1, FUNCT3_SLL, rd, OPCODE_I_TYPE);
	}
	WireData SRLI(WireData rd, WireData rs1, WireData shamt)
	{
		return GenerateIType(shamt, rs1, FUNCT3_SRL_SRA, rd, OPCODE_I_TYPE);
	}
	WireData SRAI(WireData rd, WireData rs1, WireData shamt)
	{
		WireData imm = shamt;
		BitUtils::SetBits(imm, 31, 25, FUNCT7_NEGATIVE);
		return GenerateIType(imm, rs1, FUNCT3_SRL_SRA, rd, OPCODE_I_TYPE);
	}
	WireData ADD(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_ADD_SUB, FUNCT7_POSITIVE);
	}
	WireData SUB(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_ADD_SUB, FUNCT7_NEGATIVE);
	}
	WireData SLL(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_SLL, FUNCT7_POSITIVE);
	}
	WireData SLT(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_SLT, FUNCT7_POSITIVE);
	}
	WireData SLTU(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_SLTU, FUNCT7_POSITIVE);
	}
	WireData XOR(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_XOR, FUNCT7_POSITIVE);
	}
	WireData SRL(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_SRL_SRA, FUNCT7_POSITIVE);
	}
	WireData SRA(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_SRL_SRA, FUNCT7_NEGATIVE);
	}
	WireData OR(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_OR, FUNCT7_POSITIVE);
	}
	WireData AND(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, FUNCT3_AND, FUNCT7_POSITIVE);
	}

}; // namespace Instructions