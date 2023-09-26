#include "Units/ALU.hpp"
#include "Types/Wire.hpp"
#include "RISCV-Constants.hpp"

ALU::ALU() :
	Node(3, 2)
{
}

void ALU::ProcessInternal()
{
	WireData lRD1 = GetWireData(RD1Index);
	WireData lRD2 = GetWireData(RD2Index);
	WireData lControl = GetWireData(ALUSelectIndex);

	auto lpALUResultWire = mOutputWires[ALUResultIndex];
	auto lpALUZeroWire = mOutputWires[ALUZeroIndex];

	switch (lControl)
	{
	case ALU_SELECT_ADD:
		lpALUResultWire->SetData(lRD1+lRD2);
		break;
	case ALU_SELECT_SLL:
		lpALUResultWire->SetData(lRD1<<lRD2);
		break;
	case ALU_SELECT_XOR:
		lpALUResultWire->SetData(lRD1^lRD2);
		break;
	case ALU_SELECT_SRL:
		lpALUResultWire->SetData(lRD1>>lRD2);
		break;
	case ALU_SELECT_SRA:
	{
		WireData lRD1_sign = (lRD1>>31)<<31;
		WireData lRD1_unsigned = (1<<31) & lRD1;		
		WireData lResult_unsigned = lRD1_unsigned >> lRD2;
		WireData lResult = lResult_unsigned | lRD1_sign;
		lpALUResultWire->SetData(lResult);
	}
		break;
	case ALU_SELECT_OR:
		lpALUResultWire->SetData(lRD1|lRD2);
		break;
	case ALU_SELECT_AND:
		lpALUResultWire->SetData(lRD1&lRD2);
		break;
	default:
		break;
	}
	
	if(lpALUResultWire->GetData() == 0)
	{
		lpALUZeroWire->SetData(1);
	}
}
