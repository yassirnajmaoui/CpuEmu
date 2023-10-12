#include "BitUtils.hpp"

#include "Utils.hpp"

WireData BitUtils::GenerateMask(unsigned int pMSBLimit, unsigned int pLSBLimit)
{
	return ((1 << (pMSBLimit + 1)) - 1) - ((1 << pLSBLimit) - 1);
}

WireData BitUtils::TruncateBits(WireData pCode, unsigned int pMSBLimit, unsigned int pLSBLimit)
{
	ASSERT(pMSBLimit >= pLSBLimit, "MSB Limit must be higher or equal to the LSB limit when truncating bits");

	WireData lMask = GenerateMask(pMSBLimit, pLSBLimit);
	WireData lMaskedCode = lMask & pCode;
	return lMaskedCode >> pLSBLimit;
}

void BitUtils::SetBits(WireData& pCode,
					   unsigned int pInsertionMSBLimit,
					   unsigned int pInsertionLSBLimit,
					   WireData pToInsert)
{
	ASSERT(pInsertionMSBLimit >= pInsertionLSBLimit,
		   "MSB Limit must be higher or equal to the LSB limit when truncating bits");

	// Create the insertion mask
	WireData lInsertionMask = BitUtils::GenerateMask(pInsertionMSBLimit, pInsertionLSBLimit);

	// Bitshift and truncate the insertion
	WireData lToInsert_shifted = (pToInsert << pInsertionLSBLimit) & lInsertionMask;

	// Reset the bits in the insertion area
	WireData lCode_masked = pCode & (~lInsertionMask);

	// Insert the bits
	pCode = pCode | lToInsert_shifted;
}
