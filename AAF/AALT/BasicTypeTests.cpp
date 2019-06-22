/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include <exception>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/BasicType.h"
using namespace AAL;

/*
	Конструкторы класса BasicType
*/
TEST(BasicType, EmptyConstructor)
{
    BasicType<int> b;
    CHECK(b.isZero());
}

TEST(BasicType, CopyConstructor)
{
    BasicType<uint> i(2342342554), ii(i);
    BasicType<char> j(23), jj(j);
    CHECK(i.getDigit(0) == ii.getDigit(0) && i.getDigit(0) == 2342342554);
    CHECK(j.getDigit(0) == jj.getDigit(0) && j.getDigit(0) == 23);
}

TEST(BasicType, NumberConstructor)
{
    BasicType<int> a(-235235234), b(235325235), c(0), d(1), e(-0);

    CHECK(a.getDigit(0) == -235235234);
    CHECK(b.getDigit(0) == 235325235);
    CHECK(c.isZero());
    CHECK(d.isOne());
    CHECK(e.isZero());
}

/*
	Методы для работы с памятью класса Integer
*/
TEST(BasicType, Relocation)
{
    BasicType<uint> i, one(1);

    i.Relocation(10);
    CHECK(i.getMaximumDigits() == 10 && i.getNumberDigits() == 0);

    try
    {
        one.Relocation(0);
        CHECK(false);
    }
    catch(Exception *E)
    {
        CHECK(true);
    }
}

TEST(BasicType, PressMemory)
{
    BasicType<uint> i;

    i.Relocation(100);
    CHECK(i.getMaximumDigits() == 100);
    i.PressMemory();
    CHECK(i.getMaximumDigits() == 0);
}

/*
	Методы акцепторы
*/
TEST(BasicType, getNumberBits)
{
    BasicType<uint> i(3252356), j;
    CHECK(i.getNumberBits() == 22);
    CHECK(j.getNumberBits() == 0);
}

TEST(BasicType, getNumberBytes)
{
    BasicType<int> i(3535), j;
    CHECK(i.getNumberBytes() == 2);
    CHECK(j.getNumberBytes() == 0);
}

TEST(BasicType, getFirstTrueBit)
{
    BasicType<ushort> i(3453);
    CHECK(i.getFirstTrueBit() == 0);
}

TEST(BasicType, getBit)
{
    BasicType<uint> i(78978945);
    CHECK(i.getBit(12));
}

TEST(BasicType, setBit)
{
    BasicType<int> i(324543);
    i.setBit(125, true);
    CHECK(i.getNumberBits() == 126 && i.getBit(125) && i.getMaximumDigits() == 4);
    i.setBit(200, false);
    CHECK(i.getNumberBits() == 126 && i.getBit(125) && i.getMaximumDigits() == 7);

}

TEST(BasicType, getDigit)
{
    BasicType<ushort> i(3985);
    CHECK(i.getDigit(0) == 3985);
}

TEST(BasicType, setDigit)
{
    BasicType<short> i(324);
    i.setDigit(5, 234);
    CHECK(i.getNumberDigits() == 6 && i.getDigit(5) == 234 && i.getMaximumDigits() == 6);
    i.setDigit(20, 0);
    CHECK(i.getNumberDigits() == 6 && i.getDigit(5) == 234 && i.getMaximumDigits() == 21);
}
