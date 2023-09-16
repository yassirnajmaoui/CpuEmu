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
