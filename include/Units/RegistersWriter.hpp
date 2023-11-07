#pragma once

#include "Types/Node.hpp"

class Registers;

class RegistersWriter : public Node
{
public:
	static constexpr size_t RegWriteIndex = 0;
	static constexpr size_t WriteRegisterIndex = 1;
	static constexpr size_t WriteDataIndex = 2;

	RegistersWriter(std::shared_ptr<Registers> ppRegistersNode);

	std::string GetInputPortName(unsigned int pIndex) const override;
	std::string GetOutputPortName(unsigned int pIndex) const override;

protected:
	void ProcessInternal() override;

private:
	std::shared_ptr<Registers> mpRegistersNode;
};
