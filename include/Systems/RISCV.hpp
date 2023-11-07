#pragma once

#include "Systems/System.hpp"

class RISCV : public System
{
public:
	RISCV();
	void SetInstructions(std::vector<WireData> pInstructions);
	void SetDataMemory(std::vector<Byte> pDataMemmory);

	void Clock();
	WireData GetPC() const;

	std::shared_ptr<ReadOnlyMemory> GetInstructionsNode();
	std::shared_ptr<Memory> GetDataMemoryNode();
	std::shared_ptr<Registers> GetRegistersNode();

private:
	std::shared_ptr<ReadOnlyMemory> mpInstructionMemory;
	std::shared_ptr<Memory> mpDataMemory;
	std::shared_ptr<Registers> mpRegisters;
	std::shared_ptr<Wire> mpLoopbackWire;
	std::shared_ptr<Wire> mpClockWire;
	std::shared_ptr<Wire> mpAdd4Wire;
};
