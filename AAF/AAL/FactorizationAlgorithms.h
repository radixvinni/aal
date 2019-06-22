/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __FACTORIZATIONALGORITHMS_H__
#define __FACTORIZATIONALGORITHMS_H__

#include <vector>
#include "Integer.h"
#include "Algorithms.h"
#include "DecompositionManager.h"


// Достоверные тесты простоты
namespace AAL
{
    class FactorizationAlgorithms
  { private: Integer number;
    public:
      FactorizationAlgorithms(Integer number);
    public:           //Тест простоты чисел мерсена

      DecVector MsieveDecomposition();
      DecVector ProbingDivisionAlgorithmDecomposition();
      Integer FermaAlgorithm(Integer number);
      DecVector FermaAlgorithmDecomposition();
      DecVector P0AlgorithmDecomposition();
      DecVector FastP0AlgorithmDecomposition();

  };
};
#endif
