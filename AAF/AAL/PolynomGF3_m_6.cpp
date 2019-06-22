/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF3_m_6.h"
#include "Polynom.h"
#include "Converter.h"
#include "Algorithms.h"
#include "Matrix.h"
#include "TableManager.h"
#include <stdlib.h>
#include <math.h>
#include "DecompositionManager.h"
#include "PolynomGF3_mY_9.h"
namespace AAL
{
  int terndiv(std::vector<Integer>* m, Integer n)
  {
    int j,i = 0;
    while(n >= 3)
    {
        //j = n%3;
        m->push_back(n%3);
        i++;
        n = n/3;
    }
    m->push_back(n);
    return i;
  }

 //***********************************  Конструкторы  *******************************************
	//(c) Belova, TEST(PolynomGF3_m_6, EmptyConstructor)
	PolynomGF3_m_6::PolynomGF3_m_6() :
        _a0(), _a1(), _a2(), _a3(), _a4(), _a5(), _module(), _modPolynom("2100001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, CopyConstructor)
	PolynomGF3_m_6::PolynomGF3_m_6(const PolynomGF3_m_6 &polynom)
	{
     _a0 = polynom._a0;
     _a1 = polynom._a1;
     _a2 = polynom._a2;
     _a3 = polynom._a3;
     _a4 = polynom._a4;
     _a5 = polynom._a5;
     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, StringConstructor)
	PolynomGF3_m_6::PolynomGF3_m_6(const std::string a0,
     const std::string a1, const std::string a2,
     const std::string a3, const std::string a4,
     const std::string a5, const std::string module):
     _a0(a0), _a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5),_module(module), _modPolynom("2100001")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF3_m_6::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero())
            return true;
        return false;
    }
    bool PolynomGF3_m_6::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero() && _a4.isZero() && _a5.isZero())
            return true;
        return false;
    }
