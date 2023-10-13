#include "BinToString.hpp"

#include <sstream>
#include <bitset>

std::string BitUtils::ToBinString(WireData pData, unsigned int pNumBits)
{
	std::stringstream ss;

#define BITSET_TO_SS(n) if(pNumBits==n) ss<<std::bitset<n>(pData);
	BITSET_TO_SS(1)
	BITSET_TO_SS(2)
	BITSET_TO_SS(3)
	BITSET_TO_SS(4)
	BITSET_TO_SS(5)
	BITSET_TO_SS(6)
	BITSET_TO_SS(7)
	BITSET_TO_SS(8)
	BITSET_TO_SS(9)
	BITSET_TO_SS(10)
	BITSET_TO_SS(11)
	BITSET_TO_SS(12)
	BITSET_TO_SS(13)
	BITSET_TO_SS(14)
	BITSET_TO_SS(15)
	BITSET_TO_SS(16)
	BITSET_TO_SS(17)
	BITSET_TO_SS(18)
	BITSET_TO_SS(19)
	BITSET_TO_SS(20)
	BITSET_TO_SS(21)
	BITSET_TO_SS(22)
	BITSET_TO_SS(23)
	BITSET_TO_SS(24)
	BITSET_TO_SS(25)
	BITSET_TO_SS(26)
	BITSET_TO_SS(27)
	BITSET_TO_SS(28)
	BITSET_TO_SS(29)
	BITSET_TO_SS(30)
	BITSET_TO_SS(31)
	BITSET_TO_SS(32)
#undef BITSET_TO_SS

	return ss.str();
}
