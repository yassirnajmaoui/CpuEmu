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

#include <iostream>
#include <memory>

/* TODOs:
 * Add Wire data truncating here
 * Add JAL and JALR implementation (Need to add a control bit)
 */

int main()
{
	// Instructions
	std::vector<WireData> lInstructions{Instructions::ADDI(1000, 12, 0),
										Instructions::ADDI(157, 11, 0),
										Instructions::ADD(13, 11, 12),
										Instructions::SLLI(14, 13, 5),
										Instructions::BNE(-4, 13, 11)};

	// clang-format off
	// ---------------- Nodes ----------------
	// PC module
	auto lpPC = std::make_shared<Relay>("PC Relay");
	auto lpClock = Node::CreateInputWire(lpPC, lpPC->SignalIndex);

	// Other nodes
	auto lpInstructionMemory = std::make_shared<ReadOnlyMemory>(std::move(lInstructions));

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
	auto lpDataMemory = std::make_shared<Memory>();
	auto lpRegWriterMux = std::make_shared<Multiplexer<2>>("RegWrite Multiplexer");
	auto lpRegWriter = std::make_shared<RegistersWriter>(lpRegisters);
	auto lpBranchAdder = std::make_shared<Adder>();
	auto lpBranchAnd = std::make_shared<Operator<2, 1>>(
	    [](std::array<WireData, 2> pInputs)
	    {
		    return std::array<WireData, 1>({pInputs[0] & pInputs[1]});
	    }, "Branch AND");
	auto lpPCAdder = std::make_shared<Adder>();
	auto lpPCMux = std::make_shared<Multiplexer<2>>("PC Multiplexer");

	// Wires
	std::vector<std::shared_ptr<Wire>> lWires;

	// ---------------- Connections ----------------	
	// PC
	auto lpPCMultiplier = std::make_shared<Multiplier<3>>();
	auto lpPCOut = Node::ConnectNodes(lpPC, lpPC->OutputIndex, lpPCMultiplier, lpPCMultiplier->InputIndex);
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<0>(), lpInstructionMemory, lpInstructionMemory->ReadAddressIndex));
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<1>(), lpBranchAdder, lpBranchAdder->Input1Index));
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<2>(), lpPCAdder, lpPCAdder->Input1Index));
	auto lpAdd4 = Node::CreateInputWire(lpPCAdder, lpPCAdder->Input2Index);// Wire with the value 4
	lWires.emplace_back(Node::ConnectNodes(lpPCAdder, lpPCAdder->OutputIndex, lpPCMux, lpPCMux->GetInputIndex<0>()));

	// Instruction memory & Instruction parser
	lWires.emplace_back(Node::ConnectNodes(lpInstructionMemory, lpInstructionMemory->OutputDataIndex, lpInstructionParser, lpInstructionParser->InstructionIndex));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->OpcodeIndex, lpControlUnit, lpControlUnit->OpcodeIndex));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RS1Index, lpRegisters, lpRegisters->ReadRegister1Index));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RS2Index, lpRegisters, lpRegisters->ReadRegister2Index));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->Funct3Index, lpALUControl, lpALUControl->Func3Index));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->SignBitIndex, lpALUControl, lpALUControl->SignBitIndex));
	auto lpInstructionParserImmMultiplier = std::make_shared<Multiplier<2>>();
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->ImmIndex, lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->InputIndex));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->GetOutputIndex<0>(), lpALUMux, lpALUMux->GetInputIndex<1>()));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->GetOutputIndex<1>(), lpShiftLeft1, lpShiftLeft1->InputIndex));

	// Registers reader
	auto lpRegReadData2Multiplier = std::make_shared<Multiplier<2>>();
	lWires.emplace_back(Node::ConnectNodes(lpRegisters, lpRegisters->ReadData2Index, lpRegReadData2Multiplier, lpRegReadData2Multiplier->InputIndex));
	lWires.emplace_back(Node::ConnectNodes(lpRegReadData2Multiplier, lpRegReadData2Multiplier->GetOutputIndex<0>(), lpALUMux, lpALUMux->GetInputIndex<0>()));
	lWires.emplace_back(Node::ConnectNodes(lpRegReadData2Multiplier, lpRegReadData2Multiplier->GetOutputIndex<1>(), lpDataMemory, lpDataMemory->WriteDataIndex));

	// ALU
	lWires.emplace_back(Node::ConnectNodes(lpALUMux, lpALUMux->OutputIndex, lpALU, lpALU->RD2Index));
	lWires.emplace_back(Node::ConnectNodes(lpRegisters, lpRegisters->ReadData1Index, lpALU, lpALU->RD1Index));
	lWires.emplace_back(Node::ConnectNodes(lpALUControl, lpALUControl->ALUSelectIndex, lpALU, lpALU->ALUSelectIndex));
	lWires.emplace_back(Node::ConnectNodes(lpALU, lpALU->ALUZeroIndex, lpBranchAnd, lpBranchAnd->GetInputIndex<1>()));

	// Data memory
	auto lpALUResultMultiplier = std::make_shared<Multiplier<2>>();	
	lWires.emplace_back(Node::ConnectNodes(lpALU, lpALU->ALUResultIndex, lpALUResultMultiplier, lpALUResultMultiplier->InputIndex));
	lWires.emplace_back(Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<0>(), lpDataMemory, lpDataMemory->AddressIndex));
	lWires.emplace_back(Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<1>(), lpRegWriterMux, lpRegWriterMux->GetInputIndex<0>()));
	lWires.emplace_back(Node::ConnectNodes(lpDataMemory, lpDataMemory->ReadDataIndex, lpRegWriterMux, lpRegWriterMux->GetInputIndex<1>()));

	//Registers writer
	lWires.emplace_back(Node::ConnectNodes(lpRegWriterMux, lpRegWriterMux->OutputIndex, lpRegWriter, lpRegWriter->WriteDataIndex));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RDIndex, lpRegWriter, lpRegWriter->WriteRegisterIndex));

	// Controller
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->BranchIndex, lpBranchAnd, lpBranchAnd->GetInputIndex<0>()));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemReadIndex, lpDataMemory, lpDataMemory->MemReadIndex));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemToRegIndex, lpRegWriterMux, lpRegWriterMux->InputSelectionIndex));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUOpIndex, lpALUControl, lpALUControl->ALUOpIndex));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemWriteIndex, lpDataMemory, lpDataMemory->MemWriteIndex));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUSrcIndex, lpALUMux, lpALUMux->InputSelectionIndex));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->RegWriteIndex, lpRegWriter, lpRegWriter->RegWriteIndex));
	lWires.emplace_back(Node::CreateOutputWire(lpControlUnit, lpControlUnit->JumpRegIndex));// TODO: Connect the JumpReg wire once done

	// Branching
	lWires.emplace_back(Node::ConnectNodes(lpShiftLeft1, lpShiftLeft1->OutputIndex, lpBranchAdder, lpBranchAdder->Input2Index));
	lWires.emplace_back(Node::ConnectNodes(lpBranchAdder, lpBranchAdder->OutputIndex, lpPCMux, lpPCMux->GetInputIndex<1>()));
	lWires.emplace_back(Node::ConnectNodes(lpBranchAnd, lpBranchAnd->GetOutputIndex<0>(), lpPCMux, lpPCMux->InputSelectionIndex));

	// Final loop
	auto lpLoopbackWire = Node::ConnectNodes(lpPCMux, lpPCMux->OutputIndex, lpPC, lpPC->InputIndex);

	// clang-format on

	// Init
	lpAdd4->SetData(4);
	lpClock->SetData(0);
	lpLoopbackWire->SetData(0);

	// Clock
	auto lClockFunc = [&]()
	{
		lpAdd4->SetDataReady();
		lpClock->SetDataReady();
		lpLoopbackWire->SetDataReady();
	};

	for (size_t i = 0; i < lInstructions.size(); ++i)
	{
		std::cout << "PC: " << lpLoopbackWire->GetData() << "\n";
		lClockFunc();
	}
	std::cout << "PC: " << lpLoopbackWire->GetData() << "\n";

	for (size_t i = 0; i < lpRegisters->NumberOfRegisters; i++)
	{
		std::cout << "Reg [" << i << "]: " << lpRegisters->GetRegisterValue(i) << std::endl;
	}

	return 0;
}