//------------------------------------------------------------------------------

	//simple method
	PolynomGF3_m_6& PolynomGF3_m_6::setZero()
	{
        _a0.setZero();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        _a4.setZero();
        _a5.setZero();
		return *this;
	}
    //simple method
	PolynomGF3_m_6& PolynomGF3_m_6::setOne()
	{
        _a0.setOne();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        _a4.setZero();
        _a5.setZero();
        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, Equal)
	bool operator==(const PolynomGF3_m_6& a, const PolynomGF3_m_6& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3  && a._a4 == b._a4 && a._a5 == b._a5)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, operatorEqual)
	PolynomGF3_m_6& PolynomGF3_m_6::operator= (const PolynomGF3_m_6& polynom)
	{
        if(this == &polynom)
            return *this;

        _a0 = polynom._a0;
        _a1 = polynom._a1;
        _a2 = polynom._a2;
        _a3 = polynom._a3;
        _a4 = polynom._a4;
        _a5 = polynom._a5;
        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF3_m_6& a, const PolynomGF3_m_6& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF3& PolynomGF3_m_6::getA0() const
  {
    return _a0;
  }
  const PolynomGF3& PolynomGF3_m_6::getA1() const
  {
    return _a1;
  }
  const PolynomGF3& PolynomGF3_m_6::getA2() const
  {
    return _a2;
  }
  const PolynomGF3& PolynomGF3_m_6::getA3() const
  {
    return _a3;
  }
  const PolynomGF3& PolynomGF3_m_6::getA4() const
  {
    return _a4;
  }
  const PolynomGF3& PolynomGF3_m_6::getA5() const
  {
    return _a5;
  }
  const PolynomGF3& PolynomGF3_m_6::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF3& PolynomGF3_m_6::getModule() const
  {
    return _module;
  }
//------------------------------------------------------------------------------
    void PolynomGF3_m_6::setA0(const PolynomGF3 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF3_m_6::setA1(const PolynomGF3 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF3_m_6::setA2(const PolynomGF3 & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF3_m_6::setA3(const PolynomGF3 & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF3_m_6::setA4(const PolynomGF3 & a)
    {
        _a4 = a;
        _a4 %= _module;
    }
    void PolynomGF3_m_6::setA5(const PolynomGF3 & a)
    {
        _a5 = a;
        _a5 %= _module;
    }
    void PolynomGF3_m_6::setModule(const PolynomGF3& module)
    {
        _module = module;
        _a0 %= _module;
        _a1 %= _module;
        _a2 %= _module;
        _a3 %= _module;
        _a4 %= _module;
        _a5 %= _module;
    }
    void PolynomGF3_m_6::setModPolynom(const PolynomGF3& modPolynom)
    {
        _modPolynom = modPolynom;
        if((modPolynom.getNumberBits()-1)!=6)
            throw new Exception("модулярные многочлен порождающий расширение поля должны быть степени 6");
    }
//------------------------------------------------------------------------------
//******************************    Операция сложения    ***************************************
	//simple method
	PolynomGF3_m_6 operator+(const PolynomGF3_m_6 &a, const PolynomGF3_m_6 &b)
	{
		PolynomGF3_m_6 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF3_m_6& PolynomGF3_m_6::operator+=(PolynomGF3_m_6 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF3_m_6& PolynomGF3_m_6::Add(PolynomGF3_m_6 &a, PolynomGF3_m_6 &b)
	{
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module=a._module;
 		_a0.ModAdd(a._a0, b._a0, _module);
 //       std::string s = _a0.ToString();
        _a1.ModAdd(a._a1, b._a1, _module);
 //       s = _a1.ToString();
        _a2.ModAdd(a._a2, b._a2, _module);
 //       s = _a2.ToString();
        _a3.ModAdd(a._a3, b._a3, _module);
 //       s = _a3.ToString();
        _a4.ModAdd(a._a4, b._a4, _module);
 //       s = _a4.ToString();
        _a5.ModAdd(a._a5, b._a5, _module);
 //        s = _a5.ToString();
        return *this;
	}
//******************************    Операция умножения    **************************************
	//simple method
	PolynomGF3_m_6 operator*(const PolynomGF3_m_6 &a, const PolynomGF3_m_6 &b)
	{
		PolynomGF3_m_6 result;
        PolynomGF3_m_6 copy_a(a), copy_b(b);
 		return result.Mul(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF3_m_6& PolynomGF3_m_6::operator*=(PolynomGF3_m_6 &polynom)
	{
		return Mul(*this, polynom);
	}
//------------------------------------------------------------------------------

	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF3_m_6& PolynomGF3_m_6::Mul(PolynomGF3_m_6 &a, const PolynomGF3_m_6 &b)
	{
		PolynomGF3 e0;
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
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module = a._module;
		if(a.isZero() || b.isZero())
  			return setZero();
        e0.ModMul(a._a0,b._a0, _module);
        e1 = e11.ModMul(a._a1,b._a0,_module) + e12.ModMul(a._a0, b._a1, _module);
        e2 = e21.ModMul(a._a2,b._a0,_module) + e22.ModMul(a._a1,b._a1,_module) + e23.ModMul(a._a0,b._a2,_module);
        e3 = e31.ModMul(a._a3,b._a0,_module) + e32.ModMul(a._a2,b._a1,_module) + e33.ModMul(a._a1,b._a2,_module) + e34.ModMul(a._a0,b._a3,_module);
        e4 = e41.ModMul(a._a4,b._a0,_module) + e42.ModMul(a._a3,b._a1,_module) + e43.ModMul(a._a2,b._a2,_module) + e44.ModMul(a._a1,b._a3,_module) + e45.ModMul(a._a0,b._a4,_module);
        e5 = e51.ModMul(a._a5,b._a0,_module) + e52.ModMul(a._a4,b._a1,_module) + e53.ModMul(a._a3,b._a2,_module) + e54.ModMul(a._a2,b._a3,_module) + e55.ModMul(a._a1,b._a4,_module) + e56.ModMul(a._a0,b._a5,_module);
        e6 = e61.ModMul(a._a5,b._a1,_module) + e62.ModMul(a._a4,b._a2,_module) + e63.ModMul(a._a3,b._a3,_module) + e64.ModMul(a._a2,b._a4,_module) + e65.ModMul(a._a1,b._a5,_module);
        e7 = e71.ModMul(a._a5,b._a2,_module) + e72.ModMul(a._a4,b._a3,_module) + e73.ModMul(a._a3,b._a4,_module) + e74.ModMul(a._a2,b._a5,_module);
        e8 = e81.ModMul(a._a5,b._a3,_module) + e82.ModMul(a._a4,b._a4,_module) + e83.ModMul(a._a3,b._a5,_module);
        e9 = e91.ModMul(a._a5,b._a4,_module) + e92.ModMul(a._a4, b._a5, _module);
        e10.ModMul(a._a5,b._a5, _module);

        _a0 = e0 + e6;
//        std::string s = _a0.ToString();
        _a1 = e1 + e6 + e6 + e7;
//        s  =  _a1.ToString();
        _a2 = e2 + e7 + e7 + e8;
//        s = _a2.ToString();
        _a3 = e3 + e8 + e8 + e9;
//        s = _a3.ToString();
        _a4 =  e4 +e9 + e9 +e10;
//        s = _a4.ToString();
        _a5 =  e5 + e10 +e10;
//        s = _a5.ToString();
		return *this;
	}
// простой метод возведения в степень 3 по модулю
	PolynomGF3_m_6& PolynomGF3_m_6::Cube(PolynomGF3_m_6 &a)
	{
		PolynomGF3 e0,e1,e2,e4, e11,e13,e14;
        PolynomGF3 e3;
        PolynomGF3 e6;
        PolynomGF3 e9,e12,e15;
        _modPolynom = a._modPolynom;
        _module = a._module;
		if(a.isZero())
  			return setZero();
        if(a.getModule().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");
        e0.ModPow(a._a0,3,_module);
//        std::string ss = e0.ToString();
        e3.ModPow(a._a1,3,_module);
//        ss = e3.ToString();
        //e1 =  e11.ModMul(a._a1,a._a0,_module) + e12.ModMul(a._a1,a._a0,_module)
        e6.ModPow(a._a2,3,_module);
//        ss = e6.ToString();
        e9.ModPow(a._a3,3,_module);
//        ss = e9.ToString();
        e12.ModPow(a._a4,3,_module);
//        ss = e12.ToString();
        e15.ModPow(a._a5,3,_module);
//        ss = e15.ToString();
        _a0 = e0 + e6 + e12;
//        std::string s = _a0.ToString();
        _a1 = e6 + e6 + e12;
//        s = _a1.ToString();
        _a2 = e12;
//        s = _a2.ToString();
        _a3 = e3 + e9 + e15;
//        s = _a3.ToString();
        _a4 = e9 + e9 +e15;
//        s = _a4.ToString();
        _a5 = e15;
//        s = _a5.ToString();
		return *this;
	}
  //возведение в степень
  PolynomGF3_m_6& PolynomGF3_m_6::Pow(PolynomGF3_m_6 &a, const Integer &n)
  {
    if(n.isNegative())
        throw std::domain_error("Число n - отрицательное результат не определен");
//    if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
    //int len = atoi(n.ToString().c_str());
   std::vector<Integer> m;
    int num_bit;
    num_bit = terndiv(&m,n);
    std::string s = m[0].ToString();
    _modPolynom = a._modPolynom;
    _module = a._module;
    PolynomGF3_m_6 c,result("1","0","0","0","0","0",a._module.ToString());
//    std::string m1 = a._module.ToString();
    PolynomGF3_m_6 one("1","0","0","0","0","0",a._module.ToString());
    Integer copy_n(n);
    //result.setOne();
    for(int i=1;i<=num_bit+1;i++)
    {
        c.Cube(result);// = result*result*result;
        result = c;
        if(m[num_bit + 1 - i] == 1)
            result.Mul(result,a);
        if(m[num_bit + 1 - i] == 2)
            result.Mul(result,a*a);
        else
            result *= one;
    }
    *this = result;
/*    std::string st = _a0.ToString();
    st = _a1.ToString();
    st = _a2.ToString();
    st = _a3.ToString();
    st = _a4.ToString();
    st = _a5.ToString();
*/
    m.clear();
    return *this;
  }
     const PolynomGF3& PolynomGF3_m_6::getByIndex(int index) const
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

    }
    void PolynomGF3_m_6::setByIndex(const PolynomGF3 & a, int index)
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

    }
   //определение степени многочлена
    int PolynomGF3_m_6::deg() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero()&& _a4.isZero() && _a5.isZero())
            return -1;
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
	PolynomGF3_m_6& PolynomGF3_m_6::Inverse(PolynomGF3 &module)
	{
		return Inverse(*this, module);
	}
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_m_4, Inverse)
	PolynomGF3_m_6& PolynomGF3_m_6::Inverse(PolynomGF3_m_6 &polynom, PolynomGF3 &module)
	{
 //       if(polynom.getModule().isIrreducible() == false || module.isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        PolynomGF3_mY_9 d2("0","0","0","0","0","0","0","0","0","0","0",module.ToString()),d1("1","0","0","0","0","0","0","0","0","0","0",module.ToString()),w1;
        PolynomGF3_mY_9 u("2","1","0","0","0","0","1","0","0","0","0",module.ToString()),w,r,c,_c;
        PolynomGF3_mY_9 two("2","0","0","0","0","0","0","0","0","0","0",module.ToString());
        int d = 0;
        PolynomGF3_m_6 result;
        PolynomGF3 _u,_v,inv,_q,_b;
        PolynomGF3_mY_9 v(polynom._a0.ToString(),polynom._a1.ToString(),polynom._a2.ToString(),polynom._a3.ToString(),polynom._a4.ToString(),polynom._a5.ToString(),"0","0","0","0","0",module.ToString());
        PolynomGF3_mY_9 vv,d11;
         d1.setModule(module);
        d2.setModule(module);
        u.setModule(module);
        v.setModule(module);
         std::string s;
        while(v.deg() != 0 && v.isZero() != true)
        {
            if(u.deg() < v.deg())
            {
                    w = u;
/*                   s = u.getA0().ToString();
                   s = u.getA1().ToString();
                   s = u.getA2().ToString();
                   s = u.getA3().ToString();
                   s = u.getA4().ToString();
                   s = u.getA5().ToString();
                   s = u.getA6().ToString();
                   s = u.getA7().ToString();
                   s = u.getA8().ToString();
                   s = u.getA9().ToString();
                   s = u.getA10().ToString();
*/
                    u = v;
/*                   s = v.getA0().ToString();
                   s = v.getA1().ToString();
                   s = v.getA2().ToString();
                   s = v.getA3().ToString();
                   s = v.getA4().ToString();
                   s = v.getA5().ToString();
                   s = v.getA6().ToString();
                   s = v.getA7().ToString();
                   s = v.getA8().ToString();
                   s = v.getA9().ToString();
                   s = v.getA10().ToString();
*/
                    v = w;
/*                   s = w.getA0().ToString();
                   s = w.getA1().ToString();
                   s = w.getA2().ToString();
                   s = w.getA3().ToString();
                   s = w.getA4().ToString();
                   s = w.getA5().ToString();
                   s = w.getA6().ToString();
                   s = w.getA7().ToString();
                   s = w.getA8().ToString();
                   s = w.getA9().ToString();
                   s = w.getA10().ToString();
 */
                    w1 = d1;
/*                   s = d1.getA0().ToString();
                   s = d1.getA1().ToString();
                   s = d1.getA2().ToString();
                   s = d1.getA3().ToString();
                   s = d1.getA4().ToString();
                   s = d1.getA5().ToString();
                   s = d1.getA6().ToString();
                   s = d1.getA7().ToString();
                   s = d1.getA8().ToString();
                   s = d1.getA9().ToString();
                   s = d1.getA10().ToString();
 */
                    d1 = d2;
 /*                  s = d2.getA0().ToString();
                   s = d2.getA1().ToString();
                   s = d2.getA2().ToString();
                   s = d2.getA3().ToString();
                   s = d2.getA4().ToString();
                   s = d2.getA5().ToString();
                   s = d2.getA6().ToString();
                   s = d2.getA7().ToString();
                   s = d2.getA8().ToString();
                   s = d2.getA9().ToString();
                   s = d2.getA10().ToString();
  */
                    d2 = w1;
            }
            d = u.deg() - v.deg();
            _v = v.getByIndex(v.deg());
    //        s = _v.ToString();
            _v = inv.InverseMod(_v,module);
    //        s = _v.ToString();
            _q.ModMul(u.getByIndex(u.deg()),inv,module);
    //        s = _q.ToString();
            PolynomGF3_mY_9 q;
            q.setModule(polynom._module);
            q.setByIndex(_q,0);
      /*             s = q.getA0().ToString();
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
             s = q.getModule().ToString();
        */
            q = q.NormalMonomialMul(q,d);
   /*                s = q.getA0().ToString();
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
            PolynomGF3_mY_9 minus;
            q = minus.FullMul(two,q);
            r = u + vv.FullMul(v,q);
      /*             s = r.getA0().ToString();
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
        */
            c = d2 + d11.FullMul(d1,q);
        /*           s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();
                   s = c.getA3().ToString();
                   s = c.getA4().ToString();
                   s = c.getA5().ToString();
                   s = c.getA6().ToString();
                   s = c.getA7().ToString();
                   s = c.getA8().ToString();
                   s = c.getA9().ToString();
                   s = c.getA10().ToString();
          */

            u = v;
          /*         s = u.getA0().ToString();
                   s = u.getA1().ToString();
                   s = u.getA2().ToString();
                   s = u.getA3().ToString();
                   s = u.getA4().ToString();
                   s = u.getA5().ToString();
                   s = u.getA6().ToString();
                   s = u.getA7().ToString();
                   s = u.getA8().ToString();
                   s = u.getA9().ToString();
                   s = u.getA10().ToString();
           */
            v = r;
            /*       s = v.getA0().ToString();
                   s = v.getA1().ToString();
                   s = v.getA2().ToString();
                   s = v.getA3().ToString();
                   s = v.getA4().ToString();
                   s = v.getA5().ToString();
                   s = v.getA6().ToString();
                   s = v.getA7().ToString();
                   s = v.getA8().ToString();
                   s = v.getA9().ToString();
                   s = v.getA10().ToString();
            */
            d2 = d1;
             /*      s = d2.getA0().ToString();
                   s = d2.getA1().ToString();
                   s = d2.getA2().ToString();
                   s = d2.getA3().ToString();
                   s = d2.getA4().ToString();
                   s = d2.getA5().ToString();
                   s = d2.getA6().ToString();
                   s = d2.getA7().ToString();
                   s = d2.getA8().ToString();
                   s = d2.getA9().ToString();
                   s = d2.getA10().ToString();
               */
            d1 = c;
              /*     s = d1.getA0().ToString();
                   s = d1.getA1().ToString();
                   s = d1.getA2().ToString();
                   s = d1.getA3().ToString();
                   s = d1.getA4().ToString();
                   s = d1.getA5().ToString();
                   s = d1.getA6().ToString();
                   s = d1.getA7().ToString();
                   s = d1.getA8().ToString();
                   s = d1.getA9().ToString();
                   s = d1.getA10().ToString();
                */
        }
            PolynomGF3 p,e0,e6,e01,e61,e62,e63,e64,e65;
            e0 = e01.ModMul(polynom._a0,c.getA0(),polynom._module);
            e6 = e61.ModMul(polynom._a5,c.getA1(),polynom._module) + e62.ModMul(polynom._a4,c.getA2(),polynom._module) + e63.ModMul(polynom._a3,c.getA3(),polynom._module) + e64.ModMul(polynom._a2,c.getA4(),polynom._module) + e65.ModMul(polynom._a1,c.getA5(),polynom._module);
            p = e0+e6;
 //           s = p.ToString();
            _b.InverseMod(p,module);
 //           s = _b.ToString();
            PolynomGF3_m_6 cc;
            cc.setModule(module);
            cc.setByIndex(_b,0);
   /*                s = cc.getA0().ToString();
                   s = cc.getA1().ToString();
                   s = cc.getA2().ToString();
                   s = cc.getA3().ToString();
                   s = cc.getA4().ToString();
                   s = cc.getA5().ToString();
     */
            c = _c.MonomialMul(c,cc);
       /*            s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();
                   s = c.getA3().ToString();
                   s = c.getA4().ToString();
                   s = c.getA5().ToString();
                   s = c.getA6().ToString();
                   s = c.getA7().ToString();
                   s = c.getA8().ToString();
                   s = c.getA9().ToString();
                   s = c.getA10().ToString();
         */
        result._a0 = c.getA0();
        result._a1 = c.getA1();
        result._a2 = c.getA2();
        result._a3 = c.getA3();
        result._a4 = c.getA4();
        result._a5 = c.getA5();
        result._module = c.getModule();
        *this = result;
        return *this;
    }
   // извлечение квадратного корня
   PolynomGF3_m_6& PolynomGF3_m_6::CubeRoot(PolynomGF3_m_6 &a, PolynomGF3 &module)
   {
//        if(a.getModPolynom().isIrreducible() == false ||module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
        PolynomGF3_m_6 result;
/*        int len = atoi(n.ToString().c_str());
        int* m  = new int[len];
        int num_bit;
        num_bit = terndiv(m,len); */
        _modPolynom = a._modPolynom;
        _module = a._module;
        uint m = module.getNumberBits() - 1;
        Integer power("1");
        power.Pow(3,(6*m) - 1);
       // power = (power - 1);///2;
        result.Pow(a, power);

        *this = result;
   /*     std::string s = result._a0.ToString();
        s = result._a1.ToString();
        s = result._a2.ToString();
        s = result._a3.ToString();
        s = result._a4.ToString();
        s = result._a5.ToString();
     */
        return *this;
   }
   PolynomGF3_m_6& PolynomGF3_m_6::LegendreSymbol( PolynomGF3_m_6 &a, PolynomGF3 &module)
   {
//        if(a.getModPolynom().isIrreducible() == false ||module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
       PolynomGF3_m_6 result,minus_one("2","0","0","0","0","0","");
         minus_one._module = module;
        _modPolynom = a._modPolynom;
        _module = module;
        uint m = module.getNumberBits() - 1;
        Integer power("1");
        power.Pow(3,(6*m));
        power = (power-1)/2;
        std::string s;
        result.Pow(a,power);
          s = result._a0.ToString();
          s = result._a1.ToString();
          s = result._a2.ToString();
          s = result._a3.ToString();
          s = result._a4.ToString();
          s = result._a5.ToString();

        *this = result;
        return *this;
   }
   PolynomGF3_m_6& PolynomGF3_m_6::Sqrt(PolynomGF3_m_6 &x, PolynomGF3 &module,Integer &ss,Integer &T)
   {
//        if(x.getModule().isIrreducible() == false ||module.isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");

        bool rez;
        Integer s;
        s = ss;
        PolynomGF3_m_6 test;
        PolynomGF3_m_6 zero("0","0","0","0","0","0",module.ToString());
        test.LegendreSymbol(x,module);
        if(test.isOne() != true)
        {
                *this = zero;
                return *this;
        }
        PolynomGF3_m_6 result,a,b,e1,e2,e3,e4,e5;
        result.setOne();
        PolynomGF3_m_6 minus_one("2","0","0","0","0","0",module.ToString());
         minus_one._module = module;
        _modPolynom = x._modPolynom;
        _module = module;
        uint m = module.getNumberBits() - 1;
        Integer power("1"),t("0");
        power.Pow(3,(6*m));
        power = (power-1)/2;

       // std::string st;
        while(result != minus_one)
        {
          a.Generate(module);
          result.LegendreSymbol(a,module);
        }
        a = a.Pow(a,s);
       /* st = a._a0.ToString();
        st = a._a1.ToString();
        st = a._a2.ToString();
        st = a._a3.ToString();
        st = a._a4.ToString();
        st = a._a5.ToString();
        */
        b = b.Pow(x,29);
        /*st = b._a0.ToString();
        st = b._a1.ToString();
        st = b._a2.ToString();
        st = b._a3.ToString();
        st = b._a4.ToString();
        st = b._a5.ToString();
         */
        b.setOne();
        b = b.Pow(x,(s-1)/2);
        /*st = b._a0.ToString();
        st = b._a1.ToString();
        st = b._a2.ToString();
        st = b._a3.ToString();
        st = b._a4.ToString();
        st = b._a5.ToString();
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
           //     st = two.ToString();
                e5.Pow(e4,two);
                if(e5 == minus_one)
                        c = 1;
                if(e5.isOne())
                        c = 0;
                t = t + e.Pow(2,k)*c;
                t0 = t;
                k = k + 1;
        }
        *this = a.Pow(a,t)*b*x;
        /*s = _a0.ToString();
          s = _a1.ToString();
          s = _a2.ToString();
          s = _a3.ToString();
          s = _a4.ToString();
          s = _a5.ToString();
          */
        return *this;
   }
   //тест образующего элемента, определение порядка элемента
   Integer& PolynomGF3_m_6::elementOrder(PolynomGF3 &groupModule, PolynomGF3_m_6 &polynom,std::vector<DecompositionMember> vector, const Integer &ord )
{
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    PolynomGF3 *m  = new PolynomGF3(groupModule);
    PolynomGF3_m_6 *a = new PolynomGF3_m_6(polynom);
    Integer t =  ord;
    for(it = vector.begin(); it != vector.end();it++)
   {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.ModPow(p,e, t);
      //std::string s = ex.ToString();
      t = t/(ex);
      PolynomGF3_m_6 a1;
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
bool PolynomGF3_m_6::isGenerator(PolynomGF3 &groupModule, PolynomGF3_m_6 &polynom,std::vector<DecompositionMember> vector, Integer &ord)
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
void PolynomGF3_m_6::exist(PolynomGF3 &a, PolynomGF3& module)
{
    _a0 = a;
    _a1.setZero();
    _a2.setZero();
    _a3.setZero();
    _a4.setZero();
    _a5.setZero();

    _module = module;
}
PolynomGF3_m_6& PolynomGF3_m_6::Generate(PolynomGF3& module)
{
        _a0 = _a0.Generate(module);
        _a1 = _a1.Generate(module);
        _a2 = _a2.Generate(module);
        _a3 = _a3.Generate(module);
        _a4 = _a4.Generate(module);
        _a5 = _a5.Generate(module);
        _module = module;
        return *this;
}
//-----------------------------------------------------------------------------------
PolynomGF3_m_6& PolynomGF3_m_6::getRo(PolynomGF3_m_6 &b,PolynomGF3& mod)
{
      PolynomGF3_m_6 p,f,f0,e,h("0","0","0","0","0","0",mod.ToString()),two("2","0","0","0","0","0",mod.ToString());
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
  */
        h.Pow(p,3);
 /*   s = h.getA0().ToString();
    s =  h.getA1().ToString();
    s = h.getA2().ToString();
    s = h.getA3().ToString();
    s = h.getA4().ToString();
    s = h.getA5().ToString();
   */
        e.Mul(p,two);
   /* s = e.getA0().ToString();
    s =  e.getA1().ToString();
    s = e.getA2().ToString();
    s = e.getA3().ToString();
    s = e.getA4().ToString();
    s = e.getA5().ToString();
     */
        f0.Mul(b,two);
   /* s = f0.getA0().ToString();
    s =  f0.getA1().ToString();
    s = f0.getA2().ToString();
    s = f0.getA3().ToString();
    s = f0.getA4().ToString();
    s = f0.getA5().ToString();
     */
        f = p+h+e+f0;
     /*   s = f.getA0().ToString();
    s =  f.getA1().ToString();
    s = f.getA2().ToString();
    s = f.getA3().ToString();
    s = f.getA4().ToString();
    s = f.getA5().ToString();
   */
    }

    *this = p;
    return *this;
}

};

