#pragma once

#include "Types/Node.hpp"
#include "Types/Wire.hpp"

#include <memory>
#include <vector>

using Byte = unsigned char;

class ReadOnlyMemory;
class Memory;
class Registers;

class System
{
public:
	System();
	System(std::vector<std::shared_ptr<Node>>&& ppNodes, std::vector<std::shared_ptr<Wire>>&& ppWires);

	const Node& GetNode(int pIndex) const;
	const Wire& GetWire(int pIndex) const;
	size_t GetNumNodes() const;
	size_t GetNumWires() const;

protected:
	std::vector<std::shared_ptr<Node>> mNodes;
	std::vector<std::shared_ptr<Wire>> mWires;
};

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
