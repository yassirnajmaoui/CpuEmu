#pragma once

#include "Types/Node.hpp"
#include "Utils.hpp"

class Memory : public Node
{
public:
	Memory();

	// Inputs
	static constexpr size_t MemWriteIndex = 0;
	static constexpr size_t AddressIndex = 1;
	static constexpr size_t WriteDataIndex = 2;
	static constexpr size_t MemReadIndex = 3;

	// Outputs
	static constexpr size_t ReadDataIndex = 0;

protected:
	void ProcessInternal() override;

private:
	std::vector<WireData> mMemory;
};
