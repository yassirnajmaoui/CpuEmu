#pragma once

class Node;
class System;
class Wire;

class NodesDisplay
{
public:
	static void DisplayNode(const Node& prNode, int pId);
	static void DisplayWire(const Wire& prWire, int pId);
	static void DisplaySystem(const System& prSystem);
};
