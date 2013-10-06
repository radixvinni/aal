/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF7_m_2.h"
#include "PolynomGF7_mY_3.h"
#include "PolynomGF7.h"
#include "Converter.h"
#include "Integer.h"
#include "DecompositionManager.h"
#include <string.h>
#include <stdlib.h>
namespace AAL
{
  int PolynomGF7_m_2::sevendiv(std::vector<Integer>* m, Integer n)
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
	PolynomGF7_m_2::PolynomGF7_m_2() :
        _a0(), _a1(), _module(), _modPolynom("101")
        {
        }
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, CopyConstructor)
	PolynomGF7_m_2::PolynomGF7_m_2(const PolynomGF7_m_2 &polynom)
	{
     _a0 = polynom._a0;
     _a1 = polynom._a1;
     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, StringConstructor)
	PolynomGF7_m_2::PolynomGF7_m_2(const std::string a0,
     const std::string a1, const std::string module):
     _a0(a0), _a1(a1),_module(module), _modPolynom("101")
	{
	}
//------------------------------------------------------------------------------
    bool PolynomGF7_m_2::isZero() const
    {
        if(_a0.isZero() && _a1.isZero())
            return true;
        return false;
    }
    bool PolynomGF7_m_2::isZero(PolynomGF7 &module) const
    {
        if(_a0.isZero(module) && _a1.isZero(module))
            return true;
        return false;
    }

    bool PolynomGF7_m_2::isOne() const
    {
        if(_a0.isOne() && _a1.isZero())
            return true;
        return false;
    }
//------------------------------------------------------------------------------
	PolynomGF7_m_2& PolynomGF7_m_2::setZero()
	{
        _a0.setZero();
        _a1.setZero();
		return *this;
	}
	PolynomGF7_m_2& PolynomGF7_m_2::setZero(PolynomGF7 &module)
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
		return *this;
	}

    //simple method
	PolynomGF7_m_2& PolynomGF7_m_2::setOne()
	{
        _a0.setOne();
        _a1.setZero();
        return *this;
    }
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF3_m_6, Equal)
	bool operator==(const PolynomGF7_m_2& a, const PolynomGF7_m_2& b)
	{
		if(a._a0 == b._a0 && a._a1 == b._a1)
			return true;
		return false;
	}
//------------------------------------------------------------------------------
	//(c) Belova, TEST(PolynomGF3_m_6, operatorEqual)
	PolynomGF7_m_2& PolynomGF7_m_2::operator= (const PolynomGF7_m_2& polynom)
	{
        if(this == &polynom)
            return *this;

        _a0 = polynom._a0;
        _a1 = polynom._a1;
        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
	}
