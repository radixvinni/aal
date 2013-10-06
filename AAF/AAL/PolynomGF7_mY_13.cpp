/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF7_mY_13.h"
#include "PolynomGF7.h"
#include "Converter.h"
#include "Algorithms.h"
#include "Matrix.h"
#include "TableManager.h"
#include <stdlib.h>
#include <math.h>
#include "DecompositionManager.h"
namespace AAL
{
 //***********************************   онструкторы  *******************************************
	//(c) Belova, TEST(PolynomGF2_mY_7, EmptyConstructor)
	PolynomGF7_mY_13::PolynomGF7_mY_13() :
        _a0(), _a1(), _a2(), _a3(), _a4(), _a5(), _a6(),  _a7(), _a8(), _a9(), _a10(), _a11(), _a12(),_module(), _modPolynom("11001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, CopyConstructor)
	PolynomGF7_mY_13::PolynomGF7_mY_13(const PolynomGF7_mY_13 &polynom)
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
     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, StringConstructor)
	PolynomGF7_mY_13::PolynomGF7_mY_13(const std::string a0,
     const std::string a1, const std::string a2,
     const std::string a3, const std::string a4, const std::string a5,
     const std::string a6,const std::string a7, const std::string a8,
     const std::string a9, const std::string a10,
     const std::string a11,const std::string a12,const std::string a13,
     const std::string a14, const std::string a15,
     const std::string a16, const std::string a17, const std::string a18,
     const std::string a19,const std::string a20, const std::string a21,
     const std::string a22, const std::string a23,
     const std::string a24,const std::string a25,const std::string module):
     _a0(a0,a1,module), _a1(a2,a3,module), _a2(a4,a5,module), _a3(a6,a7,module), _a4(a8,a9,module), _a5(a10,a11,module), _a6(a12,a13,module),  _a7(a14,a15,module), _a8(a16,a17,module),  _a9(a18,a19,module), _a10(a20,a21,module), _a11(a22,a23,module), _a12(a24,a25,module),_module(module), _modPolynom("46000001")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF7_mY_13::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero()  && _a11.isZero()  && _a12.isZero())
            return true;
        return false;
    }
    bool PolynomGF7_mY_13::isZero(PolynomGF7 &module) const
    {
        if(_a0.isZero(module) && _a1.isZero(module) && _a2.isZero(module) && _a3.isZero(module) && _a4.isZero(module) && _a5.isZero(module) && _a6.isZero(module) && _a7.isZero(module) && _a8.isZero(module) && _a9.isZero(module) && _a10.isZero(module)  && _a11.isZero(module)  && _a12.isZero(module))
            return true;
        return false;
    }

    bool PolynomGF7_mY_13::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero()  && _a11.isZero()  && _a12.isZero())
            return true;
        return false;
    }
    //определение степени многочлена
    int PolynomGF7_mY_13::deg() const
    {
        PolynomGF7 mod = _module;
        if(_a0.isZero(mod) && _a1.isZero(mod) && _a2.isZero(mod) && _a3.isZero(mod) && _a4.isZero(mod) && _a5.isZero(mod) && _a6.isZero(mod) && _a7.isZero(mod) && _a8.isZero(mod)  && _a9.isZero(mod) && _a10.isZero(mod)  && _a11.isZero(mod)  && _a12.isZero(mod))
            return -1;
        if(!_a12.isZero(mod))
            return 12;
        if(!_a11.isZero(mod))
            return 11;
        if(!_a10.isZero(mod))
            return 10;
        else if(!_a9.isZero(mod))
            return 9;
        else if(!_a8.isZero(mod))
            return 8;
        else if(!_a7.isZero(mod))
            return 7;
        else if(!_a6.isZero(mod))
            return 6;
        else if(!_a5.isZero(mod))
            return 5;
        else if(!_a4.isZero(mod))
            return 4;
        else if(!_a3.isZero(mod))
            return 3;
        else if(!_a2.isZero(mod))
            return 2;
        else if(!_a1.isZero(mod))
            return 1;
        else if(!_a0.isZero(mod))
            return 0;
    return 0;
    }
