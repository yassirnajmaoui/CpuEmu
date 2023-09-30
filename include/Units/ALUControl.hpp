#pragma once

#include "Types/Node.hpp"

class ALUControl : public Node
{
public:
	// Inputs
	static constexpr size_t ALUOpIndex = 0;
	static constexpr size_t Func3Index = 1;
	static constexpr size_t SignBitIndex = 2;

	// Outputs
	static constexpr size_t ALUSelectIndex = 0;

	ALUControl();

private:
	void ProcessInternal() override;
};
