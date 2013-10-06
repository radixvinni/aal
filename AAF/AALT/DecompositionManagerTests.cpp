/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/Integer.h"
#include <vector>
using namespace AAL;
TEST(DecompositionManager,FindBase)
{
   DecompositionManager a();
   Integer num("81");
   std::vector<int> vector(DecompositionManager::Instance().FindBase(num));
   CHECK(vector.size() == 2 && vector[0] == 3 && vector[1] == 4);

}
//----------------------------------------------------------------------------
TEST(DecompositionManager,getDecompositionFromDB)
{
   Integer num("243");
   Integer num1("9");
   Integer num2("81");
   Integer num3("729");
   Integer num4("531441");
   Integer num5("256");

   bool r;

   std::vector<DecompositionMember> vector5(DecompositionManager::Instance().getDecompositionFromDB(num5, &r));
   std::vector<DecompositionMember>::iterator it5 = vector5.begin();
   Integer number5(it5->getNumber());
   Integer degree5(it5->getDegree());

   CHECK(vector5.size() == 3 && number5 == 3 && degree5 == 1);


   std::vector<DecompositionMember> vector4(DecompositionManager::Instance().getDecompositionFromDB(num4, &r));
   std::vector<DecompositionMember>::iterator it4 = vector4.begin();
   Integer number4(it4->getNumber());
   Integer degree4(it4->getDegree());

   CHECK(vector4.size() == 5 && number4 == 2 && degree4 == 4);

   std::vector<DecompositionMember> vector3(DecompositionManager::Instance().getDecompositionFromDB(num3, &r));
   std::vector<DecompositionMember>::iterator it3 = vector3.begin();
   Integer number3(it3->getNumber());
   Integer degree3(it3->getDegree());

   CHECK(vector3.size() == 3 && number3 == 2 && degree3 == 3);


   std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getDecompositionFromDB(num2, &r));
   std::vector<DecompositionMember>::iterator it2 = vector2.begin();
   Integer number2(it2->getNumber());
   Integer degree2(it2->getDegree());

   CHECK(vector2.size() == 2 && number2 == 2 && degree2 == 4);


   std::vector<DecompositionMember> vector(DecompositionManager::Instance().getDecompositionFromDB(num, &r));
   std::vector<DecompositionMember>::iterator it = vector.begin();
   Integer number(it->getNumber());
   Integer degree(it->getDegree());

   CHECK(vector.size() == 2 && number == 2 && degree == 1);

   std::vector<DecompositionMember> vector1(DecompositionManager::Instance().getDecompositionFromDB(num1, &r));
   std::vector<DecompositionMember>::iterator it1 = vector1.begin();
   Integer number1(it1->getNumber());
   Integer degree1(it1->getDegree());

   CHECK(vector1.size() == 1 && number1 == 2 && degree1 == 3);

}
//----------------------------------------------------------------------------

TEST(DecompositionManager,hevComposit)
{
   //DecompositionManager a();
  // a.withOneThreeDecompositionCompositeDegrees;
 //  a.withOneThreeDecompositionCompositCount;
   bool rez = DecompositionManager::Instance().hevComposit(DecompositionManager::Instance().withOneThreeDecompositionCompositeDegrees,DecompositionManager::Instance().withOneThreeDecompositionCompositCount, 409);
   CHECK(rez == true);

}
TEST(DecompositionManager,getTwelveDegreeDecomposition)
{
/////// WithOne ////////////

        Integer chislo("283463975984399894956207700312467535193660257528529638581811655239913061806669480894999522287615393",Dec);
        Integer chislo2("1");
        Integer chislo3("140897");

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getTwelveDegreeDecomposition(112, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 4 && number == chislo3 && degree == chislo2);
        it=it+3;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 4 && number1 == chislo && degree1 == chislo2);

/////// WithoutOne ////////////
        Integer num1("11");
        Integer deg1("1");
        Integer deg2("2");
        Integer num2("9143902271574719666671109149");

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getTwelveDegreeDecomposition(99, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        Integer number2(it1->getNumber());
        Integer degree2(it1->getDegree());
        CHECK(vector2.size() == 13 && number2 == num1 && degree2 == deg2);
        it1=it1+11;
        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 13 && number4 == num2 && degree4 == deg1);


}

