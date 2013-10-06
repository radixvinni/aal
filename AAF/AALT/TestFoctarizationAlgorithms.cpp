/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <time.h>
#include <stdexcept>
#include <sys/timeb.h>
using namespace AAL;
TEST(FactorizationAlgorithms,ProbingDivisionAlgorithmDecomposition)
{ 


        FactorizationAlgorithms a(45);
        FactorizationAlgorithms b(11);
        AAL::Integer chislo("45",Dec);
        AAL::Integer chislo2("3");
        AAL::Integer chislo3("2");
        AAL::Integer chislo4("5");
        AAL::Integer chislo5("1");
        AAL::Integer chislo6("1");
        AAL::Integer chislo7("11");

        std::vector<DecompositionMember> vector = a.ProbingDivisionAlgorithmDecomposition();
        std::vector<DecompositionMember> vector1 = b.ProbingDivisionAlgorithmDecomposition();

        std::vector<DecompositionMember>::iterator it = vector.begin();
        AAL::Integer number(it->getNumber());
        AAL::Integer degree(it->getDegree());
        CHECK(vector.size() == 2 && number == chislo2 && degree == chislo3);
        it=it+1;
        AAL::Integer number1(it->getNumber());
        AAL::Integer degree1(it->getDegree());
        CHECK(vector.size() == 2 && number1 == chislo4 && degree1 == chislo5);

        std::vector<DecompositionMember>::iterator it1 = vector1.begin();
        AAL::Integer number2(it1->getNumber());
        AAL::Integer degree2(it1->getDegree());
        CHECK(vector1.size() == 1 && number2 == chislo7 && degree2 == chislo6);

 
}
//--------------------------------------------------------------------------------

TEST(FactorizationAlgorithms,FermaAlgorithmDecomposition)
{
  
        FactorizationAlgorithms a(45);
        AAL::Integer chislo("45",Dec);
        AAL::Integer chislo2("3");
        AAL::Integer chislo3("2");
        AAL::Integer chislo4("5");
        AAL::Integer chislo5("1");

        std::vector<DecompositionMember> vector = a.FermaAlgorithmDecomposition();

        std::vector<DecompositionMember>::iterator it = vector.begin();
        AAL::Integer number(it->getNumber());
        AAL::Integer degree(it->getDegree());
        CHECK(vector.size() == 2 && number == chislo4 && degree == chislo5);
        it=it+1;
        AAL::Integer number1(it->getNumber());
        AAL::Integer degree1(it->getDegree());
        CHECK(vector.size() == 2 && number1 == chislo2 && degree1 == chislo3);

}
//--------------------------------------------------------------------------------

TEST(FactorizationAlgorithms,P0AlgorithmDecomposition)
{     FactorizationAlgorithms a(45);
        AAL::Integer chislo("45",Dec);
        AAL::Integer chislo2("3");
        AAL::Integer chislo3("2");
        AAL::Integer chislo4("5");
        AAL::Integer chislo5("1");

        std::vector<DecompositionMember> vector = a.P0AlgorithmDecomposition();

        std::vector<DecompositionMember>::iterator it = vector.begin();
        AAL::Integer number(it->getNumber());
        AAL::Integer degree(it->getDegree());
        CHECK(vector.size() == 2 && number == chislo2 && degree == chislo3);
        it=it+1;
        AAL::Integer number1(it->getNumber());
        AAL::Integer degree1(it->getDegree());
        CHECK(vector.size() == 2 && number1 == chislo4 && degree1 == chislo5);

}
//--------------------------------------------------------------------------------

TEST(FactorizationAlgorithms,FastP0AlgorithmDecomposition)
{     FactorizationAlgorithms a(45);
        AAL::Integer chislo("45",Dec);
        AAL::Integer chislo2("3");
        AAL::Integer chislo3("2");
        AAL::Integer chislo4("5");
        AAL::Integer chislo5("1");

        std::vector<DecompositionMember> vector = a.FastP0AlgorithmDecomposition();

        std::vector<DecompositionMember>::iterator it = vector.begin();
        AAL::Integer number(it->getNumber());
        AAL::Integer degree(it->getDegree());
        CHECK(vector.size() == 2 && number == chislo2 && degree == chislo3);
        it=it+1;
        AAL::Integer number1(it->getNumber());
        AAL::Integer degree1(it->getDegree());
        CHECK(vector.size() == 2 && number1 == chislo4 && degree1 == chislo5);

}