//------------------------------------------------------------------------------
	PolynomGF7_mY_13& PolynomGF7_mY_13::setZero(PolynomGF7 &module)
	{
        uint m = module.getNumberBits() - 1;
        std::string s;
        for(int i = 0;i < m; i++)
        {
            s.append("0");
        }
        PolynomGF7_m_2 zr(s,s,module.ToString());
        _a0 = zr;
        _a1 = zr;
        _a2 = zr;
        _a3 = zr;
        _a4 = zr;
        _a5 = zr;
        _a6 = zr;
        _a7 = zr;
        _a8 = zr;
        _a9 = zr;
        _a10 = zr;
        _a11 = zr;
        _a12 = zr;
		return *this;
	}

	//simple method
	PolynomGF7_mY_13& PolynomGF7_mY_13::setZero()
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
		return *this;
	}
    //simple method
	PolynomGF7_mY_13& PolynomGF7_mY_13::setOne()
	{
        _a0.setOne();
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

        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, Equal)
	bool operator==(const PolynomGF7_mY_13& a, const PolynomGF7_mY_13& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3 && a._a4 == b._a4 && a._a5 == b._a5 && a._a6 == b._a6 && a._a7 == b._a7 && a._a8 == b._a8 && a._a9 == b._a9 && a._a10 == b._a10 && a._a11 == b._a11 && a._a12 == b._a12)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, operatorEqual)
	PolynomGF7_mY_13& PolynomGF7_mY_13::operator= (const PolynomGF7_mY_13& polynom)
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

        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF7_mY_13& a, const PolynomGF7_mY_13& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA0() const
  {
    return _a0;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA1() const
  {
    return _a1;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA2() const
  {
    return _a2;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA3() const
  {
    return _a3;
  }
    const PolynomGF7_m_2& PolynomGF7_mY_13::getA4() const
  {
    return _a4;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA5() const
  {
    return _a5;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA6() const
  {
    return _a6;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA7() const
  {
    return _a7;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA8() const
  {
    return _a8;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA9() const
  {
    return _a9;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA10() const
  {
    return _a10;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA11() const
  {
    return _a11;
  }
  const PolynomGF7_m_2& PolynomGF7_mY_13::getA12() const
  {
    return _a12;
  }

  const PolynomGF7& PolynomGF7_mY_13::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF7& PolynomGF7_mY_13::getModule() const
  {
    return _module;
  }
//------------------------------------------------------------------------------
    void PolynomGF7_mY_13::setA0(const PolynomGF7_m_2 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF7_mY_13::setA1(const PolynomGF7_m_2 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF7_mY_13::setA2(const PolynomGF7_m_2 & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF7_mY_13::setA3(const PolynomGF7_m_2 & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF7_mY_13::setA4(const PolynomGF7_m_2 & a)
    {
        _a4 = a;
        _a4 %= _module;
    }
     void PolynomGF7_mY_13::setA5(const PolynomGF7_m_2 & a)
    {
        _a5 = a;
        _a5 %= _module;
    }
    void PolynomGF7_mY_13::setA6(const PolynomGF7_m_2 & a)
    {
        _a6 = a;
        _a6 %= _module;
    }
    void PolynomGF7_mY_13::setA7(const PolynomGF7_m_2 & a)
    {
        _a7 = a;
        _a7 %= _module;
    }
    void PolynomGF7_mY_13::setA8(const PolynomGF7_m_2 & a)
    {
        _a8 = a;
        _a8 %= _module;
    }
    void PolynomGF7_mY_13::setA9(const PolynomGF7_m_2 & a)
    {
        _a9 = a;
        _a9 %= _module;
    }
    void PolynomGF7_mY_13::setA10(const PolynomGF7_m_2 & a)
    {
        _a10 = a;
        _a10 %= _module;
    }
    void PolynomGF7_mY_13::setA11(const PolynomGF7_m_2 & a)
    {
        _a11 = a;
        _a11 %= _module;
    }
    void PolynomGF7_mY_13::setA12(const PolynomGF7_m_2 & a)
    {
        _a12 = a;
        _a12 %= _module;
    }

   void PolynomGF7_mY_13::setModule(const PolynomGF7& module)
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
        _a8%= _module;
        _a9%= _module;
        _a10%= _module;
    }
    void PolynomGF7_mY_13::setModPolynom(const PolynomGF7& modPolynom)
    {
        _modPolynom = modPolynom;
        if((modPolynom.getNumberBits()-1)!= 7)
            throw std::out_of_range("модул€рные многочлен порождающий расширение пол€ должны быть степени 7");
    }
//------------------------------------------------------------------------------
//******************************    ќпераци€ сложени€    ***************************************
	//simple method
	PolynomGF7_mY_13 operator+(const PolynomGF7_mY_13 &a, const PolynomGF7_mY_13 &b)
	{
		PolynomGF7_mY_13 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_mY_13& PolynomGF7_mY_13::operator+=(PolynomGF7_mY_13 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF7_mY_13& PolynomGF7_mY_13::Add(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b)
	{
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
     //   if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
       //                 throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module=a._module;
        _a0.Add(a._a0, b._a0);
        std::string s = _a0._a0.ToString();
        s = _a0._a1.ToString();
        _a1.Add(a._a1, b._a1);
        s = _a1._a0.ToString();
        s = _a1._a1.ToString();
        _a2.Add(a._a2, b._a2);
        s = _a2._a0.ToString();
        s = _a2._a1.ToString();
        _a3.Add(a._a3, b._a3);
        s = _a3._a0.ToString();
        s = _a3._a1.ToString();
        _a4.Add(a._a4, b._a4);
        s = _a4._a0.ToString();
        s = _a4._a1.ToString();
        _a5.Add(a._a5, b._a5);
        s = _a5._a0.ToString();
        s = _a5._a1.ToString();
        _a6.Add(a._a6, b._a6);
        s = _a6._a0.ToString();
        s = _a6._a1.ToString();
        _a7.Add(a._a7, b._a7);
        s = _a7._a0.ToString();
        s = _a7._a1.ToString();
        _a8.Add(a._a8, b._a8);
        s = _a8._a0.ToString();
        s = _a8._a1.ToString();
        _a9.Add(a._a9, b._a9);
        s = _a9._a0.ToString();
        s = _a9._a1.ToString();
        _a10.Add(a._a10, b._a10);
        s = _a10._a0.ToString();
        s = _a10._a1.ToString();
        _a11.Add(a._a10, b._a10);
        s = _a11._a0.ToString();
        s = _a11._a1.ToString();
        _a12.Add(a._a10, b._a10);
        s = _a12._a0.ToString();
        s = _a12._a1.ToString();

        return *this;
	}
//******************************    ќпераци€ умножени€    **************************************
	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF7_mY_13& PolynomGF7_mY_13::Mul(PolynomGF7_m_14 &a, PolynomGF7_m_14 &b)
	{
        PolynomGF7_m_2 e0,e;
        PolynomGF7_m_2 e1,e1_1,e1_2;
        PolynomGF7_m_2 e2,e2_1,e2_2,e2_3;
        PolynomGF7_m_2 e3,e3_1,e3_2,e3_3,e3_4;
        PolynomGF7_m_2 e4, e4_1,e4_2,e4_3,e4_4,e4_5;
        PolynomGF7_m_2 e5,e5_1,e5_2,e5_3,e5_4,e5_5,e5_6;
        PolynomGF7_m_2 e6,e6_1,e6_2,e6_3,e6_4,e6_5,e6_6,e6_7;
        PolynomGF7_m_2 e7,e7_1,e7_2,e7_3,e7_4,e7_5,e7_6;
        PolynomGF7_m_2 e8,e8_1,e8_2,e8_3,e8_4,e8_5;
        PolynomGF7_m_2 e9,e9_1,e9_2,e9_3,e9_4;
        PolynomGF7_m_2 e10,e10_1,e10_2,e10_3;
        PolynomGF7_m_2 e11,e11_1,e11_2;
        PolynomGF7_m_2 e12;

        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
		if(a.isZero() || b.isZero())
  			return setZero();
        e =  a.getA0();
        e0.Mul(e,b.getA0());
        e1 = e1_1.Mul(a.getA1(),b.getA0()) + e1_2.Mul(a.getA0(), b.getA1());
        e2 = e2_1.Mul(a.getA2(),b.getA0()) + e2_2.Mul(a.getA1(),b.getA1()) + e2_3.Mul(a.getA0(),b.getA2());
        e3 = e3_1.Mul(a.getA3(),b.getA0()) + e3_2.Mul(a.getA2(),b.getA1()) + e3_3.Mul(a.getA1(),b.getA2()) + e3_4.Mul(a.getA0(),b.getA3());
        e4 = e4_1.Mul(a.getA4(),b.getA0()) + e4_2.Mul(a.getA3(),b.getA1()) + e4_3.Mul(a.getA2(),b.getA2()) + e4_4.Mul(a.getA1(),b.getA3()) + e4_5.Mul(a.getA0(),b.getA4());
        e5 = e5_1.Mul(a.getA5(),b.getA0()) + e5_2.Mul(a.getA4(),b.getA1()) + e5_3.Mul(a.getA3(),b.getA2()) + e5_4.Mul(a.getA2(),b.getA3()) + e5_5.Mul(a.getA1(),b.getA4()) + e5_6.Mul(a.getA0(),b.getA5());
        //e6_1.Mul(a.getA6(),b.getA0()) +
        e6 =  e6_2.Mul(a.getA5(),b.getA1()) + e6_3.Mul(a.getA4(),b.getA2()) + e6_4.Mul(a.getA3(),b.getA3()) + e6_5.Mul(a.getA2(),b.getA4()) + e6_6.Mul(a.getA1(),b.getA5()) + e6_7.Mul(a.getA0(),b.getA6());
        //e7_1.Mul(a.getA6(),b.getA1()) +
        e7 = e7_2.Mul(a.getA5(),b.getA2()) + e7_3.Mul(a.getA4(),b.getA3()) + e7_4.Mul(a.getA3(),b.getA4()) + e7_5.Mul(a.getA2(),b.getA5()) + e7_6.Mul(a.getA1(),b.getA6());
        //e8_1.Mul(a.getA6(),b.getA2()) +
        e8 =  e8_2.Mul(a.getA5(),b.getA3()) + e8_3.Mul(a.getA4(),b.getA4()) + e8_4.Mul(a.getA3(),b.getA5()) + e8_5.Mul(a.getA2(),b.getA5());
        //e9_1.Mul(a.getA6(),b.getA3()) +
        e9 =  e9_2.Mul(a.getA5(), b.getA4()) + e9_3.Mul(a.getA4(), b.getA5()) + e9_4.Mul(a.getA3(), b.getA6());
        //e10_1.Mul(a.getA6(),b.getA4()) +
        e10 =  e10_2.Mul(a.getA5(),b.getA5()) + e10_3.Mul(a.getA4(),b.getA6());
        e11 = e11_1.Mul(a.getA6(),b.getA5()) + e11_2.Mul(a.getA5(),b.getA6());
        e12.Mul(a.getA6(),b.getA6());

        _a0 = e0;
        std::string s = _a0._a0.ToString();
        s = _a0._a1.ToString();
        _a1 = e1;
        s = _a1._a0.ToString();
        s = _a1._a1.ToString();
        _a2 = e2;
        s = _a2._a0.ToString();
        s = _a2._a1.ToString();
        _a3 = e3;
       s = _a3._a0.ToString();
       s = _a3._a1.ToString();
         _a4 = e4;
       s = _a4._a0.ToString();
       s = _a4._a1.ToString();
         _a5 = e5;
       s = _a5._a0.ToString();
       s = _a5._a1.ToString();
         _a6 = e6;
       s = _a6._a0.ToString();
       s = _a6._a1.ToString();
         _a7 = e7;
       s = _a7._a0.ToString();
       s = _a7._a1.ToString();
         _a8 = e8;
       s = _a8._a0.ToString();
       s = _a8._a1.ToString();
         _a9 = e9;
       s = _a9._a0.ToString();
       s = _a9._a1.ToString();
         _a10 = e10;
       s = _a10._a0.ToString();
       s = _a10._a1.ToString();
         _a11 = e11;
       s = _a11._a0.ToString();
       s = _a11._a1.ToString();
         _a12 = e12;
       s = _a12._a0.ToString();
       s = _a12._a1.ToString();

		return *this;
        }

 	PolynomGF7_mY_13& PolynomGF7_mY_13::FullMul(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b)
	{
        PolynomGF7_m_2 e0("0","0",a._module.ToString()),e1("0","0",a._module.ToString()),e11("0","0",a._module.ToString()),e12("0","0",a._module.ToString());
        PolynomGF7_m_2 e2("0","0",a._module.ToString()),e21("0","0",a._module.ToString()),e22("0","0",a._module.ToString()),e23("0","0",a._module.ToString());
        PolynomGF7_m_2 e3("0","0",a._module.ToString()),e31("0","0",a._module.ToString()),e32("0","0",a._module.ToString()),e33("0","0",a._module.ToString()),e34("0","0",a._module.ToString());
        PolynomGF7_m_2 e4("0","0",a._module.ToString()), e41("0","0",a._module.ToString()),e42("0","0",a._module.ToString()),e43("0","0",a._module.ToString()),e44("0","0",a._module.ToString()),e45("0","0",a._module.ToString());
        PolynomGF7_m_2 e5("0","0",a._module.ToString()),e51("0","0",a._module.ToString()),e52("0","0",a._module.ToString()),e53("0","0",a._module.ToString()),e54("0","0",a._module.ToString()),e55("0","0",a._module.ToString()),e56("0","0",a._module.ToString());
        PolynomGF7_m_2 e6("0","0",a._module.ToString()),e61("0","0",a._module.ToString()),e62("0","0",a._module.ToString()),e63("0","0",a._module.ToString()),e64("0","0",a._module.ToString()),e65("0","0",a._module.ToString()),e66("0","0",a._module.ToString()),e67("0","0",a._module.ToString());
        PolynomGF7_m_2 e7("0","0",a._module.ToString()),e71("0","0",a._module.ToString()),e72("0","0",a._module.ToString()),e73("0","0",a._module.ToString()),e74("0","0",a._module.ToString()),e75("0","0",a._module.ToString()),e76("0","0",a._module.ToString()),e77("0","0",a._module.ToString()),e78("0","0",a._module.ToString());
        PolynomGF7_m_2 e8("0","0",a._module.ToString()),e81("0","0",a._module.ToString()),e82("0","0",a._module.ToString()),e83("0","0",a._module.ToString()),e84("0","0",a._module.ToString()),e85("0","0",a._module.ToString()),e86("0","0",a._module.ToString()),e87("0","0",a._module.ToString()),e88("0","0",a._module.ToString()),e89("0","0",a._module.ToString());
        PolynomGF7_m_2 e9("0","0",a._module.ToString()),e91("0","0",a._module.ToString()),e92("0","0",a._module.ToString()),e93("0","0",a._module.ToString()),e94("0","0",a._module.ToString()),e95("0","0",a._module.ToString()),e96("0","0",a._module.ToString()),e97("0","0",a._module.ToString()),e98("0","0",a._module.ToString()),e99("0","0",a._module.ToString()),e910("0","0",a._module.ToString());
        PolynomGF7_m_2 e10("0","0",a._module.ToString()),e101("0","0",a._module.ToString()),e102("0","0",a._module.ToString()),e103("0","0",a._module.ToString()),e104("0","0",a._module.ToString()),e105("0","0",a._module.ToString()),e106("0","0",a._module.ToString()),e107("0","0",a._module.ToString()),e108("0","0",a._module.ToString()),e109("0","0",a._module.ToString()),e1010("0","0",a._module.ToString()),e1011("0","0",a._module.ToString());
        PolynomGF7_m_2 e_11("0","0",a._module.ToString()),e111("0","0",a._module.ToString()),e112("0","0",a._module.ToString()),e113("0","0",a._module.ToString()),e114("0","0",a._module.ToString()),e115("0","0",a._module.ToString()),e116("0","0",a._module.ToString()),e117("0","0",a._module.ToString()),e118("0","0",a._module.ToString()),e119("0","0",a._module.ToString()),e1110("0","0",a._module.ToString()),e1111("0","0",a._module.ToString()),e1112("0","0",a._module.ToString());
        PolynomGF7_m_2 e_12("0","0",a._module.ToString()),e121("0","0",a._module.ToString()),e122("0","0",a._module.ToString()),e123("0","0",a._module.ToString()),e124("0","0",a._module.ToString()),e125("0","0",a._module.ToString()),e126("0","0",a._module.ToString()),e127("0","0",a._module.ToString()),e128("0","0",a._module.ToString()),e129("0","0",a._module.ToString()),e1210("0","0",a._module.ToString()),e1211("0","0",a._module.ToString()),e1212("0","0",a._module.ToString()),e1213("0","0",a._module.ToString());
        PolynomGF7_m_2 a0("0","0",a._module.ToString()),a1("0","0",a._module.ToString()),a2("0","0",a._module.ToString()),a3("0","0",a._module.ToString()),a4("0","0",a._module.ToString()),a5("0","0",a._module.ToString()),a6("0","0",a._module.ToString()),a7("0","0",a._module.ToString()),a8("0","0",a._module.ToString()),a9("0","0",a._module.ToString()),a10("0","0",a._module.ToString()),a11("0","0",a._module.ToString()),a12("0","0",a._module.ToString());
        PolynomGF7_m_2 b0("0","0",a._module.ToString()),b1("0","0",a._module.ToString()),b2("0","0",a._module.ToString()),b3("0","0",a._module.ToString()),b4("0","0",a._module.ToString()),b5("0","0",a._module.ToString()),b6("0","0",a._module.ToString()),b7("0","0",a._module.ToString()),b8("0","0",a._module.ToString()),b9("0","0",a._module.ToString()),b10("0","0",a._module.ToString()),b11("0","0",a._module.ToString()),b12("0","0",a._module.ToString());
        std::string s;
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
//        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
		if(a.isZero() || b.isZero())
  			return setZero();
        a0 = a.getA0();
        a0._module = _module;
        s = a0._a0.ToString();
        s = a0._a1.ToString();
        a1 = a.getA1();
        a1._module = _module;
        s = a1._a0.ToString();
        s = a1._a1.ToString();
        a2 = a.getA2();
        a2._module = _module;
        s = a2._a0.ToString();
        s = a2._a1.ToString();
        a3 = a.getA3();
        a3._module = _module;
        s = a3._a0.ToString();
        s = a3._a1.ToString();
        a4 = a.getA4();
        a4._module = _module;
        s = a4._a0.ToString();
        s = a4._a1.ToString();
        a5 = a.getA5();
        a5._module = _module;
        s = a5._a0.ToString();
        s = a5._a1.ToString();
        a6 = a.getA6();
        a6._module = _module;
        s = a6._a0.ToString();
        s = a6._a1.ToString();
        a7 = a.getA7();
        a7._module = _module;
        s = a7._a0.ToString();
        s = a7._a1.ToString();
        a8 = a.getA8();
        a8._module = _module;
        s = a8._a0.ToString();
        s = a8._a1.ToString();
        a9 = a.getA9();
        a9._module = _module;
        s = a9._a0.ToString();
        s = a9._a1.ToString();
        a10 = a.getA10();
        a10._module = _module;
        s = a10._a0.ToString();
        s = a10._a1.ToString();
        a11 = a.getA11();
        a11._module = _module;
        s = a11._a0.ToString();
        s = a11._a1.ToString();
        a12 = a.getA12();
        a12._module = _module;
        s = a12._a0.ToString();
        s = a12._a1.ToString();

        b0 = b.getA0();
        s = b0._a0.ToString();
        s = b0._a1.ToString();
        b1 = b.getA1();
        s = b1._a0.ToString();
        s = b1._a1.ToString();
        b2 = b.getA2();
        s = b2._a0.ToString();
        s = b2._a1.ToString();
        b3 = b.getA3();
        s = b3._a0.ToString();
        s = b3._a1.ToString();
        b4 = b.getA4();
        s = b4._a0.ToString();
        s = b4._a1.ToString();
        b5 = b.getA5();
        s = b5._a0.ToString();
        s = b5._a1.ToString();
        b6 = b.getA6();
        s = b6._a0.ToString();
        s = b6._a1.ToString();
        b7 = b.getA7();
        s = b7._a0.ToString();
        s = b7._a1.ToString();
        b8 = b.getA8();
        s = b8._a0.ToString();
        s = b8._a1.ToString();
        b9 = b.getA9();
        s = b9._a0.ToString();
        s = b9._a1.ToString();
        b10 = b.getA10();
        s = b10._a0.ToString();
        s = b10._a1.ToString();
        b11 = b.getA11();
        s = b11._a0.ToString();
        s = b11._a1.ToString();
        b12 = b.getA12();
        s = b12._a0.ToString();
        s = b12._a1.ToString();

        e0.Mul(a0,b0);
        e1 = e11.Mul(a1,b0) + e12.Mul(a0, b1);
        e2 = e21.Mul(a2,b0) + e22.Mul(a1,b1) + e23.Mul(a0,b2);
        e3 = e31.Mul(a3,b0) + e32.Mul(a2,b1) + e33.Mul(a1,b2) + e34.Mul(a0,b3);
        e4 = e41.Mul(a4,b0) + e42.Mul(a3,b1) + e43.Mul(a2,b2) + e44.Mul(a1,b3) + e45.Mul(a0,b4);
        e5 = e51.Mul(a5,b0) + e52.Mul(a4,b1) + e53.Mul(a3,b2) + e54.Mul(a2,b3) + e55.Mul(a1,b4) + e56.Mul(a0,b5);
        e6 = e61.Mul(a0,b6) + e62.Mul(a1,b5) + e63.Mul(a2,b4) + e64.Mul(a3,b3) + e65.Mul(a4,b2) + e66.Mul(a5,b1)  + e67.Mul(a6,b0);
        e7 = e71.Mul(a0,b7) + e72.Mul(a6,b1) + e73.Mul(a5,b2) + e74.Mul(a4,b3) + e75.Mul(a3,b4) + e76.Mul(a2,b5)  + e77.Mul(a1,b6)  + e78.Mul(a7,b0);
        e8 = e81.Mul(a0,b8) + e82.Mul(a1,b7) + e83.Mul(a2,b6) + e84.Mul(a3,b5) + e85.Mul(a4,b4) + e86.Mul(a5,b3)  + e87.Mul(a6,b2)  + e88.Mul(a7,b1)  + e89.Mul(a8,b0);
        e9 = e91.Mul(a0,b9) + e92.Mul(a8,b1) + e93.Mul(a7,b2) + e94.Mul(a6,b3) + e95.Mul(a5,b4) + e96.Mul(a4,b5)  + e97.Mul(a3,b6)  + e98.Mul(a2,b7)  + e99.Mul(a1,b8)  + e910.Mul(a9,b0);
        e10 = e101.Mul(a0,b10) + e102.Mul(a1,b9) + e103.Mul(a2,b8) + e104.Mul(a3,b7) + e105.Mul(a4,b6) + e106.Mul(a5,b5)  + e107.Mul(a6,b4)  + e108.Mul(a7,b3)  + e109.Mul(a8,b2)  + e1010.Mul(a9,b1)  + e1011.Mul(a10,b0);
        e_11 = e111.Mul(a0,b11) + e112.Mul(a10,b1) + e113.Mul(a9,b2) + e114.Mul(a8,b3) + e115.Mul(a7,b4) + e116.Mul(a6,b5)  + e117.Mul(a5,b6)  + e118.Mul(a4,b7)  + e119.Mul(a3,b8)  + e1110.Mul(a2,b9)  + e1111.Mul(a1,b10) + e1112.Mul(a11,b0);
        e_12 = e121.Mul(a0,b12) + e122.Mul(a1,b11) + e123.Mul(a2,b10) + e124.Mul(a3,b9) + e125.Mul(a4,b8) + e126.Mul(a5,b7)  + e127.Mul(a6,b6)  + e128.Mul(a7,b5)  + e129.Mul(a8,b4)  + e1210.Mul(a9,b3)  + e1211.Mul(a10,b2) + e1212.Mul(a11,b1) + e1213.Mul(a12,b0);

        _a0 = e0;
        s = _a0._a0.ToString();
        s = _a0._a1.ToString();
        _a1 = e1;
        s = _a1._a0.ToString();
        s = _a1._a1.ToString();
        _a2 = e2;
        s = _a2._a0.ToString();
        s = _a2._a1.ToString();
        _a3 = e3;
        s = _a3._a0.ToString();
        s = _a3._a1.ToString();
        _a4 = e4;
        s = _a4._a0.ToString();
        s = _a4._a1.ToString();
        _a5 = e5;
        s = _a5._a0.ToString();
        s = _a5._a1.ToString();
        _a6 = e6;
        s = _a6._a0.ToString();
        s = _a6._a1.ToString();
        _a7 = e7;
        s = _a7._a0.ToString();
        s = _a7._a1.ToString();
        _a8 = e8;
        s = _a8._a0.ToString();
        s = _a8._a1.ToString();
        _a9 = e9;
        s = _a9._a0.ToString();
        s = _a9._a1.ToString();
        _a10 = e10;
        s = _a10._a0.ToString();
        s = _a10._a1.ToString();
        _a11 = e_11;
        s = _a11._a0.ToString();
        s = _a11._a1.ToString();
        _a12 = e_12;
        s = _a12._a0.ToString();
        s = _a12._a1.ToString();

		return *this;
	}

    PolynomGF7_mY_13& PolynomGF7_mY_13::MonomialMul(PolynomGF7_mY_13 &a, PolynomGF7_m_14 &b)
    {
        PolynomGF7_m_2 e0;
        PolynomGF7_m_2 e1;
        PolynomGF7_m_2 e2;
        PolynomGF7_m_2 e3;
        PolynomGF7_m_2 e4;
        PolynomGF7_m_2 e5,e6,e7,e8,e9,e10,e11,e12;
        PolynomGF7_m_2 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12;
        PolynomGF7_m_2 b0;

        if(a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
//        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a._modPolynom;
        _module = a._module;
		if(a.isZero() || b.isZero())
  			return setZero();
        a0 = a.getA0();
        a1 = a.getA1();
        a2 = a.getA2();
        a3 = a.getA3();
        a4 = a.getA4();
        a5 = a.getA5();
        a6 = a.getA6();
        a7 = a.getA7();
        a8 = a.getA8();
        a9 = a.getA9();
        a10 = a.getA10();
        a11 = a.getA11();
        a12 = a.getA12();

        b0 = b.getA0();

        e0.Mul(a0,b0);
        e1 = e1.Mul(a1,b0);
        e2 = e2.Mul(a2,b0);
        e3 = e3.Mul(a3,b0);
        e4 = e4.Mul(a4,b0);
        e5 = e5.Mul(a5,b0);
        e6.Mul(a6,b0);
        e7.Mul(a7,b0);
        e8.Mul(a8,b0);
        e9.Mul(a9,b0);
        e10.Mul(a10,b0);
        e11.Mul(a11,b0);
        e12.Mul(a12,b0);

        _a0 = e0;
        std::string s = _a0._a0.ToString();
        s = _a0._a1.ToString();
        _a1 = e1;
        s = _a1._a0.ToString();
        s = _a1._a1.ToString();
        _a2 = e2;
        s = _a2._a0.ToString();
        s = _a2._a1.ToString();
        _a3 = e3;
        s = _a3._a0.ToString();
        s = _a3._a1.ToString();
        _a4 = e4;
        s = _a4._a0.ToString();
        s = _a4._a1.ToString();
        _a5 = e5;
        s = _a5._a0.ToString();
        s = _a5._a1.ToString();
        _a6 = e6;
        s = _a6._a0.ToString();
        s = _a6._a1.ToString();
        _a7 = e7;
        s = _a7._a0.ToString();
        s = _a7._a1.ToString();
        _a8 = e8;
        s = _a8._a0.ToString();
        s = _a8._a1.ToString();
        _a9 = e9;
        s = _a9._a0.ToString();
        s = _a9._a1.ToString();
        _a10 = e10;
        s = _a10._a0.ToString();
        s = _a10._a1.ToString();
        _a11 = e11;
        s = _a11._a0.ToString();
        s = _a11._a1.ToString();
        _a12 = e12;
        s = _a12._a0.ToString();
        s = _a12._a1.ToString();
		return *this;
    }

    PolynomGF7_mY_13& PolynomGF7_mY_13::NormalMonomialMul(PolynomGF7_mY_13 &aa, int d)
    {
              PolynomGF7_m_2 e1;
              PolynomGF7_mY_13 result,a;
              PolynomGF7 module;
              std::string o_st;
              module = aa._module;

              a = aa;
              uint m = module.getNumberBits() - 1;
              //o_st =  module.ToString();
            for(int i = 0  ; i < m; i++)
            {
                o_st.append("0");
            }
 //             if(aa.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");

              if(a.deg() + d > 12)
                        throw std::out_of_range("ошибка deg(a) + d должнобыть <= 12");
              for(int i = 0; i < d; i++)
              {
                e1 = e1.setZero(module);
                //(o_st,o_st,module.ToString());
                setByIndex(e1,i);
              }
              int j = 0;
             std::string ss = "",s;
              for(int i = d; i <= 12; i++)
              {
                e1 = a.getByIndex(j);
                s = e1._a0.ToString();
                s = e1._a1.ToString();
                if(e1._a0.ToString() == o_st && e1._a1.ToString() == o_st)
                {
                  PolynomGF7_m_2 e2;
                  e2 = e2.setZero(module);
                  setByIndex(e2,i);
                }
                else
                {
                    ss = e1._a0.ToString();
                    ss = e1._a1.ToString();
                    setByIndex(e1,i);
                }
                j++;
              }
              _module = a._module;
              _modPolynom = a._modPolynom;
             // *this = result;
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
        s = _a7._a0.ToString();
        s = _a7._a1.ToString();
        s = _a8._a0.ToString();
        s = _a8._a1.ToString();
        s = _a9._a0.ToString();
        s = _a9._a1.ToString();
        s = _a10._a0.ToString();
        s = _a10._a1.ToString();
        s = _a11._a0.ToString();
        s = _a11._a1.ToString();
        s = _a12._a0.ToString();
        s = _a12._a1.ToString();

		return *this;
    }

    const PolynomGF7_m_2& PolynomGF7_mY_13::getByIndex(int index) const
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
        else if(index == 6)
        {
            return _a6;
        }
        else if(index == 7)
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

    }

    void PolynomGF7_mY_13::setByIndex(const PolynomGF7_m_2 & a, int index)
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

    }
    PolynomGF7_mY_13& PolynomGF7_mY_13::Div(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b, PolynomGF7 &module, PolynomGF7_mY_13 *remainder)
    {
        PolynomGF7_mY_13 q,r,_a,_bb,two("600","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString());
       // PolynomGF7_m_2 sx("6","0",module.ToString());
         //two.setByIndex(sx,0);
         two.setModule(module);
         two._modPolynom = a._modPolynom;
        PolynomGF7_m_14 p;
        PolynomGF7_m_2 _q,_b,_inv;//("000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString()),_b,_inv;
        std::string s;
        q._module = module;
        q.setZero(module);
        r._module = module;
        _a = a;
        _bb = b;
            s = _a._a0.getA0().ToString();
            s = _a._a0.getA1().ToString();
            s = _a._a1.getA0().ToString();
            s = _a._a1.getA1().ToString();
            s = _a._a2.getA0().ToString();
            s = _a._a2.getA1().ToString();
            s = _a._a3.getA0().ToString();
            s = _a._a3.getA1().ToString();
            s = _a._a4.getA0().ToString();
            s = _a._a4.getA1().ToString();
            s = _a._a5.getA0().ToString();
            s = _a._a5.getA1().ToString();
            s = _a._a6.getA0().ToString();
            s = _a._a6.getA1().ToString();
            s = _a._a7.getA0().ToString();
            s = _a._a7.getA1().ToString();
            s = _a._a8.getA0().ToString();
            s = _a._a8.getA1().ToString();
            s = _a._a9.getA0().ToString();
            s = _a._a9.getA1().ToString();
            s = _a._a10.getA0().ToString();
            s = _a._a10.getA1().ToString();
            s = _a._a11.getA0().ToString();
            s = _a._a11.getA1().ToString();
            s = _a._a12.getA0().ToString();
            s = _a._a12.getA1().ToString();

        int deg_a, deg_b;
        int d;
        deg_a = a.deg();
        deg_b = b.deg();
//        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

        if(deg_a < deg_b)
        {
           *remainder = b;
           *this = q;
           return *this;
        }
        while(deg_a >= deg_b)
        {
           _b = _bb.getByIndex(deg_b);
           s = _b.getA0().ToString();
           s = _b.getA1().ToString();
           _inv.Pow(_b,Integer(47));
           //(_b ,module);
           s = _inv._a0.ToString();
           s = _inv._a1.ToString() ;
           std::string s1 = _a.getByIndex(deg_a).getA0().ToString();
           s1 = _a.getByIndex(deg_a).getA1().ToString();
           PolynomGF7_m_2 get;
           get = _a.getByIndex(deg_a);
           _q.Mul( get,_inv);
           s = _q.getA0().ToString();
           s = _q.getA1().ToString();
            d = deg_a - deg_b;
            q.setByIndex(_q,d);
            p.exist(_q,module);
            PolynomGF7_mY_13 _c;
            _c._module = module;
            _c._modPolynom = a._modPolynom;
            _c = MonomialMul( _bb, p);
            _c = NormalMonomialMul(_c,d);

            _a = _a + _c.FullMul(_c,two);
            r = _a;
            s = _a._a0.getA0().ToString();
            s = _a._a0.getA1().ToString();
            s = _a._a1.getA0().ToString();
            s = _a._a1.getA1().ToString();
            s = _a._a2.getA0().ToString();
            s = _a._a2.getA1().ToString();
            s = _a._a3.getA0().ToString();
            s = _a._a3.getA1().ToString();
            s = _a._a4.getA0().ToString();
            s = _a._a4.getA1().ToString();
            s = _a._a5.getA0().ToString();
            s = _a._a5.getA1().ToString();
            s = _a._a6.getA0().ToString();
            s = _a._a6.getA1().ToString();
            s = _a._a7.getA0().ToString();
            s = _a._a7.getA1().ToString();
            s = _a._a8.getA0().ToString();
            s = _a._a8.getA1().ToString();
            s = _a._a9.getA0().ToString();
            s = _a._a9.getA1().ToString();
            s = _a._a10.getA0().ToString();
            s = _a._a10.getA1().ToString();
            s = _a._a11.getA0().ToString();
            s = _a._a11.getA1().ToString();
            s = _a._a12.getA0().ToString();
            s = _a._a12.getA1().ToString();

            deg_a = _a.deg();
        }
            s = r._a0.getA0().ToString();
            s = r._a0.getA1().ToString();
            s = r._a1.getA0().ToString();
            s = r._a1.getA1().ToString();
            s = r._a2.getA0().ToString();
            s = r._a2.getA1().ToString();
            s = r._a3.getA0().ToString();
            s = r._a3.getA1().ToString();
            s = r._a4.getA0().ToString();
            s = r._a4.getA1().ToString();
            s = r._a5.getA0().ToString();
            s = r._a5.getA1().ToString();
            s = r._a6.getA0().ToString();
            s = r._a6.getA1().ToString();
            s = r._a7.getA0().ToString();
            s = r._a7.getA1().ToString();
            s = r._a8.getA0().ToString();
            s = r._a8.getA1().ToString();
            s = r._a9.getA0().ToString();
            s = r._a9.getA1().ToString();
            s = r._a10.getA0().ToString();
            s = r._a10.getA1().ToString();
            s = r._a11.getA0().ToString();
            s = r._a11.getA1().ToString();
            s = r._a12.getA0().ToString();
            s = r._a12.getA1().ToString();

            s = q._a0.getA0().ToString();
            s = q._a0.getA1().ToString();
            s = q._a1.getA0().ToString();
            s = q._a1.getA1().ToString();
            s = q._a2.getA0().ToString();
            s = q._a2.getA1().ToString();
            s = q._a3.getA0().ToString();
            s = q._a3.getA1().ToString();
            s = q._a4.getA0().ToString();
            s = q._a4.getA1().ToString();
            s = q._a5.getA0().ToString();
            s = q._a5.getA1().ToString();
            s = q._a6.getA0().ToString();
            s = q._a6.getA1().ToString();
            s = q._a7.getA0().ToString();
            s = q._a7.getA1().ToString();
            s = q._a8.getA0().ToString();
            s = q._a8.getA1().ToString();
            s = q._a9.getA0().ToString();
            s = q._a9.getA1().ToString();
            s = q._a10.getA0().ToString();
            s = q._a10.getA1().ToString();
            s = q._a11.getA0().ToString();
            s = q._a11.getA1().ToString();
            s = q._a12.getA0().ToString();
            s = q._a12.getA1().ToString();


        *this = q;
         *remainder = r;
         return *this;
    }

PolynomGF7_mY_13& PolynomGF7_mY_13::GCD(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b, PolynomGF7 &module)
{
    PolynomGF7_mY_13 c,r,d;
    while(!b.isZero(module))
    {
       d.Div(a,b,a._module,&r);
       a = b;
       b = r;
    }
    *this = a;
              std::string             s = a._a0.getA0().ToString();
            s = a._a0.getA1().ToString();
            s = a._a1.getA0().ToString();
            s = a._a1.getA1().ToString();
            s = a._a2.getA0().ToString();
            s = a._a2.getA1().ToString();
            s = a._a3.getA0().ToString();
            s = a._a3.getA1().ToString();
            s = a._a4.getA0().ToString();
            s = a._a4.getA1().ToString();
            s = a._a5.getA0().ToString();
            s = a._a5.getA1().ToString();
            s = a._a6.getA0().ToString();
            s = a._a6.getA1().ToString();
            s = a._a7.getA0().ToString();
            s = a._a7.getA1().ToString();
            s = a._a8.getA0().ToString();
            s = a._a8.getA1().ToString();
            s = a._a9.getA0().ToString();
            s = a._a9.getA1().ToString();
            s = a._a10.getA0().ToString();
            s = a._a10.getA1().ToString();
            s = a._a11.getA0().ToString();
            s = a._a11.getA1().ToString();
            s = a._a12.getA0().ToString();
            s = a._a12.getA1().ToString();


   return  *this;
}

};


