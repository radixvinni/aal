/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/PolynomGF3.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include "./AAF/AAL/PolynomGF3n6.h"
using namespace AAL;

/*
	Конструкторы класса PolynomGF3n6
*/
TEST(PolynomGF3n6, EmptyConstructor)
{
	PolynomN6 i;
	CHECK(i.isZero());
}


TEST(PolynomGF3n6, StringConstructor)
{
	PolynomGF3 module("201000000001"),moduleP("2100001");
      PolynomN6 i("1 0 0 0 0 0",module,moduleP);
	CHECK(i.isOne());
}

/*
Унарные операции
*/

TEST(PolynomGF3n6, operatorEqual)
{
      PolynomGF3 module("201000000001"),moduleP("2100001");
	PolynomN6 p1("11200002 0000102 2220111 11220102 12012012 120201",module,moduleP);
	PolynomN6 p2("2222222222 111111111111 21212102 02010100101 01002 010202001",module,moduleP);
	PolynomN6 p3("11111 0020002 000020011 11100000222 222001010121 11121211",module,moduleP);
	
      PolynomN6 pp1, pp2, pp3, pp4;

	pp1 = p1;
	pp2 = pp3 = p2;

	p2 = p1;
	p3 = pp4;

	CHECK(pp1 == p1 && !p1.isZero() && p1.ToString() == "11200002 0000102 2220111 11220102 12012012 120201");
	CHECK(pp2 == pp3 && !pp3.isZero() && pp2.ToString() == "2222222222 111111111111 21212102 02010100101 01002 010202001");
	CHECK(p2 == p1 && p2.ToString() == "11200002 0000102 2220111 11220102 12012012 120201");
	CHECK(p3.isZero());
}

/*
        Методы акцепторы
*/
TEST(PolynomGF3n6, SetData)
{
	PolynomGF3 module("201000000001"),moduleP("2100001");
        PolynomN6 i("1 0 0 0 0 0",module,moduleP),j("0 0 0 0 0 0",module,moduleP);
        PolynomN6 zero(i);
        PolynomN6 one(i);

        one.setOne();
        zero.setZero();
	CHECK(i == one);
        CHECK(j == zero);
        i.setZero();
        CHECK(i == zero);
}

TEST(PolynomGF3n6, isPrimitivity)
{
  PolynomGF3 module("201000000001"),moduleP("2100001");
  PolynomN6 p1("21012 112112 11012 121201101 221112 21021)",module,moduleP);
  PolynomN6 p2("2222 2222 22222 22 222222 2222222)",module,moduleP);
  CHECK(p1.isPrimitivity());
  CHECK(!p2.isPrimitivity());
}

/*
        Операции сравнения
*/
TEST(PolynomGF3n6, Smaller)
{
        PolynomGF3 module("201000000001"),moduleP("2100001");
	PolynomN6 i("121 021 211 211 211 211",module,moduleP);
        PolynomN6 j("111 011 111 111 111 111",module,moduleP);
   	CHECK(j < i);
}


/*
        Операция сложения
*/
TEST(PolynomGF3n6, Add)
{
        PolynomGF3 module("201000000001"),moduleP("2100001");
	PolynomGF3 i("0 0 0 0 0 0",module,moduleP);
	PolynomN6 j("221202 121012 102100 000011 222212 11111221222111",module,moduleP);
        PolynomN6 k("112101 212021 201200 000022 111121 22222112111222",module,moduleP);
        PolynomN6 zero(k);
        zero.setZero();

        PolynomGF3 iADDj("221202 121012 102100 000011 222212 11111221222111",module,moduleP);

	CHECK((i+j) == iADDj);
	CHECK(i.Add(i, j) == iADDj);
	CHECK((j + k) == zero && j.ToString() == "221202 121012 102100 000011 222212 11111221222111" && k.ToString() == "112101 212021 201200 000022 111121 22222112111222");
        CHECK(j.Add(j,k).isZero());

}


/*
	Операция умножения
*/
TEST(PolynomGF3n6, Mul)
{
        PolynomGF3 module("201000000001"),moduleP("2100001");
	PolynomN6 i("02011011 10001 02101011 121201101 22112 21021",module,moduleP);
	PolynomN6 j("0112020202 02102110111 01010101212 112211011 2211122 11021",module,moduleP);
	PolynomN6 k ("11002122101 0210220222 211101021 10001222211 10212011211 20201010212",module,moduleP);
        
	CHECK(k == i.Mul(i,j));
}

TEST(PolynomGF3n6, Inverse)
{
	PolynomGF3 module("201000000001"),moduleP("2100001");
        PolynomN6 i("02011011 10001 02101011 121201101 22112 21021",module,moduleP);
        PolynomN6 j("00000200002 22110000012 10012102102 00002101 02110120001 10121002122",module,moduleP);
        PolynomN6 temp(i);
	CHECK(j == temp.Inverse(i));
        CHECK(i == temp.Inverse(j));
        CHECK(temp.Mul(i,j).isOne());
}

TEST(PolynomGF3n6, Pow)
{
	PolynomGF3 module("201000000001"),moduleP("2100001");

        AAL::Integer iB("5");
        AAL::Integer iA("15");
        PolynomN6 i("20000202 22112211 11221122 21212121 11221122 1212121212",module,moduleP);
        PolynomN6 j("00110101 211012212 02201211221 00202012111 11111012201 112211121",module,moduleP);
        PolynomN6 k("1010122122 12001111021 102120011 0012110212 11001222212 12122021012",module,moduleP);
        PolynomN6 temp(i);

	CHECK(j == temp.Pow(i,iB));
        CHECK(k == temp.ModPow(i,iA));
}


