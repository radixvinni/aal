/*
        MPEI Algebraic Abstractions Library,
        2007-2011,
        Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "IntegerBinomEllipticcurves.h"
#include "Converter.h"
#include "Ellipticcurves.h"
#include <algorithm>
namespace AAL
{
//****************************  Класс Эллиптических кривых над GF(p^2)   ************************
//*********************************      Конструкторы       *************************************
        IntegerBinomEllipticCurve::IntegerBinomEllipticCurve()
        {
                _a = new IntegerBinom();
                _b = new IntegerBinom();
        }
        IntegerBinomEllipticCurve::IntegerBinomEllipticCurve(const IntegerBinom & a, const IntegerBinom & b)
        {
                if(a.getModulePolynom() != b.getModulePolynom())
                        throw new Exception("Коэффициенты кривой должны принадлежать одному полю");

                _a = new IntegerBinom(a);
                _b = new IntegerBinom(b);
        }
        IntegerBinomEllipticCurve::IntegerBinomEllipticCurve(const IntegerBinomEllipticCurve & curve)
        {
                _a = new IntegerBinom(*curve._a);
                _b = new IntegerBinom(*curve._b);
        }
        IntegerBinomEllipticCurve::~IntegerBinomEllipticCurve()
        {
                delete _a, _b;
        }
//***********************************************************************************************
//*****************************        Методы акцепторы        **********************************
        const IntegerBinomModulePolynom& IntegerBinomEllipticCurve::getModulePolynom() const
        {
                return _a->getModulePolynom();
        }
        const Integer& IntegerBinomEllipticCurve::getModule() const
        {
                return getModulePolynom().getModule();
        }
    const IntegerBinom& IntegerBinomEllipticCurve::getA() const
        {
                return *_a;
        }
    const IntegerBinom& IntegerBinomEllipticCurve::getB() const
        {
                return *_b;
        }

        IntegerBinomEllipticCurve& IntegerBinomEllipticCurve::operator=(const IntegerBinomEllipticCurve &eCurve)
        {
                *_a = *eCurve._a;
                *_b = *eCurve._b;

                return *this;
        }
//***********************************************************************************************
//********************************      Операции сравнения      *********************************
        bool operator==(const IntegerBinomEllipticCurve &eCurve1, const IntegerBinomEllipticCurve &eCurve2)
        {
                return *eCurve1._a == *eCurve2._a && *eCurve1._b == *eCurve2._b;
        }
        bool operator!=(const IntegerBinomEllipticCurve &eCurve1, const IntegerBinomEllipticCurve &eCurve2)
        {
                return !(eCurve1 == eCurve2);
        }
//***********************************************************************************************
//*************************        Принадлежность точки к кривой      ***************************
        bool IntegerBinomEllipticCurve::inGroup(const IntegerBinom &x, const IntegerBinom &y) const
        {
                if(getModulePolynom() != x.getModulePolynom() || getModulePolynom() != y.getModulePolynom())
                        return false;

                return getLeftSide(y) == getRightSide(x);
        }
        IntegerBinom IntegerBinomEllipticCurve::getLeftSide(const IntegerBinom &y) const
        {
                IntegerBinom result(y);
                Integer two("2");
                result.Pow(result, two);

                return result;
        }
        IntegerBinom IntegerBinomEllipticCurve::getRightSide(const IntegerBinom &x) const
        {
                IntegerBinom result(x), temp(x);
                Integer three("3");
                result.Pow(result, three);
                temp.Mul(temp, *_a);
                temp.Add(temp, *_b);
                result.Add(result, temp);

                return result;
        }
//***********************************************************************************************
//*************************        Создание Групп                     ***************************
        uint IntegerBinomEllipticCurve::getMaxModuleForGroupCreation() const
        {
                return 20;
        }
        bool IntegerBinomEllipticCurve::isGroupSmallEnoughForGroupCreation() const
        {
                if(getModule() > getMaxModuleForGroupCreation())
                        return false;
                return true;
        }
        // простой перебор всех возможных вариантов
        std::vector<IntegerBinomEllipticPoint> IntegerBinomEllipticCurve::CreateGroup() const
        {
                if(!isGroupSmallEnoughForGroupCreation())
                        throw new Exception("Модуль должен быть меньше " +Integer(getMaxModuleForGroupCreation()).ToString());

                std::vector<IntegerBinomEllipticPoint> group;

                IntegerBinomEllipticPoint infinity(*this);
                group.push_back(infinity);

                Integer module(getModule());

                for(Integer a1("0"); a1 < module; a1++)
                {
                  for(Integer b1("0"); b1 < module; b1++)
                  {
                    for(Integer a2("0"); a2 < module; a2++)
                    {
                      for(Integer b2("0"); b2 < module; b2++)
                      {
                        IntegerBinom x(a1, b1, getModulePolynom());
                        IntegerBinom y(a2, b2, getModulePolynom());
                        if(inGroup(x,y))
                        {
                                IntegerBinomEllipticPoint point(*this);
                                point.setXY(x,y);
                                group.push_back(point);
                        }
                      }
                    }
                  }
                }

                return group;
        }
        std::vector<IntegerBinomEllipticPoint> IntegerBinomEllipticCurve::CreateSpinningGroup(const Integer &n) const
        {
                if(n.isZero())
                        throw new Exception("n не должно быть равно 0");

                std::vector<IntegerBinomEllipticPoint> group(CreateGroup());

                if((n >= group.size()) || (group.size() % n) != 0)
                        throw new Exception("n должно делить порядок группы");

                return CreateSpinningGroup(n, group);
        }
        std::vector<IntegerBinomEllipticPoint> IntegerBinomEllipticCurve::CreateSpinningGroup(const Integer &n,
                                                                                std::vector<IntegerBinomEllipticPoint> &group) const
        {
                std::vector<IntegerBinomEllipticPoint> resgroup;

                IntegerBinomEllipticPoint infinity(*this);
                resgroup.push_back(infinity);

                for(std::vector<IntegerBinomEllipticPoint>::iterator it = group.begin();it != group.end();++it)
                {
                        if((*it).Order() == n)
                        {
                                resgroup.push_back((*it));
                        }
                }

                return resgroup;
        }
        std::vector<IntegerBinomEllipticPoint> IntegerBinomEllipticCurve::CreateMultipliedGroup(const Integer &n) const
        {
                std::vector<IntegerBinomEllipticPoint> group(CreateGroup());
                return CreateMultipliedGroup(n, group);
        }
        std::vector<IntegerBinomEllipticPoint> IntegerBinomEllipticCurve::CreateMultipliedGroup(const Integer &n, std::vector<IntegerBinomEllipticPoint> &group) const
        {
                std::vector<IntegerBinomEllipticPoint> resgroup;

                for(std::vector<IntegerBinomEllipticPoint>::iterator it = group.begin();it != group.end();++it)
                {
                        IntegerBinomEllipticPoint point(*it);
                        point.Mul(point, const_cast<Integer &>(n));
                        if(!isInMultitude(point, resgroup))
                        {
                                resgroup.push_back(point);
                        }
                }

                return resgroup;
        }
        bool IntegerBinomEllipticCurve::isInMultitude(IntegerBinomEllipticPoint & point, std::vector<IntegerBinomEllipticPoint> &multitude) const
        {
                std::vector<IntegerBinomEllipticPoint>::iterator begin = multitude.begin();
                std::vector<IntegerBinomEllipticPoint>::iterator end = multitude.end();

                return std::find(begin, end, point) != end;
        }

        std::vector<std::vector<IntegerBinomEllipticPoint> >  IntegerBinomEllipticCurve::CreateFactorGroup(const Integer &n) const
        {
                if(n.isZero())
                        throw new Exception("n не должно быть равно 0");

                std::vector<IntegerBinomEllipticPoint> group(CreateGroup());

                if((n >= group.size()) || (group.size() % n) != 0)
                        throw new Exception("n должно делить порядок группы");

                return CreateFactorGroup(n, group);
        }
        std::vector<std::vector<IntegerBinomEllipticPoint> >  IntegerBinomEllipticCurve::CreateFactorGroup(const Integer &n, std::vector<IntegerBinomEllipticPoint> &group) const
        {
                std::vector<std::vector<IntegerBinomEllipticPoint> > factorGroup;

                std::vector<IntegerBinomEllipticPoint> spinningGroup(CreateSpinningGroup(n, group));
                std::vector<IntegerBinomEllipticPoint> multipliedGroup(CreateMultipliedGroup(n, group));

                for(std::vector<IntegerBinomEllipticPoint>::iterator it = spinningGroup.begin(); it != spinningGroup.end(); ++it)
                {
                        std::vector<IntegerBinomEllipticPoint> subGroup(AddToMultitude((*it), multipliedGroup));
                        factorGroup.push_back(subGroup);
                }

                return factorGroup;
        }

        std::vector<IntegerBinomEllipticPoint> IntegerBinomEllipticCurve::AddToMultitude(IntegerBinomEllipticPoint & point, std::vector<IntegerBinomEllipticPoint> & multitude) const
        {
                std::vector<IntegerBinomEllipticPoint>  newMultitude;

                for(std::vector<IntegerBinomEllipticPoint>::iterator it = multitude.begin(); it != multitude.end(); ++it)
                {
                        IntegerBinomEllipticPoint newPoint(*it);
                        newPoint.Add(newPoint, point);
                        newMultitude.push_back(newPoint);
                }

                return newMultitude;
        }

//***********************************************************************************************
//**************************    Операция работы со строками        ******************************
        std::string IntegerBinomEllipticCurve::FactorToTexString(std::vector<std::vector<IntegerBinomEllipticPoint> > & factor)
        {
                return Converter::FactorToTexString(factor);
        }
        std::string IntegerBinomEllipticCurve::MultitudeToTexString(std::vector<IntegerBinomEllipticPoint> & multitude)
        {
                return Converter::MultitudeToTexString(multitude);
        }
//***********************************************************************************************
//***********************************************************************************************

//**********************************  Класс точка эллиптичиской кривой  *************************
//********************************      Конструкторы       **************************************
    IntegerBinomEllipticPoint::IntegerBinomEllipticPoint()
    {
        _curve = new IntegerBinomEllipticCurve();
        _x = new IntegerBinom();
        _y = new IntegerBinom();
        _infinite = true;
    }

        IntegerBinomEllipticPoint::IntegerBinomEllipticPoint(const IntegerBinomEllipticCurve &eCurve)
    {
        _curve = new IntegerBinomEllipticCurve(eCurve);
        _x = new IntegerBinom();
                _x->setModulePolynom(eCurve.getModulePolynom());
        _y = new IntegerBinom();
                _y->setModulePolynom(eCurve.getModulePolynom());
        _infinite = true;
    }
        IntegerBinomEllipticPoint::IntegerBinomEllipticPoint(const IntegerBinomEllipticPoint &ePoint)
    {
        _curve = new IntegerBinomEllipticCurve(*ePoint._curve);
        _x = new IntegerBinom(*ePoint._x);
        _y = new IntegerBinom(*ePoint._y);
        _infinite = ePoint._infinite;
    }
        IntegerBinomEllipticPoint::~IntegerBinomEllipticPoint()
    {
        delete _curve, _x, _y;
    }

//***********************************************************************************************
//****************************       Методы акцепторы        ************************************
        const IntegerBinomEllipticCurve& IntegerBinomEllipticPoint::getCurve()
        {
                return *_curve;
        }
        const IntegerBinom& IntegerBinomEllipticPoint::getX()
        {
                if(!isInfinite())return *_x;
                throw new Exception("Точка на бесконечности");
        }
        const IntegerBinom& IntegerBinomEllipticPoint::getY()
        {
                if(!isInfinite())return *_y;
                throw new Exception("Точка на бесконечности");
        }
        IntegerBinomEllipticCurve& IntegerBinomEllipticPoint::setCurve(IntegerBinomEllipticCurve &eCurve)
        {
                *_curve = eCurve;
                _x->setModulePolynom(_curve->getModulePolynom());
                _y->setModulePolynom(_curve->getModulePolynom());
        if(!isInfinite())
        {
            if(!_curve->inGroup(*_x, *_y))
                _infinite = true;
        }
        return *_curve;
        }
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::setXY(const IntegerBinom &x, const IntegerBinom &y)
        {
                bool infinite = _infinite;
                _infinite = false;
                *_x = x;
                *_y = y;
                _x->setModulePolynom(_curve->getModulePolynom());
                _y->setModulePolynom(_curve->getModulePolynom());
                if(!_curve->inGroup(*_x, *_y))
                {
                    _infinite = infinite;
                    throw new Exception("Точка не лежит на кривой");
                }
                return *this;
        }
        bool IntegerBinomEllipticPoint::isInfinite() const
        {
                return _infinite;
        }
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::setInfinite(bool infinite)
        {
                _infinite = infinite;
        return *this;
        }
        bool IntegerBinomEllipticPoint::isSelfnegative()
        {
                IntegerBinomEllipticPoint negateEPoint;
                negateEPoint.Negate(*this);
                return negateEPoint == *this;
        }
//***********************************************************************************************
//****************************         Унарные операции          ********************************
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::operator=(const IntegerBinomEllipticPoint &ePoint)
        {
                *_curve = *ePoint._curve;
                *_x = *ePoint._x;
                *_y = *ePoint._y;
                _infinite = ePoint._infinite;
                return *this;
        }
//***********************************************************************************************
//*********************************       Операции сравнения        *****************************
        bool operator==(const IntegerBinomEllipticPoint &ePoint1, const IntegerBinomEllipticPoint &ePoint2)
        {
                if(ePoint1.isInfinite() && ePoint2.isInfinite())
            return true;
                if(ePoint1.isInfinite() || ePoint2.isInfinite())
                        return false;
        if(*ePoint1._curve != *ePoint2._curve)
            return false;

        return  *ePoint1._x == *ePoint2._x && *ePoint1._y == *ePoint2._y;
        }
    bool operator!=(const IntegerBinomEllipticPoint &ePoint1, const IntegerBinomEllipticPoint &ePoint2)
        {
                return !(ePoint1 == ePoint2);
        }
//***********************************************************************************************
//**************************   Операция взятия противоположной точки   **************************
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Negate()
        {
                return Negate(*this);
        }
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Negate(IntegerBinomEllipticPoint& ePoint)
        {
                if(ePoint.isInfinite())
                        return setInfinite(true);
                setInfinite(false);
                *_curve = ePoint.getCurve();
                *_x = *ePoint._x;
                *_y = *ePoint._y;
                _y->Negate();
                return *this;
        }
//***********************************************************************************************
//*****************************        Операция сложение        *********************************
        IntegerBinomEllipticPoint operator+(IntegerBinomEllipticPoint &ePoint1, IntegerBinomEllipticPoint &ePoint2)
        {
                IntegerBinomEllipticPoint res;
        return res.Add(ePoint1, ePoint2);
        }
    IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::operator+=(IntegerBinomEllipticPoint &ePoint)
        {
                return Add(*this, ePoint);
        }
    IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Add(IntegerBinomEllipticPoint &ePoint1, IntegerBinomEllipticPoint &ePoint2)
        {
                if(*ePoint1._curve != *ePoint2._curve)
            throw new Exception("Точки лежат на разных кривых");

        *_curve = *ePoint1._curve;

        if(ePoint1.isInfinite() && ePoint2.isInfinite())
            return setInfinite(true);
        if(ePoint1.isInfinite())
        {
            *_x = *ePoint2._x;
            *_y = *ePoint2._y;
            return setInfinite(false);
        }
        if(ePoint2.isInfinite())
        {
            *_x = *ePoint1._x;
            *_y = *ePoint1._y;
            return setInfinite(false);
        }

                IntegerBinomEllipticPoint negateEPoint1;
                negateEPoint1.Negate(ePoint1);
                if(negateEPoint1 == ePoint2)
                        return setInfinite(true);

        setInfinite(false);

            IntegerBinom l(Integer("0") , Integer("0"), getCurve().getModulePolynom()),
                p(Integer("3") , Integer("0"), getCurve().getModulePolynom()),
                x1(*ePoint1._x), x2(*ePoint2._x), y1(*ePoint1._y), y2(*ePoint2._y);

        if(x1 == x2)
        {
            l.Mul(x1, x1);
            l.Mul(l, p);
            l.Add(l, const_cast<IntegerBinom &>(_curve->getA()));

                        IntegerBinom two(Integer("2") , Integer("0"), getCurve().getModulePolynom());
                        p.Mul(y1, two);
        }
        else
        {
            l.Sub(y2, y1);
            p.Sub(x2, x1);
        }

            p.Inverse();
        l.Mul(l, p);

        _x->Mul(l, l);
        _x->Sub(*_x, x1);
        _x->Sub(*_x, x2);

        _y->Sub(x1, *_x);
        _y->Mul(*_y, l);
        _y->Sub(*_y, y1);

        return *this;
        }
//***********************************************************************************************
//******************************      Операция удвоения       ***********************************
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Double()
        {
                return Double(*this);
        }
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Double(IntegerBinomEllipticPoint &e)
        {
                return Add(e, e);
        }


//***********************************************************************************************
//**************************    Операция умножения на константу    ******************************
    IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Mul(IntegerBinomEllipticPoint &ePoint, Integer &integer)
    {
        if(ePoint.isInfinite() || integer.isZero())
                {
                        setInfinite(true);
            return *this;
                }

        IntegerBinomEllipticPoint p(ePoint);
        *_curve = *ePoint._curve;
                setInfinite(true);

        uint ii=0,bit = integer.getNumberBits();
        for(uint i=0; i<bit; i++)
        {
            if(integer.getBit(i))
            {
                for(uint j=0;j<i-ii;j++)
                    p.Double();
                *this += p;
                ii = i;
            }
        }
        return *this;
    }
//***********************************************************************************************
//**************************    Операция нахождения порядка точки  ******************************
        // простой алгоритм, последовательное сложение
        Integer IntegerBinomEllipticPoint::Order()
        {
                if(isInfinite())
                        return Integer("1");
                if(isSelfnegative())
                        return Integer("2");

                Integer order("1");
                IntegerBinomEllipticPoint p(*this);

                while(!p.isInfinite())
                {
                        order++;
                        p.Add(p, *this);
                }


                return order;
        }

//***********************************************************************************************
//*******    Операция функции искажающего отображения ((x,0),(y,0)) => ((-x,0),(0,y))     *******
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Distortion(IntegerBinomEllipticPoint& point)
        {
                if(point.isInfinite())
                        throw new Exception("Точка должна быть конечной");
                if(!point.getX().getB().isZero() || !point.getY().getB().isZero())
                        throw new Exception("Точка должна быть представлена в виде:((x,0),(y,0))");

                setCurve(const_cast<IntegerBinomEllipticCurve &>(point.getCurve()));
                setXY(point.getX(), point.getY());
                _x->Negate();
                _y->setB(_y->getA());
                _y->setA(Integer("0"));
                return *this;
        }
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Distortion()
        {
                return Distortion(*this);
        }

//***********************************************************************************************
//*****************************       Генерация точки         ***********************************
        // реализован случай для кривой с коэф-ми a=(a1,0), b=(b1,0)
        IntegerBinomEllipticPoint& IntegerBinomEllipticPoint::Generate()
        {
                if(!getCurve().getA().getB().isZero() || !getCurve().getB().getB().isZero())
                        throw new Exception("Коффициенты кривой должны быть представлены в виде: a=(a1,0), b=(b1,0)");

                setInfinite(false);
                EllipticCurve curve(const_cast<Integer &>(getCurve().getModule()),
                const_cast<Integer &>(getCurve().getA().getA()),
                const_cast<Integer &>(getCurve().getB().getA()));
                EllipticPoint point(curve);
                point.Generate();

                _x->setZero();
                _x->setA(point.getX());
                _y->setZero();
                _y->setA(point.getY());

                return *this;
        }
//***********************************************************************************************
//**************************    Операция работы со строками        ******************************
        std::string IntegerBinomEllipticPoint::ToString()
        {
                if(isInfinite())
                        return "(X,Y) is infinite";

                std::string result;
                result += "(X,Y) = (" + getX().ToString() + "," + getY().ToString() + ")";
                //result += "(" + getX().ToString() + "," + getY().ToString() + ")";

                return result;
        }

        std::string IntegerBinomEllipticPoint::ToTexString()
        {
                if(isInfinite())
                        return "{\\bf \\cal O}\n";

                std::string result;
                result += "\\left(\n";
                result += "\\begin{array}{ll}\n" +
                getX().getA().ToString() + " & " + getX().getB().ToString() + " \\\\\n" +
                getY().getA().ToString() + " & " + getY().getB().ToString() + "\n" +
                "\\end{array}\n" + "\\right)\n";

                return result;
        }
}
