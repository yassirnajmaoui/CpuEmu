#include "Types/Port.hpp"

Port::Port(std::shared_ptr<Wire> pWire, std::string pName) :
	mWire(pWire), mName(pName)
{
	// TODO: Assign a unique id to mId
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

int Port::GetId() const
{
	return mId;
}
