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
