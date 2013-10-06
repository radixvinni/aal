/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF3n6.h"
#include "DecompositionManager.h"
#include "Converter.h"
#include <string>

namespace AAL
{

//***********************************  Конструкторы  *******************************************


//(c) Boldyrev, TEST(PolynomGF3N6, EmptyConstructor)
        PolynomN6::PolynomN6() :
        _a1(), _a2(), _a3(), _a4(), _a5(), _a6(), _module(),_modulePolynom()
        {
        }

//(c) Boldyrev, TEST(PolynomGF3N6, CopyConstructor)
        PolynomN6::PolynomN6(const PolynomN6 & polynom) :
        _a1(polynom._a1), _a2(polynom._a2), _a3(polynom._a3), _a4(polynom._a4), _a5(polynom._a5), _a6(polynom._a6),_module(polynom._module),_modulePolynom(polynom._modulePolynom)
        {
        }

        PolynomN6::PolynomN6(const PolynomGF3& a1, const PolynomGF3& a2, const PolynomGF3& a3, const PolynomGF3& a4,const PolynomGF3& a5,const PolynomGF3& a6,const PolynomGF3& mpolynom ,const PolynomGF3& modulePolynom) :
        _a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6),_module(mpolynom),_modulePolynom(modulePolynom)
        {
                //Добавить проверка модуля
        }

        PolynomN6::PolynomN6(const std::string dataString,const PolynomGF3& mpolynom ,const PolynomGF3& modulePolynom):
        _a1(), _a2(), _a3(), _a4(), _a5(), _a6(), _module(mpolynom),_modulePolynom(modulePolynom)

        {
           FromString(dataString);
        }
        PolynomN6::~PolynomN6()
        {
        }
                                                                                                
//**********************************************************************************************
//*************************  Преобразование и считывание из стpок ******************************
        std::string PolynomN6::ToString() const
        {
                std::string str;

                str += _a1.ToString() + " " + _a2.ToString()+ " " + _a3.ToString()+ " " + _a4.ToString()+ " " + _a5.ToString()+ " " + _a6.ToString();

                return str; 
        }
        void PolynomN6::FromString(std::string s)
        {
         std:: string ss(s),sss;
         /* Подумать над реализацией в цикле!
          while (ss.find_first_of(" ",0))
           {
            sss=ss.substr(0,ss.find_first_of(" ",0));
            a.Parse(sss);
            Edit38->Text=a.ToString().c_str();
            if (sss.length()==ss.length()) break;
            ss=ss.substr(ss.find_first_of(" ",0)+1,ss.length());
           }   */
           sss=ss.substr(0,ss.find_first_of(" ",0));
           if (sss.length()==ss.length()) throw std::out_of_range("в строке должно быть 6 элементов, разделенных пробелом");
           ss=ss.substr(ss.find_first_of(" ",0)+1,ss.length());
           _a1.Parse(sss);
           _a1%=_module;
           sss=ss.substr(0,ss.find_first_of(" ",0));
           if (sss.length()==ss.length()) throw std::out_of_range("в строке должно быть 6 элементов, разделенных пробелом");
           ss=ss.substr(ss.find_first_of(" ",0)+1,ss.length());
           _a2.Parse(sss);
           _a2%=_module;
           sss=ss.substr(0,ss.find_first_of(" ",0));
           if (sss.length()==ss.length()) throw std::out_of_range("в строке должно быть 6 элементов, разделенных пробелом");
           ss=ss.substr(ss.find_first_of(" ",0)+1,ss.length());
           _a3.Parse(sss);
           _a3%=_module;
           sss=ss.substr(0,ss.find_first_of(" ",0));
           if (sss.length()==ss.length()) throw std::out_of_range("в строке должно быть 6 элементов, разделенных пробелом");
           ss=ss.substr(ss.find_first_of(" ",0)+1,ss.length());
           _a4.Parse(sss);
           _a4%=_module;
           sss=ss.substr(0,ss.find_first_of(" ",0));
           if (sss.length()==ss.length()) throw std::out_of_range("в строке должно быть 6 элементов, разделенных пробелом");
           ss=ss.substr(ss.find_first_of(" ",0)+1,ss.length());
           _a5.Parse(sss);
           _a5%=_module;
           _a6.Parse(ss);
           _a6%=_module;
        }
