/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF7_mY_26.h"
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
 //***********************************  Конструкторы  *******************************************
	//(c) Belova, TEST(PolynomGF2_mY_7, EmptyConstructor)
	PolynomGF7_mY_26::PolynomGF7_mY_26() :
        _a0(), _a1(), _a2(), _a3(), _a4(), _a5(), _a6(),  _a7(), _a8(), _a9(), _a10(), _a11(), _a12(), _a13(), _a14(), _a15(), _a16(), _a17(), _a18(), _a19(),  _a20(), _a21(), _a22(), _a23(), _a24(), _a25(),_module(), _modPolynom("410000000000001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, CopyConstructor)
	PolynomGF7_mY_26::PolynomGF7_mY_26(const PolynomGF7_mY_26 &polynom)
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
     _a0 = polynom._a13;
     _a1 = polynom._a14;
     _a2 = polynom._a15;
     _a3 = polynom._a16;
     _a4 = polynom._a17;
     _a5 = polynom._a18;
     _a6 = polynom._a19;
     _a7 = polynom._a20;
     _a8 = polynom._a21;
     _a9 = polynom._a22;
     _a10 = polynom._a23;
     _a11 = polynom._a24;
     _a12 = polynom._a25;

     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, StringConstructor)
	PolynomGF7_mY_26::PolynomGF7_mY_26(const std::string a0,
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
     _a0(a0),_a1(a1), _a2(a2),_a3(a3), _a4(a4),_a5(a5), _a6(a6),_a7(a7), _a8(a8),_a9(a9), _a10(a10),_a11(a11), _a12(a12),_a13(a13),  _a14(a14),_a15(a15), _a16(a16),_a17(a17),  _a18(a18),_a19(a19), _a20(a20),_a21(a21), _a22(a22),_a23(a23), _a24(a24),_a25(a25),_module(module), _modPolynom("46000001")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF7_mY_26::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero()  && _a11.isZero()  && _a12.isZero() && _a13.isZero() && _a14.isZero() && _a15.isZero() && _a16.isZero() && _a17.isZero() && _a18.isZero() && _a19.isZero() && _a20.isZero() && _a21.isZero() && _a22.isZero() && _a23.isZero()  && _a24.isZero()  && _a25.isZero())
            return true;
        return false;
    }
    bool PolynomGF7_mY_26::isZero(PolynomGF7 &module) const
    {
        if(_a0.isZero(module) && _a1.isZero(module) && _a2.isZero(module) && _a3.isZero(module) && _a4.isZero(module) && _a5.isZero(module) && _a6.isZero(module) && _a7.isZero(module) && _a8.isZero(module) && _a9.isZero(module) && _a10.isZero(module)  && _a11.isZero(module)  && _a12.isZero(module) && _a13.isZero(module) && _a14.isZero(module) && _a15.isZero(module) && _a16.isZero(module) && _a17.isZero(module) && _a18.isZero(module) && _a19.isZero(module) && _a20.isZero(module) && _a21.isZero(module) && _a22.isZero(module) && _a23.isZero(module)  && _a24.isZero(module)  && _a25.isZero(module))
            return true;
        return false;
    }

    bool PolynomGF7_mY_26::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero() && _a7.isZero() && _a8.isZero() && _a9.isZero() && _a10.isZero()  && _a11.isZero()  && _a12.isZero() && _a13.isZero() && _a14.isZero() && _a15.isZero() && _a16.isZero() && _a17.isZero() && _a18.isZero() && _a19.isZero() && _a20.isZero() && _a21.isZero() && _a22.isZero() && _a23.isZero()  && _a24.isZero()  && _a25.isZero())
            return true;
        return false;
    }
    //определение степени многочлена
    int PolynomGF7_mY_26::deg() const
    {
        PolynomGF7 mod = _module;
        if(_a0.isZero(mod) && _a1.isZero(mod) && _a2.isZero(mod) && _a3.isZero(mod) && _a4.isZero(mod) && _a5.isZero(mod) && _a6.isZero(mod) && _a7.isZero(mod) && _a8.isZero(mod)  && _a9.isZero(mod) && _a10.isZero(mod)  && _a11.isZero(mod)  && _a12.isZero(mod) && _a13.isZero(mod) && _a14.isZero(mod) && _a15.isZero(mod) && _a16.isZero(mod) && _a17.isZero(mod) && _a18.isZero(mod) && _a19.isZero(mod) && _a20.isZero(mod) && _a21.isZero(mod) && _a22.isZero(mod) && _a23.isZero(mod)  && _a24.isZero(mod)  && _a25.isZero(mod))
            return -1;
        if(!_a12.isZero(mod))
            return 25;
        if(!_a11.isZero(mod))
            return 24;
        if(!_a10.isZero(mod))
            return 23;
        else if(!_a9.isZero(mod))
            return 22;
        else if(!_a8.isZero(mod))
            return 21;
        else if(!_a7.isZero(mod))
            return 20;
        else if(!_a6.isZero(mod))
            return 19;
        else if(!_a5.isZero(mod))
            return 18;
        else if(!_a4.isZero(mod))
            return 17;
        else if(!_a3.isZero(mod))
            return 16;
        else if(!_a2.isZero(mod))
            return 15;
        else if(!_a1.isZero(mod))
            return 14;
        else if(!_a0.isZero(mod))
            return 13;
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
	PolynomGF7_mY_26& PolynomGF7_mY_26::setZero(PolynomGF7 &module)
	{
        uint m = module.getNumberBits() - 1;
        std::string s;
        for(uint i = 0;i < m; i++)
        {
            s.append("0");
        }
        PolynomGF7 zr(s);
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
        _a13 = zr;
        _a14 = zr;
        _a15 = zr;
        _a16 = zr;
        _a17 = zr;
        _a18 = zr;
        _a19 = zr;
        _a20 = zr;
        _a21 = zr;
        _a22 = zr;
        _a23 = zr;
        _a24 = zr;
        _a25 = zr;

		return *this;
	}

	//simple method
	PolynomGF7_mY_26& PolynomGF7_mY_26::setZero()
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
        _a14.setZero();
        _a15.setZero();
        _a16.setZero();
        _a17.setZero();
        _a18.setZero();
        _a19.setZero();
        _a20.setZero();
        _a21.setZero();
        _a22.setZero();
        _a23.setZero();
        _a24.setZero();
        _a25.setZero();

		return *this;
	}
    //simple method
	PolynomGF7_mY_26& PolynomGF7_mY_26::setOne()
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
        _a13.setZero();
        _a14.setZero();
        _a15.setZero();
        _a16.setZero();
        _a17.setZero();
        _a18.setZero();
        _a19.setZero();
        _a20.setZero();
        _a21.setZero();
        _a22.setZero();
        _a23.setZero();
        _a24.setZero();
        _a25.setZero();

        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, Equal)
	bool operator==(const PolynomGF7_mY_26& a, const PolynomGF7_mY_26& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3 && a._a4 == b._a4 && a._a5 == b._a5 && a._a6 == b._a6 && a._a7 == b._a7 && a._a8 == b._a8 && a._a9 == b._a9 && a._a10 == b._a10 && a._a11 == b._a11 && a._a12 == b._a12 && a._a13 == b._a13 && a._a14 == b._a14 && a._a15 == b._a15 && a._a16 == b._a16 && a._a17 == b._a17 && a._a18 == b._a18 && a._a19 == b._a19 && a._a20 == b._a20 && a._a21 == b._a21 && a._a22 == b._a22 && a._a23 == b._a23 && a._a24 == b._a24 && a._a25 == b._a25)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, operatorEqual)
	PolynomGF7_mY_26& PolynomGF7_mY_26::operator= (const PolynomGF7_mY_26& polynom)
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
        _a14 = polynom._a14;
        _a15 = polynom._a15;
        _a16 = polynom._a16;
        _a17 = polynom._a17;
        _a18 = polynom._a18;
        _a19 = polynom._a19;
        _a20 = polynom._a20;
        _a21 = polynom._a21;
        _a22 = polynom._a22;
        _a23 = polynom._a23;
        _a24 = polynom._a24;
        _a25 = polynom._a25;

        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF7_mY_26& a, const PolynomGF7_mY_26& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF7& PolynomGF7_mY_26::getA0() const
  {
    return _a0;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA1() const
  {
    return _a1;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA2() const
  {
    return _a2;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA3() const
  {
    return _a3;
  }
    const PolynomGF7& PolynomGF7_mY_26::getA4() const
  {
    return _a4;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA5() const
  {
    return _a5;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA6() const
  {
    return _a6;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA7() const
  {
    return _a7;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA8() const
  {
    return _a8;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA9() const
  {
    return _a9;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA10() const
  {
    return _a10;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA11() const
  {
    return _a11;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA12() const
  {
    return _a12;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA13() const
  {
    return _a13;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA14() const
  {
    return _a14;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA15() const
  {
    return _a15;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA16() const
  {
    return _a16;
  }
    const PolynomGF7& PolynomGF7_mY_26::getA17() const
  {
    return _a17;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA18() const
  {
    return _a18;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA19() const
  {
    return _a19;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA20() const
  {
    return _a20;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA21() const
  {
    return _a21;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA22() const
  {
    return _a22;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA23() const
  {
    return _a23;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA24() const
  {
    return _a24;
  }
  const PolynomGF7& PolynomGF7_mY_26::getA25() const
  {
    return _a25;
  }

  const PolynomGF7& PolynomGF7_mY_26::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF7& PolynomGF7_mY_26::getModule() const
  {
    return _module;
  }
//------------------------------------------------------------------------------
    void PolynomGF7_mY_26::setA0(const PolynomGF7 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF7_mY_26::setA1(const PolynomGF7 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF7_mY_26::setA2(const PolynomGF7 & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF7_mY_26::setA3(const PolynomGF7 & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF7_mY_26::setA4(const PolynomGF7 & a)
    {
        _a4 = a;
        _a4 %= _module;
    }
     void PolynomGF7_mY_26::setA5(const PolynomGF7 & a)
    {
        _a5 = a;
        _a5 %= _module;
    }
    void PolynomGF7_mY_26::setA6(const PolynomGF7 & a)
    {
        _a6 = a;
        _a6 %= _module;
    }
    void PolynomGF7_mY_26::setA7(const PolynomGF7 & a)
    {
        _a7 = a;
        _a7 %= _module;
    }
    void PolynomGF7_mY_26::setA8(const PolynomGF7 & a)
    {
        _a8 = a;
        _a8 %= _module;
    }
    void PolynomGF7_mY_26::setA9(const PolynomGF7 & a)
    {
        _a9 = a;
        _a9 %= _module;
    }
    void PolynomGF7_mY_26::setA10(const PolynomGF7 & a)
    {
        _a10 = a;
        _a10 %= _module;
    }
    void PolynomGF7_mY_26::setA11(const PolynomGF7 & a)
    {
        _a11 = a;
        _a11 %= _module;
    }
    void PolynomGF7_mY_26::setA12(const PolynomGF7 & a)
    {
        _a12 = a;
        _a12 %= _module;
    }
    void PolynomGF7_mY_26::setA13(const PolynomGF7 & a)
    {
        _a13 = a;
        _a13 %= _module;
    }
    void PolynomGF7_mY_26::setA14(const PolynomGF7 & a)
    {
        _a14 = a;
        _a14 %= _module;
    }
    void PolynomGF7_mY_26::setA15(const PolynomGF7 & a)
    {
        _a15 = a;
        _a15 %= _module;
    }
    void PolynomGF7_mY_26::setA16(const PolynomGF7 & a)
    {
        _a16 = a;
        _a16 %= _module;
    }
    void PolynomGF7_mY_26::setA17(const PolynomGF7 & a)
    {
        _a17 = a;
        _a17 %= _module;
    }
     void PolynomGF7_mY_26::setA18(const PolynomGF7 & a)
    {
        _a18 = a;
        _a18 %= _module;
    }
    void PolynomGF7_mY_26::setA19(const PolynomGF7 & a)
    {
        _a19 = a;
        _a19 %= _module;
    }
    void PolynomGF7_mY_26::setA20(const PolynomGF7 & a)
    {
        _a20 = a;
        _a20 %= _module;
    }
    void PolynomGF7_mY_26::setA21(const PolynomGF7 & a)
    {
        _a21 = a;
        _a21 %= _module;
    }
    void PolynomGF7_mY_26::setA22(const PolynomGF7 & a)
    {
        _a22 = a;
        _a22 %= _module;
    }
    void PolynomGF7_mY_26::setA23(const PolynomGF7 & a)
    {
        _a23 = a;
        _a23 %= _module;
    }
    void PolynomGF7_mY_26::setA24(const PolynomGF7 & a)
    {
        _a24 = a;
        _a24 %= _module;
    }
    void PolynomGF7_mY_26::setA25(const PolynomGF7 & a)
    {
        _a25 = a;
        _a25 %= _module;
    }

   void PolynomGF7_mY_26::setModule(const PolynomGF7& module)
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
    void PolynomGF7_mY_26::setModPolynom(const PolynomGF7& modPolynom)
    {
        _modPolynom = modPolynom;
        if((modPolynom.getNumberBits()-1)!= 7)
            throw new Exception("модулярные многочлен порождающий расширение поля должны быть степени 7");
    }
//------------------------------------------------------------------------------
//******************************    Операция сложения    ***************************************
	//simple method
	PolynomGF7_mY_26 operator+(const PolynomGF7_mY_26 &a, const PolynomGF7_mY_26 &b)
	{
		PolynomGF7_mY_26 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_mY_26& PolynomGF7_mY_26::operator+=(PolynomGF7_mY_26 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF7_mY_26& PolynomGF7_mY_26::Add(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b)
	{
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
     //   if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
       //                 throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module=a._module;
        _a0.Add(a._a0, b._a0);
        std::string s = _a0.ToString();
        _a1.Add(a._a1, b._a1);
        s = _a1.ToString();
        _a2.Add(a._a2, b._a2);
        s = _a2.ToString();
        _a3.Add(a._a3, b._a3);
        s = _a3.ToString();
        _a4.Add(a._a4, b._a4);
        s = _a4.ToString();
        _a5.Add(a._a5, b._a5);
        s = _a5.ToString();
        _a6.Add(a._a6, b._a6);
        s = _a6.ToString();
        _a7.Add(a._a7, b._a7);
        s = _a7.ToString();
        _a8.Add(a._a8, b._a8);
        s = _a8.ToString();
        _a9.Add(a._a9, b._a9);
        s = _a9.ToString();
        _a10.Add(a._a10, b._a10);
        s = _a10.ToString();
        _a11.Add(a._a10, b._a10);
        s = _a11.ToString();
        _a12.Add(a._a10, b._a10);
        s = _a12.ToString();
        _a13.Add(a._a13, b._a13);
        s = _a13.ToString();
        _a14.Add(a._a14, b._a14);
        s = _a14.ToString();
        _a15.Add(a._a15, b._a15);
        s = _a15.ToString();
        _a16.Add(a._a16, b._a16);
        s = _a16.ToString();
        _a17.Add(a._a17, b._a17);
        s = _a17.ToString();
        _a18.Add(a._a18, b._a18);
        s = _a18.ToString();
        _a19.Add(a._a19, b._a19);
        s = _a19.ToString();
        _a20.Add(a._a20, b._a20);
        s = _a20.ToString();
        _a21.Add(a._a21, b._a21);
        s = _a21.ToString();
        _a22.Add(a._a22, b._a22);
        s = _a22.ToString();
        _a23.Add(a._a23, b._a23);
        s = _a23.ToString();
        _a24.Add(a._a24, b._a24);
        s = _a24.ToString();
        _a25.Add(a._a25, b._a25);
        s = _a25.ToString();

        return *this;
	}
//******************************    Операция умножения    **************************************
	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF7_mY_26& PolynomGF7_mY_26::Mul(PolynomGF7_m14 &a, PolynomGF7_m14 &b)
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
        PolynomGF7 four("4"),c("0");
        PolynomGF7 six("6"),minus2b("0"),three("3");
        minus2b.Mul(six,four);
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module = a._module;

		if(a.isZero() || b.isZero())
  			return setZero();
         e0.ModMul(a._a0,b._a0,_module);
         e1_1.ModMul(a._a0,b._a1,_module);
         e1_2.ModMul(a._a1,b._a0,_module);
         e1 = e1_1 + e1_2;
         e2 = e2_1.ModMul(a._a0,b._a2,_module) + e2_2.ModMul(a._a1,b._a1,_module) + e2_3.ModMul(a._a2,b._a0,_module);
         e3 = e3_1.ModMul(a._a0,b._a3,_module) + e3_2.ModMul(a._a1,b._a2,_module) + e3_3.ModMul(a._a2,b._a1,_module)+ e3_4.ModMul(a._a3,b._a0,_module);
         e4 = e4_1.ModMul(a._a0,b._a4,_module) + e4_2.ModMul(a._a1,b._a3,_module) + e4_3.ModMul(a._a2,b._a2,_module)+ e4_4.ModMul(a._a3,b._a1,_module)+ e4_5.ModMul(a._a4,b._a0,_module);
         e5 = e5_1.ModMul(a._a0,b._a5,_module) + e5_2.ModMul(a._a1,b._a4,_module) + e5_3.ModMul(a._a2,b._a3,_module)+ e5_4.ModMul(a._a3,b._a2,_module)+ e5_5.ModMul(a._a4,b._a1,_module)+ e5_6.ModMul(a._a5,b._a0,_module);
         e6 = e6_1.ModMul(a._a0,b._a6,_module) + e6_2.ModMul(a._a1,b._a5,_module) + e6_3.ModMul(a._a2,b._a4,_module)+ e6_4.ModMul(a._a3,b._a3,_module)+ e6_5.ModMul(a._a4,b._a2,_module)+ e6_6.ModMul(a._a5,b._a1,_module)+ e6_7.ModMul(a._a6,b._a0,_module);
         e7 = e7_1.ModMul(a._a0,b._a7,_module) + e7_2.ModMul(a._a1,b._a6,_module) + e7_3.ModMul(a._a2,b._a5,_module)+ e7_4.ModMul(a._a3,b._a4,_module)+ e7_5.ModMul(a._a4,b._a3,_module)+ e7_6.ModMul(a._a5,b._a2,_module)+ e7_7.ModMul(a._a6,b._a1,_module) + e7_8.ModMul(a._a7,b._a0,_module);
         e8 = e8_1.ModMul(a._a0,b._a8,_module) + e8_2.ModMul(a._a1,b._a7,_module) + e8_3.ModMul(a._a2,b._a6,_module)+ e8_4.ModMul(a._a3,b._a5,_module)+ e8_5.ModMul(a._a4,b._a4,_module)+ e8_6.ModMul(a._a5,b._a3,_module)+ e8_7.ModMul(a._a6,b._a2,_module)+ e8_8.ModMul(a._a7,b._a1,_module)+ e8_9.ModMul(a._a8,b._a0,_module);
         e9 = e9_1.ModMul(a._a0,b._a9,_module) + e9_2.ModMul(a._a1,b._a8,_module) + e9_3.ModMul(a._a2,b._a7,_module)+ e9_4.ModMul(a._a3,b._a6,_module)+ e9_5.ModMul(a._a4,b._a5,_module)+ e9_6.ModMul(a._a5,b._a4,_module)+ e9_7.ModMul(a._a6,b._a3,_module)+ e9_8.ModMul(a._a7,b._a2,_module)+ e9_9.ModMul(a._a8,b._a1,_module)+ e9_10.ModMul(a._a9,b._a0,_module);
         e10 = e10_1.ModMul(a._a0,b._a10,_module) + e10_2.ModMul(a._a1,b._a9,_module) + e10_3.ModMul(a._a2,b._a8,_module)+ e10_4.ModMul(a._a3,b._a7,_module)+ e10_5.ModMul(a._a4,b._a6,_module)+ e10_6.ModMul(a._a5,b._a5,_module)+ e10_7.ModMul(a._a6,b._a4,_module)+ e10_8.ModMul(a._a7,b._a3,_module)+ e10_9.ModMul(a._a8,b._a2,_module)+ e10_10.ModMul(a._a9,b._a1,_module)+ e10_11.ModMul(a._a10,b._a0,_module);
         e11 = e11_1.ModMul(a._a0,b._a11,_module) + e11_2.ModMul(a._a1,b._a10,_module) + e11_3.ModMul(a._a2,b._a9,_module) + e11_4.ModMul(a._a3,b._a8,_module) + e11_5.ModMul(a._a4,b._a7,_module) + e11_6.ModMul(a._a5,b._a6,_module) + e11_7.ModMul(a._a6,b._a5,_module) + e11_8.ModMul(a._a7,b._a4,_module) + e11_9.ModMul(a._a8,b._a3,_module) + e11_10.ModMul(a._a9,b._a2,_module) + e11_11.ModMul(a._a10,b._a1,_module) + e11_12.ModMul(a._a11,b._a0,_module);
         e12 = e12_1.ModMul(a._a0,b._a12,_module) + e12_2.ModMul(a._a1,b._a11,_module) + e12_3.ModMul(a._a2,b._a10,_module) + e12_4.ModMul(a._a3,b._a9,_module) + e12_5.ModMul(a._a4,b._a8,_module) + e12_6.ModMul(a._a5,b._a7,_module) + e12_7.ModMul(a._a6,b._a6,_module) + e12_8.ModMul(a._a7,b._a5,_module) + e12_9.ModMul(a._a8,b._a4,_module) + e12_10.ModMul(a._a9,b._a3,_module) + e12_11.ModMul(a._a10,b._a2,_module) + e12_12.ModMul(a._a11,b._a1,_module)+ e12_13.ModMul(a._a12,b._a0,_module);
         e13 = e13_1.ModMul(a._a0,b._a13,_module) + e13_2.ModMul(a._a1,b._a12,_module) + e13_3.ModMul(a._a2,b._a11,_module) + e13_4.ModMul(a._a3,b._a10,_module) + e13_5.ModMul(a._a4,b._a9,_module) + e13_6.ModMul(a._a5,b._a8,_module) + e13_7.ModMul(a._a6,b._a7,_module) + e13_8.ModMul(a._a7,b._a6,_module) + e13_9.ModMul(a._a8,b._a5,_module) + e13_10.ModMul(a._a9,b._a4,_module) + e13_11.ModMul(a._a10,b._a3,_module) + e13_12.ModMul(a._a11,b._a2,_module)+ e13_13.ModMul(a._a12,b._a1,_module)+ e13_14.ModMul(a._a12,b._a0,_module);
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

        _a0 = e0;
        std::string s = _a0.ToString();
        _a1 = e1;
        s = _a1.ToString();
        _a2 = e2;
        s = _a2.ToString();
        _a3 = e3;
       s = _a3.ToString();
         _a4 = e4;
       s = _a4.ToString();
         _a5 = e5;
       s = _a5.ToString();
         _a6 = e6;
       s = _a6.ToString();
         _a7 = e7;
       s = _a7.ToString();
         _a8 = e8;
       s = _a8.ToString();
         _a9 = e9;
       s = _a9.ToString();
         _a10 = e10;
       s = _a10.ToString();
         _a11 = e11;
       s = _a11.ToString();
         _a12 = e12;
       s = _a12.ToString();
        _a13 = e13;
       s = _a13.ToString();
        _a14 = e14;
        s = _a14.ToString();
        _a15 = e15;
        s = _a15.ToString();
        _a16 = e16;
       s = _a16.ToString();
         _a17 = e17;
       s = _a17.ToString();
         _a18 = e18;
       s = _a18.ToString();
         _a19 = e19;
       s = _a19.ToString();
         _a20 = e20;
       s = _a20.ToString();
         _a21 = e21;
       s = _a21.ToString();
         _a22 = e22;
       s = _a22.ToString();
         _a23 = e23;
       s = _a23.ToString();
         _a24 = e24;
       s = _a24.ToString();
         _a25 = e25;
       s = _a25.ToString();

		return *this;
        }

 	PolynomGF7_mY_26& PolynomGF7_mY_26::FullMul(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b)
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
        PolynomGF7 e14,e14_1,e14_2,e14_3,e14_4,e14_5,e14_6,e14_7,e14_8,e14_9,e14_10,e14_11,e14_12,e14_13,e14_14,e14_15;
        PolynomGF7 e15,e15_1,e15_2,e15_3,e15_4,e15_5,e15_6,e15_7,e15_8,e15_9,e15_10,e15_11,e15_12,e15_13,e15_14,e15_15,e15_16;
        PolynomGF7 e16,e16_1,e16_2,e16_3,e16_4,e16_5,e16_6,e16_7,e16_8,e16_9,e16_10,e16_11,e16_12,e16_13,e16_14,e16_15,e16_16,e16_17;
        PolynomGF7 e17,e17_1,e17_2,e17_3,e17_4,e17_5,e17_6,e17_7,e17_8,e17_9,e17_10,e17_11,e17_12,e17_13,e17_14,e17_15,e17_16,e17_17,e17_18;
        PolynomGF7 e18,e18_1,e18_2,e18_3,e18_4,e18_5,e18_6,e18_7,e18_8,e18_9,e18_10,e18_11,e18_12,e18_13,e18_14,e18_15,e18_16,e18_17,e18_18,e18_19;
        PolynomGF7 e19,e19_1,e19_2,e19_3,e19_4,e19_5,e19_6,e19_7,e19_8,e19_9,e19_10,e19_11,e19_12,e19_13,e19_14,e19_15,e19_16,e19_17,e19_18,e19_19,e19_20;
        PolynomGF7 e20,e20_1,e20_2,e20_3,e20_4,e20_5,e20_6,e20_7,e20_8,e20_9,e20_10,e20_11,e20_12,e20_13,e20_14,e20_15,e20_16,e20_17,e20_18,e20_19,e20_20,e20_21;
        PolynomGF7 e21,e21_1,e21_2,e21_3,e21_4,e21_5,e21_6,e21_7,e21_8,e21_9,e21_10,e21_11,e21_12,e21_13,e21_14,e21_15,e21_16,e21_17,e21_18,e21_19,e21_20,e21_21,e21_22;
        PolynomGF7 e22,e22_1,e22_2,e22_3,e22_4,e22_5,e22_6,e22_7,e22_8,e22_9,e22_10,e22_11,e22_12,e22_13,e22_14,e22_15,e22_16,e22_17,e22_18,e22_19,e22_20,e22_21,e22_22,e22_23;
        PolynomGF7 e23,e23_1,e23_2,e23_3,e23_4,e23_5,e23_6,e23_7,e23_8,e23_9,e23_10,e23_11,e23_12,e23_13,e23_14,e23_15,e23_16,e23_17,e23_18,e23_19,e23_20,e23_21,e23_22,e23_23,e23_24;
        PolynomGF7 e24,e24_1,e24_2,e24_3,e24_4,e24_5,e24_6,e24_7,e24_8,e24_9,e24_10,e24_11,e24_12,e24_13,e24_14,e24_15,e24_16,e24_17,e24_18,e24_19,e24_20,e24_21,e24_22,e24_23,e24_24,e24_25;
        PolynomGF7 e25,e25_1,e25_2,e25_3,e25_4,e25_5,e25_6,e25_7,e25_8,e25_9,e25_10,e25_11,e25_12,e25_13,e25_14,e25_15,e25_16,e25_17,e25_18,e25_19,e25_20,e25_21,e25_22,e25_23,e25_24,e25_25,e25_26;
        PolynomGF7 e26;
        PolynomGF7 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25;
        PolynomGF7 b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19,b20,b21,b22,b23,b24,b25;        std::string s;
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
//        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
		if(a.isZero() || b.isZero())
  			return setZero();
        a0 = a.getA0();
        s = a0.ToString();
        a1 = a.getA1();
        s = a1.ToString();
        a2 = a.getA2();
        s = a2.ToString();
        a3 = a.getA3();
        s = a3.ToString();
        a4 = a.getA4();
        s = a4.ToString();
        a5 = a.getA5();
        s = a5.ToString();
        a6 = a.getA6();
        s = a6.ToString();
        a7 = a.getA7();
        s = a7.ToString();
        a8 = a.getA8();
        s = a8.ToString();
        a9 = a.getA9();
        s = a9.ToString();
        a10 = a.getA10();
        s = a10.ToString();
        a11 = a.getA11();
        s = a11.ToString();
        a12 = a.getA12();
        s = a12.ToString();
        a13 = a.getA13();
        s = a13.ToString();
        a14 = a.getA14();
        s = a14.ToString();
        a15 = a.getA15();
        s = a15.ToString();
        a16 = a.getA16();
        s = a16.ToString();
        a17 = a.getA17();
        s = a17.ToString();
        a18 = a.getA18();
        s = a18.ToString();
        a19 = a.getA19();
        s = a19.ToString();
        a20 = a.getA20();
        s = a20.ToString();
        a21 = a.getA21();
        s = a21.ToString();
        a22 = a.getA22();
        s = a23.ToString();
        a23 = a.getA23();
        s = a23.ToString();
        a24 = a.getA24();
        s = a25.ToString();
        a25 = a.getA25();
        s = a25.ToString();


        b0 = b.getA0();
        s = b0.ToString();
        b1 = b.getA1();
        s = b1.ToString();
        b2 = b.getA2();
        s = b2.ToString();
        b3 = b.getA3();
        s = b3.ToString();
        b4 = b.getA4();
        s = b4.ToString();
        b5 = b.getA5();
        s = b5.ToString();
        b6 = b.getA6();
        s = b6.ToString();
        b7 = b.getA7();
        s = b7.ToString();
        b8 = b.getA8();
        s = b8.ToString();
        b9 = b.getA9();
        s = b9.ToString();
        b10 = b.getA10();
        s = b10.ToString();
        b11 = b.getA11();
        s = b11.ToString();
        b12 = b.getA12();
        s = b12.ToString();
        b13 = b.getA13();
        s = b13.ToString();
        b14 = b.getA14();
        s = b14.ToString();
        b15 = b.getA15();
        s = b15.ToString();
        b16 = b.getA16();
        s = b16.ToString();
        b17 = b.getA17();
        s = b17.ToString();
        b18 = b.getA18();
        s = b18.ToString();
        b19 = b.getA19();
        s = b19.ToString();
        b20 = b.getA20();
        s = b20.ToString();
        b21 = b.getA21();
        s = b21.ToString();
        b22 = b.getA22();
        s = b23.ToString();
        b23 = b.getA23();
        s = b23.ToString();
        b24 = b.getA24();
        s = b25.ToString();
        b25 = b.getA25();
        s = b25.ToString();

        e0.Mul(a0,b0);
        e1 = e1_1.Mul(a1,b0) + e1_2.Mul(a0, b1);
        e2 = e2_1.Mul(a2,b0) + e2_2.Mul(a1,b1) + e2_3.Mul(a0,b2);
        e3 = e3_1.Mul(a3,b0) + e3_2.Mul(a2,b1) + e3_3.Mul(a1,b2) + e3_4.Mul(a0,b3);
        e4 = e4_1.Mul(a4,b0) + e4_2.Mul(a3,b1) + e4_3.Mul(a2,b2) + e4_4.Mul(a1,b3) + e4_5.Mul(a0,b4);
        e5 = e5_1.Mul(a5,b0) + e5_2.Mul(a4,b1) + e5_3.Mul(a3,b2) + e5_4.Mul(a2,b3) + e5_5.Mul(a1,b4) + e5_6.Mul(a0,b5);
        e6 = e6_1.Mul(a6,b0) + e6_2.Mul(a5,b1) + e6_3.Mul(a4,b2) + e6_4.Mul(a3,b3) + e6_5.Mul(a2,b4) + e6_6.Mul(a1,b5)  + e6_7.Mul(a0,b6);
        e7 = e7_1.Mul(a7,b0) + e7_2.Mul(a6,b1) + e7_3.Mul(a5,b2) + e7_4.Mul(a4,b3) + e7_5.Mul(a3,b4) + e7_6.Mul(a2,b5)  + e7_7.Mul(a1,b6)  + e7_8.Mul(a0,b7);
        e8 = e8_1.Mul(a8,b0) + e8_2.Mul(a7,b1) + e8_3.Mul(a6,b2) + e8_4.Mul(a5,b3) + e8_5.Mul(a4,b4) + e8_6.Mul(a3,b3)  + e8_7.Mul(a2,b6)  + e8_8.Mul(a1,b7)  + e8_9.Mul(a0,b8);
        e9 = e9_1.Mul(a9,b0) + e9_2.Mul(a8,b1) + e9_3.Mul(a7,b2) + e9_4.Mul(a6,b3) + e9_5.Mul(a5,b4) + e9_6.Mul(a4,b5)  + e9_7.Mul(a3,b6)  + e9_8.Mul(a2,b7)  + e9_9.Mul(a1,b8)  + e9_10.Mul(a0,b9);
        e10 = e10_1.Mul(a10,b0) + e10_2.Mul(a9,b1) + e10_3.Mul(a8,b2) + e10_4.Mul(a7,b3) + e10_5.Mul(a6,b4) + e10_6.Mul(a5,b5)  + e10_7.Mul(a4,b6)  + e10_8.Mul(a3,b7)  + e10_9.Mul(a2,b8)  + e10_10.Mul(a1,b9)  + e10_11.Mul(a0,b10);
        e11 = e11_1.Mul(a11,b0) + e11_2.Mul(a10,b1) + e11_3.Mul(a9,b2) + e11_4.Mul(a8,b3) + e11_5.Mul(a7,b4) + e11_6.Mul(a6,b5)  + e11_7.Mul(a5,b6)  + e11_8.Mul(a4,b7)  + e11_9.Mul(a3,b8)  + e11_10.Mul(a2,b9)  + e11_11.Mul(a1,b10) + e11_12.Mul(a0,b11);
        e12 = e12_1.Mul(a12,b0) + e12_2.Mul(a11,b1) + e12_3.Mul(a10,b2) + e12_4.Mul(a9,b3) + e12_5.Mul(a8,b4) + e12_6.Mul(a7,b5)  + e12_7.Mul(a6,b6)  + e12_8.Mul(a5,b7)  + e12_9.Mul(a4,b8)  + e12_10.Mul(a3,b9)  + e12_11.Mul(a2,b10) + e12_12.Mul(a1,b11) + e12_13.Mul(a0,b12);
        e13 = e13_1.Mul(a13,b0) + e13_2.Mul(a12,b1) + e13_3.Mul(a11,b2) + e13_4.Mul(a10,b3) + e13_5.Mul(a9,b4) + e13_6.Mul(a8,b5)  + e13_7.Mul(a7,b6)  + e13_8.Mul(a6,b7)  + e13_9.Mul(a5,b8)  + e13_10.Mul(a4,b9)  + e13_11.Mul(a3,b10) + e13_12.Mul(a2,b11) + e13_13.Mul(a1,b12)+ e13_14.Mul(a0,b13);
        e14 = e14_1.Mul(a0,b14) + e14_2.Mul(a1,b13) + e14_3.Mul(a2,b12) + e14_4.Mul(a3,b11) + e14_5.Mul(a4,b10) + e14_6.Mul(a5,b9)  + e14_7.Mul(a6,b8)  + e14_8.Mul(a7,b7)  + e14_9.Mul(a8,b6)  + e14_10.Mul(a9,b5)  + e14_11.Mul(a10,b4) + e14_12.Mul(a11,b3) + e14_13.Mul(a12,b2)+ e14_14.Mul(a13,b1)+ e14_15.Mul(a14,b0);
        e15 = e15_1.Mul(a0,b15) + e15_2.Mul(a14,b1) + e15_3.Mul(a13,b2) + e15_4.Mul(a12,b3) + e15_5.Mul(a11,b4) + e15_6.Mul(a10,b5)  + e15_7.Mul(a9,b6)  + e15_8.Mul(a8,b7)  + e15_9.Mul(a7,b8)  + e15_10.Mul(a6,b9)  + e15_11.Mul(a5,b10) + e15_12.Mul(a4,b11) + e15_13.Mul(a3,b12)+ e15_14.Mul(a2,b13)+ e15_15.Mul(a1,b14)+ e15_16.Mul(a15,b0);
        e16 = e16_1.Mul(a0,b16) + e16_2.Mul(a1,b15) + e16_3.Mul(a2,b14) + e16_4.Mul(a3,b13) + e16_5.Mul(a4,b12) + e16_6.Mul(a5,b11)  + e16_7.Mul(a6,b10)  + e16_8.Mul(a7,b9)  + e16_9.Mul(a8,b8)  + e16_10.Mul(a9,b7)  + e16_11.Mul(a10,b6) + e16_12.Mul(a11,b5) + e16_13.Mul(a12,b4)+ e16_14.Mul(a13,b3)+ e16_15.Mul(a14,b2)+ e16_16.Mul(a15,b1)+ e16_17.Mul(a0,b16);
        e17 = e17_1.Mul(a0,b17) + e17_2.Mul(a16,b1) + e17_3.Mul(a15,b2) + e17_4.Mul(a14,b3) + e17_5.Mul(a13,b4) + e17_6.Mul(a12,b5)  + e17_7.Mul(a11,b6)  + e17_8.Mul(a10,b7)  + e17_9.Mul(a9,b8)  + e17_10.Mul(a8,b9)  + e17_11.Mul(a7,b10) + e17_12.Mul(a6,b11) + e17_13.Mul(a5,b12)+ e17_14.Mul(a4,b13)+ e17_15.Mul(a3,b14)+ e17_16.Mul(a2,b15)+ e17_17.Mul(a1,b16)+ e17_18.Mul(a17,b0);
        e18 = e18_1.Mul(a0,b18) + e18_2.Mul(a1,b17) + e18_3.Mul(a2,b16) + e18_4.Mul(a3,b15) + e18_5.Mul(a4,b14) + e18_6.Mul(a5,b13)  + e18_7.Mul(a6,b12)  + e18_8.Mul(a7,b11)  + e18_9.Mul(a8,b10)  + e18_10.Mul(a9,b9)  + e18_11.Mul(a10,b8) + e18_12.Mul(a11,b7) + e18_13.Mul(a12,b6)+ e18_14.Mul(a13,b5)+ e18_15.Mul(a14,b4)+ e18_16.Mul(a15,b3)+ e18_17.Mul(a16,b2)+ e18_18.Mul(a17,b1)+ e18_19.Mul(a0,b18);
        e19 = e19_1.Mul(a0,b19) + e19_2.Mul(a18,b1) + e19_3.Mul(a17,b2) + e19_4.Mul(a16,b3) + e19_5.Mul(a15,b4) + e19_6.Mul(a14,b5)  + e19_7.Mul(a13,b6)  + e19_8.Mul(a12,b7)  + e19_9.Mul(a11,b8)  + e19_10.Mul(a10,b9)  + e19_11.Mul(a9,b10) + e19_12.Mul(a8,b11) + e19_13.Mul(a7,b12)+ e19_14.Mul(a6,b13)+ e19_15.Mul(a5,b14)+ e19_16.Mul(a4,b15)+ e19_17.Mul(a3,b16)+ e19_18.Mul(a2,b17)+ e19_19.Mul(a1,b18)+ e19_20.Mul(a18,b0);
        e20 = e20_1.Mul(a0,b20) + e20_2.Mul(a1,b19) + e20_3.Mul(a2,b18) + e20_4.Mul(a3,b17) + e20_5.Mul(a4,b16) + e20_6.Mul(a5,b15)  + e20_7.Mul(a6,b14)  + e20_8.Mul(a7,b13)  + e20_9.Mul(a8,b12)  + e20_10.Mul(a9,b11)  + e20_11.Mul(a10,b10) + e20_12.Mul(a11,b9) + e20_13.Mul(a12,b8)+ e20_14.Mul(a13,b7)+ e20_15.Mul(a14,b6)+ e20_16.Mul(a15,b5)+ e20_17.Mul(a16,b4)+ e20_18.Mul(a17,b3)+ e20_19.Mul(a18,b2)+ e20_20.Mul(a19,b1)+ e20_21.Mul(a0,b20);
        e21= e21_1.Mul(a0,b21) + e21_2.Mul(a20,b1) + e21_3.Mul(a19,b2) + e21_4.Mul(a18,b3) + e21_5.Mul(a17,b4) + e21_6.Mul(a16,b5)  + e21_7.Mul(a15,b6)  + e21_8.Mul(a14,b7)  + e21_9.Mul(a13,b8)  + e21_10.Mul(a12,b9)  + e21_11.Mul(a11,b10) + e21_12.Mul(a10,b11) + e21_13.Mul(a9,b12)+ e21_14.Mul(a8,b13)+ e21_15.Mul(a7,b14)+ e21_16.Mul(a6,b15)+ e21_17.Mul(a5,b16)+ e21_18.Mul(a4,b17)+ e21_19.Mul(a3,b18)+ e21_20.Mul(a2,b19)+ e21_21.Mul(a1,b20)+ e21_22.Mul(a20,b0);
        e22= e22_1.Mul(a0,b22) + e22_2.Mul(a1,b21) + e22_3.Mul(a2,b20) + e22_4.Mul(a3,b19) + e22_5.Mul(a4,b18) + e22_6.Mul(a5,b17)  + e22_7.Mul(a6,b16)  + e22_8.Mul(a7,b15)  + e22_9.Mul(a8,b14)  + e22_10.Mul(a9,b13)  + e22_11.Mul(a10,b12) + e22_12.Mul(a11,b11) + e22_13.Mul(a12,b10)+ e22_14.Mul(a13,b9)+ e22_15.Mul(a14,b8)+ e22_16.Mul(a15,b7)+ e22_17.Mul(a16,b6)+ e22_18.Mul(a17,b5)+ e22_19.Mul(a18,b4)+ e22_20.Mul(a19,b3)+ e22_21.Mul(a20,b2)+ e22_22.Mul(a21,b1) + e22_23.Mul(a22,b0);
        e23= e23_1.Mul(a0,b23) + e23_2.Mul(a22,b1) + e23_3.Mul(a21,b2) + e23_4.Mul(a20,b3) + e23_5.Mul(a19,b4) + e23_6.Mul(a18,b5)  + e23_7.Mul(a17,b6)  + e23_8.Mul(a16,b7)  + e23_9.Mul(a15,b8)  + e23_10.Mul(a14,b9)  + e23_11.Mul(a13,b10) + e23_12.Mul(a12,b11) + e23_13.Mul(a11,b12)+ e23_14.Mul(a10,b13)+ e23_15.Mul(a9,b14)+ e23_16.Mul(a8,b15)+ e23_17.Mul(a7,b16)+ e23_18.Mul(a6,b17)+ e23_19.Mul(a5,b18)+ e23_20.Mul(a4,b19)+ e23_21.Mul(a3,b20)+ e23_22.Mul(a2,b21) + e23_23.Mul(a1,b22)+ e23_23.Mul(a23,b0);
        e24= e24_1.Mul(a0,b24) + e24_2.Mul(a1,b23) + e24_3.Mul(a2,b22) + e24_4.Mul(a3,b21) + e24_5.Mul(a4,b20) + e24_6.Mul(a5,b19)  + e24_7.Mul(a6,b18)  + e24_8.Mul(a7,b17)  + e24_9.Mul(a8,b16)  + e24_10.Mul(a9,b15)  + e24_11.Mul(a10,b14) + e24_12.Mul(a11,b13) + e24_13.Mul(a12,b12)+ e24_14.Mul(a13,b11)+ e24_15.Mul(a14,b10)+ e24_16.Mul(a15,b9)+ e24_17.Mul(a16,b8)+ e24_18.Mul(a17,b7)+ e24_19.Mul(a18,b6)+ e24_20.Mul(a19,b5)+ e24_21.Mul(a20,b4)+ e24_22.Mul(a21,b3) + e24_24.Mul(a22,b2)+ e24_24.Mul(a23,b1)+ e24_25.Mul(a0,b24);
        e25= e25_1.Mul(a0,b25) + e25_2.Mul(a24,b1) + e25_3.Mul(a23,b2) + e25_4.Mul(a22,b3) + e25_5.Mul(a21,b4) + e25_6.Mul(a20,b5)  + e25_7.Mul(a19,b6)  + e25_8.Mul(a18,b7)  + e25_9.Mul(a17,b8)  + e25_10.Mul(a16,b9)  + e25_11.Mul(a15,b10) + e25_12.Mul(a14,b11) + e25_13.Mul(a13,b12)+ e25_14.Mul(a12,b13)+ e25_15.Mul(a11,b14)+ e25_16.Mul(a10,b15)+ e25_17.Mul(a9,b16)+ e25_18.Mul(a8,b17)+ e25_19.Mul(a7,b18)+ e25_20.Mul(a6,b19)+ e25_21.Mul(a5,b20)+ e25_22.Mul(a4,b21) + e25_25.Mul(a3,b22)+ e25_25.Mul(a2,b23)+ e25_25.Mul(a1,b24)+ e25_26.Mul(a25,b0);

        _a0 = e0;
        s = _a0.ToString();
        _a1 = e1;
        s = _a1.ToString();
        _a2 = e2;
        s = _a2.ToString();
        _a3 = e3;
        s = _a3.ToString();
        _a4 = e4;
        s = _a4.ToString();
        _a5 = e5;
        s = _a5.ToString();
        _a6 = e6;
        s = _a6.ToString();
        _a7 = e7;
        s = _a7.ToString();
        _a8 = e8;
        s = _a8.ToString();
        _a9 = e9;
        s = _a9.ToString();
        _a10 = e10;
        s = _a10.ToString();
        _a11 = e11;
        s = _a11.ToString();
        _a12 = e12;
        s = _a12.ToString();
       _a13 = e13;
        s = _a13.ToString();
        _a14 = e14;
        s = _a14.ToString();
        _a15 = e15;
        s = _a15.ToString();
        _a16 = e16;
        s = _a16.ToString();
        _a17 = e17;
        s = _a17.ToString();
        _a18 = e18;
        s = _a18.ToString();
        _a19 = e19;
        s = _a19.ToString();
        _a20 = e20;
        s = _a20.ToString();
        _a21 = e21;
        s = _a21.ToString();
        _a22 = e22;
        s = _a22.ToString();
        _a23 = e23;
        s = _a24.ToString();
        _a24 = e24;
        s = _a24.ToString();
        _a25 = e25;
        s = _a25.ToString();

		return *this;
	}

    PolynomGF7_mY_26& PolynomGF7_mY_26::MonomialMul(PolynomGF7_mY_26 &a, PolynomGF7_m14 &b)
    {
        PolynomGF7 e0;
        PolynomGF7 e1;
        PolynomGF7 e2;
        PolynomGF7 e3;
        PolynomGF7 e4;
        PolynomGF7 e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15,e16,e17,e18,e19,e20,e21,e22,e23,e24,e25;
        PolynomGF7 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25;
        PolynomGF7 b0;

        if(a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
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
        a13 = a.getA13();
        a14 = a.getA14();
        a15 = a.getA15();
        a16 = a.getA16();
        a17 = a.getA17();
        a18 = a.getA18();
        a19 = a.getA19();
        a20 = a.getA20();
        a21 = a.getA21();
        a22 = a.getA22();
        a23 = a.getA23();
        a24 = a.getA24();
        a25 = a.getA25();

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
        e13.Mul(a13,b0);
        e14 = e14.Mul(a14,b0);
        e15 = e15.Mul(a15,b0);
        e16 = e16.Mul(a16,b0);
        e17 = e17.Mul(a17,b0);
        e18 = e18.Mul(a18,b0);
        e19.Mul(a19,b0);
        e20.Mul(a20,b0);
        e21.Mul(a21,b0);
        e22.Mul(a22,b0);
        e23.Mul(a23,b0);
        e24.Mul(a24,b0);
        e25.Mul(a25,b0);

        _a0 = e0;
        std::string s = _a0.ToString();
        _a1 = e1;
        s = _a1.ToString();
        _a2 = e2;
        s = _a2.ToString();
        _a3 = e3;
        s = _a3.ToString();
        _a4 = e4;
        s = _a4.ToString();
        _a5 = e5;
        s = _a5.ToString();
        _a6 = e6;
        s = _a6.ToString();
        _a7 = e7;
        s = _a7.ToString();
        _a8 = e8;
        s = _a8.ToString();
        _a9 = e9;
        s = _a9.ToString();
        _a10 = e10;
        s = _a10.ToString();
        _a11 = e11;
        s = _a11.ToString();
        _a12 = e12;
        s = _a12.ToString();
        _a13 = e13;
        s = _a13.ToString();
        _a14 = e14;
        s = _a14.ToString();
        _a15 = e15;
        s = _a15.ToString();
        _a16 = e16;
        s = _a16.ToString();
        _a17 = e17;
        s = _a17.ToString();
        _a18 = e18;
        s = _a19.ToString();
        _a19 = e19;
        s = _a19.ToString();
        _a20 = e20;
        s = _a20.ToString();
        _a21 = e21;
        s = _a21.ToString();
        _a22 = e22;
        s = _a22.ToString();
        _a23 = e23;
        s = _a23.ToString();
        _a24 = e24;
        s = _a24.ToString();
        _a25 = e25;
        s = _a25.ToString();

		return *this;
    }

    PolynomGF7_mY_26& PolynomGF7_mY_26::NormalMonomialMul(PolynomGF7_mY_26 &aa, int d)
    {
              PolynomGF7 e1;
              PolynomGF7_mY_26 result,a;
              PolynomGF7 module;
              std::string o_st;
              module = aa._module;

              a = aa;
              uint m = module.getNumberBits() - 1;
              //o_st =  module.ToString();
            for(uint i = 0  ; i < m; i++)
            {
                o_st.append("0");
            }
 //             if(aa.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");

              if(a.deg() + d > 25)
                        throw new Exception("ошибка deg(a) + d должнобыть <= 25");
              for(int i = 0; i < d; i++)
              {
                e1 = e1.setZero(module);
                //(o_st,o_st,module.ToString());
                setByIndex(e1,i);
              }
              int j = 0;
             std::string ss = "",s;
              for(int i = d; i <= 25; i++)
              {
                e1 = a.getByIndex(j);
                s = e1.ToString();
                if(e1.ToString() == o_st )
                {
                  PolynomGF7 e2;
                  e2 = e2.setZero(module);
                  setByIndex(e2,i);
                }
                else
                {
                    ss = e1.ToString();
                    setByIndex(e1,i);
                }
                j++;
              }
              _module = a._module;
              _modPolynom = a._modPolynom;
             // *this = result;
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
        s = _a14.ToString();
        s = _a15.ToString();
        s = _a16.ToString();
        s = _a17.ToString();
        s = _a18.ToString();
        s = _a19.ToString();
        s = _a20.ToString();
        s = _a21.ToString();
        s = _a22.ToString();
        s = _a23.ToString();
        s = _a24.ToString();
        s = _a25.ToString();

		return *this;
    }

    const PolynomGF7& PolynomGF7_mY_26::getByIndex(int index) const
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
        else if(index == 13)
        {
            return _a13;
        }
        else if(index == 14)
        {
            return _a14;
        }
        else if(index == 15)
        {
            return _a15;
        }
        else if(index == 16)
        {
            return _a16;
        }
        else if(index == 17)
        {
            return _a17;
        }
        else if(index == 18)
        {
            return _a18;
        }
        else if(index == 19)
        {
            return _a19;
        }
        else if(index == 20)
        {
            return _a20;
        }
        else if(index == 21)
        {
            return _a21;
        }
        else if(index == 22)
        {
            return _a22;
        }
        else if(index == 23)
        {
            return _a23;
        }
        else if(index == 24)
        {
            return _a24;
        }
        else if(index == 25)
        {
            return _a25;
        }

    }

    void PolynomGF7_mY_26::setByIndex(const PolynomGF7 & a, int index)
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
        else if(index == 14)
        {
            _a14 = a;
        }
        else if(index == 15)
        {
            _a15 = a;
        }
        else if(index == 16)
        {
            _a16 = a;
        }
        else if(index == 17)
        {
            _a17 = a;
        }
        else if(index == 18)
        {
            _a18 = a;
        }
        else if(index == 19)
        {
            _a19 = a;
        }
        else if(index == 20)
        {
            _a20 = a;
        }
        else if(index == 21)
        {
            _a21 = a;
        }
        else if(index == 22)
        {
            _a22 = a;
        }
        else if(index == 23)
        {
            _a23 = a;
        }
        else if(index == 24)
        {
            _a24 = a;
        }
        else if(index == 25)
        {
            _a25 = a;
        }
    }
    PolynomGF7_mY_26& PolynomGF7_mY_26::Div(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b, PolynomGF7 &module, PolynomGF7_mY_26 *remainder)
    {
        PolynomGF7_mY_26 q,r,_a,_bb,two("600","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString());
       // PolynomGF7 sx("6","0",module.ToString());
         //two.setByIndex(sx,0);
         two.setModule(module);
         two._modPolynom = a._modPolynom;
        PolynomGF7_m14 p;
        PolynomGF7 _q,_b,_inv;//("000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString()),_b,_inv;
        std::string s;
        q._module = module;
        q.setZero(module);
        r._module = module;
        _a = a;
        _bb = b;
            s = _a._a0.ToString();
            s = _a._a1.ToString();
            s = _a._a2.ToString();
            s = _a._a3.ToString();
            s = _a._a4.ToString();
            s = _a._a5.ToString();
            s = _a._a6.ToString();
            s = _a._a7.ToString();
            s = _a._a8.ToString();
            s = _a._a9.ToString();
            s = _a._a10.ToString();
            s = _a._a11.ToString();
            s = _a._a12.ToString();
            s = _a._a13.ToString();
            s = _a._a14.ToString();
            s = _a._a15.ToString();
            s = _a._a16.ToString();
            s = _a._a17.ToString();
            s = _a._a18.ToString();
            s = _a._a19.ToString();
            s = _a._a20.ToString();
            s = _a._a21.ToString();
            s = _a._a22.ToString();
            s = _a._a23.ToString();
            s = _a._a24.ToString();
            s = _a._a25.ToString();


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
           s = _b.ToString();
           _inv.Pow(_b,Integer(47),module);
           //(_b ,module);
           s = _inv.ToString();
           std::string s1 = _a.getByIndex(deg_a).ToString();
           PolynomGF7 get;
           get = _a.getByIndex(deg_a);
           _q.Mul( get,_inv);
           s = _q.ToString();
            d = deg_a - deg_b;
            q.setByIndex(_q,d);
            p.exist(_q,module);
            PolynomGF7_mY_26 _c;
            _c._module = module;
            _c._modPolynom = a._modPolynom;
            _c = MonomialMul( _bb, p);
            _c = NormalMonomialMul(_c,d);

            _a = _a + _c.FullMul(_c,two);
            r = _a;
            s = _a._a0.ToString();
            s = _a._a1.ToString();
            s = _a._a2.ToString();
            s = _a._a3.ToString();
            s = _a._a4.ToString();
            s = _a._a5.ToString();
            s = _a._a6.ToString();
            s = _a._a7.ToString();
            s = _a._a8.ToString();
            s = _a._a9.ToString();
            s = _a._a10.ToString();
            s = _a._a11.ToString();
            s = _a._a12.ToString();
            s = _a._a13.ToString();
            s = _a._a14.ToString();
            s = _a._a15.ToString();
            s = _a._a16.ToString();
            s = _a._a17.ToString();
            s = _a._a18.ToString();
            s = _a._a19.ToString();
            s = _a._a20.ToString();
            s = _a._a21.ToString();
            s = _a._a22.ToString();
            s = _a._a23.ToString();
            s = _a._a24.ToString();
            s = _a._a25.ToString();


            deg_a = _a.deg();
        }
            s = r._a0.ToString();
            s = r._a1.ToString();
            s = r._a2.ToString();
            s = r._a3.ToString();
            s = r._a4.ToString();
            s = r._a5.ToString();
            s = r._a6.ToString();
            s = r._a7.ToString();
            s = r._a8.ToString();
            s = r._a9.ToString();
            s = r._a10.ToString();
            s = r._a11.ToString();
            s = r._a12.ToString();
            s = r._a13.ToString();
            s = r._a14.ToString();
            s = r._a15.ToString();
            s = r._a16.ToString();
            s = r._a17.ToString();
            s = r._a18.ToString();
            s = r._a19.ToString();
            s = r._a20.ToString();
            s = r._a21.ToString();
            s = r._a22.ToString();
            s = r._a23.ToString();
            s = r._a24.ToString();
            s = r._a25.ToString();


            s = q._a0.ToString();
            s = q._a1.ToString();
            s = q._a2.ToString();
            s = q._a3.ToString();
            s = q._a4.ToString();
            s = q._a5.ToString();
            s = q._a6.ToString();
            s = q._a7.ToString();
            s = q._a8.ToString();
            s = q._a9.ToString();
            s = q._a10.ToString();
            s = q._a11.ToString();
            s = q._a12.ToString();
            s = q._a13.ToString();
            s = q._a14.ToString();
            s = q._a15.ToString();
            s = q._a16.ToString();
            s = q._a17.ToString();
            s = q._a18.ToString();
            s = q._a19.ToString();
            s = q._a20.ToString();
            s = q._a21.ToString();
            s = q._a22.ToString();
            s = q._a23.ToString();
            s = q._a24.ToString();
            s = q._a25.ToString();


        *this = q;
         *remainder = r;
         return *this;
    }

PolynomGF7_mY_26& PolynomGF7_mY_26::GCD(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b, PolynomGF7 &module)
{
    PolynomGF7_mY_26 c,r,d;
    while(!b.isZero(module))
    {
       d.Div(a,b,a._module,&r);
       a = b;
       b = r;
    }
    *this = a;
              std::string  s = a._a0.ToString();
            s = a._a1.ToString();
            s = a._a2.ToString();
            s = a._a3.ToString();
            s = a._a4.ToString();
            s = a._a5.ToString();
            s = a._a6.ToString();
            s = a._a7.ToString();
            s = a._a8.ToString();
            s = a._a9.ToString();
            s = a._a10.ToString();
            s = a._a11.ToString();
            s = a._a12.ToString();
            s = a._a13.ToString();
            s = a._a14.ToString();
            s = a._a15.ToString();
            s = a._a16.ToString();
            s = a._a17.ToString();
            s = a._a18.ToString();
            s = a._a19.ToString();
            s = a._a20.ToString();
            s = a._a21.ToString();
            s = a._a22.ToString();
            s = a._a23.ToString();
            s = a._a24.ToString();
            s = a._a25.ToString();



   return  *this;
}

};


