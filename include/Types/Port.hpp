#pragma once

#include "Types/WireForward.hpp"

#include <memory>
#include <string>

class Node;

class Port
{
public:
	Port(std::string pName = "Unnamed port");

	const std::shared_ptr<Wire>& GetWire() const;
	std::shared_ptr<Wire> GetWire();
	std::string GetName() const;
	void SetName(std::string pName);
	void SetWire(std::shared_ptr<Wire> ppWire);
	void SetNode(std::shared_ptr<Node> ppNode);
	int GetId() const;

	void NotifyDataReady();

private:
	std::shared_ptr<Wire> mpWire;
	std::shared_ptr<Node> mpNode;
	std::string mName;
	int mId;

	static int sNextID;
};
