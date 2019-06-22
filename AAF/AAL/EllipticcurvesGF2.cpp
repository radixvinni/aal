/*
        MPEI Algebraic Abstractions Library,
        2007-2011,
        Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "EllipticcurvesGF2.h"
#include "Matrix.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "PolynomGF2_m_4.h"
#include "PolynomGF2_mY_7.h"

#include "./Bindings/config.h"

#ifndef USE_MIRACL
#include <windows.h>
#endif

namespace AAL
{
//****************************  Класс Эллиптических кривых над GF(2^n)   *******
        EllipticCurveGF2::~EllipticCurveGF2()
        {
                // должен быть пустой
        }
//*****************************        Методы акцепторы        **********************************
        Polynom& EllipticCurveGF2::getModule() const
        {
                return *_module;
        }
//***********************************************************************************************
//********************************      Операции сравнения      *********************************
        bool operator==(const EllipticCurveGF2 &eCurve1, const EllipticCurveGF2 &eCurve2)
        {
                 return eCurve1.equals(eCurve2);
        }
        bool operator!=(const EllipticCurveGF2 &eCurve1, const EllipticCurveGF2 &eCurve2)
        {
                return !eCurve1.equals(eCurve2);
        }
//****************************  Класс Суперсингулярных Эллиптических кривых над GF(2^n)   *******
//*********************************      Конструкторы       *************************************
        SuperSingularEllipticCurve::SuperSingularEllipticCurve()
        {
                _module = new Polynom("1101");
        _a3 = new Polynom("1");
        _a4 = new Polynom("1");
                _a6 = new Polynom("1");
        }
        SuperSingularEllipticCurve::SuperSingularEllipticCurve(Polynom &module, Polynom &a3, Polynom &a4, Polynom &a6)
        {
                if(a3.isZero())
                        throw new Exception("Коэффициент a3 не может быть равен 0");
                if(!module.isIrreducible())
            throw  new Exception("Модуль является приводимым многочленом");

        _module = new Polynom(module);
        _a3 = new Polynom(a3);
        _a4 = new Polynom(a4);
                _a6 = new Polynom(a6);
        }
        SuperSingularEllipticCurve::SuperSingularEllipticCurve(const SuperSingularEllipticCurve &eCurve)
        {
                _module = new Polynom(eCurve.getModule());
        _a3 = new Polynom(eCurve.getA3());
                _a4 = new Polynom(eCurve.getA4());
                _a6 = new Polynom(eCurve.getA6());
        }
        SuperSingularEllipticCurve::~SuperSingularEllipticCurve()
        {
                delete _module, _a3, _a4, _a6;
        }
//***********************************************************************************************
//*****************************        Методы акцепторы        **********************************
        Polynom& SuperSingularEllipticCurve::getA3() const
        {
            return *_a3;
        }
        Polynom& SuperSingularEllipticCurve::getA4() const
        {
                return *_a4;
        }
        Polynom& SuperSingularEllipticCurve::getA6() const
        {
                return *_a6;
        }
        Polynom& SuperSingularEllipticCurve::setModule(const Polynom &module)
        {
                if(!module.isIrreducible())
            throw new Exception("Модуль является приводимым многочленом");
                Polynom a3;
                a3.Mod(*_a3, module);
                if(a3.isZero())
                        throw new Exception("Коэффициент a3 не может быть равен 0");
        *_module = module;
        _a3->Mod(*_module);
        _a4->Mod(*_module);
                _a6->Mod(*_module);
        return *_module;
        }
        Polynom& SuperSingularEllipticCurve::setA3(Polynom &a3)
        {
                if(a3.isZero())
                        throw new Exception("Коэффициент a3 не может быть равен 0");
                *_a3 = a3;
        _a3->Mod(*_module);
        return *_a3;
        }
        Polynom& SuperSingularEllipticCurve::setA4(Polynom &a4)
        {
                *_a4 = a4;
        _a4->Mod(*_module);
        return *_a4;
        }
        Polynom& SuperSingularEllipticCurve::setA6(Polynom &a6)
        {
                *_a6 = a6;
        _a6->Mod(*_module);
        return *_a6;
        }
        bool SuperSingularEllipticCurve::isSuperSingular() const
        {
                return true;
        }
        bool SuperSingularEllipticCurve::isNonSuperSingular() const
        {
                return !isSuperSingular();
        }
//***********************************************************************************************


 //***************************       Вычисление порядка кривой   *********************************

        Integer& SuperSingularEllipticCurve::getOrd(int step)
        {
            Integer *result;
            if(getA4().isZero() && getA6().isZero())
            {
               result = new Integer();
               result->Pow(2, step);
               *result += *(new Integer(1));
            }
            else if(!getA4().isZero() && getA6().isZero())
            {
                if(step%8 == 1 || step%8 == 7)
                {
                    result = new Integer();
                    result->Pow(2, step);
                    Integer *res;
                    res = new Integer();
                    res->Pow(2, (step + 1)/2);
                    *result = *result + *res + 1;
                }
                else if(step%8 == 3 || step%8 == 5)
                {
                    result = new Integer();
                    result->Pow(2, step);
                    Integer *res;
                    res = new Integer();
                    res->Pow(2, (step + 1)/2);
                    *result = *result - *res + 1;
                }
            }
            else if(!getA4().isZero() && !getA6().isZero())
            {
                if(step%8 == 1 || step%8 == 7)
                {
                    result = new Integer();
                    result->Pow(2, step);
                    Integer *res;
                    res = new Integer();
                    res->Pow(2, (step + 1)/2);
                    *result = *result - *res + 1;
                }
                else if(step%8 == 3 || step%8 == 5)
                {
                    result = new Integer();
                    result->Pow(2, step);
                    Integer *res;
                    res = new Integer();
                    res->Pow(2, (step + 1)/2);
                    *result = *result + *res + 1;
                }
            }
            return *result;
        }
        Integer NonSuperSingularEllipticCurve::getOrder() const
        {
                                Integer a1("0");
                                Integer a2("0");
                                Integer a3("0");




              std::set<uint> powers(getModule().getPowersOfPolynom());


              if(powers.size()!=5 && powers.size()!=3 )
                           {
                                      throw new Exception("Модуль не является полиномом третьей или пятой степени");
                                      return Integer("0");

                            }

              if(powers.size()==3 )

                  {
                    std::set<uint>:: iterator i = powers.begin();
                    Integer tmp(*(++i));
                    a1.Parse(tmp.strr() ,Dec);

                  }
                  if(powers.size()==5 )

                  {
                    std::set<uint>:: iterator i = powers.begin();
                    Integer tmp1(*(++i));
                    a3.Parse(tmp1.strr() ,Dec);
                    Integer tmp2(*(++i));
                    a2.Parse(tmp2.strr() ,Dec);
                    Integer tmp3(*(++i));
                    a1.Parse(tmp3.strr(),Dec);

                  }


                  //getA2().

                  //Application->MessageBoxA(tmp2.strr().c_str(),tmp2.strr().c_str(),1);
                  Integer A2 (strrev(const_cast<char *> ( getA2().ToString(PolynomSystem(Bin)).c_str() )),NumericSystem(Bin));
                  Integer A6 (strrev(const_cast<char *> ( getA6().ToString(PolynomSystem(Bin)).c_str() )),NumericSystem(Bin));
                  Integer module(getModule().getNumberBits()-1);

#ifndef USE_MIRACL
                                char *str="";
                                std::string s="";
              if (!FileExists("schoof2.exe"))
                        {

                                //throw std::domain_error("Не найден файл schoof.exe!");
                                throw new Exception("Не найден файл schoof2.exe");
                                return Integer("0");
                        };
#endif


                /* if( module%(module,3)==2 && A.isZero())
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
                                MessageBoxA(NULL,"Инвариант кривой равен 0 или 1728","Ошибка!",MB_OK | MB_ICONERROR | MB_APPLMODAL);
                                return Integer("0");

                        }; */

