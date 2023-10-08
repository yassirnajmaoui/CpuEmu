#include "Units/Memory.hpp"
#include "Types/Wire.hpp"

Memory::Memory() :
	Node(4, 1, "Memory")
{

}

void Memory::ProcessInternal()
{
	bool lMemRead = static_cast<bool>(GetWireData(MemReadIndex));
	bool lMemWrite = static_cast<bool>(GetWireData(MemWriteIndex));
	size_t lAddress = static_cast<size_t>(GetWireData(AddressIndex));
	WireData lWriteData = static_cast<WireData>(GetWireData(WriteDataIndex));

	if(lMemRead)
	{
		ASSERT_coherence(lMemWrite == false, "Cannot read and write at the same time");

		SetWireData(ReadDataIndex, mMemory[lAddress]);
	}

	if(lMemWrite)
	{
		mMemory[lAddress] = lWriteData;
	}
}
