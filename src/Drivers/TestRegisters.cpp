#include "Types/Wire.hpp"
#include "Units/Registers.hpp"
#include "Units/RegistersWriter.hpp"

#include <iostream>
#include <memory>
#include <sstream>

int main()
{
	// clang-format off
	auto lRegisters = std::make_shared<Registers>();
	auto lRegistersWriter = std::make_shared<RegistersWriter>(lRegisters);

	// Inputs for Registers
	auto lRS1Wire	= Node::CreateInputWire(lRegisters, Registers::ReadRegister1Index);
	auto lRS2Wire	= Node::CreateInputWire(lRegisters, Registers::ReadRegister2Index);
	// Output wires for Registers
	auto lReadData1Wire	= Node::CreateOutputWire(lRegisters, Registers::ReadData1Index);
	auto lReadData2Wire	= Node::CreateOutputWire(lRegisters, Registers::ReadData2Index);

	// Inputs for RegistersWriter
	auto lRegWriteWire		= Node::CreateInputWire(lRegistersWriter, RegistersWriter::RegWriteIndex);
	auto lWriteRegisterWire	= Node::CreateInputWire(lRegistersWriter, RegistersWriter::WriteRegisterIndex);
	auto lWriteDataWire		= Node::CreateInputWire(lRegistersWriter, RegistersWriter::WriteDataIndex);


	auto lReadRegistersFunc = [&](WireData pRS1, WireData pRS2)
	{
		lRS1Wire->SetData(pRS1);
		lRS1Wire->SetDataReady();
		lRS2Wire->SetData(pRS2);
		lRS2Wire->SetDataReady();

		// The Register should automatically process the input on the last SetDataReady()
		
		return std::make_pair(lReadData1Wire->GetData(), lReadData2Wire->GetData());
	};

	auto lWriteRegistersFunc = [&](WireData pWriteRegister, WireData pWriteData, WireData pRegWrite = 1u)
	{
		lWriteRegisterWire->SetData(pWriteRegister);
		lWriteRegisterWire->SetDataReady();
		lWriteDataWire->SetData(pWriteData);
		lWriteDataWire->SetDataReady();
		lRegWriteWire->SetData(pRegWrite);
		lRegWriteWire->SetDataReady();

		// The RegisterWriter will automatically write on the last SetDataReady()
	};

	// clang-format on

	lWriteRegistersFunc(12, 159);
	lWriteRegistersFunc(13, 147);
	auto lRes = lReadRegistersFunc(12, 13);

	std::cout << "Res: " << lRes.first << " , " << lRes.second << std::endl;
	// Output should be 159, 147

	lWriteRegistersFunc(13, 999);
	lRes = lReadRegistersFunc(13, 10);
	std::cout << "Res: " << lRes.first << " , " << lRes.second << std::endl;
	// Output should be 999, ~~~

	return 0;
}
