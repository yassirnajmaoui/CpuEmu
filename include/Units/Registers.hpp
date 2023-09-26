#pragma once

#include "Types/Node.hpp"

class Registers : public Node
{

friend class RegistersWriter;

public:
	static constexpr size_t NumberOfRegisters = 16;

	// Inputs
	static constexpr size_t ReadRegister1Index = 0;
	static constexpr size_t ReadRegister2Index = 1;

	// Outputs
	static constexpr size_t ReadData1Index = 0;
	static constexpr size_t ReadData2Index = 1;

	Registers();

protected:
	void ProcessInternal() override;
	
private:
	std::array<WireData, NumberOfRegisters> mRegisters;
};