TEST(DecompositionManager,getElevenDegreeDecomposition)
{
/////// WithOne ////////////

        Integer deg1("2");
        Integer deg2("1");
        Integer num1("2");
        Integer num2("3");
        Integer num3("3160327139569513638485230516120919120957201",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getElevenDegreeDecomposition(195, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 20 && number == num1 && degree == deg1);
        it=it+1;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 20 && number1 == num2 && degree1 == deg1);
        it=it+17 ;
        Integer number3(it->getNumber());
        Integer degree3(it->getDegree());
        CHECK(vector.size() == 20 && number3 == num3 && degree3 == deg2);

/////// WithoutOne ////////////

        Integer num4("5");
        Integer deg3("1");
        Integer deg4("3");
        Integer num5("42437717969530394595211",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getElevenDegreeDecomposition(175, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        it1++;
        Integer number2(it1->getNumber());
        Integer degree2(it1->getDegree());
        CHECK(vector2.size() == 12 && number2 == num4 && degree2 == deg4);  
        it1=it1+9;
        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 12 && number4 == num5 && degree4 == deg3);


}

TEST(DecompositionManager,getOddTenDegreeDecomposition)
{
/////// WithOne ////////////

        Integer deg1("3");
        Integer deg2("1");
        Integer num1("11");
        Integer num2("102502981431359171598893",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getOddTenDegreeDecomposition(121, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 9 && number == num1 && degree == deg1);
        it=it+7;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 9 && number1 == num2 && degree1 == deg2);

/////// WithoutOne ////////////

        Integer num4("3");
        Integer deg3("1");
        Integer deg4("7");
        Integer num5("130654897808007778425046117",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getOddTenDegreeDecomposition(243, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        Integer number2(it1->getNumber());
        Integer degree2(it1->getDegree());
        CHECK(vector2.size() == 12 && number2 == num4 && degree2 == deg4);
        it1=it1+10;
        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 12 && number4 == num5 && degree4 == deg3);


}

TEST(DecompositionManager,getSevenDegreeDecomposition)
{
/////// WithOne ////////////

        Integer deg1("2");
        Integer deg2("1");
        Integer num1("5");
        Integer num2("4170493266061",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getSevenDegreeDecomposition(214, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        it++;
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 7 && number == num1 && degree == deg1);
        it=it+3;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 7 && number1 == num2 && degree1 == deg2);

/////// WithoutOne ////////////

        Integer num4("3");
        Integer deg3("1");
        Integer deg4("6");
        Integer num5("73870787476849933393474604683663",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getSevenDegreeDecomposition(243, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        it1++;
        Integer number2(it1->getNumber());
        Integer degree2(it1->getDegree());
        CHECK(vector2.size() == 18 && number2 == num4 && degree2 == deg4);
        it1=it1+15;
        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 18 && number4 == num5 && degree4 == deg3);


}

 TEST(DecompositionManager,getSixDegreeDecomposition)
{
/////// WithOne ////////////

        Integer deg1("2");
        Integer deg2("1");
        Integer num1("7");
        Integer num2("393091150299531749364205297712116979",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getSixDegreeDecomposition(301, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 7 && number == num1 && degree == deg1);
        it=it+5;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 7 && number1 == num2 && degree1 == deg2);

/////// WithoutOne ////////////

        Integer num4("5");
        Integer deg3("1");
        Integer deg4("3");
        Integer num5("1830889518750884483049855551",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getSixDegreeDecomposition(175, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        Integer number2(it1->getNumber());
        Integer degree2(it1->getDegree());
        CHECK(vector2.size() == 16 && number2 == num4 && degree2 == deg4);
        it1=it1+15;
        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 16 && number4 == num5 && degree4 == deg3);

}

 TEST(DecompositionManager,getFiveDegreeDecomposition)
{
/////// WithOne ////////////

        Integer deg1("4");
        Integer deg2("1");
        Integer num1("3");
        Integer num2("223823944168266601",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getFiveDegreeDecomposition(135, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        it++;
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 15 && number == num1 && degree == deg1);
        it=it+13;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 15 && number1 == num2 && degree1 == deg2);

/////// WithoutOne ////////////

        Integer num4("2");
        Integer deg3("1");
        Integer deg4("2");
        Integer num6("43877290026688801",Dec);
        Integer num5("11",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getFiveDegreeDecomposition(275, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        Integer number2(it1->getNumber());
        Integer degree2(it1->getDegree());
        CHECK(vector2.size() == 20 && number2 == num4 && degree2 == deg4);
        it1++;
        Integer number3(it1->getNumber());
        Integer degree3(it1->getDegree());
        CHECK(vector2.size() == 20 && number3 == num5 && degree3 == deg4);
        it1=it1+16;

        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 20 && number4 == num6 && degree4 == deg3);

}

 TEST(DecompositionManager,getThreeDegreeDecomposition)
{
/////// WithOne ////////////

        Integer deg1("2");
        Integer deg2("1");
        Integer num1("2");
        Integer num2("7",Dec);
        Integer num3("550554229",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getThreeDegreeDecomposition(567, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 27 && number == num1 && degree == deg1);
        it++;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 27 && number1 == num2 && degree1 == deg1);
        it=it+19;
        Integer number2(it->getNumber());
        Integer degree2(it->getDegree());
        CHECK(vector.size() == 27 && number2 == num3 && degree2 == deg2);

/////// WithoutOne ////////////

        Integer num4("51457561");
        Integer deg3("1");
        Integer deg4("3");
        Integer num6("10758904556355084920587039558086313081",Dec);
        Integer num5("11",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getThreeDegreeDecomposition(385, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        it1++;
        Integer number5(it1->getNumber());
        Integer degree5(it1->getDegree());
        CHECK(vector2.size() == 16 && number5 == num5 && degree5 == deg4);
        it1=it1+8;
        Integer number3(it1->getNumber());
        Integer degree3(it1->getDegree());
        CHECK(vector2.size() == 16 && number3 == num4 && degree3 == deg3);
        it1=it1+5;

        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 16 && number4 == num6 && degree4 == deg3);

}

  TEST(DecompositionManager,getEvenTwoDegreeWithOneDecomposition)
{
/////// WithOne ////////////


        Integer deg1("2");
        Integer deg2("1");
        Integer num1("17");
        Integer num2("1580019259393",Dec);
        Integer num3("967651113494068011489137268940159136059745761",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getEvenTwoDegreeWithOneDecomposition(476));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 9 && number == num1 && degree == deg1);
        it=it+4;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 9 && number1 == num2 && degree1 == deg2);
        it=it+4;
        Integer number2(it->getNumber());
        Integer degree2(it->getDegree());
        CHECK(vector.size() == 9 && number2 == num3 && degree2 == deg2);
}

  TEST(DecompositionManager,getEvenLargeTwoDegreeWithOneDecomposition)
{
/////// WithOne ////////////

        Integer deg1("2");
        Integer deg2("1");
        Integer num1("5");
        Integer num2("18890331057055511701",Dec);
        Integer num3("2408840984250243046611173150925486103064449",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getEvenLargeTwoDegreeWithOneDecomposition(2370));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 21 && number == num1 && degree == deg1);
        it=it+9;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 21 && number1 == num2 && degree1 == deg2);
        it=it+9;
        Integer number2(it->getNumber());
        Integer degree2(it->getDegree());
        CHECK(vector.size() == 21 && number2 == num3 && degree2 == deg2);
}

 TEST(DecompositionManager,getOddTwoDegreeDecomposition)
{
/////// WithOne ////////////

        Integer deg1("4");
        Integer deg2("1");
        Integer num1("3");
        Integer num2("119827",Dec);
        Integer num3("56202143607667",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getOddTwoDegreeDecomposition(189, true));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 10 && number == num1 && degree == deg1);
        it=it+6;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 10 && number1 == num2 && degree1 == deg2);
        it=it+3;
        Integer number2(it->getNumber());
        Integer degree2(it->getDegree());
        CHECK(vector.size() == 10 && number2 == num3 && degree2 == deg2);


/////// WithoutOne ////////////

        Integer num4("7");
        Integer deg4("2");
        Integer deg3("1");
        Integer num6("29728307155963706810228435378401",Dec);
        Integer num5("649657",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getOddTwoDegreeDecomposition(315, false));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        Integer number5(it1->getNumber());
        Integer degree5(it1->getDegree());
        CHECK(vector2.size() == 18 && number5 == num4 && degree5 == deg4);
        it1=it1+14;
        Integer number3(it1->getNumber());
        Integer degree3(it1->getDegree());
        CHECK(vector2.size() == 18 && number3 == num5 && degree3 == deg3);
        it1=it1+3;

        Integer number4(it1->getNumber());
        Integer degree4(it1->getDegree());
        CHECK(vector2.size() == 18 && number4 == num6 && degree4 == deg3);

}

  TEST(DecompositionManager,getTwoDegreeDecomposition)
{
/////// WithoutOne ////////////

        Integer deg1("2");
        Integer deg2("1");
        Integer num1("7");
        Integer num2("106681",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getTwoDegreeDecomposition(105, false));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 10 && number == num1 && degree == deg1);
        it=it+7;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 10 && number1 == num2 && degree1 == deg2);


