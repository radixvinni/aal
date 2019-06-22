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
#include "./AAF/AAL/PolynomGF7_m14.h"
#include "./AAF/AAL/Matrix.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include "./AAF/AAL/FactorizationAlgorithms.h"
#include <set>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace AAL;

/*
	Конструкторы класса PolynomGF3_m_6
*/

TEST(PolynomGF7_m14, EmptyConstructor)
{
	PolynomGF7_m14 p;
	CHECK(p.isZero());
}

TEST(PolynomGF7_m14, CopyConstructor)
{
	PolynomGF7_m14 p("0", "1", "2", "3", "4", "5","6","0","1","2","3","4","5","6","1101");
    PolynomGF7_m14 pp(p);
	CHECK(p==pp);
}

TEST(PolynomGF7_m14, StringConstructor)
{
	PolynomGF7_m14 p1("0", "0", "0", "0", "0", "0","0","0","0","0","0","0","0","0","1101"), p2("", "", "", "", "", "","","","","","","","","","1101");
	CHECK(p1.isZero());
	CHECK(p2.isZero());
}

TEST(PolynomGF7_m14, Add)
{
        PolynomGF7_m14 a("504", "330", "356", "134", "415", "125","616","102","624","323","625","112","661","164","1101"),b("313", "564", "434", "010", "016", "605","024","562","506","520","420","311","055","246","1101"),c,c2;
        PolynomGF7_m14 d1("110", "124", "013", "144", "424", "023","633","664","423","143","345","423","646","333","1101");
        PolynomGF7_m14 a1("161","444","014","460","611","414","303","663","204","545","622","524","652","113","1101"),b1("241","614","055","462","534","322","623","010","333","660","322","246","010","201","1101"),c1,c3;
        PolynomGF7_m14 d("332","351","062","152","445","036","226","603","530","435","244","063","662","314","1101");
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

TEST(PolynomGF7_m14, Mul)
{

        PolynomGF7_m14 a("030","134","012","501","123","562","326","402","436","315","610","143","620","634","1101"),b("101","626","424","552","611","061","616","234","611","656","365","406","341","123","1101"),c,c2;
        PolynomGF7_m14 d("160","502","463","462","200","446","110","642","603","421","423","504","151","230","1101");
        PolynomGF7_m14 a1("100","300","000","000","000","000","000","000","000","000","000","000","000","000","1101"),b1("200","100","000","000","000","000","000","000","000","000","000","000","000","000","1101");
        PolynomGF7_m14 d1("200","000","300","000","000","000","000","000","000","000","000","000","000","000","1101");
        PolynomGF7 m("1101");
       // PolynomGF7_m_14 a1("0","0","0","0","0","0","0","0","0","0","0","0","1","0","1101"),b1("0","0","0","0","0","0","0","0","0","0","0","0","1","0","1101");
       // PolynomGF7_m_14 d1("0","0","0","0","0","0","0","0","0","0","3","0","1","0","1101");
        c._module =  m;
        CHECK(a*b == b*a);
        c2 = a * b;
        CHECK(c.Mul(a1,b1) == d1);
        CHECK((a + b)*c == (a*c + b*c));
        CHECK(c2 == d)
        b *= a;
        CHECK(b == d);
}
TEST(PolynomGF7_m14, Seven)
{
        PolynomGF7_m14 a("030","134","012","501","123","562","326","402","436","315","610","143","620","634","1101"),b("101","626","424","552","611","061","616","234","611","656","365","406","341","123","1101"),c("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101"),c2("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101");
        PolynomGF7_m14 d("220","046","252","226","406","260","650","513","365","305","605","615","212","233","1101"),c1("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101"),c3("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101");
        PolynomGF7_m14 a1("441","341","050","315","036","214","615","525","121","222","012","643","361","622","1101"),b1("424","250","561","651","464","643","315","112","660","226","601","514","526","440","1101");
        d = a1*a1*a1*a1*a1*a1*a1;
        std::string s =   d.ToString();
          CHECK(c.SevenFast(a1) == d);
          CHECK(c.Seven(a1) == d);

}

TEST(PolynomGF7_m14, Pow)
{
        PolynomGF7_m14 a("030","134","012","501","123","562","326","402","436","315","610","143","620","634","1101"),b("101","626","424","552","611","061","616","234","611","656","365","406","341","123","1101"),c("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101"),c2("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101");
        PolynomGF7_m14 d("220","046","252","226","406","260","650","513","365","305","605","615","212","233","1101"),c1("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101"),c3("0","0","0","0","0","0","0","0","0","0","0","0","0","0","1101");
        PolynomGF7_m14 a1("441","341","050","315","036","214","615","525","121","222","012","643","361","622","1101"),b1("424","250","561","651","464","643","315","112","660","226","601","514","526","440","1101");
        PolynomGF7_m14 a3("165","160","166","242","644","503","363","224","606","506","455","422","065","423","1101");
        PolynomGF7_m14 d1("514","342","125","165","006","022","610","624","152","210","303","405","401","521","1101");
          CHECK(c.Pow(a3,AAL::Integer(7)) == d1);

//          CHECK(c2.Pow(a,6) == a*a*a*a*a*a);
//          CHECK(c3.Pow(a,7) == a*a*a*a*a*a*a);
          CHECK(c1.Pow(a,AAL::Integer(5)) == a*a*a*a*a);

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
TEST(PolynomGF7_m14, Generate)
{
  PolynomGF7_m14 u;
  PolynomGF7 mod("1101");
  u.Generate(mod);
  std::string s =   u.getA0().ToString();
  s =   u.getA1().ToString();
  s =   u.getA2().ToString();
  s =   u.getA3().ToString();
  s =   u.getA4().ToString();
  s =   u.getA5().ToString();
  s =   u.getA6().ToString();
  s =   u.getA7().ToString();
  s =   u.getA8().ToString();
  s =   u.getA9().ToString();
  s =   u.getA10().ToString();
  s =   u.getA11().ToString();
  s =   u.getA12().ToString();
  s =   u.getA13().ToString();

  CHECK(true);
}
//-------------------------------------------------------------------------------
TEST(PolynomGF7_m14, LegendreSymbol)
{
  PolynomGF7_m14 c1,a1("130","434","512","501","111","555","326","402","436","221","664","041","620","634","1101"),a("242","340","545","624","413","310","230","343","052","622","230","326","340","503","1101");
   PolynomGF7_m14 one("100","000","000","000","000","000","000","000","000","000","000","000","000","000","1101");
  PolynomGF7_m14 two("600","000","000","000","000","000","000","000","000","000","000","000","000","000","1101");
  PolynomGF7 mod("1101");
//  CHECK(c1.LegendreSymbol(a1,mod) == two);
//  CHECK(c1.LegendreSymbol(a,mod) == one);
}

//--------------------------------------------------------------------------------------
TEST(PolynomGF7_m14, Sqrt)
{
        PolynomGF7_m14 a("242","340","545","624","413","310","230","343","052","622","230","326","340","503","1101"),c,c2;
        PolynomGF7_m14 d1("130","434","512","501","111","555","326","402","436","221","664","041","620","634","1101");
        PolynomGF7_m14 six("600","000","000","000","000","000","000","000","000","000","000","000","000","000","1101");
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
// c.Sqrt(six,d1,mod,s,T);

 // c.Mul(c,six);
 // CHECK(c*c == six);

//  c.Sqrt(a,d1,mod,s,T);
///  c2.Pow(c,2);
 // CHECK(c2.Pow(c,2) == a);
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
*/
TEST(PolynomGF7_m14, getRo)
{
        PolynomGF7_m14 one("100","000","000","000","000","000","000","000","000","000","000","000","000","000","1101"),m,c,c1;
        PolynomGF7 module1("1101");
        PolynomGF7_m14 a1("400","000","000","000","000","000","000","000","000","000","000","000","000","000","1101"),d11("664","451","125","333","160","204","600","444","350","524","622","242","120","525","1101");

 //  CHECK(c1.findRo(a1,module1) == d11);

    std::string s = c1.ToString();
}
TEST(PolynomGF7_m14, DLK_1)
{
        PolynomGF7_m14 si("20000000000000000000000000000","20000000000000000000000000000","00000000000000000000000000000","40000000000000000000000000000","30000000000000000000000000000","50000000000000000000000000000","60000000000000000000000000000","50000000000000000000000000000","10000000000000000000000000000","50000000000000000000000000000","10000000000000000000000000000","10000000000000000000000000000","10000000000000000000000000000","00000000000000000000000000000","130000000000000000000000000001");
        PolynomGF7_m14 ro("60000000000000000000000000000","60000000000000000000000000000","60000000000000000000000000000","60000000000000000000000000000","40000000000000000000000000000","30000000000000000000000000000","60000000000000000000000000000","00000000000000000000000000000","50000000000000000000000000000","00000000000000000000000000000","10000000000000000000000000000","10000000000000000000000000000","60000000000000000000000000000","00000000000000000000000000000","130000000000000000000000000001");
        PolynomGF7_m14 b("60000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","00000000000000000000000000000","130000000000000000000000000001");
        PolynomGF7 module1("130000000000000000000000000001");
        PolynomGF7 x_3("34544545236455644405550364500"),y_3("60545430652525140155511214106"),x_1("34544545236455644405550364500"),y_1("60545430652525140155511214106"),x_2("36642041266504060605544346302"),y_2("10504160301562612320416406422");
        PolynomGF7 al_3("55266424423402415216264612605"), bt_3("10413016610004364634443235432"),al_1("55266424423402415216264612605"), bt_1("10413016610004364634443235432"), al_2("36642041266504060605544346302"), bt_2("60203610406215165450361301355");
        PolynomGF7 minus("60000000000000000000000000000");
        PolynomGF7 al0_1_m, x0_1_m;
       // al0_1_m.Mul(al0_1,minus);
        //x0_1_m.Mul(x0_1,minus);
     std::vector<PolynomGF7> vector_x_1,vector_y_1,vector_al_1,vector_bt_1;
        vector_x_1.push_back(x_1);
        vector_y_1.push_back(y_1);
//       vector_x_1.push_back(x_2);
//       vector_y_1.push_back(y_2);
//        vector_x_1.push_back(x_3);
//       vector_y_1.push_back(y_3);

        vector_al_1.push_back(al_1);
        vector_bt_1.push_back(bt_1);
//        vector_al_1.push_back(al_2);
//        vector_bt_1.push_back(bt_2);
//        vector_al_1.push_back(al_3);
//        vector_bt_1.push_back(bt_3);

        std::string str = "";
           std::string s = "";
            std::string str1,str2,str3,str4;
        PolynomGF7_m14 result,result_1,result_2, result_3;
        time_t ts_1,te_1,ts_2,te_2,ts_3,te_3;
    FILE* f;
    f = fopen("a.txt","a");
    ts_1 = time(&ts_1);
//   result_2 = result_2.DLK(vector_x_1,vector_y_1,vector_al_1,vector_bt_1,ro,si,29,b,module1);
        te_1 = time(&te_1);
   te_1 = te_1 - ts_1;
   char string[200];
   sprintf(string ,"%d\n",te_1);
   fwrite("DLK GF7^m14\n",1,strlen("DLK GF7^m14\n"),f);
   fwrite(string,1,strlen(string),f);
 //  fwrite("\n",1,strlen("\n"),f);
 fclose(f);
}
TEST(PolynomGF7_m14, DLK)
{
/*        PolynomGF7_m14 one("100","000","000","000","000","000","000","000","000","000","000","000","000","000","1101"),m,c,c1;
        PolynomGF7_m14 si("200","200","000","400","300","500","600","500","100","500","100","100","100","000","1101");
        PolynomGF7_m14 ro("600","600","600","600","400","300","600","000","500","000","100","100","600","000","1101");
        PolynomGF7_m14 b("600","000","000","000","000","000","000","000","000","000","000","000","000","000","1101");
        PolynomGF7_m14 r("330","001","413","016","211","324","046","321","025","362","016","622","542","512","1101");
        PolynomGF7_m14 r_1("564","254","362","510","333","654","131","505","433","351","516","523","625","024","1101");
        PolynomGF7_m14 r_0("165","160","166","242","644","503","363","224","606","506","455","422","065","423","1101");
        PolynomGF7_m14 r_3("514","342","125","165","006","022","610","624","152","210","303","405","401","521","1101");

        PolynomGF7 module1("1101");
        PolynomGF7 al0_1("064"),bt0_1("520"),x0_1("454"),y0_1("456");
        PolynomGF7 al0("352"),al1("634"),bt0("255"),bt1("614"),x0("552"),x1("556"),x2("016"),y0("522"),y1("544"),y2("202");
        PolynomGF7 al0_3("634"),bt0_3("614"),x0_3("261"),y0_3("562");

     std::vector<PolynomGF7> vector_x_2,vector_y_2,vector_al_2,vector_bt_2;
        vector_x_2.push_back(x0_3);
        vector_y_2.push_back(y0_3);
        vector_al_2.push_back(al0_3);
        vector_bt_2.push_back(bt0_3);
          std::string str = "";
           std::string s = "";
            std::string str1,str2,str3,str4;
               PolynomGF7_m14 result,result_1,result_2, result_3;

            s = r_3.ToString();
    time_t ts_1,te_1,ts_2,te_2,ts_3,te_3;
    FILE* f;
    f = fopen("a.txt","a");
    ts_1 = time(&ts_1);

   result_3 = result_3.DLK(vector_x_2,vector_y_2,vector_al_2,vector_bt_2,ro,si,3,b,module1);
      te_1 = time(&te_1);
   te_1 = te_1 - ts_1;
   char string[200];
   sprintf(string ,"%d\n",te_1);
   fwrite("DLK GF7^m14\n",1,strlen("DLK GF7^m14\n"),f);
   fwrite(string,1,strlen(string),f);
 //  fwrite("\n",1,strlen("\n"),f);

//    str4 = result_3.ToString();
     CHECK(r_3== result_3);

        std::vector<PolynomGF7> vector_x,vector_y,vector_al,vector_bt;
        vector_x.push_back(x0);
        vector_x.push_back(x1);
        vector_x.push_back(x2);

        vector_y.push_back(y0);
        vector_y.push_back(y1);
        vector_y.push_back(y2);

        vector_al.push_back(al0);
        vector_al.push_back(al1);

        vector_bt.push_back(bt0);
        vector_bt.push_back(bt1);

     c1.Pow(r_0,1150);
    str = c1.ToString();

    s = r_1.ToString();
    ts_2 = time(&ts_1);

   result = result.DLK(vector_x,vector_y,vector_al,vector_bt,ro,si,3,b,module1);
      te_2 = time(&te_1);
      
   te_2 = te_2 - ts_2;
   sprintf(string ,"%d\n",te_2);
   fwrite(string,1,strlen(string),f);
//   fwrite("\n",1,strlen("\n"),f);

   result._module = module1;
  //  str1 = result.ToString();
     CHECK(result == r_1);

    s = r_1.ToString();
    ts_3 = time(&ts_1);

   result_1 = result_1.DLK(vector_al,vector_bt, vector_x,vector_y ,ro,si,3,b,module1);
      te_3 = time(&te_3);
   te_3 = te_3 - ts_3;
   sprintf(string ,"%d\n",te_3);
   fwrite(string,1,strlen(string),f);

   fclose(f);
    //str2 = result_1.ToString();
     CHECK(r_1 == result_1);

     std::vector<PolynomGF7> vector_x_1,vector_y_1,vector_al_1,vector_bt_1;
        vector_x_1.push_back(x0_1);
        vector_y_1.push_back(y0_1);
        vector_al_1.push_back(al0_1);
        vector_bt_1.push_back(bt0_1);

            s = r.ToString();
   result_2 = result_2.DLK(vector_x_1,vector_y_1,vector_al_1,vector_bt_1,ro,si,3,b,module1);

    str3 = result_2.ToString();
     CHECK(r == result_2);

*/
}




