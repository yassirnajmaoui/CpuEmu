#include "Units/Registers.hpp"
#include "Types/Wire.hpp"
#include "Utils.hpp"

Registers::Registers() :
	Node(5, 2)
{
}

void Registers::ProcessInternal()
{
	// Setup
	WireData lRegWrite = GetWireData(RegWriteIndex);
	size_t lReadRegister1 = static_cast<size_t>(GetWireData(ReadRegister1Index));
	size_t lReadRegister2 = static_cast<size_t>(GetWireData(ReadRegister2Index));
	size_t lWriteRegister = static_cast<size_t>(GetWireData(WriteRegisterIndex));
	WireData lWriteData = GetWireData(WriteDataIndex);

	ASSERT_coherence(lReadRegister1 < NumberOfRegisters, "Register address 1 requested too high");
	ASSERT_coherence(lReadRegister2 < NumberOfRegisters, "Register address 2 requested too high");

	// Logic	
	uint64_t lContentsOfReg1 = mRegisters[lReadRegister1];
	uint64_t lContentsOfReg2 = mRegisters[lReadRegister2];

	SetWireData(ReadData1Index, lContentsOfReg1);
	SetWireData(ReadData2Index, lContentsOfReg2);

	// Wire in register if RegWire is true
	if(lRegWrite)
	{
		ASSERT_coherence(lWriteRegister < NumberOfRegisters, "Write Register address requested too high");
		mRegisters[lWriteRegister] = lWriteData;
	}
}
