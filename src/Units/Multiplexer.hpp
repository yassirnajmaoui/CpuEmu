#pragma once

#include "Types/Node.hpp"

class Multiplexer : public Node
{
// Note: The first input has to always be the Control
public:
	void ProcessInternal() const override;
};
