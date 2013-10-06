/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "EllipticcurvesGF3.h"
#include "PolynomGF3.h"
#include "PolynomGF3_m_6.h"
#include "PolynomGF3_mY_9.h"
#include <stdexcept>
#include <stdlib.h>
#include <math.h>
namespace AAL
{
//****************************  Класс Эллиптических кривых над GF(3^n)   *******

//*********************************      Конструкторы       *************************************
        EllipticCurveGF3::EllipticCurveGF3()
        {
                _module = new PolynomGF3("1101");
		            _a2 = new PolynomGF3("1");
		            _a4 = new PolynomGF3("1");
                _a6 = new PolynomGF3("1");
        }
        EllipticCurveGF3::EllipticCurveGF3(PolynomGF3 &module, PolynomGF3 &a2, PolynomGF3 &a4, PolynomGF3 &a6)
        {
               	_module = new PolynomGF3(module);
                a2%=module;
                a4%=module;
                a6%=module;
            		_a2 = new PolynomGF3(a2);
                _a4 = new PolynomGF3(a4);
                _a6 = new PolynomGF3(a6);
        }
        EllipticCurveGF3::EllipticCurveGF3(const EllipticCurveGF3 &eCurve)
        {
                _module = new PolynomGF3(eCurve.getModule());
            		_a2 = new PolynomGF3(eCurve.getA2());
                _a4 = new PolynomGF3(eCurve.getA4());
                _a6 = new PolynomGF3(eCurve.getA6());
        }
        EllipticCurveGF3::~EllipticCurveGF3()
        {
                delete _module, _a2, _a4, _a6;
        }
//***********************************************************************************************
//*****************************        Методы акцепторы        **********************************
        PolynomGF3& EllipticCurveGF3::getModule() const
        {
                return *_module;
        }
        PolynomGF3& EllipticCurveGF3::getA2() const
        {
        	return *_a2;
        }
        PolynomGF3& EllipticCurveGF3::getA4() const
        {
                return *_a4;
        }
        PolynomGF3& EllipticCurveGF3::getA6() const
        {
                return *_a6;
        }
        PolynomGF3& EllipticCurveGF3::setModule(PolynomGF3 &module)
        {

              *_module = module;
	            *_a2%=*_module;
	            *_a4%=*_module;
              *_a6%=*_module;
              return *_module;
        }
        PolynomGF3& EllipticCurveGF3::setA2(PolynomGF3 &a2)
        {
                *_a2 = a2;
	              *_a2%=*_module;
          		return *_a2;
        }
        PolynomGF3& EllipticCurveGF3::setA4(PolynomGF3 &a4)
        {
                *_a4 = a4;
                *_a4%=*_module;
        		return *_a4;
        }
        PolynomGF3& EllipticCurveGF3::setA6(PolynomGF3 &a6)
        {
                *_a6 = a6;
      	        *_a6%=*_module;
		        return *_a6;
        }

//***********************************************************************************************
//***************************          Унарные операции         *********************************
        EllipticCurveGF3& EllipticCurveGF3::operator=(const EllipticCurveGF3 &eCurve)
        {
                *_module = *eCurve._module;
		            *_a2 = *eCurve._a2;
                *_a4 = *eCurve._a4;
                *_a6 = *eCurve._a6;
		      return *this;
        }
//***********************************************************************************************
//********************************      Операции сравнения      *********************************
        bool EllipticCurveGF3::equals(const EllipticCurveGF3 &eCurve) const
        {
                if(this->getModule()==eCurve.getModule())
                 if( (*_a2==eCurve.getA2())&&(*_a4==eCurve.getA4())&&(*_a6==eCurve.getA6())  )
                  return true;
                return false;
        }
        bool operator==(const EllipticCurveGF3 &eCurve1, const EllipticCurveGF3 &eCurve2)
        {
                 return eCurve1.equals(eCurve2);
        }
        bool operator!=(const EllipticCurveGF3 &eCurve1, const EllipticCurveGF3 &eCurve2)
        {
                return !eCurve1.equals(eCurve2);
        }
//***********************************************************************************************
//*************************        Принадлежность точки к кривой      ***************************
	bool EllipticCurveGF3::inGroup(PolynomGF3 &x, PolynomGF3 &y) const
        {
                PolynomGF3 temp1("0"),m(this->getModule());
                PolynomGF3 temp2("0"),temp3("0");

                temp3.Mul(x, x);             //x^2

                temp3%= m;
                temp2.Mul(temp3, *_a2);      //a2*x^2

                temp2%= m;
                temp1.Mul(temp3,x);           //x^3

                temp1%= m;
                temp3.Add(temp1, temp2);    //a2*x^2+x^3
                temp3%= m;
                temp1.Mul(*_a4, x);         //a4*x

                temp1%= m;
                temp2.Add(temp1, temp3);    //a2*x^2+x^3+a4*x

                temp2%= m;
                temp3.Add(temp2, *_a6);     //правая часть

                temp3%= m;

                temp1.Mul(y,y);//левая часть

                temp1%=m;

                return (temp1 == temp3);
        }
//***********************************************************************************************

//****************************  Класс точки Эллиптических кривых над GF(3^n)   *******
//********************************      Конструкторы       **************************************
      EllipticPointGF3::EllipticPointGF3()
        {
                _curve = new EllipticCurveGF3();
		            _x = new PolynomGF3();
		            _y = new PolynomGF3();
		            _infinite = true;
        }
	EllipticPointGF3::EllipticPointGF3(const EllipticCurveGF3 &eCurve)
        {
                _curve = new EllipticCurveGF3(eCurve);
	            	_x = new PolynomGF3();
		            _y = new PolynomGF3();
		            _infinite = true;
        }
	EllipticPointGF3::EllipticPointGF3(const EllipticPointGF3 &ePoint)
        {
                _curve = new EllipticCurveGF3(*ePoint._curve);
		            _x = new PolynomGF3(*ePoint._x);
		            _y = new PolynomGF3(*ePoint._y);
		            _infinite = ePoint._infinite;
        }
       EllipticPointGF3::~EllipticPointGF3()
        {
                delete _curve, _x, _y;
        }
//****************************       Методы акцепторы        ************************************
        EllipticCurveGF3& EllipticPointGF3::getCurve()
        {
                return *_curve;
        }
        EllipticCurveGF3& EllipticPointGF3::setCurve(EllipticCurveGF3 &eCurve)
        {

                *_curve =eCurve;
               	if(!isInfinite())
		            {
			            *_x%=_curve->getModule();
                  *_y%=_curve->getModule();
                  if(!_curve->inGroup(*_x, *_y))
			          	_infinite = true;
		            }

                return *_curve;
        }
	PolynomGF3& EllipticPointGF3::getX()
        {
                 return *_x;
        }
	PolynomGF3& EllipticPointGF3::getY()
        {
                return *_y;
        }
        EllipticPointGF3& EllipticPointGF3::setXY(PolynomGF3 &x, PolynomGF3 &y)
        {
               	bool infinite = _infinite;
                _infinite = false;
                *_x = x;
                *_y = y;
		            *_x%=_curve->getModule();
		            *_y%=_curve->getModule();
                if(!_curve->inGroup(*_x, *_y))
                {
                  _infinite = infinite;
                	throw new Exception("Точка не лежит на кривой");
                }
                return *this;
        }
        bool EllipticPointGF3::isInfinite() const
        {
                return _infinite;
        }
	EllipticPointGF3& EllipticPointGF3::setInfinite(bool infinite)
        {
                _infinite = infinite;
                return *this;
        }
//*********************************       Операции сравнения        *****************************
	bool operator==(const EllipticPointGF3 &ePoint1, const EllipticPointGF3 &ePoint2)
        {
                if(ePoint1.isInfinite() && ePoint2.isInfinite())
		            	return true;
		            if(*ePoint1._curve != *ePoint2._curve)
			            return false;

		            return  *ePoint1._x == *ePoint2._x && *ePoint1._y == *ePoint2._y;
        }
	bool operator!=(const EllipticPointGF3 &ePoint1, const EllipticPointGF3 &ePoint2)
        {
                return !(ePoint1 == ePoint2);
        }
//***********************************************************************************************
//**************************   Операция взятия противоположной точки   **************************
        EllipticPointGF3& EllipticPointGF3::Negate()
        {
                return Negate(*this);
        }
        EllipticPointGF3& EllipticPointGF3::Negate(EllipticPointGF3& ePoint)
        {
                 if(ePoint.isInfinite())
                        return setInfinite(true);
                this->setInfinite(false);
                *this->_x = *ePoint._x;
                PolynomGF3 temp1(*ePoint._y),temp2("0");
                temp1=_y->Sub(temp2, temp1);
                *this->_y=temp1;
                *this->_curve =*ePoint._curve;
                return *this;
        }
//***********************************************************************************************
//*****************************        Операция сложение        *********************************
        EllipticPointGF3& EllipticPointGF3::operator+=(EllipticPointGF3 &ePoint)
        {
                return Add(*this, ePoint);
        }

//***********************************************************************************************
//******************************      Операция удвоения       ***********************************
	EllipticPointGF3& EllipticPointGF3::Double()
        {
                return this->Double(*this);
        }
//***********************************************************************************************
//**************************    Операция умножения на константу    ******************************
       	EllipticPointGF3& EllipticPointGF3::operator*=(Integer &i)
       	{
       		return Mul(*this, i);
       	}
        EllipticPointGF3& EllipticPointGF3::Mul(EllipticPointGF3 &ePoint,Integer &integer)
        {       //this->setCurve(*ePoint._curve);
                setInfinite(true);
		            if(ePoint.isInfinite() || integer.isZero())
		            	return *this;

	     	        EllipticPointGF3 p(ePoint);
                *this->_curve =*ePoint._curve;

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
//***************************          Унарные операции         *********************************
        EllipticPointGF3& EllipticPointGF3::operator=(const EllipticPointGF3 &ePoint)
        {
                *_curve= *ePoint._curve;
	            	*_x = *ePoint._x;
		            *_y = *ePoint._y;
		            _infinite = ePoint._infinite;
		          return *this;
        }

//**************************   Операция сложения   **************************
  	EllipticPointGF3& EllipticPointGF3::Add(EllipticPointGF3 &ePoint1, EllipticPointGF3 &ePoint2)
        {
                *this->_curve =*ePoint1._curve;
                if(*ePoint1._curve != *ePoint2._curve)
			            throw new Exception("Точки на разных кривых");

		            if(ePoint1.isInfinite() && ePoint2.isInfinite())
		          	{return setInfinite(true);}
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
                EllipticPointGF3 a(ePoint1),b(ePoint2);
                PolynomGF3 lam("0"),beta("0"),module(a._curve->getModule()),x3("0"),y3("0"),temp1("0"),temp2("0");
                EllipticPointGF3 negateEPoint1;
                negateEPoint1.Negate(ePoint1);
                if(negateEPoint1 == ePoint2)
                {return setInfinite(true);}
               	setInfinite(false);
                if (a!=b)
                {
                  temp1.Sub(*b._y,*a._y);
                  beta.Sub(*b._x,*a._x);
                  beta.InverseMod(beta,module);
                  lam.Mul(temp1,beta);

                  lam%=module;

                  temp1.Mul(lam,lam);
                  temp1%=module;
                  temp2.Sub(temp1,a._curve->getA2());
                  temp1.Sub(temp2,*a._x);
                  x3.Sub(temp1,*b._x);
                  x3%=module;
                  temp1.Sub(*a._x,x3);

                  temp2.Mul(temp1,lam);
                  temp2%=module;
                  y3.Sub(temp2,*a._y);
                  *_x=x3;*_y=y3;
                }
                if(a==b)
                {
                 lam.Mul(a._curve->getA2(),*a._x);
                 lam%=module;
                 lam.Sub(lam,a._curve->getA4());

                 beta.InverseMod(*a._y,module);
                 lam.Mul(lam,beta);
                 lam%=module;
                 x3.Mul(lam,lam);
                 x3%=module;
                 x3.Sub(x3,a._curve->getA2());
                 x3.Sub(x3,*a._x);
                 x3.Sub(x3,*a._x);
                 x3%=module;
                 y3.Sub(*a._x,x3);

                 y3.Mul(y3,lam);
                 y3%=module;
                 y3.Sub(y3,*a._y);
                 *_x=x3;*_y=y3;
                }
               return  *this;
        }
//***********************************************************************************************
//******************************      Удвоение       ***********************************

	EllipticPointGF3& EllipticPointGF3::Double(EllipticPointGF3 &ePoint)
        {       *this->_curve =*ePoint._curve;
                if(ePoint.isInfinite())
			            return setInfinite(true);
                EllipticPointGF3 negateEPoint;
                negateEPoint.Negate(ePoint);
                if(negateEPoint == ePoint)
                  return setInfinite(true);
		            setInfinite(false);
                EllipticPointGF3 a(ePoint);
                PolynomGF3 lam("0"),beta("0"),module(a._curve->getModule()),x3("0"),y3("0");

                lam.Mul(a._curve->getA2(),*a._x);

                lam%=module;

                lam.Sub(lam,a._curve->getA4());

                beta.InverseMod(*a._y,module);

                lam.Mul(lam,beta);

                lam%=module;

                 x3.Mul(lam,lam);
                 x3%=module;

                 x3.Sub(x3,a._curve->getA2());

                 x3.Sub(x3,*a._x);

                 x3.Sub(x3,*a._x);
                 x3%=module;

                 y3.Sub(*a._x,x3);
                 y3%=module;
                 y3.Mul(y3,lam);
                 y3%=module;
                 y3.Sub(y3,*a._y);
                 *_x=x3;*_y=y3;
                 return *this;
        }


//***********************************************************************************************

//**************************    Генерация точки                    ******************************
       EllipticPointGF3& EllipticPointGF3::Generate()
        { uint n = _curve->getModule().getNumberBits()-1;
                if(n % 2 != 1)
                       throw std::domain_error("старшая степень модулярного многочлена должна быть нечетной");

                PolynomGF3 x, y,c, temp1, temp2,m(_curve->getModule()),temp3,a2(_curve->getA2()),a4(_curve->getA4()),a6(_curve->getA6());
                Integer two("2");
                 int md = m.getNumberBits() - 1;
                AAL::Integer ord(1);
                std::string str;
                ord = ord.Pow(3,md);
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
               do
                do
                {
                        // ????????? X
                        x.Generate(m);
                        // ?????????? ?????? ????? ?????????
                        temp3.Mul(x, x);
                        temp3%= m;
                        temp2.Mul(temp3, a2);      //a2*x^2
                        temp2%= m;
                        temp1.Mul(temp3,x);           //x^3
                        temp1%= m;

                        temp2.Add(temp2, temp1);    //a2*x^2+x^3
                        temp2%= m;
                        temp3.Mul(a4, x);         //a4*x
                        temp3%= m;
                        temp2.Add(temp2, temp3);    //a2*x^2+x^3+a4*x
                        temp2%= m;
                        temp2.Add(temp2, a6);     //правая часть
                        temp2%= m;
                        //temp1.Square1(temp2,m);
                        c.Sqrt(temp2,m,s,T);
                }
                while(c==m); // Проверка: существует ли корень
              while(!_curve->inGroup(x,c));
		*_x = x;
                *_y = c;

		return *this;
        }
// генерация точки с вложением данных
      EllipticPointGF3& EllipticPointGF3::Generate(const PolynomGF3 &mes)
        { uint n = _curve->getModule().getNumberBits()-1;
          uint mesn=mes.getNumberBits();
                if(n % 2 != 1)
                       throw std::domain_error("n не нечетно");
                if(mesn>n-2)
                       throw std::domain_error("Сообщение H1 больше n-2");
                PolynomGF3 x, y,c, temp1, temp2,m(_curve->getModule()),temp3,a2(_curve->getA2()),a4(_curve->getA4()),a6(_curve->getA6());
                Integer two("2");
                 int md = m.getNumberBits() - 1;
                AAL::Integer ord(1);
                std::string str;
                ord = ord.Pow(3,md);
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

               do
                do
                {
                        // Генерация X
                        x.Generate(m,mes);
                        // Вычисление правой части уравнения
                        temp3.Mul(x, x);
                        temp3%= m;
                        temp2.Mul(temp3, a2);      //a2*x^2
                        temp2%= m;
                        temp1.Mul(temp3,x);           //x^3
                        temp1%= m;
                        temp2.Add(temp2, temp1);    //a2*x^2+x^3
                        temp2%= m;
                        temp3.Mul(a4, x);         //a4*x
                        temp3%= m;
                        temp2.Add(temp2, temp3);    //a2*x^2+x^3+a4*x
                        temp2%= m;
                        temp2.Add(temp2, a6);     //правая часть
                        temp2%= m;
                        //temp1.Square1(temp2,m);
                        c.Sqrt(temp2,m,s,T);
                }
                while(c==m); // Проверка: существует ли корень
              while(!_curve->inGroup(x,c));
		*_x = x;
                *_y = c;

		return *this;
        }
//***********************************************************************************************
PolynomGF3_m_6& EllipticPointGF3::findRo(PolynomGF3 &mod,PolynomGF3_m_6 &b )
{
   PolynomGF3_m_6 s("10200","01010","00120","01002","21002","02101",mod.ToString()),s1,a,a_3,a1,r;
   PolynomGF3_m_6 two("2","0","0","000","0","0",mod.ToString());
   Integer t;
   std::string str;
    int m = mod.getNumberBits() - 1;
   t.Pow(3,6*m);
   t = (t - 1)/26;
   str = t.ToString();
   s.setModule(mod);
   s1.setModule(mod);
   a.setModule(mod);
   r.setModule(mod);
   a_3.setModule(mod);
   a1.setModule(mod);
   b.setModule(mod);
   b.Mul(b,two);
   str = b.getA0().ToString();
    str = b.getA1().ToString();
    str = b.getA2().ToString();
    str = b.getA3().ToString();
    str = b.getA4().ToString();
    str = b.getA5().ToString();

   s1.Pow(s,t);
      str = s1.getA0().ToString();
    str = s1.getA1().ToString();
    str = s1.getA2().ToString();
    str = s1.getA3().ToString();
    str = s1.getA4().ToString();
    str = s1.getA5().ToString();

   t = 1;
   a  = s1;
   a_3.Cube(a);
   str = a_3.getA0().ToString();
    str = a_3.getA1().ToString();
    str = a_3.getA2().ToString();
    str = a_3.getA3().ToString();
    str = a_3.getA4().ToString();
    str = a_3.getA5().ToString();

   a1.Mul(a,two);
   str = a1.getA0().ToString();
    str = a1.getA1().ToString();
    str = a1.getA2().ToString();
    str = a1.getA3().ToString();
    str = a1.getA4().ToString();
    str = a1.getA5().ToString();

   r.Add(a_3,a1);
   str = r.getA0().ToString();
    str = r.getA1().ToString();
    str = r.getA2().ToString();
    str = r.getA3().ToString();
    str = r.getA4().ToString();
    str = r.getA5().ToString();

   r.Add(r,b);
   str = r.getA0().ToString();
    str = r.getA1().ToString();
    str = r.getA2().ToString();
    str = r.getA3().ToString();
    str = r.getA4().ToString();
    str = r.getA5().ToString();

   while(r.isZero() == false)
   {
        a.Pow(s1,t);
   str = a.getA0().ToString();
    str = a.getA1().ToString();
    str = a.getA2().ToString();
    str = a.getA3().ToString();
    str = a.getA4().ToString();
    str = a.getA5().ToString();

        t = t + 1;
       str = t.ToString();
/*        b.Mul(b,two);
   str = b.getA0().ToString();
    str = b.getA1().ToString();
    str = b.getA2().ToString();
    str = b.getA3().ToString();
    str = b.getA4().ToString();
    str = b.getA5().ToString();

        s1.Pow(s,t);
      str = s1.getA0().ToString();
    str = s1.getA1().ToString();
    str = s1.getA2().ToString();
    str = s1.getA3().ToString();
    str = s1.getA4().ToString();
    str = s1.getA5().ToString();
*/
        a_3.Cube(a);
   str = a_3.getA0().ToString();
    str = a_3.getA1().ToString();
    str = a_3.getA2().ToString();
    str = a_3.getA3().ToString();
    str = a_3.getA4().ToString();
    str = a_3.getA5().ToString();

        a1.Mul(a,two);
   str = a1.getA0().ToString();
    str = a1.getA1().ToString();
    str = a1.getA2().ToString();
    str = a1.getA3().ToString();
    str = a1.getA4().ToString();
    str = a1.getA5().ToString();

        r.Add(a_3,a1);
   str = r.getA0().ToString();
    str = r.getA1().ToString();
    str = r.getA2().ToString();
    str = r.getA3().ToString();
    str = r.getA4().ToString();
    str = r.getA5().ToString();

        r.Add(r,b);
   str = r.getA0().ToString();
    str = r.getA1().ToString();
    str = r.getA2().ToString();
    str = r.getA3().ToString();
    str = r.getA4().ToString();
    str = r.getA5().ToString();

   }
   PolynomGF3_m_6 *result;
   result  = new PolynomGF3_m_6();
   result->setModule(mod);
//   a.Add(a,b);
   *result = a;
      str = a.getA0().ToString();
    str = a.getA1().ToString();
    str = a.getA2().ToString();
    str = a.getA3().ToString();
    str = a.getA4().ToString();
    str = a.getA5().ToString();

   return  *result;
}

PolynomGF3_m_6& EllipticPointGF3::DLK(EllipticPointGF3 &ePoint1,EllipticPointGF3 &ePoint2,PolynomGF3_m_6 &ro,PolynomGF3_m_6 &si,int n,PolynomGF3_m_6 &b,PolynomGF3 &mod)
{
    PolynomGF3_m_6* f = new PolynomGF3_m_6();
    PolynomGF3_m_6 x1,d,g,two("2","0","0","000","0","0",mod.ToString());
    PolynomGF3_m_6 x,y,al,bt;
  //  PolynomGF3 mod("220001");
  std::string str;
    char m1[100];
    PolynomGF3_m_6 mm(itoa(n%3,m1,10),"0","0","0","0","0",mod.ToString());
    d.Mul(b,mm); //d=mb
    PolynomGF3 xx,yy,all,btt;
    xx = ePoint1.getX();
    yy = ePoint1.getY();
    all = ePoint2.getX();
    btt = ePoint2.getY();
     xx.FastCube(xx,n);  //xx*xx*xx;
     yy.FastCube(yy,n); //= yy*yy*yy;
    f->setOne(); //f = 1
    f->setModule(mod);
    x.setModule(mod);
    x.setByIndex(xx,0);
    y.setModule(mod);
    y.setByIndex(yy,0);
    al.setModule(mod);
    al.setByIndex(all,0);
    bt.setModule(mod);
    bt.setByIndex(btt,0);
//    x.Cube(x); //x  = x^3
//    y.Cube(y); //y = y^3
    int i;
    PolynomGF3 a11("1"),b11("2");
    for(i = 1; i <= n ; i++)
	{
      if(i == 3)
       { int t = 0; t++;}
      all.FastCube(all,n);
      all.FastCube(all,n);//ModPow(all,9,mod);//  = all*all*all;
      //all = all*all*all;
      al.setModule(mod);
      al.setByIndex(all,0);

    //    al.Cube(al);
//    al.Cube(al);
	//al.Pow(al,9);// alpha = (alpha^3)^3
    //btt.ModPow(btt,9,mod);// = btt*btt*btt;
    btt.FastCube(btt,n);
    btt.FastCube(btt,n);
    //btt = btt*btt*btt;
    bt.setModule(mod);
    bt.setByIndex(btt,0);

    //        bt.Cube(bt);
//        bt.Cube(bt);
       //	bt.Pow(bt,9);// beta = (beta^3)^3
    	PolynomGF3_m_6 mu;
       mu.setModule(mod) ;
       mu.Add(al,x);  // alpha+x
        mu.Add(mu,d); //mu = alpha+x+d
        PolynomGF3_m_6 lambda, mu_2;
        lambda.setModule(mod);
        mu_2.setModule(mod);
 //       mu_2 = mu;
        mu_2=mu*mu;//.Pow(mu,2); // mu^2
        mu_2.Mul(mu_2,two);//-mu^2
        lambda.Mul(si,bt); //sigma*beta
       lambda.Mul(lambda,y); //sigma*beta*y
        lambda.Add(lambda,mu_2);//lambda = sigma*beta*y - mu^2
    	f->Cube(*f); //f^3
    PolynomGF3_m_6 muro, ro_2,mlt;
   muro.setModule(mod);
   ro_2.setModule(mod);
   mlt.setModule(mod);

  muro.Mul(mu,ro);//mu*ro
   muro.Mul(muro,two); //-mu*ro
   ro_2 = ro*ro;//.Pow(ro,2); //ro^2
  //  ro_2 = ro;
   ro_2.Mul(ro_2,two); //-ro^2
   mlt.Add(lambda,muro);//lambda -mu*ro
   mlt.Add(mlt,ro_2);//lambda-mu*ro-ro^2
   f->Mul(*f,mlt); //f*(lambda-mu*ro-ro^2)
       y.Mul(y,two); //y = -y
        PolynomGF3_m_6 b1;
       b1.setModule(mod);
       b1.Mul(b,two);//-b
        d.Add(d,b1); //d = d-b
   }
	Integer three_n;
        three_n.Mul(3,n);
 //       three_n.Pow(3,three_n);
        PolynomGF3_m_6 ff(*f);
        for(Integer k = 0; k < three_n; k++)
            f->Cube(*f);
        //ff.Inverse(ff,mod);
        //f->Mul(ff,*f);
    //f->Pow(*f,three_n-1);
    return *f;
}
}

