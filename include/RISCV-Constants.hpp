#pragma once

#include "Types/WireForward.hpp"

// The RISC-V Implementation chosen here is RV32I (No extensions)

constexpr WireData ALU_SELECT_ADD = 0b0000;
constexpr WireData ALU_SELECT_SLL = 0b0001;
constexpr WireData ALU_SELECT_XOR = 0b0100;
constexpr WireData ALU_SELECT_SRL = 0b0101;
constexpr WireData ALU_SELECT_SRA = 0b1101;
constexpr WireData ALU_SELECT_OR  = 0b0110;
constexpr WireData ALU_SELECT_AND = 0b0111;

// Instruction-type opcodes
constexpr WireData OPCODE_R_TYPE = 0b0110011;
constexpr WireData OPCODE_S_TYPE = 0b0100011;
constexpr WireData OPCODE_I_TYPE = 0b0010011;
constexpr WireData OPCODE_J_TYPE = 0b1101111;
constexpr WireData OPCODE_B_TYPE = 0b1100011;

// Instruction-specific opcodes
constexpr WireData OPCODE_JALR		= 0b1100111;
constexpr WireData OPCODE_LOAD_TYPE = 0b0000011; // LB, LH, LW, LBU, LHU
constexpr WireData OPCODE_LUI		= 0b0110111;
constexpr WireData OPCODE_AUIPC		= 0b0010111;
constexpr WireData OPCODE_FENCE		= 0b0001111;

// TODO: Manage ECALL operation
// TODO: Manage EBREAK operation