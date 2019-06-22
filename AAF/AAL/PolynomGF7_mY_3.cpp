/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF7_mY_3.h"
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
	PolynomGF7_mY_3::PolynomGF7_mY_3() :
        _a0(), _a1(), _a2(),_module(), _modPolynom("11001")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, CopyConstructor)
	PolynomGF7_mY_3::PolynomGF7_mY_3(const PolynomGF7_mY_3 &polynom)
	{
     _a0 = polynom._a0;
     _a1 = polynom._a1;
     _a2 = polynom._a2;

     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, StringConstructor)
	PolynomGF7_mY_3::PolynomGF7_mY_3(const std::string a0,
     const std::string a1, const std::string a2,
        const std::string module):
     _a0(a0), _a1(a1), _a2(a2),_module(module), _modPolynom("311")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF7_mY_3::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() )
            return true;
        return false;
    }
    bool PolynomGF7_mY_3::isZero(PolynomGF7 &module) const
    {
        if(_a0.isZero(module) && _a1.isZero(module) && _a2.isZero(module) )
            return true;
        return false;
    }

    bool PolynomGF7_mY_3::isOne() const
    {
        if(_a0.isOne() && _a1.isZero() && _a2.isZero())
            return true;
        return false;
    }
    //определение степени многочлена
    int PolynomGF7_mY_3::deg() const
    {
        PolynomGF7 mod = _module;
        if(_a0.isZero(mod) && _a1.isZero(mod) && _a2.isZero(mod) )
            return -1;
        else if(!_a2.isZero(mod))
            return 2;
        else if(!_a1.isZero(mod))
            return 1;
        else if(!_a0.isZero(mod))
            return 0;
    return 0;
    }
