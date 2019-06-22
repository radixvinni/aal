/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF3_mY_9.h"
#include "PolynomGF3.h"
#include "Converter.h"
#include "Algorithms.h"
#include "Matrix.h"
#include "TableManager.h"
#include <stdlib.h>
#include <math.h>
#include "DecompositionManager.h"
namespace AAL
{
 //***********************************  Конструкторы  *******************************************
	//(c) Belova, TEST(PolynomGF2_mY_7, EmptyConstructor)
	PolynomGF3_mY_9::PolynomGF3_mY_9() :
        _a0(), _a1(), _a2(), _a3(), _a4(), _a5(), _a6(),  _a7(), _a8(), _a9(), _a10(),_module(), _modPolynom("11001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, CopyConstructor)
	PolynomGF3_mY_9::PolynomGF3_mY_9(const PolynomGF3_mY_9 &polynom)
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

     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, StringConstructor)
	PolynomGF3_mY_9::PolynomGF3_mY_9(const std::string a0,
     const std::string a1, const std::string a2,
     const std::string a3, const std::string a4, const std::string a5,
     const std::string a6,const std::string a7, const std::string a8,const std::string a9, const std::string a10,const std::string module):
     _a0(a0), _a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6),  _a7(a7), _a8(a8),  _a9(a9), _a10(a10),_module(module), _modPolynom("11001")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF3_mY_9::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero())
            return true;
        return false;
    }
    bool PolynomGF3_mY_9::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero())
            return true;
        return false;
    }
    //определение степени многочлена
    int PolynomGF3_mY_9::deg() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero()  && _a9.isZero() && _a10.isZero())
            return -1;
        if(!_a10.isZero())
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
    return 0;
    }
