#include "Systems/System.hpp"

System::System() {}

const Node& System::GetNode(int pIndex) const
{
	return *mNodes[pIndex];
}

const Wire& System::GetWire(int pIndex) const
{
	return *mWires[pIndex];
}

size_t System::GetNumNodes() const
{
	return mNodes.size();
}

size_t System::GetNumWires() const
{
	return mWires.size();
}
