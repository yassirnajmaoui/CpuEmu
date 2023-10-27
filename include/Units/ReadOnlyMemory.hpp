#pragma once

#include "Types/Node.hpp"
#include "Utils.hpp"

class ReadOnlyMemory : public Node
{
public:
	// Inputs
	static constexpr size_t ReadAddressIndex = 0;

	// Outputs
	static constexpr size_t OutputDataIndex = 0;

	ReadOnlyMemory(std::string pName = "Read-only memory");
	ReadOnlyMemory(std::vector<WireData> pmMemory, std::string pName = "Read-only memory");

	void SetMemory(std::vector<WireData> pmMemory);

protected:
	void ProcessInternal() override;

private:
	std::vector<WireData> mMemory;
};
