/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/IntegerBinomEllipticcurves.h"
using namespace AAL;

TEST(IntegerBinomEllipticCurve,MainConstructor)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinomModulePolynom otherModPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        IntegerBinom a(AAL::Integer("3"), AAL::Integer("5"), modPol);
        IntegerBinom b(AAL::Integer("3"), AAL::Integer("5"), otherModPol);

        try
        {
                IntegerBinomEllipticCurve curve(a, b);
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}

TEST(IntegerBinomEllipticCurve,EqualOperator)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinomModulePolynom otherModPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("7"));
        IntegerBinom a(AAL::Integer("3"), AAL::Integer("5"), modPol);
        IntegerBinom b(AAL::Integer("3"), AAL::Integer("5"), otherModPol);

        IntegerBinomEllipticCurve curve1(a, a), curve2(curve1), curve3;
        curve3 = curve1;

        CHECK(curve1 == curve2 && curve1 == curve3);
        IntegerBinomEllipticCurve curve4(b, b);
        CHECK(curve1 != curve4);
}
TEST(IntegerBinomEllipticCurve,InGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom zero(AAL::Integer("0"), AAL::Integer("0"), modPol);
        //IntegerBinom a(AAL::Integer("-3"), AAL::Integer("0"), modPol); // -3 не подходит так как не принадлежит GF(p)
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 - 3X или Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        CHECK(curve.inGroup(zero, zero));

        IntegerBinom x1(AAL::Integer("0"), AAL::Integer("5"), modPol);
        IntegerBinom y1(AAL::Integer("2"), AAL::Integer("9"), modPol);
        CHECK(curve.inGroup(x1, y1));

        IntegerBinom x2(AAL::Integer("0"), AAL::Integer("5"), modPol);
        IntegerBinom y2(AAL::Integer("2"), AAL::Integer("9"), modPol);
        CHECK(curve.inGroup(x2, y2));

        IntegerBinom x3(AAL::Integer("6"), AAL::Integer("7"), modPol);
        IntegerBinom y3(AAL::Integer("5"), AAL::Integer("4"), modPol);
        CHECK(curve.inGroup(x3, y3));
}
TEST(IntegerBinomEllipticPoint,EqualOperator)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom zero(AAL::Integer("0"), AAL::Integer("0"), modPol);
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x1(AAL::Integer("0"), AAL::Integer("5"), modPol);
        IntegerBinom y1(AAL::Integer("2"), AAL::Integer("9"), modPol);
        IntegerBinomEllipticPoint point1(curve);

        point1.setXY(x1, y1);

        IntegerBinomEllipticPoint point2(point1), point3;
        point3 = point1;
        CHECK(point1 == point2 && point1 == point3);
}
TEST(IntegerBinomEllipticPoint,Negate)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom zero(AAL::Integer("0"), AAL::Integer("0"), modPol);
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x(AAL::Integer("0"), AAL::Integer("5"), modPol);
        IntegerBinom y(AAL::Integer("2"), AAL::Integer("9"), modPol);
        IntegerBinomEllipticPoint point(curve);

        point.setXY(x, y);

        IntegerBinomEllipticPoint negatePoint(curve);
        negatePoint.setXY(x, y.Negate());

        CHECK(point.Negate() == negatePoint);
}
TEST(IntegerBinomEllipticPoint,Add)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom zero(AAL::Integer("0"), AAL::Integer("0"), modPol);
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x1(AAL::Integer("0"), AAL::Integer("5"), modPol);
        IntegerBinom y1(AAL::Integer("2"), AAL::Integer("9"), modPol);
        IntegerBinomEllipticPoint point1(curve);
        point1.setXY(x1, y1);

        IntegerBinomEllipticPoint point2(curve);
        IntegerBinom x2(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y2(AAL::Integer("8"), AAL::Integer("0"), modPol);
        point2.setXY(x2, y2);

        IntegerBinomEllipticPoint rightResPoint(curve);
        IntegerBinom x3(AAL::Integer("1"), AAL::Integer("6"), modPol);
        IntegerBinom y3(AAL::Integer("8"), AAL::Integer("3"), modPol);
        rightResPoint.setXY(x3, y3);

        IntegerBinomEllipticPoint res(curve);

        CHECK(res.Add(point1, point2) == rightResPoint);
}
TEST(IntegerBinomEllipticPoint,Add2)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom zero(AAL::Integer("0"), AAL::Integer("0"), modPol);
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x1(AAL::Integer("0"), AAL::Integer("3"), modPol);
        IntegerBinom y1(AAL::Integer("9"), AAL::Integer("9"), modPol);
        IntegerBinomEllipticPoint point1(curve);
        point1.setXY(x1, y1);

        IntegerBinomEllipticPoint point2(curve);
        IntegerBinom x2(AAL::Integer("5"), AAL::Integer("7"), modPol);
        IntegerBinom y2(AAL::Integer("4"), AAL::Integer("5"), modPol);
        point2.setXY(x2, y2);

        IntegerBinomEllipticPoint rightResPoint(curve);
        IntegerBinom x3(AAL::Integer("7"), AAL::Integer("1"), modPol);
        IntegerBinom y3(AAL::Integer("9"), AAL::Integer("0"), modPol);
        rightResPoint.setXY(x3, y3);

        IntegerBinomEllipticPoint res(curve);

        res.Add(point1, point2);

        CHECK(!res.isInfinite()  && res == rightResPoint);
}
TEST(IntegerBinomEllipticPoint,Double)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x(AAL::Integer("0"), AAL::Integer("5"), modPol);
        IntegerBinom y(AAL::Integer("2"), AAL::Integer("9"), modPol);
        IntegerBinomEllipticPoint point(curve);
        point.setXY(x, y);

        IntegerBinomEllipticPoint rightResPoint(curve);
        IntegerBinom x3(AAL::Integer("0"), AAL::Integer("0"), modPol);
        IntegerBinom y3(AAL::Integer("0"), AAL::Integer("0"), modPol);
        rightResPoint.setXY(x3, y3);

        IntegerBinomEllipticPoint res(curve);

        CHECK(res.Double(point) == rightResPoint);
}
TEST(IntegerBinomEllipticPoint,Double2)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinomEllipticPoint point(curve);
        point.setXY(x, y);

        IntegerBinomEllipticPoint rightResPoint(curve);
        IntegerBinom x3(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y3(AAL::Integer("3"), AAL::Integer("0"), modPol);
        rightResPoint.setXY(x3, y3);

        IntegerBinomEllipticPoint res(curve);

        CHECK(res.Double(point) == rightResPoint);
}
TEST(IntegerBinomEllipticPoint,Mul)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinomEllipticPoint point(curve);
        point.setXY(x, y);

        IntegerBinomEllipticPoint rightResPoint(curve);
        IntegerBinom x3(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y3(AAL::Integer("3"), AAL::Integer("0"), modPol);
        rightResPoint.setXY(x3, y3);

        IntegerBinomEllipticPoint res1(curve), res2;

        AAL::Integer two("2"), three("3");

        CHECK(res1.Mul(point, two) == rightResPoint && res2.Mul(point, three).isInfinite());

}
TEST(IntegerBinomEllipticPoint,Ord)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x1(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y1(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinomEllipticPoint point1(curve);
        point1.setXY(x1, y1);

        AAL::Integer three("3");

        CHECK(point1.Order() == three);
}
TEST(IntegerBinomEllipticCurve,CreateGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        std::vector<IntegerBinomEllipticPoint> group(curve.CreateGroup());


        CHECK(group.size() == 144); 
        
        for(std::vector<IntegerBinomEllipticPoint>::iterator it = group.begin(); it != group.end(); ++it)
        {
                CHECK((*it).isInfinite() || curve.inGroup((*it).getX(), (*it).getY()));
        }          
}
TEST(IntegerBinomEllipticCurve,CreateSpinningGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        AAL::Integer three("3");
        std::vector<IntegerBinomEllipticPoint> group(curve.CreateSpinningGroup(three));


        CHECK(group.size() == 9);

        for(std::vector<IntegerBinomEllipticPoint>::iterator it = group.begin(); it != group.end(); ++it)
        {
                CHECK((*it).isInfinite() || (*it).Order() == three);
        }
}
TEST(IntegerBinomEllipticCurve,CreateMultipliedGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        AAL::Integer three("3");
        std::vector<IntegerBinomEllipticPoint> group(curve.CreateMultipliedGroup(three));


        CHECK(group.size() == 16);
}
/*#include <iostream>
TEST(IntegerBinomEllipticCurve,CreateFactorGroup)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        AAL::Integer three("3");
        std::vector<std::vector<IntegerBinomEllipticPoint> > factorGroup(curve.CreateFactorGroup(three));


        CHECK(factorGroup.size() == 9);

        for(std::vector<std::vector<IntegerBinomEllipticPoint> >::iterator subGroupIt = factorGroup.begin(); subGroupIt != factorGroup.end(); ++subGroupIt)
        {
                std::vector<IntegerBinomEllipticPoint> subGroup(*subGroupIt);
                for(std::vector<IntegerBinomEllipticPoint>::iterator it = subGroup.begin(); it != subGroup.end(); ++it)
                {
                        std::cout << (*it).ToString() << std::endl;                        
                }

                std::cout << std::endl;
        }
        
}
#include <iostream>
TEST(IntegerBinomEllipticCurve,ToTexString)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinom x(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinomEllipticPoint point(curve), infinity;
        point.setXY(x, y);

        std::cout << infinity.ToTexString() << std::endl;
        std::cout << point.ToTexString() << std::endl;
}*/

TEST(IntegerBinomEllipticCurve,Distortion)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve(a, b);

        IntegerBinomEllipticPoint point1(curve);
        IntegerBinom x1(AAL::Integer("9"), AAL::Integer("0"), modPol);
        IntegerBinom y1(AAL::Integer("8"), AAL::Integer("0"), modPol);
        point1.setXY(x1, y1);

        point1.Distortion();
        CHECK(point1.getX().getA().ToString() == "2" && point1.getX().getB().isZero() &&
        point1.getY().getB().ToString() == "8" && point1.getY().getA().isZero());


        IntegerBinom x2(AAL::Integer("0"), AAL::Integer("5"), modPol);
        IntegerBinom y2(AAL::Integer("2"), AAL::Integer("9"), modPol);
        IntegerBinomEllipticPoint point2(curve);
        point2.setXY(x2, y2);

        try
        {
                point2.Distortion();
                CHECK(false);        
        }
        catch(Exception *E)
        {
                CHECK(true);
        }

}
TEST(IntegerBinomEllipticCurve,Generate)
{
        IntegerBinomModulePolynom modPol(AAL::Integer("1"),AAL::Integer("0"),AAL::Integer("11"));
        IntegerBinom a1(AAL::Integer("8"), AAL::Integer("0"), modPol);
        IntegerBinom b1(AAL::Integer("0"), AAL::Integer("0"), modPol);

        // Y^2 = X^3 + 8X
        IntegerBinomEllipticCurve curve1(a1, b1);

        IntegerBinomEllipticPoint point1(curve1);

        point1.Generate();
        CHECK(curve1.inGroup(point1.getX(), point1.getY()));

        IntegerBinom a2(AAL::Integer("8"), AAL::Integer("1"), modPol);
        IntegerBinom b2(AAL::Integer("0"), AAL::Integer("0"), modPol);

        IntegerBinomEllipticCurve curve2(a2, b2);

        IntegerBinomEllipticPoint point2(curve2);

        try
        {
                point2.Generate();
                CHECK(false);
        }
        catch(Exception *E)
        {
                CHECK(true);
        }
}
