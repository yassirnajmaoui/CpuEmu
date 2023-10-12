#include "Units/ALU.hpp"

#include "RISCV-Constants.hpp"
#include "Types/Wire.hpp"

ALU::ALU() : Node(3, 2, "ALU") {}

void ALU::ProcessInternal()
{
	WireData lRD1 = GetWireData(RD1Index);
	WireData lRD2 = GetWireData(RD2Index);
	WireData lRD1_unsigned = (lRD1 < 0) ? -lRD1 : lRD1;
	WireData lRD2_unsigned = (lRD2 < 0) ? -lRD2 : lRD2;
	WireData lControl = GetWireData(ALUSelectIndex);

	WireData lResult = 0u;
	WireData lZero = 0u; // Branch

	WireData lResult_unsigned = 0u;
	switch (lControl)
	{
	// Arithmetic operations
	case ALU_SELECT_ADD:
		lResult = lRD1 + lRD2;
		break;
	case ALU_SELECT_SUB:
		lResult = lRD1 - lRD2;
		break;
	case ALU_SELECT_XOR:
		lResult = lRD1 ^ lRD2;
		break;
	case ALU_SELECT_OR:
		lResult = lRD1 | lRD2;
		break;
	case ALU_SELECT_AND:
		lResult = lRD1 & lRD2;
		break;
	case ALU_SELECT_SLL:
		lResult = lRD1 << lRD2;
		break;
	case ALU_SELECT_SRL:
		lResult = lRD1 >> lRD2;
		break;
	case ALU_SELECT_SRA:
		lResult_unsigned = lRD1_unsigned >> lRD2;
		lResult = (lRD1 < 0) ? -lResult_unsigned : lResult_unsigned;
		break;
	case ALU_SELECT_SLT:
		lResult = lRD1 < lRD2 ? 1 : 0;
		break;
	case ALU_SELECT_SLTU:
		lResult = lRD1_unsigned < lRD2_unsigned ? 1 : 0;
		break;
	// Branch
	case ALU_SELECT_BEQ:
		lZero = (lRD1 == lRD2) ? 1 : 0;
		break;
	case ALU_SELECT_BNE:
		lZero = (lRD1 != lRD2) ? 1 : 0;
		break;
	case ALU_SELECT_BLT:
		lZero = (lRD1 < lRD2) ? 1 : 0;
		break;
	case ALU_SELECT_BGE:
		lZero = (lRD1 >= lRD2) ? 1 : 0;
		break;
	case ALU_SELECT_BLTU:
		lZero = (lRD1_unsigned < lRD2_unsigned) ? 1 : 0;
		break;
	case ALU_SELECT_BGEU:
		lZero = (lRD1_unsigned >= lRD2_unsigned) ? 1 : 0;
		break;
	default:
		break;
	}

	SetWireData(ALUResultIndex, lResult);
	SetWireData(ALUZeroIndex, lZero);
}
