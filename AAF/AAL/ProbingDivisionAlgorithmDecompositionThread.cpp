/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "ProbingDivisionAlgorithmDecompositionThread.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ProbingDivisionAlgorithmDecompositionThread::
  ProbingDivisionAlgorithmDecompositionThread
    (AAL::Integer& number)
  : mAlgorithm(number) {

}
//---------------------------------------------------------------------------
#if !defined(__GNUC__) && !defined (__APPLE_CC__)
#include <io.h>
void __fastcall ProbingDivisionAlgorithmDecompositionThread::Execute() {
  /*while(!mAlgorithm.isFinished() && !Terminated) {
    mAlgorithm.doStep();
  } */
if (access("msieve.exe", 0) == -1)
{
 factorizationDone = true;
 MessageBoxA(NULL,"Не найден файл msieve.exe!","Ошибка!",MB_OK ||MB_ICONERROR || MB_APPLMODAL);
 return;
 }

mAlgorithm.FactorIntegerUsingMsieve();


  if(Terminated) {

    //mAlgorithm.ExecProcess("TASKKILL  /F /IM notepad.exe",HIGH_PRIORITY_CLASS);
    return;
  }
  factorizationDone = true;
}
//---------------------------------------------------------------------------
#endif


std::vector<AAL::DecompositionMember>
                    ProbingDivisionAlgorithmDecompositionThread::getResult() {
  return mAlgorithm.getResult();
}
//---------------------------------------------------------------------------



