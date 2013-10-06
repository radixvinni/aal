/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef ProbingDivisionAlgorithmDecompositionH
#define ProbingDivisionAlgorithmDecompositionH
//---------------------------------------------------------------------------

#include "Integer.h"
#include "DecompositionManager.h"
#if !defined(__GNUC__) && !defined (__APPLE_CC__)
#include <windows.h>
#endif

namespace AAL
{
  class ProbingDivisionAlgorithmDecomposition {
    private:
      DecVector result;
      Integer sqrtNum;
      Integer F;
      Integer divNum;
    public:

     /**********             Factorization using msieve executable       ************/
//        void ExecProcess(char *Proc, DWORD Flags);
        void FactorIntegerUsingMsieve();
        void ParseFileAndGetResults();
     /*******************************************************************************/
#if !defined(__GNUC__) && !defined (__APPLE_CC__)
		void  ProbingDivisionAlgorithmDecomposition::ExecProcess(char *Proc,DWORD Flags);
#endif
      ProbingDivisionAlgorithmDecomposition(Integer number);
      bool isFinished();
      void doStep();
      DecVector getResult();
  };
}
//---------------------------------------------------------------------------
#endif
