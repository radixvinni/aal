/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/Polynom.h"
#include "./AAF/AAL/PolynomGF3_m_6.h"
#include "./AAF/AAL/PolynomGF3_mY_9.h"
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include <set>
using namespace AAL;

/*
	Конструкторы класса PolynomGF2_mY_7
*/

TEST(PolynomGF3_mY_9, EmptyConstructor)
{
	PolynomGF3_mY_9 p;
	CHECK(p.isZero());
}

TEST(PolynomGF3_mY_9, CopyConstructor)
{
	PolynomGF3_mY_9 p("111", "000", "1010", "1100", "000", "1010","000","000","000","000","000","");
    PolynomGF3_mY_9 pp(p);
	CHECK(p==pp);
}

TEST(PolynomGF3_mY_9, StringConstructor)
{
	PolynomGF3_mY_9 p1("0","0","0","000","0","0","000","0","0","000","0",""), p2("","","","","","","","","","","",""), p3("10","1","0","01","1","0","01","1","0","01","0","");
    PolynomGF3 a0("10");
	CHECK(p1.isZero());
	CHECK(p2.isZero());
	CHECK(p3.getA0() == a0);
}
TEST(PolynomGF3_mY_9, Deg)
{
	PolynomGF3_mY_9 p1("0","0","0","000","0","0","000","0","0","000","0",""), p2("0","0","0","1","0","0","0","0","0","0","0",""), p3("10","1","0","01","1","0","01","1","0","01","0","");
	CHECK(p1.deg() == -1);
	CHECK(p2.deg() == 3);
	CHECK(p3.deg() == 9);
}

TEST(PolynomGF3_mY_9, Add)
{
        PolynomGF3_mY_9 a("10101","0","0","0","0","0","0","0","0","0","0","220001"),b("01","01","01","01","01","01","01","01","01","01","01","220001");
        PolynomGF3_mY_9 d("11101","01","01","01","01","01","01","01","01","01","01","220001"),c,c2,c1,c3;
//        PolynomGF2_m_4 a1("11111","11111","11111","11111","101001"),b1("11110","11110","11110","11110","101001");
//        PolynomGF2_mY_7 d1("00001","00001","00001","00001","00001","00001","00001","101001");
//        c1 = a1 + b1;
        c2 = a + b;
        CHECK(c2 == d)
//        CHECK(c3.Add(a1,b1) == d1);
        CHECK(c.Add(a,b) == d);
//        CHECK(c1 == d1)
//        b += a;
//        CHECK(b == d);
        CHECK(a + b == b + a);
        CHECK((a + b) + c == a + (b + c));

}

TEST(PolynomGF3_mY_9, Mul)
{
        PolynomGF3_m_6 a("001","010","011","100","100","100","220001"),b("000","100","000","000","000","000","220001");
        PolynomGF3_mY_9 d("000","001","010","011","100","100","100","0","0","0","0","220001"),c;
//        PolynomGF3_m_9 a1("001","010","011","100","220001"),b1("000","000","010","000","220001");
//        PolynomGF3_mY_9 d1("000","00","110","001","111","01","0","220001"),c1;
//        PolynomGF3_m_9 a2("001","010","011","100","220001"),b2("000","100","010","000","220001");
//        PolynomGF3_mY_9 d2("000","001","100","010","011","01","0","220001"),c2;
        CHECK(c.Mul(a,b) == d);
//        CHECK(c1.Mul(a1,b1) == d1);
//        CHECK(c2.Mul(a2,b2) == d2);

}
TEST(PolynomGF3_mY_9, FullMul)
{
        PolynomGF3_mY_9 a("001","010","011","100","100","100","0","0","0","0","0","220001"),b("000","100","000","000","000","000","000","000","000","000","000","220001");
        PolynomGF3_mY_9 d("000","001","010","011","100","100","100","0","0","0","0","220001"),c;
//        PolynomGF3_m_9 a1("001","010","011","100","220001"),b1("000","000","010","000","220001");
//        PolynomGF3_mY_9 d1("000","00","110","001","111","01","0","220001"),c1;
//        PolynomGF3_m_9 a2("001","010","011","100","220001"),b2("000","100","010","000","220001");
//        PolynomGF3_mY_9 d2("000","001","100","010","011","01","0","220001"),c2;
        CHECK(c.FullMul(a,b) == d);
//        CHECK(c1.Mul(a1,b1) == d1);
//        CHECK(c2.Mul(a2,b2) == d2);

}

TEST(PolynomGF3_mY_9, MonomialMul)
{
        PolynomGF3_mY_9 a("001","010","011","100","0","0","0","0","0","0","0","220001"),c;
        PolynomGF3_m_6 b("010","000","000","000","000","000","220001");
        PolynomGF3_mY_9 d("0001","001","0011","010","0","0","0","0","0","0","0","220001");
        CHECK(c.MonomialMul(a,b) == d);
}
TEST(PolynomGF3_mY_9, NormalMonomialMul)
{
        PolynomGF3_mY_9 a("001","010","011","100","101","110","0","0","0","0","0","220001"),c;
        PolynomGF3_mY_9 d("0","001","010","011","100","101","110","0","0","0","0","220001");
        CHECK(c.NormalMonomialMul(a,1) == d);
        PolynomGF3_mY_9 a1("001","010","011","100","101","0","0","0","0","0","0","220001"),c1;
        PolynomGF3_mY_9 d1("0","0","001","010","011","100","101","0","0","0","0","220001");
        CHECK(c1.NormalMonomialMul(a1,2) == d1);
}
TEST(PolynomGF3_mY_9, Div)
{
        PolynomGF3 f("220001");
        PolynomGF3_mY_9 a("100","100","000","000","100","000","000","000","000","000","000","220001"),c,r;
        PolynomGF3_mY_9 b("101","111","001","000","000","000","000","000","000","000","000","220001");
        PolynomGF3_mY_9 q("21122","22021","10012","000","000","000","000","000","000","000","000","220001");
        PolynomGF3_mY_9 remainder("011","0101","000","000","000","000","000","000","000","000","000","220001");
        CHECK(c.Div(a,b,f,&r) == q);
        CHECK(remainder == r);
}
TEST(PolynomGF3_mY_9, GCD)
{
        PolynomGF3 f("220001");
        PolynomGF3_mY_9 a("100","000","100","000","000","000","000","000","000","000","000","220001"),c,r;
        PolynomGF3_mY_9 b("100","100","000","000","000","000","000","000","000","000","000","220001");
        PolynomGF3_mY_9 q("2","000","000","000","000","000","000","000","000","000","000","220001");
        CHECK(c.GCD(a,b,f) == q);
}

 