#ifndef USE_MIRACL

                                s.append("schoof2.exe ");
                                s.append(A2.strr());
                                s.append(" ");
                                s.append(A6.strr());
                                s.append(" ");
                                s.append(module.strr());
                                s.append(" ");
                                s.append(a1.strr());
                                s.append(" ");
                                s.append(a2.strr());
                                s.append(" ");
                                s.append(a3.strr());
                                s.append(" -o curveorder.log");
                                str=const_cast<char *>(s.c_str());
                                //Application->MessageBoxA(str,str,1);
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
                                MessageBoxA(NULL,"Невозможно запустить schoof2.exe","Ошибка!",MB_OK | MB_ICONERROR | MB_APPLMODAL);
                                return Integer("0") ;
                        }
  // Ждём, пока процесс не выполнится:
                                WaitForSingleObject(PrInfo.hProcess,INFINITE);
#else
                            //ref:shoof2_main
                            char** argv=new char*[9];
                            for(int i=0;i<9;i++)argv[i]=new char[256];
                            strcpy(argv[0],"./shoof2.exe");
                            strcpy(argv[1],A2.strr().c_str());
                            strcpy(argv[2],A6.strr().c_str());
                            strcpy(argv[3],module.strr().c_str());
                            strcpy(argv[4],a1.strr().c_str());
                            strcpy(argv[5],a2.strr().c_str());
                            strcpy(argv[6],a3.strr().c_str());
                            strcpy(argv[7],"-o");
                            strcpy(argv[8],"curveorder.log");
                            shoof2_main(9,(char**)argv);
                            for(int i=0;i<9;i++)delete[] argv[i];
                            delete[] argv;
#endif

                                std::vector<std::string> result;
                try
                        {
                                std::ifstream ifs("curveorder.log");
                                std::string temp;
                                while( getline( ifs, temp ) )
                                    result.push_back( temp );

                                std::string s;
                                s.append("schoof2.exe ");
                                s.append(A2.strr());
                                s.append(" ");
                                s.append(A6.strr());
                                s.append(" ");
                                s.append(module.strr());
                                s.append(" ");
                                s.append(a1.strr());
                                s.append(" ");
                                s.append(a2.strr());
                                s.append(" ");
                                s.append(a3.strr());
                                s.append(" -o curveorder.log");
                                printf("command: %s, result len: %u\n",s.c_str(),result.size());

                        }
                catch(...)
                        {
                                 throw new Exception("Невозможно прочитать curveorder.log ");
                                 return Integer("0");
                        }
                if (result.size()<9)
                        {
                                throw new Exception("Операция отменена пользователем");
                                return Integer("0");

                        }
                                std::string  tmp1 = result[3];
                                std::string  tmp2 = result[4];
                                Integer prnp(tmp1.c_str(),NumericSystem(Hex));
                                Integer cf(tmp2.c_str(),NumericSystem(Hex));
                                Integer np(0);
                                np.Mul(prnp,cf);
                                //Integer e(crvord.c_str(),NumericSystem(Hex));
                                return prnp;

     };











//***************************          Унарные операции         *********************************
        SuperSingularEllipticCurve& SuperSingularEllipticCurve::operator=(const SuperSingularEllipticCurve &eCurve)
        {
                *_module = *eCurve._module;
        *_a3 = *eCurve._a3;
                *_a4 = *eCurve._a4;
                *_a6 = *eCurve._a6;
        return *this;
        }

//***********************************************************************************************
//********************************      Операции сравнения      *********************************
        bool SuperSingularEllipticCurve::equals(const EllipticCurveGF2 &eCurve) const
        {
                const SuperSingularEllipticCurve * pECurve = dynamic_cast<const SuperSingularEllipticCurve *>(&eCurve);
                return (pECurve == 0) ? false :
                (*this->_module == *pECurve->_module && *this->_a3 == *pECurve->_a3 && *this->_a4 == *pECurve->_a4
                && *this->_a6 == *pECurve->_a6);
        }
//***********************************************************************************************
//*************************        Принадлежность точки к кривой      ***************************
    bool SuperSingularEllipticCurve::inGroup(Polynom &x, Polynom &y) const
        {
                Polynom temp1;
                temp1.ModMul(y, y, *_module);
                Polynom temp2;
                temp2.ModMul(*_a3, y, *_module);
                temp2.ModAdd(temp2, temp1, *_module);
                temp1 = rightSide(x);

                return (temp2 == temp1);
        }
//***********************************************************************************************
//*************************        Вычисление правой части уравнения      ***********************
        Polynom SuperSingularEllipticCurve::rightSide(Polynom &x) const
        {
                Polynom temp1;
                temp1.ModMul(x, x, *_module);
                temp1.ModMul(x, temp1, *_module);
                Polynom temp2;
                temp2.ModMul(*_a4, x, *_module);
                temp1.ModAdd(temp1, temp2, *_module);
                temp1.ModAdd(temp1, *_a6, *_module);
                return temp1;
        }
//***********************************************************************************************
//*************************   Проверка на существование Y для данного X   ***********************
        bool SuperSingularEllipticCurve::hasY(Polynom &x) const
        {
                if(x.isZero())
                        return false;

                Polynom  right(rightSide(x)), temp;
                return right.isZero() || temp.Trace(right, getModule()).isZero();
        }
//***********************************************************************************************
//****************************  Класс точки Эллиптических кривых над GF(2^n)   *******
//********************************      Конструкторы       **************************************
        EllipticPointGF2::~EllipticPointGF2()
        {
                // должен быть пустой
        }
