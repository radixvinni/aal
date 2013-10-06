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

/*
	Конструкторы класса PolynomGF3_m_6
*/

TEST(PolynomGF7_m_14, EmptyConstructor)
{
	PolynomGF7_m_14 p;
	CHECK(p.isZero());
}

TEST(PolynomGF7_m_14, CopyConstructor)
{
	PolynomGF7_m_14 p("0", "1", "2", "3", "4", "5","6","0","1","2","3","4","5","6","1101");
    PolynomGF7_m_14 pp(p);
	CHECK(p==pp);
}

TEST(PolynomGF7_m_14, StringConstructor)
{
	PolynomGF7_m_14 p1("0", "0", "0", "0", "0", "0","0","0","0","0","0","0","0","0","1101"), p2("", "", "", "", "", "","","","","","","","","","1101");
	CHECK(p1.isZero());
	CHECK(p2.isZero());
}

TEST(PolynomGF7_m_14, Add)
{
        PolynomGF7_m_14 a("504", "330", "356", "134", "415", "125","616","102","624","323","625","112","661","164","1101"),b("313", "564", "434", "010", "016", "605","024","562","506","520","420","311","055","246","1101"),c,c2;
        PolynomGF7_m_14 d1("110", "124", "013", "144", "424", "023","633","664","423","143","345","423","646","333","1101");
        PolynomGF7_m_14 a1("161","444","014","460","611","414","303","663","204","545","622","524","652","113","1101"),b1("241","614","055","462","534","322","623","010","333","660","322","246","010","201","1101"),c1,c3;
        PolynomGF7_m_14 d("332","351","062","152","445","036","226","603","530","435","244","063","662","314","1101");
        c = a + b;
        CHECK(c == d1);
        c2 = a1 + b1;
        CHECK(c2 == d);
        CHECK(c3.Add(a1,b1) == d);
        CHECK(c.Add(a,b) == d1);

        b += a;
        CHECK(b == d1);
        CHECK(a + b == b + a);
        CHECK((a + b) + c == a + (b + c));
}

TEST(PolynomGF7_m_14, Mul)
{

        PolynomGF7_m_14 a("030","134","012","501","123","562","326","402","436","315","610","143","620","634","1101"),b("11","626","424","552","611","061","616","234","611","656","365","406","341","123","1101"),c,c2;
        PolynomGF7_m_14 d("231","361","656","534","122","211","253","540","115","056","114","661","040","322","1101");
        PolynomGF7_m_14 a1("0","0","0","0","0","0","0","0","1","0","0","0","0","0","1101"),b1("0","0","0","0","0","0","1","0","0","0","0","0","0","0","1101");
        PolynomGF7_m_14 d1("300","000","100","000","000","000","000","000","000","000","000","000","000","000","1101");

       // PolynomGF7_m_14 a1("0","0","0","0","0","0","0","0","0","0","0","0","1","0","1101"),b1("0","0","0","0","0","0","0","0","0","0","0","0","1","0","1101");
       // PolynomGF7_m_14 d1("0","0","0","0","0","0","0","0","0","0","3","0","1","0","1101");

        c2 = a * b;
        CHECK(c.Mul(a1,b1) == d1);
        CHECK(c2 == d)
        b *= a;
        CHECK(b == d);
        CHECK(a*b == b*a);
        CHECK((a + b)*c == (a*c + b*c));
}

