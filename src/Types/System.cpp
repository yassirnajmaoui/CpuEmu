#include "Types/System.hpp"

System::System() {}

System::System(std::vector<Node>&& pNodes, std::vector<Wire>&& pWires) : mNodes(std::move(pNodes)), mWires(std::move(pWires)) {}

Node& System::GetNode(int pIndex)
{
	return mNodes[pIndex];
}

Wire& System::GetWire(int pIndex)
{
	return mWires[pIndex];
}

// ----------- Initialize RISC-V CPU -----------

RISCV::RISCV()
{
	
}

void RISCV::SetInstructions(std::vector<WireData> pInstructions) {}

void RISCV::SetDataMemory(std::vector<Byte> pDataMemmory) {}
