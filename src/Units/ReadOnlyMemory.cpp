#include "Units/ReadOnlyMemory.hpp"

#include "Types/Wire.hpp"

ReadOnlyMemory::ReadOnlyMemory() : Node(1, 1, "Read-only memory") {}

ReadOnlyMemory::ReadOnlyMemory(std::vector<WireData>&& pmMemory) : Node(1, 1, "Read-only memory"), mMemory(pmMemory) {}

void ReadOnlyMemory::ProcessInternal()
{
	size_t lAddress = static_cast<size_t>(GetWireData(ReadAddressIndex));
	lAddress >>= 2; // Since C++ pointers already increment by 4 if you're using pointers of a 32 bit size
	SetWireData(OutputDataIndex, mMemory[lAddress]);
}