//****************************       Методы акцепторы        ************************************
        EllipticCurveGF2& EllipticPointGF2::getCurve()
        {
                return *_curve;
        }
    Polynom& EllipticPointGF2::getX()
        {
                 if(!isInfinite()) return *_x;
                 throw new Exception("Точка на бесконечности");
        }
    Polynom& EllipticPointGF2::getY()
        {
                if(!isInfinite()) return *_y;
                throw new Exception("Точка на бесконечности");
        }
        EllipticPointGF2& EllipticPointGF2::setXY(Polynom &x, Polynom &y)
        {
                bool infinite = _infinite;
                _infinite = false;
                *_x = x;
                *_y = y;
        _x->Mod(_curve->getModule());
        _y->Mod(_curve->getModule());
                if(!_curve->inGroup(*_x, *_y))
                {
                _infinite = infinite;
            throw new Exception("Точка не лежит на кривой");
                }
                return *this;
        }
        bool EllipticPointGF2::isInfinite() const
        {
                return _infinite;
        }
    EllipticPointGF2& EllipticPointGF2::setInfinite(bool infinite)
        {
                _infinite = infinite;
        return *this;
        }
//*********************************       Операции сравнения        *****************************
    bool operator==(const EllipticPointGF2 &ePoint1, const EllipticPointGF2 &ePoint2)
        {
                if(ePoint1._curve->isSuperSingular() != ePoint2._curve->isSuperSingular())
            return false;
                if(ePoint1.isInfinite() && ePoint2.isInfinite())
            return true;
        if(*ePoint1._curve != *ePoint2._curve)
            return false;

        return  *ePoint1._x == *ePoint2._x && *ePoint1._y == *ePoint2._y;
        }
    bool operator!=(const EllipticPointGF2 &ePoint1, const EllipticPointGF2 &ePoint2)
        {
                return !(ePoint1 == ePoint2);
        }
//***********************************************************************************************
//**************************   Операция взятия противоположной точки   **************************
        EllipticPointGF2& EllipticPointGF2::Negate()
        {
                return Negate(*this);
        }
//***********************************************************************************************
//*****************************        Операция сложение        *********************************
        EllipticPointGF2& EllipticPointGF2::operator+=(EllipticPointGF2 &ePoint)
        {
                return Add(*this, ePoint);
        }
//***********************************************************************************************
//******************************      Операция удвоения       ***********************************
    EllipticPointGF2& EllipticPointGF2::Double()
        {
                return this->Double(*this);
        }
//***********************************************************************************************
//**************************    Операция умножения на константу    ******************************
    EllipticPointGF2& EllipticPointGF2::operator*=(Integer &i)
    {
        return Mul(*this, i);
    }
//***********************************************************************************************
//*********************************    Генерация точки    ***************************************
        EllipticPointGF2& EllipticPointGF2::Generate()
        {
                return GenerateImpl();
        }
//***********************************************************************************************
//**************************    Генерация точки  с упаковкой данных *****************************
        EllipticPointGF2& EllipticPointGF2::WrappingGenerate(const Polynom & xforwrap)
        {
                return GenerateImpl(&xforwrap);
        }

        Polynom EllipticPointGF2::findYOddCase(const Polynom & right) // решение уравнения Y^2 + Y = right, n = 2k+1
        {
                Polynom result(right), temp(right);
                uint n = _curve->getModule().getNumberBits()-1;
                uint k = n / 2;
                Integer four("4");

                for(uint i = 0; i < k; i++)
                {
                        temp.ModPow(temp, four, _curve->getModule());
                        result.ModAdd(result, temp, _curve->getModule());
                }
                return result;
        }
        Polynom EllipticPointGF2::findYEvenCase(const Polynom & right) // решение уравнения Y^2 + Y = right, n = 2k
        {
                Matrix T(createGenerationMatrix());
                Polynom result(T.SolveLinearEquationSystem(T, right));
                // Сдвиг влево на 1 бит, т.к. y0 = 1 и 0
                result <<= 1;
                return result;
        }
        Matrix EllipticPointGF2::createGenerationMatrix()
        {
                std::vector<Polynom *> vec;
                Polynom x("01"), x_square("001"), res;
                AAL::Integer two("2");

                // сотавление матрицы x^i + (x^i)^2 (mod m(x)), i = 1,..., deg(m(x)) - 1; deg(m(x)) = n
                uint n = getCurve().getModule().getNumberBits() - 1;
                for(uint i = 1; i < n; i++)
                {
                        res.ModAdd(x, x_square, getCurve().getModule());
                        vec.push_back(new Polynom(res));
                        x <<= 1;
                        x_square = x;
                        x_square.ModPow(x_square, two, getCurve().getModule());
                }
                Matrix matrix(Matrix::ON_LINE, n - 1, n - 1, vec);

                for(std::vector<Polynom *>::iterator iterator = vec.begin(); iterator != vec.end(); ++iterator)
                {
                        delete (*iterator);
                }
                matrix.Transpose();
                return matrix;
        }
               PolynomGF2_m_4& EllipticPointGF2::findRo(Polynom &module, PolynomGF2_m_4 &b )
        {
                PolynomGF2_m_4 t("101","111","110","100",module.ToString()),t1,a,a_2,s_3,s_2,r1,r2;
                PolynomGF2_m_4 s("0","1","1","0",module.ToString());
                Integer f;
                std::string str;
                int m = module.getNumberBits() - 1;
                f.Pow(2,4*m);
                f = (f - 1)/15;
                str = f.ToString();
                t.setModule(module);
                t1.setModule(module);
                a.setModule(module);
                a_2.setModule(module);
                s_3.setModule(module);
                s_2.setModule(module);
                r1.setModule(module);
                r2.setModule(module);
                s.setModule(module);

                t1.Pow(t,f);
                //s.Sqrt(two,module);
                str = t1.getA0().ToString();
                str = t1.getA1().ToString();
                str = t1.getA2().ToString();
                str = t1.getA3().ToString();

                str = s.getA0().ToString();
                str = s.getA1().ToString();
                str = s.getA2().ToString();
                str = s.getA3().ToString();

                a  = t1;
                a_2.Pow(a,Integer(2));
                str = a_2.getA0().ToString();
                str = a_2.getA1().ToString();
                str = a_2.getA2().ToString();
                str = a_2.getA3().ToString();


                r1.Add(a_2,a);
                str = r1.getA0().ToString();
                str = r1.getA1().ToString();
                str = r1.getA2().ToString();
                str = r1.getA3().ToString();

                s_3.Pow(s,Integer(3));
                str = s_3.getA0().ToString();
                str = s_3.getA1().ToString();
                str = s_3.getA2().ToString();
                str = s_3.getA3().ToString();

                s_2.Pow(s,Integer(2));
                str = s_2.getA0().ToString();
                str = s_2.getA1().ToString();
                str = s_2.getA2().ToString();
                str = s_2.getA3().ToString();

                r2.Add(s_3,s_2);
                str = r2.getA0().ToString();
                str = r2.getA1().ToString();
                str = r2.getA2().ToString();
                str = r2.getA3().ToString();

                while(r1 != r2)
                {
                        a.Mul(a,t1);
                        str = a.getA0().ToString();
                        str = a.getA1().ToString();
                        str = a.getA2().ToString();
                        str = a.getA3().ToString();

                a_2.Pow(a,Integer(2));
                str = a_2.getA0().ToString();
                str = a_2.getA1().ToString();
                str = a_2.getA2().ToString();
                str = a_2.getA3().ToString();


                r1.Add(a_2,a);
                str = r1.getA0().ToString();
                str = r1.getA1().ToString();
                str = r1.getA2().ToString();
                str = r1.getA3().ToString();

                s_3.Pow(s,Integer(3));
                str = s_3.getA0().ToString();
                str = s_3.getA1().ToString();
                str = s_3.getA2().ToString();
                str = s_3.getA3().ToString();

                s_2.Pow(s,Integer(2));
                str = s_2.getA0().ToString();
                str = s_2.getA1().ToString();
                str = s_2.getA2().ToString();
                str = s_2.getA3().ToString();

                r2.Add(s_3,s_2);
                str = r2.getA0().ToString();
                str = r2.getA1().ToString();
                str = r2.getA2().ToString();
                str = r2.getA3().ToString();
                }
                PolynomGF2_m_4 *result;
                result  = new PolynomGF2_m_4();
                result->setModule(module);
                *result = a;
                str = a.getA0().ToString();
                str = a.getA1().ToString();
                str = a.getA2().ToString();
                str = a.getA3().ToString();


                return  *result;

        }