//------------------------------------------------------------------------------

	//simple method
	PolynomGF3_mY_9& PolynomGF3_mY_9::setZero()
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

		return *this;
	}
    //simple method
	PolynomGF3_mY_9& PolynomGF3_mY_9::setOne()
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

        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, Equal)
	bool operator==(const PolynomGF3_mY_9& a, const PolynomGF3_mY_9& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3 && a._a4 == b._a4 && a._a5 == b._a5 && a._a6 == b._a6 && a._a7 == b._a7 && a._a8 == b._a8 && a._a9 == b._a9 && a._a10 == b._a10)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, operatorEqual)
	PolynomGF3_mY_9& PolynomGF3_mY_9::operator= (const PolynomGF3_mY_9& polynom)
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

        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF3_mY_9& a, const PolynomGF3_mY_9& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF3& PolynomGF3_mY_9::getA0() const
  {
    return _a0;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA1() const
  {
    return _a1;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA2() const
  {
    return _a2;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA3() const
  {
    return _a3;
  }
    const PolynomGF3& PolynomGF3_mY_9::getA4() const
  {
    return _a4;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA5() const
  {
    return _a5;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA6() const
  {
    return _a6;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA7() const
  {
    return _a7;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA8() const
  {
    return _a8;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA9() const
  {
    return _a9;
  }
  const PolynomGF3& PolynomGF3_mY_9::getA10() const
  {
    return _a10;
  }
  const PolynomGF3& PolynomGF3_mY_9::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF3& PolynomGF3_mY_9::getModule() const
  {
    return _module;
  }
//------------------------------------------------------------------------------
    void PolynomGF3_mY_9::setA0(const PolynomGF3 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF3_mY_9::setA1(const PolynomGF3 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF3_mY_9::setA2(const PolynomGF3 & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF3_mY_9::setA3(const PolynomGF3 & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF3_mY_9::setA4(const PolynomGF3 & a)
    {
        _a4 = a;
        _a4 %= _module;
    }
     void PolynomGF3_mY_9::setA5(const PolynomGF3 & a)
    {
        _a5 = a;
        _a5 %= _module;
    }
    void PolynomGF3_mY_9::setA6(const PolynomGF3 & a)
    {
        _a6 = a;
        _a6 %= _module;
    }
    void PolynomGF3_mY_9::setA7(const PolynomGF3 & a)
    {
        _a7 = a;
        _a7 %= _module;
    }
    void PolynomGF3_mY_9::setA8(const PolynomGF3 & a)
    {
        _a8 = a;
        _a8 %= _module;
    }
    void PolynomGF3_mY_9::setA9(const PolynomGF3 & a)
    {
        _a9 = a;
        _a9 %= _module;
    }
    void PolynomGF3_mY_9::setA10(const PolynomGF3 & a)
    {
        _a10 = a;
        _a10 %= _module;
    }

   void PolynomGF3_mY_9::setModule(const PolynomGF3& module)
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
    void PolynomGF3_mY_9::setModPolynom(const PolynomGF3& modPolynom)
    {
        _modPolynom = modPolynom;
        if((modPolynom.getNumberBits()-1)!=4)
            throw new Exception("модулярные многочлен порождающий расширение поля должны быть степени 4");
    }
//------------------------------------------------------------------------------
//******************************    Операция сложения    ***************************************
	//simple method
	PolynomGF3_mY_9 operator+(const PolynomGF3_mY_9 &a, const PolynomGF3_mY_9 &b)
	{
		PolynomGF3_mY_9 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF3_mY_9& PolynomGF3_mY_9::operator+=(PolynomGF3_mY_9 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF3_mY_9& PolynomGF3_mY_9::Add(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b)
	{
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module=a._module;
		_a0.Add(a._a0, b._a0);
//        std::string s = _a0.ToString();
        _a1.Add(a._a1, b._a1);
//        s = _a1.ToString();
        _a2.Add(a._a2, b._a2);
//        s = _a2.ToString();
        _a3.Add(a._a3, b._a3);
//        s = _a3.ToString();
        _a4.Add(a._a4, b._a4);
//        s = _a4.ToString();
        _a5.Add(a._a5, b._a5);
//        s = _a5.ToString();
        _a6.Add(a._a6, b._a6);
//        s = _a6.ToString();
        _a7.Add(a._a7, b._a7);
//        s = _a7.ToString();
        _a8.Add(a._a8, b._a8);
//        s = _a8.ToString();
        _a9.Add(a._a9, b._a9);
//        s = _a9.ToString();
        _a10.Add(a._a10, b._a10);
//         s = _a10.ToString();
        return *this;
	}
//******************************    Операция умножения    **************************************
 	//simple method
/*	PolynomGF2_mY_7 operator*(const PolynomGF2_m_4 &a, const PolynomGF2_m_4 &b)
	{
		PolynomGF2_mY_7 result;
        PolynomGF2_m_4 copy_a(a), copy_b(b);
 		return result.Mul(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
/*	PolynomGF2_mY_7& PolynomGF2_mY_7::operator*=(PolynomGF2_mY_7 &polynom)
	{
		return Mul(*this, polynom);
	} */
//------------------------------------------------------------------------------

	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF3_mY_9& PolynomGF3_mY_9::Mul(PolynomGF3_m_6 &a, PolynomGF3_m_6 &b)
	{
		PolynomGF3 e0,e;
        PolynomGF3 e1,e11,e12;
        PolynomGF3 e2,e21,e22,e23;
        PolynomGF3 e3,e31,e32,e33,e34;
        PolynomGF3 e4, e41,e42,e43,e44,e45;
        PolynomGF3 e5,e51,e52,e53,e54,e55,e56;
        PolynomGF3 e6,e61,e62,e63,e64,e65;
        PolynomGF3 e7,e71,e72,e73,e74;
        PolynomGF3 e8,e81,e82,e83;
        PolynomGF3 e9,e91,e92;
        PolynomGF3 e10;
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
		if(a.isZero() || b.isZero())
  			return setZero();
                        e =  a.getA0();
        e0.ModMul(e,b.getA0(), _module);
        e1 = e11.ModMul(a.getA1(),b.getA0(),_module) + e12.ModMul(a.getA0(), b.getA1(), _module);
        e2 = e21.ModMul(a.getA2(),b.getA0(),_module) + e22.ModMul(a.getA1(),b.getA1(),_module) + e23.ModMul(a.getA0(),b.getA2(),_module);
        e3 = e31.ModMul(a.getA3(),b.getA0(),_module) + e32.ModMul(a.getA2(),b.getA1(),_module) + e33.ModMul(a.getA1(),b.getA2(),_module) + e34.ModMul(a.getA0(),b.getA3(),_module);
        e4 = e41.ModMul(a.getA4(),b.getA0(),_module) + e42.ModMul(a.getA3(),b.getA1(),_module) + e43.ModMul(a.getA2(),b.getA2(),_module) + e44.ModMul(a.getA1(),b.getA3(),_module) + e45.ModMul(a.getA0(),b.getA4(),_module);
        e5 = e51.ModMul(a.getA5(),b.getA0(),_module) + e52.ModMul(a.getA4(),b.getA1(),_module) + e53.ModMul(a.getA3(),b.getA2(),_module) + e54.ModMul(a.getA2(),b.getA3(),_module) + e55.ModMul(a.getA1(),b.getA4(),_module) + e56.ModMul(a.getA0(),b.getA5(),_module);
        e6 = e61.ModMul(a.getA5(),b.getA1(),_module) + e62.ModMul(a.getA4(),b.getA2(),_module) + e63.ModMul(a.getA3(),b.getA3(),_module) + e64.ModMul(a.getA2(),b.getA4(),_module) + e65.ModMul(a.getA1(),b.getA5(),_module);
        e7 = e71.ModMul(a.getA5(),b.getA2(),_module) + e72.ModMul(a.getA4(),b.getA3(),_module) + e73.ModMul(a.getA3(),b.getA4(),_module) + e74.ModMul(a.getA2(),b.getA5(),_module);
        e8 = e81.ModMul(a.getA5(),b.getA3(),_module) + e82.ModMul(a.getA4(),b.getA4(),_module) + e83.ModMul(a.getA3(),b.getA5(),_module);
        e9 = e91.ModMul(a.getA5(),b.getA4(),_module) + e92.ModMul(a.getA4(), b.getA5(), _module);
        e10.ModMul(a.getA5(),b.getA5(), _module);
        _a0 = e0;
//        std::string s = _a0.ToString();
        _a1 = e1;
//        s  =  _a1.ToString();
        _a2 = e2;
//        s = _a2.ToString();
        _a3 = e3;
//        s = _a3.ToString();
        _a4 = e4;
//        s  =  _a4.ToString();
        _a5 = e5;
//        s = _a5.ToString();
        _a6 = e6;
//        s = _a6.ToString();
        _a7 = e7;
//        s = _a7.ToString();
        _a8 = e8;
//        s  =  _a8.ToString();
        _a9 = e9;
//        s = _a9.ToString();
        _a10 = e10;
//        s = _a10.ToString();

		return *this;
	}
 	PolynomGF3_mY_9& PolynomGF3_mY_9::FullMul(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b)
	{
        PolynomGF3 e0,e1,e11,e12;
        PolynomGF3 e2,e21,e22,e23;
        PolynomGF3 e3,e31,e32,e33,e34;
        PolynomGF3 e4, e41,e42,e43,e44,e45;
        PolynomGF3 e5,e51,e52,e53,e54,e55,e56;
        PolynomGF3 e6,e61,e62,e63,e64,e65,e66,e67;
        PolynomGF3 e7,e71,e72,e73,e74,e75,e76,e77,e78;
        PolynomGF3 e8,e81,e82,e83,e84,e85,e86,e87,e88,e89;
        PolynomGF3 e9,e91,e92,e93,e94,e95,e96,e97,e98,e99,e910;
        PolynomGF3 e10,e101,e102,e103,e104,e105,e106,e107,e108,e109,e1010,e1011;
        PolynomGF3 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
        PolynomGF3 b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10;

        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
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

        b0 = b.getA0();
        b1 = b.getA1();
        b2 = b.getA2();
        b3 = b.getA3();
        b4 = b.getA4();
        b5 = b.getA5();
        b6 = b.getA6();
        b7 = b.getA7();
        b8 = b.getA8();
        b9 = b.getA9();
        b10 = b.getA10();


        e0.ModMul(a0,b0, _module);
        e1 = e11.ModMul(a1,b0,_module) + e12.ModMul(a0, b1, _module);
        e2 = e21.ModMul(a2,b0,_module) + e22.ModMul(a1,b1,_module) + e23.ModMul(a0,b2,_module);
        e3 = e31.ModMul(a3,b0,_module) + e32.ModMul(a2,b1,_module) + e33.ModMul(a1,b2,_module) + e34.ModMul(a0,b3,_module);
        e5 = e51.ModMul(a5,b0,_module) + e52.ModMul(a4,b1,_module) + e53.ModMul(a3,b2,_module) + e54.ModMul(a2,b3,_module) + e55.ModMul(a1,b4,_module) + e56.ModMul(a0,b5,_module);
        e6 = e61.ModMul(a0,b6,_module) + e62.ModMul(a1,b5,_module) + e63.ModMul(a2,b4,_module) + e64.ModMul(a3,b3,_module) + e65.ModMul(a4,b2,_module) + e66.ModMul(a5,b1,_module)  + e67.ModMul(a6,b0,_module);
        e7 = e71.ModMul(a0,b7,_module) + e72.ModMul(a6,b1,_module) + e73.ModMul(a5,b2,_module) + e74.ModMul(a4,b3,_module) + e75.ModMul(a3,b4,_module) + e76.ModMul(a2,b5,_module)  + e77.ModMul(a1,b6,_module)  + e78.ModMul(a7,b0,_module);
        e8 = e81.ModMul(a0,b8,_module) + e82.ModMul(a1,b7,_module) + e83.ModMul(a2,b6,_module) + e84.ModMul(a3,b5,_module) + e85.ModMul(a4,b4,_module) + e86.ModMul(a5,b3,_module)  + e87.ModMul(a6,b2,_module)  + e88.ModMul(a7,b1,_module)  + e89.ModMul(a8,b0,_module);
        e9 = e91.ModMul(a0,b9,_module) + e92.ModMul(a8,b1,_module) + e93.ModMul(a7,b2,_module) + e94.ModMul(a6,b3,_module) + e95.ModMul(a5,b4,_module) + e96.ModMul(a4,b5,_module)  + e97.ModMul(a3,b6,_module)  + e98.ModMul(a2,b7,_module)  + e99.ModMul(a1,b8,_module)  + e910.ModMul(a9,b0,_module);
        e10 = e101.ModMul(a0,b10,_module) + e102.ModMul(a1,b9,_module) + e103.ModMul(a2,b8,_module) + e104.ModMul(a3,b7,_module) + e105.ModMul(a4,b6,_module) + e106.ModMul(a5,b5,_module)  + e107.ModMul(a6,b4,_module)  + e108.ModMul(a7,b3,_module)  + e109.ModMul(a8,b2,_module)  + e1010.ModMul(a9,b1,_module)  + e1011.ModMul(a10,b0,_module);
        e4 = e41.ModMul(a4,b0,_module) + e42.ModMul(a3,b1,_module) + e43.ModMul(a2,b2,_module) + e44.ModMul(a1,b3,_module) + e45.ModMul(a0,b4,_module);

        _a0 = e0;
//        std::string s = _a0.ToString();
        _a1 = e1;
//        s  =  _a1.ToString();
        _a2 = e2;
//        s = _a2.ToString();
        _a3 = e3;
//        s = _a3.ToString();
        _a4 = e4;
//        s  =  _a4.ToString();
        _a5 = e5;
 //       s = _a5.ToString();
        _a6 = e6;
 //       s = _a6.ToString();
        _a7 = e7;
 //       s = _a7.ToString();
        _a8 = e8;
//        s  =  _a8.ToString();
        _a9 = e9;
//        s = _a9.ToString();
        _a10 = e10;
  //      s = _a10.ToString();
		return *this;
	}

    PolynomGF3_mY_9& PolynomGF3_mY_9::MonomialMul(PolynomGF3_mY_9 &a, PolynomGF3_m_6 &b)
    {
        PolynomGF3 e0;
        PolynomGF3 e1;
        PolynomGF3 e2;
        PolynomGF3 e3;
        PolynomGF3 e4;
        PolynomGF3 e5,e6,e7,e8,e9,e10;
        if(a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a._modPolynom;
        _module = a._module;
		if(a.isZero() || b.isZero())
  			return setZero();
        e0.ModMul(a._a0,b.getA0(), _module);
        e1 = e1.ModMul(a._a1,b.getA0(),_module);
        e2 = e2.ModMul(a._a2,b.getA0(),_module);
        e3 = e3.ModMul(a._a3,b.getA0(),_module);
        e4 = e4.ModMul(a._a4,b.getA0(),_module);
        e5 = e5.ModMul(a._a5,b.getA0(),_module);
        e6.ModMul(a._a6,b.getA0(),_module);
        e7.ModMul(a._a7,b.getA0(),_module);
        e8.ModMul(a._a8,b.getA0(),_module);
        e9.ModMul(a._a9,b.getA0(),_module);
        e10.ModMul(a._a10,b.getA0(),_module);

        _a0 = e0;
  //      std::string s = _a0.ToString();
        _a1 = e1;
  //      s  =  _a1.ToString();
        _a2 = e2;
  //      s = _a2.ToString();
        _a3 = e3;
   //     s = _a3.ToString();
        _a4 = e4;
   //     s  =  _a4.ToString();
        _a5 = e5;
   //     s = _a5.ToString();
        _a6 = e6;
   //     s = _a6.ToString();
        _a7 = e7;
   //     s = _a7.ToString();
        _a8 = e8;
   //     s  =  _a8.ToString();
        _a9 = e9;
   //     s = _a9.ToString();
        _a10 = e10;
   //     s = _a10.ToString();

		return *this;
    }

    PolynomGF3_mY_9& PolynomGF3_mY_9::NormalMonomialMul(PolynomGF3_mY_9 &aa, int d)
    {
              PolynomGF3 e1;
              PolynomGF3_mY_9 result,a;
              a = aa;
     /*         std::string s = a.getA0().ToString();
                s = a.getA1().ToString();
                s = a.getA2().ToString();
                s = a.getA3().ToString();
                s = a.getA4().ToString();
                s = a.getA5().ToString();
                s = a.getA6().ToString();
                s = a.getA7().ToString();
                s = a.getA8().ToString();
                s = a.getA9().ToString();
                s = a.getA10().ToString();
      */
              if(aa.getModule().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

              if(a.deg() + d > 9)
                        throw new Exception("ошибка deg(a) + d должнобыть <= 10");
              for(int i = 0; i < d; i++)
              {
                e1 = e1.setZero();
                setByIndex(e1,i);
              }
              int j = 0;
        //     std::string ss = "";
              for(int i = d; i <= 10; i++)
              {
                e1 = a.getByIndex(j);
                if(e1.isZero())
                {
                  PolynomGF3 e2;
                  e2 = e2.setZero();
                  setByIndex(e2,i);
                }
                else
                {
          //              ss = e1.ToString();
                        setByIndex(e1,i);
                }
                j++;
              }
              _module = a._module;
              _modPolynom = a._modPolynom;
             // *this = result;
		return *this;
    }

    const PolynomGF3& PolynomGF3_mY_9::getByIndex(int index) const
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
    }

    void PolynomGF3_mY_9::setByIndex(const PolynomGF3 & a, int index)
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
    }
    PolynomGF3_mY_9& PolynomGF3_mY_9::Div(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b, PolynomGF3 &module, PolynomGF3_mY_9 *remainder)
    {
        PolynomGF3_mY_9 q,r,_a,_bb,two("2","000","000","000","000","000","000","000","000","000","000",module.ToString());
        PolynomGF3_m_6 p;
        PolynomGF3 _q,_b,_inv;
        std::string s;
        q._module = module;
        q.setZero();
        r._module = module;
        _a = a;
        _bb = b;
        int deg_a, deg_b;
        int d;
        deg_a = a.deg();
        deg_b = b.deg();
        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        if(deg_a < deg_b)
        {
           *remainder = b;
           *this = q;
           return *this;
        }
        while(deg_a >= deg_b)
        {
           _b = _bb.getByIndex(deg_b);
          // s = _b.ToString();
           _inv.InverseMod1(_b ,module);
          // s = _inv.ToString();
          // std::string s1 = _a.getByIndex(deg_a).ToString();
           _q.ModMul( _a.getByIndex(deg_a),_inv,module);
           s = _q.ToString();
            d = deg_a - deg_b;
            q.setByIndex(_q,d);
            p.exist(_q,module);
            PolynomGF3_mY_9 _c;
            _c._module = module;
            _c = MonomialMul( _bb, p);
            _c = NormalMonomialMul(_c,d);

            _a = _a + _c.FullMul(_c,two);
            r = _a;
           /* s = _a._a0.ToString();
            s  =  _a._a1.ToString();
            s = _a._a2.ToString();
            s = _a._a3.ToString();
            s  =  _a._a4.ToString();
            s = _a._a5.ToString();
            s = _a._a6.ToString();
            s = _a._a7.ToString();
            s  =  _a._a8.ToString();
            s = _a._a9.ToString();
            s = _a._a10.ToString();
            */
            deg_a = _a.deg();
        }
       /* s = r.getA0().ToString();
        s = r.getA1().ToString();
        s = r.getA2().ToString();
        s = r.getA3().ToString();
        s = r.getA4().ToString();
        s = r.getA5().ToString();
        s = r.getA6().ToString();
        s = r.getA7().ToString();
        s = r.getA8().ToString();
        s = r.getA9().ToString();
        s = r.getA10().ToString();

        s = q.getA0().ToString();
        s = q.getA1().ToString();
        s = q.getA2().ToString();
        s = q.getA3().ToString();
        s = q.getA4().ToString();
        s = q.getA5().ToString();
        s = q.getA6().ToString();
        s = q.getA7().ToString();
        s = q.getA8().ToString();
        s = q.getA9().ToString();
        s = q.getA10().ToString();

         */
        *this = q;
         *remainder = r;
         return *this;
    }

PolynomGF3_mY_9& PolynomGF3_mY_9::GCD(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b, PolynomGF3 &module)
{
    PolynomGF3_mY_9 c,r,d;
    while(!b.isZero())
    {
       d.Div(a,b,a._module,&r);
       a = b;
       b = r;
    }
    *this = a;
           /*   std::string s = a._a0.ToString();
            s  =  a._a1.ToString();
            s = a._a2.ToString();
            s = a._a3.ToString();
            s  =  a._a4.ToString();
            s = a._a5.ToString();
            s = a._a6.ToString();
            s = a._a7.ToString();
            s  =  a._a8.ToString();
            s = a._a9.ToString();
            s = a._a10.ToString();
             */
   return  *this;
}
};


