/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "Ellipticcurves.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>

#include "./Bindings/config.h"

#ifndef USE_MIRACL
#include <windows.h>
#endif


namespace AAL
{
//****************************  Класс Эллиптических кривых  *************************************
//*********************************      Конструкторы       *************************************
	EllipticCurve::EllipticCurve()
	{
		_module = new Integer(5);
		_a = new Integer(1);
		_b = new Integer(1);
	}

	EllipticCurve::EllipticCurve(Integer &module, Integer &J)
	{
		_module = new Integer();
		_a = new Integer();
		_b = new Integer();
		setCurve(module, J);
	}

	EllipticCurve::EllipticCurve(Integer &module, Integer &a, Integer &b)
	{
		if(!module.isPrime())
			throw new Exception("Модуль составное число");
		if(module.isNegative())
			throw new Exception("Модуль отрицательное число");
		if(!isSmooth(module, a, b))
			throw new Exception("Инвариант равен 0");

		_module = new Integer(module);
		_a = new Integer(a);
		_b = new Integer(b);
	}

	EllipticCurve::EllipticCurve(const EllipticCurve &eCurve)
	{
		_module = new Integer(eCurve.getModule());
		_a = new Integer(eCurve.getA());
		_b = new Integer(eCurve.getB());
	}

	EllipticCurve::~EllipticCurve()
	{
		delete _module, _a, _b;
	}
//***********************************************************************************************

//*****************************        Методы акцепторы        **********************************
	//private method
	bool EllipticCurve::isSmooth(Integer &module, Integer &a, Integer &b) const
	{
		Integer temp1;
		temp1.ModMul(a, a, module);
		temp1.ModMul(temp1, a, module);
		temp1 <<= 2;

		Integer temp2;
		temp2.ModMul(b, b, module);

		Integer e(27);
		temp2.ModMul(temp2, e, module);
		temp1.ModAdd(temp1, temp2, module);
		return !temp1.isZero();
	}

	Integer& EllipticCurve::getModule() const
	{
		return *_module;
	}

	Integer EllipticCurve::getInvariant() const
	{
		Integer temp1;
		temp1.ModMul(getA(), getA(), getModule());
		temp1.ModMul(temp1, getA(), getModule());
		temp1 <<= 2;

		Integer temp2;
		temp2.ModMul(getB(), getB(), getModule());

		Integer e(27);
		temp2.ModMul(temp2, e, getModule());
		temp1.ModAdd(temp1, temp2, getModule());
		return temp1;
	}

	Integer& EllipticCurve::getA() const
	{
		return *_a;
	}

	Integer& EllipticCurve::getB() const
	{
		return *_b;
	}

	Integer& EllipticCurve::setModule(Integer &module)
	{
		if(!module.isPrime())
			throw new Exception("Модуль составное число");
		if(module.isNegative())
			throw new Exception("Модуль отрицательное число");
		*_module = module;
		_a->ModPositive(*_module);
		_b->ModPositive(*_module);
		//if(!isSmooth(*_module, *_a, *_b))
			//throw std::domain_error("Инвариант равен 0");
		return *_module;
	}

	Integer& EllipticCurve::setA(Integer &a)
	{
		*_a = a;
		_a->ModPositive(*_module);
		//if(isSmooth(*_module, *_a, *_b))
			//throw std::domain_error("Инвариант равен 0");
		return *_a;
	}

	Integer& EllipticCurve::setB(Integer &b)
	{
		*_b = b;
		_b->ModPositive(*_module);
		//if(isSmooth(*_module, *_a, *_b))
			//throw std::domain_error("Инвариант равен 0");
		return *_b;
	}

	EllipticCurve& EllipticCurve::setCurve(Integer &module, Integer &J)
	{
		if(!module.isPrime())
			throw new Exception("Модуль не простое число");
		if(module.isNegative())
			throw new Exception("Модуль отрицательное число");
        if(J.isZero())
			throw new Exception("Инвариант равен 0");

		Integer k(1728);
		k -= J;
		k.ModPositive(module);

		if(k.isZero())
			throw new Exception("Инвариант равен 1728");

		k.Inverse(module);
		k.ModMul(k, J, module);
		Integer two(2),three(3);
		*_module = module;
		three.ModMul(three, k, module);
		*_a = three;
		two.ModMul(two, k, module);
		*_b = two;

		return *this;
	}

