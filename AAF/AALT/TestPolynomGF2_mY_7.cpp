/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/Polynom.h"
#include "./AAF/AAL/PolynomGF2_m_4.h"
#include "./AAF/AAL/PolynomGF2_mY_7.h"
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include <set>
using namespace AAL;

/*
	Конструкторы класса PolynomGF2_mY_7
*/

TEST(PolynomGF2_mY_7, EmptyConstructor)
{
	PolynomGF2_mY_7 p;
	CHECK(p.isZero());
}

TEST(PolynomGF2_mY_7, CopyConstructor)
{
	PolynomGF2_mY_7 p("111", "000", "1010", "1100", "000", "1010", "1100","");
    PolynomGF2_mY_7 pp(p);
	CHECK(p==pp);
}

TEST(PolynomGF2_mY_7, StringConstructor)
{
	PolynomGF2_mY_7 p1("0","0","0","000","0","0","000",""), p2("","","","","","","",""), p3("10","1","0","01","1","0","01","");
    Polynom a0("10");
	CHECK(p1.isZero());
	CHECK(p2.isZero());
	CHECK(p3.getA0() == a0);
}
TEST(PolynomGF2_mY_7, Deg)
{
	PolynomGF2_mY_7 p1("0","0","0","000","0","0","000",""), p2("0","0","0","1","0","0","0",""), p3("10","1","0","01","1","0","01","");
	CHECK(p1.deg() == -1);
	CHECK(p2.deg() == 3);
	CHECK(p3.deg() == 6);
}

TEST(PolynomGF2_mY_7, Add)
{
/*        PolynomGF2_m_4 a("10101","0","0","11","101001"),b("01","01","01","01","101001");
        PolynomGF2_mY_7 d("11101","01","01","10","01","01","10","101001"),c,c2,c1,c3;
        PolynomGF2_m_4 a1("11111","11111","11111","11111","101001"),b1("11110","11110","11110","11110","101001");
        PolynomGF2_mY_7 d1("00001","00001","00001","00001","00001","00001","00001","101001");
//        c1 = a1 + b1;
//        c2 = a + b;
//        CHECK(c2 == d)
        CHECK(c3.Add(a1,b1) == d1);
        CHECK(c.Add(a,b) == d);
//        CHECK(c1 == d1)
//        b += a;
//        CHECK(b == d);
//        CHECK(a + b == b + a);
//        CHECK((a + b) + c == a + (b + c));
 */
}
TEST(PolynomGF2_mY_7, Mul)
{
        PolynomGF2_m_4 a("001","010","011","100","1101"),b("000","100","000","000","1101");
        PolynomGF2_mY_7 d("000","001","010","011","100","0","0","101001"),c;
        PolynomGF2_m_4 a1("001","010","011","100","1101"),b1("000","000","010","000","1101");
        PolynomGF2_mY_7 d1("000","00","110","001","111","01","0","1101"),c1;
        PolynomGF2_m_4 a2("001","010","011","100","1101"),b2("000","100","010","000","1101");
        PolynomGF2_mY_7 d2("000","001","100","010","011","01","0","1101"),c2;

       // c2,c1,c3;
 //       c2 = a * b;
        CHECK(c.Mul(a,b) == d);
        CHECK(c1.Mul(a1,b1) == d1);
        CHECK(c2.Mul(a2,b2) == d2);

 //       CHECK(c2 == d)
 //       b *= a;
 //       CHECK(b == d);
 //       CHECK(a*b == b*a);
 //       CHECK((a + b)*c == (a*c + b*c));
}
TEST(PolynomGF2_mY_7, FullMul)
{
        PolynomGF2_mY_7 a("001","010","011","100","000","000","000","1101"),b("000","100","000","000","0","0","0","1101");
        PolynomGF2_mY_7 d("000","001","010","011","100","0","0","101001"),c;
        PolynomGF2_mY_7 a1("001","010","011","100","0","0","0","1101"),b1("000","000","010","000","0","0","0","1101");
        PolynomGF2_mY_7 d1("000","00","110","001","111","01","0","1101"),c1;
        PolynomGF2_mY_7 a2("001","010","011","100","0","0","0","1101"),b2("000","100","010","000","0","0","0","1101");
        PolynomGF2_mY_7 d2("000","001","100","010","011","01","0","1101"),c2;

       // c2,c1,c3;
 //       c2 = a * b;
        CHECK(c.FullMul(a,b) == d);
        CHECK(c1.FullMul(a1,b1) == d1);
        CHECK(c2.FullMul(a2,b2) == d2);

 //       CHECK(c2 == d)
 //       b *= a;
 //       CHECK(b == d);
 //       CHECK(a*b == b*a);
 //       CHECK((a + b)*c == (a*c + b*c));
}
TEST(PolynomGF2_mY_7, MonomialMul)
{
        PolynomGF2_mY_7 a("001","010","011","100","0","0","0","1101"),c;
        PolynomGF2_m_4 b("010","000","000","000","1101");
        PolynomGF2_mY_7 d("110","001","111","010","0","0","0","1101");
        CHECK(c.MonomialMul(a,b) == d);
}
TEST(PolynomGF2_mY_7, NormalMonomialMul)
{
        PolynomGF2_mY_7 a("001","010","011","100","101","110","0","1101"),c;
        PolynomGF2_mY_7 d("0","001","010","011","100","101","110","1101");
        CHECK(c.NormalMonomialMul(a,1) == d);
        PolynomGF2_mY_7 a1("001","010","011","100","101","0","0","1101"),c1;
        PolynomGF2_mY_7 d1("0","0","001","010","011","100","101","1101");
        CHECK(c1.NormalMonomialMul(a1,2) == d1);
}
TEST(PolynomGF2_mY_7, Div)
{
        Polynom f("1101");
        PolynomGF2_mY_7 a("100","100","000","000","100","000","000","1101"),c,r;
        PolynomGF2_mY_7 b("101","111","001","000","000","000","000","1101");
        PolynomGF2_mY_7 q("010","010","111","000","000","000","000","1101");
        PolynomGF2_mY_7 remainder("000","101","000","000","000","000","000","1101");
        CHECK(c.Div(a,b,f,&r) == q);
        CHECK(remainder == r);
}
TEST(PolynomGF2_mY_7, GCD)
{
        Polynom f("1101");
        PolynomGF2_mY_7 a("100","000","100","000","000","000","000","1101"),c,r;
        PolynomGF2_mY_7 b("100","100","000","000","000","000","000","1101");
        PolynomGF2_mY_7 q("100","100","000","000","000","000","000","1101");
//        PolynomGF2_mY_7 remainder("000","101","000","000","000","000","000","1101");
        CHECK(c.GCD(a,b,f) == q);
}

