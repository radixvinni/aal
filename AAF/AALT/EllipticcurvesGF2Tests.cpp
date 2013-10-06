/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/EllipticcurvesGF2.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/PolynomGF2_m_4.h"
#include "./AAF/AAL/PolynomGF2_mY_7.h"
using namespace AAL;
TEST(EllipticCurveGF2, ord)
{
        Polynom module1("1101"), a3("1"), a4("0"), a6("0"), a44("1"), a66("1");
        SuperSingularEllipticCurve curve3(module1, a3, a4, a6);
        AAL::Integer rez("11972621413014756705924586149611790497021399392059393");
        CHECK(curve3.getOrd(173) == rez);
        SuperSingularEllipticCurve curve(module1, a3, a44, a6);
        AAL::Integer rez1("3138550867693340381917894711683061370565442059825561206785");
        CHECK(curve.getOrd(191) == rez1);
        SuperSingularEllipticCurve curve2(module1, a3, a44, a66);
        AAL::Integer rez2("3138550867693340381917894711524605045536913384638473306113");
        CHECK(curve2.getOrd(191) == rez2);
}
TEST(EllipticCurveGF2, equals)
{
        SuperSingularEllipticCurve curve1, curve2;
        CHECK(curve1 == curve1 && curve1 == curve2);
        Polynom module1("1101"), a3("1"), a4("1"), a6("0");
        SuperSingularEllipticCurve curve3(module1, a3, a4, a6);
        CHECK(curve1 != curve3);
        
        NonSuperSingularEllipticCurve curve4, curve5;
        CHECK(curve4 == curve4 && curve4 == curve5);
        Polynom module2("1101"), b2("1"), b6("0");
        NonSuperSingularEllipticCurve curve6(module2, b2, b6);
        CHECK(curve4 != curve6);

        CHECK(curve1 != curve4 && curve4 != curve1);
}
TEST(EllipticCurveGF2, inGroup)
{
        SuperSingularEllipticCurve sscurve;
        Polynom x1("01"), y1("0");     
        CHECK(sscurve.inGroup(x1,y1));

        NonSuperSingularEllipticCurve nsscurve;
        nsscurve.setModule(Polynom("111"));
        Polynom x2("0"), y2("1"), x3("11"), y3("01");
        CHECK(nsscurve.inGroup(x2, y2) && nsscurve.inGroup(x3, y3));

}
/*TEST(SuperSingularEllipticPoint, SetCurve)
{
        Polynom a3("01"), a4("01"), a6("01"), module("1101");
        SuperSingularEllipticCurve curve1, curve2(module, a3, a4, a6);

        SuperSingularEllipticCurve & curve1ref = curve1, & curve2ref = curve2;

        Polynom x("01");
        Polynom y("0");
        SuperSingularEllipticPoint point(curve1);
        point.setCurve(curve2);
}*/
TEST(EllipticPointGF2, Negate)
{
        SuperSingularEllipticCurve curve;
        Polynom x("01");
        Polynom y("0");
        SuperSingularEllipticPoint point(curve);
        point.setXY(x, y);
        point.Negate();
        CHECK(point.getX().ToString() == "01" && point.getY().ToString() == "1");

        NonSuperSingularEllipticCurve nsscurve;
        nsscurve.setModule(Polynom("111"));
        Polynom x2("0"), y2("1");
        NonSuperSingularEllipticPoint nsspoint(nsscurve);
        nsspoint.setXY(x2, y2);
        nsspoint.Negate();
        CHECK(nsspoint.getX().ToString() == "0" && point.getY().ToString() == "1");
}
TEST(EllipticPointGF2, Add)
{
        SuperSingularEllipticCurve curve;
        Polynom x1("01"), y1("0"), x2("01"), y2("0");
        SuperSingularEllipticPoint point1(curve), negatePoint1, point2(curve), result1, result2;
        point1.setXY(x1, y1);
        negatePoint1.Negate(point1);
        point2.setXY(x2, y2);

        CHECK(result1.Add(point1, negatePoint1).isInfinite());
        result2.Add(point1, point2);
        CHECK(result2.getX().ToString() == "111" && result2.getY().ToString() == "011");

        NonSuperSingularEllipticCurve nsscurve;
        nsscurve.setModule(Polynom("111"));
        Polynom x3("0"), y3("1"), x4("1"), y4("01"); // самообратная точка
        NonSuperSingularEllipticPoint nsspoint1(nsscurve), nsspoint2(nsscurve), nsspoint3(nsscurve), result3, result4;
        nsspoint1.setXY(x3, y3);
        nsspoint2.setXY(x3, y3);
        nsspoint3.setXY(x4, y4);                

        CHECK(result3.Add(nsspoint1, nsspoint2).isInfinite());
        result4.Add(nsspoint3, nsspoint3);
        CHECK(result4.getX().ToString() == "0" && result4.getY().ToString() == "1");
        result4.Add(nsspoint1, nsspoint3);
        CHECK(result4.getX().ToString() == "1" && result4.getY().ToString() == "11");
}

