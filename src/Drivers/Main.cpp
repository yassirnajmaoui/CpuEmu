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
#include <iostream>
#include <memory>

/* TODOs:
 * Make SB, AH, LB and LH work + test if offsetting works
 * Add JAL and JALR implementation (Need to add a control bit)
 */

int main()
{
	// Instructions
	std::vector<WireData> lInstructions{Instructions::ADDI(-1485, 2, 0),
										Instructions::SH(2,0,2),
										Instructions::LB(2,5,0)};

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
	auto lpPCOut = Node::ConnectNodes(lpPC, lpPC->OutputIndex, lpPCMultiplier, lpPCMultiplier->InputIndex, 32);
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<0>(), lpInstructionMemory, lpInstructionMemory->ReadAddressIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<1>(), lpBranchAdder, lpBranchAdder->Input1Index, 32));
	lWires.emplace_back(Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<2>(), lpPCAdder, lpPCAdder->Input1Index, 32));
	auto lpAdd4 = Node::CreateInputWire(lpPCAdder, lpPCAdder->Input2Index, 32, true);// Wire with the value 4
	lWires.emplace_back(Node::ConnectNodes(lpPCAdder, lpPCAdder->OutputIndex, lpPCMux, lpPCMux->GetInputIndex<0>(), 32));

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
	auto lpALUResultMultiplier = std::make_shared<Multiplier<2>>();
	lWires.emplace_back(Node::ConnectNodes(lpALU, lpALU->ALUResultIndex, lpALUResultMultiplier, lpALUResultMultiplier->InputIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<0>(), lpDataMemory, lpDataMemory->AddressIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<1>(), lpRegWriterMux, lpRegWriterMux->GetInputIndex<0>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpDataMemory, lpDataMemory->ReadDataIndex, lpRegWriterMux, lpRegWriterMux->GetInputIndex<1>(), 32));

	// Registers writer
	lWires.emplace_back(Node::ConnectNodes(lpRegWriterMux, lpRegWriterMux->OutputIndex, lpRegWriter, lpRegWriter->WriteDataIndex, 32));
	lWires.emplace_back(Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RDIndex, lpRegWriter, lpRegWriter->WriteRegisterIndex, 5));

	// Controller
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->BranchIndex, lpBranchAnd, lpBranchAnd->GetInputIndex<0>(), 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemReadIndex, lpDataMemory, lpDataMemory->MemReadIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemToRegIndex, lpRegWriterMux, lpRegWriterMux->InputSelectionIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUOpIndex, lpALUControl, lpALUControl->ALUOpIndex, 2));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->MemWriteIndex, lpDataMemory, lpDataMemory->MemWriteIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUSrcIndex, lpALUMux, lpALUMux->InputSelectionIndex, 1));
	lWires.emplace_back(Node::ConnectNodes(lpControlUnit, lpControlUnit->RegWriteIndex, lpRegWriter, lpRegWriter->RegWriteIndex, 1));
	lWires.emplace_back(Node::CreateOutputWire(lpControlUnit, lpControlUnit->JumpRegIndex, 1));// TODO: Connect the JumpReg wire once JAL & JALR done

	// Branching
	lWires.emplace_back(Node::ConnectNodes(lpShiftLeft1, lpShiftLeft1->OutputIndex, lpBranchAdder, lpBranchAdder->Input2Index, 32));
	lWires.emplace_back(Node::ConnectNodes(lpBranchAdder, lpBranchAdder->OutputIndex, lpPCMux, lpPCMux->GetInputIndex<1>(), 32));
	lWires.emplace_back(Node::ConnectNodes(lpBranchAnd, lpBranchAnd->GetOutputIndex<0>(), lpPCMux, lpPCMux->InputSelectionIndex, 1));

	// Final loop
	// LoopbackWire contains the Value that would be put to the PC
	auto lpLoopbackWire = Node::ConnectNodes(lpPCMux, lpPCMux->OutputIndex, lpPC, lpPC->InputIndex, 32);

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
		std::cout << "Reg [" << i << "]:\t" << std::bitset<32>(lRegVal) << " ("
				  << lRegVal << ")" << std::endl;
	}
	std::cout << "Memory" << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		WireData lMemVal = lpDataMemory->GetMemoryData(i);
		std::cout << "Mem [" << i << "]:\t" << std::bitset<32>(lMemVal) << " ("
				  << lMemVal << ")" << std::endl;
	}

	return 0;
}