PolynomGF2_m_4& EllipticPointGF2::DLK(EllipticPointGF2 &ePoint1,EllipticPointGF2 &ePoint2,PolynomGF2_m_4 &t,int n,PolynomGF2_m_4 &b,Polynom &mod)
{
    PolynomGF2_m_4* f = new PolynomGF2_m_4();
    PolynomGF2_m_4 x1,si,d,g,two("1","0","0","0",mod.ToString());
    PolynomGF2_m_4 x,y,al,bt;
    int i;
    int m = mod.getNumberBits() - 1;
    std:string str;
    char m1[100];
    Polynom xx,yy,all,btt;
    xx = ePoint1.getX();
    yy = ePoint1.getY();
    all = ePoint2.getX();
    btt = ePoint2.getY();
    f->setOne(); //f = 1
    f->setModule(mod);
    x.setModule(mod);
    x.setByIndex(xx,0);  //x
    str = x.getA0().ToString();
    str = x.getA1().ToString();
    str = x.getA2().ToString();
    str = x.getA3().ToString();
    y.setModule(mod);
    y.setByIndex(yy,0); //y
    str = y.getA0().ToString();
    str = y.getA1().ToString();
    str = y.getA2().ToString();
    str = y.getA3().ToString();

    al.setModule(mod);
    al.setByIndex(all,0);//alpha
    str = al.getA0().ToString();
    str = al.getA1().ToString();
    str = al.getA2().ToString();
    str = al.getA3().ToString();

    bt.setModule(mod);
    bt.setByIndex(btt,0); //beta
    str = bt.getA0().ToString();
    str = bt.getA1().ToString();
    str = bt.getA2().ToString();
    str = bt.getA3().ToString();

    for(i = 1; i <= n ; i++)
    {
    al.Pow(al,Integer(2));// alpha = (alpha^2)
    str = al.getA0().ToString();
    str = al.getA1().ToString();
    str = al.getA2().ToString();
    str = al.getA3().ToString();

    bt.Pow(bt,Integer(2));// beta = (beta^2)
    str = bt.getA0().ToString();
    str = bt.getA1().ToString();
    str = bt.getA2().ToString();
    str = bt.getA3().ToString();
    PolynomGF2_m_4 z;
    z.setModule(mod) ;
    z.Add(al,x); //z = alpha+x
    str = z.getA0().ToString();
    str = z.getA1().ToString();
    str = z.getA2().ToString();
    str = z.getA3().ToString();
    PolynomGF2_m_4 w, alx;
    w.setModule(mod);
    alx.setModule(mod);
    alx.Mul(al,x); //alpha*x
    str = alx.getA0().ToString();
    str = alx.getA1().ToString();
    str = alx.getA2().ToString();
    str = alx.getA3().ToString();

    w.Add(z,alx); //z + alpha*x
    str = w.getA0().ToString();
    str = w.getA1().ToString();
    str = w.getA2().ToString();
    str = w.getA3().ToString();

    w.Add(w,bt); //z+ alpha*x + beta
    str = w.getA0().ToString();
    str = w.getA1().ToString();
    str = w.getA2().ToString();
    str = w.getA3().ToString();

    w.Add(w,y);//z + alpha*x+beta+y
    str = w.getA0().ToString();
    str = w.getA1().ToString();
    str = w.getA2().ToString();
    str = w.getA3().ToString();

    w.Add(w,b);//w = z + alpha*x+beta+y +b
    str = w.getA0().ToString();
    str = w.getA1().ToString();
    str = w.getA2().ToString();
    str = w.getA3().ToString();

     PolynomGF2_m_4 zt, t_2,mlt,one("1","0","0","0",mod.ToString()),zpls1;
   zt.setModule(mod);
   t_2.setModule(mod);
   mlt.setModule(mod);
   zpls1.setModule(mod);
   zt.Mul(z,t);// z*t
    str = zt.getA0().ToString();
    str = zt.getA1().ToString();
    str = zt.getA2().ToString();
    str = zt.getA3().ToString();

    t_2.Pow(t,Integer(2));// t^2
    str = t_2.getA0().ToString();
    str = t_2.getA1().ToString();
    str = t_2.getA2().ToString();
    str = t_2.getA3().ToString();
    zpls1.Add(z,one); //z+1
   str = zpls1.getA0().ToString();
    str = zpls1.getA1().ToString();
    str = zpls1.getA2().ToString();
    str = zpls1.getA3().ToString();
   zpls1.Mul(zpls1,t_2); //(z+1)*t^2
   str = zpls1.getA0().ToString();
    str = zpls1.getA1().ToString();
    str = zpls1.getA2().ToString();
    str = zpls1.getA3().ToString();

   mlt.Add(w,zt);// w+z*t
   str = mlt.getA0().ToString();
    str = mlt.getA1().ToString();
    str = mlt.getA2().ToString();
    str = mlt.getA3().ToString();


   mlt.Add(mlt,zpls1);//w+z*t +(z+1)*t^2
       str = mlt.getA0().ToString();
    str = mlt.getA1().ToString();
    str = mlt.getA2().ToString();
    str = mlt.getA3().ToString();

   f->Mul(*f,mlt); //f*(w+z*t +(z+1)*t^2)
    str = f->getA0().ToString();
    str = f->getA1().ToString();
    str = f->getA2().ToString();
    str = f->getA3().ToString();



        Integer pw(4);
        //pw.Pow(2,m-1);
        y.Pow(y,pw);//x=x^(2^(m-1))
        x.Pow(x,pw);//y = y^(2^(m-1))
    }
    Integer three_n;
        three_n.Mul(2,n);
        three_n.Pow(2,three_n);
    f->Pow(*f,three_n-1);//f= f^(2^((2m)-1))
    str = f->getA0().ToString();
    str = f->getA1().ToString();
    str = f->getA2().ToString();
    str = f->getA3().ToString();
    return *f;
}

