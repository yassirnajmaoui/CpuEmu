#include "Types/Port.hpp"

int Port::sNextID = 1;

Port::Port(std::shared_ptr<Wire> pWire, std::string pName) :
	mWire(pWire), mName(pName)
{
	mId = sNextID++;
}

const std::shared_ptr<Wire>& Port::GetWire() const
{
	return mWire;
}

std::shared_ptr<Wire>& Port::GetWire()
{
	return mWire;
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
