#include "Units/ReadOnlyMemory.hpp"

#include "Types/Wire.hpp"

ReadOnlyMemory::ReadOnlyMemory(std::string pName) : Node(1, 1, pName) {}

ReadOnlyMemory::ReadOnlyMemory(std::vector<WireData> pmMemory, std::string pName) : Node(1, 1, pName)
{
	SetMemory(pmMemory);
}

void ReadOnlyMemory::ProcessInternal()
{
	size_t lAddress = static_cast<size_t>(GetWireData(ReadAddressIndex));
	lAddress =
	lAddress / sizeof(WireData); // Since C++ pointers already increment by 4 if you're using pointers of a 32 bit size
	SetWireData(OutputDataIndex, mMemory[lAddress]);
}

void ReadOnlyMemory::SetMemory(std::vector<WireData> pmMemory)
{
	mMemory = pmMemory;
}
