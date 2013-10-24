/*
        MPEI Algebraic Abstractions Library,
        2007-2011,
        Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF2_m_4.h"
#include "Polynom.h"
#include "Converter.h"
#include "Algorithms.h"
#include "Matrix.h"
#include "TableManager.h"
#include <stdlib.h>
#include <math.h>
#include "DecompositionManager.h"
#include "PolynomGF2_mY_7.h"
namespace AAL
{
 //***********************************  Конструкторы  *******************************************
    //(c) Belova, TEST(PolynomGF2_m_4, EmptyConstructor)
/*  PolynomGF2_m_4::PolynomGF2_m_4() :
        _a0(), _a1(), _a2(), _a3(), _module(), _modPolynom("11001")
        {
        }   */
//------------------------------------------------------------------------------
    //(c) Belova, TEST(PolynomGF2_m_4, CopyConstructor)
    PolynomGF2_m_4::PolynomGF2_m_4(const PolynomGF2_m_4 &polynom)
    {
     _a0 = polynom._a0;
     _a1 = polynom._a1;
     _a2 = polynom._a2;
     _a3 = polynom._a3;
     _module = polynom._module;
     _modPolynom = polynom._modPolynom;
    }
//------------------------------------------------------------------------------

    //(c) Belova, TEST(PolynomGF2_m_4, StringConstructor)
    PolynomGF2_m_4::PolynomGF2_m_4(const std::string a0,
     const std::string a1, const std::string a2,
     const std::string a3, const std::string module):
     _a0(a0), _a1(a1), _a2(a2), _a3(a3), _module(module), _modPolynom("11001")
    {
    }
//------------------------------------------------------------------------------
    bool PolynomGF2_m_4::isZero() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero())
            return true;
        return false;
    }
    bool PolynomGF2_m_4::isOne() const
    {
        std::string s0,s1,s2,s3;
        s0 = _a0.ToString();
        s1 = _a1.ToString();
        s2 = _a2.ToString();
        s3 = _a3.ToString();
        if(_a0.isOne() && _a1.isZero() && _a2.isZero() && _a3.isZero())
            return true;
        return false;
    }
//------------------------------------------------------------------------------

    //simple method
    PolynomGF2_m_4& PolynomGF2_m_4::setZero()
    {
        _a0.setZero();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        return *this;
    }
    //simple method
    PolynomGF2_m_4& PolynomGF2_m_4::setOne()
    {
        _a0.setOne();
        _a1.setZero();
        _a2.setZero();
        _a3.setZero();
        return *this;
    }
//------------------------------------------------------------------------------

    //(c) Belova, TEST(PolynomGF2_m_4, Equal)
    bool operator==(const PolynomGF2_m_4& a, const PolynomGF2_m_4& b)
    {
        if(a._a0 == b._a0 && a._a1 == b._a1 && a._a2 == b._a2 && a._a3 == b._a3)
            return true;
        return false;
    }
//------------------------------------------------------------------------------
    //(c) Belova, TEST(Polynom, operatorEqual)
    PolynomGF2_m_4& PolynomGF2_m_4::operator= (const PolynomGF2_m_4& polynom)
    {
        if(this == &polynom)
            return *this;

        _a0 = polynom._a0;
        _a1 = polynom._a1;
        _a2 = polynom._a2;
        _a3 = polynom._a3;
        _modPolynom = polynom._modPolynom;
        _module=polynom._module;
        return *this;
    }
//------------------------------------------------------------------------------
//simple method
    bool operator!=(const PolynomGF2_m_4& a, const PolynomGF2_m_4& b)
    {
        return !(a == b);
    }
//------------------------------------------------------------------------------
  const Polynom& PolynomGF2_m_4::getA0() const
  {
    return _a0;
  }
  const Polynom& PolynomGF2_m_4::getA1() const
  {
    return _a1;
  }
  const Polynom& PolynomGF2_m_4::getA2() const
  {
    return _a2;
  }
  const Polynom& PolynomGF2_m_4::getA3() const
  {
    return _a3;
  }
  const Polynom& PolynomGF2_m_4::getModPolynom() const
  {
    return _modPolynom;
  }
  const Polynom& PolynomGF2_m_4::getModule() const
  {
    return _module;
  }
