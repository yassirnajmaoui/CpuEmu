#include "Units/ReadOnlyMemory.hpp"
#include "Types/Wire.hpp"

ReadOnlyMemory::ReadOnlyMemory() :
	Node(1, 1)
{
}

void ReadOnlyMemory::ProcessInternal()
{
	size_t lAddress = static_cast< size_t >(GetWireData(ReadAddressIndex));
	SetWireData(OutputDataIndex, mMemory[lAddress]);
}
