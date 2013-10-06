/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/PolynomGF7.h"
#include "./AAF/AAL/PolynomGF7_m_2.h"
#include "./AAF/AAL/PolynomGF7_m_14.h"
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include <set>
using namespace AAL;
TEST(PolynomGF7_m_2, Mul)
{

        PolynomGF7_m_2 a("1","0","1101"),b("0","0","1101"),c,c2;
        PolynomGF7_m_2 d("000","000","1101");

        c2 = a * b;
        CHECK(c.Mul(a,b) == d);
        CHECK(c2 == d)
//        b *= a;
//        CHECK(b == d);
        CHECK(a*b == b*a);
        CHECK((a + b)*c == (a*c + b*c));
}

 