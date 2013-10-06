#include "TestResult.h"
#include "Failure.h"

#include <iostream>
#include <time.h>

namespace CppUnitLite
{
	void TestResult::testWasRun()
	{
		testCount++;
	}

	void TestResult::startTests () 
	{	start=clock();
	}

	void TestResult::addFailure (Failure failure) 
	{
		using namespace std;
		cout << failure << endl;
		failureCount++;
	}

	void TestResult::endTests () 
	{
		using namespace std;
		cout << testCount << " tests run" << endl;
		cout << "Time elapsed is " << (clock()-start)/CLOCKS_PER_SEC << " seconds" << endl;
		if (failureCount > 0)
			cout << "There were " << failureCount << " failures" << endl;
		else
			cout << "There were no test failures" << endl;
	}
};