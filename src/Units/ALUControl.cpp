#include "Units/ALUControl.hpp"

#include "BitUtils.hpp"
#include "RISCV-Constants.hpp"
#include "Types/Wire.hpp"

#include <iostream>

ALUControl::ALUControl() : Node(3, 1, "ALU controller") {}

void ALUControl::ProcessInternal()
{
	WireData alu_op = GetWireData(ALUOpIndex);
	WireData func3 = GetWireData(Funct3Index);
	WireData sign_bit = GetWireData(SignBitIndex);

	// Default
	WireData lALUSelect = 0u; // ADD

	if (alu_op == 0b01)
	{
		switch (func3)
		{
		case 0b000:
			lALUSelect = ALU_SELECT_BEQ;
			break; // BEQ
		case 0b001:
			lALUSelect = ALU_SELECT_BNE;
			break; // BNE
		case 0b100:
			lALUSelect = ALU_SELECT_BLT;
			break; // BLT
		case 0b101:
			lALUSelect = ALU_SELECT_BGE;
			break; // BGE
		case 0b110:
			lALUSelect = ALU_SELECT_BLTU;
			break; // BLTU
		case 0b111:
			lALUSelect = ALU_SELECT_BGEU;
			break; // BGEU
		default:
			break;
		}
	}
	else if (alu_op == 0b10)
	{
		switch (func3)
		{
		case 0b000:
			if (sign_bit == 0b1)
			{
				lALUSelect = ALU_SELECT_SUB; // SUB
			}
			else
			{
				lALUSelect = ALU_SELECT_ADD; // ADD (or JALR ?)
			}
			break;
		case 0b001:
			lALUSelect = ALU_SELECT_SLL;
			break; // SLL
		case 0b010:
			lALUSelect = ALU_SELECT_SLT;
			break; // SLT
		case 0b011:
			lALUSelect = ALU_SELECT_SLTU;
			break; // SLTU
		case 0b100:
			lALUSelect = ALU_SELECT_XOR;
			break; // XOR
		case 0b101:
			if (sign_bit == 0b1)
			{
				lALUSelect = ALU_SELECT_SRA;
			}
			else
			{
				lALUSelect = ALU_SELECT_SRL;
			} // SRL
			break;
		case 0b110:
			lALUSelect = ALU_SELECT_OR;
			break; // OR
		case 0b111:
			lALUSelect = ALU_SELECT_AND;
			break; // AND
		default:
			break;
		}
	}

	// Any other case, ALUSelect stays all 0s

	SetWireData(ALUSelectIndex, lALUSelect);
}
