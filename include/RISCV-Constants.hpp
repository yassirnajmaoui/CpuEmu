#pragma once

#include "Types/WireForward.hpp"

// The RISC-V Implementation chosen here is RV32I (No extensions)

// Instruction-type opcodes
constexpr WireData OPCODE_R_TYPE = 0b0110011;
constexpr WireData OPCODE_S_TYPE = 0b0100011;
constexpr WireData OPCODE_I_TYPE = 0b0010011; // Arithmetic only
constexpr WireData OPCODE_J_TYPE = 0b1101111;
constexpr WireData OPCODE_B_TYPE = 0b1100011;

// Instruction-specific opcodes
constexpr WireData OPCODE_JALR = 0b1100111;
constexpr WireData OPCODE_LOAD_TYPE = 0b0000011; // LB, LH, LW, LBU, LHU
constexpr WireData OPCODE_LUI = 0b0110111;
constexpr WireData OPCODE_AUIPC = 0b0010111;
constexpr WireData OPCODE_FENCE = 0b0001111;

// Funct7s
constexpr WireData FUNCT7_POSITIVE = 0b0000000;
constexpr WireData FUNCT7_NEGATIVE = 0b0100000;

// Funct3s
constexpr WireData FUNCT3_BEQ = 0b000;
constexpr WireData FUNCT3_BNE = 0b001;
constexpr WireData FUNCT3_BLT = 0b100;
constexpr WireData FUNCT3_BGE = 0b101;
constexpr WireData FUNCT3_BLTU = 0b110;
constexpr WireData FUNCT3_BGEU = 0b111;
constexpr WireData FUNCT3_SB = 0b000;
constexpr WireData FUNCT3_SH = 0b001;
constexpr WireData FUNCT3_SW = 0b010;
constexpr WireData FUNCT3_LB = 0b000;
constexpr WireData FUNCT3_LH = 0b001;
constexpr WireData FUNCT3_LW = 0b010;
constexpr WireData FUNCT3_LBU = 0b100;
constexpr WireData FUNCT3_LHU = 0b101;
constexpr WireData FUNCT3_JALR = 0b000;
constexpr WireData FUNCT3_ADD_SUB = 0b000;
constexpr WireData FUNCT3_SLL = 0b001;
constexpr WireData FUNCT3_SLT = 0b010;
constexpr WireData FUNCT3_SLTU = 0b011;
constexpr WireData FUNCT3_XOR = 0b100;
constexpr WireData FUNCT3_SRL_SRA = 0b101;
constexpr WireData FUNCT3_OR = 0b110;
constexpr WireData FUNCT3_AND = 0b111;

// TODO: Manage ECALL operation
// TODO: Manage EBREAK operation

// ALU select that goes to ALU
// (These are arbitrary, as they are not defined by the RISC-V manual)
constexpr WireData ALU_SELECT_BEQ = 0b1010;
constexpr WireData ALU_SELECT_BNE = 0b1011;
constexpr WireData ALU_SELECT_BLT = 0b1100;
constexpr WireData ALU_SELECT_BGE = 0b1101;
constexpr WireData ALU_SELECT_BLTU = 0b1110;
constexpr WireData ALU_SELECT_BGEU = 0b1111;
constexpr WireData ALU_SELECT_SUB = 0b0001;
constexpr WireData ALU_SELECT_ADD = 0b0000;
constexpr WireData ALU_SELECT_SLL = 0b0101;
constexpr WireData ALU_SELECT_SLT = 0b1000;
constexpr WireData ALU_SELECT_SLTU = 0b1001;
constexpr WireData ALU_SELECT_XOR = 0b0010;
constexpr WireData ALU_SELECT_SRA = 0b0111;
constexpr WireData ALU_SELECT_SRL = 0b0110;
constexpr WireData ALU_SELECT_OR = 0b0011;
constexpr WireData ALU_SELECT_AND = 0b0100;
