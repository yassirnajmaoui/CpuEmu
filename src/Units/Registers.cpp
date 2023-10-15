#include "Units/Registers.hpp"

#include "Types/Wire.hpp"
#include "Utils.hpp"

Registers::Registers() : Node(2, 2, "Registers")
{
	for (unsigned int i = 0; i < NumberOfRegisters; ++i)
	{
		mRegisters[i] = 0u;
	}
}

void Registers::ProcessInternal()
{
	// Setup
	size_t lReadRegister1 = static_cast<size_t>(GetWireData(ReadRegister1Index));
	size_t lReadRegister2 = static_cast<size_t>(GetWireData(ReadRegister2Index));

	ASSERT_coherence(lReadRegister1 < NumberOfRegisters, "Register address 1 requested too high");
	ASSERT_coherence(lReadRegister2 < NumberOfRegisters, "Register address 2 requested too high");

	// Logic
	uint64_t lContentsOfReg1 = mRegisters[lReadRegister1];
	uint64_t lContentsOfReg2 = mRegisters[lReadRegister2];

	SetWireData(ReadData1Index, lContentsOfReg1);
	SetWireData(ReadData2Index, lContentsOfReg2);
}

WireData Registers::GetRegisterValue(size_t pRegisterIndex) const
{
	return mRegisters[pRegisterIndex];
}
