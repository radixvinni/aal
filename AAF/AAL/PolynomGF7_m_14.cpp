/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF7_m_14.h"
#include "PolynomGF7_mY_13.h"
#include "PolynomGF7.h"
#include "Converter.h"
#include "Integer.h"
#include "DecompositionManager.h"
#include <string>
#include <stdlib.h>
namespace AAL
{
  int PolynomGF7_m_14::sevendiv(std::vector<Integer>* m, Integer n)
  {
    int j,i = 0;
    while(n >= 7)
    {
        //j = n%3;
        m->push_back(n%7);
        i++;
        n = n/7;
    }
    m->push_back(n);
    return i;
  }

//***********************************  Конструкторы  *******************************************
	//(c) Belova, TEST(PolynomGF3_m_6, EmptyConstructor)
	PolynomGF7_m_14::PolynomGF7_m_14() :
        _a0(), _a1(), _a2(), _a3(), _a4(), _a5(),_a6(), _module(), _modPolynom("46000001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, CopyConstructor)
	PolynomGF7_m_14::PolynomGF7_m_14(const PolynomGF7_m_14 &polynom)
	{
     _a0 = polynom._a0;
     _a1 = polynom._a1;
     _a2 = polynom._a2;
     _a3 = polynom._a3;
     _a4 = polynom._a4;
     _a5 = polynom._a5;
     _a6 = polynom._a6;


     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, StringConstructor)
	PolynomGF7_m_14::PolynomGF7_m_14(const std::string a0,
     const std::string a1, const std::string a2,
     const std::string a3, const std::string a4,
     const std::string a5, const std::string a6,
     const std::string a7, const std::string a8,
     const std::string a9, const std::string a10,
     const std::string a11, const std::string a12,
     const std::string a13, const std::string module):
     _a0(a0,a1,module), _a1(a2,a3,module), _a2(a4,a5,module), _a3(a6,a7,module), _a4(a8,a9,module), _a5(a10,a11,module), _a6(a12,a13,module),_module(module), _modPolynom("46000001")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF7_m_14::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero())
            return true;
        return false;
    }
    bool PolynomGF7_m_14::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero()&& _a6.isZero())
            return true;
        return false;
    }
