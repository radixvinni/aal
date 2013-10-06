//---------------------------------------------------------------------------
#pragma hdrstop
//#include <Sysutils.hpp>
#include <iostream>
#include "CppUnitLite\TestHarness.h"

int main()
{
    //try{
	    TestResult tr;
	    TestRegistry::runAllTests(tr);

	    int symbol;
	    std::cin>>symbol;
	    return 0;
     /*}
     catch (Exception &exception)
     {
       std::cout<<exception.Message.c_str();
       //Application->ShowException(&exception);
     }
     catch (...)
     {
        try
        {
            //throw Exception("");
            std::cout<<"unknown exception";
        }
        catch (Exception &exception)
        {
            std::cout<<exception.Message.c_str();
           // Application->ShowException(&exception);
        }
     }
     return 0; /*  */
}
//---------------------------------------------------------------------------
