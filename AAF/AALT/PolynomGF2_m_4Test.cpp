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
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include <set>
using namespace AAL;

/*
	Конструкторы класса PolynomGF2_m_4
*/

TEST(PolynomGF2_m_4, EmptyConstructor)
{
	PolynomGF2_m_4 p;
	CHECK(p.isZero());
}

TEST(PolynomGF2_m_4, CopyConstructor)
{
	PolynomGF2_m_4 p("111", "000", "1010", "1100","");
    PolynomGF2_m_4 pp(p);
	CHECK(p==pp);
}

TEST(PolynomGF2_m_4, StringConstructor)
{
	PolynomGF2_m_4 p1("0","0","0","000",""), p2("","","","",""), p3("10","1","0","01","");
    Polynom a0("10");
	CHECK(p1.isZero());
	CHECK(p2.isZero());
	CHECK(p3.getA0() == a0);
}
TEST(PolynomGF2_m_4, Add)
{
        PolynomGF2_m_4 a("10101","0","0","11","1101"),b("01","01","01","01","1101"),c,c2;
        PolynomGF2_m_4 d1("011","011","011","011","1101");
        PolynomGF2_m_4 a1("11111","11111","11111","11111","1101"),b1("11110","11110","11110","11110","1101"),c1,c3;
        PolynomGF2_m_4 d("1","01","01","1","1101");

        PolynomGF2_m_4 a11("111","101","101","100","1101"),b11("010","100","011","011","1101");
        PolynomGF2_m_4 d11("101","001","110","111","1101");
        PolynomGF2_m_4 a12("001","011","011","001","1101"),b12("000","111","110","110","1101");
        PolynomGF2_m_4 d12("001","100","101","111","1101");
        PolynomGF2_m_4 a13("111","001","101","011","1101"),b13("111","111","010","011","1101");
        PolynomGF2_m_4 d13("000","110","111","000","1101");
        PolynomGF2_m_4 a14("011","101","100","000","1101"),b14("011","001","110","101","1101");
        PolynomGF2_m_4 d14("000","100","010","101","1101");
        PolynomGF2_m_4 a15("001","010","111","111","1101"),b15("111","011","101","100","1101");
        PolynomGF2_m_4 d15("110","001","010","011","1101");
        PolynomGF2_m_4 a16("110","010","011","111","1101"),b16("110","101","100","101","1101");
        PolynomGF2_m_4 d16("000","111","111","010","1101");
        PolynomGF2_m_4 a17("110","010","001","100","1101"),b17("011","100","001","000","1101");
        PolynomGF2_m_4 d17("101","110","000","100","1101");
        PolynomGF2_m_4 a18("001","101","010","010","1101"),b18("011","111","001","011","1101");
        PolynomGF2_m_4 d18("010","010","011","001","1101");
        PolynomGF2_m_4 a19("101","111","001","111","1101"),b19("001","110","111","001","1101");
        PolynomGF2_m_4 d19("100","001","110","110","1101");
        PolynomGF2_m_4 a110("101","010","010","001","1101"),b110("101","100","100","000","1101");
        PolynomGF2_m_4 d110("000","110","110","001","1101");


        CHECK(c.Add(a11,b11) == d11);
        CHECK(c.Add(a12,b12) == d12);
        CHECK(c.Add(a13,b13) == d13);
        CHECK(c.Add(a14,b14) == d14);
        CHECK(c.Add(a15,b15) == d15);
        CHECK(c.Add(a16,b16) == d16);
        CHECK(c.Add(a17,b17) == d17);
        CHECK(c.Add(a18,b18) == d18);
        CHECK(c.Add(a19,b19) == d19);
        CHECK(c.Add(a110,b110) == d110);


        c1 = a1 + b1;
        c2 = a + b;
        CHECK(c2 == d)
        CHECK(c3.Add(a1,b1) == d1);
        CHECK(c.Add(a,b) == d);
        CHECK(c1 == d1)
        b += a;
        CHECK(b == d);
        CHECK(a + b == b + a);
        CHECK((a + b) + c == a + (b + c));

}
TEST(PolynomGF2_m_4, Mul)
{
        PolynomGF2_m_4 a("10101","0","0","11","1101"),b("01","01","01","01","1101"),c,c2;
        PolynomGF2_m_4 d("0","011","011","011","1101");
        PolynomGF2_m_4 a1("10101","0","0","11","1101"),b1("01","01","01","01","1101"),c1,c3;


        PolynomGF2_m_4 a11("000","010","111","110","1101"),b11("001","010","001","100","1101");
        PolynomGF2_m_4 d11("101","011","011","010","1101");
        PolynomGF2_m_4 a12("001","110","000","101","1101"),b12("110","100","110","010","1101");
        PolynomGF2_m_4 d12("001","011","100","110","1101");
        PolynomGF2_m_4 a13("111","010","100","011","1101"),b13("001","011","001","110","1101");
        PolynomGF2_m_4 d13("100","100","101","110","1101");
        PolynomGF2_m_4 a14("100","001","001","001","1101"),b14("101","000","011","001","1101");
        PolynomGF2_m_4 d14("011","010","100","101","1101");
        PolynomGF2_m_4 a15("010","000","010","011","1101"),b15("111","001","101","100","1101");
        PolynomGF2_m_4 d15("100","011","110","110","1101");
        PolynomGF2_m_4 a16("001","010","111","111","1101"),b16("101","101","001","010","1101");
        PolynomGF2_m_4 d16("100","001","000","101","1101");
        PolynomGF2_m_4 a17("110","110","110","101","1101"),b17("101","010","110","101","1101");
        PolynomGF2_m_4 d17("001","010","000","111","1101");
        PolynomGF2_m_4 a18("010","101","111","111","1101"),b18("100","011","010","001","1101");
        PolynomGF2_m_4 d18("100","101","101","000","1101");
        PolynomGF2_m_4 a19("000","111","111","010","1101"),b19("000","111","111","111","1101");
        PolynomGF2_m_4 d19("101","110","000","101","1101");
        PolynomGF2_m_4 a110("001","100","001","100","1101"),b110("111","000","010","011","1101");
        PolynomGF2_m_4 d110("001","101","110","011","1101");


        CHECK(c.Mul(a11,b11) == d11);
        CHECK(c.Mul(a12,b12) == d12);
        CHECK(c.Mul(a13,b13) == d13);
        CHECK(c.Mul(a14,b14) == d14);
        CHECK(c.Mul(a15,b15) == d15);
        CHECK(c.Mul(a16,b16) == d16);
        CHECK(c.Mul(a17,b17) == d17);
        CHECK(c.Mul(a18,b18) == d18);
        CHECK(c.Mul(a19,b19) == d19);
        CHECK(c.Mul(a110,b110) == d110);





        c2 = a * b;
        CHECK(c.Mul(a,b) == d);
        CHECK(c2 == d)
        b *= a;
        CHECK(b == d);
        CHECK(a*b == b*a);
        CHECK((a + b)*c == (a*c + b*c));

}
TEST(PolynomGF2_m_4, Pow)
{
	PolynomGF2_m_4 a("11111","11111","11111","11111","1101"),d("0","001","0","001","1101"),c;
	PolynomGF2_m_4 a1("1","0","0","0","0");


        PolynomGF2_m_4 a11("100","101","010","011","1101");
        PolynomGF2_m_4 d11("110","111","011","111","1101");
        PolynomGF2_m_4 a12("111","111","011","001","1101");
        PolynomGF2_m_4 d12("111","100","000","110","1101");
        PolynomGF2_m_4 a13("101","000","111","010","1101");
        PolynomGF2_m_4 d13("111","101","000","110","1101");
        PolynomGF2_m_4 a14("101","101","011","110","1101");
        PolynomGF2_m_4 d14("101","101","100","101","1101");
        PolynomGF2_m_4 a15("101","001","010","010","1101");
        PolynomGF2_m_4 d15("001","001","100","110","1101");
        PolynomGF2_m_4 a16("011","001","000","110","1101");
        PolynomGF2_m_4 d16("100","001","010","001","1101");
        PolynomGF2_m_4 a17("110","101","001","111","1101");
        PolynomGF2_m_4 d17("000","010","110","111","1101");
        PolynomGF2_m_4 a18("011","001","001","010","1101");
        PolynomGF2_m_4 d18("100","010","101","010","1101");
        PolynomGF2_m_4 a19("100","010","100","111","1101");
        PolynomGF2_m_4 d19("011","000","010","100","1101");
        PolynomGF2_m_4 a110("100","100","110","010","1101");
        PolynomGF2_m_4 d110("010","000","000","011","1101");

    CHECK(c.Pow(a11,1050) == d11);
    CHECK(c.Pow(a12,698) == d12);
    CHECK(c.Pow(a13,530) == d13);
    CHECK(c.Pow(a14,806) == d14);
    CHECK(c.Pow(a15,423) == d15);
    CHECK(c.Pow(a16,866) == d16);
    CHECK(c.Pow(a17,564) == d17);
    CHECK(c.Pow(a18,965) == d18);
    CHECK(c.Pow(a19,660) == d19);
    CHECK(c.Pow(a110,1219) == d110);


    PolynomGF2_m_4  e("0","011","0","0","1101"),r;
    r.Pow(e,4094);
    std::string s = r.getA0().ToString();
    s = r.getA1().ToString();
    s = r.getA2().ToString();
    s = r.getA3().ToString();
    CHECK(c.Pow(a,2) == d);
    CHECK(c.Pow(a,1) == a);
    CHECK(c.Pow(a,0) == a1);
}
TEST(PolynomGF2_m_4, Squar)
{
	PolynomGF2_m_4 a("11111","11111","11111","11111","1101"),d("0","001","0","001","1101"),c;
    PolynomGF2_m_4 a1("1","0","0","0","0");

        PolynomGF2_m_4 a11("111","000","110","001","1101");
        PolynomGF2_m_4 d11("011","101","011","011","1101");
        PolynomGF2_m_4 a12("010","001","101","111","1101");
        PolynomGF2_m_4 d12("110","111","101","110","1101");
        PolynomGF2_m_4 a13("100","000","010","100","1101");
        PolynomGF2_m_4 d13("101","001","100","100","1101");
        PolynomGF2_m_4 a14("000","100","000","101","1101");
        PolynomGF2_m_4 d14("000","000","011","111","1101");
        PolynomGF2_m_4 a15("000","100","101","100","1101");
        PolynomGF2_m_4 d15("111","111","000","100","1101");
        PolynomGF2_m_4 a16("101","011","010","001","1101");
        PolynomGF2_m_4 d16("110","001","001","011","1101");
        PolynomGF2_m_4 a17("111","001","011","010","1101");
        PolynomGF2_m_4 d17("100","010","010","001","1101");
        PolynomGF2_m_4 a18("101","110","101","011","1101");
        PolynomGF2_m_4 d18("000","111","111","010","1101");
        PolynomGF2_m_4 a19("000","111","000","010","1101");
        PolynomGF2_m_4 d19("000","000","111","001","1101");
        PolynomGF2_m_4 a110("000","101","010","000","1101");
        PolynomGF2_m_4 d110("001","001","111","000","1101");


        CHECK(c.Square(a11) == d11);
        CHECK(c.Square(a12) == d12);
        CHECK(c.Square(a13) == d13);
        CHECK(c.Square(a14) == d14);
        CHECK(c.Square(a15) == d15);
        CHECK(c.Square(a16) == d16);
        CHECK(c.Square(a17) == d17);
        CHECK(c.Square(a18) == d18);
        CHECK(c.Square(a19) == d19);
        CHECK(c.Square(a110) == d110);



    CHECK(c.Square(a) == d);
    CHECK(c.Square(a) == a*a);
}
TEST(PolynomGF2_m_4, Sqrt)
{
	PolynomGF2_m_4 a("110","100","000","000","1101"),c,c11("010","000","100","000","1101");
    PolynomGF2_m_4 a1("101","000","100","000","1101"),c1,c12("010","100","000","000","1101");
    Polynom module("1101");

        PolynomGF2_m_4 a11("001","111","010","101","1101");
        PolynomGF2_m_4 d11("111","101","101","110","1101");
        PolynomGF2_m_4 a12("010","110","100","010","1101");
        PolynomGF2_m_4 d12("100","111","111","011","1101");
        PolynomGF2_m_4 a13("100","100","110","010","1101");
        PolynomGF2_m_4 d13("000","100","100","011","1101");
        PolynomGF2_m_4 a14("001","100","011","010","1101");
        PolynomGF2_m_4 d14("110","010","100","011","1101");
        PolynomGF2_m_4 a15("100","001","110","101","1101");
        PolynomGF2_m_4 d15("110","001","010","110","1101");
        PolynomGF2_m_4 a16("011","001","011","010","1101");
        PolynomGF2_m_4 d16("011","010","010","011","1101");
        PolynomGF2_m_4 a17("110","101","101","001","1101");
        PolynomGF2_m_4 d17("001","100","110","010","1101");
        PolynomGF2_m_4 a18("010","000","010","100","1101");
        PolynomGF2_m_4 d18("011","111","000","100","1101");
        PolynomGF2_m_4 a19("111","110","111","100","1101");
        PolynomGF2_m_4 d19("010","001","111","100","1101");
        PolynomGF2_m_4 a110("000","001","011","101","1101");
        PolynomGF2_m_4 d110("010","111","010","110","1101");

   CHECK(c.Sqrt(a11,module) == d11);
   CHECK(c.Sqrt(a12,module) == d12);
   CHECK(c.Sqrt(a13,module) == d13);
   CHECK(c.Sqrt(a14,module) == d14);
   CHECK(c.Sqrt(a15,module) == d15);
   CHECK(c.Sqrt(a16,module) == d16);
   CHECK(c.Sqrt(a17,module) == d17);
   CHECK(c.Sqrt(a18,module) == d18);
   CHECK(c.Sqrt(a19,module) == d19);
   CHECK(c.Sqrt(a110,module) == d110);

    c.Sqrt(a,module);
    c1.Sqrt(a1,module);
    CHECK(c1*c1 == a1);
    CHECK(c*c == a);}
