/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef ProbingDivisionAlgorithmDecompositionThreadH
#define ProbingDivisionAlgorithmDecompositionThreadH
//---------------------------------------------------------------------------

#include "ProbingDivisionAlgorithmDecomposition.h"


class ProbingDivisionAlgorithmDecompositionThread {
  private:
	bool Terminated;
    AAL::ProbingDivisionAlgorithmDecomposition mAlgorithm;
  public:
#if !defined(__GNUC__) && !defined (__APPLE_CC__)
	  void __fastcall ProbingDivisionAlgorithmDecompositionThread::Execute();
#endif
    bool factorizationDone;
    ProbingDivisionAlgorithmDecompositionThread(AAL::Integer& number);
//    virtual void __fastcall Execute();
    std::vector<AAL::DecompositionMember> getResult();
};
#endif
