#include "Units/Controller.hpp"
#include "Types/Wire.hpp"
#include "BitUtils.hpp"
#include "RISCV-Constants.hpp"

Controller::Controller() :
	Node(1, 8, "Controller")
{
}

void Controller::ProcessInternal()
{
	WireData opcode = GetWireData(OpcodeIndex);

	// Control bits
	WireData lBranch = 0;
	WireData lMemRead = 0;
	WireData lMemToReg = 0;
	WireData lMemWrite = 0;
	WireData lALUSrc = 0;
	WireData lRegWrite = 0;
	WireData lALUOp = 0;
	WireData lJumpReg = 0;

	// Note: ALUSrc determines whether to use the immediate value for the ALU
	// or the register value from rs2

	if(opcode == OPCODE_R_TYPE)
	{
		lALUSrc = 0;
		lMemToReg = 0;
		lRegWrite = 1;
		lMemRead = 0;
		lMemWrite = 0;
		lBranch = 0;
		lJumpReg = 0;

		lALUOp = 0b10;
	}
	else if(opcode == OPCODE_S_TYPE)
	{
		lALUSrc = 1;
		lMemToReg = 0;
		lRegWrite = 0;
		lMemRead = 0;
		lMemWrite = 1;
		lBranch = 0;
		lJumpReg = 0;
		
		lALUOp = 0b00;
	}
	else if(opcode == OPCODE_I_TYPE)
	{
		lALUSrc = 1;
		lMemToReg = 0;
		lRegWrite = 1;
		lMemRead = 0;
		lMemWrite = 0;
		lBranch = 0;
		lJumpReg = 0;
		
		lALUOp = 0b10;
	}
	else if(opcode == OPCODE_LOAD_TYPE)
	{
		lALUSrc = 1;
		lMemToReg = 1;
		lRegWrite = 1;
		lMemRead = 1;
		lMemWrite = 0;
		lBranch = 0;
		lJumpReg = 0;
		
		lALUOp = 0b00;
	}
	else if(opcode == OPCODE_B_TYPE)
	{
		lALUSrc = 0;
		lMemToReg = 0;
		lRegWrite = 1;
		lMemRead = 0;
		lMemWrite = 0;
		lBranch = 1;
		lJumpReg = 0;
		
		lALUOp = 0b01;
	}
	else if(opcode == OPCODE_J_TYPE)
	{
		lALUSrc = 0;
		lMemToReg = 0;
		lRegWrite = 1;
		lMemRead = 0;
		lMemWrite = 0;
		lBranch = 1;
		lJumpReg = 0;
		
		lALUOp = 0b11;
	}
	else if(opcode == OPCODE_JALR)
	{
		lALUSrc = 1;
		lMemToReg = 0;
		lRegWrite = 1;
		lMemRead = 0;
		lMemWrite = 0;
		lBranch = 1;
		lJumpReg = 1;
		
		lALUOp = 0b10;
	}
	else if(opcode == OPCODE_LUI)
	{
		lALUSrc = 1;
		lMemToReg = 0;
		lRegWrite = 1;
		lMemRead = 0;
		lMemWrite = 0;
		lBranch = 0;
		lJumpReg = 0;
		
		lALUOp = 0b11;
	}
	else if(opcode == OPCODE_AUIPC)
	{
		lALUSrc = 1;
		lMemToReg = 0;
		lRegWrite = 1;
		lMemRead = 0;
		lMemWrite = 0;
		lBranch = 0;
		lJumpReg = 0;
		
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
}
