#include "Units/ALU.hpp"
#include "Types/Wire.hpp"

void ALU::ProcessInternal() const
{
	WireData lControl = mpALUControl.lock()->GetData();
	WireData lRD1 = mpReadData1.lock()->GetData();
	WireData lRD2 = mpReadData2.lock()->GetData();
	auto lpALUResultWire = mpALUResut.lock();
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
		mpZero.lock()->SetData(1);
	}
}
