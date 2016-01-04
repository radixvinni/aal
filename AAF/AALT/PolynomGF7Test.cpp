/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/PolynomGF7.h"
#include "./AAF/AAL/Polynom.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
using namespace AAL;

/*
	Êîíñòðóêòîðû êëàññà PolynomGF3
*/
TEST(PolynomGF7, EmptyConstructor)
{
	PolynomGF7 i;
	CHECK(i.isZero());
}

/*
        Óíàðíûå îïåðàöèè
*/

TEST(PolynomGF7, operatorEqual)
{
	PolynomGF7 p1("11200002000010222201111122010212012012120201");
	PolynomGF7 p2("2222222222111111111111212121020201010010101002010202001");
	PolynomGF7 p3("1111100200020000200111110000022222200101012111121211");
	PolynomGF7 pp1, pp2, pp3, pp4;

	pp1 = p1;
	pp2 = pp3 = p2;

	p2 = p1;
	p3 = pp4;

	CHECK(pp1 == p1 && !p1.isZero() && p1.ToString() == "11200002000010222201111122010212012012120201");
	CHECK(pp2 == pp3 && !pp3.isZero() && pp2.ToString() == "2222222222111111111111212121020201010010101002010202001");
	CHECK(p2 == p1 && p2.ToString() == "11200002000010222201111122010212012012120201");
	CHECK(p3.isZero());
}


/*        Ìåòîäû àêöåïòîðû
*/
/*
TEST(PolynomGF3, SetData)
{
	PolynomGF3 i("1"),j("2");
        PolynomGF3 zero;
        PolynomGF3 one;
        PolynomGF3 two;

        one.setOne();
        two.setTwo();
	CHECK(i == one);
        CHECK(j == two);
        i.setZero();
        CHECK(i == zero);
}
TEST(PolynomGF3, isIrreducible)
{
  PolynomGF3 p10("211"), p11("2011"), p12("200011"), p13("21001"), p14("210001"), p15("200011");
  PolynomGF3 p20("1201"), p21("120001"), p22("1200001"), p23("1020000000001");
  PolynomGF3 p30("221"), p31("2201"), p32("200200000001");
  PolynomGF3 p40("1100000001"), p41("100100001"), p42("1011"), p43("20010001");
  PolynomGF3 p50("22000000000000000000000000000000001"), p("01");
 
  CHECK(p10.isIrreducible());
  CHECK(p11.isIrreducible());
  CHECK(p12.isIrreducible());
  CHECK(p13.isIrreducible());
  CHECK(!p14.isIrreducible());
  CHECK(p15.isIrreducible());

  CHECK(p20.isIrreducible());
  CHECK(p21.isIrreducible());
  CHECK(p22.isIrreducible());
  CHECK(p23.isIrreducible());

  CHECK(p30.isIrreducible());
  CHECK(p31.isIrreducible());
  CHECK(p32.isIrreducible());

  CHECK(!p40.isIrreducible());
  CHECK(!p41.isIrreducible());
  CHECK(!p42.isIrreducible());
  CHECK(!p43.isIrreducible());
}

TEST(PolynomGF3, GenerateIrreducible)
{
  PolynomGF3 p1, p2, p3, p4;
  p1.GenerateIrreducible(10);
  p2.GenerateIrreducible(32);
  p3.GenerateIrreducible(34);
  p4.GenerateIrreducible(38);
  CHECK(p1.isIrreducible());
  CHECK(p2.isIrreducible());
  CHECK(p3.isIrreducible());
  CHECK(p4.isIrreducible());
}

/*TEST(PolynomGF3, isPrimitivity)
{
  PolynomGF3 p10("2011"), p11("200011"), p12("210001"), p13("200011");
  PolynomGF3 p20("1201"), p21("120001"), p22("1200001"), p23("1020000000001");
  PolynomGF3 p30("221"), p31("2201"), p32("200200000001");
  PolynomGF3 p40("1100000001"), p41("100100001"), p42("1011"), p43("20010001");

  CHECK(!p10.isPrimitivity());
  CHECK(!p11.isPrimitivity());
  CHECK(p12.isPrimitivity());
  CHECK(!p13.isPrimitivity());

  /* CHECK(p20.isPrimitivity());
  CHECK(p21.isPrimitivity());
  CHECK(p22.isPrimitivity());
  CHECK(p23.isPrimitivity());

  CHECK(p30.isPrimitivity());
  CHECK(p31.isPrimitivity());
  CHECK(p32.isPrimitivity());

  CHECK(!p40.isPrimitivity());
  CHECK(!p41.isPrimitivity());
  CHECK(!p42.isPrimitivity());
  CHECK(!p43.isPrimitivity()); 
}
*/
/*
        Îïåðàöèè ñðàâíåíèÿ
*/
/*TEST(PolynomGF3, Smaller)
{
	PolynomGF3 i("121021211211"), j("12121012");
	CHECK(j < i);
}


/*
	Îïåðàöèè ïîáèòîâîãî ñäâèãà
*/
TEST(PolynomGF7, SHL)
{
	PolynomGF7 i("1002000210101010012101010100012101000121001022211111111111111111111111000001111222111211121112110020011211211211110001011121211111111");
	PolynomGF7 j("0000000000000000000000000000000000000000000001002000210101010012101010100012101000121001022211111111111111111111111000001111222111211121112110020011211211211110001011121211111111");
	PolynomGF7 k;

	k<<=100;
	CHECK((i<<45) == j);
	CHECK(k.isZero());
}

