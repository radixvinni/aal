/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/Ellipticcurves.h"
#include "./AAF/AAL/Integer.h"
using namespace AAL;

/*
	ЭЦП
*/
TEST(EllipticCurves, DigitalSignature)
{
	AAL::Integer p("57896044618658097711785492504343953926634992332820282019728792003956564821041"), a("7"), b("43308876546767276905765904595650931995942111794451039583252968842033849580414");
	AAL::Integer m("57896044618658097711785492504343953927082934583725450622380973592137631069619"), q("57896044618658097711785492504343953927082934583725450622380973592137631069619");
	AAL::Integer x_p("2"), y_p("4018974056539037503335449422937059775635739389905545080690979365213431566280");
	AAL::Integer d("55441196065363246126355624130324183196576709222340016572108097750006097525544");
	AAL::Integer x_q("57520216126176808443631405023338071176630104906313632182896741342206604859403"), y_q("17614944419213781543809391949654080031942662045363639260709847859438286763994");

	//Формирование подписи шаг 1-3
	AAL::Integer e("20798893674476452017134061561508270130637142515379653289952617252661468872421"), k("53854137677348463731403841147996619241504003434302020712960838528893196233395");

	EllipticCurve curve(p, a, b);
	EllipticPoint pp(curve), c, qq(curve), cc, t;
	AAL::Integer r, s, v, z1, z2, rr;

	//точка P
	pp.setXY(x_p, y_p);
	//точка Q
	qq.setXY(x_q, y_q);
	//c=kP
	c.Mul(k, pp);
	CHECK(c.getX().ToString() == "29700980915817952874371204983938256990422752107994319651632687982059210933395" && c.getY().ToString() == "32842535278684663477094665322517084506804721032454543268132854556539274060910");
	//r=x_c(mod q)
	r = c.getX();
	r.ModPositive(q);
	CHECK(r.ToString() == "29700980915817952874371204983938256990422752107994319651632687982059210933395");
	//s=rd+ke(mod q)
	s = (r*d + k*e) % q;
	CHECK(s.ToString() == "574973400270084654178925310019147038455227042649098563933718999175515839552");

	//Проверка подписи
	//v=e^-1
	v.Inverse(e, q);
	CHECK(v.ToString() == "17686683605934468677301713824900268562746883080675496715288036572431145718978");
	//z1=sv(mod q), z2=-rv(mod q)
	z1 = (s*v) % q;
	CHECK(z1.ToString() == "37699167500901938556841057293512656108841345190491942619304532412743720999759");
	z2 = (-r*v).ModPositive(q);
	CHECK(z2.ToString() == "1417199842734347211251591796950076576924665583897286211449993265333367109221");
	//cc=z1P+z2Q
	cc = (z1*pp);
        t = z2*qq;
        cc += t;
	CHECK(cc.getX().ToString() == "29700980915817952874371204983938256990422752107994319651632687982059210933395");
	CHECK(cc.getY().ToString() == "32842535278684663477094665322517084506804721032454543268132854556539274060910");
	rr = cc.getX();
	rr.ModPositive(q);
	CHECK(rr == r && rr.ToString() == "29700980915817952874371204983938256990422752107994319651632687982059210933395");
}
TEST(EllipticCurves, Negate)
{
        AAL::Integer x("5"), y("0"), N("11");
        AAL::Integer a("-3"), b("0");
        EllipticCurve e(N,a,b);
        EllipticPoint ep(e), negate1, negate2(e);
        ep.setXY(x, y); // (5,0) = - (5,0)
        negate2.setInfinite(true);


        negate1.Negate(ep);
        negate2.Negate();

        CHECK(negate1 == ep);
        CHECK(negate2.isInfinite());
}
TEST(EllipticCurves, Add)
{
        AAL::Integer x("5"), y("0"), N("11");
        AAL::Integer a("-3"), b("0");
        EllipticCurve e(N,a,b);
        EllipticPoint ep(e);
        ep.setXY(x, y);// (5,0) = - (5,0)

        CHECK(ep.Add(ep, ep).isInfinite());
}
TEST(EllipticCurves, Double)
{
        AAL::Integer x("5"), y("0"), N("11");
        AAL::Integer a("-3"), b("0");
        EllipticCurve e(N,a,b);
        EllipticPoint ep(e);
        ep.setXY(x, y);// (5,0) = - (5,0)

        CHECK(ep.Double().isInfinite());
}

TEST(EllipticCurves, Mul)
{
        AAL::Integer x("72"), y("103"), N("127");
        AAL::Integer a("1"), b("1");
        EllipticCurve e(N,a,b);
        EllipticPoint ep1(e), ep2(e);
        ep1.setXY(x, y);
        ep2.setXY(x, y);

        AAL::Integer two(2);
        ep1.Double();
        ep2.Mul(ep2, two);

        CHECK(ep1 == ep2);
}

TEST(EllipticCurves, Mul1)
{
        AAL::Integer x("72"), y("103"), N("127");
        AAL::Integer a("1"), b("1");
        EllipticCurve e(N,a,b);
        EllipticPoint ep(e);
        ep.setXY(x, y);

        AAL::Integer zero(0);

        ep.Mul(ep, zero);

        CHECK(ep.isInfinite());
}

