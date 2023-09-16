#pragma once

#include "Types/Node.hpp"

class Multiplexer : public Node
{
public:
	static constexpr size_t InputSelectionIndex = 0;

	Multiplexer(size_t pNumberOfInputs);
protected:
	void ProcessInternal() override;
};
