/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/PolynomGF3.h"
#include "./AAF/AAL/EllipticcurvesGF3.h"
#include "./AAF/AAL/PolynomGF3_m_6.h"
#include "./AAF/AAL/PolynomGF3_mY_9.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace AAL;

/*
	Конструкторы класса PolynomGF3
*/
TEST(EllipticCurveGF3, EmptyConstructor)
{
	EllipticCurveGF3 i;
        PolynomGF3 m("1101"),a2("1"),a4("1"),a6("1");
	CHECK(m == i.getModule());
        CHECK(a2 == i.getA2());
        CHECK(a4 == i.getA4());
        CHECK(a6 == i.getA6());
}

 /*
TEST(EllipticCurveGF3, inGroup)
{
        PolynomGF3 m("20000000000000000000000000000010000000000000000000000000000001"),a2("1"),a4("1"),a6("1");
        EllipticCurveGF3 i(m,a2,a4,a6);
        PolynomGF3 x1("221011220222120000110122102002120122212100001");
        PolynomGF3 y1("0011212120110202001012022112201011002020210210201222220022002");
        CHECK(i.inGroup(x1,y1));
}

/*
        Операция сложения
*/
/*TEST(EllipticPointGF3, Add)
{
        PolynomGF3 module("20000000000000000000000000000010000000000000000000000000000001");
        PolynomGF3 a2("1"), a4("1"), a6("1");
        EllipticCurveGF3 Curve1(module,a2,a4,a6);
        EllipticPointGF3 point1(Curve1), point2(Curve1), point3(Curve1);
	PolynomGF3 x1("221011220222120000110122102002120122212100001");
        PolynomGF3 x2("00011121110002112202002012110011212001102210212");
	PolynomGF3 y1("0011212120110202001012022112201011002020210210201222220022002");
        PolynomGF3 y2("021110100210021100200101122202121111221111100121101212100002");
        point1.setXY(x1,y1);
        point2.setXY(x2,y2);
        PolynomGF3 resX1("0001010201202122120111202010112011011110201221200020021110012");
        PolynomGF3 resY1("2021200202200012110110010212111110200201212122102002110102212");
        PolynomGF3 resX2("1222021201000221002201112001221202012110021020211001012222011");
        PolynomGF3 resY2("1201002200210002002122102100000102121220221110021000101020212");
        point3.Add(point1,point2);
        CHECK (point3.getX() == resX1);
        CHECK (point3.getY() == resY1);
        point3.Add(point1,point1);
        CHECK (point3.getX() == resX2);
        CHECK (point3.getY() == resY2);

        PolynomGF3 module1("220001");
        PolynomGF3 a12("22121"), a14("21121"), a16("20000");
        EllipticCurveGF3 Curve11(module1,a12,a14,a16);
        EllipticPointGF3 point11(Curve11), point12(Curve11), point13(Curve11), point14(Curve11);
	PolynomGF3 x11("10022");
        PolynomGF3 y11("10000");
        point11.setXY(x11,y11);

	PolynomGF3 x21("12122");
        PolynomGF3 y21("21000");
        point12.setXY(x21,y21);

        PolynomGF3 res1X2("02021");
        PolynomGF3 res1Y2("02212");
        point13.Add(point12,point11);
        CHECK (point13.getX() == res1X2);
        CHECK (point13.getY() == res1Y2);

}
/*
        Операция удвоения
*/
/*TEST(EllipticPointGF3, Double)
{
        PolynomGF3 module("20000000000000000000000000000010000000000000000000000000000001");
        PolynomGF3 a2("1"), a4("1"), a6("1");
        EllipticCurveGF3 Curve1(module,a2,a4,a6);
        EllipticPointGF3 point1(Curve1), point2(Curve1), point3(Curve1), point4(Curve1);
	PolynomGF3 x1("221011220222120000110122102002120122212100001");
        PolynomGF3 y1("0011212120110202001012022112201011002020210210201222220022002");
        point1.setXY(x1,y1);
        point2.setXY(x1,y1);
        PolynomGF3 resX2("1222021201000221002201112001221202012110021020211001012222011");
        PolynomGF3 resY2("1201002200210002002122102100000102121220221110021000101020212");
        point3.Add(point1,point2);
        point4.Double(point1);
        CHECK (point4.getX() == resX2);
        CHECK (point4.getY() == resY2);
        CHECK (point3==point4);

	PolynomGF3 module1("220001");
        PolynomGF3 a12("11000"), a14("22121"), a16("11012");
        EllipticCurveGF3 Curve11(module1,a12,a14,a16);
        EllipticPointGF3 point11(Curve11), point12(Curve11), point13(Curve11), point14(Curve11);
	PolynomGF3 x11("02120");
        PolynomGF3 y11("10022");
        point11.setXY(x11,y11);
        point12.setXY(x11,y11);
        EllipticPointGF3 point21(Curve11), point22(Curve11), point23(Curve11), point24(Curve11);
	PolynomGF3 x21("02120");
        PolynomGF3 y21("20011");
        point21.setXY(x21,y21);

        PolynomGF3 res1X2("02201");
        PolynomGF3 res1Y2("00101");
        point13.Double(point12);
        CHECK (point13.getX() == res1X2);
        CHECK (point13.getY() == res1Y2);


        PolynomGF3 a32("22121"), a34("21121"), a36("20000");
        EllipticCurveGF3 Curve31(module1,a32,a34,a36);
        EllipticPointGF3 point31(Curve31), point32(Curve31), point33(Curve31), point34(Curve31);
	PolynomGF3 x31("21210");
        PolynomGF3 y31("21210");
        point31.setXY(x31,y31);

	PolynomGF3 x23("21210");
        PolynomGF3 y23("12120");
        point32.setXY(x23,y23);
        PolynomGF3 res3X2("22201");
        PolynomGF3 res3Y2("10012");
        point33.Double(point31);
        CHECK (point33.getX() == res3X2);
        CHECK (point33.getY() == res3Y2);
        PolynomGF3 res32X2("22201");
        PolynomGF3 res32Y2("20021");
        point34.Double(point32);
        CHECK (point34.getX() == res32X2);
        CHECK (point34.getY() == res32Y2);

}

TEST(EllipticPointGF3, Negate)
{
PolynomGF3 module1("220001");
        PolynomGF3 a12("11000"), a14("22121"), a16("11012");
        EllipticCurveGF3 Curve11(module1,a12,a14,a16);
        EllipticPointGF3 point11(Curve11), point12(Curve11), point13(Curve11), point14(Curve11);
	PolynomGF3 x11("02120");
        PolynomGF3 y11("10022");
        point11.setXY(x11,y11);
        point12.setXY(x11,y11);

        PolynomGF3 res1X2("02120");
        PolynomGF3 res1Y2("20011");
        point13.Negate(point12);
        CHECK (point13.getX() == res1X2);
        CHECK (point13.getY() == res1Y2);

        PolynomGF3 a32("22121"), a34("21121"), a36("20000");
        EllipticCurveGF3 Curve31(module1,a32,a34,a36);
        EllipticPointGF3 point31(Curve31), point32(Curve31), point33(Curve31), point34(Curve31);
	PolynomGF3 x31("21210");
        PolynomGF3 y31("21210");
        point31.setXY(x31,y31);

        PolynomGF3 res3X2("21210");
        PolynomGF3 res3Y2("12120");
        point32.Negate(point31);
        CHECK (point32.getX() == res3X2);
        CHECK (point32.getY() == res3Y2);

}

/*
	Операция умножения на константу
*/
/*TEST(EllipticPointGF3, Mul)
{
	PolynomGF3 module("20000000000000000000000000000010000000000000000000000000000001");
        PolynomGF3 a2("1"), a4("1"), a6("1");
        EllipticCurveGF3 Curve1(module,a2,a4,a6);
        EllipticPointGF3 point1(Curve1), point2(Curve1), point3(Curve1), point4(Curve1);
	PolynomGF3 x1("221011220222120000110122102002120122212100001");
        PolynomGF3 y1("0011212120110202001012022112201011002020210210201222220022002");
        point1.setXY(x1,y1);
        point2.setXY(x1,y1);
        Integer C("2"), CC("55");
        PolynomGF3 resX2("1222021201000221002201112001221202012110021020211001012222011");
        PolynomGF3 resY2("1201002200210002002122102100000102121220221110021000101020212");
        PolynomGF3 resX1("110220220020211100221002211212022101121202210102220001202222");
        PolynomGF3 resY1("111120121002010010201221112211110211000120222201102002102002");
        point3.Mul(point2,C);
        point4.Mul(point1,CC);
        CHECK (point3.getX() == resX2);
        CHECK (point3.getY() == resY2);
        CHECK (point4.getX() == resX1);
        CHECK (point4.getY() == resY1);
	PolynomGF3 module1("220001");
        PolynomGF3 a12("11000"), a14("22121"), a16("11012");
        EllipticCurveGF3 Curve11(module1,a12,a14,a16);
        EllipticPointGF3 point11(Curve11), point12(Curve11), point13(Curve11), point14(Curve11);
	PolynomGF3 x11("02120");
        PolynomGF3 y11("10022");
        point11.setXY(x11,y11);
        point12.setXY(x11,y11);
        EllipticPointGF3 point21(Curve11), point22(Curve11), point23(Curve11), point24(Curve11);
	PolynomGF3 x21("02120");
        PolynomGF3 y21("20011");
        point21.setXY(x21,y21);
        point22.setXY(x21,y21);

        Integer C1("2"), CC1("13");
        PolynomGF3 res1X2("02201");
        PolynomGF3 res1Y2("00101");
        PolynomGF3 res1X1("01212");
        PolynomGF3 res1Y1("21212");
        point13.Mul(point12,C1);
        point14.Mul(point11,CC1);
        CHECK (point13.getX() == res1X2);
        CHECK (point13.getY() == res1Y2);
        CHECK (point14.getX() == res1X1);
        CHECK (point14.getY() == res1Y1);

        PolynomGF3 res2X2("02201");
        PolynomGF3 res2Y2("00202");
        PolynomGF3 res2X1("01212");
        PolynomGF3 res2Y1("12121");
        point23.Mul(point22,C1);
        point24.Mul(point21,CC1);
        CHECK (point23.getX() == res2X2);
        CHECK (point23.getY() == res2Y2);
        CHECK (point24.getX() == res2X1);
        CHECK (point24.getY() == res2Y1);

        PolynomGF3 a32("22121"), a34("21121"), a36("20000");
        EllipticCurveGF3 Curve31(module1,a32,a34,a36);
        EllipticPointGF3 point31(Curve31), point32(Curve31), point33(Curve31), point34(Curve31);
	PolynomGF3 x31("21210");
        PolynomGF3 y31("21210");
        point31.setXY(x31,y31);
        point32.setXY(x31,y31);
        PolynomGF3 res3X2("00010");
        PolynomGF3 res3Y2("21222");


        point33.Mul(point31,CC1);
        CHECK (point33.getX() == res3X2);
        CHECK (point33.getY() == res3Y2);


}

/*
	Операция размещения данных в точке
*/
/*TEST(EllipticPointGF3, Generate)
{
	PolynomGF3 module("20000000000000000000000000000010000000000000000000000000000001");
        PolynomGF3 a2("1"), a4("1"), a6("1");
        EllipticCurveGF3 Curve1(module,a2,a4,a6);
        EllipticPointGF3 point1(Curve1), point2(Curve1), point3(Curve1), point4(Curve1);
        point1.Generate();
        CHECK(Curve1.inGroup(point1.getX(),point1.getY()));
        PolynomGF3 mes("121121121121");
        point2.Generate(mes);
        CHECK(Curve1.inGroup(point2.getX(),point2.getY()))
}
TEST(EllipticPointGF3, findRo)
{
   PolynomGF3_m_6 ro;
  PolynomGF3 module1("220001");
  PolynomGF3 a12("0"), a14("2"), a16("1");
  EllipticCurveGF3 Curve11(module1,a12,a14,a16);
  EllipticPointGF3 point11(Curve11);
  PolynomGF3_m_6 b("1","0","0","0","0","0","220001");
  PolynomGF3_m_6 ro1("1", "0", "2", "1", "2", "0","220001");
 // ro = point11.findRo(module1,b);
 // ro.setModule(module1);
 // CHECK(ro == ro1)

}
*/
TEST(EllipticPointGF3, DLK)
{
 	PolynomGF3 module1("220001"),module("10000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
//        PolynomGF3_m_6 b("1","0","0","0","0","0","220001");
        PolynomGF3_m_6 b("1","0","0","0","0","0","10000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

        //PolynomGF3_m_6 ro;
        PolynomGF3 a12("0"), a14("2"), a16("1");
        EllipticCurveGF3 Curve11(module,a12,a14,a16);
        EllipticPointGF3 point1(Curve11),point11(Curve11), point12(Curve11), point13(Curve11), point14(Curve11);
       // ro = point11.findRo(module1,b);
        //point1.Generate();
/*	PolynomGF3 x11("22");
        PolynomGF3 y11("20022");
	PolynomGF3 x21("12012");
        PolynomGF3 y21("2012");
        point11.setXY(x21,y21);
        point12.setXY(x21,y21);
 */
	PolynomGF3 x11("0222112021101002102101121122100201212202002102221110201220210020001102212020122");
        PolynomGF3 y11("0022021022002002011122202201210002201212221002120012220022201001121212002112112100010020210011112012222000021");
	PolynomGF3 x21("0202122001110002202200001022212221121201012201010112012122111110211222012020111011110110211000221120011002001");
        PolynomGF3 y21("1122011020221021120210222211010110112211110000000021111111102012121121212100011221010102012202110211112001122");
        point11.setXY(x21,y21);
        point12.setXY(x21,y21);

	PolynomGF3 x1("22002200210001210020211221020001211002201112221221202212122220100102210100010021");
        PolynomGF3 y1("2202011211101111222010012222002020120100122121211101012212100200020211210021010111201110111022210121022122122");
	PolynomGF3 x2("2021221022011220110121122110212122002121210000101121020221202001022222220201020002200201220122222212010111221");
        PolynomGF3 y2("012122222211001210200220202221212112200000020011102201201200000220200021000102100202221210101001211000022111");
//        point13.Mul(point11,3);
//        point14.Mul(point12,2);
        std::string str;
        PolynomGF3_m_6 ro("0", "0", "2", "1", "2", "0","10000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
        PolynomGF3_m_6 result,result1,r,t1,t("0", "0", "0", "0", "0", "0","10000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"),two("2", "0", "0", "0", "0", "0","20000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000000000000000001");
 //       t.Pow(ro,3);
 //       t1.Mul(ro,two);
 //       r.Add(t,t1);
  //      r.Add(r,two);

         ro.setModule(module);
/*        str  = ro.getA0().ToString();
    str = ro.getA1().ToString();
    str = ro.getA2().ToString();
    str = ro.getA3().ToString();
    str = ro.getA4().ToString();
    str = ro.getA5().ToString();


    str  = r.getA0().ToString();
    str = r.getA1().ToString();
    str = r.getA2().ToString();
    str = r.getA3().ToString();
    str = r.getA4().ToString();
    str = r.getA5().ToString();
  */
   result.setModule(module);
   result1.setModule(module);
   t.setModule(module);
   b.setOne();
   PolynomGF3_m_6 si("0","1","2","1","1","0","10000000000000000000020000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
/*       int m = module1.getNumberBits() - 1;
    AAL::Integer ord(1);
    ord = ord.Pow(3, 6* m);
    ord = ord - 1;
    AAL::Integer two_pow("0"),div,copy_ord;
    copy_ord = ord;
    div = ord%2;
    ord = ord/2;
    str = div.ToString();
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
    T = two_pow;
    s = ord;
    str = s.ToString();
   si.Sqrt(two,module1,s,T); //calc sigma as sqrt(-1)
    si.setModule(module1);
    str = si.getA0().ToString();
    str = si.getA1().ToString();
    str = si.getA2().ToString();
    str = si.getA3().ToString();
    str = si.getA4().ToString();
    str = si.getA5().ToString();
    si.Mul(si,two);
*/
 /*   str = si.getA0().ToString();
    str = si.getA1().ToString();
    str = si.getA2().ToString();
    str = si.getA3().ToString();
    str = si.getA4().ToString();
    str = si.getA5().ToString();
   */
    time_t ts_1,te_1,ts_2,te_2,ts_3,te_3;
    FILE* f;
    f = fopen("aa.txt","a");
    ts_1 = time(&ts_1);
//   result = point1.DLK(point11,point12,ro,si,109,b,module);
   te_1 = time(&te_1);
   te_1 = te_1 - ts_1;
   
   char* string = itoa(te_1,new char[10],10);
   fwrite("DLK GF3^m6\n",1,strlen("DLK GF3^m6\n"),f);
   fwrite(string,1,strlen(string),f);
   fwrite("\n",1,strlen("\n"),f);
 /*   str = result.getA0().ToString();
    str = result.getA1().ToString();
    str = result.getA2().ToString();
    str = result.getA3().ToString();
    str = result.getA4().ToString();
    str = result.getA5().ToString();    */
    ts_2 = time(&ts_2);
//       result1 = point1.DLK(point13,point14,ro,si,109,b,module);
    te_2 = time(&te_2);
    te_2 = te_2 - ts_1;
   string = itoa(te_2,string,int(10));
   fwrite(string,1,strlen(string),f);
    fclose(f);
/*    str = result1.getA0().ToString();
    str = result1.getA1().ToString();
    str = result1.getA2().ToString();
    str = result1.getA3().ToString();
    str = result1.getA4().ToString();
    str = result1.getA5().ToString();
    t.Pow(result,2*3);
    str = t.getA0().ToString();
    str = t.getA1().ToString();
    str = t.getA2().ToString();
    str = t.getA3().ToString();
    str = t.getA4().ToString();
    str = t.getA5().ToString();
    CHECK(t == result1);    */
	delete string;
}
