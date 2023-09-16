#include "Units/Registers.hpp"
#include "Types/Wire.hpp"

Registers::Registers() :
	Node(5, 2)
{
}

void Registers::ProcessInternal()
{
	// Setup
	WireData lRegWrite = mInputWires[RegWriteIndex]->GetData();
	WireData lReadRegister1 = mInputWires[ReadRegister1Index]->GetData();
	WireData lReadRegister2 = mInputWires[ReadRegister2Index]->GetData();
	WireData lWriteRegister = mInputWires[WriteRegisterIndex]->GetData();
	WireData lWriteData = mInputWires[WriteDataIndex]->GetData();
	
	auto lpReadData1Wire = mOutputWires[ReadData1Index];
	auto lpReadData2Wire = mOutputWires[ReadData2Index];

	ASSERT_coherence(lReadRegister1 < NumberOfRegisters, "Register address 1 requested too high");
	ASSERT_coherence(lReadRegister2 < NumberOfRegisters, "Register address 2 requested too high");

	// Logic
	uint64_t lContentsOfReg1 = mRegisters[lReadRegister1];
	uint64_t lContentsOfReg2 = mRegisters[lReadRegister2];

	lpReadData1Wire->SetData(lContentsOfReg1);
	lpReadData2Wire->SetData(lContentsOfReg2);

	if(lRegWrite > 0)
	{
		mRegisters[lWriteRegister] = lWriteData;
	}

	lpReadData1Wire->SetDataReady();
	lpReadData2Wire->SetDataReady();

}
