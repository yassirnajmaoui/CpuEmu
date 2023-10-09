#include "Units/ALUControl.hpp"
#include "BitUtils.hpp"
#include "RISCV-Constants.hpp"
#include "Types/Wire.hpp"

#include <iostream>

ALUControl::ALUControl() : Node(3, 1, "ALU controller") {}

void ALUControl::ProcessInternal()
{
	std::cout << "ALUContol ProcessInternal" << std::endl;
	WireData alu_op = GetWireData(ALUOpIndex);
	WireData func3 = GetWireData(Func3Index);
	WireData sign_bit = GetWireData(SignBitIndex);

	std::cout << "ALUContol GetWireData done" << std::endl;
	
	// Default
	WireData lALUSelect = 0u;  // ADD

	if (alu_op == 0b01)
	{
		switch (func3)
		{
		case 0x00: lALUSelect = ALU_SELECT_BEQ;   // BEQ
		case 0x01: lALUSelect = ALU_SELECT_BNE;   // BNE
		case 0x04: lALUSelect = ALU_SELECT_BLT;   // BLT
		case 0x05: lALUSelect = ALU_SELECT_BGE;   // BGE
		case 0x06: lALUSelect = ALU_SELECT_BLTU;  // BLTU
		case 0x07: lALUSelect = ALU_SELECT_BGEU;  // BGEU
		default: break;
		}
	}
	else if (alu_op == 0b10)
	{
		switch (func3)
		{
		case 0b000:
			if (sign_bit == 0b1)
				lALUSelect = ALU_SELECT_SUB;  // SUB
			else
				lALUSelect = ALU_SELECT_ADD;       // ADD (or JALR ?)
		case 0b001: lALUSelect = ALU_SELECT_SLL;   // SLL
		case 0b010: lALUSelect = ALU_SELECT_SLT;   // SLT
		case 0b011: lALUSelect = ALU_SELECT_SLTU;  // SLTU
		case 0b100: lALUSelect = ALU_SELECT_XOR;   // XOR
		case 0b101:
			if (sign_bit == 0b1)
				lALUSelect = ALU_SELECT_SRA;  // SRA
			else
				lALUSelect = ALU_SELECT_SRL;      // SRL
		case 0b110: lALUSelect = ALU_SELECT_OR;   // OR
		case 0b111: lALUSelect = ALU_SELECT_AND;  // AND
		default: break;
		}
	}

	// Any other case, ALUSelect stays all 0s

	std::cout << "ALUContol SetWireData" << std::endl;
	SetWireData(ALUSelectIndex, lALUSelect);
}