TEST(PolynomGF7_m_14, Pow)
{
        PolynomGF7_m_14 a("030","134","012","501","123","562","326","402","436","315","610","143","620","634","1101"),b("11","626","424","552","611","061","616","234","611","656","365","406","341","123","1101"),c("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101"),c2("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101");
        PolynomGF7_m_14 d("220","046","252","226","406","260","650","513","365","305","605","615","212","233","1101"),c1("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101"),c3("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101");

          CHECK(c.Pow(a,AAL::Integer(2)) == d);

//          CHECK(c2.Pow(a,6) == a*a*a*a*a*a);
//          CHECK(c3.Pow(a,7) == a*a*a*a*a*a*a);
          CHECK(c1.Pow(a,AAL::Integer(14)) == a*a*a*a*a*a*a*a*a*a*a*a*a*a);

}
//--------------------------------------------------------------------------------------
/*TEST(PolynomGF3_m_6, elementOrder)
{
  PolynomGF7_m_14 u, u1, u2, a("030","134","012","501","123","562","326","402","436","315","610","143","620","634","1101"), a1,a2;
  PolynomGF7 mod("1101");
  AAL::Integer ord(1);
  int m = mod.getNumberBits() - 1;
  ord = ord.Pow(7, 14* m);
  ord = ord - 1;
//  a1.Pow(a,2);
//  a2.Pow(a,3);
  std::string s = ord.ToString();
  FactorizationAlgorithms w(ord);
  std::vector<DecompositionMember> vector = w.ProbingDivisionAlgorithmDecomposition();
  AAL::Integer t = u.elementOrder(mod, a,vector,ord);
  AAL::Integer t1 = u1.elementOrder(mod, a1.Pow(a,7),vector,ord);
  AAL::Integer t2 = u2.elementOrder(mod, a2.Pow(a,3),vector,ord);
  CHECK(t == t1);
  CHECK(t/3 == t2);
}
*/
//--------------------------------------------------------------------------------------
/*TEST(PolynomGF3_m_6, isGenerator)
{
  PolynomGF7_m_14 u, u1, u2, a("030","134","012","501","123","562","326","402","436","315","610","143","620","634","1101"), a1,a2;
  PolynomGF7 mod("1101");
  int m = mod.getNumberBits() - 1;
  AAL::Integer ord(1);
  ord = ord.Pow(3, 6* m);
  ord = ord - 1;
  a1.Pow(a,7);
  FactorizationAlgorithms w(ord);
  bool r;
  std::vector<DecompositionMember> vector = w.ProbingDivisionAlgorithmDecomposition();
  r = u.isGenerator(mod, a,vector,ord+1);
  CHECK(r == false);
  r = u1.isGenerator(mod, a1,vector,ord+1);
  CHECK(r == false);
}
*/
//--------------------------------------------------------------------------------------
TEST(PolynomGF7_m_14, Generate)
{
  PolynomGF7_m_14 u;
  PolynomGF7 mod("1101");
  u.Generate(mod);
  std::string s =   u.getA0()._a0.ToString();
  s =   u.getA0()._a1.ToString();
  s =   u.getA1()._a0.ToString();
  s =   u.getA1()._a1.ToString();
  s =   u.getA2()._a0.ToString();
  s =   u.getA2()._a1.ToString();
  s =   u.getA3()._a0.ToString();
  s =   u.getA3()._a1.ToString();
  s =   u.getA4()._a0.ToString();
  s =   u.getA4()._a1.ToString();
  s =   u.getA5()._a0.ToString();
  s =   u.getA5()._a1.ToString();
  s =   u.getA6()._a0.ToString();
  s =   u.getA6()._a1.ToString();

  CHECK(true);
}
//-------------------------------------------------------------------------------
TEST(PolynomGF7_m_14, LegendreSymbol)
{
  PolynomGF7_m_14 c1,a1("130","434","512","501","111","555","326","402","436","221","664","041","620","634","1101"),a("0","0","5","0","3","0","1","0","0","0","0","0","0","0","1101");
   PolynomGF7_m_14 one("100","000","000","000","000","000","000","000","000","000","000","000","000","000","1101");
  PolynomGF7_m_14 two("600","000","000","000","000","000","000","000","000","000","000","000","000","000","1101");
  PolynomGF7 mod("1101");
//  CHECK(c1.LegendreSymbol(a1,mod) == two);
//  CHECK(c1.LegendreSymbol(a,mod) == one);
}

//--------------------------------------------------------------------------------------
TEST(PolynomGF7_m_14, Sqrt)
{
        PolynomGF7_m_14 a("000","000","500","000","300","000","100","000","000","000","000","000","000","000","1101"),c,c2;
        PolynomGF7_m_14 d1("130","434","512","501","111","555","326","402","436","221","664","041","620","634","1101");
  PolynomGF7 mod("1101");
  int m = mod.getNumberBits() - 1;
  AAL::Integer ord(1);
  ord = ord.Pow(7, 14* m);
  ord = ord - 1;
  AAL::Integer two_pow("0"),div,copy_ord;
  copy_ord = ord;
  div = ord%2;
  ord = ord/2;
  std::string str = div.ToString();
  while(div == 0)
  {
        two_pow++;
        ord = ord/2;
        str = ord.ToString();
        div = ord%2;
        str = div.ToString();
  }
  str = two_pow.ToString();
  AAL::Integer s,T,i;
  //("25736391511831"), T("2");
  T = two_pow;
  s = ord;
  str = s.ToString();
//  c.Sqrt(a,d1,mod,s,T);
  //c2.Pow(c,2);
//  CHECK(c2.Pow(c,2) == a);
}
/*
//--------------------------------------------------------------------------------------
TEST(PolynomGF3_m_6, Inverse)
{
        PolynomGF3_m_6 a3("01100","01210","22101","11111","11002","20220","220001"),c1,c11;
        PolynomGF3_m_6 a4("02200","02120","11202","22222","22001","10110","220001");
        PolynomGF3_m_6 d1("22122","10020","22022","02222","21212","22001","220001"), d2("11211","20010","11011","01111","12121","11002","220001");
        PolynomGF3_m_6 one("1","0","0","0","0","0","220001"),m;
        PolynomGF3 module1("220001");
        PolynomGF3_m_6 a1("1","0","0","0","0","1","220001"),d11("0","1","0","0","0","0","220001");

    CHECK(c1.Inverse(a1,module1) == d11);

    std::string s = c1.getA0().ToString();
    s =  c1.getA1().ToString();
    s = c1.getA2().ToString();
    s = c1.getA3().ToString();
    s = c1.getA4().ToString();
    s = c1.getA5().ToString();
    c11 = c1.Inverse(a3,module1);
    CHECK(c11 == d1);
    s = c11.getA0().ToString();
    s = c11.getA1().ToString();
    s = c11.getA2().ToString();
    s = c11.getA3().ToString();
    s = c11.getA4().ToString();
    s = c11.getA5().ToString();
    CHECK(c1.Inverse(a4,module1)*a4 == one);
}
//----------------------------------------------------------------------------------
TEST(PolynomGF3_m_6, getRo)
{
        PolynomGF3_m_6 one("1","0","0","0","0","0","220001"),m,c,c1;
        PolynomGF3 module1("220001");
        PolynomGF3_m_6 a1("1","0","0","0","0","0","220001"),d11("0","1","0","0","0","0","220001");

//    CHECK(c1.getRo(a1,module1) == d11);

    std::string s = c1.getA0().ToString();
    s =  c1.getA1().ToString();
    s = c1.getA2().ToString();
    s = c1.getA3().ToString();
    s = c1.getA4().ToString();
    s = c1.getA5().ToString();
}
*/

 