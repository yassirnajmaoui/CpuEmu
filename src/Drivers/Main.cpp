#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Units/Operator.hpp"
#include "Utils.hpp"

#include <iostream>
#include <memory>

/* TODOs:
 * Add ALU_control (reads from Control unit and instruction (immediate) and gives an AluOP)
 * Implement the full datapath
 * Add JAL and JALR implementation (Need to add a control bit)
 */

int main()
{
	auto lANDGate = std::make_shared<Operator<2,1>>([](std::array<WireData, 2> pInputs) -> std::array<WireData,1>
	{
		return {pInputs[0] & pInputs[1]};
	});

	auto lWire0 = Node::CreateInputWire(lANDGate, 0);
	auto lWire1 = Node::CreateInputWire(lANDGate, 1);
	auto lOutWire = Node::CreateOutputWire(lANDGate, 0);

	lWire0->SetData(0b111001);
	lWire1->SetData(0b101011);
	// Expected:	0b101001
	lWire0->SetDataReady();
	lWire1->SetDataReady();
	std::cout << "Output: " << lOutWire->GetData() << std::endl;
	return 0;
}