//**********************************************************************************************
//***************************************  Методы акцепторы   **********************************
        bool PolynomN6::isZero() const
        {
                return (_a1.isZero() && _a2.isZero()&& _a3.isZero()&& _a4.isZero()&& _a5.isZero()&& _a6.isZero());
        }
        bool PolynomN6::isOne() const
        {
                return (_a1.isOne() && _a2.isZero()&& _a3.isZero()&& _a4.isZero()&& _a5.isZero()&& _a6.isZero());
        }
        void PolynomN6::setZero()
        {
                _a1.setZero();
                _a2.setZero();
                _a3.setZero();
                _a4.setZero();
                _a5.setZero();
                _a6.setZero();
        }
        void PolynomN6::setOne()
        {
                _a1.setOne();
                _a2.setZero();
                _a3.setZero();
                _a4.setZero();
                _a5.setZero();
                _a6.setZero();
        }
        void PolynomN6::setTwo()
        {
                _a1.setTwo();
                _a2.setZero();
                _a3.setZero();
                _a4.setZero();
                _a5.setZero();
                _a6.setZero();
        }

        const PolynomGF3& PolynomN6::getA1() const
        {
                return _a1;
        }
        const PolynomGF3& PolynomN6::getA2() const
        {
                return _a2;
        }
        const PolynomGF3& PolynomN6::getA3() const
        {
                return _a3;
        }
        const PolynomGF3& PolynomN6::getA4() const
        {
                return _a4;
        }
        const PolynomGF3& PolynomN6::getA5() const
        {
                return _a5;
        }
        const PolynomGF3& PolynomN6::getA6() const
        {
                return _a6;
        }
        const PolynomGF3& PolynomN6::getModulePolynom() const
        {
                return _modulePolynom;
        }
        const PolynomGF3& PolynomN6::getModule() const
        {
                return _module;
        }
        void PolynomN6::setA1(const PolynomGF3 & a)
        {
                _a1 = a;
                _a1%=_module;
        }
        void PolynomN6::setA2(const PolynomGF3 & a)
        {

                 _a2 = a;
                 _a2%=_module;
        }
        void PolynomN6::setA3(const PolynomGF3 & a)
        {
                 _a3 = a;
                 _a3%=_module;
        }
        void PolynomN6::setA4(const PolynomGF3 & a)
        {
                _a4 = a;
                _a4%=_module;
        }
        void PolynomN6::setA5(const PolynomGF3 & a)
        {
                _a5 = a;
                _a5%=_module;
        }
        void PolynomN6::setA6(const PolynomGF3 & a)
        {
                _a6 = a;
                _a6%=_module;
        }

        void PolynomN6::setModule(const PolynomGF3& modulePolynom)
        {        //Проверки на неприводимость
                _module = modulePolynom;
                _a1%=_module;
                _a2%=_module;
                _a3%=_module;
                _a4%=_module;
                _a5%=_module;
                _a6%=_module;

        }
        void PolynomN6::setModulePolynom(const PolynomGF3& modulePolynom)
        {       //Проверки на неприводимость
                _modulePolynom = modulePolynom;
                //Проверки на размер
                if((modulePolynom.getNumberBits()-1)!=6)
                        throw std::out_of_range("модулярные многочлен порождающий расширение поля должны быть степени 6");


        }
        //определение порядка группы
        Integer PolynomN6::getMulGroupOrder() const
        {

                uint lenm=_module.getNumberBits()-1;
                uint lenmp=_modulePolynom.getNumberBits()-1;
                Integer AA,BB,BBB,CC,CCC;
                AA.Parse("3");
                BB=lenm;
                BBB=lenmp;
                CC=BB*BBB;
                CCC.Pow(AA,CC);
                CCC=CCC-1;
                return CCC;
        }
        //тест на образующий элемент
        bool PolynomN6::isPrimitivity() const
        {
          uint lenm=_module.getNumberBits()-1;
          uint lenmp=_modulePolynom.getNumberBits()-1;
          uint n = lenm*lenmp - 1;
          std::vector<DecompositionMember> vector(DecompositionManager::Instance().getThreeDegreeDecomposition(n,false));
          Integer number, mersen;
          PolynomN6 plCur(*this), res(*this);
          res.setOne();
          for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
           {
            if (vector.size() == 1)
            return true;
            number = i->getNumber();
            PolynomN6 p1;
            mersen = (mersen.Pow(3, n) - 1)/number;
            p1.Pow(plCur, mersen);
            if (p1 == res)
            return false;
           }
          return true;
        }

