#pragma once

#include "Types/Node.hpp"
#include "Types/Wire.hpp"

#include <vector>

using Byte = unsigned char;

class System
{
public:
	System();
	System(std::vector<Node>&& pNodes, std::vector<Wire>&& pWires);

	Node& GetNode(int pIndex);
	Wire& GetWire(int pIndex);
protected:
	std::vector<Node> mNodes;
	std::vector<Wire> mWires;
};

class RISCV : public System
{
public:
	RISCV();
	void SetInstructions(std::vector<WireData> pInstructions);
	void SetDataMemory(std::vector<Byte> pDataMemmory);
};
