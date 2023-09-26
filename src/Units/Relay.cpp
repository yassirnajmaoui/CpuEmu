#include "Units/Relay.hpp"
#include "Types/Wire.hpp"

Relay::Relay() :
	Node(2,1)
{

}

void Relay::ProcessInternal()
{
	SetWireData(OutputIndex, GetWireData(InputIndex));
}
