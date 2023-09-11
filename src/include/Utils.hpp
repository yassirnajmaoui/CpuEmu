#pragma once

#include <iostream>

void constexpr ASSERT(bool pCondition, const char* pErrorMessage )
{
	if(!pCondition)
	{
		std::cout << pErrorMessage << std::endl;
		throw;
	}
}
