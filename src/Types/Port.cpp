#include "Types/Port.hpp"
#include "Types/Node.hpp"

int Port::sNextID = 1;

Port::Port(std::string pName) :
	mName(pName)
{
	mId = sNextID++;
}

void Port::NotifyDataReady()
{
	mpNode->NotifyDataReady();
}

const std::shared_ptr<Wire>& Port::GetWire() const
{
	return mpWire;
}

std::shared_ptr<Wire> Port::GetWire()
{
	return mpWire;
}

void Port::SetWire(std::shared_ptr<Wire> ppWire)
{
	mpWire = ppWire;
}

void Port::SetNode(std::shared_ptr<Node> ppNode)
{
	mpNode = ppNode;
}

std::string Port::GetName() const
{
	return mName;
}

void Port::SetName(std::string pName)
{
	mName = pName;
}

int Port::GetId() const
{
	return mId;
}
