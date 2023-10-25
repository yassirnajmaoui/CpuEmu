#include "Units/Memory.hpp"

#include "BitUtils.hpp"
#include "Types/Wire.hpp"

Memory::Memory(std::string pName) : Node(5, 1, pName)
{
	mMemory.resize(DefaultMemorySize);
}

Memory::Memory(std::vector<Byte>&& pmMemory, std::string pName) : Node(5, 1, pName), mMemory(pmMemory) {}

size_t Memory::GetMemorySize() const
{
	return mMemory.size();
}

Byte Memory::GetMemoryData(unsigned int pIndex) const
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
		if (lFunct3 == 0b000) // LB
		{
			Byte lMemData = GetMemoryData(lAddress);
			SetWireData(ReadDataIndex, BitUtils::SignExtend(static_cast<WireData>(lMemData), 8, 32));
		}
		else if (lFunct3 == 0b001) // LH
		{
			Byte lMemData0 = GetMemoryData(lAddress);
			Byte lMemData1 = GetMemoryData(lAddress + 1);
			WireData lOut = static_cast<WireData>(lMemData0);
			BitUtils::SetBits(lOut, 15, 8, static_cast<WireData>(lMemData1));
			SetWireData(ReadDataIndex, BitUtils::SignExtend(lOut, 16, 32));
		}
		else if (lFunct3 == 0b010) // LW
		{
			Byte lMemData0 = GetMemoryData(lAddress);
			Byte lMemData1 = GetMemoryData(lAddress + 1);
			Byte lMemData2 = GetMemoryData(lAddress + 2);
			Byte lMemData3 = GetMemoryData(lAddress + 3);
			WireData lOut = static_cast<WireData>(lMemData0);
			BitUtils::SetBits(lOut, 15, 8,  static_cast<WireData>(lMemData1));
			BitUtils::SetBits(lOut, 23, 16, static_cast<WireData>(lMemData2));
			BitUtils::SetBits(lOut, 31, 24, static_cast<WireData>(lMemData3));
			SetWireData(ReadDataIndex, lOut);
		}
		else if (lFunct3 == 0b100) // LBU
		{
			Byte lMemData = GetMemoryData(lAddress);
			SetWireData(ReadDataIndex, static_cast<WireData>(lMemData));
		}
		else if (lFunct3 == 0b101) // LHU
		{
			Byte lMemData0 = GetMemoryData(lAddress);
			Byte lMemData1 = GetMemoryData(lAddress + 1);
			WireData lOut = static_cast<WireData>(lMemData0);
			BitUtils::SetBits(lOut, 15, 8, static_cast<WireData>(lMemData1));
			SetWireData(ReadDataIndex, lOut);
		}
	}

	if (lMemWrite)
	{
		if (lFunct3 == 0b000) // SB
		{
			lWriteData = BitUtils::TruncateBits(lWriteData, 7, 0);
			mMemory[lAddress] = lWriteData;
		}
		if (lFunct3 == 0b001) // SH
		{
			mMemory[lAddress] = BitUtils::TruncateBits(lWriteData, 7, 0);
			mMemory[lAddress+1] = BitUtils::TruncateBits(lWriteData, 15, 8);
		}
		if (lFunct3 == 0b010) // SW
		{
			mMemory[lAddress]   = BitUtils::TruncateBits(lWriteData, 7, 0);
			mMemory[lAddress+1] = BitUtils::TruncateBits(lWriteData, 15, 8);
			mMemory[lAddress+2] = BitUtils::TruncateBits(lWriteData, 23, 16);
			mMemory[lAddress+3] = BitUtils::TruncateBits(lWriteData, 31, 24);
		}
	}
}