//***********************************************************************************************
//*******************  Класс точка суперсингулярной эллиптичиской кривой над GF(2^n)   **********
//********************************      Конструкторы       **************************************
        SuperSingularEllipticPoint::SuperSingularEllipticPoint()
        {
                _curve = new SuperSingularEllipticCurve();
        _x = new Polynom();
        _y = new Polynom();
        _infinite = true;
        }
    SuperSingularEllipticPoint::SuperSingularEllipticPoint(const SuperSingularEllipticCurve &eCurve)
        {
                _curve = new SuperSingularEllipticCurve(eCurve);
        _x = new Polynom();
        _y = new Polynom();
        _infinite = true;
        }
    SuperSingularEllipticPoint::SuperSingularEllipticPoint(const SuperSingularEllipticPoint &ePoint)
        {
                _curve = new SuperSingularEllipticCurve(dynamic_cast<SuperSingularEllipticCurve &>(*ePoint._curve));
        _x = new Polynom(*ePoint._x);
        _y = new Polynom(*ePoint._y);
        _infinite = ePoint._infinite;
        }
        SuperSingularEllipticPoint::~SuperSingularEllipticPoint()
        {
                delete _curve, _x, _y;
        }
//***********************************************************************************************
//****************************       Методы акцепторы        ************************************
        SuperSingularEllipticCurve& SuperSingularEllipticPoint::setCurve(EllipticCurveGF2 &eCurve)
        {
                if(!eCurve.isSuperSingular())
                        throw new Exception("Кривая не суперсингулярна");
                //dynamic_cast<SuperSingularEllipticCurve &>(*_curve) = eCurve;
                SuperSingularEllipticCurve & _curveref = dynamic_cast<SuperSingularEllipticCurve &>(*_curve);
                _curveref = dynamic_cast<SuperSingularEllipticCurve &>(eCurve);
        if(!isInfinite())
        {
            _x->Mod(_curve->getModule());
            _y->Mod(_curve->getModule());
            //if(!_curve->inGroup(*_x, *_y))
                        if(!_curveref.inGroup(*_x, *_y))
                _infinite = true;
        }
        //return dynamic_cast<SuperSingularEllipticCurve &>(*_curve);
                return _curveref;
        }


//***********************************************************************************************
//****************************         Унарные операции          ********************************
    SuperSingularEllipticPoint& SuperSingularEllipticPoint::operator=(const SuperSingularEllipticPoint &ePoint)
        {
                dynamic_cast<SuperSingularEllipticCurve &>(*_curve) = dynamic_cast<SuperSingularEllipticCurve &>(*ePoint._curve);
        *_x = *ePoint._x;
        *_y = *ePoint._y;
        _infinite = ePoint._infinite;
        return *this;
        }
//***********************************************************************************************
//**************************   Операция взятия противоположной точки   **************************
        EllipticPointGF2& SuperSingularEllipticPoint::Negate()
        {
                return EllipticPointGF2::Negate();
        }
        EllipticPointGF2& SuperSingularEllipticPoint::Negate(EllipticPointGF2& ePoint)
        {
                if(!ePoint._curve->isSuperSingular())
                        throw new Exception("Не все точки лежат на суперсингулярных кривых");// TODO: поменять
                if(ePoint.isInfinite())
                        return setInfinite(true);
                this->setInfinite(false);
                SuperSingularEllipticCurve & _curveref = dynamic_cast<SuperSingularEllipticCurve &>(*_curve);
                //dynamic_cast<SuperSingularEllipticCurve &>(*this->_curve) = dynamic_cast<SuperSingularEllipticCurve &>(ePoint.getCurve());
                _curveref = dynamic_cast<SuperSingularEllipticCurve &>(ePoint.getCurve());
                *this->_x = *ePoint._x;
                this->_y->ModAdd(*ePoint._y, _curveref.getA3(), _curveref.getModule());
                return *this;
        }
//***********************************************************************************************
//*****************************        Операция сложение        *********************************
        /*SuperSingularEllipticPoint operator+(SuperSingularEllipticPoint &ePoint1, SuperSingularEllipticPoint &ePoint2)
        {
                SuperSingularEllipticPoint res;
        return res.Add(ePoint1, ePoint2);
        }*/
    EllipticPointGF2& SuperSingularEllipticPoint::Add(EllipticPointGF2 &ePoint1, EllipticPointGF2 &ePoint2)
        {
                if(!(ePoint1._curve->isSuperSingular() && ePoint2._curve->isSuperSingular()))
                        throw  new Exception("Не все точки лежат на суперсингулярных кривых");// TODO: поменять
                if(*ePoint1._curve != *ePoint2._curve)
            throw new Exception("Точки лежат на разных кривых");

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

                SuperSingularEllipticPoint negateEPoint1;
                negateEPoint1.Negate(ePoint1);
                if(negateEPoint1 == ePoint2)
                        return setInfinite(true);

                SuperSingularEllipticCurve & _curveref = dynamic_cast<SuperSingularEllipticCurve &>(*_curve);
                //dynamic_cast<SuperSingularEllipticCurve &>(*this->_curve) = dynamic_cast<SuperSingularEllipticCurve &>(*ePoint1._curve);
                _curveref = dynamic_cast<SuperSingularEllipticCurve &>(*ePoint1._curve);

        setInfinite(false);

        Polynom l, p, x1(*ePoint1._x), x2(*ePoint2._x), y1(*ePoint1._y), y2(*ePoint2._y);
        x1.Mod(_curveref.getModule());
        x2.Mod(_curveref.getModule());

        if(x1 == x2)
        {
            y1.Mod(_curveref.getModule());
            y2.Mod(_curveref.getModule());

            l.ModMul(x1, x1, _curveref.getModule());
            l.ModAdd(l, _curveref.getA4(), _curveref.getModule());
                        p.Inverse(_curveref.getA3(), _curveref.getModule());
                        l.ModMul(l, p, _curveref.getModule());
                        _x->ModMul(l, l, _curveref.getModule());
                        _y->ModAdd(x1, *_x, _curveref.getModule());
                _y->ModMul(*_y, l, _curveref.getModule());
                _y->ModAdd(*_y, y1, _curveref.getModule());
                        _y->ModAdd(*_y, _curveref.getA3(), _curveref.getModule());
        }
        else
        {
            l.ModAdd(y2, y1, _curveref.getModule());
            p.ModAdd(x2, x1, _curveref.getModule());
                        p.Inverse(_curveref.getModule());
                l.ModMul(l, p, _curveref.getModule());
                        _x->ModMul(l, l, _curveref.getModule());
                _x->ModAdd(*_x, x1, _curveref.getModule());
                _x->ModAdd(*_x, x2, _curveref.getModule());
                        _y->ModAdd(x1, *_x, _curveref.getModule());
                _y->ModMul(*_y, l, _curveref.getModule());
                _y->ModAdd(*_y, y1, _curveref.getModule());
                        _y->ModAdd(*_y,  _curveref.getA3(), _curveref.getModule());
        }
        return *this;
        }