TEST(PolynomGF7, SHR)
{
	PolynomGF7 i("102020201010121001110121010001020100010100101111121111211121121112111200000211211121121121112112001021111111111111201001121121121111");
	PolynomGF7 j("10100101111121111211121121112111200000211211121121121112112001021111111111111201001121121121111");
	PolynomGF7 k;

	k>>=10001;
	CHECK((i>>37) == j);
	CHECK(k.isZero());
}

/*
        Îïåðàöèÿ ñëîæåíèÿ
*/
TEST(PolynomGF7, Sub)
{
	PolynomGF7 i("162025");
	PolynomGF7 j("111111");
        PolynomGF7 k("051614");
        PolynomGF7 zero("0");
        CHECK((i-j) == k);
        CHECK(i.ToString() == "162025");
        CHECK(j.ToString() == "111111");
	CHECK(i.Sub(i, j) == k );
	CHECK(j.Sub(j, zero).ToString() == "111111");
        CHECK(j.Sub(zero,zero).isZero());
}

TEST(PolynomGF7, Add)
{
	PolynomGF7 i("162025");
	PolynomGF7 j("141125");
        PolynomGF7 k("233143");
        PolynomGF7 i1("0346061");
        PolynomGF7 i11("3460610");
        PolynomGF7 i111("3036601");
        PolynomGF7 zero("0");
        CHECK((i1+i11) == i111);
        CHECK(i.ToString()=="162025");
        CHECK(j.ToString() == "141125");
	CHECK((i+j) == k);
	CHECK(i.Add(i, j) == k );
	CHECK(j.Add(j, zero).ToString() == "141125" && !j.isZero() && zero.isZero());
        CHECK(j.Add(zero,zero).isZero());

}


/*
	Îïåðàöèÿ óìíîæåíèÿ
*/

TEST(PolynomGF7, MulToConstant)
{
	PolynomGF7 i("162025");
	PolynomGF7 j("3");
	PolynomGF7 k ("346061");

	CHECK(k.ToString() == i.MulToConstant(i,j).ToString());
}

TEST(PolynomGF7, Mul)
{
	PolynomGF7 i("162025");
	PolynomGF7 j("333333");
	PolynomGF7 k ("30665636001");

	CHECK(k.ToString() == i.Mul(i,j).ToString());
}
TEST(PolynomGF7, ModMul)
{
	PolynomGF7 i("162025");
	PolynomGF7 j("333333");
	PolynomGF7 k ("364656360");
        PolynomGF7 f("1200000001");
        //std::string st = i.ModMul(i,j,f).ToString();
	CHECK(k.ToString() == i.ModMul(i,j,f).ToString());

	PolynomGF7 i1("461002325412");
	PolynomGF7 j1("312563254");
	PolynomGF7 k1("650643002");
        PolynomGF7 f1("1200000001");
       // std::string st = i1.ModMul(i1,j1,f1).ToString();
	CHECK(k1.ToString() == i1.ModMul(i1,j1,f1).ToString());

	PolynomGF7 i2("00001000000000");
	PolynomGF7 j2("00010000000000");
	PolynomGF7 k2 ("0121");
        PolynomGF7 f2("1101");
      std::string  st = i2.ModMul(i2,j2,f2).ToString();
	CHECK(k2.ToString() == st);

}
TEST(PolynomGF7, MulGF7_2n)
{
	PolynomGF7 i("162025");
	PolynomGF7 j("333333");
	PolynomGF7 k ("364656360");
        PolynomGF7 i1("461002325412");
	PolynomGF7 j1("312563254");
	PolynomGF7 k1("650643002"),r;
        PolynomGF7 g;
        PolynomGF7 f("1200000001");
        std::string st = r.MulGF7_2n(i,i1,j,j1,f,&g).ToString();
        st = g.ToString();
	CHECK(k.ToString() == r.MulGF7_2n(i,i1,j,j1,f,&g).ToString() && g.ToString() == k1.ToString());
}