TEST(EllipticPointGF2, Add2)
{
        NonSuperSingularEllipticCurve nsscurve;
        nsscurve.setModule(Polynom("101001"));
        Polynom x("00101"), y("1011");
        CHECK(nsscurve.inGroup(x, y));
        NonSuperSingularEllipticPoint nsspoint1(nsscurve), nsspoint2(nsscurve), nsspoint3(nsscurve), result3, result4;
        nsspoint1.setXY(x, y);
        nsspoint2.Mul(nsspoint1, AAL::Integer(2));
        CHECK(nsscurve.inGroup(nsspoint2.getX(), nsspoint2.getY()));
        nsspoint3.Add(nsspoint1, nsspoint2);
        CHECK(nsscurve.inGroup(nsspoint3.getX(), nsspoint3.getY()));
}

TEST(EllipticPointGF2, Double)
{
        SuperSingularEllipticCurve curve;
        Polynom x1("01"), y1("0");
        SuperSingularEllipticPoint point1(curve), result1;
        point1.setXY(x1, y1);

        result1.Double(point1);
        CHECK(result1.getX().ToString() == "111" && result1.getY().ToString() == "011");

        NonSuperSingularEllipticCurve nsscurve;
        nsscurve.setModule(Polynom("111"));
        Polynom x3("0"), y3("1"), x4("1"), y4("01"); // самообратная точка
        NonSuperSingularEllipticPoint nsspoint1(nsscurve), nsspoint2(nsscurve), result3, result4;
        nsspoint1.setXY(x3, y3);
        nsspoint2.setXY(x4, y4);

        CHECK(result3.Double(nsspoint1).isInfinite());
        result4.Double(nsspoint2);
        CHECK(result4.getX().ToString() == "0" && result4.getY().ToString() == "1");
}

TEST(EllipticPointGF2, Mul)
{
        SuperSingularEllipticCurve curve;
        Polynom x1("01"), y1("0");
        SuperSingularEllipticPoint point1(curve), result1;
        AAL::Integer i(5);
        point1.setXY(x1, y1);

        //result1.Mul(i, point1);
        result1.Mul(point1, i);
        CHECK(result1.getX().ToString() == "11" && result1.getY().ToString() == "01");

        NonSuperSingularEllipticCurve nsscurve;
        nsscurve.setModule(Polynom("111"));
        Polynom x2("0"), y2("1");
        NonSuperSingularEllipticPoint point2(nsscurve), result2;
        AAL::Integer j(5);
        point2.setXY(x2, y2);

        result2.Mul(point2, j);
        CHECK(result2.getX().ToString() == "0" && result2.getY().ToString() == "1");
}

TEST(EllipticPointGF2, Mul1)
{
        SuperSingularEllipticCurve curve;
        Polynom x1("01"), y1("0");
        SuperSingularEllipticPoint point1(curve);
        AAL::Integer i(5);
        point1.setXY(x1, y1);

        point1.Mul(point1, i);
        CHECK(!point1.isInfinite());

        NonSuperSingularEllipticCurve nsscurve;
        nsscurve.setModule(Polynom("111"));
        Polynom x2("0"), y2("1");
        NonSuperSingularEllipticPoint point2(nsscurve);
        AAL::Integer j(5);
        point2.setXY(x2, y2);

        point2.Mul(point2, j);
        CHECK(!point2.isInfinite());
}

