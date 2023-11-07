#include "Units/ALUControl.hpp"

#include "BitUtils.hpp"
#include "RISCV-Constants.hpp"
#include "Types/Wire.hpp"

#include <iostream>

ALUControl::ALUControl() : Node(3, 1, "ALU controller") {}

void ALUControl::ProcessInternal()
{
	WireData alu_op = GetWireData(ALUOpIndex);
	WireData funct3 = GetWireData(Funct3Index);
	WireData sign_bit = GetWireData(SignBitIndex);

	// Default
	WireData lALUSelect = 0u; // ADD

	if (alu_op == 0b01)
	{
		switch (funct3)
		{
		case FUNCT3_BEQ:
			lALUSelect = ALU_SELECT_BEQ;
			break; // BEQ
		case FUNCT3_BNE:
			lALUSelect = ALU_SELECT_BNE;
			break; // BNE
		case FUNCT3_BLT:
			lALUSelect = ALU_SELECT_BLT;
			break; // BLT
		case FUNCT3_BGE:
			lALUSelect = ALU_SELECT_BGE;
			break; // BGE
		case FUNCT3_BLTU:
			lALUSelect = ALU_SELECT_BLTU;
			break; // BLTU
		case FUNCT3_BGEU:
			lALUSelect = ALU_SELECT_BGEU;
			break; // BGEU
		default:
			break;
		}
	}
	else if (alu_op == 0b10)
	{
		switch (funct3)
		{
		case FUNCT3_ADD_SUB:
			if (sign_bit == 0b1)
			{
				lALUSelect = ALU_SELECT_SUB; // SUB
			}
			else
			{
				lALUSelect = ALU_SELECT_ADD; // ADD (or JALR ?)
			}
			break;
		case FUNCT3_SLL:
			lALUSelect = ALU_SELECT_SLL;
			break; // SLL
		case FUNCT3_SLT:
			lALUSelect = ALU_SELECT_SLT;
			break; // SLT
		case FUNCT3_SLTU:
			lALUSelect = ALU_SELECT_SLTU;
			break; // SLTU
		case FUNCT3_XOR:
			lALUSelect = ALU_SELECT_XOR;
			break; // XOR
		case FUNCT3_SRL_SRA:
			if (sign_bit == 0b1)
			{
				lALUSelect = ALU_SELECT_SRA;
			}
			else
			{
				lALUSelect = ALU_SELECT_SRL;
			} // SRL
			break;
		case FUNCT3_OR:
			lALUSelect = ALU_SELECT_OR;
			break; // OR
		case FUNCT3_AND:
			lALUSelect = ALU_SELECT_AND;
			break; // AND
		default:
			break;
		}
	}
	else if(alu_op == 0b11)
	{
		lALUSelect = ALU_SELECT_ADD;// JAL, LUI, AUIPC
	}

	// Any other case, ALUSelect stays all 0s

	SetWireData(ALUSelectIndex, lALUSelect);
}

std::string ALUControl::GetInputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case ALUOpIndex:
		return "ALU Op";
	case Funct3Index:
		return "funct3";
	case SignBitIndex:
		return "sign_bit";
	default:
		return "";
	}
}

std::string ALUControl::GetOutputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case ALUSelectIndex:
		return "ALU Select";
	default:
		return "";
	}
}
