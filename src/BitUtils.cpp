#include "BitUtils.hpp"

#include "Utils.hpp"

WireData BitUtils::GenerateMask(unsigned int pMSBLimit, unsigned int pLSBLimit)
{
	return ((static_cast<unsigned long long>(1) << (pMSBLimit + 1)) - 1) - ((1 << pLSBLimit) - 1);
}

WireData BitUtils::TruncateBits(WireData pCode, unsigned int pMSBLimit, unsigned int pLSBLimit)
{
	ASSERT(pMSBLimit >= pLSBLimit, "MSB Limit must be higher or equal to the LSB limit when truncating bits");

	// TODO: Better way to do this: (pCode & (1<<pMSBLimits)-1) >> pLSBLimit
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

WireData BitUtils::SignExtend(WireData pData, unsigned int pInputNumBits, unsigned int pOutputNumBits)
{
	ASSERT(pInputNumBits > 0, "pInputNumBits must be a non-zero positive");
	ASSERT(pInputNumBits <= pOutputNumBits, "InputNumBits must be lower or equal to OutputNumBits");
	ASSERT(pOutputNumBits <= 32, "The max amount of bits allowed is 32");

	WireData lMask = (static_cast<unsigned long long>(1)  << pInputNumBits) - 1;
	WireData lTruncated = pData & lMask;
	WireData lOutput = lTruncated;
	if ((lTruncated >> (pInputNumBits - 1)) > 0)
	{
		lOutput |= static_cast<WireData>(-1) & (~lMask);
	}
	return lOutput;
}