//**********************************************************************************************
//************************************  Унарные операции   *************************************
        PolynomN6& PolynomN6::operator= (const PolynomN6& polynom)
        {
                if(this == &polynom)
                        return *this;
                        
                _a1 = polynom._a1;
                _a2 = polynom._a2;
                _a3 = polynom._a3;
                _a4 = polynom._a4;
                _a5 = polynom._a5;
                _a6 = polynom._a6;
                _modulePolynom = polynom._modulePolynom;
                _module=polynom._module;                
                return *this;
        }

//**********************************************************************************************
//*****************************    Операции сравнения    ***************************************
        bool operator==(const PolynomN6& a, const PolynomN6& b)
        {
                return (a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3 && a._a4 == b._a4&& a._a5 == b._a5&& a._a6 == b._a6 && a._modulePolynom == b._modulePolynom &&a._module == b._module);
        }
        bool operator!=(const PolynomN6& a, const PolynomN6& b)
        {
                return !(a==b);
        }

//**********************************************************************************************
//******************************    Операция сложения    ***************************************
        PolynomN6 operator+(const PolynomN6 &a, const PolynomN6 &b)
        {
                PolynomN6 result, copy_a(a), copy_b(b);
                return result.Add(copy_a, copy_b);
        }
	PolynomN6& PolynomN6::operator+=(PolynomN6 & polynom)
        {
                return Add(*this, polynom);
        }
	PolynomN6& PolynomN6::Add(PolynomN6 &a, PolynomN6 &b)
        {
                if(a.getModulePolynom() != b.getModulePolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модулярные многочлены должны быть равны");

                _modulePolynom = a._modulePolynom;
                _module=a._module;
                PolynomGF3 module(_module);
                _a1.ModAdd(a._a1, b._a1, module);
                _a2.ModAdd(a._a2, b._a2, module);
                _a3.ModAdd(a._a3, b._a3, module);
                _a4.ModAdd(a._a4, b._a4, module);
                _a5.ModAdd(a._a5, b._a5, module);
                _a6.ModAdd(a._a6, b._a6, module);
                return *this;
        }
//**********************************************************************************************
//******************************    Операция вычитания   ***************************************
        PolynomN6 operator-(const PolynomN6 &a, const PolynomN6 &b)
        {
                PolynomN6 result, copy_a(a), copy_b(b);
                return result.Sub(copy_a, copy_b);
        }
	PolynomN6& PolynomN6::operator-=(PolynomN6 & polynom)
        {
                return Sub(*this, polynom);
        }
	PolynomN6& PolynomN6::Sub(PolynomN6 &a, PolynomN6 &b)
        {
                if(a.getModulePolynom() != b.getModulePolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модулярные многочлены должны быть равны");

                _modulePolynom = a._modulePolynom;
                _module=a._module;
                PolynomGF3 module(_module);
                _a1.ModSub(a._a1, b._a1, module);
                _a2.ModSub(a._a2, b._a2, module);
                _a3.ModSub(a._a3, b._a3, module);
                _a4.ModSub(a._a4, b._a4, module);
                _a5.ModSub(a._a5, b._a5, module);
                _a6.ModSub(a._a6, b._a6, module);
                return *this;
        }
//**********************************************************************************************
//******************************    Операция взятия противоположного элемента    ***************        
        PolynomN6& PolynomN6::Negate()
        {
                return Negate(*this);
        }
	PolynomN6& PolynomN6::Negate(PolynomN6 &polynom)
        {
                PolynomGF3 temp("0");
                _modulePolynom = polynom._modulePolynom;
                _module = polynom._module;
                _a1.ModSub(temp,_a1,_module);
                _a2.ModSub(temp,_a2,_module);
                _a3.ModSub(temp,_a3,_module);
                _a4.ModSub(temp,_a4,_module);
                _a5.ModSub(temp,_a5,_module);
                _a6.ModSub(temp,_a6,_module);
                return *this;
        }

//**********************************************************************************************
//******************************    Операция умножения   ***************************************

        PolynomN6 operator*(const PolynomN6 &a, const PolynomN6 &b)
        {
                PolynomN6 result, copy_a(a), copy_b(b);
                return result.Mul(copy_a, copy_b);
        }
	PolynomN6& PolynomN6::operator*=(PolynomN6 & polynom)
        {
                return Mul(*this, polynom);
        }
	PolynomN6& PolynomN6::Mul(PolynomN6 &a, PolynomN6 &b)
        {
                if(a.getModulePolynom() != b.getModulePolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модулярные многочлены должны быть равны");

                _modulePolynom = a._modulePolynom;
                _module = a._module;
                PolynomN6 copy_a(a), copy_b(b);

                PolynomGF3 c6Coef, c7Coef,c8Coef, c9Coef, c10Coef, temp1, temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9,temp10;
                PolynomGF3 module(_module),modulePolynom(_modulePolynom);

                // умножение многочленов и приведение по модулю
                _a1.ModMul(copy_a._a1, copy_b._a1, module);
                temp1.ModMul(copy_a._a1, copy_b._a2, module);
                temp2.ModMul(copy_a._a2, copy_b._a1, module);
                _a2.ModAdd(temp1, temp2, module);
                temp1.ModMul(copy_a._a1, copy_b._a3, module);
                temp2.ModMul(copy_a._a2, copy_b._a2, module);
                temp3.ModMul(copy_a._a3, copy_b._a1, module);
                temp4.ModAdd(temp1,temp2,module);
                _a3.ModAdd(temp4,temp3,module);
                temp1.ModMul(copy_a._a1, copy_b._a4, module);
                temp2.ModMul(copy_a._a2, copy_b._a3, module);
                temp3.ModMul(copy_a._a3, copy_b._a2, module);
                temp4.ModMul(copy_a._a4, copy_b._a1, module);
                temp5.ModAdd(temp1,temp2,module);
                temp6.ModAdd(temp3,temp4,module);
                _a4.ModAdd(temp5,temp6,module);
                temp1.ModMul(copy_a._a1, copy_b._a5, module);
                temp2.ModMul(copy_a._a2, copy_b._a4, module);
                temp3.ModMul(copy_a._a3, copy_b._a3, module);
                temp4.ModMul(copy_a._a4, copy_b._a2, module);
                temp5.ModMul(copy_a._a5, copy_b._a1, module);
                temp6.ModAdd(temp1,temp2,module);
                temp7.ModAdd(temp3,temp4,module);
                temp8.ModAdd(temp5,temp6,module);
                _a5.ModAdd(temp7,temp8,module);
                temp1.ModMul(copy_a._a1, copy_b._a6, module);
                temp2.ModMul(copy_a._a2, copy_b._a5, module);
                temp3.ModMul(copy_a._a3, copy_b._a4, module);
                temp4.ModMul(copy_a._a4, copy_b._a3, module);
                temp5.ModMul(copy_a._a5, copy_b._a2, module);
                temp6.ModMul(copy_a._a6, copy_b._a1, module);
                temp7.ModAdd(temp1, temp2, module);
                temp8.ModAdd(temp3, temp4, module);
                temp9.ModAdd(temp5, temp6, module);
                temp10.ModAdd(temp7, temp8, module);
                _a6.ModAdd(temp9,temp10,module);
                temp1.ModMul(copy_a._a2, copy_b._a6, module);
                temp2.ModMul(copy_a._a3, copy_b._a5, module);
                temp3.ModMul(copy_a._a4, copy_b._a4, module);
                temp4.ModMul(copy_a._a5, copy_b._a3, module);
                temp5.ModMul(copy_a._a6, copy_b._a2, module);
                temp6.ModAdd(temp1,temp2,module);
                temp7.ModAdd(temp3,temp4,module);
                temp8.ModAdd(temp5,temp6,module);
                c6Coef.ModAdd(temp7,temp8,module);
                temp1.ModMul(copy_a._a3, copy_b._a6, module);
                temp2.ModMul(copy_a._a4, copy_b._a5, module);
                temp3.ModMul(copy_a._a5, copy_b._a4, module);
                temp4.ModMul(copy_a._a6, copy_b._a3, module);
                temp5.ModAdd(temp1,temp2,module);
                temp6.ModAdd(temp3,temp4,module);
                c7Coef.ModAdd(temp5,temp6,module);
                temp1.ModMul(copy_a._a4, copy_b._a6, module);
                temp2.ModMul(copy_a._a5, copy_b._a5, module);
                temp3.ModMul(copy_a._a6, copy_b._a4, module);
                temp4.ModAdd(temp1,temp2,module);
                c8Coef.ModAdd(temp4,temp3,module);
                temp1.ModMul(copy_a._a5, copy_b._a6, module);
                temp2.ModMul(copy_a._a6, copy_b._a5, module);
                c9Coef.ModAdd(temp1, temp2, module);
                c10Coef.ModMul(copy_a._a6, copy_b._a6, module);
                if(c10Coef.isZero() && c9Coef.isZero() && c8Coef.isZero()&&c7Coef.isZero()&&c6Coef.isZero())
                        return *this;

                // редуцирование
                      //s-i-1

                Polynom one("1");
                if((((modulePolynom.A1>>(5))&one).isOne())) c9Coef.ModAdd(c9Coef, c10Coef, module);
                if((((modulePolynom.A0>>(5))&one).isOne())) c9Coef.ModAdd(c9Coef, c10Coef+c10Coef, module);
                if((((modulePolynom.A1>>(4))&one).isOne())) c8Coef.ModAdd(c8Coef, c10Coef, module);
                if((((modulePolynom.A0>>(4))&one).isOne())) c8Coef.ModAdd(c8Coef, c10Coef+c10Coef, module);
                if((((modulePolynom.A1>>(3))&one).isOne())) c7Coef.ModAdd(c7Coef, c10Coef, module);
                if((((modulePolynom.A0>>(3))&one).isOne())) c7Coef.ModAdd(c7Coef, c10Coef+c10Coef, module);
                if((((modulePolynom.A1>>(2))&one).isOne())) c6Coef.ModAdd(c6Coef, c10Coef, module);
                if((((modulePolynom.A0>>(2))&one).isOne())) c6Coef.ModAdd(c6Coef, c10Coef+c10Coef, module);
                if((((modulePolynom.A1>>(1))&one).isOne())) _a6.ModAdd(_a6, c10Coef, module);
                if((((modulePolynom.A0>>(1))&one).isOne())) _a6.ModAdd(_a6, c10Coef+c10Coef, module);
                if((((modulePolynom.A1>>(0))&one).isOne())) _a5.ModAdd(_a5, c10Coef, module);
                if((((modulePolynom.A0>>(0))&one).isOne())) _a5.ModAdd(_a5, c10Coef+c10Coef, module);
                if(c9Coef.isZero() && c8Coef.isZero()&&c7Coef.isZero()&&c6Coef.isZero())
                        return *this;
                if((((modulePolynom.A1>>(5))&one).isOne())) c8Coef.ModAdd(c8Coef, c9Coef, module);
                if((((modulePolynom.A0>>(5))&one).isOne())) c8Coef.ModAdd(c8Coef, c9Coef+c9Coef, module);
                if((((modulePolynom.A1>>(4))&one).isOne())) c7Coef.ModAdd(c7Coef, c9Coef, module);
                if((((modulePolynom.A0>>(4))&one).isOne())) c7Coef.ModAdd(c7Coef, c9Coef+c9Coef, module);
                if((((modulePolynom.A1>>(3))&one).isOne())) c6Coef.ModAdd(c6Coef, c9Coef, module);
                if((((modulePolynom.A0>>(3))&one).isOne())) c6Coef.ModAdd(c6Coef, c9Coef+c9Coef, module);
                if((((modulePolynom.A1>>(2))&one).isOne())) _a6.ModAdd(_a6, c9Coef, module);
                if((((modulePolynom.A0>>(2))&one).isOne())) _a6.ModAdd(_a6, c9Coef+c9Coef, module);
                if((((modulePolynom.A1>>(1))&one).isOne())) _a5.ModAdd(_a5, c9Coef, module);
                if((((modulePolynom.A0>>(1))&one).isOne())) _a5.ModAdd(_a5, c9Coef+c9Coef, module);
                if((((modulePolynom.A1>>(0))&one).isOne())) _a4.ModAdd(_a4, c9Coef, module);
                if((((modulePolynom.A0>>(0))&one).isOne())) _a4.ModAdd(_a4, c9Coef+c9Coef, module);
                if(c8Coef.isZero()&&c7Coef.isZero()&&c6Coef.isZero())
                        return *this;
                if((((modulePolynom.A1>>(5))&one).isOne())) c7Coef.ModAdd(c7Coef, c8Coef, module);
                if((((modulePolynom.A0>>(5))&one).isOne())) c7Coef.ModAdd(c7Coef, c8Coef+c8Coef, module);
                if((((modulePolynom.A1>>(4))&one).isOne())) c6Coef.ModAdd(c6Coef, c8Coef, module);
                if((((modulePolynom.A0>>(4))&one).isOne())) c6Coef.ModAdd(c6Coef, c8Coef+c8Coef, module);
                if((((modulePolynom.A1>>(3))&one).isOne())) _a6.ModAdd(_a6, c8Coef, module);
                if((((modulePolynom.A0>>(3))&one).isOne())) _a6.ModAdd(_a6, c8Coef+c8Coef, module);
                if((((modulePolynom.A1>>(2))&one).isOne())) _a5.ModAdd(_a5, c8Coef, module);
                if((((modulePolynom.A0>>(2))&one).isOne())) _a5.ModAdd(_a5, c8Coef+c8Coef, module);
                if((((modulePolynom.A1>>(1))&one).isOne())) _a4.ModAdd(_a4, c8Coef, module);
                if((((modulePolynom.A0>>(1))&one).isOne())) _a4.ModAdd(_a4, c8Coef+c8Coef, module);
                if((((modulePolynom.A1>>(0))&one).isOne())) _a3.ModAdd(_a3, c8Coef, module);
                if((((modulePolynom.A0>>(0))&one).isOne())) _a3.ModAdd(_a3, c8Coef+c8Coef, module);
                if(c7Coef.isZero()&&c6Coef.isZero())
                        return *this;
                if((((modulePolynom.A1>>(5))&one).isOne())) c6Coef.ModAdd(c6Coef, c7Coef, module);
                if((((modulePolynom.A0>>(5))&one).isOne())) c6Coef.ModAdd(c6Coef, c7Coef+c7Coef, module);
                if((((modulePolynom.A1>>(4))&one).isOne())) _a6.ModAdd(_a6, c7Coef, module);
                if((((modulePolynom.A0>>(4))&one).isOne())) _a6.ModAdd(_a6, c7Coef+c7Coef, module);
                if((((modulePolynom.A1>>(3))&one).isOne())) _a5.ModAdd(_a5, c7Coef, module);
                if((((modulePolynom.A0>>(3))&one).isOne())) _a5.ModAdd(_a5, c7Coef+c7Coef, module);
                if((((modulePolynom.A1>>(2))&one).isOne())) _a4.ModAdd(_a4, c7Coef, module);
                if((((modulePolynom.A0>>(2))&one).isOne())) _a4.ModAdd(_a4, c7Coef+c7Coef, module);
                if((((modulePolynom.A1>>(1))&one).isOne())) _a3.ModAdd(_a3, c7Coef, module);
                if((((modulePolynom.A0>>(1))&one).isOne())) _a3.ModAdd(_a3, c7Coef+c7Coef, module);
                if((((modulePolynom.A1>>(0))&one).isOne())) _a2.ModAdd(_a2, c7Coef, module);
                if((((modulePolynom.A0>>(0))&one).isOne())) _a2.ModAdd(_a2, c7Coef+c7Coef, module);
                if(c6Coef.isZero())
                        return *this;
                if((((modulePolynom.A1>>(5))&one).isOne())) _a6.ModAdd(_a6, c6Coef, module);
                if((((modulePolynom.A0>>(5))&one).isOne())) _a6.ModAdd(_a6, c6Coef+c6Coef, module);
                if((((modulePolynom.A1>>(4))&one).isOne())) _a5.ModAdd(_a5, c6Coef, module);
                if((((modulePolynom.A0>>(4))&one).isOne())) _a5.ModAdd(_a5, c6Coef+c6Coef, module);
                if((((modulePolynom.A1>>(3))&one).isOne())) _a4.ModAdd(_a4, c6Coef, module);
                if((((modulePolynom.A0>>(3))&one).isOne())) _a4.ModAdd(_a4, c6Coef+c6Coef, module);
                if((((modulePolynom.A1>>(2))&one).isOne())) _a3.ModAdd(_a3, c6Coef, module);
                if((((modulePolynom.A0>>(2))&one).isOne())) _a3.ModAdd(_a3, c6Coef+c6Coef, module);
                if((((modulePolynom.A1>>(1))&one).isOne())) _a2.ModAdd(_a2, c6Coef, module);
                if((((modulePolynom.A0>>(1))&one).isOne())) _a2.ModAdd(_a2, c6Coef+c6Coef, module);
                if((((modulePolynom.A1>>(0))&one).isOne())) _a1.ModAdd(_a1, c6Coef, module);
                if((((modulePolynom.A0>>(0))&one).isOne())) _a1.ModAdd(_a1, c6Coef+c6Coef, module);
                 
                return *this;
        }

//**********************************************************************************************
//******************************    Операция возведения в степень    ***************************        
        PolynomN6& PolynomN6::Pow(PolynomN6 &a, Integer &n)
        {
                if(n.isNegative())
			throw std::domain_error("Число n - отрицательное результат не определен");

                _modulePolynom = a._modulePolynom;
                _module=a._module;
                
                PolynomN6 copy_a(a);
		Integer copy_n(n);

		setOne();
                
		uint s = copy_n.getNumberBits();
		for(uint i=0;i<s;i++)
		{
                        Mul(*this, *this);
			if(copy_n.getBit(s-1-i))
			        Mul(*this, copy_a);
		}

                return *this;
        }
//**********************************************************************************************
//******************************    Операция взятия обратного элемента    **********************
        PolynomN6& PolynomN6::Inverse()
        {
                return Inverse(*this);
        }
        // алгоритм вычисления обратного элемента по т. ферма
        PolynomN6& PolynomN6::Inverse(PolynomN6 &a)
        {
                PolynomN6 copy_a(a);

                Integer mulGroupOrderWithoutOne(copy_a.getMulGroupOrder());
                mulGroupOrderWithoutOne--;

                return Pow(copy_a, mulGroupOrderWithoutOne);
        }
//**********************************************************************************************
//******************************           Операции генерации             **********************
        PolynomN6& PolynomN6::Generate()
        {
                _a1.Generate(getModule());
                _a2.Generate(getModule());
                _a3.Generate(getModule());
                _a4.Generate(getModule());
                _a5.Generate(getModule());
                _a6.Generate(getModule());
                return *this;
        }
//**********************************************************************************************
//******************************           Операции извлечения квадратного корня            **********************
       PolynomN6& PolynomN6::Square(PolynomN6 &a)
       { //не реализовано
         return *this;
       }



}
