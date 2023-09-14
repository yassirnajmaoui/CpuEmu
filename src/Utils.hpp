#pragma once

#include <iostream>

typedef unsigned long long WireData;

void constexpr ASSERT(bool pCondition, const char* pErrorMessage )
{
	if(!pCondition)
	{
		std::cout << pErrorMessage << std::endl;
		throw;
	}
}
