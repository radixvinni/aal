// DevProject.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <conio.h>
#include "./CppUnitLite/TestHarness.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TestResult tr;
	TestRegistry::runAllTests(tr);

	int symbol;
	getch();
	return 0;
}

