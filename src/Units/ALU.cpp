#include "Units/ALU.hpp"
#include "Types/Wire.hpp"

ALU::ALU() :
	Node(3, 2)
{
}

void ALU::ProcessInternal()
{
	WireData lRD1 = GetWireData(RD1Index);
	WireData lRD2 = GetWireData(RD2Index);
	WireData lControl = GetWireData(ALUControlIndex);

	auto lpALUResultWire = mOutputWires[ALUResultIndex];
	auto lpALUZeroWire = mOutputWires[ALUZeroIndex];

	switch (lControl)
	{
	case ALUOP_ADD:
		lpALUResultWire->SetData(lRD1+lRD2);
		break;
	case ALUOP_SLL:
		lpALUResultWire->SetData(lRD1<<lRD2);
		break;
	case ALUOP_XOR:
		lpALUResultWire->SetData(lRD1^lRD2);
		break;
	case ALUOP_SRL:
		lpALUResultWire->SetData(lRD1>>lRD2);
		break;
	case ALUOP_SRA:
	{
		WireData lRD1_sign = (lRD1>>31)<<31;
		WireData lRD1_unsigned = (1<<31) & lRD1;		
		WireData lResult_unsigned = lRD1_unsigned >> lRD2;
		WireData lResult = lResult_unsigned | lRD1_sign;
		lpALUResultWire->SetData(lResult);
	}
		break;
	case ALUOP_OR:
		lpALUResultWire->SetData(lRD1|lRD2);
		break;
	case ALUOP_AND:
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
