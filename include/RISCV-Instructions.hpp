#pragma once

#include "Types/WireForward.hpp"

namespace Instructions
{
	// Primitives
	WireData GenerateRType(WireData rd, WireData rs1, WireData rs2, WireData funct3, WireData funct7);
	WireData GenerateIType(WireData imm, WireData rs1, WireData funct3, WireData rd, WireData opcode);
	WireData GenerateSType(WireData imm, WireData rs2, WireData rs1, WireData funct3);
	WireData GenerateBType(WireData imm, WireData rs2, WireData rs1, WireData funct3);
	WireData GenerateUType(WireData imm, WireData rd, WireData opcode);
	WireData GenerateJType(WireData imm, WireData rd);

	// Specific instructions
	WireData LUI(WireData imm, WireData rd);
	WireData AUIPC(WireData imm, WireData rd);

	WireData JAL(WireData imm, WireData rd);

	WireData JALR(WireData rd, WireData rs1, WireData imm);

	WireData BEQ(WireData imm, WireData rs1, WireData rs2);
	WireData BNE(WireData imm, WireData rs1, WireData rs2);
	WireData BLT(WireData imm, WireData rs1, WireData rs2);
	WireData BGE(WireData imm, WireData rs1, WireData rs2);
	WireData BLTU(WireData imm, WireData rs1, WireData rs2);
	WireData BGEU(WireData imm, WireData rs1, WireData rs2);

	WireData LB(WireData imm, WireData rd, WireData rs1);
	WireData LH(WireData imm, WireData rd, WireData rs1);
	WireData LW(WireData imm, WireData rd, WireData rs1);
	WireData LBU(WireData imm, WireData rd, WireData rs1);
	WireData LHU(WireData imm, WireData rd, WireData rs1);

	WireData SB(WireData imm, WireData rs1, WireData rs2);
	WireData SH(WireData imm, WireData rs1, WireData rs2);
	WireData SW(WireData imm, WireData rs1, WireData rs2);

	WireData ADDI(WireData imm, WireData rd, WireData rs1);
	WireData SLTI(WireData imm, WireData rd, WireData rs1);
	WireData SLTIU(WireData imm, WireData rd, WireData rs1);
	WireData XORI(WireData imm, WireData rd, WireData rs1);
	WireData ORI(WireData imm, WireData rd, WireData rs1);
	WireData ANDI(WireData imm, WireData rd, WireData rs1);

	WireData SLLI(WireData rd, WireData rs1, WireData shamt);
	WireData SRLI(WireData rd, WireData rs1, WireData shamt);
	WireData SRAI(WireData rd, WireData rs1, WireData shamt);
	WireData ADD(WireData rd, WireData rs1, WireData rs2);
	WireData SUB(WireData rd, WireData rs1, WireData rs2);
	WireData SLL(WireData rd, WireData rs1, WireData rs2);
	WireData SLT(WireData rd, WireData rs1, WireData rs2);
	WireData SLTU(WireData rd, WireData rs1, WireData rs2);
	WireData XOR(WireData rd, WireData rs1, WireData rs2);
	WireData SRL(WireData rd, WireData rs1, WireData rs2);
	WireData SRA(WireData rd, WireData rs1, WireData rs2);
	WireData OR(WireData rd, WireData rs1, WireData rs2);
	WireData AND(WireData rd, WireData rs1, WireData rs2);
} // namespace Instructions
