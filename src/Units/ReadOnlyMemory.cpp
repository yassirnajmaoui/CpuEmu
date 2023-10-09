#include "Units/ReadOnlyMemory.hpp"
#include "Types/Wire.hpp"

ReadOnlyMemory::ReadOnlyMemory() : Node(1, 1, "Read-only memory") {}

ReadOnlyMemory::ReadOnlyMemory(std::vector<WireData>&& pmMemory) : Node(1, 1), mMemory(pmMemory) {}

void ReadOnlyMemory::ProcessInternal()
{
	size_t lAddress = static_cast<size_t>(GetWireData(ReadAddressIndex));
	SetWireData(OutputDataIndex, mMemory[lAddress]);
}
