#pragma once

#include "Types/Node.hpp"
#include "Utils.hpp"

class Wire;

class ReadOnlyMemory : public Node
{
public:
	ReadOnlyMemory();

	//TODO: Create a constructor to give the data

	// Inputs
	static constexpr size_t ReadAddressIndex = 0;

	// Outputs
	static constexpr size_t OutputDataIndex = 0;

protected:
	void ProcessInternal() override;

private:
	std::vector<WireData> mMemory;
};