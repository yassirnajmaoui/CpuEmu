#pragma once

#include "Types/Node.hpp"
#include "Utils.hpp"

using Byte = unsigned char;

class Memory : public Node
{
public:
	static constexpr size_t DefaultMemorySize = 512;

	// Inputs
	static constexpr size_t MemWriteIndex = 0;
	static constexpr size_t AddressIndex = 1;
	static constexpr size_t WriteDataIndex = 2;
	static constexpr size_t MemReadIndex = 3;
	static constexpr size_t Funct3Index = 4;

	// Outputs
	static constexpr size_t ReadDataIndex = 0;

	Memory(std::string pName = "Memory");
	Memory(std::vector<Byte> pMemory, std::string pName = "Memory");

	void SetMemory(std::vector<Byte> pMemory);

	size_t GetMemorySize() const;
	Byte GetMemoryData(unsigned int pIndex) const;

	std::string GetInputPortName(unsigned int pIndex) const override;
	std::string GetOutputPortName(unsigned int pIndex) const override;

protected:
	void ProcessInternal() override;

private:
	std::vector<Byte> mMemory;
};

