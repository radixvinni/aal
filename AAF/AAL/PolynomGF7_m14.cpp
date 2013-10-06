/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF7_m14.h"
#include "PolynomGF7_mY_13.h"
#include "PolynomGF7.h"
#include "Converter.h"
#include "Integer.h"
#include "DecompositionManager.h"
#include <string>
#include <stdlib.h>
namespace AAL
{
  int PolynomGF7_m14::sevendiv(std::vector<Integer>* m, Integer n)
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

//***********************************   онструкторы  *******************************************
	//(c) Belova, TEST(PolynomGF3_m_6, EmptyConstructor)
	PolynomGF7_m14::PolynomGF7_m14() :
        _a0(), _a1(), _a2(), _a3(), _a4(), _a5(),_a6(),_a7(), _a8(), _a9(), _a10(), _a11(), _a12(),_a13(), _module(), _modPolynom("410000000000001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, CopyConstructor)
	PolynomGF7_m14::PolynomGF7_m14(const PolynomGF7_m14 &polynom)
	{
     _a0 = polynom._a0;
     _a1 = polynom._a1;
     _a2 = polynom._a2;
     _a3 = polynom._a3;
     _a4 = polynom._a4;
     _a5 = polynom._a5;
     _a6 = polynom._a6;
     _a7 = polynom._a7;
     _a8 = polynom._a8;
     _a9 = polynom._a9;
     _a10 = polynom._a10;
     _a11 = polynom._a11;
     _a12 = polynom._a12;
     _a13 = polynom._a13;


     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, StringConstructor)
	PolynomGF7_m14::PolynomGF7_m14(const std::string a0,
     const std::string a1, const std::string a2,
     const std::string a3, const std::string a4,
     const std::string a5, const std::string a6,
     const std::string a7, const std::string a8,
     const std::string a9, const std::string a10,
     const std::string a11, const std::string a12,
     const std::string a13, const std::string module):
     _a0(a0), _a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6),_a7(a7), _a8(a8), _a9(a9), _a10(a10), _a11(a11), _a12(a12), _a13(a13),_module(module), _modPolynom("410000000000001")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF7_m14::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero() && _a11.isZero() && _a12.isZero() && _a13.isZero())
            return true;
        return false;
    }
    bool PolynomGF7_m14::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero()&& _a6.isZero()&& _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero() && _a11.isZero() && _a12.isZero()&& _a13.isZero())
            return true;
        return false;
    }
//------------------------------------------------------------------------------
	PolynomGF7_m14& PolynomGF7_m14::setZero()
	{
        _a0.setZero();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        _a4.setZero();
        _a5.setZero();
        _a6.setZero();
        _a7.setZero();
        _a8.setZero();
        _a9.setZero();
        _a10.setZero();
        _a11.setZero();
        _a12.setZero();
        _a13.setZero();

		return *this;
	}
    //simple method
	PolynomGF7_m14& PolynomGF7_m14::setOne()
	{
        _a0.setOne();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        _a4.setZero();
        _a5.setZero();
        _a6.setZero();
        _a7.setOne();
        _a8.setZero();
        _a9.setZero();
        _a10.setZero();
        _a11.setZero();
        _a12.setZero();
        _a13.setZero();

        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, Equal)
	bool operator==(const PolynomGF7_m14& a, const PolynomGF7_m14& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3  && a._a4 == b._a4 && a._a5 == b._a5 && a._a6 == b._a6 && a._a7 == b._a7 && a._a8 == b._a8 && a._a9 == b._a9 && a._a10 == b._a10  && a._a11 == b._a11 && a._a12 == b._a12 && a._a13 == b._a13)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, operatorEqual)
	PolynomGF7_m14& PolynomGF7_m14::operator= (const PolynomGF7_m14& polynom)
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
        _a7 = polynom._a7;
        _a8 = polynom._a8;
        _a9 = polynom._a9;
        _a10 = polynom._a10;
        _a11 = polynom._a11;
        _a12 = polynom._a12;
        _a13 = polynom._a13;


        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF7_m14& a, const PolynomGF7_m14& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF7& PolynomGF7_m14::getA0() const
  {
    return _a0;
  }
  const PolynomGF7& PolynomGF7_m14::getA1() const
  {
    return _a1;
  }
  const PolynomGF7& PolynomGF7_m14::getA2() const
  {
    return _a2;
  }
  const PolynomGF7& PolynomGF7_m14::getA3() const
  {
    return _a3;
  }
  const PolynomGF7& PolynomGF7_m14::getA4() const
  {
    return _a4;
  }
  const PolynomGF7& PolynomGF7_m14::getA5() const
  {
    return _a5;
  }
  const PolynomGF7& PolynomGF7_m14::getA6() const
  {
    return _a6;
  }
  const PolynomGF7& PolynomGF7_m14::getA7() const
  {
    return _a7;
  }
  const PolynomGF7& PolynomGF7_m14::getA8() const
  {
    return _a8;
  }
  const PolynomGF7& PolynomGF7_m14::getA9() const
  {
    return _a9;
  }
  const PolynomGF7& PolynomGF7_m14::getA10() const
  {
    return _a10;
  }
  const PolynomGF7& PolynomGF7_m14::getA11() const
  {
    return _a11;
  }
  const PolynomGF7& PolynomGF7_m14::getA12() const
  {
    return _a12;
  }
  const PolynomGF7& PolynomGF7_m14::getA13() const
  {
    return _a13;
  }

  const PolynomGF7& PolynomGF7_m14::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF7& PolynomGF7_m14::getModule() const
  {
    return _module;
  }

