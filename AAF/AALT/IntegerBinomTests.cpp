/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/IntegerBinom.h"
using namespace AAL;

/*
	Конструкторы класса IntegerBinom
*/
TEST(IntegerBinom, EmptyConstructor)
{
        IntegerBinom binom;
        CHECK(binom.isZero());
}

TEST(IntegerBinom, CopyConstructor)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        IntegerBinom binom(AAL::Integer("3"), AAL::Integer("5"), modPol), copybinom(binom);
        CHECK(binom == copybinom);
}

TEST(IntegerBinom, MainConstructor)
{
        try
        {
                IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("-8"),AAL::Integer("7"));
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
        try
        {
                IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("5"),AAL::Integer("8"));
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
        try
        {
                IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("5"),AAL::Integer("7"));
                IntegerBinom binom(AAL::Integer("-3"), AAL::Integer("5"), modPol), copybinom(binom);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }

        try
        {
                IntegerBinomModulePolynom modPol1(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
                IntegerBinomModulePolynom modPol2(AAL::Integer("2"),AAL::Integer("0"),AAL::Integer("7"));
                IntegerBinomModulePolynom modPol3(AAL::Integer("4"),AAL::Integer("0"),AAL::Integer("7"));
                CHECK(true);
        }
        catch(Exception *E)
        {
                CHECK(false);
        }
        try
        {
                IntegerBinomModulePolynom modPol(AAL::Integer("3"),AAL::Integer("0"),AAL::Integer("7"));
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
        try
        {
                IntegerBinomModulePolynom modPol(AAL::Integer("0"),AAL::Integer("0"),AAL::Integer("7"));
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}



//	Унарные операции класса IntegerBinom


TEST(IntegerBinom, operatorEqual)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom(AAL::Integer("3"), AAL::Integer("5"), modPol), equalbinom;

        equalbinom = binom;

        CHECK(binom == equalbinom);
}


//	Операции сложения


TEST(IntegerBinom, Add)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom1(AAL::Integer("3"), AAL::Integer("5"), modPol);
        IntegerBinom binom2(AAL::Integer("1"), AAL::Integer("4"), modPol);
        IntegerBinom rightres1(AAL::Integer("4"), AAL::Integer("2"), modPol),
        rightres2(AAL::Integer("6"), AAL::Integer("3"), modPol),
        res;

        CHECK(res.Add(binom1, binom2) == rightres1);
        CHECK(res.Add(binom1, binom1) == rightres2);
        CHECK(binom1.Add(binom1, binom1) == rightres2);        

        IntegerBinomModulePolynom otherModPol(AAL::Integer("4"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom3(AAL::Integer("1"), AAL::Integer("4"), otherModPol);

        try
        {
                res.Add(binom1, binom3);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}
TEST(IntegerBinom, Sub)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom binom1(AAL::Integer("3"), AAL::Integer("5"), modPol);
        IntegerBinom binom2(AAL::Integer("1"), AAL::Integer("4"), modPol);
        IntegerBinom rightres1(AAL::Integer("2"), AAL::Integer("1"), modPol),
        rightres2(AAL::Integer("9"), AAL::Integer("10"), modPol), res;

        CHECK(res.Sub(binom1, binom2) == rightres1);
        CHECK(res.Sub(binom2, binom1) == rightres2);
        CHECK(res.Sub(binom1, binom1).isZero());
        CHECK(binom1.Sub(binom1, binom1).isZero());        

        IntegerBinomModulePolynom otherModPol(AAL::Integer("4"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom3(AAL::Integer("1"), AAL::Integer("4"), otherModPol);

        try
        {
                res.Sub(binom1, binom3);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}
TEST(IntegerBinom, Negate)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom binom(AAL::Integer("3"), AAL::Integer("5"), modPol);
        IntegerBinom zero(AAL::Integer("0"), AAL::Integer("0"), modPol);
        IntegerBinom rightres(AAL::Integer("8"), AAL::Integer("6"), modPol), res;


        CHECK(res.Negate(binom) == rightres);
        CHECK(zero.Negate().isZero());
}

//#include <iostream>
TEST(IntegerBinom, Mul)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom1(AAL::Integer("3"), AAL::Integer("5"), modPol);
        IntegerBinom binom2(AAL::Integer("1"), AAL::Integer("4"), modPol);
        IntegerBinom rightres1(AAL::Integer("4"), AAL::Integer("6"), modPol),
        rightres2(AAL::Integer("5"), AAL::Integer("4"), modPol),
        res;

        CHECK(res.Mul(binom1, binom2) == rightres1);
        CHECK(res.Mul(binom1, binom1) == rightres2);
        CHECK(binom1.Mul(binom1, binom1) == rightres2);

        IntegerBinomModulePolynom otherModPol(AAL::Integer("4"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom3(AAL::Integer("1"), AAL::Integer("4"), otherModPol);

        try
        {
                res.Mul(binom1, binom3);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }

        /*res = binom1;
        for(int i = 0; i < 47; i++)
        {
                res *= binom1;
                std::cout << res.ToString() << std::endl;
        }*/

}
TEST(IntegerBinom, Mul2)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom binom(AAL::Integer("0"), AAL::Integer("10"), modPol);
        IntegerBinom rightres(AAL::Integer("10"), AAL::Integer("0"), modPol),
        res;

        CHECK(res.Mul(binom, binom) == rightres);
}

TEST(IntegerBinom, Pow)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom(AAL::Integer("3"), AAL::Integer("5"), modPol),
        rightres(AAL::Integer("5"), AAL::Integer("4"), modPol), res;
        AAL::Integer two("2");
        AAL::Integer negative("-10");
        AAL::Integer fieldOrdWithoutOne(modPol.getModule()*modPol.getModule());
        fieldOrdWithoutOne--;



        CHECK(res.Pow(binom, two) == rightres);
        CHECK(res.Pow(binom, fieldOrdWithoutOne).isOne());

        try
        {
                res.Pow(binom, negative);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}

TEST(IntegerBinom, Inverse)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("3"),AAL::Integer("7"));
        IntegerBinom binom(AAL::Integer("3"), AAL::Integer("5"), modPol),
        rightres(AAL::Integer("3"), AAL::Integer("3"), modPol), res;     

        CHECK(res.Inverse(binom) == rightres);
        CHECK((binom*res).isOne());
}

TEST(IntegerBinom, isGenerative)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        IntegerBinom binom1(AAL::Integer("1"), AAL::Integer("1"), modPol);
        IntegerBinom binom2(AAL::Integer("1"), AAL::Integer("3"), modPol);
        std::vector<DecompositionMember> decomposition;
        std::vector<DecompositionMember> wrongDecomposition;

        decomposition.push_back(DecompositionMember(AAL::Integer("2"), AAL::Integer("4")));
        decomposition.push_back(DecompositionMember(AAL::Integer("3"), AAL::Integer("1")));


        CHECK(!binom1.isGenerative(decomposition));
        CHECK(binom2.isGenerative(decomposition));

        try
        {
 //               binom2.isGenerative(wrongDecomposition);
 //               CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}/*
TEST(IntegerBinom, GenerateGenerative)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        IntegerBinom binom(AAL::Integer("1"), AAL::Integer("0"), modPol);
        std::vector<DecompositionMember> decomposition;

        decomposition.push_back(DecompositionMember(AAL::Integer("2"), AAL::Integer("4")));
        decomposition.push_back(DecompositionMember(AAL::Integer("3"), AAL::Integer("1")));


        binom.GenerateGenerative(decomposition);
        CHECK(binom.isGenerative(decomposition));
}
//#include <iostream>
TEST(IntegerBinom, GenerateOneRootGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        //IntegerBinom generative(AAL::Integer("1"), AAL::Integer("0"), modPol);
        IntegerBinom binom(AAL::Integer("1"), AAL::Integer("0"), modPol);
        std::vector<DecompositionMember> decomposition;

        decomposition.push_back(DecompositionMember(AAL::Integer("2"), AAL::Integer("4")));
        decomposition.push_back(DecompositionMember(AAL::Integer("3"), AAL::Integer("1")));


        //generative.GenerateGenerative(decomposition);

        AAL::Integer rootDegree("3");
        //std::vector<IntegerBinom> group(IntegerBinom::GenerateOneRootGroup(rootDegree, generative));
        //std::vector<IntegerBinom> group(IntegerBinom::GenerateOneRootGroup(rootDegree, decomposition));
        std::vector<IntegerBinom> group(binom.GenerateOneRootGroup(rootDegree, decomposition));
        CHECK(group.size() == 3);

        for(std::vector<IntegerBinom>::iterator it = group.begin();
        it != group.end(); ++it)
        {
                IntegerBinom member(*it);
                //std::cout << member.ToString() << std::endl;
                member.Pow(member, rootDegree);
                CHECK(member.isOne());
        }

        AAL::Integer badRootDegree("5");
        try
        {
                binom.GenerateOneRootGroup(badRootDegree, decomposition);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }

}  */
/*
#include <iostream>
TEST(IntegerBinom, GenerateSubGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        IntegerBinom binom(AAL::Integer("1"), AAL::Integer("0"), modPol);
        std::vector<DecompositionMember> decomposition;

        decomposition.push_back(DecompositionMember(AAL::Integer("2"), AAL::Integer("4")));
        decomposition.push_back(DecompositionMember(AAL::Integer("3"), AAL::Integer("1")));

        AAL::Integer groupOrd("16");
        std::vector<IntegerBinom> group(binom.GenerateSubGroup(groupOrd, decomposition));

        CHECK(group.size() == 16);

        /*std::cout << std::endl;
        for(std::vector<IntegerBinom>::iterator it = group.begin();
        it != group.end(); ++it)
        {
                std::cout << (*it).ToString() << std::endl;
        }*/
  /*
        AAL::Integer badGroupOrd("5");
        try
        {
                binom.GenerateOneRootGroup(badGroupOrd, decomposition);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}   */
/*#include <fstream>
TEST(IntegerBinom, GenerateFactorGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        IntegerBinom binom(AAL::Integer("1"), AAL::Integer("0"), modPol);
        std::vector<DecompositionMember> decomposition;

        decomposition.push_back(DecompositionMember(AAL::Integer("2"), AAL::Integer("4")));
        decomposition.push_back(DecompositionMember(AAL::Integer("3"), AAL::Integer("1")));

        AAL::Integer rootDegree("3");
        std::vector<IntegerBinom> oneRootGroup(binom.GenerateOneRootGroup(rootDegree, decomposition));

        AAL::Integer groupOrd("16");
        std::vector<IntegerBinom> subGroup(binom.GenerateSubGroup(groupOrd, decomposition));

        std::vector<std::vector<IntegerBinom> > subGroups;

        for(std::vector<IntegerBinom>::iterator it = oneRootGroup.begin();
        it != oneRootGroup.end(); ++it)
        {
                std::vector<IntegerBinom> group(binom.MulMultitude(subGroup, (*it)));
                subGroups.push_back(group);
        }
        std::string string (IntegerBinom::FactorToTexString(oneRootGroup, subGroups));
        std::cout << string << std::endl;

        std::ofstream out("out.txt");

        out << string;
}*/

