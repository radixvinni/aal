/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "ProbingDivisionAlgorithmDecomposition.h"
#include <string>
#include <iostream>
#include <fstream>

//---------------------------------------------------------------------------

#pragma package(smart_init)



namespace AAL
{



/**********************   Factorization using msieve executable (implementation)    *********************************/
#if !defined(__GNUC__) && !defined (__APPLE_CC__)
#include <windows.h>
void  ProbingDivisionAlgorithmDecomposition::ExecProcess(char *Proc,DWORD Flags)
{
  STARTUPINFOA StInfo;
  PROCESS_INFORMATION PrInfo;
  ZeroMemory(&StInfo,sizeof(StInfo));
  StInfo.cb=sizeof(StInfo);
  if (!CreateProcessA(NULL,Proc,NULL,NULL,FALSE,Flags,
                     NULL,
                     NULL,
                     &StInfo,
                     &PrInfo))
    {
        //return ;
    }
  // Ждём, пока процесс не выполнится:
  WaitForSingleObject(PrInfo.hProcess,INFINITE);
}

//---------------------------------------------------------------------------

void  ProbingDivisionAlgorithmDecomposition::FactorIntegerUsingMsieve()
{

 //if (access("worktodo.ini", 0) != -1)
 //DeleteFileA ("worktodo.ini");
 //if (access("msieve.log", 0) != -1)
 //DeleteFileA ("msieve.log");
 FILE *f=fopen("worktodo.ini","w");
 fprintf(f,divNum.ToString().c_str());
 fclose(f);
 ExecProcess("msieve.exe -e",CREATE_NO_WINDOW);
 ParseFileAndGetResults();

}

#endif



void ProbingDivisionAlgorithmDecomposition::ParseFileAndGetResults()
{
	std::vector<std::string> res;
	std::vector<std::string> factors;

	std::ifstream ifs("msieve.log");
	std::string temp;
	while( getline( ifs, temp ) )
		res.push_back( temp );

    std::string isfinished =res[res.size()-1];
    if (isfinished.find("elapsed time")==std::string::npos) return;
    for (int j=0;j<res.size();j++)
    {
      std::string str=res[j];
       int pos=str.find("factor:");
        if (pos!=std::string::npos)
          factors.push_back(str.substr(pos+8,str.size()-pos-7));
    }

int pos=0;
while ( pos < factors.size())
{
 Integer exp(0);
 std::string tmpfactor=factors[pos];
  while ( (pos < factors.size()) && (factors[pos]==tmpfactor) )
  {
   exp=exp+1;
   pos++;
  }
    /* forming factor-exponent struction */
    Integer n(tmpfactor.c_str());
    DecompositionMember a(n ,exp);
    result.push_back(a);


}

}



/*******************************************************************************************************************/



ProbingDivisionAlgorithmDecomposition::
                          ProbingDivisionAlgorithmDecomposition(Integer number)
                                        :F(2), divNum(number)
  {
    sqrtNum.SquareRoot(divNum);
  }
  //---------------------------------------------------------------------------


  bool ProbingDivisionAlgorithmDecomposition::isFinished() {
    return divNum == 1;
  }
  //---------------------------------------------------------------------------


  void ProbingDivisionAlgorithmDecomposition::doStep() {
    if(divNum%F == 0)
    {
      Integer Int_degree(1);
      divNum = divNum/F;
      while(divNum%F == 0) {
        Int_degree++;
        divNum = divNum/F;
      }
      sqrtNum.SquareRoot(divNum);
      DecompositionMember a(F,Int_degree);
      result.push_back(a);
    }
    if(F > sqrtNum + 1) {
      F = divNum;
    } else {
      F++;
    }
  }
  //---------------------------------------------------------------------------


  DecVector ProbingDivisionAlgorithmDecomposition::getResult() {

    return result;
  }
  //---------------------------------------------------------------------------
}