//------------------------------------------------------------------------------
	PolynomGF7_mY_3& PolynomGF7_mY_3::setZero(PolynomGF7 &module)
	{
        uint m = module.getNumberBits() - 1;
        std::string s;
        for(int i = 0;i < m; i++)
        {
            s.append("0");
        }
        PolynomGF7 zr(s);
        _a0 = zr;
        _a1 = zr;
        _a2 = zr;

		return *this;
	}

	//simple method
	PolynomGF7_mY_3& PolynomGF7_mY_3::setZero()
	{
        _a0.setZero();
        _a1.setZero();
        _a2.setZero();
		return *this;
	}
    //simple method
	PolynomGF7_mY_3& PolynomGF7_mY_3::setOne()
	{
        _a0.setOne();
        _a1.setZero();
        _a2.setZero();

        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_mY_7, Equal)
	bool operator==(const PolynomGF7_mY_3& a, const PolynomGF7_mY_3& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 )
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF2_mY_7, operatorEqual)
	PolynomGF7_mY_3& PolynomGF7_mY_3::operator= (const PolynomGF7_mY_3& polynom)
	{
        if(this == &polynom)
            return *this;

        _a0 = polynom._a0;
        _a1 = polynom._a1;
        _a2 = polynom._a2;

        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF7_mY_3& a, const PolynomGF7_mY_3& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF7& PolynomGF7_mY_3::getA0() const
  {
    return _a0;
  }
  const PolynomGF7& PolynomGF7_mY_3::getA1() const
  {
    return _a1;
  }
  const PolynomGF7& PolynomGF7_mY_3::getA2() const
  {
    return _a2;
  }

  const PolynomGF7& PolynomGF7_mY_3::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF7& PolynomGF7_mY_3::getModule() const
  {
    return _module;
  }
//------------------------------------------------------------------------------
    void PolynomGF7_mY_3::setA0(const PolynomGF7 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF7_mY_3::setA1(const PolynomGF7 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF7_mY_3::setA2(const PolynomGF7 & a)
    {
        _a2 = a;
        _a2 %= _module;
    }

   void PolynomGF7_mY_3::setModule(const PolynomGF7& module)
    {
        _module = module;
        _a0 %= _module;
        _a1 %= _module;
        _a2 %= _module;

    }
    void PolynomGF7_mY_3::setModPolynom(const PolynomGF7& modPolynom)
    {
        _modPolynom = modPolynom;
        if((modPolynom.getNumberBits()-1)!= 3)
            throw new Exception("модулярные многочлен порождающий расширение поля должны быть степени 7");
    }
//------------------------------------------------------------------------------
//******************************    Операция сложения    ***************************************
	//simple method
	PolynomGF7_mY_3 operator+(const PolynomGF7_mY_3 &a, const PolynomGF7_mY_3 &b)
	{
		PolynomGF7_mY_3 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_mY_3& PolynomGF7_mY_3::operator+=(PolynomGF7_mY_3 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF7_mY_3& PolynomGF7_mY_3::Add(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b)
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
        return *this;
	}
//******************************    Операция умножения    **************************************
	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF7_mY_3& PolynomGF7_mY_3::FullMul(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b)
	{
        PolynomGF7 e0,e;
        PolynomGF7 e1,e1_1,e1_2;
        PolynomGF7 e2,e2_1,e2_2,e2_3;
        PolynomGF7 e3,e3_1,e3_2,e3_3,e3_4;

        if( a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a.getModPolynom();
        _module = a.getModule();
		if(a.isZero() || b.isZero())
  			return setZero();
        e =  a.getA0();
        std::string str = e.ToString();
        str = a.getA1().ToString();
        str = a.getA2().ToString();
        str = b.getA0().ToString();
        str = b.getA1().ToString();
        str = b.getA2().ToString();
        e0.Mul(e,b.getA0());
        e1 = e1_1.Mul(a.getA1(),b.getA0()) + e1_2.Mul(a.getA0(), b.getA1());
        e2 = e2_1.Mul(a.getA2(),b.getA0()) + e2_2.Mul(a.getA1(),b.getA1()) + e2_3.Mul(a.getA0(),b.getA2());

        str = e0.ToString();
        uint m = a._module.getNumberBits() - 1;
        uint l = str.length();
        if(l < m)
        {
                for(unsigned int i = 0; i < m - l; i++)
                        str.append("0");
                PolynomGF7 r(str);
                e0 = r;
                str = e0.ToString();
        }
        str = e1.ToString();
        m = a._module.getNumberBits() - 1;
        l = str.length();
        if(l < m)
        {
                for(unsigned int i = 0; i < m - l; i++)
                        str.append("0");
                PolynomGF7 r(str);
                e1 = r;
                str = e1.ToString();
        }
        str = e2.ToString();
        m = a._module.getNumberBits() - 1;
        l = str.length();
        if(l < m)
        {
                for(unsigned int i = 0; i < m - l; i++)
                        str.append("0");
                PolynomGF7 r(str);
                e2 = r;
                str = e2.ToString();
        }

        _a0 = e0;
        std::string s = _a0.ToString();
        _a1 = e1;
        s = _a1.ToString();
        _a2 = e2;
        s = _a2.ToString();

		return *this;
        }
    PolynomGF7_mY_3& PolynomGF7_mY_3::MonomialMul(PolynomGF7_mY_3 &a, PolynomGF7 &b)
    {
        PolynomGF7 e0;
        PolynomGF7 e1;
        PolynomGF7 e2;
        PolynomGF7 a0,a1,a2;
        PolynomGF7 b0;

//        if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a._modPolynom;
        _module = a._module;
		if(a.isZero() || b.isZero())
  			return setZero();
        a0 = a.getA0();
        a1 = a.getA1();
        a2 = a.getA2();

        b0 = b;

        e0.Mul(a0,b0);
        e1 = e1.Mul(a1,b0);
        e2 = e2.Mul(a2,b0);

        _a0 = e0;
        std::string s = _a0.ToString();
        _a1 = e1;
        s = _a1.ToString();
         _a2 = e2;
        s = _a2.ToString();
		return *this;
    }

    PolynomGF7_mY_3& PolynomGF7_mY_3::NormalMonomialMul(PolynomGF7_mY_3 &aa, int d)
    {
              PolynomGF7 e1;
              PolynomGF7_mY_3 result,a;
              PolynomGF7 module;
              std::string o_st,st;
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

              if(a.deg() + d > 3)
                        throw new Exception("ошибка deg(a) + d должнобыть <= 12");
              for(int i = 0; i < d; i++)
              {
                PolynomGF7 z(o_st);
                e1 = z;
                //(o_st,o_st,module.ToString());
                setByIndex(e1,i);
                st = _a0.ToString();
              }
              int j = 0;
             std::string ss = "",s;
              for(int i = d; i <= 3; i++)
              {
                e1 = a.getByIndex(j);
                s = e1.ToString();
                if(e1.ToString() == o_st)
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

		return *this;
    }

    const PolynomGF7& PolynomGF7_mY_3::getByIndex(int index) const
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
    }

    void PolynomGF7_mY_3::setByIndex(const PolynomGF7 & a, int index)
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

    }
    PolynomGF7_mY_3& PolynomGF7_mY_3::Div(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b, PolynomGF7 &module, PolynomGF7_mY_3 *remainder)
    {
        PolynomGF7_mY_3 q,r,_a,_bb,two("600","000","000",module.ToString());
       // PolynomGF7_m_2 sx("6","0",module.ToString());
         //two.setByIndex(sx,0);
         two.setModule(module);
         two._modPolynom = a._modPolynom;
        PolynomGF7 p;
        PolynomGF7 _q,_b,_inv;//("000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000",module.ToString()),_b,_inv;
        std::string s;
        q._module = module;
        q.setZero(module);
        r._module = module;
        _a = a;
        _bb = b;
            s = _a.getA0().ToString();
            s = _a.getA1().ToString();
            s = _a.getA2().ToString();

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
            //p.exist(_q,module);
            PolynomGF7_mY_3 _c;
            _c._module = module;
            _c._modPolynom = a._modPolynom;
            _c = MonomialMul( _bb, p);
            _c = NormalMonomialMul(_c,d);

            _a = _a + _c.FullMul(_c,two);
            r = _a;
            s = _a.getA0().ToString();
            s = _a.getA1().ToString();
            s = _a.getA2().ToString();

            deg_a = _a.deg();
        }
            s = r._a0.ToString();
            s = r._a1.ToString();
            s = r._a2.ToString();

            s = q._a0.ToString();
            s = q._a1.ToString();
            s = q._a2.ToString();

        *this = q;
         *remainder = r;
         return *this;
    }

PolynomGF7_mY_3& PolynomGF7_mY_3::GCD(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b, PolynomGF7 &module)
{
    PolynomGF7_mY_3 c,r,d;
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

   return  *this;
}

};