	EllipticCurve& EllipticCurve::setCurve(Integer &module)
	{
		if(!module.isPrime())
			throw new Exception("Модуль составное число");
		if(module.isNegative())
			throw new Exception("Модуль отрицательное число");

        Integer J, temp(1728);
		temp.ModPositive(module);
		do
		{
			J.Generate(module);
		}while(J.isZero() || J == temp);

		return setCurve(module, J);
	}
//***********************************************************************************************

//***************************          Унарные операции         *********************************
	EllipticCurve& EllipticCurve::operator=(const EllipticCurve &eCurve)
	{
		*_module = *eCurve._module;
		*_a = *eCurve._a;
		*_b = *eCurve._b;
		return *this;
	}
//***********************************************************************************************

//********************************      Операции сравнения      *********************************
	bool operator==(const EllipticCurve &eCurve1, const EllipticCurve &eCurve2)
	{
		return(*eCurve1._module == *eCurve2._module && *eCurve1._a == *eCurve2._a && *eCurve1._b == *eCurve2._b);
	}

	bool operator!=(const EllipticCurve &eCurve1, const EllipticCurve &eCurve2)
	{
		return !(eCurve1 == eCurve2);
	}
//***********************************************************************************************

//*************************        Принадлежность точки к кривой      ***************************
	bool EllipticCurve::inGroup(Integer &x, Integer &y) const
	{
		Integer temp1;
		temp1.ModMul(y, y, *_module);
		Integer temp2;
		temp2.ModMul(x, x, *_module);
		temp2.ModMul(x, temp2, *_module);
		Integer temp3;
		temp3.ModMul(*_a, x, *_module);
		temp2.ModAdd(temp2, temp3, *_module);
		temp2.ModAdd(temp2, *_b, *_module);

		if(temp1.isNegative())
			temp1 += *_module;
		if(temp2.isNegative())
			temp2 += *_module;

		return (temp2 == temp1);
	}

//***********************************************************************************************
           //*****************************       Генерация точки         ***********************************
	EllipticPoint& EllipticPoint::Generate()
	{
		Integer x,y,temp;
		do
		{
			x.Generate(_curve->getModule());
			y.ModMul(x, x, _curve->getModule());
			y.ModMul(y, x, _curve->getModule());
			temp.ModMul(x, _curve->getA(), _curve->getModule());
			y.ModAdd(y, temp, _curve->getModule());
			y.ModAdd(y, _curve->getB(), _curve->getModule());

		}while(y.isZero() || y.LegendreSymbol(_curve->getModule()) != 1);

		y.ModSqrt(_curve->getModule());
		setInfinite(false);
		*_x = x;
		*_y = y;
		_x->ModPositive(_curve->getModule());
		_y->ModPositive(_curve->getModule());
		return *this;
	}
//***********************************************************************************************

//*****************************       Вычисление порядка кривой     ***********************************
      Integer EllipticCurve::getOrder()
          {
                                Integer A(getA());
                                Integer B(getB());
                                Integer module(getModule());
#ifndef USE_MIRACL

                                char *str="";
                                std::string s="";
				if (!FileExists("schoof.exe"))
                        {

                                //throw std::domain_error("Не найден файл schoof.exe!");
                                throw new Exception("Не найден файл schoof.exe");
                                return Integer("0");
                        };

               if (!FileExists("sea.exe"))
                        {
                                 //throw std::domain_error("Не найден файл sea.exe!");
                                 throw new Exception("Не найден файл sea.exe");
                                  return Integer("0");
                        };

               if (!FileExists("modpol.exe"))
                        {
                                  //throw std::domain_error("Не найден файл modpol.exe!");
                                 throw new Exception("Не найден файл modpol.exe");
                                 return Integer("0");
                        };

               if (!FileExists("mueller.exe"))
                        {
                                //throw std::domain_error("Не найден файл mueller.exe");
                                throw new Exception("Не найден файл mueller.exe");
                                return Integer("0");
                        };
#endif

                if( module%(module,3)==2 && A.isZero())
                        {
                                return Integer(module+1);

                        };

                if( module%(module,3)==4 && B.isZero() && A.LegendreSymbol(module)==1 )
                         {
                                return Integer(module+1);

                        };

                Integer J (this->getInvariant());

                if (J.isZero()  || J==1728 )
                        {
                                //throw std::domain_error("Инвариант равен 0");
                                throw new Exception("Инвариант кривой равен 0 или 1728");
                                return Integer("0");

                        };

                if (module.getNumberBits()<=190 )
                        {
#ifndef USE_MIRACL
                            s.append("schoof.exe ");
                            s.append(module.strr());
                            s.append(" ");
                            s.append(A.strr());
                            s.append(" ");
                            s.append(B.strr());
                            s.append(" -o curveorder.log");
                            str=const_cast<char *>(s.c_str());
#else
							//ref:shoof_main
							char** argv=new char*[6];
							for(int i=0;i<6;i++)argv[i]=new char[256];
							strcpy(argv[0],"./shoof.exe");
							strcpy(argv[1],module.strr().c_str());
							strcpy(argv[2],A.strr().c_str());
							strcpy(argv[3],B.strr().c_str());
							strcpy(argv[4],"-o");
							strcpy(argv[5],"curveorder.log");
							shoof_main(6,(char**)argv);
							for(int i=0;i<6;i++)delete[] argv[i];
							delete[] argv;
#endif
                        }
                        else
                        {
#ifndef USE_MIRACL
                                if (FileExists("sea.bat")) DeleteFileA("sea.bat");
                                FILE *f =fopen("sea.bat","w");
                                s.append("modpol ");
                                s.append(module.strr());
                                s.append(" 0 120 -o test.pol\n");
                                s.append("sea ");
                                s.append(A.strr());
                                s.append(" ");
                                s.append(B.strr());
                                s.append(" -i test.pol -o curveorder.log\n");
                                fprintf(f,const_cast<char *>(s.c_str()));
                                fclose(f);
                                str="sea.bat";
#else
							//ref:modpol_main
							char** argv=new char*[7];
							for(int i=0;i<7;i++)argv[i]=new char[256];
							strcpy(argv[0],"./modpol.exe");
							strcpy(argv[1],module.strr().c_str());
							strcpy(argv[2],"0");
							strcpy(argv[3],"120");
							strcpy(argv[4],"-o");
							strcpy(argv[5],"test.pol");
							modpol_main(6,(char**)argv);
							//ref:sea_main
							strcpy(argv[1],A.strr().c_str());
							strcpy(argv[2],B.strr().c_str());
							strcpy(argv[3],"-i");
							strcpy(argv[4],"test.pol");
							strcpy(argv[5],"-o");
							strcpy(argv[6],"curveorder.log");
							sea_main(7,(char**)argv);
							for(int i=0;i<7;i++)delete[] argv[i];
							delete[] argv;
#endif

                        };
#ifndef USE_MIRACL
                                STARTUPINFOA StInfo;
                                PROCESS_INFORMATION PrInfo;
                                ZeroMemory(&StInfo,sizeof(StInfo));
                                StInfo.cb=sizeof(StInfo);
                  if (!CreateProcessA(NULL,str,NULL,NULL,FALSE,CREATE_NEW_CONSOLE |IDLE_PRIORITY_CLASS,
                                NULL,
                                NULL,
                                &StInfo,
                                &PrInfo))
                        {
                                throw new Exception("Невозможно запустить schoof.exe или sea.exe");
                                return Integer("0") ;
                        }
						// Ждём, пока процесс не выполнится:
                                WaitForSingleObject(PrInfo.hProcess,INFINITE);
#endif
                                std::vector<std::string> result;
                try
                        {
                                std::ifstream ifs("curveorder.log");
								std::string temp;
								while( getline( ifs, temp ) )
									result.push_back( temp );

                        }
                catch(...)
                        {
                                 throw new Exception("Невозможно прочитать curveorder.log ");
                                 return Integer("0");
                        }
                if (result.size()<7)
                        {
                                throw new Exception("Операция отменена пользователем");
                                return Integer("0");

                        }
                                std::string  crvord = result[4];
                                Integer e(crvord.c_str(),NumericSystem(Hex));
                                return e;
     };






//***********************************************************************************************

//**********************************  Класс точка эллиптичиской кривой  *************************
//********************************      Конструкторы       **************************************
	EllipticPoint::EllipticPoint()
	{
		_curve = new EllipticCurve();
		_x = new Integer();
		_y = new Integer();
		_infinite = true;
	}

