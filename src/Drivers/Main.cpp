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
 * Implement the full datapath
 * Add JAL and JALR implementation (Need to add a control bit)
 */

int main()
{
	// clang-format off
	// ---------------- Nodes ----------------
	// PC module
	auto lpPC = std::make_shared<Relay>();
	auto lpClock = Node::CreateInputWire(lpPC, Relay::SignalIndex);

	// Other nodes
	auto lpInstructionMemory = std::make_shared<ReadOnlyMemory>(/*TODO: Add instructions here*/);

	auto lpInstructionParser = std::make_shared<InstructionParser>();
	auto lpShiftLeft1 = std::make_shared<SimpleOperator>(
	    [](WireData pAddr) -> WireData
	    {
		    return pAddr << 1;
	    });
	auto lpRegisters = std::make_shared<Registers>();
	auto lpControlUnit = std::make_shared<Controller>();
	auto lpALUMux = std::make_shared<Multiplexer<2>>();
	auto lpALUControl = std::make_shared<ALUControl>();
	auto lpALU = std::make_shared<ALU>();
	auto lpDataMemory = std::make_shared<Memory>();
	auto lpRegWriterMux = std::make_shared<Multiplexer<2>>();
	auto lpRegWriter = std::make_shared<RegistersWriter>(lpRegisters);
	auto lpBranchAdder = std::make_shared<Adder>();
	auto lpBranchAnd = std::make_shared<Operator<2, 1>>(
	    [](std::array<WireData, 2> pInputs)
	    {
		    return std::array<WireData, 1>({pInputs[0] & pInputs[1]});
	    });
	auto lpPCAdder = std::make_shared<Adder>();
	auto lpPCMux = std::make_shared<Multiplexer<2>>();

	// ---------------- Connections ----------------
	// PC
	auto lpPCMultiplier = std::make_shared<Multiplier<3>>();
	Node::ConnectNodes(lpPC, Relay::OutputIndex, lpPCMultiplier, lpPCMultiplier->InputIndex);
	Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<0>(), lpInstructionMemory, lpInstructionMemory->ReadAddressIndex);
	Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<1>(), lpBranchAdder, lpBranchAdder->Input1Index);
	Node::ConnectNodes(lpPCMultiplier, lpPCMultiplier->GetOutputIndex<2>(), lpPCAdder, lpPCAdder->Input1Index);
	auto lpAdd4 = Node::CreateInputWire(lpPCAdder, lpPCAdder->Input2Index);// Wire with the value 4
	Node::ConnectNodes(lpPCAdder, lpPCAdder->OutputIndex, lpPCMux, lpPCMux->GetInputIndex<0>());

	// Instruction memory & Instruction parser
	Node::ConnectNodes(lpInstructionMemory, ReadOnlyMemory::OutputDataIndex, lpInstructionParser, lpInstructionParser->InstructionIndex);
	Node::ConnectNodes(lpInstructionParser, InstructionParser::OpcodeIndex, lpControlUnit, lpControlUnit->OpcodeIndex);
	Node::ConnectNodes(lpInstructionParser, InstructionParser::RS1Index, lpRegisters, lpRegisters->ReadRegister1Index);
	Node::ConnectNodes(lpInstructionParser, InstructionParser::RS2Index, lpRegisters, lpRegisters->ReadRegister2Index);
	Node::ConnectNodes(lpInstructionParser, InstructionParser::Funct3Index, lpALUControl, lpALUControl->Func3Index);
	Node::ConnectNodes(lpInstructionParser, InstructionParser::SignBitIndex, lpALUControl, lpALUControl->SignBitIndex);
	auto lpInstructionParserImmMultiplier = std::make_shared<Multiplier<2>>();
	Node::ConnectNodes(lpInstructionParser, InstructionParser::ImmIndex, lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->InputIndex);
	Node::ConnectNodes(lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->GetOutputIndex<0>(), lpALUMux, lpALUMux->GetInputIndex<1>());
	Node::ConnectNodes(lpInstructionParserImmMultiplier, lpInstructionParserImmMultiplier->GetOutputIndex<1>(), lpShiftLeft1, lpShiftLeft1->InputIndex);

	// Registers reader
	auto lpRegReadData2Multiplier = std::make_shared<Multiplier<2>>();
	Node::ConnectNodes(lpRegisters, Registers::ReadData2Index, lpRegReadData2Multiplier, lpRegReadData2Multiplier->InputIndex);
	Node::ConnectNodes(lpRegReadData2Multiplier, lpRegReadData2Multiplier->GetOutputIndex<0>(), lpALUMux, lpALUMux->GetInputIndex<0>());
	Node::ConnectNodes(lpRegReadData2Multiplier, lpRegReadData2Multiplier->GetOutputIndex<1>(), lpDataMemory, lpDataMemory->WriteDataIndex);

	// ALU
	Node::ConnectNodes(lpALUMux, lpALUMux->OutputIndex, lpALU, lpALU->RD2Index);
	Node::ConnectNodes(lpRegisters, lpRegisters->ReadData1Index, lpALU, lpALU->RD1Index);
	Node::ConnectNodes(lpALUControl, lpALUControl->ALUSelectIndex, lpALU, lpALU->ALUSelectIndex);
	Node::ConnectNodes(lpALU, lpALU->ALUZeroIndex, lpBranchAnd, lpBranchAnd->GetInputIndex<1>());

	// Data memory
	auto lpALUResultMultiplier = std::make_shared<Multiplier<2>>();	
	Node::ConnectNodes(lpALU, lpALU->ALUResultIndex, lpALUResultMultiplier, lpALUResultMultiplier->InputIndex);
	Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<0>(), lpDataMemory, lpDataMemory->AddressIndex);
	Node::ConnectNodes(lpALUResultMultiplier, lpALUResultMultiplier->GetOutputIndex<1>(), lpRegWriterMux, lpRegWriterMux->GetInputIndex<0>());
	Node::ConnectNodes(lpDataMemory, lpDataMemory->ReadDataIndex, lpRegWriterMux, lpRegWriterMux->GetInputIndex<1>());

	//Registers writer
	Node::ConnectNodes(lpRegWriterMux, lpRegWriterMux->OutputIndex, lpRegWriter, lpRegWriter->WriteDataIndex);
	Node::ConnectNodes(lpInstructionParser, lpInstructionParser->RDIndex, lpRegWriter, lpRegWriter->WriteRegisterIndex);

	// Controller
	Node::ConnectNodes(lpControlUnit, lpControlUnit->BranchIndex, lpBranchAnd, lpBranchAnd->GetInputIndex<0>());
	Node::ConnectNodes(lpControlUnit, lpControlUnit->MemReadIndex, lpDataMemory, lpDataMemory->MemReadIndex);
	Node::ConnectNodes(lpControlUnit, lpControlUnit->MemToRegIndex, lpRegWriterMux, lpRegWriterMux->InputSelectionIndex);
	Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUOpIndex, lpALUControl, lpALUControl->ALUOpIndex);
	Node::ConnectNodes(lpControlUnit, lpControlUnit->MemWriteIndex, lpDataMemory, lpDataMemory->MemWriteIndex);
	Node::ConnectNodes(lpControlUnit, lpControlUnit->ALUSrcIndex, lpALUMux, lpALUMux->InputSelectionIndex);
	Node::ConnectNodes(lpControlUnit, lpControlUnit->RegWriteIndex, lpRegWriter, lpRegWriter->RegWriteIndex);

	// Branching
	Node::ConnectNodes(lpShiftLeft1, lpShiftLeft1->OutputIndex, lpBranchAdder, lpBranchAdder->Input2Index);
	Node::ConnectNodes(lpBranchAdder, lpBranchAdder->OutputIndex, lpPCMux, lpPCMux->GetInputIndex<1>());
	Node::ConnectNodes(lpBranchAnd, lpBranchAnd->GetOutputIndex<0>(), lpPCMux, lpPCMux->InputSelectionIndex);

	// Final loop
	Node::ConnectNodes(lpPCMux, lpPCMux->OutputIndex, lpPC, lpPC->InputIndex);


	// TODO: add initialize function
	// TODO: add an instruction
	// Test the instruction
	
	// clang-format on
	return 0;
}
