#pragma once

#include "Types/Node.hpp"

class ALUControl : public Node
{
public:
	// Inputs
	static constexpr size_t ALUOpIndex = 0;
	static constexpr size_t Funct3Index = 1;
	static constexpr size_t SignBitIndex = 2;

	// Outputs
	static constexpr size_t ALUSelectIndex = 0;

	ALUControl();

	std::string GetInputPortName(unsigned int pIndex) const override;
	std::string GetOutputPortName(unsigned int pIndex) const override;

protected:
	void ProcessInternal() override;
};
