#include "Types/Node.hpp"
#include "Types/Wire.hpp"
#include "Units/Adder.hpp"
#include "Utils.hpp"

#include <iostream>
#include <memory>

int main()
{
	auto adder1 = std::make_shared<Adder>();
	auto adder2 = std::make_shared<Adder>();
	auto adder3 = std::make_shared<Adder>();
	auto adder4 = std::make_shared<Adder>();
	
	auto in1	= Node::CreateInputWire(adder1);
	auto in2	= Node::CreateInputWire(adder1);
	auto in3	= Node::CreateInputWire(adder3);
	auto in4	= Node::CreateInputWire(adder2);
	auto in5	= Node::CreateInputWire(adder2);
	
	auto inter1	= Node::ConnectNodes(adder1, adder3);
	auto inter2	= Node::ConnectNodes(adder2, adder4);
	auto inter3	= Node::ConnectNodes(adder3, adder4);

	auto out	= Node::CreateOutputWire(adder4);

	in1->SetData(1);
	in1->SetDataReady();
	in2->SetData(2);
	in2->SetDataReady();
	in3->SetData(3);
	in3->SetDataReady();
	in4->SetData(4);
	in4->SetDataReady();
	in5->SetData(5);
	in5->SetDataReady();

	std::cout << "out data: " << out->GetData() << std::endl;

	return 0;
}
