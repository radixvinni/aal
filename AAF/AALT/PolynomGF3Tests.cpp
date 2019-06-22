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
using namespace AAL;

/*
	Конструкторы класса PolynomGF3
*/
TEST(PolynomGF3, EmptyConstructor)
{
	PolynomGF3 i;
	CHECK(i.isZero());
}

/*
        Унарные операции
*/

TEST(PolynomGF3, operatorEqual)
{
	PolynomGF3 p1("11200002000010222201111122010212012012120201");
	PolynomGF3 p2("2222222222111111111111212121020201010010101002010202001");
	PolynomGF3 p3("1111100200020000200111110000022222200101012111121211");
	PolynomGF3 pp1, pp2, pp3, pp4;

	pp1 = p1;
	pp2 = pp3 = p2;

	p2 = p1;
	p3 = pp4;

	CHECK(pp1 == p1 && !p1.isZero() && p1.ToString() == "11200002000010222201111122010212012012120201");
	CHECK(pp2 == pp3 && !pp3.isZero() && pp2.ToString() == "2222222222111111111111212121020201010010101002010202001");
	CHECK(p2 == p1 && p2.ToString() == "11200002000010222201111122010212012012120201");
	CHECK(p3.isZero());
}

/*
        Методы акцепторы
*/
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
        Операции сравнения
*/
TEST(PolynomGF3, Smaller)
{
	PolynomGF3 i("121021211211"), j("12121012");
	CHECK(j < i);
}


/*
	Операции побитового сдвига
*/
TEST(PolynomGF3, SHL)
{
	PolynomGF3 i("1002000210101010012101010100012101000121001022211111111111111111111111000001111222111211121112110020011211211211110001011121211111111");
	PolynomGF3 j("0000000000000000000000000000000000000000000001002000210101010012101010100012101000121001022211111111111111111111111000001111222111211121112110020011211211211110001011121211111111");
	PolynomGF3 k;

	k<<=100;
	CHECK((i<<45) == j && k.isZero());
}

TEST(PolynomGF3, SHR)
{
	PolynomGF3 i("102020201010121001110121010001020100010100101111121111211121121112111200000211211121121121112112001021111111111111201001121121121111");
	PolynomGF3 j("10100101111121111211121121112111200000211211121121121112112001021111111111111201001121121121111");
	PolynomGF3 k;

	k>>=10001;
	CHECK((i>>37) == j && k.isZero());
}

/*
        Операция сложения
*/
TEST(PolynomGF3, Add)
{
	PolynomGF3 i("212011220121000011122212121001210212");
	PolynomGF3 j("22120212101210210000001122221211111221222111");
        PolynomGF3 k("11210121202120120000002211112122222112111222");
        PolynomGF3 zero;

        PolynomGF3 iADDj("10021001110010211112222001021002102121222111");

	CHECK((i+j) == iADDj && i.ToString()=="212011220121000011122212121001210212" && j.ToString() == "22120212101210210000001122221211111221222111" );
	CHECK(i.Add(i, j) == iADDj && i.ToString()=="10021001110010211112222001021002102121222111" && j.ToString() == "22120212101210210000001122221211111221222111" );
	CHECK(j.Add(j, zero).ToString() == "22120212101210210000001122221211111221222111" && !j.isZero() && zero.isZero());
	CHECK((j + k) == zero && j.ToString() == "22120212101210210000001122221211111221222111" && k.ToString() == "11210121202120120000002211112122222112111222");
        CHECK(j.Add(j,k).isZero());

}


/*
	Операция умножения
*/
TEST(PolynomGF3, Mul)
{
	PolynomGF3 i("010000000020000010002");
	PolynomGF3 j("00010010000000020000000001");
	PolynomGF3 k ("0000100100000200100100120100000200000000010002");
        
	CHECK(k == i.Mul(i,j));
}

/*
	Операция деление
*/

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

/*
	Операция приведения по модулю
*/

TEST(PolynomGF3, Mod)
{
	PolynomGF3 i("1010200200120000100002");
	PolynomGF3 j("102001");
	PolynomGF3 r, r1("01022");

	CHECK(r.Mod(i,j) == r1);
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

/* Тесты Чернышевой */
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
TEST(PolynomGF3, elementOrder)
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

//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
TEST(PolynomGF3, LegendreSymbol)
{
  PolynomGF3 a("112"),c1,c2;
  PolynomGF3 a1("2101");
  PolynomGF3 a2("10120");
  PolynomGF3 one("1");
  PolynomGF3 two("2");
  PolynomGF3 mod("220001");
  CHECK(c1.LegendreSymbol(a2,mod) == two);
  CHECK(c1.LegendreSymbol(a,mod) == one);
  CHECK(c1.LegendreSymbol(a1,mod) == two);
}

//--------------------------------------------------------------------------------------
TEST(PolynomGF3, Sqrt)
{
  PolynomGF3 a22("1"),c;
  PolynomGF3 a11("02202"),c1;
  PolynomGF3 a12("01100");

  PolynomGF3 a("02111"),d("01112");
  PolynomGF3 a1("10010"),d1("20002");
  PolynomGF3 a2("21101"),d2("0");
  PolynomGF3 a3("11201"),d3("0");
  PolynomGF3 a4("10200"),d4("0");
  PolynomGF3 a5("02202"),d5("0");
  PolynomGF3 a6("10200"),d6("0");


  PolynomGF3 mod("220001");
  int m = mod.getNumberBits() - 1;
  AAL::Integer ord(1);
  std::string str;
  ord = ord.Pow(3,m);
  ord = ord - 1;
  str = ord.ToString();
  AAL::Integer two_pow("0"),div,copy_ord;
  copy_ord = ord;
  div = ord%2;
  ord = ord/2;
  str = div.ToString();
  str = ord.ToString();
  while(div == 0)
  {
        two_pow++;
        div = ord%2;
        str = div.ToString();
        ord = ord/2;
        str = ord.ToString();
  }
  str = two_pow.ToString();
  AAL::Integer s,T,i;
  //("25736391511831"), T("2");
  T = two_pow;
  s = ord*2+1;
  str = s.ToString();
  c.Sqrt(a11,mod,s,T);
  CHECK(c.isZero());
  c1.Sqrt(a12,mod,s,T);
  CHECK(c.ModPow(c1,Integer(2),mod) == a12);


  CHECK(c.Sqrt(a,mod,s,T) == d);
CHECK(c.Sqrt(a1,mod,s,T) == d1);
  CHECK(c.ModPow(d1,Integer(2),mod) == a1);
CHECK(c.Sqrt(a2,mod,s,T) == d2);
CHECK(c.Sqrt(a3,mod,s,T) == d3);
CHECK(c.Sqrt(a4,mod,s,T) == d4);
CHECK(c.Sqrt(a5,mod,s,T) == d5);
CHECK(c.Sqrt(a6,mod,s,T) == d6);
}
//--------------------------------------------------------------------------------------

