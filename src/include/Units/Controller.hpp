#pragma once

#include "Types/Node.hpp"

class Controller : public Node
{
public:
	// Inputs
	static constexpr size_t OpcodeIndex = 0;

	// Outputs
	static constexpr size_t BranchIndex = 0;
	static constexpr size_t MemReadIndex = 1;
	static constexpr size_t MemToRegIndex = 2;
	static constexpr size_t ALUOpIndex = 3;
	static constexpr size_t MemWriteIndex = 4;
	static constexpr size_t ALUSrcIndex = 5;
	static constexpr size_t RegWriteIndex = 6;

	Controller();

private:
	void ProcessInternal() override;
};
