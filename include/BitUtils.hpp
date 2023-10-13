#pragma once

#include "Types/WireForward.hpp"

namespace BitUtils
{
	// This generates a mask of all 1s from bits at position pLSBLimit to
	// pLSBLimit (inclusive)
	WireData GenerateMask(unsigned int pMSBLimit, unsigned int pLSBLimit);

	// This returns the bits in pCode from pMSBLimit to pLSBLimit (inclusive)
	WireData TruncateBits(WireData pCode, unsigned int pMSBLimit, unsigned int pLSBLimit);

	// This Sets the bits of pCode from pInsertionMSBLimit to pInsertionLSBLimit
	// (inclusive) to the value stored by the LSB bits of pToInsert
	void SetBits(WireData& pCode, unsigned int pInsertionMSBLimit, unsigned int pInsertionLSBLimit, WireData pToInsert);

	WireData SignExtend(WireData pData, unsigned int pNumBits, unsigned int pOutputNumBits);

} // namespace BitUtils
