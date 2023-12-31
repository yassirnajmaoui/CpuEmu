#include "Units/RegistersWriter.hpp"

#include "Units/Registers.hpp"
#include "Utils.hpp"

RegistersWriter::RegistersWriter(std::shared_ptr<Registers> ppRegistersNode) :
	Node(3, 0, "Registers writer"), mpRegistersNode(ppRegistersNode)
{
}

void RegistersWriter::ProcessInternal()
{
	WireData lRegWrite = GetWireData(RegWriteIndex);

	// Wire in register if RegWrite is true
	if (lRegWrite)
	{
		size_t lWriteRegister = static_cast<size_t>(GetWireData(WriteRegisterIndex));
		ASSERT_coherence(lWriteRegister < Registers::NumberOfRegisters, "Write Register address requested too high");

		WireData lWriteData = GetWireData(WriteDataIndex);
		mpRegistersNode->mRegisters[lWriteRegister] = lWriteData;
	}
}

std::string RegistersWriter::GetInputPortName(unsigned int pIndex) const
{
	switch (pIndex)
	{
	case RegWriteIndex:
		return "RegWrite";
	case WriteRegisterIndex:
		return "Write Register";
	case WriteDataIndex:
		return "Write Data";
	default:
		return "";
	}
}
std::string RegistersWriter::GetOutputPortName(unsigned int pIndex) const
{
	return "";
}
