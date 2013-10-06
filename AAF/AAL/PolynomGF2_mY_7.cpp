/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF2_mY_7.h"
#include "Polynom.h"
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
	PolynomGF2_mY_7::PolynomGF2_mY_7() :
        _a0(), _a1(), _a2(), _a3(), _a4(), _a5(), _a6(), _module(), _modPolynom("11001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, CopyConstructor)
	PolynomGF2_mY_7::PolynomGF2_mY_7(const PolynomGF2_mY_7 &polynom)
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

	//(c) Belova, TEST(PolynomGF2_mY_7, StringConstructor)
	PolynomGF2_mY_7::PolynomGF2_mY_7(const std::string a0,
     const std::string a1, const std::string a2,
     const std::string a3, const std::string a4, const std::string a5,
     const std::string a6,const std::string module):
     _a0(a0), _a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _module(module), _modPolynom("11001")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF2_mY_7::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero())
            return true;
        return false;
    }
    bool PolynomGF2_mY_7::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero())
            return true;
        return false;
    }
    //определение степени многочлена
    int PolynomGF2_mY_7::deg() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero() && _a6.isZero())
            return -1;
        if(!_a6.isZero())
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
//------------------------------------------------------------------------------

	//simple method
	PolynomGF2_mY_7& PolynomGF2_mY_7::setZero()
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
	PolynomGF2_mY_7& PolynomGF2_mY_7::setOne()
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

	//(c) Belova, TEST(PolynomGF2_mY_7, Equal)
	bool operator==(const PolynomGF2_mY_7& a, const PolynomGF2_mY_7& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3 && a._a4 == b._a4 && a._a5 == b._a5 && a._a6 == b._a6)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, operatorEqual)
	PolynomGF2_mY_7& PolynomGF2_mY_7::operator= (const PolynomGF2_mY_7& polynom)
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
	bool operator!=(const PolynomGF2_mY_7& a, const PolynomGF2_mY_7& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const Polynom& PolynomGF2_mY_7::getA0() const
  {
    return _a0;
  }
  const Polynom& PolynomGF2_mY_7::getA1() const
  {
    return _a1;
  }
  const Polynom& PolynomGF2_mY_7::getA2() const
  {
    return _a2;
  }
  const Polynom& PolynomGF2_mY_7::getA3() const
  {
    return _a3;
  }
    const Polynom& PolynomGF2_mY_7::getA4() const
  {
    return _a4;
  }
  const Polynom& PolynomGF2_mY_7::getA5() const
  {
    return _a5;
  }
  const Polynom& PolynomGF2_mY_7::getA6() const
  {
    return _a6;
  }
  const Polynom& PolynomGF2_mY_7::getModPolynom() const
  {
    return _modPolynom;
  }
  const Polynom& PolynomGF2_mY_7::getModule() const
  {
    return _module;
  }
//------------------------------------------------------------------------------
    void PolynomGF2_mY_7::setA0(const Polynom & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF2_mY_7::setA1(const Polynom & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF2_mY_7::setA2(const Polynom & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF2_mY_7::setA3(const Polynom & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF2_mY_7::setA4(const Polynom & a)
    {
        _a4 = a;
        _a4 %= _module;
    }
    void PolynomGF2_mY_7::setA5(const Polynom & a)
    {
        _a5 = a;
        _a5 %= _module;
    }
    void PolynomGF2_mY_7::setA6(const Polynom & a)
    {
        _a6 = a;
        _a6 %= _module;
    }
    void PolynomGF2_mY_7::setModule(const Polynom& module)
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
    void PolynomGF2_mY_7::setModPolynom(const Polynom& modPolynom)
    {
        _modPolynom = modPolynom;
        if((modPolynom.getNumberBits()-1)!=4)
            throw std::out_of_range("модул€рные многочлен порождающий расширение пол€ должны быть степени 4");
    }
//------------------------------------------------------------------------------
//******************************    ќпераци€ сложени€    ***************************************
	//simple method
	PolynomGF2_mY_7 operator+(const PolynomGF2_mY_7 &a, const PolynomGF2_mY_7 &b)
	{
		PolynomGF2_mY_7 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF2_mY_7& PolynomGF2_mY_7::operator+=(PolynomGF2_mY_7 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF2_mY_7& PolynomGF2_mY_7::Add(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b)
	{
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");

        if(a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module=a._module;
		_a0.Add(a._a0, b._a0);
        _a1.Add(a._a1, b._a1);
        _a2.Add(a._a2, b._a2);
        _a3.Add(a._a3, b._a3);
        _a4.Add(a._a4, b._a4);
        _a5.Add(a._a5, b._a5);
        _a6.Add(a._a6, b._a6);
        return *this;
	}
//******************************    ќпераци€ умножени€    **************************************
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
	PolynomGF2_mY_7& PolynomGF2_mY_7::Mul(PolynomGF2_m_4 &a, PolynomGF2_m_4 &b)
	{
		Polynom e0;
        Polynom e1,e11,e12;
        Polynom e2,e21,e22,e23;
        Polynom e3,e31,e32,e33,e34;
        Polynom e4, e41,e42,e43;
        Polynom e5,e51,e52,e6;
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
        if(a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
		if(a.isZero() || b.isZero())
  			return setZero();
        e0.ModMul(a.getA0(),b.getA0(), _module);
        e1 = e1.ModMul(a.getA1(),b.getA0(),_module) + e2.ModMul(a.getA0(), b.getA1(), _module);
        e2 = e21.ModMul(a.getA2(),b.getA0(),_module) + e22.ModMul(a.getA1(),b.getA1(),_module) + e23.ModMul(a.getA0(),b.getA2(),_module);
        e3 = e31.ModMul(a.getA3(),b.getA0(),_module) + e32.ModMul(a.getA2(),b.getA1(),_module) + e33.ModMul(a.getA1(),b.getA2(),_module) + e34.ModMul(a.getA0(),b.getA3(),_module);
        e4 = e41.ModMul(a.getA1(),b.getA3(),_module) + e42.ModMul(a.getA2(),b.getA2(),_module) + e43.ModMul(a.getA3(),b.getA1(),_module);
        e5 = e51.ModMul(a.getA2(),b.getA3(),_module) + e52.ModMul(a.getA3(),b.getA2(),_module);
        e6.ModMul(a.getA3(),b.getA3(),_module);
        _a0 = e0;
        std::string s = _a0.ToString();
        _a1 = e1;
        s  =  _a1.ToString();
        _a2 = e2;
        s = _a2.ToString();
        _a3 = e3;
        s = _a3.ToString();
        _a4 = e4;
        s  =  _a4.ToString();
        _a5 = e5;
        s = _a5.ToString();
        _a6 = e6;
        s = _a6.ToString();
		return *this;
	}
	PolynomGF2_mY_7& PolynomGF2_mY_7::FullMul(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b)
	{
        Polynom e0;
        Polynom e1,e11,e12;
        Polynom e2,e21,e22,e23;
        Polynom e3,e31,e32,e33,e34;
        Polynom e4, e41,e42,e43,e44,e45;
        Polynom e5,e51,e52,e53,e54,e55,e56,e6,e61,e62,e63,e64,e65,e66,e67;
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
        if(a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
		if(a.isZero() || b.isZero())
  			return setZero();
        e0.ModMul(a.getA0(),b.getA0(), _module);
        e1 = e1.ModMul(a.getA1(),b.getA0(),_module) + e2.ModMul(a.getA0(), b.getA1(), _module);
        e2 = e21.ModMul(a.getA2(),b.getA0(),_module) + e22.ModMul(a.getA1(),b.getA1(),_module) + e23.ModMul(a.getA0(),b.getA2(),_module);
        e3 = e31.ModMul(a.getA3(),b.getA0(),_module) + e32.ModMul(a.getA2(),b.getA1(),_module) + e33.ModMul(a.getA1(),b.getA2(),_module) + e34.ModMul(a.getA0(),b.getA3(),_module);
        e4 = e41.ModMul(a.getA0(),b.getA4(),_module) + e42.ModMul(a.getA1(),b.getA3(),_module) + e43.ModMul(a.getA2(),b.getA2(),_module) + e44.ModMul(a.getA3(),b.getA1(),_module) + e45.ModMul(a.getA4(),b.getA0(),_module);
        e5 = e51.ModMul(a.getA0(),b.getA5(),_module) + e52.ModMul(a.getA4(),b.getA1(),_module) + e53.ModMul(a.getA3(),b.getA2(),_module) + e54.ModMul(a.getA2(),b.getA3(),_module) + e55.ModMul(a.getA1(),b.getA4(),_module) + e56.ModMul(a.getA5(),b.getA0(),_module);
        e6 = e61.ModMul(a.getA0(),b.getA6(),_module) + e62.ModMul(a.getA1(),b.getA5(),_module) + e63.ModMul(a.getA2(),b.getA4(),_module) + e64.ModMul(a.getA3(),b.getA3(),_module) + e65.ModMul(a.getA4(),b.getA2(),_module) + e66.ModMul(a.getA5(),b.getA1(),_module) + e67.ModMul(a.getA6(),b.getA0(),_module);
        _a0 = e0;
        std::string s = _a0.ToString();
        _a1 = e1;
        s  =  _a1.ToString();
        _a2 = e2;
        s = _a2.ToString();
        _a3 = e3;
        s = _a3.ToString();
        _a4 = e4;
        s  =  _a4.ToString();
        _a5 = e5;
        s = _a5.ToString();
        _a6 = e6;
        s = _a6.ToString();
		return *this;
	}

    PolynomGF2_mY_7& PolynomGF2_mY_7::MonomialMul(PolynomGF2_mY_7 &a, PolynomGF2_m_4 &b)
    {
		Polynom e0;
        Polynom e1;
        Polynom e2;
        Polynom e3;
        Polynom e4;
        Polynom e5,e6;
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
        if(a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
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
        _a0 = e0;
        std::string s = _a0.ToString();
        _a1 = e1;
        s  =  _a1.ToString();
        _a2 = e2;
        s = _a2.ToString();
        _a3 = e3;
        s = _a3.ToString();
        _a4 = e4;
        s  =  _a4.ToString();
        _a5 = e5;
        s = _a5.ToString();
        _a6 = e6;
        s = _a6.ToString();
		return *this;
    }
    PolynomGF2_mY_7& PolynomGF2_mY_7::NormalMonomialMul(PolynomGF2_mY_7 &a, int d)
    {
              Polynom e1;
              PolynomGF2_mY_7 result;
                if(a.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");
              if(a.deg() + d > 6)
                        throw std::out_of_range("ошибка deg(a) + d должнобыть <= 6");
              for(int i = 0; i < d; i++)
              {
                e1 = e1.setZero();
                result.setByIndex(e1,i);
              }
              int j = 0;
              for(int i = d; i <= 7; i++)
              if(j<7) {
                e1 = a.getByIndex(j);
                result.setByIndex(e1,i);
                j++;
              }
              result._module = a._module;
              result._modPolynom = a._modPolynom;
              *this = result;
		return *this;
    }

    const Polynom& PolynomGF2_mY_7::getByIndex(int index) const
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
    }
    void PolynomGF2_mY_7::setByIndex(const Polynom & a, int index)
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
    }
    PolynomGF2_mY_7& PolynomGF2_mY_7::Div(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b, Polynom &module, PolynomGF2_mY_7 *remainder)
    {
                if(a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        PolynomGF2_mY_7 q,r,_a,_bb,_c;
        PolynomGF2_m_4 p;
        Polynom _q,_b,_inv;
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
        if(deg_a < deg_b)
        {
           *remainder = b;
           *this = q;
           return *this;
        }
        while(deg_a >= deg_b)
        {
           _b = _bb.getByIndex(deg_b);
           _inv.Inverse(_b ,module);
           s = _inv.ToString();
           std::string s1 = _a.getByIndex(deg_a).ToString();
           _q.ModMul( _a.getByIndex(deg_a),_inv,module);
           s = _q.ToString();
            d = deg_a -deg_b;
            q.setByIndex(_q,d);
            p.exist(_q,module);
            _c._module = module;
            _c = MonomialMul( _bb, p);
            _c = NormalMonomialMul(_c,d);

            _a = _a + _c;
            r = _a;
/*            s = _a._a0.ToString();
            s  =  _a._a1.ToString();
            s = _a._a2.ToString();
            s = _a._a3.ToString();
            s  =  _a._a4.ToString();
            s = _a._a5.ToString();
            s = _a._a6.ToString();
*/
            deg_a = _a.deg();
        }
/*        s = r.getA0().ToString();
        s = r.getA1().ToString();
        s = r.getA2().ToString();
        s = r.getA3().ToString();
        s = r.getA4().ToString();
        s = r.getA5().ToString();
        s = r.getA6().ToString();
*/
        *this = q;
         *remainder = r;
         return *this;
    }
PolynomGF2_mY_7& PolynomGF2_mY_7::GCD(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b, Polynom &module)
{
    PolynomGF2_mY_7 c,r,d;
    while(!b.isZero())
    {
       d.Div(a,b,a._module,&r);
       a = b;
       b = r;
    }
    *this = a;
              std::string s = a._a0.ToString();
            s  =  a._a1.ToString();
            s = a._a2.ToString();
            s = a._a3.ToString();
            s  =  a._a4.ToString();
            s = a._a5.ToString();
            s = a._a6.ToString();
   return  *this;
}    
};