//--------------------------------------------------------------------------------------
TEST(PolynomGF2_m_4, elementOrder)
{
  PolynomGF2_m_4 u, u1, u2, a("11","1","1","1","1101"), a1,a2;
  PolynomGF2_m_4  a11("000","111","100","111","1101");
  PolynomGF2_m_4  a22("001","001","110","111","1101");
  PolynomGF2_m_4  a3("111","000","000","001","1101");
  PolynomGF2_m_4  a4("010","001","010","011","1101");
  PolynomGF2_m_4  a5("111","001","010","010","1101");
  PolynomGF2_m_4  a6("000","011","011","010","1101");
  PolynomGF2_m_4  a7("110","110","110","011","1101");
  PolynomGF2_m_4  a8("110","011","000","100","1101");
  PolynomGF2_m_4  a9("010","001","111","000","1101");
  PolynomGF2_m_4  a10("011","001","100","011","1101");
  PolynomGF2_m_4  a111("100","001","111","111","1101");
  PolynomGF2_m_4  a12("111","100","011","010","1101");
  PolynomGF2_m_4  a13("000","100","101","000","1101");
  PolynomGF2_m_4  a14("110","011","001","101","1101");
  PolynomGF2_m_4  a15("101","111","001","110","1101");
  PolynomGF2_m_4  a16("111","101","100","111","1101");
  PolynomGF2_m_4  a17("000","001","001","101","1101");
  PolynomGF2_m_4  a18("011","101","001","111","1101");
  PolynomGF2_m_4  a19("100","100","001","001","1101");
  PolynomGF2_m_4  a20("101","100","010","101","1101");

  Polynom mod("1101");
  AAL::Integer ord(1);
  int m = mod.getNumberBits() - 1;
  ord = ord.Pow(2, 4* m);
  ord = ord - 1;
//  a1.Pow(a,2);
//  a2.Pow(a,3);
  std::string s = ord.ToString();
  FactorizationAlgorithms w(ord);
  std::vector<DecompositionMember> vector = w.ProbingDivisionAlgorithmDecomposition();
  AAL::Integer t = u.elementOrder(mod, a,vector,ord);
  AAL::Integer t1 = u1.elementOrder(mod, a1.Pow(a,2),vector,ord);
  AAL::Integer t2 = u2.elementOrder(mod, a2.Pow(a,3),vector,ord);

  CHECK(u.elementOrder(mod, a11,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a22,vector,ord) == 117);
  CHECK(u.elementOrder(mod, a3,vector,ord) == 819);
  CHECK(u.elementOrder(mod, a4,vector,ord) == 819);
  CHECK(u.elementOrder(mod, a5,vector,ord) == 819);
  CHECK(u.elementOrder(mod, a6,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a7,vector,ord) == 585);
  CHECK(u.elementOrder(mod, a8,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a9,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a10,vector,ord) == 585);
  CHECK(u.elementOrder(mod, a111,vector,ord) == 819);
  CHECK(u.elementOrder(mod, a12,vector,ord) == 819);
  CHECK(u.elementOrder(mod, a13,vector,ord) == 819);
  CHECK(u.elementOrder(mod, a14,vector,ord) == 1365);
  CHECK(u.elementOrder(mod, a15,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a16,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a17,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a18,vector,ord) == 455);
  CHECK(u.elementOrder(mod, a19,vector,ord) == 4095);
  CHECK(u.elementOrder(mod, a20,vector,ord) == 585);


  CHECK(t == t1);
  CHECK(t/3 == t2);
}
//--------------------------------------------------------------------------------------
TEST(PolynomGF2_m_4, isGenerator)
{
  PolynomGF2_m_4 u, u1,a01, a("11","0","0","1","1101");
  Polynom mod("1101");

  PolynomGF2_m_4  a1("010","011","101","101","1101");
  PolynomGF2_m_4  a2("101","111","110","100","1101");
  PolynomGF2_m_4  a3("000","101","011","101","1101");
  PolynomGF2_m_4  a4("001","111","000","010","1101");
  PolynomGF2_m_4  a5("011","011","110","000","1101");
  PolynomGF2_m_4  a6("011","111","001","111","1101");
  PolynomGF2_m_4  a7("011","111","111","110","1101");
  PolynomGF2_m_4  a8("011","110","100","001","1101");
  PolynomGF2_m_4  a9("010","111","110","000","1101");
  PolynomGF2_m_4  a10("011","000","111","111","1101");
  PolynomGF2_m_4  a11("001","011","011","010","1101");
  PolynomGF2_m_4  a12("100","111","000","011","1101");
  PolynomGF2_m_4  a13("001","010","100","001","1101");
  PolynomGF2_m_4  a14("000","110","001","001","1101");
  PolynomGF2_m_4  a15("011","100","100","100","1101");
  PolynomGF2_m_4  a16("001","100","011","011","1101");
  PolynomGF2_m_4  a17("110","110","100","111","1101");
  PolynomGF2_m_4  a18("011","010","000","101","1101");
  PolynomGF2_m_4  a19("100","101","110","000","1101");
  PolynomGF2_m_4  a20("010","010","011","111","1101");

  int m = mod.getNumberBits() - 1;
  AAL::Integer ord(1);
  ord = ord.Pow(2, 4* m);
  ord = ord - 1;
  a1.Pow(a,3);
  FactorizationAlgorithms w(ord);
  bool r;
  std::vector<DecompositionMember> vector = w.ProbingDivisionAlgorithmDecomposition();

  r = u.isGenerator(mod, a1,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a2,vector,ord+1);
  CHECK(r == true);
  r = u.isGenerator(mod, a3,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a4,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a5,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a6,vector,ord+1);
  CHECK(r == true);
  r = u.isGenerator(mod, a7,vector,ord+1);
  CHECK(r == true);
  r = u.isGenerator(mod, a8,vector,ord+1);
  CHECK(r == true);
  r = u.isGenerator(mod, a9,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a10,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a11,vector,ord+1);
  CHECK(r == true);
  r = u.isGenerator(mod, a12,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a13,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a14,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a15,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a16,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a17,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a18,vector,ord+1);
  CHECK(r == true);
  r = u.isGenerator(mod, a19,vector,ord+1);
  CHECK(r == false);
  r = u.isGenerator(mod, a20,vector,ord+1);
  CHECK(r == false);

}