//***********************************************************************************************
//******************************      Операция удвоения       ***********************************
        EllipticPointGF2& SuperSingularEllipticPoint::Double()
        {
                return EllipticPointGF2::Double();
        }
    EllipticPointGF2& SuperSingularEllipticPoint::Double(EllipticPointGF2 &ePoint)
        {
                if(!ePoint._curve->isSuperSingular())
                        throw  new Exception("Точка лежит на суперсингулярной кривой");// TODO: поменять

        if(ePoint.isInfinite())
            return setInfinite(true);

                SuperSingularEllipticPoint negateEPoint;
                negateEPoint.Negate(ePoint);
                if(negateEPoint == ePoint)
                        return setInfinite(true);

                 SuperSingularEllipticCurve & _curveref = dynamic_cast<SuperSingularEllipticCurve &>(*_curve);
                //dynamic_cast<SuperSingularEllipticCurve &>(*this->_curve) = dynamic_cast<SuperSingularEllipticCurve &>(*e._curve);
                _curveref = dynamic_cast<SuperSingularEllipticCurve &>(*ePoint._curve);

        setInfinite(false);
                Polynom l, p, x(*ePoint._x), y(*ePoint._y);
                y.Mod(_curveref.getModule());

        l.ModMul(x, x, _curveref.getModule());
        l.ModAdd(l, _curveref.getA4(), _curveref.getModule());
                p.Inverse(_curveref.getA3(), _curveref.getModule());
                l.ModMul(l, p, _curveref.getModule());
                _x->ModMul(l, l, _curveref.getModule());
                _y->ModAdd(x, *_x, _curveref.getModule());
            _y->ModMul(*_y, l, _curveref.getModule());
            _y->ModAdd(*_y, y, _curveref.getModule());
                _y->ModAdd(*_y, _curveref.getA3(), _curveref.getModule());
                return *this;
        }