/////// WithOne ////////////

        Integer num4("3");
        Integer deg4("4");
        Integer deg3("1");
        Integer num5("385838642647891",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getTwoDegreeDecomposition(135, true));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        Integer number5(it1->getNumber());
        Integer degree5(it1->getDegree());
        CHECK(vector2.size() == 9 && number5 == num4 && degree5 == deg4);
        it1=it1+8;
        Integer number3(it1->getNumber());
        Integer degree3(it1->getDegree());
        CHECK(vector2.size() == 9 && number3 == num5 && degree3 == deg3);

}

  TEST(DecompositionManager,getTenDegreeDecomposition)
{
/////// WithoutOne ////////////



        Integer deg1("4");
        Integer deg2("1");
        Integer num1("3");
        Integer num2("4185502830133110721",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getTenDegreeDecomposition(45, false));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 9 && number == num1 && degree == deg1);
        it=it+8;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 9 && number1 == num2 && degree1 == deg2);


/////// WithOne ////////////

        Integer num4("11");
        Integer deg4("2");
        Integer deg3("1");
        Integer num5("4539402627853030477",Dec);

        std::vector<DecompositionMember> vector2(DecompositionManager::Instance().getTenDegreeDecomposition(77, true));
        std::vector<DecompositionMember>::iterator it1 = vector2.begin();
        Integer number5(it1->getNumber());
        Integer degree5(it1->getDegree());
        CHECK(vector2.size() == 11 && number5 == num4 && degree5 == deg4);
        it1=it1+9;
        Integer number3(it1->getNumber());
        Integer degree3(it1->getDegree());
        CHECK(vector2.size() == 11 && number3 == num5 && degree3 == deg3);

}
  TEST(DecompositionManager,getSpecialTwoDegreeDecomposition)
{
/////// WithoutOne ////////////



        Integer deg1("3");
        Integer deg2("1");
        Integer num1("3");
        Integer num2("18837001",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getSpecialTwoDegreeDecomposition(90));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 11 && number == num1 && degree == deg1);
        it=it+10;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 11 && number1 == num2 && degree1 == deg2);

}
//--------------------------------------------------------------------------------
  TEST(DecompositionManager,getDecomposition)
{
/////// WithoutOne ////////////


        bool rez;
        Integer deg1("65537");
        Integer deg2("1");
        Integer num1("129541188208935646963818844716591986208974410651257601",Dec);
        Integer num2("2582249878086908589655919172003011874329705792829223512830659356540647622016841194629645353280137831435903171972747493377",Dec);

        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getDecomposition(num2,&rez));
        std::vector<DecompositionMember>::iterator it = vector.begin();
        Integer number(it->getNumber());
        Integer degree(it->getDegree());
        CHECK(vector.size() == 6 && number == deg1 && degree == deg2);
        it=it+5;
        Integer number1(it->getNumber());
        Integer degree1(it->getDegree());
        CHECK(vector.size() == 6 && number1 == num1 && degree1 == deg2);

}

TEST(DecompositionManager,getPrimeDecomposition)
{
  Integer n1("2"), n2("5");
  std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(10));
  std::vector<DecompositionMember>::iterator it = vector.begin();
  Integer number(it->getNumber());
  CHECK(vector.size() == 2 && number == n1);
  it++;
  number = it->getNumber();
  CHECK(vector.size() == 2 && number == n2);

  Integer n3("2"), n4("3"), n5("569");
  std::vector<DecompositionMember> vector1(DecompositionManager::Instance().getPrimeDecomposition(6828));
  std::vector<DecompositionMember>::iterator it1 = vector1.begin();
  number = it1->getNumber();
  CHECK(vector1.size() == 3 && number == n3);
  it1++;
  number = it1->getNumber();
  CHECK(vector1.size() == 3 && number == n4);
  it1++;
  number = it1->getNumber();
  CHECK(vector1.size() == 3 && number == n5);
}