//------------------------------------------------------------------------------
    void PolynomGF2_m_4::setA0(const Polynom & a)
    {
        _a0 = a;
        _a0 %= _module;
    }
    void PolynomGF2_m_4::setA1(const Polynom & a)
    {
        _a1 = a;
        _a1 %= _module;
    }
    void PolynomGF2_m_4::setA2(const Polynom & a)
    {
        _a2 = a;
        _a2 %= _module;
    }
    void PolynomGF2_m_4::setA3(const Polynom & a)
    {
        _a3 = a;
        _a3 %= _module;
    }
    void PolynomGF2_m_4::setModule(const Polynom& module)
    {
        _module = module;
        _a0 %= _module;
        _a1 %= _module;
        _a2 %= _module;
        _a3 %= _module;
    }
    void PolynomGF2_m_4::setModPolynom(const Polynom& modPolynom)
    {
        _modPolynom = modPolynom;
        if((modPolynom.getNumberBits()-1)!=4)
            throw std::out_of_range("модулярные многочлен порождающий расширение поля должны быть степени 4");
    }
//------------------------------------------------------------------------------
//******************************    Операция сложения    ***************************************
    //simple method
    PolynomGF2_m_4 operator+(const PolynomGF2_m_4 &a, const PolynomGF2_m_4 &b)
    {
        PolynomGF2_m_4 result, copy_a(a), copy_b(b);
        return result.Add(copy_a, copy_b);
    }
//------------------------------------------------------------------------------

    //simple method
    PolynomGF2_m_4& PolynomGF2_m_4::operator+=(PolynomGF2_m_4 &polynom)
    {
        return Add(*this, polynom);
    }