/*
	Îïåðàöèÿ ïðèâåäåíèÿ ïî ìîäóëþ
*/

TEST(PolynomGF7, Mod)
{
	PolynomGF7 j("1200000001");
	PolynomGF7 i("01234560123456010");
	PolynomGF7 r, r1("516420551");

	PolynomGF7 jj("10000300000001");
	PolynomGF7 ii("0123456012345601011111111");
	PolynomGF7 rr, rr1("4446320525602");

	PolynomGF7 jj1("10000300000001");
	PolynomGF7 ii1("01234560123456010111122221111");
	PolynomGF7 rr_1, rr_11("1112631636013");

	CHECK(r.Mod(i,j) == r1);
	CHECK(rr.Mod(ii,jj) == rr1);
	CHECK(rr_1.Mod(ii1,jj1) == rr_11);
}
TEST(PolynomGF7, Pow)
{
        PolynomGF7 a("030"),b("110"),c("0"),c2("0");
        PolynomGF7 d("002"),c1("0"),c3("0"),d1("100");
        PolynomGF7 a1("12345612345612345612345612345");
        PolynomGF7 module("130000000000000000000000000001");
        PolynomGF7 ax("3"),bx("1");
        c.ModMul(a1,a1,module);
        std::string s = c.ToString();
        c.ModMul(c,a1,module);
        s = c.ToString();
        c.ModMul(c,a1,module);
        s = c.ToString();
        c.ModMul(c,a1,module);
        s = c.ToString();
        c.ModMul(c,a1,module);
        s = c.ToString();
        c.ModMul(c,a1,module);
        s = c.ToString();


         c2.Pow(a1,AAL::Integer(7),module);
         CHECK(c2 == c);
         c1.PowSeven_29(a1,module,bx,ax);
         CHECK(c == c1);
         s = c.ToString();
         s = c1.ToString();
         PolynomGF7 module1("1101");
          CHECK(c3.Pow(b,AAL::Integer(342),module1) == d1);
          s = c3.ToString();
          CHECK(c1.Pow(a,AAL::Integer(2),module) == c2.ModMul(a,a,module));

}
TEST(PolynomGF7, Inverse)
{
        PolynomGF7 a3("300"),c1,c11;
        PolynomGF7 a4("02200");
        PolynomGF7 d1("22122"), d2("11211");
        PolynomGF7 one("1"),m;
        PolynomGF7 module1("1101");
        PolynomGF7 a1("1"),d11("0");
        c1.Inverse(a1,module1);
    CHECK(c1*a3 == one);
    std::string s = c1.ToString();
    CHECK(c1.Inverse(a3,module1)*a3 == one);
}

