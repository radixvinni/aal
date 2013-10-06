/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __DECOMPOSITIONMANAGER_H__
#define __DECOMPOSITIONMANAGER_H__

#include <vector>
#include "Integer.h"
#include "Algorithms.h"
#include <stdio.h>
#include <string.h>
// ?????? ??? ???????? ????????? ??????
// (???????? ??????, ?????????? ???????? ????? ? ?.?.)
// ?????????? ? ?????????????? ????????? Singleton(??. "??????? ??????????????" GOF)
namespace AAL
{
  typedef std::vector<DecompositionMember> DecVector;

  class DecompositionManager
  {
    private:
      DecompositionManager();
    public:
  unsigned int withOneOddTwoDecompositionCompositeDegrees[129];
  unsigned int withoutOneOddTwoDecompositionCompositeDegrees[98];
  unsigned int EvenLargeTwoWithOneDecompositionCompositeDegrees[181];
  unsigned int EvenTwoWithOneDecompositionCompositeDegrees[48];
  unsigned int withOneThreeDecompositionCompositeDegrees[37];
  unsigned int withoutOneThreeDecompositionCompositeDegrees[16];
  unsigned int withOneFiveDecompositionCompositeDegrees[27];
  unsigned int withoutOneFiveDecompositionCompositeDegrees[23];
  unsigned int withOneSixDecompositionCompositeDegrees[25];
  unsigned int withoutOneSixDecompositionCompositeDegrees[10];
  unsigned int withOneSevenDecompositionCompositeDegrees[19];
  unsigned int withoutOneSevenDecompositionCompositeDegrees[10];
  unsigned int withOneOddTenDecompositionCompositeDegrees[57];
  unsigned int withoutOneOddTenDecompositionCompositeDegrees[22];
  unsigned int withOneElevenDecompositionCompositeDegrees[13];
  unsigned int withoutOneElevenDecompositionCompositeDegrees[8];
  unsigned int withOneTwelveDecompositionCompositeDegrees[13];
  unsigned int withoutOneTwelveDecompositionCompositeDegrees[11];

  unsigned int withOneOddTwoDecompositionCompositCount;
  unsigned int withoutOneOddTwoDecompositionCompositeCount;
  unsigned int EvenLargeTwoWithOneDecompositionCompositeCount;
  unsigned int EvenTwoWithOneDecompositionCompositeCount;
  unsigned int withOneThreeDecompositionCompositCount;
  unsigned int withoutOneThreeDecompositionCompositeCount;
  unsigned int withOneFiveDecompositionCompositeCount;
  unsigned int withoutOneFiveDecompositionCompositeCount;
  unsigned int withOneSixDecompositionCompositeCount;
  unsigned int withoutOneSixDecompositionCompositeCount;
  unsigned int withOneSevenDecompositionCompositeCount;
  unsigned int withoutOneSevenDecompositionCompositeCount;
  unsigned int withOneOddTenDecompositionCompositeCount;
  unsigned int withoutOneOddTenDecompositionCompositCount;
  unsigned int withOneElevenDecompositionCompositeCount;
  unsigned int withoutOneElevenDecompositionCompositeCount;
  unsigned int withOneTwelveDecompositionCompositeCount;
  unsigned int withoutOneTwelveDecompositionCompositeCount;


      static DecompositionManager& Instance();
      static void NumberGenerator(std::string addres, std::string str_addres);
      static std::string FindEqualNumberInTheDecompositionsDB(const Integer & nmbr);
      bool hevComposit(unsigned int CompositeDegrees[], uint n, uint degree);
      bool TestComposit(std::string addres, uint degree);
      DecVector getDecomposition(const Integer & number, bool *composit);
      std::vector<int> FindBase(Integer num);

    public:
      DecVector getDecompositionFromFile(std::string str_addres,uint degree);
      DecVector getCheckedDecompositionFromFile(uint degree, uint maxDegree, std::string fileName);

      DecVector getTenDegreeDecomposition(uint degree, bool withOne);
      DecVector getTwoDegreeDecomposition(uint degree, bool withOne);
      DecVector getOddTwoDegreeDecomposition(uint degree, bool withOne);
      DecVector getEvenLargeTwoDegreeWithOneDecomposition(uint degree); //2^n+1 n=4k-2 n<2400
      DecVector getEvenTwoDegreeWithOneDecomposition(uint degree);   // 2^n+1   n=4k n<=1200
      DecVector getThreeDegreeDecomposition(uint degree, bool withOne);
      DecVector getFiveDegreeDecomposition(uint degree, bool withOne);
      DecVector getSixDegreeDecomposition(uint degree, bool withOne);
      DecVector getSevenDegreeDecomposition(uint degree, bool withOne);
      DecVector getOddTenDegreeDecomposition(uint degree, bool withOne);
      DecVector getElevenDegreeDecomposition(uint degree, bool withOne);
      DecVector getTwelveDegreeDecomposition(uint degree, bool withOne);

      DecVector getSpecialTenDegreeDecomposition(uint degree);
      DecVector getSpecialTwoDegreeDecomposition(uint degree);
      DecVector getSpecialOddTwoDegreeDecomposition(uint degree);
      DecVector getSpecialEvenLargeTwoDegreeWithOneDecomposition(uint degree); //2^n+1 n=4k-2 n<2400
      DecVector getSpecialEvenTwoDegreeWithOneDecomposition(uint degree);   // 2^n+1   n=4k n<=1200
      DecVector getSpecialThreeDegreeDecomposition(uint degree);
      DecVector getSpecialFiveDegreeDecomposition(uint degree);
      DecVector getSpecialSixDegreeDecomposition(uint degree);
      DecVector getSpecialSevenDegreeDecomposition(uint degree);
      DecVector getSpecialOddTenDegreeDecomposition(uint degree);
      DecVector getSpecialElevenDegreeDecomposition(uint degree);
      DecVector getSpecialTwelveDegreeDecomposition(uint degree);


      DecVector getSpecialDecomposition(DecVector vectorWithOne, DecVector vectorWithoutOne);
      DecVector getDecompositionFromDB(Integer & number, bool *composit);
      void  logTime(FILE* f, int checkpoint) ;
      //(c) Chernysheva
      DecVector getPrimeDecomposition(uint number);

  };

};
#endif


