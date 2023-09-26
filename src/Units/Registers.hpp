#pragma once

#include "Types/Node.hpp"

// TODO: Create a Register Write back class that allows to write in the registry
// - Remove the Write operations in class Registers (only allow reading)
// - The Write back class should do only reading and have a shared_ptr of
//   the Registers object

class Registers : public Node
{
public:
	static constexpr size_t NumberOfRegisters = 16;

	// Inputs
	static constexpr size_t RegWriteIndex = 0;
	static constexpr size_t ReadRegister1Index = 1;
	static constexpr size_t ReadRegister2Index = 2;
	static constexpr size_t WriteRegisterIndex = 3;
	static constexpr size_t WriteDataIndex = 4;

	// Outputs
	static constexpr size_t ReadData1Index = 0;
	static constexpr size_t ReadData2Index = 1;

	Registers();

protected:
	void ProcessInternal() override;
	
private:
	std::array<WireData, NumberOfRegisters> mRegisters;
};
