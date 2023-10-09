#pragma once

#include <iostream>

void constexpr ASSERT(bool pCondition, const char* pErrorMsg)
{
	if (!pCondition)
	{
		std::cerr << pErrorMsg << std::endl;
		throw;
	}
}

class Incoherence : public std::exception
{
public:
	Incoherence(const char* pErrorMsg);

	const char* what();

private:
	const char* mErrorMsg;
};

void ASSERT_coherence(bool pCondition, const char* pErrorMsg);
