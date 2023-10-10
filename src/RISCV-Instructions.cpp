#include "RISCV-Instructions.hpp"

#include "BitUtils.hpp"

namespace Instructions
{

	WireData
	    GenerateRType(WireData rd, WireData rs1, WireData rs2, WireData funct3, WireData funct7)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 25, funct7);
		BitUtils::SetBits(lInstruction, 24, 20, rs2);
		BitUtils::SetBits(lInstruction, 19, 15, rs1);
		BitUtils::SetBits(lInstruction, 14, 12, funct3);
		BitUtils::SetBits(lInstruction, 11, 7, rd);
		BitUtils::SetBits(lInstruction, 6, 0, 0b0110011);
		return lInstruction;
	}

	WireData
	    GenerateIType(WireData imm, WireData rs1, WireData funct3, WireData rd, WireData opcode)
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
		BitUtils::SetBits(lInstruction, 6, 0, 0b0100011);
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
		BitUtils::SetBits(lInstruction, 6, 0, 0b1100011);
		return lInstruction;
	}

	WireData GenerateUType(WireData imm, WireData rd, WireData opcode)
	{
		WireData lInstruction = 0;
		BitUtils::SetBits(lInstruction, 31, 12, BitUtils::TruncateBits(imm, 31, 12));
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
		BitUtils::SetBits(lInstruction, 6, 0, 0b1101111);
		return lInstruction;
	}

	WireData LUI(WireData imm, WireData rd)
	{
		return GenerateUType(imm, rd, 0b110111);
	}
	WireData AUIPC(WireData imm, WireData rd)
	{
		return GenerateUType(imm, rd, 0b0010111);
	}

	WireData JAL(WireData imm, WireData rd)
	{
		return GenerateJType(imm, rd);
	}

	WireData JALR(WireData rd, WireData rs1, WireData imm)
	{
		return GenerateIType(imm, rs1, 0b000, rd, 0b1100111);
	}

	WireData BEQ(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, 0b000);
	}
	WireData BNE(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, 0b001);
	}
	WireData BLT(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, 0b100);
	}
	WireData BGE(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, 0b101);
	}
	WireData BLTU(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, 0b110);
	}
	WireData BGEU(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateBType(imm, rs2, rs1, 0b111);
	}

	WireData LB(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b000, rd, 0b0000011);
	}
	WireData LH(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b001, rd, 0b0000011);
	}
	WireData LW(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b010, rd, 0b0000011);
	}
	WireData LBU(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b100, rd, 0b0000011);
	}
	WireData LHU(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b101, rd, 0b0000011);
	}

	WireData SB(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateSType(imm, rs2, rs1, 0b000);
	}
	WireData SH(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateSType(imm, rs2, rs1, 0b001);
	}
	WireData SW(WireData imm, WireData rs1, WireData rs2)
	{
		return GenerateSType(imm, rs2, rs1, 0b010);
	}

	WireData ADDI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b000, rd, 0b0010011);
	}
	WireData SLTI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b010, rd, 0b0010011);
	}
	WireData SLTIU(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b011, rd, 0b0010011);
	}
	WireData XORI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b100, rd, 0b0010011);
	}
	WireData ORI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b110, rd, 0b0010011);
	}
	WireData ANDI(WireData imm, WireData rd, WireData rs1)
	{
		return GenerateIType(imm, rs1, 0b111, rd, 0b0010011);
	}

	WireData SLLI(WireData rd, WireData rs1, WireData shamt)
	{
		return GenerateIType(shamt, rs1, 0b001, rd, 0b0010011);
	}
	WireData SRLI(WireData rd, WireData rs1, WireData shamt)
	{
		return GenerateIType(shamt, rs1, 0b101, rd, 0b0010011);
	}
	WireData SRAI(WireData rd, WireData rs1, WireData shamt)
	{
		WireData imm = shamt;
		BitUtils::SetBits(imm, 31, 25, 0b0100000);
		return GenerateIType(imm, rs1, 0b101, rd, 0b0010011);
	}
	WireData ADD(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b000, 0b0000000);
	}
	WireData SUB(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b000, 0b0100000);
	}
	WireData SLL(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b001, 0b0000000);
	}
	WireData SLT(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b010, 0b0000000);
	}
	WireData SLTU(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b011, 0b0000000);
	}
	WireData XOR(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b100, 0b0000000);
	}
	WireData SRL(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b101, 0b0000000);
	}
	WireData SRA(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b101, 0b0100000);
	}
	WireData OR(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b110, 0b0000000);
	}
	WireData AND(WireData rd, WireData rs1, WireData rs2)
	{
		return GenerateRType(rd, rs1, rs2, 0b111, 0b0000000);
	}

};  // namespace Instructions