/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/PrimeTester.h"
#include "./AAF/AAL/Integer.h"
#include <vector>
#include <iostream>
using namespace AAL;
TEST(PrimeTester,TestLukaLemera)//mersen number (2^s)-1
{
        bool  result,result2,result3,result4,result5;
        AAL::Integer num("17179869183");
        AAL::Integer num1("200867255532373784442745261542645325315275374222849104412671");
        AAL::Integer num2("170141183460469231731687303715884105727");
        result = PrimeTester(7).TestLukaLemera(3);
        result2 = PrimeTester(15).TestLukaLemera(4);
        result3 = PrimeTester(num).TestLukaLemera(34);
        result4 = PrimeTester(num1).TestLukaLemera(197);
        result5 = PrimeTester(num2).TestLukaLemera(127);

        CHECK(result == true);
        CHECK(result2 == false);
        CHECK(result3 == false);
        CHECK(result4 == false);
        CHECK(result5 == true);

}
TEST(PrimeTests,ModifiedTestLuka)
{
        bool test;
        bool result,result1,result2;
        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getDecomposition(AAL::Integer(6), &test));
        std::vector<DecompositionMember> vector1(DecompositionManager::Instance().getDecomposition(AAL::Integer(26), &test));
        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getDecomposition(AAL::Integer("161052"), &test));

        result = PrimeTester(7).ModifiedTestLuka(vector);
        result1 = PrimeTester(27).ModifiedTestLuka(vector1);
        result2 = PrimeTester(AAL::Integer("161053")).ModifiedTestLuka(vector2);
        CHECK(result == true);
        CHECK(result1 == false);
        CHECK(result2 == true);

}
//------------------------------------------------------------------------------
TEST(PrimeTests,TestPoklingtona)
{       bool test;
        bool result,result1,result2;
        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getDecomposition(AAL::Integer(10), &test));
        std::vector<DecompositionMember> vector1(DecompositionManager::Instance().getDecomposition(AAL::Integer(50), &test));
        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getDecomposition(AAL::Integer("161052"), &test));

        result = PrimeTester(11).TestPoklingtona(vector);
        CHECK(result == true);
        result2 = PrimeTester(AAL::Integer("161053")).TestPoklingtona(vector2);
        CHECK(result2 == true);

        try
        {
                result1 = PrimeTester(51).TestPoklingtona(vector1);
                CHECK(true);
        }
        catch(Exception *E)
        {
            CHECK(true);
         }

 }