//------------------------------------------------------------------------------

    //simple method
    PolynomGF2_m_4& PolynomGF2_m_4::Add(PolynomGF2_m_4 &a, PolynomGF2_m_4 &b)
    {
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
         if(a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");
        _modPolynom = a._modPolynom;
        _module=a._module;
        _a0.ModAdd(a._a0, b._a0, _module);
        std::string s = _a0.ToString();
        _a1.ModAdd(a._a1, b._a1, _module);
        s = _a1.ToString();
        _a2.ModAdd(a._a2, b._a2, _module);
        s = _a2.ToString();
        _a3.ModAdd(a._a3, b._a3, _module);
         s = _a3.ToString();
        return *this;
    }
//******************************    Операция умножения    **************************************
    //simple method
    PolynomGF2_m_4 operator*(const PolynomGF2_m_4 &a, const PolynomGF2_m_4 &b)
    {
        PolynomGF2_m_4 result;
        PolynomGF2_m_4 copy_a(a), copy_b(b);
        return result.Mul(copy_a, copy_b);
    }
//------------------------------------------------------------------------------

    //simple method
    PolynomGF2_m_4& PolynomGF2_m_4::operator*=(PolynomGF2_m_4 &polynom)
    {
        return Mul(*this, polynom);
    }
//------------------------------------------------------------------------------

    // (c) Morozov, TEST(PolynomGF2_m_4, Mul)
    PolynomGF2_m_4& PolynomGF2_m_4::Mul(PolynomGF2_m_4 &a, PolynomGF2_m_4 &b)
    {
        Polynom e0;
        Polynom e1,e11,e12;
        Polynom e2,e21,e22,e23;
        Polynom e3,e31,e32,e33,e34;
        Polynom e4, e41,e42,e43;
        Polynom e5,e51,e52,e6;
        if(a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
                        throw new Exception("модулярные многочлены должны быть равны");
         if(a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        _modPolynom = a._modPolynom;
        _module = a._module;
        if(a.isZero() || b.isZero())
            return setZero();
        e0.ModMul(a._a0,b._a0, _module);
        e1 = e1.ModMul(a._a1,b._a0,_module) + e2.ModMul(a._a0, b._a1, _module);
        e2 = e21.ModMul(a._a2,b._a0,_module) + e22.ModMul(a._a1,b._a1,_module) + e23.ModMul(a._a0,b._a2,_module);
        e3 = e31.ModMul(a._a3,b._a0,_module) + e32.ModMul(a._a2,b._a1,_module) + e33.ModMul(a._a1,b._a2,_module) + e34.ModMul(a._a0,b._a3,_module);
        e4 = e41.ModMul(a._a1,b._a3,_module) + e42.ModMul(a._a2,b._a2,_module) + e43.ModMul(a._a3,b._a1,_module);
        e5 = e51.ModMul(a._a2,b._a3,_module) + e52.ModMul(a._a3,b._a2,_module);
        e6.ModMul(a._a3,b._a3,_module);
        _a0 = e0 + e4;
        std::string s = _a0.ToString();
        _a1 = e1 + e4 + e5;
        s  =  _a1.ToString();
        _a2 = e2 + e5 + e6;
        s = _a2.ToString();
        _a3 = e3 + e6;
        s = _a3.ToString();
        return *this;
    }
// простой метод возведения в степень 2 по модулю
    PolynomGF2_m_4& PolynomGF2_m_4::Square(PolynomGF2_m_4 &a)
    {
        Polynom e0;
        Polynom e2,e22;
        Polynom e4,e42;
        Polynom e6;
        _modPolynom = a._modPolynom;
        _module = a._module;
        if(a.isZero())
            return setZero();
         if(a.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        e0.ModMul(a._a0,a._a0, _module);
        e2 = e22.ModMul(a._a1,a._a1,_module);
        e4 = e42.ModMul(a._a2,a._a2,_module);
        e6.ModMul(a._a3,a._a3,_module);
        _a0 = e0 + e4;
        std::string s = _a0.ToString();
        _a1 = e4;
        s = _a1.ToString();
        _a2 = e2 + e6;
        s = _a2.ToString();
        _a3 = e6;
        s = _a3.ToString();
        return *this;
    }
  //возведение в степень
  PolynomGF2_m_4& PolynomGF2_m_4::Pow(PolynomGF2_m_4 &a, Integer n)
  {
    if(n.isNegative())
        throw new Exception("Число n - отрицательное результат не определен");
    if(n == 1)
    {
        *this = a;
        return *this;
    }
    if(a.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

    _modPolynom = a._modPolynom;
    _module=a._module;
    PolynomGF2_m_4 c,result("1","0","0","0",a._module.ToString());
    std::string m = a._module.ToString();
    PolynomGF2_m_4 one("1","0","0","0",a._module.ToString());
    Integer copy_n(n);
    //result.setOne();
    uint s = copy_n.getNumberBits();
    for(uint i=0;i<s;i++)
    {
        c = result*result;
        result = c;
        if(copy_n.getBit(s - 1 - i))
            result.Mul(result,a);
        else
            result *= one;
    }
    *this = result;
    std::string st = _a0.ToString();
    st = _a1.ToString();
    st = _a2.ToString();
    st = _a3.ToString();
    return *this;
  }
  //инвертирование
  //------------------------------------------------------------------------------

    //simple method
    PolynomGF2_m_4& PolynomGF2_m_4::Inverse(Polynom &module)
    {
        return Inverse(*this, module);
    }
  //определение степени многочлена
    int PolynomGF2_m_4::deg() const
    {
        if(_a0.isZero() && _a1.isZero() && _a2.isZero() && _a3.isZero())
            return -1;
        else if(!_a3.isZero())
            return 3;
        else if(!_a2.isZero())
            return 2;
        else if(!_a1.isZero())
            return 1;
        else if(!_a0.isZero())
            return 0;
    }
     const Polynom& PolynomGF2_m_4::getByIndex(int index) const
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
    }
    void PolynomGF2_m_4::setByIndex(const Polynom & a, int index)
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
    }

//------------------------------------------------------------------------------

    //(c) Belova, TEST(PolynomGF2_m_4, Inverse)
    PolynomGF2_m_4& PolynomGF2_m_4::Inverse(PolynomGF2_m_4 &polynom, Polynom &module)
    {
                 if(polynom.getModPolynom().isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        PolynomGF2_mY_7 d2("0","0","0","0","0","0","0",module.ToString()),d1("1","0","0","0","0","0","0",module.ToString()),w1;
        PolynomGF2_mY_7 u("1","1","0","0","1","0","0",module.ToString()),w,r,c,_c;
        int d = 0;
        PolynomGF2_m_4 result,rr;
        Polynom _u,_v,inv,_q,_b,pp;

        PolynomGF2_mY_7 vv,d11;
         d1.setModule(module);
        d2.setModule(module);
        u.setModule(module);
         std::string s;
         PolynomGF2_mY_7 v(polynom._a0.ToString(),polynom._a1.ToString(),polynom._a2.ToString(),polynom._a3.ToString(),"0","0","0",module.ToString());
        v.setModule(module);

        while(v.deg() != 0 && v.isZero() != true)
        {
            if(u.deg() < v.deg())
            {
                    w = u;
                   s = u.getA0().ToString();
                   s = u.getA1().ToString();
                   s = u.getA2().ToString();
                   s = u.getA3().ToString();
                   s = u.getA4().ToString();
                   s = u.getA5().ToString();
                    u = v;
                   s = v.getA0().ToString();
                   s = v.getA1().ToString();
                   s = v.getA2().ToString();
                   s = v.getA3().ToString();
                   s = v.getA4().ToString();
                   s = v.getA5().ToString();
                    v = w;
                   s = w.getA0().ToString();
                   s = w.getA1().ToString();
                   s = w.getA2().ToString();
                   s = w.getA3().ToString();
                   s = w.getA4().ToString();
                   s = w.getA5().ToString();
                    w1 = d1;
                   s = d1.getA0().ToString();
                   s = d1.getA1().ToString();
                   s = d1.getA2().ToString();
                   s = d1.getA3().ToString();
                   s = d1.getA4().ToString();
                   s = d1.getA5().ToString();
                    d1 = d2;
                   s = d2.getA0().ToString();
                   s = d2.getA1().ToString();
                   s = d2.getA2().ToString();
                   s = d2.getA3().ToString();
                   s = d2.getA4().ToString();
                   s = d2.getA5().ToString();

                    d2 = w1;
            }
            d = u.deg() - v.deg();
            _v = v.getByIndex(v.deg());
            s = _v.ToString();
            _v = inv.Inverse(_v,module);
            s = _v.ToString();
            _q.ModMul(Polynom(u.getByIndex(u.deg())),inv,module);
            s = _q.ToString();
            PolynomGF2_mY_7 q;
            q.setModule(module);
            q.setByIndex(_q,0);
                   s = q.getA0().ToString();
                   s = q.getA1().ToString();
                   s = q.getA2().ToString();
                   s = q.getA3().ToString();
                   s = q.getA4().ToString();
                   s = q.getA5().ToString();
            q = q.NormalMonomialMul(q,d);
                   s = q.getA0().ToString();
                   s = q.getA1().ToString();
                   s = q.getA2().ToString();
                   s = q.getA3().ToString();
                   s = q.getA4().ToString();
                   s = q.getA5().ToString();

            r = u + vv.FullMul(v,q);
                   s = r.getA0().ToString();
                   s = r.getA1().ToString();
                   s = r.getA2().ToString();
                   s = r.getA3().ToString();
                   s = r.getA4().ToString();
                   s = r.getA5().ToString();

            c = d2 + d11.FullMul(d1,q);
                   s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();
                   s = c.getA3().ToString();
                   s = c.getA4().ToString();
                   s = c.getA5().ToString();


            u = v;
                   s = u.getA0().ToString();
                   s = u.getA1().ToString();
                   s = u.getA2().ToString();
                   s = u.getA3().ToString();
                   s = u.getA4().ToString();
                   s = u.getA5().ToString();

            v = r;
                   s = v.getA0().ToString();
                   s = v.getA1().ToString();
                   s = v.getA2().ToString();
                   s = v.getA3().ToString();
                   s = v.getA4().ToString();
                   s = v.getA5().ToString();

            d2 = d1;
                   s = d2.getA0().ToString();
                   s = d2.getA1().ToString();
                   s = d2.getA2().ToString();
                   s = d2.getA3().ToString();
                   s = d2.getA4().ToString();
                   s = d2.getA5().ToString();

            d1 = c;
                   s = d1.getA0().ToString();
                   s = d1.getA1().ToString();
                   s = d1.getA2().ToString();
                   s = d1.getA3().ToString();
                   s = d1.getA4().ToString();
                   s = d1.getA5().ToString();

        }
            Polynom p,e0,e4,e01,e41,e42,e43;
            e0 = e01.ModMul(polynom._a0,c.getA0(),polynom._module);
            e4 = e41.ModMul(polynom._a1,c.getA3(),polynom._module) + e42.ModMul(polynom._a2,c.getA2(),polynom._module) + e43.ModMul(polynom._a3,c.getA1(),polynom._module);
            p = e0+e4;
            s = p.ToString();
            _b.Inverse(p,module);
            s = _b.ToString();
            PolynomGF2_m_4 cc;
            cc.setModule(module);
            cc.setByIndex(_b,0);
                   s = cc.getA0().ToString();
                   s = cc.getA1().ToString();
                   s = cc.getA2().ToString();
                   s = cc.getA3().ToString();
            c = _c.MonomialMul(c,cc);
                   s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();
                   s = c.getA3().ToString();
                   s = c.getA4().ToString();
                   s = c.getA5().ToString();
/*        c = c.FullMul(c,c);
                   s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();
                   s = c.getA3().ToString();
                   s = c.getA4().ToString();
                   s = c.getA5().ToString(); */
        result._a0 = c.getA0();
        result._a1 = c.getA1();
        result._a2 = c.getA2();
        result._a3 = c.getA3();
        result._module = c.getModule();
        *this = result;
        return *this;
    }
   // извлечение квадратного корня
   PolynomGF2_m_4& PolynomGF2_m_4::Sqrt(PolynomGF2_m_4 &a, Polynom &module)
   {
        PolynomGF2_m_4 result;
        uint m = module.getNumberBits() - 1;
        Integer power("1");
        power.Pow(2,(4*m)-1);
        //power = (power - 1);///2;
        result.Pow(a, power);

        *this = result;
        return *this;
   }
   //тест образующего элемента, определение порядка элемента
   Integer& PolynomGF2_m_4::elementOrder(Polynom &groupModule, PolynomGF2_m_4 &polynom,std::vector<DecompositionMember> vector, const Integer &ord )
{
  if(!groupModule.isIrreducible()) throw new Exception("Модуль должен быть неприводим.");
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    Polynom *m  = new Polynom(groupModule);
    PolynomGF2_m_4 *a = new PolynomGF2_m_4(polynom);
    Integer t =  ord;
    for(it = vector.begin(); it != vector.end();it++)
   {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.ModPow(p,e,ord);
      std::string s = ex.ToString();
      t = t/(ex);
      PolynomGF2_m_4 a1;
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
bool PolynomGF2_m_4::isGenerator(Polynom &groupModule, PolynomGF2_m_4 &polynom,std::vector<DecompositionMember> vector, const Integer &ord)
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
void PolynomGF2_m_4::exist(Polynom &a, Polynom& module)
{
    _a0 = a;
    _a1.setZero();
    _a2.setZero();
    _a3.setZero();
    _module = module;
}
//-----------------------------------------------------------------------------------
};