	EllipticPoint::EllipticPoint(const EllipticCurve &eCurve)
	{
		_curve = new EllipticCurve(eCurve);
		_x = new Integer();
		_y = new Integer();
		_infinite = true;
	}

	EllipticPoint::EllipticPoint(const EllipticPoint &ePoint)
	{
		_curve = new EllipticCurve(*ePoint._curve);
		_x = new Integer(*ePoint._x);
		_y = new Integer(*ePoint._y);
		_infinite = ePoint._infinite;
	}

	EllipticPoint::~EllipticPoint()
	{
		delete _curve, _x, _y;
	}

//***********************************************************************************************

//****************************       Методы акцепторы        ************************************
	EllipticCurve& EllipticPoint::getCurve()
	{
		return *_curve;
	}

	Integer& EllipticPoint::getX()
	{
		return *_x;
	}

	Integer& EllipticPoint::getY()
	{
		return *_y;
	}

	EllipticCurve& EllipticPoint::setCurve(EllipticCurve &eCurve)
	{
		*_curve = eCurve;
		if(!isInfinite())
		{
			_x->ModPositive(_curve->getModule());
			_y->ModPositive(_curve->getModule());
			if(!_curve->inGroup(*_x, *_y))
				_infinite = true;
		}
		return *_curve;
	}