//------------------------------------------------------------------------------
//simple method
	bool operator!=(const PolynomGF7_m_2& a, const PolynomGF7_m_2& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------
  const PolynomGF7& PolynomGF7_m_2::getA0() const
  {
    return _a0;
  }
  const PolynomGF7& PolynomGF7_m_2::getA1() const
  {
    return _a1;
  }
  const PolynomGF7& PolynomGF7_m_2::getModPolynom() const
  {
    return _modPolynom;
  }
  const PolynomGF7& PolynomGF7_m_2::getModule() const
  {
    return _module;
  }

//------------------------------------------------------------------------------
    void PolynomGF7_m_2::setA0(const PolynomGF7 & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF7_m_2::setA1(const PolynomGF7 & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF7_m_2::setModule(const PolynomGF7& module)
    {
        _module = module;
        _a0 %= _module;
        _a1 %= _module;
    }
    void PolynomGF7_m_2::setModPolynom(const PolynomGF7& modPolynom)
    {
        _modPolynom = modPolynom;
     //   if((modPolynom.getNumberBits()-1)!=14)
       //     throw std::out_of_range("модул€рные многочлен порождающий расширение пол€ должны быть степени 14");
    }
//------------------------------------------------------------------------------
//******************************    ќпераци€ сложени€    ***************************************
	//simple method
	PolynomGF7_m_2 operator+(const PolynomGF7_m_2 &a, const PolynomGF7_m_2 &b)
	{
		PolynomGF7_m_2 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m_2& PolynomGF7_m_2::operator+=(PolynomGF7_m_2 &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

    //simple method
	PolynomGF7_m_2& PolynomGF7_m_2::Add(PolynomGF7_m_2 &a, PolynomGF7_m_2 &b)
	{
        if(a.getModule() != b.getModule())
                        throw std::out_of_range("модул€рные многочлены должны быть равны");
 //       if(a.getModule().isIrreducible() == false || b.getModule().isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module=a._module;
        _a0.ModAdd(a._a0, b._a0,_module);
  //      std::string s = _a0.ToString();
        _a1.ModAdd(a._a1, b._a1,_module);
   //     s = _a1.ToString();
        return *this;
	}
	//simple method
	PolynomGF7_m_2 operator*(const PolynomGF7_m_2 &a, const PolynomGF7_m_2 &b)
	{
		PolynomGF7_m_2 result;
        PolynomGF7_m_2 copy_a(a), copy_b(b);
 		return result.Mul(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m_2& PolynomGF7_m_2::operator*=(PolynomGF7_m_2 &polynom)
	{
		return Mul(*this, polynom);
	}
//------------------------------------------------------------------------------

	// (c) Morozov, TEST(PolynomGF2_m_4, Mul)
	PolynomGF7_m_2& PolynomGF7_m_2::Mul(PolynomGF7_m_2 a, PolynomGF7_m_2 b)
	{
                PolynomGF7 module = a._module;
                PolynomGF7 copy_a(a._a0),copy_b(b._a0),copy_c(a._a1),copy_d(b._a1);
                PolynomGF7 e,gg("0"),r1("0"),r2("0"),six("6");
                PolynomGF7 e1("0"),e2("0"),e3("0"),e4("0");
                e1.ModMul(a._a0,b._a0,module);
                e2.ModMul(a._a0,b._a1,module);
                e3.ModMul(a._a1,b._a0,module);
                e4.ModMul(a._a1,b._a1,module);
                r1.ModMul(e4,six,module);
                r2 = e1 + r1;
                gg = e2 + e3;
                std::string s = gg.ToString();
                s = r2.ToString();
                _a0 = r2;
                _a1 = gg;
                _module = module;
                s = _module.ToString();
                _modPolynom = a._modPolynom;

		return *this;
	}

  //возведение в степень
  PolynomGF7_m_2& PolynomGF7_m_2::Pow(PolynomGF7_m_2 &a, const Integer &n)
  {
    if(n.isNegative())
        throw std::domain_error("„исло n - отрицательное результат не определен");
//    if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
    //int len = atoi(n.ToString().c_str());
   std::vector<Integer> m;
    int num_bit;
    num_bit = sevendiv(&m,n);
    std::string s = m[0].ToString();
    _modPolynom = a._modPolynom;
    _module = a._module;
    PolynomGF7_m_2 c,result;//("1","0","0","0","0","0","0","0","0","0","0","0","0",a._module.ToString());
    result.setOne();
    result.setModule(_module);
    //    std::string m1 = a._module.ToString();
    PolynomGF7_m_2 one;("1","0","0","0","0","0","0","0","0","0","0","0","0",a._module.ToString());
    one.setOne();
    one.setModule(_module);
    PolynomGF7_m_2 a_2(a*a),a_3(a*a*a),a_4(a*a*a*a),a_5(a*a*a*a*a),a_6(a*a*a*a*a*a);
    Integer copy_n(n);
    //result.setOne();
    for(int i=1;i<=num_bit+1;i++)
    {
        c = result*result*result*result*result*result*result;
        result = c;
        if(m[num_bit + 1 - i] == 1)
            result.Mul(result,a);
        if(m[num_bit + 1 - i] == 2)
        {
            //a.Pow(a,2);
            result.Mul(result,a_2);
        }
        if(m[num_bit + 1 - i] == 3)
        {
            //a.Pow(a,3);
            result.Mul(result,a_3);
        }
        if(m[num_bit + 1 - i] == 4)
        {
            //a.Pow(a,4);
            result.Mul(result,a_4);
        }
        if(m[num_bit + 1 - i] == 5)
        {
            //a.Pow(a,5);
            result.Mul(result,a_5);
        }
        if(m[num_bit + 1 - i] == 6)
        {
            //a.Pow(a,6);
            result.Mul(result,a_6);
        }
        else
            result *= one;
    }
    *this = result;
    std::string st = _a0.ToString();
    st = _a1.ToString();
    m.clear();
    return *this;
  }
     const PolynomGF7& PolynomGF7_m_2::getByIndex(int index) const
    {
        if(index == 0)
        {
            return _a0;
        }
        else if(index == 1)
        {
            return _a1;
        }
    }
    void PolynomGF7_m_2::setByIndex(const PolynomGF7 & a, int index)
    {
        if(index == 0)
        {
            _a0 = a;
        }
        else if(index == 1)
        {
            _a1 = a;
        }
    }
   //определение степени многочлена
    int PolynomGF7_m_2::deg() const
    {
        if(_a0.isZero() && _a1.isZero()  )
            return -1;
        else if(!_a1.isZero())
            return 1;
        else if(!_a0.isZero())
            return 0;
    }

  //инвертирование
  //------------------------------------------------------------------------------
   // извлечение квадратного корн€
   PolynomGF7_m_2& PolynomGF7_m_2::LegendreSymbol( PolynomGF7_m_2 &a, PolynomGF7 &module)
   {
 //       if(a.getModPolynom().isIrreducible() == false ||module.isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");
       PolynomGF7_m_2 result,minus_one;//("6","0","0","0","0","0","0","0","0","0","0","0","0","");
       PolynomGF7 six("6");
         minus_one.setByIndex(six,0);
         minus_one._module = module;
        _modPolynom = a._modPolynom;
        _module = module;
        uint m = module.getNumberBits() - 1;
        Integer power("1");
        power.Pow(7,(2*m));
        power = (power-1)/2;
        std::string s;
        result.Pow(a,power);
          s = result._a0.ToString();
          s = result._a1.ToString();
        *this = result;
        return *this;
   }
   PolynomGF7_m_2& PolynomGF7_m_2::Sqrt(PolynomGF7_m_2 &x, PolynomGF7 &module,Integer &ss,Integer &T)
   {
 //       if(x.getModule().isIrreducible() == false ||module.isIrreducible() == false)
 //                       throw new Exception("f(x) - должен быть неприводим");

        bool rez;
        Integer s;
        s = ss;
        PolynomGF7_m_2 test;
        PolynomGF7_m_2 zero;//("0","0","0","0","0","0","0","0","0","0","0","0","0",module.ToString());
        zero.setZero();
        zero.setModule(module);
        test.LegendreSymbol(x,module);
        if(test.isOne() != true)
        {
                *this = zero;
                return *this;
        }
        PolynomGF7_m_2 result,a,b,e1,e2,e3,e4,e5;
        result.setOne();
        PolynomGF7_m_2 minus_one;//("6","0","0","0","0","0","0","0","0","0","0","0","0",module.ToString());
        PolynomGF7 six("6");
         minus_one.setByIndex(six,0);
         minus_one._module = module;
        _modPolynom = x._modPolynom;
        _module = module;
        uint m = module.getNumberBits() - 1;
        Integer power("1"),t("0");
        power.Pow(7,(2*m));
        power = (power-1)/2;

        std::string st;
        while(result != minus_one)
        {
          a.Generate(module);
          result.LegendreSymbol(a,module);
        }
        a = a.Pow(a,s);
        st = a._a0.ToString();
        st = a._a1.ToString();


        b = b.Pow(x,Integer(29));
        st = b._a0.ToString();
        st = b._a1.ToString();


        b.setOne();
        b = b.Pow(x,(s-1)/2);
        st = b._a0.ToString();
        st = b._a1.ToString();


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
                if(e5 == minus_one)
                        c = 1;
                if(e5.isOne())
                        c = 0;
                t = t + e.Pow(2,k)*c;
                t0 = t;
                k = k + 1;
        }
        *this = a.Pow(a,t)*b*x;
        s = _a0.ToString();
        s = _a1.ToString();
        return *this;
   }
   //тест образующего элемента, определение пор€дка элемента
   Integer& PolynomGF7_m_2::elementOrder(PolynomGF7 &groupModule, PolynomGF7_m_2 &polynom,std::vector<DecompositionMember> vector, const Integer &ord )
{
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    PolynomGF7 *m  = new PolynomGF7(groupModule);
    PolynomGF7_m_2 *a = new PolynomGF7_m_2(polynom);
    Integer t =  ord;
    for(it = vector.begin(); it != vector.end();it++)
   {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.ModPow(p,e, t);
      std::string s = ex.ToString();
      t = t/(ex);
      PolynomGF7_m_2 a1;
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
bool PolynomGF7_m_2::isGenerator(PolynomGF7 &groupModule, PolynomGF7_m_2 &polynom,std::vector<DecompositionMember> vector, Integer &ord)
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
void PolynomGF7_m_2::exist(PolynomGF7 &a, PolynomGF7& module)
{
    _a0 = a;
    _a1.setZero();
    _module = module;
}
PolynomGF7_m_2& PolynomGF7_m_2::Generate(PolynomGF7& module)
{
        _a0 = _a0.Generate(module);
        _a1 = _a1.Generate(module);
        _module = module;
        return *this;
}

//-----------------------------------------------------------------------------------
	PolynomGF7_m_2 operator%(const PolynomGF7_m_2 &a, const PolynomGF7 &b)
	{
		PolynomGF7_m_2 result, copy_a(a);
                PolynomGF7 copy_b(b);
		return result.Mod(copy_a, copy_b);
	}

	//simple method
	PolynomGF7_m_2& PolynomGF7_m_2::operator%=(PolynomGF7 &polynom)
	{
		return Mod(*this, polynom);
	}

	//(c) Mamontov, TEST(Polynom, Mod)
	PolynomGF7_m_2& PolynomGF7_m_2::Mod(PolynomGF7_m_2 &a, PolynomGF7 &f)
	{
                if(a.isZero() && f.isZero())
		  return setZero();
                _a0.Mod(a._a0,f);
                _a1.Mod(a._a1,f);
		return *this;
	}
//------------------------------------------------------------------------------
  //инвертирование
  //------------------------------------------------------------------------------

	//simple method
	PolynomGF7_m_2& PolynomGF7_m_2::Inverse(PolynomGF7 &module)
	{
		return Inverse(*this, module);
	}
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_m_4, Inverse)
	PolynomGF7_m_2& PolynomGF7_m_2::Inverse(PolynomGF7_m_2 &polynom, PolynomGF7 &module)
	{
//        if(polynom.getModule().isIrreducible() == false || module.isIrreducible() == false)
//                        throw new Exception("f(x) - должен быть неприводим");
       PolynomGF7_mY_3 d2("000","000","000",module.ToString()),d1("100","000","000",module.ToString()),w1;
        PolynomGF7_mY_3 u("100","000","100",module.ToString()),w,r,c,_c;
        PolynomGF7_mY_3 two("600","000","000",module.ToString());
        int d = 0;
        PolynomGF7_m_2 result;
        PolynomGF7 _u,_v,inv,_q,_b,zr("000");
        PolynomGF7_mY_3 v;
        v.setA0(polynom._a0);
        v.setA1(polynom._a1);
        v.setA2(zr);
        PolynomGF7_mY_3 vv,d11;
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
                   s = u.getA0().ToString();
                   s = u.getA1().ToString();
                   s = u.getA2().ToString();


                    u = v;
                   s = v.getA0().ToString();
                   s = v.getA1().ToString();
                   s = v.getA2().ToString();

                    v = w;
                   s = w.getA0().ToString();
                   s = w.getA1().ToString();
                   s = w.getA2().ToString();

                    w1 = d1;
                   s = d1.getA0().ToString();
                   s = d1.getA1().ToString();
                   s = d1.getA2().ToString();


                    d1 = d2;
                   s = d2.getA0().ToString();
                   s = d2.getA1().ToString();
                   s = d2.getA2().ToString();

                    d2 = w1;
            }
            d = u.deg() - v.deg();
            _v = v.getByIndex(v.deg());
            s = _v.ToString();
//            _v = inv.Inverse(_v,module);
            s = _v.ToString();
            _q.Mul(u.getByIndex(u.deg()),inv);
            s = _q.ToString();
            PolynomGF7_mY_3 q;
            q.setModule(polynom._module);
            q.setByIndex(_q,0);
                   s = q.getA0().ToString();
                   s = q.getA1().ToString();
                   s = q.getA2().ToString();

             s = q.getModule().ToString();
            q = q.NormalMonomialMul(q,d);
                   s = q.getA0().ToString();
                   s = q.getA1().ToString();
                   s = q.getA2().ToString();

            PolynomGF7_mY_3 minus;
            //q = minus.FullMul(two,q);
            r = u + vv.FullMul(v,q);
                   s = r.getA0().ToString();
                   s = r.getA1().ToString();
                   s = r.getA2().ToString();

            c = d2 + d11.FullMul(d1,q);
                   s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();


            u = v;
                   s = u.getA0().ToString();
                   s = u.getA1().ToString();
                   s = u.getA2().ToString();


            v = r;
                   s = v.getA0().ToString();
                   s = v.getA1().ToString();
                   s = v.getA2().ToString();


            d2 = d1;
                   s = d2.getA0().ToString();
                   s = d2.getA1().ToString();
                   s = d2.getA2().ToString();


            d1 = c;
                   s = d1.getA0().ToString();
                   s = d1.getA1().ToString();
                   s = d1.getA2().ToString();


        }
            PolynomGF7 p,e0,e6,e01,e61,e62,e63,e64,e65;
            e0 = e01.Mul(polynom._a0,c.getA0());
            e6 = e61.Mul(polynom._a0,c.getA2()) + e62.Mul(polynom._a1,c.getA1()) + e63.Mul(polynom._a1,c.getA0());
            p = e0+e6;
            s = p.ToString();
//            _b.Inverse(p,module);
            s = _b.ToString();
            PolynomGF7_mY_3 cc;
/*           cc.setModule(module);
            cc.setByIndex(_b,0);
                   s = cc.getA0().ToString();
                   s = cc.getA1().ToString();
                   s = cc.getA2().ToString();
*/
            c = _c.MonomialMul(c,_b);
                   s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();


        result._a0 = c.getA0();
        result._a1 = c.getA1();
//        result._a2 = c.getA2();


        result._module = c.getModule();
        *this = result;
        return *this;
    }

};



