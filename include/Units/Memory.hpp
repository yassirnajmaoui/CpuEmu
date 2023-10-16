#pragma once

#include "Types/Node.hpp"
#include "Utils.hpp"

class Memory : public Node
{
public:
	static constexpr size_t InitialMemorySize = 512;

	// Inputs
	static constexpr size_t MemWriteIndex = 0;
	static constexpr size_t AddressIndex = 1;
	static constexpr size_t WriteDataIndex = 2;
	static constexpr size_t MemReadIndex = 3;
	static constexpr size_t Funct3Index = 4;

	// Outputs
	static constexpr size_t ReadDataIndex = 0;

	Memory();

	size_t GetMemorySize() const;
	WireData GetMemoryData(unsigned int pIndex) const;

protected:
	void ProcessInternal() override;

private:
	std::vector<WireData> mMemory;
};

