#include <iostream>
#include "Utils.hpp"

Incoherence::Incoherence(const char* pErrorMsg) :
	mErrorMsg(pErrorMsg)
{
}

const char* Incoherence::what()
{
	return mErrorMsg;
}

void ASSERT_coherence(bool pCondition, const char* pErrorMsg )
{
	if(!pCondition)
	{
		Incoherence e(pErrorMsg);
		throw e;
	}
}

