#include "Units/Memory.hpp"

#include "BitUtils.hpp"
#include "Types/Wire.hpp"

Memory::Memory(std::string pName) : Node(5, 1, pName)
{
	mMemory.resize(InitialMemorySize);
}

Memory::Memory(std::vector<WireData>&& pmMemory, std::string pName) : Node(5, 1, pName), mMemory(pmMemory) {}

size_t Memory::GetMemorySize() const
{
	return mMemory.size();
}

WireData Memory::GetMemoryData(unsigned int pIndex) const
{
	return mMemory.at(pIndex);
}

void Memory::ProcessInternal()
{
	bool lMemRead = static_cast<bool>(GetWireData(MemReadIndex));
	bool lMemWrite = static_cast<bool>(GetWireData(MemWriteIndex));
	WireData lFunct3 = GetWireData(Funct3Index);
	size_t lAddress = static_cast<size_t>(GetWireData(AddressIndex));
	WireData lWriteData = GetWireData(WriteDataIndex);

	if (lMemRead)
	{
		ASSERT_coherence(lMemWrite == false, "Cannot read and write at the same time");
		// TODO: use lAddress coherently
		WireData lMemData = *reinterpret_cast<WireData*>(reinterpret_cast<void*>(mMemory.data()) + lAddress);
		if (lFunct3 == 0b000) // LB
		{
			lMemData = BitUtils::SignExtend(BitUtils::TruncateBits(lMemData, 7, 0), 8, 32);
		}
		else if (lFunct3 == 0b001) // LH
		{
			lMemData = BitUtils::SignExtend(BitUtils::TruncateBits(lMemData, 15, 0), 16, 32);
		}
		else if (lFunct3 == 0b010) // LW
		{
			// Leave as-is
		}
		else if (lFunct3 == 0b100) // LBU
		{
			lMemData = BitUtils::TruncateBits(lMemData, 7, 0);
		}
		else if (lFunct3 == 0b101) // LHU
		{
			lMemData = BitUtils::TruncateBits(lMemData, 15, 0);
		}
		SetWireData(ReadDataIndex, lMemData);
	}

	if (lMemWrite)
	{
		if (lFunct3 == 0b000) // SB
		{
			lWriteData = BitUtils::TruncateBits(lWriteData, 7, 0);
		}
		if (lFunct3 == 0b001) // SH
		{
			lWriteData = BitUtils::TruncateBits(lWriteData, 15, 0);
		}
		if (lFunct3 == 0b010) // SW
		{
			// Leave as-is
		}
		mMemory[lAddress] = lWriteData;
	}
}
