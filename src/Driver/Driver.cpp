#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Units/Registers.hpp"
#include "Utils.hpp"

#include <iostream>
#include <memory>

int main()
{
	auto lRegisters = std::make_shared<Registers>();
	
	auto lRegWrite	= Node::CreateInputWire(lRegisters, Registers::RegWriteIndex);
	auto lReadRegister1	= Node::CreateInputWire(lRegisters, Registers::ReadRegister1Index);
	auto lReadRegister2	= Node::CreateInputWire(lRegisters, Registers::ReadRegister2Index);
	auto lWriteRegister	= Node::CreateInputWire(lRegisters, Registers::WriteRegisterIndex);
	auto lWriteData	= Node::CreateInputWire(lRegisters, Registers::WriteDataIndex);
	
	auto lReadData1	= Node::CreateOutputWire(lRegisters, Registers::ReadData1Index);
	auto lReadData2	= Node::CreateOutputWire(lRegisters, Registers::ReadData2Index);

	// Set all ready
	auto lSetAllInputsReadyFunc = [&]()
	{
		lRegWrite->SetDataReady();
		lReadRegister1->SetDataReady();
		lReadRegister2->SetDataReady();
		lWriteRegister->SetDataReady();
		lWriteData->SetDataReady();
	};

	// Write data
	lRegWrite->SetData(1);
	lReadRegister1->SetData(0);
	lReadRegister2->SetData(0);
	lWriteRegister->SetData(3);
	lWriteData->SetData(189894);

	lSetAllInputsReadyFunc();

	lRegWrite->SetData(0);
	lReadRegister1->SetData(3);
	lReadRegister2->SetData(0);
	lSetAllInputsReadyFunc();

	WireData lDataWritten = lReadData1->GetData();

	std::cout << "Data written: " << lDataWritten << std::endl;

	return 0;
}
