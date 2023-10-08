#include "Units/Relay.hpp"
#include "Types/Wire.hpp"

Relay::Relay(std::string pName) :
	Node(2, 1, pName)
{

}

void Relay::ProcessInternal()
{
	SetWireData(OutputIndex, GetWireData(InputIndex));
}
