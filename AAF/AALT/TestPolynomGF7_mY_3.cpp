/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/PolynomGF7.h"
#include "./AAF/AAL/PolynomGF7_m_14.h"
#include "./AAF/AAL/PolynomGF7_m_2.h"
#include "./AAF/AAL/PolynomGF7_mY_3.h"
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include <set>
using namespace AAL;

/*
	Конструкторы класса PolynomGF2_mY_7
*/

TEST(PolynomGF7_mY_3, EmptyConstructor)
{
	PolynomGF7_mY_3 p;
	CHECK(p.isZero());
}

TEST(PolynomGF7_mY_3, CopyConstructor)
{
	PolynomGF7_mY_3 p("111", "000", "101","");
    PolynomGF7_mY_3 pp(p);
	CHECK(p==pp);
}

TEST(PolynomGF7_mY_3, StringConstructor)
{
	PolynomGF7_mY_3 p1("000","000","000","1101"), p2("","","",""), p3("100","100","000","1101");
    PolynomGF7 a0("100");
    PolynomGF7 module("1101");
	CHECK(p1.isZero(module));
	CHECK(p2.isZero());
	CHECK(p3.getA0() == a0);
}
TEST(PolynomGF7_mY_3, Deg)
{
	PolynomGF7_mY_3 p1("000","000","000","1101"), p2("000","100","000","1101"), p3("100","100","100","1101");
	CHECK(p1.deg() == -1);
	CHECK(p2.deg() == 1);
	CHECK(p3.deg() == 2);
}

TEST(PolynomGF7_mY_3, Add)
{
        PolynomGF7_mY_3 a("101","0","0","1101"),b("010","010","010","1101");
        PolynomGF7_mY_3 d("111","010","010","1101"),c,c2,c1,c3;
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

/*TEST(PolynomGF7_mY_3, Mul)
{
//        PolynomGF7_m_14 a("001","010","011","100","100","100","001","010","011","100","100","100","011","100","1101"),b("000","100","000","000","000","000","000","100","000","000","000","000","000","000","1101");
        PolynomGF7_mY_3 d("000","001","010","011","100","100","100","000","000","000","000","000","001","010","011","100","100","100","000","000","000","000","000","000","000","000","1101"),c,c1;
        PolynomGF7_mY_3 d1("300","000","100","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","1101");
        PolynomGF7  a1("1","0","0","0","0","0","0","0","0","0","0","0","0","0","1101"),b1("300","0","100","0","0","0","0","0","0","0","0","0","0","0","1101");
//        PolynomGF3_m_9 a1("001","010","011","100","220001"),b1("000","000","010","000","220001");
//        PolynomGF3_mY_9 d1("000","00","110","001","111","01","0","220001"),c1;
//        PolynomGF3_m_9 a2("001","010","011","100","220001"),b2("000","100","010","000","220001");
//        PolynomGF3_mY_9 d2("000","001","100","010","011","01","0","220001"),c2;
        CHECK(c.Mul(b1,a1) == d1);
        CHECK(c.Mul(a1,b1) == c1.Mul(b1,a1));
//        CHECK(c2.Mul(a2,b2) == d2);

}
*/
TEST(PolynomGF7_mY_3, FullMul)
{
        PolynomGF7_mY_3 a("300","000","100","1101"),b("100","000","000","1101"),c1;
        PolynomGF7_mY_3 d("300","000","100","1101"),c;
        CHECK(c.FullMul(a,b) == d);
        CHECK(c1.FullMul(a,b) == c.FullMul(b,a));
}

TEST(PolynomGF7_mY_3, MonomialMul)
{
        PolynomGF7_mY_3 a("100","300","000","1101"),c;
        PolynomGF7 b("200");
        PolynomGF7_mY_3 d("200","600","000","1101");
        CHECK(c.MonomialMul(a,b) == d);
}
TEST(PolynomGF7_mY_3, NormalMonomialMul)
{
        PolynomGF7_mY_3 a("100","300","000","1101"),c;
        PolynomGF7_mY_3 d("000","100","300","1101");
        CHECK(c.NormalMonomialMul(a,1) == d);
        PolynomGF7_mY_3 a1("100","300","000","1101"),c1;
        PolynomGF7_mY_3 d1("000","000","100","1101");
        CHECK(c1.NormalMonomialMul(a1,2) == d1);
}
TEST(PolynomGF7_mY_3, Div)
{
        PolynomGF7 f("1101");
        PolynomGF7_mY_3 t,a("100","300","000","1101"),c,r;
        PolynomGF7_mY_3 b("600","000","000","1101");
        PolynomGF7_mY_3 q("200","100","000","1101");
        PolynomGF7_mY_3 remainder("000","000","000","1101");
        //;
//       CHECK(c.Div(a,b,f,&r) == q);
//        CHECK(remainder == r);
}
TEST(PolynomGF7_mY_3, GCD)
{
        PolynomGF7 f("1101");
        PolynomGF7_mY_3 t,a("100","300","000","1101"),c,r;
        PolynomGF7_mY_3 b("600","000","000","1101");
        PolynomGF7_mY_3 q("100","300","000","1101");
//        CHECK(c.GCD(b,a,f) == q);
}


 