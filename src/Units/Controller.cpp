#include "Units/Controller.hpp"

#include "BitUtils.hpp"
#include "RISCV-Constants.hpp"
#include "Types/Wire.hpp"

#include <iostream>

Controller::Controller() : Node(1, 10, "Controller") {}

void Controller::ProcessInternal()
{
	WireData opcode = GetWireData(OpcodeIndex);

	// Control bits
	WireData lBranch = 0u;
	WireData lMemRead = 0u;
	WireData lMemToReg = 0u;
	WireData lMemWrite = 0u;
	WireData lALUSrc = 0u;
	WireData lRegWrite = 0u;
	WireData lALUOp = 0u;
	WireData lJumpReg = 0u;
	WireData lLink = 0u;
	WireData lAUIPC = 0u;

	// Note: ALUSrc determines whether to use the immediate value for the ALU
	// or the register value from rs2

	if (opcode == OPCODE_R_TYPE)
	{
		lRegWrite = 1;

		lALUOp = 0b10;
	}
	else if (opcode == OPCODE_S_TYPE)
	{
		lALUSrc = 1;
		lMemWrite = 1;

		lALUOp = 0b00;
	}
	else if (opcode == OPCODE_I_TYPE)
	{
		lALUSrc = 1;
		lRegWrite = 1;

		lALUOp = 0b10;
	}
	else if (opcode == OPCODE_LOAD_TYPE)
	{
		lALUSrc = 1;
		lMemToReg = 1;
		lRegWrite = 1;
		lMemRead = 1;

		lALUOp = 0b00;
	}
	else if (opcode == OPCODE_B_TYPE)
	{
		lBranch = 1;

		lALUOp = 0b01;
	}
	else if (opcode == OPCODE_JALR)
	{
		lALUSrc = 1;
		lRegWrite = 1;
		lJumpReg = 1;
		lLink = 1;

		lALUOp = 0b10;
	}
	else if (opcode == OPCODE_J_TYPE)
	{
		lRegWrite = 1;
		lBranch = 1;
		lLink = 1;

		lALUOp = 0b11;
	}
	else if (opcode == OPCODE_LUI)
	{
		lALUSrc = 1;
		lRegWrite = 1;

		lALUOp = 0b11;
	}
	else if (opcode == OPCODE_AUIPC)
	{
		lALUSrc = 1;
		lRegWrite = 1;
		lAUIPC = 1;

		lALUOp = 0b11;
	}

	SetWireData(BranchIndex, lBranch);
	SetWireData(MemReadIndex, lMemRead);
	SetWireData(MemToRegIndex, lMemToReg);
	SetWireData(ALUOpIndex, lALUOp);
	SetWireData(MemWriteIndex, lMemWrite);
	SetWireData(ALUSrcIndex, lALUSrc);
	SetWireData(RegWriteIndex, lRegWrite);
	SetWireData(JumpRegIndex, lJumpReg);
	SetWireData(LinkIndex, lLink);
	SetWireData(AUIPCIndex, lAUIPC);
}