/*
/*
	Îïåðàöèÿ äåëåíèå
*/
  /*
TEST(PolynomGF3, Div)
{
       	PolynomGF3 i1("1010200200120000100002");
	PolynomGF3 j1("102001");
	PolynomGF3 k1 ("12202202002202002");
	PolynomGF3 r1, r2("01022");

	CHECK((k1 == i1.Div(i1,j1,&r1)) && (r1 == r2));

	PolynomGF3 i2("001");
	PolynomGF3 j2("121");
	PolynomGF3 k2 ("1");
	PolynomGF3 r3, r4("21");

	CHECK((k2 == i2.Div(i2,j2,&r3)) && (r3 == r4));

}

TEST(PolynomGF3, Square1)
{
	PolynomGF3 i("102102102");
	PolynomGF3 j("12210101210000110122220211100001000212200220201201202120212");
        PolynomGF3 i1("1");
        PolynomGF3 m("20000000000000000000000000000010000000000000000000000000000001");
	PolynomGF3 k ("0000100100000200100100120100000200000000010002");
        PolynomGF3 temp("1");

	CHECK(i1 == temp.Square1(i1,m));
        CHECK(i == k.Square1(i,m)*k.Square1(i,m));
        CHECK(j == k.Square1(i,m));
}
TEST(PolynomGF3, InverseMod)
{
	PolynomGF3 i("102102102");
	PolynomGF3 j("1120020001120020001120020001120212102002000011120212102002");
        PolynomGF3 i1("1");
        PolynomGF3 m("20000000000000000000000000000010000000000000000000000000000001");
	PolynomGF3 k ("0000100100000200100100120100000200000000010002");
        PolynomGF3 temp("1");

	CHECK(j == temp.InverseMod(i,m));
        CHECK(i1 == k.InverseMod(i1,m));
}

TEST(PolynomGF3, ModPow)
{
	PolynomGF3 i("102102102");
	PolynomGF3 j("10121222212101000000000000020212111121202");
        AAL::Integer iB("5");
        PolynomGF3 i1("1");
        PolynomGF3 m("20000000000000000000000000000010000000000000000000000000000001");
	PolynomGF3 k ("0000100100000200100100120100000200000000010002");
        PolynomGF3 temp("1");

	CHECK(j == temp.ModPow(i,iB,m));
        CHECK(i1 == k.ModPow(i1,iB,m));
}

/* Òåñòû ×åðíûøåâîé */
/*
TEST(PolynomGF3, getPowersOfPolynom)
{
	PolynomGF3 a("00002"), b("102001");

  std::list<std::pair<uint, uint> > setA, setB;
  std::list<std::pair<uint, uint> > setAA, setBB;
  setAA.push_back(std::make_pair(2,4));
  setBB.push_back(std::make_pair(1,0));
  setBB.push_back(std::make_pair(2,2));
  setBB.push_back(std::make_pair(1,5));
  setA = a.getPowersOfPolynom();
  setB = b.getPowersOfPolynom();

  bool flag = false;
  std::list<std::pair<uint, uint> >::iterator j = setAA.begin();
  for (std::list<std::pair<uint, uint> >::iterator i = setA.begin(); i != setA.end(); ++i)
  {
    if (i->first != j->first && i->second != j->second)
    {
      flag = false;
      break;
    }
    else
      flag = true;
    j++;
  }
  CHECK(flag == true);

  j = setBB.begin();
  for (std::list<std::pair<uint, uint> >::iterator i = setB.begin(); i != setB.end(); ++i)
  {
    if (i->first != j->first && i->second != j->second)
    {
      flag = false;
      break;
    }
    else
      flag = true;
    j++;
  }
  CHECK(flag == true);
}

TEST(PolynomGF3, getPowersString)
{
  PolynomGF3 a("00001"), b("102001");

  std::string sA, sB;
  sA = a.ToStringByPowers();
  sB = b.ToStringByPowers();
  CHECK(sA == "{1,4} \n");
  CHECK(sB == "{1,0} {2,2} {1,5} \n");
}

TEST(PolynomGF3, ONB1)
{
  PolynomGF3 p;
  CHECK(p.ONB1Test(2));
  CHECK(p.ONB1Test(6));
  CHECK(p.ONB1Test(16));
  CHECK(p.ONB1Test(18));
  CHECK(p.ONB1Test(28));

  CHECK(!p.ONB1Test(10));
  CHECK(!p.ONB1Test(12));
  CHECK(!p.ONB1Test(22));
}
*/
//--------------------------------------------------------------------------------------
/*TEST(PolynomGF3, elementOrder)
{
  PolynomGF3 u;
  PolynomGF3 mod("1000201"), a("11");
  AAL::Integer ord(728);
  FactorizationAlgorithms w(ord);
  bool r;
  std::vector<DecompositionMember> vector = w.ProbingDivisionAlgorithmDecomposition();
  AAL::Integer t = u.elementOrder(mod, a,vector,ord);
  CHECK(t == 364);
}
//--------------------------------------------------------------------------------------
TEST(PolynomGF3, isGenerator)
{
  PolynomGF3 u;
  PolynomGF3 mod("1000201"), a("11");
  AAL::Integer ord(728);
  FactorizationAlgorithms w(ord);
  bool r;
  std::vector<DecompositionMember> vector = w.ProbingDivisionAlgorithmDecomposition();
  r = u.isGenerator(mod, a,vector,ord+1);
  CHECK(r == false);
}
 */
//--------------------------------------------------------------------------------------


