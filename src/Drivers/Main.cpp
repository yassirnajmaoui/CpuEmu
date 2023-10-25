#include "RISCV-Instructions.hpp"
#include "Units/ALU.hpp"
#include "Units/ALUControl.hpp"
#include "Units/Adder.hpp"
#include "Units/Controller.hpp"
#include "Units/InstructionParser.hpp"
#include "Units/Memory.hpp"
#include "Units/Multiplexer.hpp"
#include "Units/Multiplier.hpp"
#include "Units/Operator.hpp"
#include "Units/ReadOnlyMemory.hpp"
#include "Units/Registers.hpp"
#include "Units/RegistersWriter.hpp"
#include "Units/Relay.hpp"
#include "Units/SimpleOperator.hpp"
#include "Utils.hpp"

#include <bitset>
#include <cstring>
#include <iostream>
#include <memory>

/* TODOs:
 * test LUI and AUIPC
 */

int main()
{
	// Instructions
	std::vector<WireData> lInstructions{
	// make registry 10 point to memory address of a string
	Instructions::ADDI(0, 10, 0),
	//-- func start
	Instructions::ADDI(0, 5, 0),
	//-- loop
	Instructions::ADD(6, 5, 10),
	Instructions::LB(0, 6, 6),
	Instructions::BEQ(+6, 6, 0),
	Instructions::ADDI(1, 5, 5),
	Instructions::JAL(-8, 31),
	//-- loop
	Instructions::SW(0, 5, 5)
	//-- func end
	};

	std::string mystr = "Hello:) My name is Whoo!";
	std::vector<Byte> lMemory;
	lMemory.resize(mystr.size() + 1*sizeof(WireData));// + 1 For the null terminator
	std::memcpy(lMemory.data(), mystr.data(), mystr.size());

	// clang-format off

	// ---------------- Nodes ----------------
	// PC module
	auto lpPC = std::make_shared<Relay>("PC Relay");
	auto lpClock = Node::CreateInputWire(lpPC, lpPC->SignalIndex);

	// Other nodes
	auto lpInstructionMemory = std::make_shared<ReadOnlyMemory>(std::move(lInstructions), "Instruction memory");

	auto lpInstructionParser = std::make_shared<InstructionParser>();
	auto lpShiftLeft1 = std::make_shared<SimpleOperator>(
	    [](WireData pAddr) -> WireData
	    {
		    return pAddr << 1;
	    }, "Shift left 1");
	auto lpRegisters = std::make_shared<Registers>();
	auto lpControlUnit = std::make_shared<Controller>();
	auto lpALUMux = std::make_shared<Multiplexer<2>>("ALU Multiplexer");
	auto lpALUControl = std::make_shared<ALUControl>();
	auto lpALU = std::make_shared<ALU>();
	auto lpDataMemory = std::make_shared<Memory>(std::move(lMemory));
	auto lpRegWriterMux = std::make_shared<Multiplexer<2>>("RegWrite Multiplexer");
	auto lpLinkMux = std::make_shared<Multiplexer<2>>("Link Multiplexer");
	auto lpRegWriter = std::make_shared<RegistersWriter>(lpRegisters);
	auto lpBranchAdder = std::make_shared<Adder>();
	auto lpBranchAnd = std::make_shared<Operator<2, 1>>(
	    [](std::array<WireData, 2> pInputs)
	    {
		    return std::array<WireData, 1>({pInputs[0] & pInputs[1]});
	    }, "Branch AND");
	auto lpPCAdder = std::make_shared<Adder>();
	auto lpBranchMux = std::make_shared<Multiplexer<2>>("PC Multiplexer");
	auto lpJumpRegMux = std::make_shared<Multiplexer<2>>("JumpReg Multiplexer");

	// Wires
	std::vector<std::shared_ptr<Wire>> lWires;

	// ---------------- Connections ----------------	
	// PC
	auto lpPCMultiplier = std::make_shared<Multiplier<3>>();
	auto lpPCOut = Node::ConnectNodes(lpPC, lpPC->OutputIndex, lpPCMultiplier, lpPCMultiplier->InputIndex, 32);
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<0>(), lpInstructionMemory, lpInstructionMemory->ReadAddressIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<1>(), lpBranchAdder, lpBranchAdder->Input1Index, 32));
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<2>(), lpPCAdder, lpPCAdder->Input1Index, 32));
	auto lpAdd4 = Node::CreateInputWire(lpPCAdder, lpPCAdder->Input2Index, 32, true);// Wire with the value 4
	// Link
	auto lpPCPlus4Multiplier = std::make_shared<Multiplier<2>>();
	lWires.emplace_back(Node::ConnectNodes(lpPCAdder, lpPCAdder->OutputIndex, lpPCPlus4Multiplier, lpPCPlus4Multiplier->InputIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpPCPlus4Multiplier, lpPCPlus4Multiplier->GetOutputIndex<0>(), lpBranchMux, lpBranchMux->GetInputIndex<0>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpPCPlus4Multiplier, lpPCPlus4Multiplier->GetOutputIndex<1>(), lpLinkMux, lpLinkMux->GetInputIndex<1>(), 32));

	// Instruction memory & Instruction parser
	lWires.emplace_back(Node::ConnectNodes(lpInstructionMemory, lpInstructionMemory->OutputDataIndex, lpInstructionParser, lpInstructionParser->InstructionIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->OpcodeIndex, lpControlUnit, lpControlUnit->OpcodeIndex, 7));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RS1Index, lpRegisters, lpRegisters->ReadRegister1Index, 5));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RS2Index, lpRegisters, lpRegisters->ReadRegister2Index, 5));
	auto lpFunct3Multiplier = std::make_shared<Multiplier<2>>();
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->Funct3Index, lpFunct3Multiplier, lpFunct3Multiplier->InputIndex, 3));
	lWires.emplace_back(Node::ConnectNodes(lpFunct3Multiplier, lpFunct3Multiplier->GetOutputIndex<0>(), lpALUControl, lpALUControl->Funct3Index, 3));
	lWires.emplace_back(Node::ConnectNodes(lpFunct3Multiplier, lpFunct3Multiplier->GetOutputIndex<1>(), lpDataMemory, lpDataMemory->Funct3Index, 3));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->SignBitIndex, lpALUControl, lpALUControl->SignBitIndex, 1));
	auto lpInstructionParserImmMultiplier = std::make_shared<Multiplier<2>>();
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->ImmIndex, lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->InputIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->GetOutputIndex<0>(), lpALUMux, lpALUMux->GetInputIndex<1>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->GetOutputIndex<1>(), lpShiftLeft1, lpShiftLeft1->InputIndex, 32));

	// Registers reader
	auto lpRegReadData2Multiplier = std::make_shared<Multiplier<2>>();
	lWires.emplace_back(Node::ConnectNodes(lpRegisters, lpRegisters->ReadData2Index, lpRegReadData2Multiplier, lpRegReadData2Multiplier->InputIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpRegReadData2Multiplier, lpRegReadData2Multiplier->GetOutputIndex<0>(), lpALUMux, lpALUMux->GetInputIndex<0>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpRegReadData2Multiplier, lpRegReadData2Multiplier->GetOutputIndex<1>(), lpDataMemory, lpDataMemory->WriteDataIndex, 32));

	// ALU
	lWires.emplace_back(Node::ConnectNodes(lpALUMux, lpALUMux->OutputIndex, lpALU, lpALU->RD2Index, 32));
	lWires.emplace_back(Node::ConnectNodes(lpRegisters, lpRegisters->ReadData1Index, lpALU, lpALU->RD1Index, 32));
	lWires.emplace_back(Node::ConnectNodes(lpALUControl, lpALUControl->ALUSelectIndex, lpALU, lpALU->ALUSelectIndex, 5));
	lWires.emplace_back(Node::ConnectNodes(lpALU, lpALU->ALUZeroIndex, lpBranchAnd, lpBranchAnd->GetInputIndex<1>(), 1));

	// Data memory
	auto lpALUResultMultiplier = std::make_shared<Multiplier<3>>();
	lWires.emplace_back(Node::ConnectNodes(lpALU, lpALU->ALUResultIndex, lpALUResultMultiplier, lpALUResultMultiplier->InputIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<0>(), lpDataMemory, lpDataMemory->AddressIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpDataMemory, lpDataMemory->ReadDataIndex, lpRegWriterMux, lpRegWriterMux->GetInputIndex<1>(), 32));

	// Registers writer
	lWires.emplace_back(Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<1>(), lpRegWriterMux, lpRegWriterMux->GetInputIndex<0>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpRegWriterMux, lpRegWriterMux->OutputIndex, lpLinkMux, lpLinkMux->GetInputIndex<0>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpLinkMux, lpLinkMux->OutputIndex, lpRegWriter, lpRegWriter->WriteDataIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RDIndex, lpRegWriter, lpRegWriter->WriteRegisterIndex, 5));

	// Controller
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->BranchIndex, lpBranchAnd, lpBranchAnd->GetInputIndex<0>(), 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemReadIndex, lpDataMemory, lpDataMemory->MemReadIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemToRegIndex, lpRegWriterMux, lpRegWriterMux->InputSelectionIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUOpIndex, lpALUControl, lpALUControl->ALUOpIndex, 2));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemWriteIndex, lpDataMemory, lpDataMemory->MemWriteIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUSrcIndex, lpALUMux, lpALUMux->InputSelectionIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->RegWriteIndex, lpRegWriter, lpRegWriter->RegWriteIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->JumpRegIndex, lpJumpRegMux, lpJumpRegMux->InputSelectionIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->LinkIndex, lpLinkMux, lpLinkMux->InputSelectionIndex, 1));

	// Branch & Jump
	lWires.emplace_back(Node::ConnectNodes(lpShiftLeft1, lpShiftLeft1->OutputIndex, lpBranchAdder, lpBranchAdder->Input2Index, 32));
	lWires.emplace_back(Node::ConnectNodes(lpBranchAdder, lpBranchAdder->OutputIndex, lpBranchMux, lpBranchMux->GetInputIndex<1>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpBranchAnd, lpBranchAnd->GetOutputIndex<0>(), lpBranchMux, lpBranchMux->InputSelectionIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<2>(), lpJumpRegMux, lpJumpRegMux->GetInputIndex<1>(), 32));

	// Final loop
	// LoopbackWire contains the Value that would be put to the PC
	lWires.emplace_back(Node::ConnectNodes(lpBranchMux, lpBranchMux->OutputIndex, lpJumpRegMux, lpJumpRegMux->GetInputIndex<0>(), 32));
	auto lpLoopbackWire = Node::ConnectNodes(lpJumpRegMux, lpJumpRegMux->OutputIndex, lpPC, lpPC->InputIndex);

	// clang-format on

	// Init
	lpAdd4->SetData(4);
	lpClock->SetData(0);
	lpLoopbackWire->SetData(0);

	// Clock
	auto lClockFunc = [&]()
	{
		lpClock->SetDataReady();
		lpLoopbackWire->SetDataReady();
	};

	while (lpLoopbackWire->GetData() < lInstructions.size() * 4)
	{
		std::cout << "------------------------------------------------------------------" << std::endl;
		std::cout << "PC: " << lpLoopbackWire->GetData() << "\n";
		lClockFunc();
	}
	std::cout << "PC: " << lpLoopbackWire->GetData() << "\n";

	std::cout << "Registers" << std::endl;
	for (size_t i = 0; i < lpRegisters->NumberOfRegisters; i++)
	{
		int lRegVal = static_cast<int>(lpRegisters->GetRegisterValue(i));
		std::cout << "Reg [" << i << "]:\t" << std::bitset<32>(lRegVal) << " (" << lRegVal << ")" << std::endl;
	}
	std::cout << "Memory" << std::endl;
	for (size_t i = 0; i < lpDataMemory->GetMemorySize(); i++)
	{
		WireData lMemVal = lpDataMemory->GetMemoryData(i);
		std::cout << "Mem [" << i << "]:\t" << std::bitset<8>(lMemVal) << " (" << lMemVal << ")" << std::endl;
	}

	return 0;
}
