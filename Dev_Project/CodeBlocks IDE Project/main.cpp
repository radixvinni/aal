/*
    MPEI Algebraic Abstractions Library
    Moscow Power Engineering Institute
    2007-2011

    This file contains a test module for the library

*/

#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include <exception>
#include <stdexcept>

int main()
{
	try{
		TestResult tr;
		TestRegistry::runAllTests(tr);
	}
	catch(std::exception* e)
	{
		std::cout<<(std::string("Exception:")+e->what());
	}
	return 0;
}