//--------------------------------------------------------------------------------------
TEST(PolynomGF2_m_4, Inverse)
{
/*       
		PolynomGF2_m_4 a("100","011","100","010","1101"),d("101","001","100","100","1101"),c;
        PolynomGF2_m_4 a2("000","111","001","111","1101"),d2("011","001","111","001","1101"),c2;
        PolynomGF2_m_4 a3("111","111","111","011","1101"),d3("110","111","101","001","1101"),c3;
        PolynomGF2_m_4 a4("100","110","101","011","1101"),d4("010","001","000","010","1101"),c4;
        PolynomGF2_m_4 a5("011","100","000","000","1101"),d5("010","111","010","011","1101"),c5;
        PolynomGF2_m_4 a6("001","110","111","111","1101"),d6("101","001","011","010","1101"),c6;


        PolynomGF2_m_4 a11("11110","10100","01101","00111","101001"),d11("00010","10111","01110","01010","101001"),c11;
        PolynomGF2_m_4 a22("10100","01110","00111","10011","101001"),d22("11110","01010","11010","10110","101001"),c22;
        PolynomGF2_m_4 a33("01011","00010","01000","01111","101001"),d33("11110","10111","11011","01001","101001"),c33;
        PolynomGF2_m_4 a44("00111","10110","11011","01011","101001"),d44("10111","00101","00100","10101","101001"),c44;
        PolynomGF2_m_4 a55("01000","10110","11011","01011","101001"),d55("11","0001","00001","01101","101001"),c55;
        PolynomGF2_m_4 a66("00000","01101","00010","10110","101001"),d66("00111","00100","10100","11001","101001"),c66;



    PolynomGF2_m_4 a1("0","011","0","0","1101"),d1("11","0","0","11","1101"),c1;
    PolynomGF2_m_4 one("1","0","0","0","1101"),m;
    Polynom module("101001");

    CHECK(c11.Inverse(a11,module) == d11);
    CHECK(c22.Inverse(a22,module) == d22);
    std::string s = c22.getA0().ToString();
    s = c22.getA1().ToString();
    s = c22.getA2().ToString();
    s = c22.getA3().ToString();
    CHECK(c33.Inverse(a33,module) == d33);
    CHECK(c44.Inverse(a44,module) == d44);
    s = c44.getA0().ToString();
    s = c44.getA1().ToString();
    s = c44.getA2().ToString();
    s = c44.getA3().ToString();
    CHECK(c55.Inverse(a55,module) == d55);
    s = c55.getA0().ToString();
    s = c55.getA1().ToString();
    s = c55.getA2().ToString();
    s = c55.getA3().ToString();
    CHECK(c66.Inverse(a66,module) == d66);
    s = c66.getA0().ToString();
    s = c66.getA1().ToString();
    s = c66.getA2().ToString();
    s = c66.getA3().ToString();

    CHECK(c11.Inverse(a11,module)*a11 == one);
    m = c22.Inverse(a22,module)*a22;
    CHECK(c22.Inverse(a22,module)*a22 == one);
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c33.Inverse(a33,module)*a33 == one);
     m = c33.Inverse(a33,module)*a33;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c44.Inverse(a44,module)*a44 == one);
     m = c44.Inverse(a44,module)*a44;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c55.Inverse(a55,module)*a55 == one);
     m = c55.Inverse(a55,module)*a55;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c66.Inverse(a66,module)*a66 == one);
     m = c66.Inverse(a66,module)*a66;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();

     Polynom module1("1101");
    CHECK(c.Inverse(a,module1) == d);
    CHECK(c2.Inverse(a2,module1) == d2);
    s = c2.getA0().ToString();
    s = c2.getA1().ToString();
    s = c2.getA2().ToString();
    s = c2.getA3().ToString();
    CHECK(c3.Inverse(a3,module1) == d3);
    CHECK(c4.Inverse(a4,module1) == d4);
    s = c4.getA0().ToString();
    s = c4.getA1().ToString();
    s = c4.getA2().ToString();
    s = c4.getA3().ToString();
    CHECK(c5.Inverse(a5,module1) == d5);
    s = c5.getA0().ToString();
    s = c5.getA1().ToString();
    s = c5.getA2().ToString();
    s = c5.getA3().ToString();
    CHECK(c6.Inverse(a6,module1) == d6);
    s = c6.getA0().ToString();
    s = c6.getA1().ToString();
    s = c6.getA2().ToString();
    s = c6.getA3().ToString();

    CHECK(c.Inverse(a,module1)*a == one);
    m = c2.Inverse(a2,module1)*a2;
    CHECK(c2.Inverse(a2,module1)*a2 == one);
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c3.Inverse(a3,module1)*a3 == one);
     m = c3.Inverse(a3,module1)*a3;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c4.Inverse(a4,module1)*a4 == one);
     m = c4.Inverse(a4,module1)*a4;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c5.Inverse(a5,module1)*a5 == one);
     m = c5.Inverse(a5,module1)*a5;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();
    CHECK(c6.Inverse(a6,module1)*a6 == one);
     m = c6.Inverse(a6,module1)*a6;
    s = m.getA0().ToString();
    s = m.getA1().ToString();
    s = m.getA2().ToString();
    s = m.getA3().ToString();


    CHECK(c1.Inverse(a1,module1) == d1);
    CHECK(c1.Inverse(a1,module1)*a1 == one);
    Polynom module2("1101");
    PolynomGF2_m_4 a21("100","001","110","001","1101"),d21("111","100","100","111","1101");
    PolynomGF2_m_4 a222("101","101","011","001","1101"),d222("101","011","110","001","1101");
    PolynomGF2_m_4 a23("101","110","010","010","1101"),d23("101","001","101","101","1101");
    PolynomGF2_m_4 a24("111","000","000","001","1101"),d24("101","110","011","111","1101");
    PolynomGF2_m_4 a25("011","101","101","111","1101"),d25("010","000","101","010","1101");
    PolynomGF2_m_4 a26("101","010","111","001","1101"),d26("110","000","000","111","1101");
    PolynomGF2_m_4 a27("001","110","001","001","1101"),d27("001","010","110","100","1101");
    PolynomGF2_m_4 a28("001","001","010","101","1101"),d28("001","011","001","110","1101");
    PolynomGF2_m_4 a29("000","100","100","001","1101"),d29("110","000","011","111","1101");
    PolynomGF2_m_4 a210("110","100","110","111","1101"),d210("111","111","110","101","1101");

    CHECK(c1.Inverse(a21,module2) == d21);
    CHECK(c1.Inverse(a222,module2) == d222);
    CHECK(c1.Inverse(a23,module2) == d23);
    CHECK(c1.Inverse(a24,module2) == d24);
    CHECK(c1.Inverse(a25,module2) == d25);
    CHECK(c1.Inverse(a26,module2) == d26);
    CHECK(c1.Inverse(a27,module2) == d27);
    CHECK(c1.Inverse(a28,module2) == d28);
    CHECK(c1.Inverse(a29,module2) == d29);
    CHECK(c1.Inverse(a210,module2) == d210); /* */
}

//--------------------------------------------------------------------------------------


 