//------------------------------------------------------------------------------
	PolynomGF7_m_14& PolynomGF7_m_14::setZero()
	{
        _a0.setZero();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        _a4.setZero();
        _a5.setZero();
        _a6.setZero();

		return *this;
	}
    //simple method
	PolynomGF7_m_14& PolynomGF7_m_14::setOne()
	{
        _a0.setOne();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        _a4.setZero();
        _a5.setZero();
        _a6.setZero();

        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, Equal)
	bool operator==(const PolynomGF7_m_14& a, const PolynomGF7_m_14& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3  && a._a4 == b._a4 && a._a5 == b._a5 && a._a6 == b._a6)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, operatorEqual)
	PolynomGF7_m_14& PolynomGF7_m_14::operator= (const PolynomGF7_m_14& polynom)
	{
        if(this == &polynom)
            return *this;

        _a0 = polynom._a0;
        _a1 = polynom._a1;
        _a2 = polynom._a2;
        _a3 = polynom._a3;
        _a4 = polynom._a4;
        _a5 = polynom._a5;
        _a6 = polynom._a6;


        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF7_m_14& a, const PolynomGF7_m_14& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF7_m_2& PolynomGF7_m_14::getA0() const
  {
    return _a0;
  }
  const PolynomGF7_m_2& PolynomGF7_m_14::getA1() const
  {
    return _a1;
  }
  const PolynomGF7_m_2& PolynomGF7_m_14::getA2() const
  {
    return _a2;
  }
  const PolynomGF7_m_2& PolynomGF7_m_14::getA3() const
  {
    return _a3;
  }
  const PolynomGF7_m_2& PolynomGF7_m_14::getA4() const
  {
    return _a4;
  }
  const PolynomGF7_m_2& PolynomGF7_m_14::getA5() const
  {
    return _a5;
  }
  const PolynomGF7_m_2& PolynomGF7_m_14::getA6() const
  {
    return _a6;
  }

  const PolynomGF7& PolynomGF7_m_14::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF7& PolynomGF7_m_14::getModule() const
  {
    return _module;
  }

//------------------------------------------------------------------------------
    void PolynomGF7_m_14::setA0(const PolynomGF7_m_2 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF7_m_14::setA1(const PolynomGF7_m_2 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF7_m_14::setA2(const PolynomGF7_m_2 & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF7_m_14::setA3(const PolynomGF7_m_2 & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF7_m_14::setA4(const PolynomGF7_m_2 & a)
    {
        _a4 = a;
        _a4 %= _module;
    }
    void PolynomGF7_m_14::setA5(const PolynomGF7_m_2 & a)
    {
        _a5 = a;
        _a5 %= _module;
    }
    void PolynomGF7_m_14::setA6(const PolynomGF7_m_2 & a)
    {
        _a6 = a;
        _a6 %= _module;
    }
    void PolynomGF7_m_14::setModule(const PolynomGF7& module)
    {
        _module = module;
        _a0 %= _module;
        _a1 %= _module;
        _a2 %= _module;
        _a3 %= _module;
        _a4 %= _module;
        _a5 %= _module;
        _a6 %= _module;


    }
    void PolynomGF7_m_14::setModPolynom(const PolynomGF7& modPolynom)
    {
        _modPolynom = modPolynom;
     //   if((modPolynom.getNumberBits()-1)!=14)
       //     throw new Exception("модулярные многочлен порождающий расширение поля должны быть степени 14");
    }
//------------------------------------------------------------------------------
//******************************    Операция сложения    ***************************************
	//simple method
	PolynomGF7_m_14 operator+(const PolynomGF7_m_14 &a, const PolynomGF7_m_14 &b)
	{
		PolynomGF7_m_14 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m_14& PolynomGF7_m_14::operator+=(PolynomGF7_m_14 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF7_m_14& PolynomGF7_m_14::Add(PolynomGF7_m_14 &a, PolynomGF7_m_14 &b)
	{
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module=a._module;
        _a0.Add(a._a0, b._a0);
        std::string s =  _a0._a0.ToString();
        s =  _a0._a1.ToString();
        _a1.Add(a._a1, b._a1);
        s =  _a1._a0.ToString();
        s =  _a1._a1.ToString();
        _a2.Add(a._a2, b._a2);
        s =  _a2._a0.ToString();
        s =  _a2._a1.ToString();
        _a3.Add(a._a3, b._a3);
        s =  _a3._a0.ToString();
        s =  _a3._a1.ToString();
        _a4.Add(a._a4, b._a4);
        s =  _a4._a0.ToString();
        s =  _a4._a1.ToString();
        _a5.Add(a._a5, b._a5);
        s =  _a5._a0.ToString();
        s =  _a5._a1.ToString();
        _a6.Add(a._a6, b._a6);
        s =  _a6._a0.ToString();
        s =  _a6._a1.ToString();

        return *this;
	}
	//simple method
	PolynomGF7_m_14 operator*(const PolynomGF7_m_14 &a, const PolynomGF7_m_14 &b)
	{
		PolynomGF7_m_14 result;
        PolynomGF7_m_14 copy_a(a), copy_b(b);
 		return result.Mul(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m_14& PolynomGF7_m_14::operator*=(PolynomGF7_m_14 &polynom)
	{
		return Mul(*this, polynom);
	}
//------------------------------------------------------------------------------

	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF7_m_14& PolynomGF7_m_14::Mul(PolynomGF7_m_14 &a, PolynomGF7_m_14 &b)
	{
        PolynomGF7_m_2 e0("0","0",a._module.ToString());
        PolynomGF7_m_2 e1("0","0",a._module.ToString()),e1_1("0","0",a._module.ToString()),e1_2("0","0",a._module.ToString());
        PolynomGF7_m_2 e2("0","0",a._module.ToString()),e2_1("0","0",a._module.ToString()),e2_2("0","0",a._module.ToString()),e2_3("0","0",a._module.ToString());
        PolynomGF7_m_2 e3("0","0",a._module.ToString()),e3_1("0","0",a._module.ToString()),e3_2("0","0",a._module.ToString()),e3_3("0","0",a._module.ToString()),e3_4("0","0",a._module.ToString());
        PolynomGF7_m_2 e4("0","0",a._module.ToString()), e4_1("0","0",a._module.ToString()),e4_2("0","0",a._module.ToString()),e4_3("0","0",a._module.ToString()),e4_4("0","0",a._module.ToString()),e4_5("0","0",a._module.ToString());
        PolynomGF7_m_2 e5("0","0",a._module.ToString()),e5_1("0","0",a._module.ToString()),e5_2("0","0",a._module.ToString()),e5_3("0","0",a._module.ToString()),e5_4("0","0",a._module.ToString()),e5_5("0","0",a._module.ToString()),e5_6("0","0",a._module.ToString());
        PolynomGF7_m_2 e6("0","0",a._module.ToString()),e6_1("0","0",a._module.ToString()),e6_2("0","0",a._module.ToString()),e6_3("0","0",a._module.ToString()),e6_4("0","0",a._module.ToString()),e6_5("0","0",a._module.ToString()),e6_6("0","0",a._module.ToString()),e6_7("0","0",a._module.ToString());
        PolynomGF7_m_2 e7("0","0",a._module.ToString()),e7_1("0","0",a._module.ToString()),e7_2("0","0",a._module.ToString()),e7_3("0","0",a._module.ToString()),e7_4("0","0",a._module.ToString()),e7_5("0","0",a._module.ToString()),e7_6("0","0",a._module.ToString());
        PolynomGF7_m_2 e8("0","0",a._module.ToString()),e8_1("0","0",a._module.ToString()),e8_2("0","0",a._module.ToString()),e8_3("0","0",a._module.ToString()),e8_4("0","0",a._module.ToString()),e8_5("0","0",a._module.ToString());
        PolynomGF7_m_2 e9("0","0",a._module.ToString()),e9_1("0","0",a._module.ToString()),e9_2("0","0",a._module.ToString()),e9_3("0","0",a._module.ToString()),e9_4("0","0",a._module.ToString());
        PolynomGF7_m_2 e10("0","0",a._module.ToString()),e10_1("0","0",a._module.ToString()),e10_2("0","0",a._module.ToString()),e10_3("0","0",a._module.ToString());
        PolynomGF7_m_2 e11("0","0",a._module.ToString()),e11_1("0","0",a._module.ToString()),e11_2("0","0",a._module.ToString());
        PolynomGF7_m_2 e12("0","0",a._module.ToString());
        PolynomGF7_m_2 four("4","0",a._module.ToString()),c("0","0",a._module.ToString());
        PolynomGF7_m_2 six("6","0",a._module.ToString()),minus2b("0","0",a._module.ToString()),three("3","0",a._module.ToString());
        minus2b.Mul(six,four);
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module = a._module;
        c._module = a._module;
        c._modPolynom = a._modPolynom;
        three._modPolynom = a._modPolynom;
        six._modPolynom = a._modPolynom;
        minus2b._modPolynom = a._modPolynom;
        four._modPolynom = a._modPolynom;
		if(a.isZero() || b.isZero())
  			return setZero();
         e0.Mul(a._a0,b._a0);
         e1_1.Mul(a._a0,b._a1);
         e1_2.Mul(a._a1,b._a0);
         e1 = e1_1 + e1_2;
         e2 = e2_1.Mul(a._a0,b._a2) + e2_2.Mul(a._a1,b._a1) + e2_3.Mul(a._a2,b._a0);
         e3 = e3_1.Mul(a._a0,b._a3) + e3_2.Mul(a._a1,b._a2) + e3_3.Mul(a._a2,b._a1)+ e3_4.Mul(a._a3,b._a0);
         e4 = e4_1.Mul(a._a0,b._a4) + e4_2.Mul(a._a1,b._a3) + e4_3.Mul(a._a2,b._a2)+ e4_4.Mul(a._a3,b._a1)+ e4_5.Mul(a._a4,b._a0);
         e5 = e5_1.Mul(a._a0,b._a5) + e5_2.Mul(a._a1,b._a4) + e5_3.Mul(a._a2,b._a3)+ e5_4.Mul(a._a3,b._a2)+ e5_5.Mul(a._a4,b._a1)+ e5_6.Mul(a._a5,b._a0);
         e6 = e6_1.Mul(a._a0,b._a6) + e6_2.Mul(a._a1,b._a5) + e6_3.Mul(a._a2,b._a4)+ e6_4.Mul(a._a3,b._a3)+ e6_5.Mul(a._a4,b._a2)+ e6_6.Mul(a._a5,b._a1)+ e6_7.Mul(a._a6,b._a0);
         e7 = e7_1.Mul(a._a1,b._a6) + e7_2.Mul(a._a2,b._a5) + e7_3.Mul(a._a3,b._a4)+ e7_4.Mul(a._a4,b._a3)+ e7_5.Mul(a._a5,b._a2)+ e7_6.Mul(a._a6,b._a1);
         e8 = e8_1.Mul(a._a2,b._a6) + e8_2.Mul(a._a3,b._a5) + e8_3.Mul(a._a4,b._a4)+ e8_4.Mul(a._a5,b._a3)+ e8_5.Mul(a._a6,b._a2);
         e9 = e9_1.Mul(a._a3,b._a6) + e9_2.Mul(a._a4,b._a5) + e9_3.Mul(a._a5,b._a4)+ e9_4.Mul(a._a6,b._a3);
         e10 = e10_1.Mul(a._a4,b._a6) + e10_2.Mul(a._a5,b._a5) + e10_3.Mul(a._a6,b._a4);
         e11 = e11_1.Mul(a._a5,b._a6) + e11_2.Mul(a._a6,b._a5);
         e12.Mul(a._a6,b._a6);

        _a6 = e6 + e12;
        std::string s = _a6._a0.ToString();
        s = _a6._a1.ToString();
        _a5 = e5 + e11 + c.Mul(minus2b,e12);
        s = _a5._a0.ToString();
        s = _a5._a1.ToString();
        _a4 = e4 + e10 + c.Mul(minus2b,e11);
        s = _a4._a0.ToString();
        s = _a4._a1.ToString();
        _a3 = e3 + e9 + c.Mul(minus2b,e10);
        s = _a3._a0.ToString();
        s = _a3._a1.ToString();
        _a2 =  e2 +e8 + c.Mul(minus2b,e9);
        s = _a2._a0.ToString();
        s = _a2._a1.ToString();
        _a1 =  e1 + e7 + c.Mul(minus2b,e8);
        s = _a1._a0.ToString();
        s = _a1._a1.ToString();
        _a0 =  e0 + c.Mul(minus2b,e7);
        s = _a0._a0.ToString();
        s = _a0._a1.ToString();

		return *this;
	}
// простой метод возведения в степень 3 по модулю
	PolynomGF7_m_14& PolynomGF7_m_14::Seven(PolynomGF7_m_14 &a)
	{
		PolynomGF7 e0,e1,e2,e4, e11,e13,e14;
        PolynomGF7 e3;
        PolynomGF7 e6;
        PolynomGF7 e9,e12,e15;
        _modPolynom = a._modPolynom;
        _module = a._module;
		if(a.isZero())
  			return setZero();
//        if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
/*        e0.ModPow(a._a0,3,_module);
        std::string ss = e0.ToString();
        e3.ModPow(a._a1,3,_module);
        ss = e3.ToString();
        //e1 =  e11.ModMul(a._a1,a._a0,_module) + e12.ModMul(a._a1,a._a0,_module)
        e6.ModPow(a._a2,3,_module);
        ss = e6.ToString();
        e9.ModPow(a._a3,3,_module);
        ss = e9.ToString();
        e12.ModPow(a._a4,3,_module);
        ss = e12.ToString();
        e15.ModPow(a._a5,3,_module);
        ss = e15.ToString();
        _a0 = e0 + e6 + e12;
        std::string s = _a0.ToString();
        _a1 = e6 + e6 + e12;
        s = _a1.ToString();
        _a2 = e12;
        s = _a2.ToString();
        _a3 = e3 + e9 + e15;
        s = _a3.ToString();
        _a4 = e9 + e9 +e15;
        s = _a4.ToString();
        _a5 = e15;
        s = _a5.ToString();*/
		return *this;
	}
  //возведение в степень
  PolynomGF7_m_14& PolynomGF7_m_14::Pow(PolynomGF7_m_14 &a, const Integer &n)
  {
    if(a.isZero() == true)
    {
        *this = a;
        return *this;
    }
    if(n.isNegative())
        throw std::domain_error("Число n - отрицательное результат не определен");
//    if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
    //int len = atoi(n.ToString().c_str());
   std::vector<Integer> m;
    int num_bit;
    num_bit = sevendiv(&m,n);
    std::string s = m[0].ToString();
    _modPolynom = a._modPolynom;
    _module = a._module;
    PolynomGF7_m_14 c,result("1","0","0","0","0","0","0","0","0","0","0","0","0","0",a._module.ToString());
   // result.setOne();
    result.setModule(_module);
    result.setModPolynom(_modPolynom);
    //    std::string m1 = a._module.ToString();
    PolynomGF7_m_14 one("1","0","0","0","0","0","0","0","0","0","0","0","0","0",a._module.ToString());
    PolynomGF7_m_14 a_2(a*a),a_3(a*a*a),a_4(a*a*a*a),a_5(a*a*a*a*a),a_6(a*a*a*a*a*a);
    one.setOne();
    one.setModule(_module);

    Integer copy_n(n);
    //result.setOne();
    for(int i=1;i<=num_bit+1;i++)
    {
        c = result*result*result*result*result*result*result;
        result = c;
        if(m[num_bit + 1 - i] == 1)
            result.Mul(result,a);
        else if(m[num_bit + 1 - i] == 2)
        {
            //a = a*a;
            result.Mul(result,a_2);
        }
        else if(m[num_bit + 1 - i] == 3)
        {
            //a = a*a*a;
            result.Mul(result,a_3);
        }
        else if(m[num_bit + 1 - i] == 4)
        {
            //a = a*a*a*a;
            result.Mul(result,a_4);
        }
        else if(m[num_bit + 1 - i] == 5)
        {
            //a = a*a*a*a*a;
            result.Mul(result,a_5);
        }
        else if(m[num_bit + 1 - i] == 6)
        {
            //a = a*a*a*a*a*a;
            result.Mul(result,a_6);
        }
        else
            result *= one;
    }
    *this = result;
        s = _a0._a0.ToString();
        s = _a0._a1.ToString();
        s = _a1._a0.ToString();
        s = _a1._a1.ToString();
        s = _a2._a0.ToString();
        s = _a2._a1.ToString();
        s = _a3._a0.ToString();
        s = _a3._a1.ToString();
        s = _a4._a0.ToString();
        s = _a4._a1.ToString();
        s = _a5._a0.ToString();
        s = _a5._a1.ToString();
        s = _a6._a0.ToString();
        s = _a6._a1.ToString();
    m.clear();
    return *this;
  }
     const PolynomGF7_m_2& PolynomGF7_m_14::getByIndex(int index) const
    {
        if(index == 0)
        {
            return _a0;
        }
        else if(index == 1)
        {
            return _a1;
        }
        else if(index == 2)
        {
            return _a2;
        }
        else if(index == 3)
        {
            return _a3;
        }
        else if(index == 4)
        {
            return _a4;
        }
        else if(index == 5)
        {
            return _a5;
        }
        if(index == 6)
        {
            return _a6;
        }
    }
    void PolynomGF7_m_14::setByIndex(const PolynomGF7_m_2 & a, int index)
    {
        if(index == 0)
        {
            _a0 = a;
        }
        else if(index == 1)
        {
            _a1 = a;
        }
        else if(index == 2)
        {
            _a2 = a;
        }
        else if(index == 3)
        {
            _a3 = a;
        }
        else if(index == 4)
        {
            _a4 = a;
        }
        else if(index == 5)
        {
            _a5 = a;
        }
        if(index == 6)
        {
            _a6 = a;
        }
    }
   //определение степени многочлена
    int PolynomGF7_m_14::deg() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero()&& _a4.isZero() && _a5.isZero() && _a6.isZero())
            return -1;
        else if(!_a6.isZero())
            return 6;
        else if(!_a5.isZero())
            return 5;
        else if(!_a4.isZero())
            return 4;
        else if(!_a3.isZero())
            return 3;
        else if(!_a2.isZero())
            return 2;
        else if(!_a1.isZero())
            return 1;
        else if(!_a0.isZero())
            return 0;
    }

  //инвертирование
  //------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m_14& PolynomGF7_m_14::Inverse(PolynomGF7 &module)
	{
		return Inverse(*this, module);
	}
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_m_4, Inverse)
	PolynomGF7_m_14& PolynomGF7_m_14::Inverse(PolynomGF7_m_14 &polynom, PolynomGF7 &module)
	{
//        if(polynom.getModule().isIrreducible() == false || module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
       PolynomGF7_mY_13 d2("000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString()),d1("100","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString()),w1;
        PolynomGF7_mY_13 u("400","000","600","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","100","000",module.ToString()),w,r,c,_c;
        PolynomGF7_mY_13 two("600","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString());
        int d = 0;
        PolynomGF7_m_14 result;
        PolynomGF7_m_2 _u,_v,inv,_q,_b,zr("000","000",module.ToString());
        PolynomGF7_mY_13 v;
        v.setA0(polynom._a0);
        v.setA1(polynom._a1);
        v.setA2(polynom._a2);
        v.setA3(polynom._a3);
        v.setA4(polynom._a4);
        v.setA5(polynom._a5);
        v.setA6(polynom._a6);
        v.setA7(zr);
        v.setA8(zr);
        v.setA9(zr);
        v.setA10(zr);
        v.setA11(zr);
        v.setA12(zr);

        //(,polynom._a1._a0.ToString(),polynom._a1._a1.ToString(),polynom._a2._a0.ToString(),polynom._a2._a1.ToString(),polynom._a3._a0.ToString(),polynom._a3._a1.ToString(),polynom._a4._a0.ToString(),polynom._a4._a1.ToString(),polynom._a5._a0.ToString(),polynom._a5._a1.ToString(),polynom._a6._a0.ToString(),polynom._a6._a1.ToString(),module.ToString());
        PolynomGF7_mY_13 vv,d11;
         d1.setModule(module);
        d2.setModule(module);
        u.setModule(module);
        v.setModule(module);
         std::string s;
        while(v.deg() != 0 && v.isZero(module) != true)
        {
            if(u.deg() < v.deg())
            {
                    w = u;
                   s = u.getA0()._a0.ToString();
                   s = u.getA0()._a1.ToString();
                   s = u.getA1()._a0.ToString();
                   s = u.getA1()._a1.ToString();
                   s = u.getA2()._a0.ToString();
                   s = u.getA2()._a1.ToString();
                   s = u.getA3()._a0.ToString();
                   s = u.getA3()._a1.ToString();
                   s = u.getA4()._a0.ToString();
                   s = u.getA4()._a1.ToString();
                   s = u.getA5()._a0.ToString();
                   s = u.getA5()._a1.ToString();
                   s = u.getA6()._a0.ToString();
                   s = u.getA6()._a1.ToString();


                    u = v;
                   s = v.getA0()._a0.ToString();
                   s = v.getA0()._a1.ToString();
                   s = v.getA1()._a0.ToString();
                   s = v.getA1()._a1.ToString();
                   s = v.getA2()._a0.ToString();
                   s = v.getA2()._a1.ToString();
                   s = v.getA3()._a0.ToString();
                   s = v.getA3()._a1.ToString();
                   s = v.getA4()._a0.ToString();
                   s = v.getA4()._a1.ToString();
                   s = v.getA5()._a0.ToString();
                   s = v.getA5()._a1.ToString();
                   s = v.getA6()._a0.ToString();
                   s = v.getA6()._a1.ToString();


                    v = w;
                   s = w.getA0()._a0.ToString();
                   s = w.getA0()._a1.ToString();
                   s = w.getA1()._a0.ToString();
                   s = w.getA1()._a1.ToString();
                   s = w.getA2()._a0.ToString();
                   s = w.getA2()._a1.ToString();
                   s = w.getA3()._a0.ToString();
                   s = w.getA3()._a1.ToString();
                   s = w.getA4()._a0.ToString();
                   s = w.getA4()._a1.ToString();
                   s = w.getA5()._a0.ToString();
                   s = w.getA5()._a1.ToString();
                   s = w.getA6()._a0.ToString();
                   s = w.getA6()._a1.ToString();


                    w1 = d1;
                   s = d1.getA0()._a0.ToString();
                   s = d1.getA0()._a1.ToString();
                   s = d1.getA1()._a0.ToString();
                   s = d1.getA1()._a1.ToString();
                   s = d1.getA2()._a0.ToString();
                   s = d1.getA2()._a1.ToString();
                   s = d1.getA3()._a0.ToString();
                   s = d1.getA3()._a1.ToString();
                   s = d1.getA4()._a0.ToString();
                   s = d1.getA4()._a1.ToString();
                   s = d1.getA5()._a0.ToString();
                   s = d1.getA5()._a1.ToString();
                   s = d1.getA6()._a0.ToString();
                   s = d1.getA6()._a1.ToString();


                    d1 = d2;
                   s = d2.getA0()._a0.ToString();
                   s = d2.getA0()._a1.ToString();
                   s = d2.getA1()._a0.ToString();
                   s = d2.getA1()._a1.ToString();
                   s = d2.getA2()._a0.ToString();
                   s = d2.getA2()._a1.ToString();
                   s = d2.getA3()._a0.ToString();
                   s = d2.getA3()._a1.ToString();
                   s = d2.getA4()._a0.ToString();
                   s = d2.getA4()._a1.ToString();
                   s = d2.getA5()._a0.ToString();
                   s = d2.getA5()._a1.ToString();
                   s = d2.getA6()._a0.ToString();
                   s = d2.getA6()._a1.ToString();


                    d2 = w1;
            }
            d = u.deg() - v.deg();
            _v = v.getByIndex(v.deg());
            s = _v._a0.ToString();
            s = _v._a1.ToString();
 //           _v = inv.Inverse(_v,module);
            s = _v._a0.ToString();
            s = _v._a1.ToString();
            _q.Mul(u.getByIndex(u.deg()),inv);
            s = _q._a0.ToString();
            s = _q._a1.ToString();
            PolynomGF7_mY_13 q;
            q.setModule(polynom._module);
            q.setByIndex(_q,0);
                   s = q.getA0()._a0.ToString();
                   s = q.getA0()._a1.ToString();
                   s = q.getA1()._a0.ToString();
                   s = q.getA1()._a1.ToString();
                   s = q.getA2()._a0.ToString();
                   s = q.getA2()._a1.ToString();
                   s = q.getA3()._a0.ToString();
                   s = q.getA3()._a1.ToString();
                   s = q.getA4()._a0.ToString();
                   s = q.getA4()._a1.ToString();
                   s = q.getA5()._a0.ToString();
                   s = q.getA5()._a1.ToString();
                   s = q.getA6()._a0.ToString();
                   s = q.getA6()._a1.ToString();

             s = q.getModule().ToString();
            q = q.NormalMonomialMul(q,d);
                   s = q.getA0()._a0.ToString();
                   s = q.getA0()._a1.ToString();
                   s = q.getA1()._a0.ToString();
                   s = q.getA1()._a1.ToString();
                   s = q.getA2()._a0.ToString();
                   s = q.getA2()._a1.ToString();
                   s = q.getA3()._a0.ToString();
                   s = q.getA3()._a1.ToString();
                   s = q.getA4()._a0.ToString();
                   s = q.getA4()._a1.ToString();
                   s = q.getA5()._a0.ToString();
                   s = q.getA5()._a1.ToString();
                   s = q.getA6()._a0.ToString();
                   s = q.getA6()._a1.ToString();

            PolynomGF7_mY_13 minus;
            //q = minus.FullMul(two,q);
            r = u + vv.FullMul(v,q);
                   s = r.getA0()._a0.ToString();
                   s = r.getA0()._a1.ToString();
                   s = r.getA1()._a0.ToString();
                   s = r.getA1()._a1.ToString();
                   s = r.getA2()._a0.ToString();
                   s = r.getA2()._a1.ToString();
                   s = r.getA3()._a0.ToString();
                   s = r.getA3()._a1.ToString();
                   s = r.getA4()._a0.ToString();
                   s = r.getA4()._a1.ToString();
                   s = r.getA5()._a0.ToString();
                   s = r.getA5()._a1.ToString();
                   s = r.getA6()._a0.ToString();
                   s = r.getA6()._a1.ToString();

            c = d2 + d11.FullMul(d1,q);
                   s = c.getA0()._a0.ToString();
                   s = c.getA0()._a1.ToString();
                   s = c.getA1()._a0.ToString();
                   s = c.getA1()._a1.ToString();
                   s = c.getA2()._a0.ToString();
                   s = c.getA2()._a1.ToString();
                   s = c.getA3()._a0.ToString();
                   s = c.getA3()._a1.ToString();
                   s = c.getA4()._a0.ToString();
                   s = c.getA4()._a1.ToString();
                   s = c.getA5()._a0.ToString();
                   s = c.getA5()._a1.ToString();
                   s = c.getA6()._a0.ToString();
                   s = c.getA6()._a1.ToString();



            u = v;
                   s = u.getA0()._a0.ToString();
                   s = u.getA0()._a1.ToString();
                   s = u.getA1()._a0.ToString();
                   s = u.getA1()._a1.ToString();
                   s = u.getA2()._a0.ToString();
                   s = u.getA2()._a1.ToString();
                   s = u.getA3()._a0.ToString();
                   s = u.getA3()._a1.ToString();
                   s = u.getA4()._a0.ToString();
                   s = u.getA4()._a1.ToString();
                   s = u.getA5()._a0.ToString();
                   s = u.getA5()._a1.ToString();
                   s = u.getA6()._a0.ToString();
                   s = u.getA6()._a1.ToString();


            v = r;
                   s = v.getA0()._a0.ToString();
                   s = v.getA0()._a1.ToString();
                   s = v.getA1()._a0.ToString();
                   s = v.getA1()._a1.ToString();
                   s = v.getA2()._a0.ToString();
                   s = v.getA2()._a1.ToString();
                   s = v.getA3()._a0.ToString();
                   s = v.getA3()._a1.ToString();
                   s = v.getA4()._a0.ToString();
                   s = v.getA4()._a1.ToString();
                   s = v.getA5()._a0.ToString();
                   s = v.getA5()._a1.ToString();
                   s = v.getA6()._a0.ToString();
                   s = v.getA6()._a1.ToString();


            d2 = d1;
                   s = d2.getA0()._a0.ToString();
                   s = d2.getA0()._a1.ToString();
                   s = d2.getA1()._a0.ToString();
                   s = d2.getA1()._a1.ToString();
                   s = d2.getA2()._a0.ToString();
                   s = d2.getA2()._a1.ToString();
                   s = d2.getA3()._a0.ToString();
                   s = d2.getA3()._a1.ToString();
                   s = d2.getA4()._a0.ToString();
                   s = d2.getA4()._a1.ToString();
                   s = d2.getA5()._a0.ToString();
                   s = d2.getA5()._a1.ToString();
                   s = d2.getA6()._a0.ToString();
                   s = d2.getA6()._a1.ToString();


            d1 = c;
                   s = d1.getA0()._a0.ToString();
                   s = d1.getA0()._a1.ToString();
                   s = d1.getA1()._a0.ToString();
                   s = d1.getA1()._a1.ToString();
                   s = d1.getA2()._a0.ToString();
                   s = d1.getA2()._a1.ToString();
                   s = d1.getA3()._a0.ToString();
                   s = d1.getA3()._a1.ToString();
                   s = d1.getA4()._a0.ToString();
                   s = d1.getA4()._a1.ToString();
                   s = d1.getA5()._a0.ToString();
                   s = d1.getA5()._a1.ToString();
                   s = d1.getA6()._a0.ToString();
                   s = d1.getA6()._a1.ToString();


        }
            PolynomGF7_m_2 p,e0,e6,e01,e61,e62,e63,e64,e65;
            e0 = e01.Mul(polynom._a0,c.getA0());
            e6 = e61.Mul(polynom._a5,c.getA1()) + e62.Mul(polynom._a4,c.getA2()) + e63.Mul(polynom._a3,c.getA3()) + e64.Mul(polynom._a2,c.getA4()) + e65.Mul(polynom._a1,c.getA5());
            p = e0+e6;
            s = p._a0.ToString();
            s = p._a1.ToString();
//            _b.Inverse(p,module);
            s = _b._a0.ToString();
            s = _b._a1.ToString();
            PolynomGF7_m_14 cc;
            cc.setModule(module);
            cc.setByIndex(_b,0);
                   s = cc.getA0()._a0.ToString();
                   s = cc.getA0()._a1.ToString();
                   s = cc.getA1()._a0.ToString();
                   s = cc.getA1()._a1.ToString();
                   s = cc.getA2()._a0.ToString();
                   s = cc.getA2()._a1.ToString();
                   s = cc.getA3()._a0.ToString();
                   s = cc.getA3()._a1.ToString();
                   s = cc.getA4()._a0.ToString();
                   s = cc.getA4()._a1.ToString();
                   s = cc.getA5()._a0.ToString();
                   s = cc.getA5()._a1.ToString();
                   s = cc.getA6()._a0.ToString();
                   s = cc.getA6()._a1.ToString();

            c = _c.MonomialMul(c,cc);
                   s = c.getA0()._a0.ToString();
                   s = c.getA0()._a1.ToString();
                   s = c.getA1()._a0.ToString();
                   s = c.getA1()._a1.ToString();
                   s = c.getA2()._a0.ToString();
                   s = c.getA2()._a1.ToString();
                   s = c.getA3()._a0.ToString();
                   s = c.getA3()._a1.ToString();
                   s = c.getA4()._a0.ToString();
                   s = c.getA4()._a1.ToString();
                   s = c.getA5()._a0.ToString();
                   s = c.getA5()._a1.ToString();
                   s = c.getA6()._a0.ToString();
                   s = c.getA6()._a1.ToString();


        result._a0 = c.getA0();
        result._a1 = c.getA1();
        result._a2 = c.getA2();
        result._a3 = c.getA3();
        result._a4 = c.getA4();
        result._a5 = c.getA5();
        result._a6 = c.getA6();


        result._module = c.getModule();
        *this = result;
        return *this;
    }
   // извлечение квадратного корня
   PolynomGF7_m_14& PolynomGF7_m_14::LegendreSymbol( PolynomGF7_m_14 &a, PolynomGF7 &module)
   {
//        if(a.getModPolynom().isIrreducible() == false ||module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
       PolynomGF7_m_14 result,minus_one;//("6","0","0","0","0","0","0","0","0","0","0","0","0","");
       PolynomGF7_m_2 six("6","0",module.ToString());
         minus_one.setByIndex(six,0);
         minus_one._module = module;
        _modPolynom = a._modPolynom;
        _module = module;
        uint m = module.getNumberBits() - 1;
        Integer power("1");
        power.Pow(7,(14*m));
        power = (power-1)/2;
        std::string s;
        result.Pow(a,power);
        *this = result;
        s = _a0._a0.ToString();
        s = _a0._a1.ToString();
        s = _a1._a0.ToString();
        s = _a1._a1.ToString();
        s = _a2._a0.ToString();
        s = _a2._a1.ToString();
        s = _a3._a0.ToString();
        s = _a3._a1.ToString();
        s = _a4._a0.ToString();
        s = _a4._a1.ToString();
        s = _a5._a0.ToString();
        s = _a5._a1.ToString();
        s = _a6._a0.ToString();
        s = _a6._a1.ToString();
        return *this;
   }
   PolynomGF7_m_14& PolynomGF7_m_14::Sqrt(PolynomGF7_m_14 &x,PolynomGF7_m_14 &a, PolynomGF7 &module,Integer &ss,Integer &T)
   {
//        if(x.getModule().isIrreducible() == false ||module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

        bool rez;
        Integer s;
        s = ss;
         std::string st,o_st;
        PolynomGF7_m_14 test;
        PolynomGF7_m_14 zero;//("0","0","0","0","0","0","0","0","0","0","0","0","0",module.ToString());
        zero.setZero();
        zero.setModule(module);
        test.LegendreSymbol(x,module);
        st = test._a0._a0.ToString();
        st = test._a0._a1.ToString();
        st = test._a1._a0.ToString();
        st = test._a1._a1.ToString();
        st = test._a2._a0.ToString();
        st = test._a2._a1.ToString();
        st = test._a3._a0.ToString();
        st = test._a3._a1.ToString();
        st = test._a4._a0.ToString();
        st = test._a4._a1.ToString();
        st = test._a5._a0.ToString();
        st = test._a5._a1.ToString();
        st = test._a6._a0.ToString();
        st = test._a6._a1.ToString();
        uint m = module.getNumberBits() - 1;
        o_st.append("1");
        for(unsigned int i = 0  ; i < m-1; i++)
        {
            o_st.append("0");
        }
        if(test._a0._a0.ToString() != o_st)
        {
                *this = zero;
                return *this;
        }
        PolynomGF7_m_14 result,b,e1,e2,e3,e4,e5;
        result.setOne();
        PolynomGF7_m_14 minus_one;//("6","0","0","0","0","0","0","0","0","0","0","0","0",module.ToString());
        PolynomGF7_m_2 six("6","0",module.ToString());
         minus_one.setByIndex(six,0);
         minus_one._module = module;
        _modPolynom = x._modPolynom;
        _module = module;
//        uint m = module.getNumberBits() - 1;
        Integer power("1"),t("0");
        power.Pow(7,(14*m));
        power = (power-1)/2;

/*
        while(result != minus_one)
        {
          a.Generate(module);
          result.LegendreSymbol(a,module);
        }
*/
        a = a.Pow(a,s);
        st = a._a0._a0.ToString();
        st = a._a0._a1.ToString();
        st = a._a1._a0.ToString();
        st = a._a1._a1.ToString();
        st = a._a2._a0.ToString();
        st = a._a2._a1.ToString();
        st = a._a3._a0.ToString();
        st = a._a3._a1.ToString();
        st = a._a4._a0.ToString();
        st = a._a4._a1.ToString();
        st = a._a5._a0.ToString();
        st = a._a5._a1.ToString();
        st = a._a6._a0.ToString();
        st = a._a6._a1.ToString();
//        b = b.Pow(x,29);
/*        st = b._a0.ToString();
        st = b._a1.ToString();
        st = b._a2.ToString();
        st = b._a3.ToString();
        st = b._a4.ToString();
        st = b._a5.ToString();
        st = b._a6.ToString();
*/
        b.setOne();
        b = b.Pow(x,(s-1)/2);
        st = b._a0._a0.ToString();
        st = b._a0._a1.ToString();
        st = b._a1._a0.ToString();
        st = b._a1._a1.ToString();
        st = b._a2._a0.ToString();
        st = b._a2._a1.ToString();
        st = b._a3._a0.ToString();
        st = b._a3._a1.ToString();
        st = b._a4._a0.ToString();
        st = b._a4._a1.ToString();
        st = b._a5._a0.ToString();
        st = b._a5._a1.ToString();
        st = b._a6._a0.ToString();
        st = b._a6._a1.ToString();
        Integer two("2"), c("1"),e("1");
        Integer k("0"),t0("0");
        for(Integer i = 0; i < T; i++)
        {
                e1.Pow(a,t0);
                e2 = e1*b;
                e3 = e2*e2;
                e4 = e3*x;
                two.Pow(2,T-k - 1);
                st = two.ToString();
                e5.Pow(e4,two);
        st = e5._a0._a0.ToString();
        st = e5._a0._a1.ToString();
        st = e5._a1._a0.ToString();
        st = e5._a1._a1.ToString();
        st = e5._a2._a0.ToString();
        st = e5._a2._a1.ToString();
        st = e5._a3._a0.ToString();
        st = e5._a3._a1.ToString();
        st = e5._a4._a0.ToString();
        st = e5._a4._a1.ToString();
        st = e5._a5._a0.ToString();
        st = e5._a5._a1.ToString();
        st = e5._a6._a0.ToString();
        st = e5._a6._a1.ToString();

                if(e5 == minus_one)
                        c = 1;
                if(e5._a0._a0.ToString() == o_st)
                        c = 0;
                t = t + e.Pow(2,k)*c;
                t0 = t;
                k = k + 1;
        }
        *this = a.Pow(a,t)*b*x;
        st = _a0._a0.ToString();
        st = _a0._a1.ToString();
        st = _a1._a0.ToString();
        st = _a1._a1.ToString();
        st = _a2._a0.ToString();
        st = _a2._a1.ToString();
        st = _a3._a0.ToString();
        st = _a3._a1.ToString();
        st = _a4._a0.ToString();
        st = _a4._a1.ToString();
        st = _a5._a0.ToString();
        st = _a5._a1.ToString();
        st = _a6._a0.ToString();
        st = _a6._a1.ToString();
      return *this;
   }
   //тест образующего элемента, определение порядка элемента
   Integer& PolynomGF7_m_14::elementOrder(PolynomGF7 &groupModule, PolynomGF7_m_14 &polynom,std::vector<DecompositionMember> vector, const Integer &ord )
{
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    PolynomGF7 *m  = new PolynomGF7(groupModule);
    PolynomGF7_m_14 *a = new PolynomGF7_m_14(polynom);
    Integer t =  ord;
    for(it = vector.begin(); it != vector.end();it++)
   {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.ModPow(p,e, t);
      std::string s = ex.ToString();
      t = t/(ex);
      PolynomGF7_m_14 a1;
      a1._module  = *m;
      a1.Pow(*a,t);
      while(a1.isOne() == false)
      {
        a1.Pow(a1,p);
        t = t*p;
      }
    }
    AAL::Integer *rez =  new AAL::Integer(t);
    return *rez;
  }
  else
     throw new Exception("Введите разложение порядка группы.");
}
bool PolynomGF7_m_14::isGenerator(PolynomGF7 &groupModule, PolynomGF7_m_14 &polynom,std::vector<DecompositionMember> vector, Integer &ord)
{
    if(vector.size() >= 1)
    {   AAL::Integer m(ord-1);
       // AAL::Integer b(polynom.ToString(),Bin);
      Integer t = elementOrder(groupModule, polynom,vector,ord-1);
       if(t == m)
        return true;
    }
  else
   throw new Exception("Введите разложение порядка группы.");
return false;
}
void PolynomGF7_m_14::exist(PolynomGF7_m_2 &a, PolynomGF7& module)
{
    _a0 = a;
    _a1.setZero();
    _a2.setZero();
    _a3.setZero();
    _a4.setZero();
    _a5.setZero();
    _a6.setZero();


    _module = module;
}
PolynomGF7_m_14& PolynomGF7_m_14::Generate(PolynomGF7& module)
{
        _a0 = _a0.Generate(module);
        _a1 = _a1.Generate(module);
        _a2 = _a2.Generate(module);
        _a3 = _a3.Generate(module);
        _a4 = _a4.Generate(module);
        _a5 = _a5.Generate(module);
        _a6 = _a6.Generate(module);


        _module = module;
        return *this;
}

//-----------------------------------------------------------------------------------
PolynomGF7_m_14& PolynomGF7_m_14::getRo(PolynomGF7_m_14 &b,PolynomGF7& mod)
{
      PolynomGF7_m_14 p,f,f0,e,h;//("0","0","0","0","0","0","0","0","0","0","0","0","0",mod.ToString())
      h.setZero();
      h.setModule(mod);
      PolynomGF7_m_14 six;//("6","0","0","0","0","0","0","0","0","0","0","0","0",mod.ToString());
      PolynomGF7_m_2 sx("6","0",mod.ToString());
      six.setByIndex(sx,0);
      six.setModule(mod);
      f.setModule(mod);
      f.setOne();
      h.setModule(mod);
      e.setModule(mod);
      f0.setModule(mod);
      std::string s;
      while(f.isZero() == false)
      {
        p.Generate(mod);
/*    s = p.getA0().ToString();
    s =  p.getA1().ToString();
    s = p.getA2().ToString();
    s = p.getA3().ToString();
    s = p.getA4().ToString();
    s = p.getA5().ToString();
    s = p.getA6().ToString();
*/
        h.Pow(p,Integer(7));
/*    s = h.getA0().ToString();
    s =  h.getA1().ToString();
    s = h.getA2().ToString();
    s = h.getA3().ToString();
    s = h.getA4().ToString();
    s = h.getA5().ToString();
    s = h.getA6().ToString();
*/

        e.Mul(p,six);
/*    s = e.getA0().ToString();
    s =  e.getA1().ToString();
    s = e.getA2().ToString();
    s = e.getA3().ToString();
    s = e.getA4().ToString();
    s = e.getA5().ToString();
    s = e.getA6().ToString();
*/

        f0.Mul(b,six);
/*    s = f0.getA0().ToString();
    s =  f0.getA1().ToString();
    s = f0.getA2().ToString();
    s = f0.getA3().ToString();
    s = f0.getA4().ToString();
    s = f0.getA5().ToString();
    s = f0.getA6().ToString();

*/
        f = p+h+e+f0;
/*        s = f.getA0().ToString();
    s =  f.getA1().ToString();
    s = f.getA2().ToString();
    s = f.getA3().ToString();
    s = f.getA4().ToString();
    s = f.getA5().ToString();
    s = f.getA6().ToString();
*/

    }
    *this = p;
    return *this;
}
};