	EllipticPoint& EllipticPoint::setXY(Integer &x, Integer &y)
	{
		bool infinite = _infinite;
        _infinite = false;
        *_x = x;
        *_y = y;
		_x->ModPositive(_curve->getModule());
		_y->ModPositive(_curve->getModule());
        if(!_curve->inGroup(*_x, *_y))
        {
			_infinite = infinite;
			throw new Exception("точка не лежит на кривой");
        }
        return *this;
	}

	bool EllipticPoint::isInfinite() const
	{
		return _infinite;
	}

	EllipticPoint& EllipticPoint::setInfinite(bool infinite)
	{
		_infinite = infinite;
		return *this;
	}
//***********************************************************************************************

//****************************         Унарные операции          ********************************
	EllipticPoint& EllipticPoint::operator=(const EllipticPoint &ePoint)
	{
		*_curve = *ePoint._curve;
		*_x = *ePoint._x;
		*_y = *ePoint._y;
		_infinite = ePoint._infinite;
		return *this;
	}

//***********************************************************************************************

//*********************************       Операции сравнения        *****************************
	bool operator==(const EllipticPoint &ePoint1, const EllipticPoint &ePoint2)
	{
		if(ePoint1.isInfinite() && ePoint2.isInfinite())
			return true;
		if(*ePoint1._curve != *ePoint2._curve)
			return false;

		return  *ePoint1._x == *ePoint2._x && *ePoint1._y == *ePoint2._y;
	}

	bool operator!=(const EllipticPoint &ePoint1, const EllipticPoint &ePoint2)
	{
		return !(ePoint1 == ePoint2);
	}
//***********************************************************************************************

//**************************   Операция взятия противоположной точки   **************************
        EllipticPoint& EllipticPoint::Negate()
        {
                return Negate(*this);
        }
        EllipticPoint& EllipticPoint::Negate(EllipticPoint& ePoint)
        {
                if(ePoint.isInfinite())
                        return this->setInfinite(true);
                this->setInfinite(false);
                *this->_curve = ePoint.getCurve();
                *this->_x = *ePoint._x;
                *this->_y = -*ePoint._y;
                this->_y->ModPositive(this->getCurve().getModule());
                return *this;
        }
//***********************************************************************************************

//*****************************        Операция сложение        *********************************
	EllipticPoint operator+(EllipticPoint &ePoint1, EllipticPoint &ePoint2)
	{
		EllipticPoint res;
		return res.Add(ePoint1, ePoint2);
	}

	EllipticPoint& EllipticPoint::operator+=(EllipticPoint &ePoint)
	{
		return Add(*this, ePoint);
	}