//------------------------------------------------------------------------------
    void PolynomGF7_m14::setA0(const PolynomGF7 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF7_m14::setA1(const PolynomGF7 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF7_m14::setA2(const PolynomGF7 & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF7_m14::setA3(const PolynomGF7 & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF7_m14::setA4(const PolynomGF7 & a)
    {
        _a4 = a;
        _a4 %= _module;
    }
    void PolynomGF7_m14::setA5(const PolynomGF7 & a)
    {
        _a5 = a;
        _a5 %= _module;
    }
    void PolynomGF7_m14::setA6(const PolynomGF7 & a)
    {
        _a6 = a;
        _a6 %= _module;
    }
    void PolynomGF7_m14::setA7(const PolynomGF7 & a)
    {
        _a7 = a;
        _a7 %= _module;
    }
    void PolynomGF7_m14::setA8(const PolynomGF7 & a)
    {
        _a8 = a;
        _a8 %= _module;
    }
    void PolynomGF7_m14::setA9(const PolynomGF7 & a)
    {
        _a9 = a;
        _a9 %= _module;
    }
    void PolynomGF7_m14::setA10(const PolynomGF7 & a)
    {
        _a10 = a;
        _a10 %= _module;
    }
    void PolynomGF7_m14::setA11(const PolynomGF7 & a)
    {
        _a11 = a;
        _a11 %= _module;
    }
    void PolynomGF7_m14::setA12(const PolynomGF7 & a)
    {
        _a12 = a;
        _a12 %= _module;
    }
    void PolynomGF7_m14::setA13(const PolynomGF7 & a)
    {
        _a13 = a;
        _a13 %= _module;
    }
    void PolynomGF7_m14::setModule(const PolynomGF7& module)
    {
        _module = module;
        _a0 %= _module;
        _a1 %= _module;
        _a2 %= _module;
        _a3 %= _module;
        _a4 %= _module;
        _a5 %= _module;
        _a6 %= _module;
        _a7 %= _module;
        _a8 %= _module;
        _a9 %= _module;
        _a10 %= _module;
        _a11 %= _module;
        _a12 %= _module;
        _a13 %= _module;


    }
    void PolynomGF7_m14::setModPolynom(const PolynomGF7& modPolynom)
    {
        _modPolynom = modPolynom;
     //   if((modPolynom.getNumberBits()-1)!=14)
       //     throw std::out_of_range("модул€рные многочлен порождающий расширение пол€ должны быть степени 14");
    }
//------------------------------------------------------------------------------
//******************************    ќпераци€ сложени€    ***************************************
	//simple method
	PolynomGF7_m14 operator+(const PolynomGF7_m14 &a, const PolynomGF7_m14 &b)
	{
		PolynomGF7_m14 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m14& PolynomGF7_m14::operator+=(PolynomGF7_m14 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF7_m14& PolynomGF7_m14::Add(PolynomGF7_m14 &a, PolynomGF7_m14 &b)
	{
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module=a._module;
        _a0.Add(a._a0, b._a0);
//        std::string s =  _a0.ToString();
        _a1.Add(a._a1, b._a1);
//        s =  _a1.ToString();
        _a2.Add(a._a2, b._a2);
//        s =  _a2.ToString();
        _a3.Add(a._a3, b._a3);
//        s =  _a3.ToString();
        _a4.Add(a._a4, b._a4);
//        s =  _a4.ToString();
        _a5.Add(a._a5, b._a5);
//        s =  _a5.ToString();
        _a6.Add(a._a6, b._a6);
//        s =  _a6.ToString();
        _a7.Add(a._a7, b._a7);
//        s =  _a7.ToString();
        _a8.Add(a._a8, b._a8);
//        s =  _a8.ToString();
        _a9.Add(a._a9, b._a9);
//        s =  _a9.ToString();
        _a10.Add(a._a10, b._a10);
//        s =  _a10.ToString();
        _a11.Add(a._a11, b._a11);
//        s =  _a11.ToString();
        _a12.Add(a._a12, b._a12);
//        s =  _a12.ToString();
        _a13.Add(a._a13, b._a13);
//        s =  _a13.ToString();

        return *this;
	}
	//simple method
	PolynomGF7_m14 operator*(const PolynomGF7_m14 &a, const PolynomGF7_m14 &b)
	{
		PolynomGF7_m14 result;
        PolynomGF7_m14 copy_a(a), copy_b(b);
 		return result.Mul(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m14& PolynomGF7_m14::operator*=(PolynomGF7_m14 &polynom)
	{
		return Mul(*this, polynom);
	}
//------------------------------------------------------------------------------

	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF7_m14& PolynomGF7_m14::Mul(PolynomGF7_m14 &a, PolynomGF7_m14 &b)
	{
        PolynomGF7 e0;
        PolynomGF7 e1,e1_1,e1_2;
        PolynomGF7 e2,e2_1,e2_2,e2_3;
        PolynomGF7 e3,e3_1,e3_2,e3_3,e3_4;
        PolynomGF7 e4, e4_1,e4_2,e4_3,e4_4,e4_5;
        PolynomGF7 e5,e5_1,e5_2,e5_3,e5_4,e5_5,e5_6;
        PolynomGF7 e6,e6_1,e6_2,e6_3,e6_4,e6_5,e6_6,e6_7;
        PolynomGF7 e7,e7_1,e7_2,e7_3,e7_4,e7_5,e7_6,e7_7,e7_8;
        PolynomGF7 e8,e8_1,e8_2,e8_3,e8_4,e8_5,e8_6,e8_7,e8_8,e8_9;
        PolynomGF7 e9,e9_1,e9_2,e9_3,e9_4,e9_5,e9_6,e9_7,e9_8,e9_9,e9_10;
        PolynomGF7 e10,e10_1,e10_2,e10_3,e10_4,e10_5,e10_6,e10_7,e10_8,e10_9,e10_10,e10_11;
        PolynomGF7 e11,e11_1,e11_2,e11_3,e11_4,e11_5,e11_6,e11_7,e11_8,e11_9,e11_10,e11_11,e11_12;
        PolynomGF7 e12,e12_1,e12_2,e12_3,e12_4,e12_5,e12_6,e12_7,e12_8,e12_9,e12_10,e12_11,e12_12,e12_13;
        PolynomGF7 e13,e13_1,e13_2,e13_3,e13_4,e13_5,e13_6,e13_7,e13_8,e13_9,e13_10,e13_11,e13_12,e13_13,e13_14;
        PolynomGF7 e14,e14_1,e14_2,e14_3,e14_4,e14_5,e14_6,e14_7,e14_8,e14_9,e14_10,e14_11,e14_12,e14_13;
        PolynomGF7 e15,e15_1,e15_2,e15_3,e15_4,e15_5,e15_6,e15_7,e15_8,e15_9,e15_10,e15_11,e15_12;
        PolynomGF7 e16,e16_1,e16_2,e16_3,e16_4,e16_5,e16_6,e16_7,e16_8,e16_9,e16_10,e16_11;
        PolynomGF7 e17,e17_1,e17_2,e17_3,e17_4,e17_5,e17_6,e17_7,e17_8,e17_9,e17_10;
        PolynomGF7 e18,e18_1,e18_2,e18_3,e18_4,e18_5,e18_6,e18_7,e18_8,e18_9;
        PolynomGF7 e19,e19_1,e19_2,e19_3,e19_4,e19_5,e19_6,e19_7,e19_8;
        PolynomGF7 e20,e20_1,e20_2,e20_3,e20_4,e20_5,e20_6,e20_7;
        PolynomGF7 e21,e21_1,e21_2,e21_3,e21_4,e21_5,e21_6;
        PolynomGF7 e22,e22_1,e22_2,e22_3,e22_4,e22_5;
        PolynomGF7 e23,e23_1,e23_2,e23_3,e23_4;
        PolynomGF7 e24,e24_1,e24_2,e24_3;
        PolynomGF7 e25,e25_1,e25_2;
        PolynomGF7 e26;
        PolynomGF7 four("400"),c("0");
        PolynomGF7 six("600"),minus2b("000"),three("300");
        PolynomGF7 c0("0"),c1("0"),c2("0"),c3("0"),c4("0"),c5("0"),c6("0"),c7("0"),c8("0"),c9("0"),c10("0"),c11("0"),c12("0"),c13("0");
        PolynomGF7 d0("0"),d1("0"),d2("0"),d3("0"),d4("0"),d5("0"),d6("0"),d7("0"),d8("0"),d9("0"),d10("0"),d11("0"),d12("0"),d13("0");

        minus2b.Mul(six,four);
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module = a._module;

		if(a.isZero() || b.isZero())
  			return setZero();
         e0.ModMul(a._a0,b._a0,_module);
         e1_1.ModMul(a._a1,b._a0,_module);
         e1_2.ModMul(a._a0,b._a1,_module);
         e1 = e1_1 + e1_2;
         e2 = e2_1.ModMul(a._a2,b._a0,_module) + e2_2.ModMul(a._a1,b._a1,_module) + e2_3.ModMul(a._a0,b._a2,_module);
         e3 = e3_1.ModMul(a._a3,b._a0,_module) + e3_2.ModMul(a._a2,b._a1,_module) + e3_3.ModMul(a._a1,b._a2,_module)+ e3_4.ModMul(a._a0,b._a3,_module);
         e4 = e4_1.ModMul(a._a4,b._a0,_module) + e4_2.ModMul(a._a3,b._a1,_module) + e4_3.ModMul(a._a2,b._a2,_module)+ e4_4.ModMul(a._a1,b._a3,_module)+ e4_5.ModMul(a._a0,b._a4,_module);
         e5 = e5_1.ModMul(a._a5,b._a0,_module) + e5_2.ModMul(a._a4,b._a1,_module) + e5_3.ModMul(a._a3,b._a2,_module)+ e5_4.ModMul(a._a2,b._a3,_module)+ e5_5.ModMul(a._a1,b._a4,_module)+ e5_6.ModMul(a._a0,b._a5,_module);
         e6 = e6_1.ModMul(a._a6,b._a0,_module) + e6_2.ModMul(a._a5,b._a1,_module) + e6_3.ModMul(a._a4,b._a2,_module)+ e6_4.ModMul(a._a3,b._a3,_module)+ e6_5.ModMul(a._a2,b._a4,_module)+ e6_6.ModMul(a._a1,b._a5,_module)+ e6_7.ModMul(a._a0,b._a6,_module);
         e7 = e7_1.ModMul(a._a7,b._a0,_module) + e7_2.ModMul(a._a6,b._a1,_module) + e7_3.ModMul(a._a5,b._a2,_module)+ e7_4.ModMul(a._a4,b._a3,_module)+ e7_5.ModMul(a._a3,b._a4,_module)+ e7_6.ModMul(a._a2,b._a5,_module)+ e7_7.ModMul(a._a1,b._a6,_module) + e7_8.ModMul(a._a0,b._a7,_module);
         e8 = e8_1.ModMul(a._a8,b._a0,_module) + e8_2.ModMul(a._a7,b._a1,_module) + e8_3.ModMul(a._a6,b._a2,_module)+ e8_4.ModMul(a._a5,b._a3,_module)+ e8_5.ModMul(a._a4,b._a4,_module)+ e8_6.ModMul(a._a3,b._a5,_module)+ e8_7.ModMul(a._a2,b._a6,_module)+ e8_8.ModMul(a._a1,b._a7,_module)+ e8_9.ModMul(a._a0,b._a8,_module);
         e9 = e9_1.ModMul(a._a9,b._a0,_module) + e9_2.ModMul(a._a8,b._a1,_module) + e9_3.ModMul(a._a7,b._a2,_module)+ e9_4.ModMul(a._a6,b._a3,_module)+ e9_5.ModMul(a._a5,b._a4,_module)+ e9_6.ModMul(a._a4,b._a5,_module)+ e9_7.ModMul(a._a3,b._a6,_module)+ e9_8.ModMul(a._a2,b._a7,_module)+ e9_9.ModMul(a._a1,b._a8,_module)+ e9_10.ModMul(a._a0,b._a9,_module);
         e10 = e10_1.ModMul(a._a10,b._a0,_module) + e10_2.ModMul(a._a9,b._a1,_module) + e10_3.ModMul(a._a8,b._a2,_module)+ e10_4.ModMul(a._a7,b._a3,_module)+ e10_5.ModMul(a._a6,b._a4,_module)+ e10_6.ModMul(a._a5,b._a5,_module)+ e10_7.ModMul(a._a4,b._a6,_module)+ e10_8.ModMul(a._a3,b._a7,_module)+ e10_9.ModMul(a._a2,b._a8,_module)+ e10_10.ModMul(a._a1,b._a9,_module)+ e10_11.ModMul(a._a0,b._a10,_module);
         e11 = e11_1.ModMul(a._a11,b._a0,_module) + e11_2.ModMul(a._a10,b._a1,_module) + e11_3.ModMul(a._a9,b._a2,_module) + e11_4.ModMul(a._a8,b._a3,_module) + e11_5.ModMul(a._a7,b._a4,_module) + e11_6.ModMul(a._a6,b._a5,_module) + e11_7.ModMul(a._a5,b._a6,_module) + e11_8.ModMul(a._a4,b._a7,_module) + e11_9.ModMul(a._a3,b._a8,_module) + e11_10.ModMul(a._a2,b._a9,_module) + e11_11.ModMul(a._a1,b._a10,_module) + e11_12.ModMul(a._a0,b._a11,_module);
         e12 = e12_1.ModMul(a._a12,b._a0,_module) + e12_2.ModMul(a._a11,b._a1,_module) + e12_3.ModMul(a._a10,b._a2,_module) + e12_4.ModMul(a._a9,b._a3,_module) + e12_5.ModMul(a._a8,b._a4,_module) + e12_6.ModMul(a._a7,b._a5,_module) + e12_7.ModMul(a._a6,b._a6,_module) + e12_8.ModMul(a._a5,b._a7,_module) + e12_9.ModMul(a._a4,b._a8,_module) + e12_10.ModMul(a._a3,b._a9,_module) + e12_11.ModMul(a._a2,b._a10,_module) + e12_12.ModMul(a._a1,b._a11,_module)+ e12_13.ModMul(a._a0,b._a12,_module);
         e13 = e13_1.ModMul(a._a13,b._a0,_module) + e13_2.ModMul(a._a12,b._a1,_module) + e13_3.ModMul(a._a11,b._a2,_module) + e13_4.ModMul(a._a10,b._a3,_module) + e13_5.ModMul(a._a9,b._a4,_module) + e13_6.ModMul(a._a8,b._a5,_module) + e13_7.ModMul(a._a7,b._a6,_module) + e13_8.ModMul(a._a6,b._a7,_module) + e13_9.ModMul(a._a5,b._a8,_module) + e13_10.ModMul(a._a4,b._a9,_module) + e13_11.ModMul(a._a3,b._a10,_module) + e13_12.ModMul(a._a2,b._a11,_module)+ e13_13.ModMul(a._a1,b._a12,_module)+ e13_14.ModMul(a._a0,b._a13,_module);
         e14 = e14_1.ModMul(a._a13,b._a1,_module) + e14_2.ModMul(a._a12,b._a2,_module) + e14_3.ModMul(a._a11,b._a3,_module) + e14_4.ModMul(a._a10,b._a4,_module) + e14_5.ModMul(a._a9,b._a5,_module) + e14_6.ModMul(a._a8,b._a6,_module) + e14_7.ModMul(a._a7,b._a7,_module) + e14_8.ModMul(a._a6,b._a8,_module) + e14_9.ModMul(a._a5,b._a9,_module) + e14_10.ModMul(a._a4,b._a10,_module) + e14_11.ModMul(a._a3,b._a11,_module) + e14_12.ModMul(a._a2,b._a12,_module)+ e14_13.ModMul(a._a1,b._a13,_module);
         e15 = e15_1.ModMul(a._a13,b._a2,_module) + e15_2.ModMul(a._a12,b._a3,_module) + e15_3.ModMul(a._a11,b._a4,_module) + e15_4.ModMul(a._a10,b._a5,_module) + e15_5.ModMul(a._a9,b._a6,_module) + e15_6.ModMul(a._a8,b._a7,_module) + e15_7.ModMul(a._a7,b._a8,_module) + e15_8.ModMul(a._a6,b._a9,_module) + e15_9.ModMul(a._a5,b._a10,_module) + e15_10.ModMul(a._a4,b._a11,_module) + e15_11.ModMul(a._a3,b._a12,_module) + e15_12.ModMul(a._a2,b._a13,_module);
         e16 = e16_1.ModMul(a._a13,b._a3,_module) + e16_2.ModMul(a._a12,b._a4,_module) + e16_3.ModMul(a._a11,b._a5,_module) + e16_4.ModMul(a._a10,b._a6,_module) + e16_5.ModMul(a._a9,b._a7,_module) + e16_6.ModMul(a._a8,b._a8,_module) + e16_7.ModMul(a._a7,b._a9,_module) + e16_8.ModMul(a._a6,b._a10,_module) + e16_9.ModMul(a._a5,b._a11,_module) + e16_10.ModMul(a._a4,b._a12,_module) + e16_11.ModMul(a._a3,b._a13,_module);
         e17 = e17_1.ModMul(a._a13,b._a4,_module) + e17_2.ModMul(a._a12,b._a5,_module) + e17_3.ModMul(a._a11,b._a6,_module) + e17_4.ModMul(a._a10,b._a7,_module) + e17_5.ModMul(a._a9,b._a8,_module) + e17_6.ModMul(a._a8,b._a9,_module) + e17_7.ModMul(a._a7,b._a10,_module) + e17_8.ModMul(a._a6,b._a11,_module) + e17_9.ModMul(a._a5,b._a12,_module) + e17_10.ModMul(a._a4,b._a13,_module);
         e18 = e18_1.ModMul(a._a13,b._a5,_module) + e18_2.ModMul(a._a12,b._a6,_module) + e18_3.ModMul(a._a11,b._a7,_module) + e18_4.ModMul(a._a10,b._a8,_module) + e18_5.ModMul(a._a9,b._a9,_module) + e18_6.ModMul(a._a8,b._a10,_module) + e18_7.ModMul(a._a7,b._a11,_module) + e18_8.ModMul(a._a6,b._a12,_module) + e18_9.ModMul(a._a5,b._a13,_module);
         e19 = e19_1.ModMul(a._a13,b._a6,_module) + e19_2.ModMul(a._a12,b._a7,_module) + e19_3.ModMul(a._a11,b._a8,_module) + e19_4.ModMul(a._a10,b._a9,_module) + e19_5.ModMul(a._a9,b._a10,_module) + e19_6.ModMul(a._a8,b._a11,_module) + e19_7.ModMul(a._a7,b._a12,_module) + e19_8.ModMul(a._a6,b._a13,_module);
         e20 = e20_1.ModMul(a._a13,b._a7,_module) + e20_2.ModMul(a._a12,b._a8,_module) + e20_3.ModMul(a._a11,b._a9,_module) + e20_4.ModMul(a._a10,b._a10,_module) + e20_5.ModMul(a._a9,b._a11,_module) + e20_6.ModMul(a._a8,b._a12,_module) + e20_7.ModMul(a._a7,b._a13,_module);
         e21 = e21_1.ModMul(a._a13,b._a8,_module) + e21_2.ModMul(a._a12,b._a9,_module) + e21_3.ModMul(a._a11,b._a10,_module) + e21_4.ModMul(a._a10,b._a11,_module) + e21_5.ModMul(a._a9,b._a12,_module) + e21_6.ModMul(a._a8,b._a13,_module);
         e22 = e22_1.ModMul(a._a13,b._a9,_module) + e22_2.ModMul(a._a12,b._a10,_module) + e22_3.ModMul(a._a11,b._a11,_module) + e22_4.ModMul(a._a10,b._a12,_module) + e22_5.ModMul(a._a9,b._a13,_module);
         e23 = e23_1.ModMul(a._a13,b._a10,_module) + e23_2.ModMul(a._a12,b._a11,_module) + e23_3.ModMul(a._a11,b._a12,_module) + e23_4.ModMul(a._a10,b._a13,_module);
         e24 = e24_1.ModMul(a._a13,b._a11,_module) + e24_2.ModMul(a._a12,b._a12,_module) + e24_3.ModMul(a._a11,b._a13,_module);
         e25 = e25_1.ModMul(a._a13,b._a12,_module) + e25_2.ModMul(a._a12,b._a13,_module);
         e26.ModMul(a._a13,b._a13,_module);
        _a13 = e13 + c13.ModMul(six,e26,_module);
//        std::string s = _a13.ToString();
        _a12 = e12 + c12.ModMul(six,e25,_module) + d12.ModMul(minus2b,e26,_module);
//        s = _a12.ToString();
        _a11 = e11 + c11.ModMul(six,e24,_module) + d11.ModMul(minus2b,e25,_module);
//        s = _a11.ToString();
        _a10 = e10 + c10.ModMul(six,e23,_module) + d10.ModMul(minus2b,e24,_module);
//        s = _a10.ToString();
        _a9 =  e9 +c9.ModMul(six,e22,_module) + d9.ModMul(minus2b,e23,_module);
//        s = _a9.ToString();
        _a8 =  e8 + c8.ModMul(six,e21,_module) + d8.ModMul(minus2b,e22,_module);
//        s = _a8.ToString();
        _a7 =  e7 + c7.ModMul(six,e20,_module) + d7.ModMul(minus2b,e21,_module);
//        s = _a7.ToString();
        _a6 = e6 + c6.ModMul(six,e19,_module)+d6.ModMul(minus2b,e20,_module);
//         s = _a6.ToString();
        _a5 = e5 + c5.ModMul(six,e18,_module) + d5.ModMul(minus2b,e19,_module);
//        s = _a5.ToString();
        _a4 = e4 + c4.ModMul(six,e17,_module) + d4.ModMul(minus2b,e18,_module);
//        s = _a4.ToString();
        _a3 = e3 + c3.ModMul(six,e16,_module) + d3.ModMul(minus2b,e17,_module);
//        s = _a3.ToString();
        _a2 =  e2 +c2.ModMul(six,e15,_module) + d2.ModMul(minus2b,e16,_module);
//        s = _a2.ToString();
        _a1 =  e1 + c1.ModMul(six,e14,_module) + d1.ModMul(minus2b,e15,_module);
//        s = _a1.ToString();
        _a0 =  e0 + c0.ModMul(minus2b,e14,_module);
//        s = _a0.ToString();

		return *this;
	}
// простой метод возведени€ в степень 7 по модулю
	PolynomGF7_m14& PolynomGF7_m14::Seven(PolynomGF7_m14 &a)
	{
		PolynomGF7_m14 e0,e1,e2,e3,e13,e14;
        _modPolynom = a._modPolynom;
        _module = a._module;
		if(a.isZero())
  			return setZero();
//        if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
        e0._module = a._module;
        e1._module = a._module;
        e2._module = a._module;
        e3._module = a._module;
        e0.Mul(a,a);
        e1.Mul(e0,e0);
        e2.Mul(e1,e0);
        e3.Mul(e2,a);
        *this = e3;
/*        std::string s;
        s = _a0.ToString();
        s = _a1.ToString();
        s = _a2.ToString();
        s = _a3.ToString();
        s = _a4.ToString();
        s = _a5.ToString();
        s = _a6.ToString();
        s = _a7.ToString();
        s = _a8.ToString();
        s = _a9.ToString();
        s = _a10.ToString();
        s = _a11.ToString();
        s = _a12.ToString();
        s = _a13.ToString();
  */
		return *this;
	}
	PolynomGF7_m14& PolynomGF7_m14::SevenFast(PolynomGF7_m14 &a)
	{
        PolynomGF7 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13;
        PolynomGF7 c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13;
        PolynomGF7 c0_1,c0_2,c0_3,c0_4,c0_5,c0_6,c0_7;
        PolynomGF7 c1_1,c1_2,c1_3,c1_4,c1_5,c1_6,c1_7;
        PolynomGF7 c2_1,c2_2,c2_3,c2_4,c2_5,c2_6,c2_7;
        PolynomGF7 c3_1,c3_2,c3_3,c3_4,c3_5,c3_6,c3_7;
        PolynomGF7 c4_1,c4_2,c4_3,c4_4,c4_5,c4_6,c4_7;
        PolynomGF7 c5_1,c5_2,c5_3,c5_4,c5_5,c5_6,c5_7;
        PolynomGF7 c6_1,c6_2,c6_3,c6_4,c6_5,c6_6,c6_7;
        PolynomGF7 c7_1,c7_2,c7_3,c7_4,c7_5,c7_6,c7_7;
        PolynomGF7 c8_1,c8_2,c8_3,c8_4,c8_5,c8_6,c8_7;
        PolynomGF7 c9_1,c9_2,c9_3,c9_4,c9_5,c9_6,c9_7;
        PolynomGF7 c10_1,c10_2,c10_3,c10_4,c10_5,c10_6,c10_7;
        PolynomGF7 c11_1,c11_2,c11_3,c11_4,c11_5,c11_6,c11_7;
        PolynomGF7 c12_1,c12_2,c12_3,c12_4,c12_5,c12_6,c12_7;

        _modPolynom = a._modPolynom;
        _module = a._module;
      std::string  o_2,e_4,o_5,e_6,e_3,o_6,s;
      e_4.append("4");
      o_2.append("2");
      e_6.append("6");
      o_5.append("5");
      e_3.append("3");
      o_6.append("6");
      uint m1 = a._module.getNumberBits() - 1;
        for(unsigned int i = 0  ; i < m1-1; i++)
        {
          e_4.append("0");
          o_2.append("0");
          e_6.append("0");
          o_5.append("0");
          e_3.append("0");
          o_6.append("0");

        }
        PolynomGF7 two(o_2),three(e_3),four(e_4),five(o_5),six(o_6);

		if(a.isZero())
  			return setZero();
//        if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

       a0 =  a0.Pow(a._a0,Integer(7),a._module);
       a1 =  a1.Pow(a._a1,Integer(7),a._module);
        a2.Pow(a._a2,Integer(7),a._module);
        a3.Pow(a._a3,Integer(7),a._module);
        a4.Pow(a._a4,Integer(7),a._module);
        a5.Pow(a._a5,Integer(7),a._module);
        a6.Pow(a._a6,Integer(7),a._module);
        a7.Pow(a._a7,Integer(7),a._module);
        a8.Pow(a._a8,Integer(7),a._module);
        a9.Pow(a._a9,Integer(7),a._module);
        a10.Pow(a._a10,Integer(7),a._module);
        a11.Pow(a._a11,Integer(7),a._module);
        a12.Pow(a._a12,Integer(7),a._module);

//        c6 = a._a6*a._a6*a._a6*a._a6*a._a6*a._a6*a._a6;
//        s = c6.ToString();

        a13.Pow(a._a13,Integer(7),a._module);
/*        s = a0.ToString();
        s = a1.ToString();
        s = a2.ToString();
        s = a3.ToString();
        s = a4.ToString();
        s = a5.ToString();
        s = a6.ToString();
        s = a7.ToString();
        s = a8.ToString();
        s = a9.ToString();
        s = a10.ToString();
        s = a11.ToString();
        s = a12.ToString();
        s = a13.ToString();
 */

        c0 = a0 + c0_1.ModMul(a2,three,a._module) + c0_2.ModMul(a4,two,a._module) + c0_3.ModMul(a6,six,a._module) + c0_4.ModMul(a8,four,a._module)+ c0_5.ModMul(a10,five,a._module) + a12;
        c1 = c1_1.ModMul(a2,six,a._module) + a4 + a6 + c1_4.ModMul(a8,four,a._module)+ a10 + c1_2.ModMul(a12,five,a._module);
        c2 = a4 + c2_1.ModMul(a6,two,a._module) + c2_2.ModMul(a8,five,a._module) + c2_3.ModMul(a10,four,a._module) + c2_4.ModMul(a12,four,a._module);
        c3 = c3_1.ModMul(a6,six,a._module) + c3_2.ModMul(a8,two,a._module) + a10 + c3_4.ModMul(a12,six,a._module);
        c4 = a8 + a10 + c4_1.ModMul(a12,two,a._module);
        c5 = c5_1.ModMul(a10,six,a._module) + c5_2.ModMul(a12,three,a._module);
        c6 = a12 ;
        c7 = a1 + c7_1.ModMul(a3,three,a._module) + c7_2.ModMul(a5,two,a._module) + c7_3.ModMul(a7,six,a._module) + c7_4.ModMul(a9,four,a._module)+ c7_5.ModMul(a11,five,a._module) + a13;
        c8 = c8_1.ModMul(a3,six,a._module) + a5 + a7 + c8_4.ModMul(a9,four,a._module)+ a11 + c8_2.ModMul(a13,five,a._module);
        c9 = a5 + c9_1.ModMul(a7,two,a._module) + c9_2.ModMul(a9,five,a._module) + c9_3.ModMul(a11,four,a._module) + c9_4.ModMul(a13,four,a._module);
        c10 = c10_1.ModMul(a7,six,a._module) + c10_2.ModMul(a9,two,a._module) + a11 + c10_4.ModMul(a13,six,a._module);
        c11 = a9 + a11 + c11_1.ModMul(a13,two,a._module);
        c12 = c12_1.ModMul(a11,six,a._module) + c12_2.ModMul(a13,three,a._module);
        c13 = a13;
        _a0.Mod(c0,a._module);
        _a1.Mod(c1,a._module);
        _a2.Mod(c2,a._module);
        _a3.Mod(c3,a._module);
        _a4.Mod(c4,a._module);
        _a5.Mod(c5,a._module);
        _a6.Mod(c6,a._module);
        _a7.Mod(c7,a._module);
        _a8.Mod(c8,a._module);
        _a9.Mod(c9,a._module);
        _a10.Mod(c10,a._module);
        _a11.Mod(c11,a._module);
        _a12.Mod(c12,a._module);
        _a13.Mod(c13,a._module);

 /*       s = _a0.ToString();
        s = _a1.ToString();
        s = _a2.ToString();
        s = _a3.ToString();
        s = _a4.ToString();
        s = _a5.ToString();
        s = _a6.ToString();
        s = _a7.ToString();
        s = _a8.ToString();
        s = _a9.ToString();
        s = _a10.ToString();
        s = _a11.ToString();
        s = _a12.ToString();
        s = _a13.ToString();
  */
		return *this;
	}
  //возведение в степень
  PolynomGF7_m14& PolynomGF7_m14::Pow(PolynomGF7_m14 &a, const Integer &n)
  {
    if(a.isZero() == true)
    {
        *this = a;
        return *this;
    }
    if(n.isNegative())
        throw std::domain_error("„исло n - отрицательное результат не определен");
//    if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
    //int len = atoi(n.ToString().c_str());
   std::vector<Integer> m;
    int num_bit;
    uint m1 = a._module.getNumberBits() - 1;
      std::string  o_st,e_st;
      e_st.append("1");
      o_st.append("0");
        for(unsigned int i = 0  ; i < m1-1; i++)
        {
            o_st.append("0");

            e_st.append("0");
        }

    num_bit = sevendiv(&m,n);
    std::string s = m[0].ToString();
    _modPolynom = a._modPolynom;
    _module = a._module;
    PolynomGF7_m14 c,result(e_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,a._module.ToString());
   // result.setOne();
    result.setModule(_module);
    result.setModPolynom(_modPolynom);
    //    std::string m1 = a._module.ToString();
    PolynomGF7_m14 one(e_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,o_st,a._module.ToString());
    PolynomGF7_m14 a_2,a_3,a_4,a_5,a_6,c_1,c_2,c_3,c_4,c_5,c_6,c_7;
    a_2.Mul(a,a);
    a_3.Mul(a_2,a);
    a_4.Mul(a_3,a);
    a_5.Mul(a_4,a);
    a_6.Mul(a_5,a);
 //   one.setOne();
 //   one.setModule(_module);

    Integer copy_n(n);
    //result.setOne();
    for(int i=1;i<=num_bit+1;i++)
    {
        c_1.SevenFast(result);
        result = c_1;
        if(m[num_bit + 1 - i] == 1)
            result *= a;
        else if(m[num_bit + 1 - i] == 2)
        {
            //a = a*a;
            result *= a_2;
        }
        else if(m[num_bit + 1 - i] == 3)
        {
            //a = a*a*a;
            result *= a_3;
        }
        else if(m[num_bit + 1 - i] == 4)
        {
            //a = a*a*a*a;
            result *= a_4;
        }
        else if(m[num_bit + 1 - i] == 5)
        {
            //a = a*a*a*a*a;
            result *= a_5;
        }
        else if(m[num_bit + 1 - i] == 6)
        {
            //a = a*a*a*a*a*a;
            result *= a_6;
        }
        else
            result *= one;
    }
    *this = result;
    //    s = result.ToString();

    m.clear();
    return *this;
  }
     const PolynomGF7& PolynomGF7_m14::getByIndex(int index) const
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
        if(index == 7)
        {
            return _a7;
        }
        else if(index == 8)
        {
            return _a8;
        }
        else if(index == 9)
        {
            return _a9;
        }
        else if(index == 10)
        {
            return _a10;
        }
        else if(index == 11)
        {
            return _a11;
        }
        else if(index == 12)
        {
            return _a12;
        }
        if(index == 13)
        {
            return _a13;
        }

    }
    void PolynomGF7_m14::setByIndex(const PolynomGF7 & a, int index)
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
        else if(index == 6)
        {
            _a6 = a;
        }
        else if(index == 7)
        {
            _a7 = a;
        }
        else if(index == 8)
        {
            _a8 = a;
        }
        else if(index == 9)
        {
            _a9 = a;
        }
        else if(index == 10)
        {
            _a10 = a;
        }
        else if(index == 11)
        {
            _a11 = a;
        }
        else if(index == 12)
        {
            _a12 = a;
        }
        else if(index == 13)
        {
            _a13 = a;
        }
    }
   //определение степени многочлена
    int PolynomGF7_m14::deg() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero()&& _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero()&& _a11.isZero() && _a12.isZero() && _a13.isZero())
            return -1;
        else if(!_a13.isZero())
            return 13;
        else if(!_a12.isZero())
            return 12;
        else if(!_a11.isZero())
            return 11;
        else if(!_a10.isZero())
            return 10;
        else if(!_a9.isZero())
            return 9;
        else if(!_a8.isZero())
            return 8;
        else if(!_a7.isZero())
            return 7;
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
	PolynomGF7_m14& PolynomGF7_m14::Inverse(PolynomGF7 &module)
	{
		return Inverse(*this, module);
	}
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_m_4, Inverse)
	PolynomGF7_m14& PolynomGF7_m14::Inverse(PolynomGF7_m14 &polynom, PolynomGF7 &module)
	{
//        if(polynom.getModule().isIrreducible() == false || module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
/*       PolynomGF7_mY_3 d2("000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString()),d1("100","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString()),w1;
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
        *this = result;  */
        return *this;
    }
   // извлечение квадратного корн€
   PolynomGF7_m14& PolynomGF7_m14::LegendreSymbol( PolynomGF7_m14 &a, PolynomGF7 &module)
   {
//        if(a.getModPolynom().isIrreducible() == false ||module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
       PolynomGF7_m14 result,minus_one;//("6","0","0","0","0","0","0","0","0","0","0","0","0","");
       PolynomGF7 six("6");
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
 /*       s = _a0.ToString();
        s = _a1.ToString();
        s = _a2.ToString();
        s = _a3.ToString();
        s = _a4.ToString();
        s = _a5.ToString();
        s = _a6.ToString();
        s = _a7.ToString();
        s = _a8.ToString();
        s = _a9.ToString();
        s = _a10.ToString();
        s = _a11.ToString();
        s = _a12.ToString();
        s = _a13.ToString();
*/
        return *this;
   }
   PolynomGF7_m14& PolynomGF7_m14::Sqrt(PolynomGF7_m14 &x,PolynomGF7_m14 &a, PolynomGF7 &module,Integer &ss,Integer &T)
   {
//        if(x.getModule().isIrreducible() == false ||module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

        bool rez;
        Integer s;
        s = ss;
         std::string st,o_st,m_str,e_str;
        PolynomGF7_m14 test;
        PolynomGF7_m14 zero;//("0","0","0","0","0","0","0","0","0","0","0","0","0",module.ToString());
        zero.setZero();
        zero.setModule(module);
        test.LegendreSymbol(x,module);
/*        st = test._a0.ToString();
        st = test._a1.ToString();
        st = test._a2.ToString();
        st = test._a3.ToString();
        st = test._a4.ToString();
        st = test._a5.ToString();
        st = test._a6.ToString();
        st = test._a7.ToString();
        st = test._a8.ToString();
        st = test._a9.ToString();
        st = test._a10.ToString();
        st = test._a11.ToString();
        st = test._a12.ToString();
        st = test._a13.ToString();
 */
        uint m = module.getNumberBits() - 1;
        o_st.append("1");
        m_str.append("6");
        e_str.append("0");
        for(unsigned int i = 0  ; i < m-1; i++)
        {
            o_st.append("0");
            m_str.append("0");
            e_str.append("0");
        }
        if(test._a0.ToString() != o_st)
        {
                *this = zero;
                return *this;
        }
        PolynomGF7_m14 result,b,e1,e2,e3,e4,e5;
        result.setOne();
        PolynomGF7_m14 minus_one(m_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,module.ToString());
        PolynomGF7 six("6");
//         minus_one.setByIndex(six,0);
//         minus_one._module = module;
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
/*        st = a._a0.ToString();
        st = a._a1.ToString();
        st = a._a2.ToString();
        st = a._a3.ToString();
        st = a._a4.ToString();
        st = a._a5.ToString();
        st = a._a6.ToString();
        st = a._a7.ToString();
        st = a._a8.ToString();
        st = a._a9.ToString();
        st = a._a10.ToString();
        st = a._a11.ToString();
        st = a._a12.ToString();
        st = a._a13.ToString();
        */
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
/*        st = b._a0.ToString();
        st = b._a1.ToString();
        st = b._a2.ToString();
        st = b._a3.ToString();
        st = b._a4.ToString();
        st = b._a5.ToString();
        st = b._a6.ToString();
        st = b._a7.ToString();
        st = b._a8.ToString();
        st = b._a9.ToString();
        st = b._a10.ToString();
        st = b._a11.ToString();
        st = b._a12.ToString();
        st = b._a13.ToString();
 */
        Integer two("2"), c("1"),e("1");
        Integer k("0"),t0("0");
        for(Integer i = 0; i < T; i++)
        {
                e1.Pow(a,t0);
                e2 = e1*b;
                e3 = e2*e2;
                e4 = e3*x;
                two.Pow(2,T-k - 1);
  //              st = two.ToString();
                e5.Pow(e4,two);
  /*      st = e5._a0.ToString();
        st = e5._a1.ToString();
        st = e5._a2.ToString();
        st = e5._a3.ToString();
        st = e5._a4.ToString();
        st = e5._a5.ToString();
        st = e5._a6.ToString();
        st = e5._a7.ToString();
        st = e5._a8.ToString();
        st = e5._a9.ToString();
        st = e5._a10.ToString();
        st = e5._a11.ToString();
        st = e5._a12.ToString();
        st = e5._a13.ToString();


        st = minus_one._a0.ToString();
        st = minus_one._a1.ToString();
        st = minus_one._a2.ToString();
        st = minus_one._a3.ToString();
        st = minus_one._a4.ToString();
        st = minus_one._a5.ToString();
        st = minus_one._a6.ToString();
        st = minus_one._a7.ToString();
        st = minus_one._a8.ToString();
        st = minus_one._a9.ToString();
        st = minus_one._a10.ToString();
        st = minus_one._a11.ToString();
        st = minus_one._a12.ToString();
        st = minus_one._a13.ToString();
    */
                if(e5 == minus_one)
                        c = 1;
                if(e5._a0.ToString() == o_st)
                        c = 0;
                t = t + e.Pow(2,k)*c;
                t0 = t;
                k = k + 1;
        }
        *this = a.Pow(a,t)*b*x;
     /*   st = _a0.ToString();
        st = _a1.ToString();
        st = _a2.ToString();
        st = _a3.ToString();
        st = _a4.ToString();
        st = _a5.ToString();
        st = _a6.ToString();
        st = _a7.ToString();
        st = _a8.ToString();
        st = _a9.ToString();
        st = _a10.ToString();
        st = _a11.ToString();
        st = _a12.ToString();
        st = _a13.ToString();
      */
      return *this;
   }
   //тест образующего элемента, определение пор€дка элемента
   Integer& PolynomGF7_m14::elementOrder(PolynomGF7 &groupModule, PolynomGF7_m14 &polynom,std::vector<DecompositionMember> vector,const Integer &ord )
{
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    PolynomGF7 *m  = new PolynomGF7(groupModule);
    PolynomGF7_m14 *a = new PolynomGF7_m14(polynom);
    Integer t =  ord;
    for(it = vector.begin(); it != vector.end();it++)
   {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.ModPow(p,e, t);
      std::string s = ex.ToString();
      t = t/(ex);
      PolynomGF7_m14 a1;
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
     throw new Exception("¬ведите разложение пор€дка группы.");
}
bool PolynomGF7_m14::isGenerator(PolynomGF7 &groupModule, PolynomGF7_m14 &polynom,std::vector<DecompositionMember> vector, Integer &ord)
{
    if(vector.size() >= 1)
    {   AAL::Integer m(ord-1);
       // AAL::Integer b(polynom.ToString(),Bin);
      Integer t = elementOrder(groupModule, polynom,vector,ord-1);
       if(t == m)
        return true;
    }
  else
   throw new Exception("¬ведите разложение пор€дка группы.");
return false;
}
void PolynomGF7_m14::exist(PolynomGF7 &a, PolynomGF7& module)
{
    _a0 = a;
    _a1.setZero();
    _a2.setZero();
    _a3.setZero();
    _a4.setZero();
    _a5.setZero();
    _a6.setZero();
    _a7.setZero();
    _a8.setZero();
    _a9.setZero();
    _a10.setZero();
    _a11.setZero();
    _a12.setZero();
    _a13.setZero();


    _module = module;
}
PolynomGF7_m14& PolynomGF7_m14::Generate(PolynomGF7& module)
{
        _a0 = _a0.Generate(module);
        _a1 = _a1.Generate(module);
        _a2 = _a2.Generate(module);
        _a3 = _a3.Generate(module);
        _a4 = _a4.Generate(module);
        _a5 = _a5.Generate(module);
        _a6 = _a6.Generate(module);
        _a7 = _a7.Generate(module);
        _a8 = _a8.Generate(module);
        _a9 = _a9.Generate(module);
        _a10 = _a10.Generate(module);
        _a11 = _a11.Generate(module);
        _a12 = _a12.Generate(module);
        _a13 = _a13.Generate(module);


        _module = module;
        return *this;
}

//-----------------------------------------------------------------------------------
PolynomGF7_m14& PolynomGF7_m14::findRo(PolynomGF7_m14 &b ,PolynomGF7 &mod)
{
   PolynomGF7_m14 s("664","451","125","333","160","204","600","444","350","524","622","242","120","525",mod.ToString()),s1,a,a_3,a1,r;
 //  PolynomGF7_m14 two("200","000","000","000","000","000",mod.ToString());
        uint m = mod.getNumberBits() - 1;
        std::string o_st,m_str,e_str,t_str;
        o_st.append("1");
        m_str.append("6");
        e_str.append("0");
        t_str.append("2");
        for(unsigned int i = 0  ; i < m-1; i++)
        {
            o_st.append("0");
            m_str.append("0");
            e_str.append("0");
            t_str.append("0");
        }
        PolynomGF7_m14 six(m_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
        PolynomGF7_m14 two(t_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());

   Integer t;
   std::string str;
   t.Pow(7,14*m);
   t = (t - 1)/(823543);
 //  str = t.ToString();
   s.setModule(mod);
   s1.setModule(mod);
   a.setModule(mod);
   r.setModule(mod);
   a_3.setModule(mod);
   a1.setModule(mod);
   b.setModule(mod);
   b.Mul(b,two);
   //str = b.ToString();

   s1.Pow(s,t);
    //str = s1.ToString();

   t = 1;
   a  = s1;
   a_3.SevenFast(a);
   //str = a_3.ToString();

   a1.Mul(a,six);
   //str = a1.ToString();

   r.Add(a_3,a1);
   //str = r.ToString();

   r.Add(r,b);
   //str = r.ToString();
    a = s1;
    //std::string st = "";
   while(r.isZero() == false)
   {
       if(t >= 823543)
       {
          int tt = 0   ;
              break;
        }
        if(t > 0)
            a.Mul(s1,a);
   //str = a.ToString();
     //   st = t.ToString();
        t = t + 1;
       //str = t.ToString();
        a_3.SevenFast(a);
   //str = a_3.ToString();

        a1.Mul(a,six);
   //str = a1.ToString();
        r.Add(a_3,a1);
   //str = r.ToString();

        r.Add(r,b);
    //str = r.ToString();

   }
   PolynomGF7_m14 *result;
   result  = new PolynomGF7_m14();
   result->setModule(mod);
//   a.Add(a,b);
   *result = a;
     // str = a.ToString();

   return  *result;
}
std::string PolynomGF7_m14::ToString() const
{
    std::string dataString = "";
    dataString.append(_a0.ToString() );
    dataString.append("," );
    dataString.append(_a1.ToString() );
    dataString.append("," );
    dataString.append(_a2.ToString() );
    dataString.append("," );
    dataString.append(_a3.ToString() );
    dataString.append("," );
    dataString.append(_a4.ToString() );
    dataString.append("," );
    dataString.append(_a5.ToString() );
    dataString.append("," );
    dataString.append(_a6.ToString() );
    dataString.append("," );
    dataString.append(_a7.ToString() );
    dataString.append("," );
    dataString.append(_a8.ToString() );
    dataString.append("," );
    dataString.append(_a9.ToString() );
    dataString.append("," );
    dataString.append(_a10.ToString() );
    dataString.append("," );
    dataString.append(_a11.ToString() );
    dataString.append("," );
    dataString.append(_a12.ToString() );
    dataString.append("," );
    dataString.append(_a13.ToString() );
    return dataString;
}
  PolynomGF7_m14& PolynomGF7_m14::DLK(std::vector<PolynomGF7> vector_x,std::vector<PolynomGF7> vector_y,std::vector<PolynomGF7> vector_al,std::vector<PolynomGF7> vector_bt,PolynomGF7_m14 &ro,PolynomGF7_m14 &si,int n,PolynomGF7_m14 &b,PolynomGF7 &mod)
  {
        PolynomGF7 c;
        uint m = mod.getNumberBits() - 1;
        std::string o_st,m_str,e_str,s,tw;
        o_st.append("1");
        m_str.append("6");
        e_str.append("0");
        tw.append("2");
        for(unsigned int i = 0  ; i < m-1; i++)
        {
            o_st.append("0");
            m_str.append("0");
            e_str.append("0");
            tw.append("0");
        }
        PolynomGF7_m14 minusro,d,one(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString()),six(m_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
         PolynomGF7_m14* f = new PolynomGF7_m14(one);

       //f = one;
        PolynomGF7_m14 two(tw,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
        minusro.Mul(ro,six);
        uint sz_x  = vector_x.size();
      std::vector<PolynomGF7_m14> X;
      std::vector<PolynomGF7_m14> Y;
      PolynomGF7 ax("1");
        for(uint  i = 0; i < sz_x;i++)
        {
       //    s =  vector_x[i].ToString();
          // vector_x[i]  =  c.Pow(vector_x[i],7,mod);
           vector_x[i]  =  c.PowSeven_29(vector_x[i],mod,b._a0,ax);
         //  s =  vector_x[i].ToString();
           PolynomGF7_m14 xp(s,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
           X.push_back(xp);
        //   s =  vector_y[i].ToString();
         //  vector_y[i]  =  c.Pow(vector_y[i],7,mod);
           vector_y[i]  =  c.PowSeven_29(vector_y[i],mod,b._a0,ax);
        //   s =  vector_y[i].ToString();
           PolynomGF7_m14 yp(s,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
           Y.push_back(yp);
        }
          std::string str;
      char m1[100];
      PolynomGF7_m14 mm(itoa((2*n-1)%7,m1,10),e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
    mm.Mul(mm,six);
    //str = mm.ToString();
    //str = b.ToString();

    d.Mul(b,mm); //d=mb
    //str = d.ToString();
                 PolynomGF7_m14 bty(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
             PolynomGF7_m14 btysi(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
             PolynomGF7_m14 alphax(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
             PolynomGF7_m14 dminusro(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
             PolynomGF7_m14 alphaxdminusro(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
             PolynomGF7_m14 alphaxdminusro4(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
             PolynomGF7_m14 minusalphaxdminusro4(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
             PolynomGF7_m14 btysiminusalphaxdminusro4(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
      uint sz_al  = vector_al.size();


    for( int t = 1; t <= n; t++)
    {

     std::vector<PolynomGF7_m14> alpha;
      std::vector<PolynomGF7_m14> beta;
             std::vector<PolynomGF7_m14> g;
       int k = 0;

        for(uint  i = 0; i < sz_al;i++)
        {
         //  s =  vector_al[i].ToString();
           //vector_al[i]  =  c.Pow(vector_al[i],49,mod);
           vector_al[i]  =  c.PowSeven_29(vector_al[i],mod,b._a0,ax);
           vector_al[i]  =  c.PowSeven_29(vector_al[i],mod,b._a0,ax);
           //s =  vector_al[i].ToString();
           PolynomGF7_m14 aip(s,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
           alpha.push_back(aip);
           //s =  vector_bt[i].ToString();
//           vector_bt[i]  =  c.Pow(vector_bt[i],49,mod);
           vector_bt[i]  =  c.PowSeven_29(vector_bt[i],mod,b._a0,ax);
           vector_bt[i]  =  c.PowSeven_29(vector_bt[i],mod,b._a0,ax);
           //s =  vector_bt[i].ToString();
           PolynomGF7_m14 bip(s,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
           beta.push_back(bip);
        }


        for(int i = 0; i < sz_al; i++)
        {
          for(int j = 0; j < sz_x; j++)
          {
             bty.Mul(beta[i],Y[j]);
          //       str = bty.ToString();

             btysi.Mul(bty,si);
            //     str = btysi.ToString();

             alphax.Add(alpha[i],X[j]);
              //   str = alphax.ToString();

             dminusro.Add(d,minusro);
                // str = dminusro.ToString();
             alphaxdminusro.Add(alphax,dminusro);
                 //str = alphaxdminusro.ToString();
             alphaxdminusro4.Pow(alphaxdminusro,Integer(4));
                 //str = alphaxdminusro4.ToString();
             minusalphaxdminusro4.Mul(alphaxdminusro4,six);
                 //str = minusalphaxdminusro4.ToString();
             btysiminusalphaxdminusro4.Add(btysi,minusalphaxdminusro4);
             //str = btysiminusalphaxdminusro4.ToString();
             g.push_back(btysiminusalphaxdminusro4);
             k++;
          }
        }
        f->SevenFast(*f);
            //str = f->ToString();
        PolynomGF7_m14 b2(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString()),pg(o_st,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,e_str,mod.ToString());
        for(uint i = 0; i < k; i++)
        {
          //str = g[i].ToString();
          pg =pg.Mul(pg,g[i]);
        }
            //    str = pg.ToString();

        f->Mul(*f,pg);
              //       str = f->ToString();

        PolynomGF7_m14 c1;
        for(uint  i = 0; i < sz_x;i++)
        {
           Y[i]  =  c1.Mul(Y[i],six);
            //str = Y[i].ToString();
        }
        b2.Mul(b,two);
            //str = b2.ToString();

        d.Add(d,b2);
            //str = d.ToString();

    }
    Integer sev(7),sv(7);
    sv.Mul(sv,n);
    //sev.Pow(sev,sv);
    PolynomGF7_m14 ff(*f);
    for(Integer k = 0; k < sv; k++)
        f->SevenFast(*f);
    //sev = sev - 1;
    //str =sev.ToString();
   // f->Pow(*f,sev);
      //              str = f->ToString();
    return *f;
  }

};



