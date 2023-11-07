#include "RISCV-Instructions.hpp"
#include "Systems/RISCV.hpp"
#include "Units/Memory.hpp"
#include "Units/Registers.hpp"
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
	// ================== Instructions ==================

	std::vector<WireData> lInstructions{
		Instructions::LUI(1548, 8),
		Instructions::AUIPC(1, 9),
		// Here goes all the instructions
	};

	// ================== Memory ========================

	std::string mystr = "";
	std::vector<Byte> lMemory;
	lMemory.resize(mystr.size() + 1*sizeof(WireData));// + 1 For the null terminator
	std::memcpy(lMemory.data(), mystr.data(), mystr.size());

	// ================== Create CPU ====================

	RISCV lCPU;

	lCPU.SetInstructions(lInstructions);
	lCPU.SetDataMemory(lMemory);

	// ================== Clock CPU =====================

	while (lCPU.GetPC() < lInstructions.size() * 4)
	{
		std::cout << "==================================================================" << std::endl;
		std::cout << "PC: " << lCPU.GetPC() << "\n";
		lCPU.Clock();
	}
	std::cout << "PC: " << lCPU.GetPC() << "\n";

	// =========== Show Registers and Memory ============

	std::cout << "Registers" << std::endl;
	auto lpRegisters = lCPU.GetRegistersNode();
	for (size_t i = 0; i < lpRegisters->NumberOfRegisters; i++)
	{
		int lRegVal = static_cast<int>(lpRegisters->GetRegisterValue(i));
		std::cout << "Reg [" << i << "]:\t" << std::bitset<32>(lRegVal) << " (" << lRegVal << ")" << std::endl;
	}

	std::cout << "Memory" << std::endl;
	auto lpDataMemory = lCPU.GetDataMemoryNode();
	for (size_t i = 0; i < lpDataMemory->GetMemorySize(); i++)
	{
		WireData lMemVal = lpDataMemory->GetMemoryData(i);
		std::cout << "Mem [" << i << "]:\t" << std::bitset<8>(lMemVal) << " (" << lMemVal << ")" << std::endl;
	}

	return 0;
}
