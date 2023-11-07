#pragma once

#include "Types/WireForward.hpp"

#include <memory>
#include <string>

class Port
{
public:
	Port(std::shared_ptr<Wire> pWire, std::string pName = "Unnamed port");

	std::shared_ptr<Wire>& GetWire();
	const std::shared_ptr<Wire>& GetWire() const;
	std::string GetName() const;
	int GetId() const;

private:
	std::shared_ptr<Wire> mWire;
	std::string mName;
	int mId;
};
