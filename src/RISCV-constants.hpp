#pragma once

#include "Types/WireForward.hpp"

// The RISC-V Implementation chosen here is RV32I

constexpr WireData ALUOP_ADD = 0b000;
constexpr WireData ALUOP_SLL = 0b001;
constexpr WireData ALUOP_XOR = 0b100;
constexpr WireData ALUOP_SRL = 0b101;
constexpr WireData ALUOP_SRA = 0b1101;//?
constexpr WireData ALUOP_OR = 0b110;
constexpr WireData ALUOP_AND = 0b111;

constexpr WireData Opcode_R_type = 0b0110011;
constexpr WireData Opcode_S_type = 0b0100011;
constexpr WireData Opcode_J_type = 0b1101111;
constexpr WireData Opcode_B_type = 0b1100011;

// TODO: Manage ECALL operation
// TODO: Manage EBREAK operation
