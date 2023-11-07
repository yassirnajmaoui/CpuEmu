#pragma once

#include "Types/WireForward.hpp"

#include <memory>
#include <string>

class Port
{
public:
//	TODO: Change this: it was to have a Node here. Add a getter to the node. Do not stock the wire
	Port(std::shared_ptr<Wire> pWire, std::string pName = "Unnamed port");

	std::shared_ptr<Wire>& GetWire();
	const std::shared_ptr<Wire>& GetWire() const;
	std::string GetName() const;
	void SetName(std::string pName);
	int GetId() const;

private:
	std::shared_ptr<Wire> mWire;
	std::string mName;
	int mId;

	static int sNextID;
};