TEST(EllipticPointGF2, Generate)
{
        SuperSingularEllipticCurve curve1, curve2;
        curve2.setModule(Polynom("11001"));
        SuperSingularEllipticPoint point1(curve1), point2(curve2);

        point1.Generate();
        point2.Generate();
        CHECK(curve1.inGroup(point1.getX(), point1.getY()));
        CHECK(curve2.inGroup(point2.getX(), point2.getY()));

        NonSuperSingularEllipticCurve curve3, curve4;
        curve4.setModule(Polynom("11001"));
        NonSuperSingularEllipticPoint point3(curve3), point4(curve4);

        point3.Generate();
        point4.Generate();
        CHECK(curve3.inGroup(point3.getX(), point3.getY()));
        CHECK(curve4.inGroup(point4.getX(), point4.getY()));
}
TEST(EllipticPointGF2, WrappingGenerate)
{
        SuperSingularEllipticCurve curve1, curve2;
        curve1.setModule(Polynom("100000000101"));
        curve2.setModule(Polynom("10000001001"));

        SuperSingularEllipticPoint point1(curve1), point2(curve2);
        Polynom xforwrap("111"), badxforwrap("111111111");


        point1.WrappingGenerate(xforwrap);
        point2.WrappingGenerate(xforwrap);
        CHECK(curve1.inGroup(point1.getX(), point1.getY()) && ((point1.getX() & xforwrap) == xforwrap));
        CHECK(curve2.inGroup(point2.getX(), point2.getY()) && ((point2.getX() & xforwrap) == xforwrap));

        try
        {
                point1.WrappingGenerate(badxforwrap);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }

        NonSuperSingularEllipticCurve curve3, curve4;
        curve3.setModule(Polynom("100000000101"));
        curve4.setModule(Polynom("10000001001"));

        NonSuperSingularEllipticPoint point3(curve3), point4(curve4);    

        point3.WrappingGenerate(xforwrap);
        point4.WrappingGenerate(xforwrap);
        CHECK(curve3.inGroup(point3.getX(), point3.getY()) && ((point3.getX() & xforwrap) == xforwrap));
        CHECK(curve4.inGroup(point4.getX(), point4.getY()) && ((point4.getX() & xforwrap) == xforwrap));
/*
        try
        {
                point3.WrappingGenerate(badxforwrap);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
*/
}
TEST(EllipticPointGF2, findRo)
{
   PolynomGF2_m_4 ro;
  Polynom module1("1101");
  SuperSingularEllipticCurve curve;
  SuperSingularEllipticPoint point1(curve), result1;
  PolynomGF2_m_4 b("1","0","0","0","1101");
  PolynomGF2_m_4 ro1("0", "1", "0", "0","1101");
  ro = point1.findRo(module1,b);
  ro.setModule(module1);
  CHECK(ro == ro1)
  PolynomGF2_m_4 r4,r,one("1","0","0","0","1101");
  r4.setModule(module1);
  r.setModule(module1);
  r4.Pow(ro,Integer(4));
  r.Add(ro,r4);
  r.Add(r,one);
  std::string str = r.getA0().ToString();
  str = r.getA1().ToString();
  str = r.getA2().ToString();
  str = r.getA3().ToString();
}
TEST(EllipticPointGF2, DLK)
{
 	Polynom module1("101001");
        PolynomGF2_m_4 b("1","0","0","0","101001");
        PolynomGF2_m_4 t("1","1","0","0","101001");
  SuperSingularEllipticCurve curve;
          std::string str;
  SuperSingularEllipticPoint point11(curve), point12(curve),point13(curve), point14(curve);
        t = point11.findRo(module1,b);
        point11.Generate();
        point12.Double(point11);
        //point1.Generate();
	Polynom x11("0");
        Polynom y11("1");
	Polynom x21("1");
        Polynom y21("0");
        x11 = point11.getX();
        y11 = point11.getY();
        x21 = point12.getX();
        y21 = point12.getY();
        str = x11.ToString();
        str = y11.ToString();
        str = x21.ToString();
        str = y21.ToString();
 //       point11.setXY(x11,y11);
  //      point12.setXY(x21,y21);
	Polynom x1("1");
        Polynom y1("0");
	Polynom x2("0");
        Polynom y2("0");
        point13.Mul(point11,Integer(3));
        point14.Mul(point12,Integer(3));

      //  PolynomGF3_m_6 ro("0", "0", "2", "1", "2", "0","220001");
        PolynomGF2_m_4 result,result1,r,t1,t2("0", "0", "0", "0","101001"),two("1", "0", "0", "0","101001");
        t2.Pow(t,Integer(4));
        r.Add(t2,t);
        r.Add(r,two);

         t.setModule(module1);
        str  = t.getA0().ToString();
    str = t.getA1().ToString();
    str = t.getA2().ToString();
    str = t.getA3().ToString();

    str  = r.getA0().ToString();
    str = r.getA1().ToString();
    str = r.getA2().ToString();
    str = r.getA3().ToString();


   result.setModule(module1);
   result1.setModule(module1);
   t2.setModule(module1);
   uint m = module1.getNumberBits() - 1;
   result = point13.DLK(point11,point12,t,m,b,module1);
    str = result.getA0().ToString();
    str = result.getA1().ToString();
    str = result.getA2().ToString();
    str = result.getA3().ToString();

       result1 = point13.DLK(point13,point14,t,3,b,module1);
    str = result1.getA0().ToString();
    str = result1.getA1().ToString();
    str = result1.getA2().ToString();
    str = result1.getA3().ToString();

    t2.Pow(result,Integer(9));
    str = t2.getA0().ToString();
    str = t2.getA1().ToString();
    str = t2.getA2().ToString();
    str = t2.getA3().ToString();
    CHECK(t2 == result1);
}