	EllipticPoint& EllipticPoint::Add(EllipticPoint &ePoint1, EllipticPoint &ePoint2)
	{
		if(*ePoint1._curve != *ePoint2._curve)
			throw new Exception("точки лежат на разных кривых");

		*this->_curve = *ePoint1._curve;

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

                EllipticPoint negateEPoint1;
                negateEPoint1.Negate(ePoint1);
                if(negateEPoint1 == ePoint2)
                        return setInfinite(true);

		setInfinite(false);

		Integer l,p(3),x1(*ePoint1._x), x2(*ePoint2._x), y1(*ePoint1._y), y2(*ePoint2._y);
		x1.ModPositive(_curve->getModule());
		x2.ModPositive(_curve->getModule());

		if(x1 == x2)
		{
			y1.ModPositive(_curve->getModule());
			y2.ModPositive(_curve->getModule());

			l.ModMul(x1, x1, _curve->getModule());
			l.ModMul(l, p, _curve->getModule());
			l.ModAdd(l, _curve->getA(), _curve->getModule());

			p = y1 << 1;
			p.ModPositive(_curve->getModule());
		}
		else
		{
			l.ModSub(y2, y1, _curve->getModule());
			p.ModSub(x2, x1, _curve->getModule());
		}

        	p.Inverse(_curve->getModule());
		l.ModMul(l, p, _curve->getModule());

		_x->ModMul(l, l, _curve->getModule());
		_x->ModSub(*_x, x1, _curve->getModule());
		_x->ModSub(*_x, x2, _curve->getModule());

		_y->ModSub(x1, *_x, _curve->getModule());
		_y->ModMul(*_y, l, _curve->getModule());
		_y->ModSub(*_y, y1, _curve->getModule());

		_x->ModPositive(_curve->getModule());
		_y->ModPositive(_curve->getModule());
		return *this;
	}
//***********************************************************************************************

//******************************      Операция удвоения       ***********************************
	EllipticPoint& EllipticPoint::Double()
	{
		return this->Double(*this);
	}

	EllipticPoint& EllipticPoint::Double(EllipticPoint &e)
	{
		*_curve = *e._curve;
		if(e.isInfinite())
			return setInfinite(true);

                EllipticPoint negateE;
                negateE.Negate(e);
                if(negateE == e)
                        return setInfinite(true);

		setInfinite(false);


		Integer l,p(3),x(*e._x), y(*e._y);

                l.ModMul(x, x, _curve->getModule());
                l.ModMul(l, p, _curve->getModule());
                l.ModAdd(l, _curve->getA(), _curve->getModule());

                p = y << 1;
                p.ModPositive(_curve->getModule());

                p.Inverse(_curve->getModule());
                l.ModMul(l, p, _curve->getModule());

                _x->ModMul(l, l, _curve->getModule());
                _x->ModSub(*_x, x, _curve->getModule());
                _x->ModSub(*_x, x, _curve->getModule());

                _y->ModSub(x, *_x, _curve->getModule());
                _y->ModMul(*_y, l, _curve->getModule());
                _y->ModSub(*_y, y, _curve->getModule());

                _x->ModPositive(_curve->getModule());
		_y->ModPositive(_curve->getModule());
		return *this;
	}
//***********************************************************************************************

//**************************    Операция умножения на константу    ******************************
	EllipticPoint operator*(const EllipticPoint &ePoint, const Integer &i)
	{
		EllipticPoint res, copy_ePoint(ePoint);
		Integer copy_i(i);
		return res.Mul(copy_ePoint, copy_i);
	}

	EllipticPoint operator*(const Integer &i, const EllipticPoint &ePoint)
	{
		EllipticPoint res, copy_ePoint(ePoint);
		Integer copy_i(i);
		return res.Mul(copy_ePoint, copy_i);
	}

	EllipticPoint& EllipticPoint::operator*=(Integer &i)
	{
		return Mul(*this, i);
	}

	EllipticPoint& EllipticPoint::Mul(Integer &i, EllipticPoint &ePoint)
	{
		return Mul(ePoint, i);
	}

	EllipticPoint& EllipticPoint::Mul(EllipticPoint &ePoint, Integer &integer)
	{
		if(ePoint.isInfinite() || integer.isZero())
                {
                        setInfinite(true);
			return *this;
                }

		EllipticPoint p(ePoint);

                setInfinite(true);
		*_curve = *ePoint._curve;

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
}


