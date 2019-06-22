/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __PRIMETESTS_H__
#define __PRIMETESTS_H__

#include <vector>
#include "Integer.h"
#include "Algorithms.h"
#include "./AAF/AAL/DecompositionManager.h"

// Достоверные тесты простоты
namespace AAL
{
    class PrimeTester
  {
   private: Integer Mersen_Number;
    public:
      PrimeTester(Integer number);
    public:           //Тест простоты чисел мерсена

      bool TestLukaLemera(Integer degree);
      bool ModifiedTestLuka(std::vector<DecompositionMember> vector);
      bool TestPoklingtona(std::vector<DecompositionMember> vector);
  };
};
#endif