//***********************************************************************************************
//**************************    Операция умножения на константу    ******************************
    /*SuperSingularEllipticPoint operator*(const SuperSingularEllipticPoint &ePoint, const Integer &i)
    {
        SuperSingularEllipticPoint res, copy_ePoint(ePoint);
        Integer copy_i(i);
        return res.Mul(copy_ePoint, copy_i);
    }

    SuperSingularEllipticPoint operator*(const Integer &i, const SuperSingularEllipticPoint &ePoint)
    {
        SuperSingularEllipticPoint res, copy_ePoint(ePoint);
        Integer copy_i(i);
        return res.Mul(copy_ePoint, copy_i);
    }

    SuperSingularEllipticPoint& SuperSingularEllipticPoint::operator*=(Integer &i)
    {
        return Mul(*this, i);
    }
        SuperSingularEllipticPoint& SuperSingularEllipticPoint::Mul(Integer &i, SuperSingularEllipticPoint &ePoint)
        {
                return Mul(ePoint, i);
        }*/
        EllipticPointGF2& SuperSingularEllipticPoint::Mul(EllipticPointGF2 &ePoint, const Integer &integer)
        {
                if(!ePoint._curve->isSuperSingular())
                        throw new Exception("Точка лежит на суперсингулярной кривой");// TODO: поменять

        if(ePoint.isInfinite() || integer.isZero())
                {
                        setInfinite(true);
            return *this;
                }

        SuperSingularEllipticPoint p(dynamic_cast<SuperSingularEllipticPoint &>(ePoint));
                setInfinite(true);
                dynamic_cast<SuperSingularEllipticCurve &>(*this->_curve) = dynamic_cast<SuperSingularEllipticCurve &>(*ePoint._curve);

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
//**************************    Генерация точки                    ******************************
        SuperSingularEllipticPoint& SuperSingularEllipticPoint::GenerateImpl(const Polynom * xforwrap)
        {
        if(!dynamic_cast<SuperSingularEllipticCurve *>(_curve)->getA3().isOne())
                        throw new Exception("Коэффициент a3 не равен 1");

                if(xforwrap != NULL)
                        if(getCurve().getModule().getNumberBits() - xforwrap->getNumberBits() < 4)
                                throw new Exception("В размещаемой информации должно быть на 4 бита меньше чем в модуле");

                uint n = _curve->getModule().getNumberBits()-1;

                SuperSingularEllipticCurve & _curveref = dynamic_cast<SuperSingularEllipticCurve &>(*_curve);
                Polynom x, y;
                do
                {
                        if(xforwrap == NULL)
                                x.Generate(_curveref.getModule());
                        else
                                x.WrappingGenerate(Polynom(*xforwrap), _curveref.getModule());
                }
                while(!_curveref.hasY(x));

                setInfinite(false);
                *_x = x;
                if(n % 2 == 1)
                        *_y = findYOddCase(_curveref.rightSide(x));
                else
                        *_y = findYEvenCase(_curveref.rightSide(x));
        _x->Mod(_curve->getModule());
        _y->Mod(_curve->getModule());

        return *this;
        }
//-----------------------------------------------------------------------------------

//***********************************************************************************************
//****************************  Класс НЕСуперсингулярных Эллиптических кривых над GF(2^n)   *******
//*********************************      Конструкторы       *************************************
        NonSuperSingularEllipticCurve::NonSuperSingularEllipticCurve()
        {
                _module = new Polynom("1101");
        _a2 = new Polynom("1");
                _a6 = new Polynom("1");
        }
        NonSuperSingularEllipticCurve::NonSuperSingularEllipticCurve(Polynom &module, Polynom &a2, Polynom &a6)
        {
                if(!module.isIrreducible())
            throw  new Exception("Модуль является приводимым многочленом");

        _module = new Polynom(module);
            _a2 = new Polynom(a2);
                _a6 = new Polynom(a6);
        }
        NonSuperSingularEllipticCurve::NonSuperSingularEllipticCurve(const NonSuperSingularEllipticCurve &eCurve)
        {
                _module = new Polynom(eCurve.getModule());
        _a2 = new Polynom(eCurve.getA2());
                _a6 = new Polynom(eCurve.getA6());
        }
        NonSuperSingularEllipticCurve::~NonSuperSingularEllipticCurve()
        {
                delete _module, _a2, _a6;
        }
//***********************************************************************************************
//*****************************        Методы акцепторы        **********************************
        Polynom& NonSuperSingularEllipticCurve::getA2() const
        {
            return *_a2;
        }
        Polynom& NonSuperSingularEllipticCurve::getA6() const
        {
                return *_a6;
        }
        Polynom& NonSuperSingularEllipticCurve::setModule(const Polynom &module)
        {
                if(!module.isIrreducible())
            throw new Exception("Модуль является приводимым многочленом");
        *_module = module;
        _a2->Mod(*_module);
                _a6->Mod(*_module);
        return *_module;
        }
        Polynom& NonSuperSingularEllipticCurve::setA2(Polynom &a2)
        {
                *_a2 = a2;
        _a2->Mod(*_module);
        return *_a2;
        }
        Polynom& NonSuperSingularEllipticCurve::setA6(Polynom &a6)
        {
                *_a6 = a6;
        _a6->Mod(*_module);
        return *_a6;
        }
        bool NonSuperSingularEllipticCurve::isSuperSingular() const
        {
                return false;
        }
        bool NonSuperSingularEllipticCurve::isNonSuperSingular() const
        {
                return !isSuperSingular();
        }
//***********************************************************************************************
//***************************          Унарные операции         *********************************
        NonSuperSingularEllipticCurve& NonSuperSingularEllipticCurve::operator=(const NonSuperSingularEllipticCurve &eCurve)
        {
                *_module = *eCurve._module;
        *_a2 = *eCurve._a2;
                *_a6 = *eCurve._a6;
        return *this;
        }
//***********************************************************************************************
//********************************      Операции сравнения      *********************************
        bool NonSuperSingularEllipticCurve::equals(const EllipticCurveGF2 &eCurve) const
        {
                const NonSuperSingularEllipticCurve * pECurve = dynamic_cast<const NonSuperSingularEllipticCurve *>(&eCurve);
                return (pECurve == 0) ? false :
                (*this->_module == *pECurve->_module && *this->_a2 == *pECurve->_a2 && *this->_a6 == *pECurve->_a6);
        }
//***********************************************************************************************
//*************************        Принадлежность точки к кривой      ***************************
    bool NonSuperSingularEllipticCurve::inGroup(Polynom &x, Polynom &y) const
        {
                Polynom temp1;
                temp1.ModMul(y, y, *_module);
                Polynom temp2;
                temp2.ModMul(x, y, *_module);
                temp2.ModAdd(temp2, temp1, *_module);
                temp1 = rightSide(x);

                return (temp2 == temp1);
        }
//***********************************************************************************************
//*************************        Вычисление правой части уравнения      ***********************
        Polynom NonSuperSingularEllipticCurve::rightSide(Polynom &x) const
        {
                Polynom temp1;
                temp1.ModMul(x, x, *_module);
                temp1.ModMul(x, temp1, *_module);
                Polynom temp2;
                temp2.ModMul(x, x, *_module);
                temp2.ModMul(*_a2, temp2, *_module);
                temp1.ModAdd(temp1, temp2, *_module);
                temp1.ModAdd(temp1, *_a6, *_module);
                return temp1;
        }
//***********************************************************************************************
//*************************   Проверка на существование Y для данного X   ***********************
        bool NonSuperSingularEllipticCurve::hasY(Polynom &x) const
        {
                if(x.isZero())
                        return false;

                Polynom right(rightSide(x)), temp;

                right.ModMul(right, getInvertSquare(x), getModule());

                return right.isZero() || temp.Trace(right, getModule()).isZero();
        }
        Polynom NonSuperSingularEllipticCurve::getInvertSquare(Polynom &x) const
        {
                Integer two("2");
                Polynom ixSquare(x);
                ixSquare.Inverse(getModule());
                ixSquare.ModPow(ixSquare, two, getModule());
                return ixSquare;
        }
//***********************************************************************************************
//*******************  Класс точка НЕсуперсингулярной эллиптичиской кривой над GF(2^n)   **********
//********************************      Конструкторы       **************************************
        NonSuperSingularEllipticPoint::NonSuperSingularEllipticPoint()
        {
                _curve = new NonSuperSingularEllipticCurve();
        _x = new Polynom();
        _y = new Polynom();
        _infinite = true;
        }
    NonSuperSingularEllipticPoint::NonSuperSingularEllipticPoint(const NonSuperSingularEllipticCurve &eCurve)
        {
                _curve = new NonSuperSingularEllipticCurve(eCurve);
        _x = new Polynom();
        _y = new Polynom();
        _infinite = true;
        }
    NonSuperSingularEllipticPoint::NonSuperSingularEllipticPoint(const NonSuperSingularEllipticPoint &ePoint)
        {
                _curve = new NonSuperSingularEllipticCurve(dynamic_cast<NonSuperSingularEllipticCurve &>(*ePoint._curve));
        _x = new Polynom(*ePoint._x);
        _y = new Polynom(*ePoint._y);
        _infinite = ePoint._infinite;
        }
        NonSuperSingularEllipticPoint::~NonSuperSingularEllipticPoint()
        {
                delete _curve, _x, _y;
        }
//***********************************************************************************************
//****************************       Методы акцепторы        ************************************
        NonSuperSingularEllipticCurve& NonSuperSingularEllipticPoint::setCurve(EllipticCurveGF2 &eCurve)
        {
                if(!eCurve.isNonSuperSingular())
                        throw new Exception("Кривая не несуперсингулярна");

                NonSuperSingularEllipticCurve & _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(*_curve);
                _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(eCurve);
        if(!isInfinite())
        {
            _x->Mod(_curve->getModule());
            _y->Mod(_curve->getModule());
                        if(!_curveref.inGroup(*_x, *_y))
                _infinite = true;
        }
                return _curveref;
        }
//***********************************************************************************************
//****************************         Унарные операции          ********************************
    NonSuperSingularEllipticPoint& NonSuperSingularEllipticPoint::operator=(const NonSuperSingularEllipticPoint &ePoint)
        {
                dynamic_cast<NonSuperSingularEllipticCurve &>(*_curve) = dynamic_cast<NonSuperSingularEllipticCurve &>(*ePoint._curve);
        *_x = *ePoint._x;
        *_y = *ePoint._y;
        _infinite = ePoint._infinite;
        return *this;
        }
//***********************************************************************************************
//**************************   Операция взятия противоположной точки   **************************
        EllipticPointGF2& NonSuperSingularEllipticPoint::Negate()
        {
                return EllipticPointGF2::Negate();
        }
        EllipticPointGF2& NonSuperSingularEllipticPoint::Negate(EllipticPointGF2& ePoint)
        {
                if(!ePoint._curve->isNonSuperSingular())
                        throw new Exception("Не все точки лежат на суперсингулярных кривых");// TODO: поменять
                if(ePoint.isInfinite())
                        return setInfinite(true);
                this->setInfinite(false);
                NonSuperSingularEllipticCurve & _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(*_curve);
                _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(ePoint.getCurve());
                *this->_x = *ePoint._x;
                this->_y->ModAdd(*ePoint._x, *ePoint._y, _curveref.getModule());
                return *this;
        }
//***********************************************************************************************
//*****************************        Операция сложение        *********************************
    EllipticPointGF2& NonSuperSingularEllipticPoint::Add(EllipticPointGF2 &ePoint1, EllipticPointGF2 &ePoint2)
        {
                if(!(ePoint1._curve->isNonSuperSingular() && ePoint2._curve->isNonSuperSingular()))
                        throw  new Exception("Не все точки лежат на несуперсингулярных кривых");// TODO: поменять
                if(*ePoint1._curve != *ePoint2._curve)
            throw new Exception("Точки лежат на разных кривых");

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

                NonSuperSingularEllipticPoint negateEPoint1;
                negateEPoint1.Negate(ePoint1);
                if(negateEPoint1 == ePoint2)
                        return setInfinite(true);

                NonSuperSingularEllipticCurve & _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(*_curve);
                _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(*ePoint1._curve);

        setInfinite(false);

        Polynom l, p, x1(*ePoint1._x), x2(*ePoint2._x), y1(*ePoint1._y), y2(*ePoint2._y);
        x1.Mod(_curveref.getModule());
        x2.Mod(_curveref.getModule());

        if(x1 == x2)
        {
            y1.Mod(_curveref.getModule());
            y2.Mod(_curveref.getModule());

                        p.Inverse(x1, _curveref.getModule());
                        l.ModMul(y1, p, _curveref.getModule());
                        l.ModAdd(x1, l, _curveref.getModule());
                        _x->ModMul(l, l, _curveref.getModule());
                        _x->ModAdd(*_x, l, _curveref.getModule());
                        _x->ModAdd(*_x, _curveref.getA2(), _curveref.getModule());
                        _y->ModMul(x1, x1, _curveref.getModule());
                        p.ModMul(l, *_x, _curveref.getModule());
                        p.ModAdd(p, *_x, _curveref.getModule());
                        _y->ModAdd(*_y, p, _curveref.getModule());
        }
        else
        {
                        l.ModAdd(y2, y1, _curveref.getModule());
                        p.ModAdd(x2, x1, _curveref.getModule());
                        p.Inverse(_curveref.getModule());
                        l.ModMul(l, p, _curveref.getModule());
                        _x->ModMul(l, l, _curveref.getModule());
                        _x->ModAdd(*_x, l, _curveref.getModule());
                        _x->ModAdd(*_x, _curveref.getA2(), _curveref.getModule());
                        _x->ModAdd(*_x, x1, _curveref.getModule());
                        _x->ModAdd(*_x, x2, _curveref.getModule());
                        _y->ModAdd(*_x, x1, _curveref.getModule());
                        _y->ModMul(*_y, l, _curveref.getModule());
                        _y->ModAdd(*_y, y1, _curveref.getModule());
                        _y->ModAdd(*_y, *_x, _curveref.getModule());
        }
        return *this;
        }
//***********************************************************************************************
//******************************      Операция удвоения       ***********************************
        EllipticPointGF2& NonSuperSingularEllipticPoint::Double()
        {
                return EllipticPointGF2::Double();
        }
    EllipticPointGF2& NonSuperSingularEllipticPoint::Double(EllipticPointGF2 &ePoint)
        {
                if(!ePoint._curve->isNonSuperSingular())
                        throw new  Exception("Точка лежит на несуперсингулярной кривой");// TODO: поменять

        if(ePoint.isInfinite())
            return setInfinite(true);

                NonSuperSingularEllipticPoint negateEPoint;
                negateEPoint.Negate(ePoint);
                if(negateEPoint == ePoint)
                        return setInfinite(true);

                 NonSuperSingularEllipticCurve & _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(*_curve);
                _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(*ePoint._curve);

        setInfinite(false);

                Polynom l, p, x(*ePoint._x), y(*ePoint._y);
                y.Mod(_curveref.getModule());

                y.Mod(_curveref.getModule());
                p.Inverse(x, _curveref.getModule());
                l.ModMul(y, p, _curveref.getModule());
                l.ModAdd(x, l, _curveref.getModule());
                _x->ModMul(l, l, _curveref.getModule());
                _x->ModAdd(*_x, l, _curveref.getModule());
                _x->ModAdd(*_x, _curveref.getA2(), _curveref.getModule());
                _y->ModMul(x, x, _curveref.getModule());
                p.ModMul(l, *_x, _curveref.getModule());
                p.ModAdd(p, *_x, _curveref.getModule());
                _y->ModAdd(*_y, p, _curveref.getModule());
                return *this;
        }

//***********************************************************************************************
//**************************    Операция умножения на константу    ******************************
        EllipticPointGF2& NonSuperSingularEllipticPoint::Mul(EllipticPointGF2 &ePoint, const Integer &integer)
        {
                if(!ePoint._curve->isNonSuperSingular())
                        throw new Exception("Точка лежит на несуперсингулярной кривой");// TODO: поменять

        if(ePoint.isInfinite() || integer.isZero())
                {
                        setInfinite(true);
            return *this;
                }

        NonSuperSingularEllipticPoint p(dynamic_cast<NonSuperSingularEllipticPoint &>(ePoint));
                setInfinite(true);
                dynamic_cast<NonSuperSingularEllipticCurve &>(*this->_curve) = dynamic_cast<NonSuperSingularEllipticCurve &>(*ePoint._curve);

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
//**************************    Генерация точки                    ******************************
        NonSuperSingularEllipticPoint& NonSuperSingularEllipticPoint::GenerateImpl(const Polynom * xforwrap)
        {
                if(xforwrap != NULL)
                        if(getCurve().getModule().getNumberBits() - xforwrap->getNumberBits() < 4)
                                throw new Exception("В размещаемой информации должно быть на 4 бита меньше чем в модуле");

        uint n = _curve->getModule().getNumberBits()-1;

                NonSuperSingularEllipticCurve & _curveref = dynamic_cast<NonSuperSingularEllipticCurve &>(*_curve);
                Polynom x, y, changedright;
                Integer two("2");
                do
                {
                         if(xforwrap == NULL)
                                x.Generate(_curveref.getModule());
                        else
                                x.WrappingGenerate(Polynom(*xforwrap), _curveref.getModule());
                }
                while(!_curveref.hasY(x));

                setInfinite(false);
                changedright.ModMul(_curveref.rightSide(x), _curveref.getInvertSquare(x), _curveref.getModule());

                *_x = x;
                if(n % 2 == 1)
                        *_y = findYOddCase(changedright);
                else
                        *_y = findYEvenCase(changedright);
                _y->ModMul(*_x, *_y, _curveref.getModule());
        _x->Mod(_curve->getModule());
        _y->Mod(_curve->getModule());

        return *this;
        }
//***********************************************************************************************
}
