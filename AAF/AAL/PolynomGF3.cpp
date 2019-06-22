/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF3.h"
#include "Converter.h"
#include "DecompositionManager.h"
#include <string>
#include <stdlib.h>

namespace AAL
{
//***********************************  Конструкторы  *******************************************
	PolynomGF3::PolynomGF3()// : BasicType<uchar>()
	{}
  PolynomGF3::PolynomGF3(const PolynomGF3 &polynom) //: BasicType<uchar>(polynom)
	{
    A0 = polynom.A0;
    A1 = polynom.A1;
  }

  PolynomGF3::PolynomGF3(const std::string dataString)
	{
		Parse(dataString);
  }
  PolynomGF3::~PolynomGF3()
  {
  }
//**********************************************************************************************

//*************************  Преобразование и считывание из сторк ******************************
	///(c) Mamontov
	PolynomGF3& PolynomGF3::Parse(const std::string dataString)
	{

                std::string polynomA0;
                std::string polynomA1;
                const std::string zero("0");
                const std::string one("1");
                uint length = (uint)dataString.length();
                Polynom buf;
                if(length)
		{
                     for(uint i=0; i<length; i++)
		     {
		          if(dataString[i] == '0')
                          {
		               polynomA1.append(zero);
                               polynomA0.append(zero);
                          }
			  else if(dataString[i] == '1')
                          {
                               polynomA1.append(zero);
                               polynomA0.append(one);
			  }
			  else if(dataString[i] == '2' )
                          {
                               polynomA1.append(one);
                               polynomA0.append(zero);
			  }
                          else
                               throw new Exception("Число задано в непредусмотренном формате");

		     }
		}
                const std::string strA0(polynomA0);
                const std::string strA1(polynomA1);
		A0.Parse(strA0, BackBin);
                A1.Parse(strA1, BackBin);

                return *this;
	}

	//(c) Mamontov
	std::string PolynomGF3::ToString() const
	{
    std::string StringA0;
    std::string StringA1;
    std::string dataString;
    const std::string zero("0");
    const std::string one("1");
		StringA0 = Converter::ToString(A0, BackBin);
    StringA1 = Converter::ToString(A1, BackBin);
    uint lengthA0 = (uint)StringA0.length();
    uint lengthA1 = (uint)StringA1.length();
    uint length;
    uint j = 0;

    if (!A1.isZero() || !A0.isZero())
      {
        if ( lengthA0>=lengthA1)
          {
            length = lengthA0;
            while(j<(lengthA0-lengthA1))
              {
                StringA1 = StringA1 + "0";
                j++;
              };
          }
        else
          {
            length = lengthA1;
            while(j<(lengthA1-lengthA0))
              {
                StringA0 = StringA0 + "0";
                j++;
              };
          }
        for(uint i=0; i<length; i++)
		      {
		        if(StringA0[i] == '0' && StringA1[i] == '0')
              {
		            dataString=dataString + "0";
              }
		        else if(StringA0[i] == '1' && StringA1[i] == '0')
              {
                dataString = dataString + "1";
              }
		        else if(StringA0[i] == '0' && StringA1[i] == '1' )
              {
                dataString = dataString + "2";
		          }
          }
      }
    else
      {
        dataString = "0";
        if( A1.isZero() && A0.isZero() )
        {
          return dataString;
        }
      }
    return dataString;
	}

//**********************************************************************************************
//***************************************  Методы акцепторы   **********************************
       bool PolynomGF3::isZero() const
       {
            if( A0.isZero()&& A1.isZero())
               return true;
            else
               return false;
       }
       bool PolynomGF3::isOne() const
       {
            if( A0.isOne() && A1.isZero() )
               return true;
            else
               return false;
       }
    //(c) Chernysheva
  uint PolynomGF3::getBit(uint index) const
  {
    bool a0bit = A0.getBit(index), a1bit = A1.getBit(index);
    if (!a0bit && !a1bit)
      return 0;
    if (a0bit && a1bit)
      return 0;
    if (!a0bit && a1bit)
      return 2;
    if (a0bit && !a1bit)
      return 1;
  }

  //(c) Chernysheva
  void PolynomGF3::setBit(uint index, uint bit)
  {
    switch(bit)
    {
      case 0:
        A0.setBit(index, false);
        A1.setBit(index, false);
        break;
      case 1:
        A0.setBit(index, true);
        A1.setBit(index, false);
        break;
      case 2:
        A0.setBit(index, false);
        A1.setBit(index, true);
        break;
      default:
        throw new Exception("????? ?????? ? ????????????????? ???????");
        break;
    }
  }


  //(c) Chernysheva, TEST(PolynomGF3, isIrreducible)
	//неприводимость многочлена
	bool PolynomGF3::isIrreducible() const
	{
    uint n = this->getNumberBits() - 1;
    PolynomGF3 q0("01"), qk = q0, plA(*this);
    bool flagNOD = true;
    for (uint k = 1; k <= n; k++)
    {
      qk = (qk * qk * qk) % plA;
      /*qk = qk.Pow(qk, 3);
      qk = qk % plA; */
      std::string str = qk.ToString();
      uint s = n/k;
      Integer integer(s);
      if (s != 1 && s < n && n%s == 0 && n%k == 0 && integer.isPrime())
      {
        if (qk == q0)
          return false;
        else
        {
          PolynomGF3 NOD, polOne("1"), polTwo("2");
          NOD.GCD(qk-q0, plA);
          std::string strNOD = NOD.ToString();
          if (NOD == polOne || NOD == polTwo)
            flagNOD = true;
          else
            return false;
        }
      }
    }
    if (qk == q0.Mod(q0, plA) && flagNOD)
      return true;
    else
      return false;
	}

  //(c) Chernysheva, TEST(PolynomGF3, isPrimitivity)
	//примитивность многочлена, есть разложение только для нечетных
  bool PolynomGF3::isPrimitivity() const
  {
    PolynomGF3 plCur(*this);
    if (plCur.isIrreducible())
    {
      uint n = this->getNumberBits() - 1;
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getThreeDegreeDecomposition(n,false));
      Integer number, mersen;
      PolynomGF3 res("1");
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        if (vector.size() == 1)
          return true;
        number = i->getNumber();
        PolynomGF3 p0("01"), p1;
        mersen = (mersen.Pow(3, n) - 1)/number;
        p1.ModPow(p0, mersen, plCur);
        if (p1 == res)
          return false;
      }
      return true;
    }
    else
      return false;
  }

//************************************  Унарные операции   *************************************
	//(c) Mamontov, TEST(Polynom, operatorEqual)
	PolynomGF3& PolynomGF3::operator= (const PolynomGF3& polynom)
	{
		A0 = polynom.A0;
                A1 = polynom.A1;
		return *this;
	}
//**********************************************************************************************

//***************************************  Методы акцепторы   **********************************
	//simple method
	PolynomGF3& PolynomGF3::setOne()
	{
		A0.setOne();
                A1.setZero();
		return *this;
	}

        	//simple method
	PolynomGF3& PolynomGF3::setTwo()
	{
		A0.setZero();
                A1.setOne();
		return *this;
	}
	//simple method
	PolynomGF3& PolynomGF3::setZero()
	{
		A0.setZero();
                A1.setZero();
		return *this;
	}

//**********************************************************************************************

//*****************************    Операции сравнения    ***************************************
	//(c) Mamontov, TEST(Polynom, Equal)
	bool operator==(const PolynomGF3& a, const PolynomGF3& b)
	{
		if((a.A0==b.A0) && (a.A1==b.A1))// && a.CmpImpl(b) == Equal )
			return true;
		return false;
	}

      	//simple method
	bool operator!=(const PolynomGF3& a, const PolynomGF3& b)
	{
		return !(a == b);
	}

      	//(c) Mamontov, TEST(Polynom, Smaller)
	bool operator<(const PolynomGF3& a, const PolynomGF3& b)
	{
		if(a.isZero())
			return !b.isZero();
		if(b.isZero())
			return !a.isZero();

                if (a.getNumberBits()< b.getNumberBits())
		    return true;
                else
                    return false;

        }

       //simple method
	bool operator<=(const PolynomGF3& a, const PolynomGF3& b)
	{
		return !(b < a);
	}

	//simple method
	bool operator>(const PolynomGF3& a, const PolynomGF3& b)
	{
		return b < a;
	}
	bool operator>=(const PolynomGF3& a, const PolynomGF3& b)
	{
		return !(a < b);
	}
//**********************************************************************************************

//***************************    Операции побитового сдвига    *********************************
	//simple method
	PolynomGF3 PolynomGF3::operator<<(int numberBits) const
	{
		PolynomGF3 result(*this);
		return result<<=numberBits;
	}

	//(c) Mamontov, TEST(Polynom, SHL)
	PolynomGF3& PolynomGF3::operator<<=(int numberBits)
	{
	        A0<<=numberBits;
                A1<<=numberBits;
		return *this;
	}

	//simple method
	PolynomGF3 PolynomGF3::operator>>(int numberBits) const
	{
		PolynomGF3 result(*this);
		return result>>=numberBits;
	}

	//(c) Mamontov, TEST(Polynom, SHR)
	PolynomGF3& PolynomGF3::operator>>=(int numberBits)
	{
	        A0>>=numberBits;
                A1>>=numberBits;
                return *this;
	}
//**********************************************************************************************


//******************************    Операция сложения    ***************************************
	//simple method
	PolynomGF3 operator+(const PolynomGF3 &a, const PolynomGF3 &b)
	{
		PolynomGF3 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}

	//simple method
	PolynomGF3& PolynomGF3::operator+=(PolynomGF3 &polynom)
	{
		return Add(*this, polynom);
	}

	//simple method
	PolynomGF3& PolynomGF3::Add(PolynomGF3 &a, PolynomGF3 &b)
	{
                Polynom T;
                Polynom buf;
                PolynomGF3 copy_a(a), copy_b(b);

                T = (copy_a.A1 | copy_b.A0)+(copy_a.A0 | copy_b.A1);
                A1 = (copy_a.A0 | copy_b.A0)+T;
                A0 = (copy_a.A1 | copy_b.A1)+T;

		return *this;
	}
  PolynomGF3& PolynomGF3::ModAdd(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module)
  {
    PolynomGF3 copy_a(a), copy_b(b);
    return Add(copy_a, copy_b) %= module;
  }
  PolynomGF3& PolynomGF3::AddInGF3_n(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module)
  {
    if(module.isIrreducible())
    {
      PolynomGF3 copy_a(a), copy_b(b);
      return Add(copy_a, copy_b) %= module;
    }
    else
      throw new Exception("f(x) должен быть неприводимым.");
  }

//**********************************************************************************************

//******************************    Операция вычитания    **************************************
	//simple method
	PolynomGF3 operator-(const PolynomGF3 &a, const PolynomGF3 &b)
	{
		PolynomGF3 result, copy_a(a), copy_b(b);
		return result.Sub(copy_a, copy_b);
	}

	//simple method
	PolynomGF3& PolynomGF3::operator-=(PolynomGF3 &polynom)
	{
		return Sub(*this, polynom);
	}

	//simple method
	PolynomGF3& PolynomGF3::Sub(PolynomGF3 &a, PolynomGF3 &b)
	{
                Polynom buf;
                PolynomGF3 copy_a(a), copy_b(b);

                buf = copy_b.A0;
                copy_b.A0 = copy_b.A1;
                copy_b.A1 = buf;

		return Add(copy_a, copy_b);
	}
	PolynomGF3& PolynomGF3::ModSub(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module)
	{
		PolynomGF3 copy_a(a), copy_b(b);
		return Sub(copy_a, copy_b) %= module;
	}

//**********************************************************************************************

//******************************    Операция умножения    **************************************

        //simple method
	PolynomGF3 operator*(const PolynomGF3 &a, const PolynomGF3 &b)
	{
		PolynomGF3 result, copy_a(a), copy_b(b);
		return result.Mul(copy_a, copy_b);
	}

	//simple method
	PolynomGF3& PolynomGF3::operator*=(PolynomGF3 &polynom)
	{
		return Mul(*this, polynom);
	}

        // Функция реализующая умножение многочленов над полем GF(2)
	PolynomGF3& PolynomGF3::Mul(PolynomGF3 &a, PolynomGF3 &b)
	{
                if(a.isZero() || b.isZero())
                {
                       this->setZero();
		       return *this;
                }

                PolynomGF3 copy_a(a), copy_b(b);
                PolynomGF3 buf1;
                PolynomGF3 buf2;
                Polynom one;
                one.setOne();
                uint length;
                length = copy_b.getNumberBits();
                buf1=copy_a;
                if((copy_b.A0 & one)==one)
                {
                     buf1.A0=copy_a.A0;
                     buf1.A1=copy_a.A1;
                }
                else if((copy_b.A1 & one)==one)
                {
                     buf1.A0=copy_a.A1;
                     buf1.A1=copy_a.A0;
                }
                else
                     buf1.setZero();
                for ( uint i=1;i<length;i++)
                {
                     copy_a<<=1;
                     copy_b>>=1;
                     if((copy_b.A0 & one)==one)
                     {
                         buf2.A0=copy_a.A0;
                         buf2.A1=copy_a.A1;
                     }
                     else if((copy_b.A1 & one)==one)
                     {
                         buf2.A0=copy_a.A1;
                         buf2.A1=copy_a.A0;
                      }
                      else
                         buf2.setZero();
                      buf1 = buf1 + buf2;
                }
                buf1.A0.RemoveElderNulls();
                buf1.A1.RemoveElderNulls();

                *this=buf1;

           	return *this;
	}
  PolynomGF3& PolynomGF3::ModMul(PolynomGF3 a, PolynomGF3 b, PolynomGF3 &module)
	{
                PolynomGF3 copy_a(a), copy_b(b);
		return Mul(copy_a, copy_b) %= module;
	}
  PolynomGF3& PolynomGF3::MulGF3_n(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module)
	{
    if(module.isIrreducible())
    { PolynomGF3 copy_a(a), copy_b(b);
		  return Mul(copy_a, copy_b) %= module;
    }
    else
    throw new Exception("f(x) должен быть неприводимым.");
	}


//**********************************************************************************************


//******************************    Операция деления    ****************************************
	//simple method
	PolynomGF3 operator/(const PolynomGF3 &a, const PolynomGF3 &b)
	{
		PolynomGF3 result, copy_a(a), copy_b(b);
		return result.Div(copy_a, copy_b);
	}

	//simple method
	PolynomGF3& PolynomGF3::operator/=(PolynomGF3 &polynom)
	{
		return Div(*this, polynom);
	}

	//(c) Mamontov, TEST(Polynom, Div)
	PolynomGF3& PolynomGF3::Div(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 *remainder)
	{
               	if(this == remainder)
			throw new Exception("Частное и остаток не могут быть одним числом");
		if(b.isZero())
			throw new Exception("Деление на ноль");

                if(a.isZero() || a.getNumberBits()<b.getNumberBits())
		{
			if(remainder != NULL)
				*remainder = a;
			return setZero();
		}
	        
		if(a == b)
		{
			if(remainder != NULL)
				remainder->setZero();
			return setOne();
		}

		PolynomGF3 copy_a(a), copy_b(b);
                PolynomGF3 two("2");
                PolynomGF3 one("1");
                PolynomGF3 zero("0");
                PolynomGF3 buf;
                PolynomGF3 result;
                PolynomGF3 inveseWithElderBit;

                uint lengthA;
                uint lengthB;

                inveseWithElderBit=one;
                lengthA = copy_a.getNumberBits()-1;
                lengthB = copy_b.getNumberBits()-1;
                if( (copy_b>>lengthB)==two)
                {
                    copy_b=copy_b*two;
                    inveseWithElderBit=two;

                }
                copy_b<<=lengthA-lengthB;
                for (uint i=0;i<=(lengthA-lengthB);i++)
                {
                     if((copy_a>>(lengthA-i))==two)
                     {
                          buf=copy_b*two;
                          result=result+(two*inveseWithElderBit);
                     }
                     else if((copy_a>>(lengthA-i))==one)
                     {
                          buf=copy_b;
                          result=result+(one*inveseWithElderBit);
                     }
                     else
                          buf.setZero();
                     result<<=1;
                     copy_a = copy_a-buf;
                     copy_b>>=1;
                }
                result>>=1;
                *this=result;

                if(remainder != NULL)
		{
                   *remainder = copy_a;
		}

		return *this;
	}

  PolynomGF3& PolynomGF3::GCD(const PolynomGF3 &a, PolynomGF3 &b)
	{
    if (a.isZero() && b.isZero())
      throw new Exception("Оба полинома нулевые");
    else
    {
      if (!a.isZero() && !b.isZero())
      {
         PolynomGF3 u(a), v(b);
         std::string strU = u.ToString(), strV = v.ToString();
         while (!v.isZero())
         {
           PolynomGF3 r=u%v;
           u = v;
           v = r;
           strU = u.ToString();
           strV = v.ToString();
         }
         *this = u;
         return *this;
       }
       if (a.isZero() && !b.isZero())
       {
         *this = a;
         return *this;
       }
       if (!a.isZero() && b.isZero())
       {
         *this = b;
         return *this;
       }
    }
	}

//**********************************************************************************************

//***************************    Операция приведения по модулю    ******************************
	//simple method
	PolynomGF3 operator%(const PolynomGF3 &a, const PolynomGF3 &b)
	{
		PolynomGF3 result, copy_a(a), copy_b(b);
		return result.Mod(copy_a, copy_b);
	}

	//simple method
	PolynomGF3& PolynomGF3::operator%=(PolynomGF3 &polynom)
	{
		return Mod(*this, polynom);
	}

	//(c) Mamontov, TEST(Polynom, Mod)
	PolynomGF3& PolynomGF3::Mod(PolynomGF3 &a, PolynomGF3 &b)
	{
                if(a.isZero() && b.isZero())
		  return setZero();

                if (a.getNumberBits()<b.getNumberBits())
                {
                    *this = a;
		    return *this;
                }
                if(a == b)
			return setZero();

                PolynomGF3 copy_a(a), copy_b(b);
                PolynomGF3 quotient;
                uint numDigits;

                if (copy_b.A1._numberDigits > copy_b.A0._numberDigits)
                    numDigits = copy_b.A1._numberDigits;
                else
                    numDigits = copy_b.A0._numberDigits;

                A0.setNumberDigits(numDigits);
                A1.setNumberDigits(numDigits);
		quotient.Div(copy_a, copy_b, this);

		return *this;
	}
//------------------------------------------------------------------------------
//simple method
	PolynomGF3& PolynomGF3::ModPositive(PolynomGF3 &module)
	{
		*this %= module;
		return *this;
	}
//----------------------------------------------------------------------------
    PolynomGF3& PolynomGF3::FastCube(PolynomGF3 &a1,int len)
    {
        std::string a1_s = a1.ToString();
        int l = a1_s.length();
        Integer ziro("0"),two("2"),one("1");
        std::vector<Integer> c;
        int j = 0;
        for(int i = 0; i < len*3 - 3; i++)
        {
            if(i%3 == 0)
            {
              std::string v;
              if(j >= l)
              {
                v = "0";
              }
              else
                v = a1_s[j];
              Integer val(v);
              j++;
              c.push_back(val);
            }
            else
                c.push_back(ziro);
        }
        for(int i = len*3-3; i > len; i--)
        {
            if(c[i] == one)
            {
                c[i-len]  = c[i-len]+two;
                c[i-len+1]  = c[i-len+21]+one;
            }
            if(c[i] == two)
            {
                c[i-len]  = c[i-len]+one;
                c[i-len+1]  = c[i-len+21]+two;
            }
        }
        std::string result_s;
        for(int i = 0; i < len; i++)
        {
            result_s.append((c[i]%3).ToString());
        }
        PolynomGF3 result(result_s);
        *this = result;
        return *this;
    }

//-----------------------------------------------------------------------------
  PolynomGF3& PolynomGF3::ModPow(PolynomGF3 &a, const Integer &n, PolynomGF3 &module)
    {
      std::string A(n.ToString(NumericSystem(3)).c_str()),B,C("012");
      uint len1=A.length();
      for(uint i1=1;i1<=len1;i1++)
        {
          if(A[len1-i1]==C[0]) B.append("0");
          if(A[len1-i1]==C[1]) B.append("1");
          if(A[len1-i1]==C[2]) B.append("2");
        }
      PolynomGF3 b(B.c_str());
      uint s0=b.A0.getNumberBits();
      uint s1=b.A1.getNumberBits();
      uint s;
      if(s0>s1) s=s0;
      if(s1>s0) s=s1;
      PolynomGF3 res,copy_b(b),copy_a(a);
      Polynom one("1");
      PolynomGF3 two("2");
      res.setOne();
      PolynomGF3 PG(module);
      PolynomGF3 temp1(*this);
      *this=a;
      if(b.isZero())
		    return setOne();
      if(b.A0.isOne()&&b.A1.isZero())           //odin
		    { *this%=PG;return *this;}
      if(b.A1.isOne()&&b.A0.isZero())       //kvadrat
		    { Mul(a,a);*this%=PG;return *this;}
      if((s0==2)&&(b.A1.isZero())&&((b.A0&one).isZero()))  //kub
		    { Mul(a,a);Mul(*this,a);*this%=PG;return *this;}
      for(uint i=0;i<s;i++)
		    { temp1=res*res;
          temp1%=PG;
          res=temp1*res;
          res%=PG;
          if((s-1-i<s0)&&(((b.A0>>(s-1-i))&one).isOne()) )
		        res=res*a;
          else if((s-1-i<s1)&&(((b.A1>>(s-1-i))&one).isOne()) )
            { temp1=a*a;temp1%=PG;res=temp1*res;}
          res%=PG;
		    }
      *this=res;
		  return *this;
    }
//-----------------------------------------------------------------------------
  PolynomGF3& PolynomGF3::PowGF3_n(PolynomGF3 &a, Integer &n, PolynomGF3 &module)
    {
      if(module.isIrreducible())
      {
        std::string A(n.ToString(NumericSystem(3)).c_str()),B,C("012");
        uint len1=A.length();
        for(uint i1=0;i1<=len1;i1++)
          {
            if(A[len1-i1]==C[0]) B.append("0");
            if(A[len1-i1]==C[1]) B.append("1");
            if(A[len1-i1]==C[2]) B.append("2");
          }
        PolynomGF3 b(B.c_str());
        uint s0=b.A0.getNumberBits();
        uint s1=b.A1.getNumberBits();
        uint s;
        if(s0>s1) s=s0;
        if(s1>s0) s=s1;
        PolynomGF3 res,copy_b(b),copy_a(a);
        Polynom one("1");
        PolynomGF3 two("2");
        res.setOne();
        PolynomGF3 PG(module);
        PolynomGF3 temp1(*this);
        *this=a;
        if(b.isZero())
		      return setOne();
        if(b.A0.isOne()&&b.A1.isZero())           //odin
		      { *this%=PG;return *this;}
        if(b.A1.isOne()&&b.A0.isZero())       //kvadrat
		      { Mul(a,a);*this%=PG;return *this;}
        if((s0==2)&&(b.A1.isZero())&&((b.A0&one).isZero()))  //kub
		      { Mul(a,a);Mul(*this,a);*this%=PG;return *this;}
        for(uint i=0;i<s;i++)
		     { temp1=res*res;
           temp1%=PG;
           res=temp1*res;
           res%=PG;
            if((s-1-i<s0)&&(((b.A0>>(s-1-i))&one).isOne()) )
		          res=res*a;
            else if((s-1-i<s1)&&(((b.A1>>(s-1-i))&one).isOne()) )
              { temp1=a*a;temp1%=PG;res=temp1*res;}
            res%=PG;
		      }
        *this=res;
		    return *this;
      }
      else
       throw new Exception("f(x) должен быть неприводимым.");
    }

//------------------------------------------------------------------------------
  PolynomGF3& PolynomGF3::Pow(PolynomGF3 &a, Integer &n)
    {
       std::string A(n.ToString(NumericSystem(3)).c_str()),B,C("012");
       uint len1=A.length();
       for(uint i1=1;i1<=len1;i1++)
        {
          if(A[len1-i1]==C[0]) B.append("0");
          if(A[len1-i1]==C[1]) B.append("1");
          if(A[len1-i1]==C[2]) B.append("2");
        }
       PolynomGF3 b(B.c_str());
       uint s0=b.A0.getNumberBits();
       uint s1=b.A1.getNumberBits();
       uint s;
       if(s0>s1) s=s0;
       if(s1>s0) s=s1;
        PolynomGF3 res,copy_b(b),copy_a(a);
       Polynom one("1");
       PolynomGF3 two("2");
       res.setOne();
       PolynomGF3 temp1(*this);
       *this=a;
       if(b.isZero())
		    return setOne();
       if(b.A0.isOne()&&b.A1.isZero())           //odin
		    {return *this;}
       if(b.A1.isOne()&&b.A0.isZero())       //kvadrat
		    {
          Mul(a,a);
          return *this;
        }
       if((s0==2)&&(b.A1.isZero())&&((b.A0&one).isZero()))  //kub
		    {
          Mul(a,a);
          Mul(*this,copy_a);
          return *this;
        }
       for(uint i=0;i<s;i++)
		    {
          temp1=res*res;
          res=temp1*res;
          if((s-1-i<s0)&&(((b.A0>>(s-1-i))&one).isOne()) )
    		   res=res*a;
          else if((s-1-i<s1)&&(((b.A1>>(s-1-i))&one).isOne()) )
            {
              temp1=a*a;
              res=temp1*res;
            }
    		 }
       *this=res;
       return *this;
  }
//---------------------------------------------------------------------------
PolynomGF3& PolynomGF3::Generate(const PolynomGF3& module)
{   int q;
    std::string A;
    uint len=module.getNumberBits();
    for(uint i1=0;i1<len;i1++)
      {
        q=rand()%4;
        if(q==0) A.append("0");
        if(q==1) A.append("1");
        if(q==2) A.append("2");
       }
    PolynomGF3 res,m(module);
    res.Parse(A);
    res%=m;
    *this=res;
    return *this;
}

     PolynomGF3& PolynomGF3::Generate(const PolynomGF3& module, const PolynomGF3& m)
     {  int q;
        std::string A;
        uint len=module.getNumberBits();
        uint lenm=m.getNumberBits();
        A=m.ToString();
       for(uint i1=lenm+1;i1<len;i1++)
       {
         q=rand()%4;
         if(q==0) A.append("0");
         if(q==1) A.append("1");
         if(q==2) A.append("2");
       }
       PolynomGF3 res,mm(module);
       res.Parse(A);
       res%=mm;
       *this=res;
       return *this;
     }

//(c) Chernysheva, TEST(PolynomGF3, GenerateIrreducible)
// генерация неприводимого трехчлена
PolynomGF3& PolynomGF3::GenerateIrreducible(const uint nDegree)
{
  if (nDegree < 2)
    throw new std::domain_error("cтепень полинома меньше 2");

  bool isGen = false;
  //2_+_X^t_+_X^n
  if (!isGen)
  {
    PolynomGF3 plGen("2"), plCur;
    plGen.setBit(nDegree, 1);
    uint k = 1;
    while (k < nDegree && !isGen)
    {
      plCur = plGen;
      plCur.setBit(k, 1);
      if (plCur.isIrreducible())
      {
        isGen = true;
        *this = plCur;
        break;
      }
      k++;
    }
  }


  //1_+_2X^t_+_X^n
  if (!isGen)
  {
    PolynomGF3 plGen("1"), plCur;
    plGen.setBit(nDegree, 1);
    uint k = 1;
    while (k <= nDegree/2 && !isGen)
    {
      plCur = plGen;
      plCur.setBit(k, 2);
      if (plCur.isIrreducible())
      {
        isGen = true;
        *this = plCur;
        break;
      }
      k++;
    }
  }

  // 2_+_2X^t_+_X^n
  if (!isGen)
  {
    PolynomGF3 plGen("2"), plCur;
    plGen.setBit(nDegree, 1);
    uint k = 1;
    while (k < nDegree && !isGen)
    {
      plCur = plGen;
      plCur.setBit(k, 2);
      if (plCur.isIrreducible())
      {
        isGen = true;
        *this = plCur;
        break;
      }
      k++;
    }
  }

  if (!isGen)
    throw new Exception("Не удалось сгенерировать трехчлен с данными параметрами");
  else
    return *this;
}

//----------------------------------------------------------------------------
PolynomGF3& PolynomGF3::ModPow1(PolynomGF3 &a, PolynomGF3 &b,PolynomGF3 &module)
{ uint s0=b.A0.getNumberBits();
  uint s1=b.A1.getNumberBits();
  uint s;
  if(s0>s1) s=s0;
  if(s1>s0) s=s1;
  PolynomGF3 res,copy_b(b),copy_a(a);
  Polynom one("1");
  PolynomGF3 two("2");
  res.setOne();
  PolynomGF3 PG(module);
  PolynomGF3 temp1(*this);
  *this=a;
  if(b.isZero())
    return setOne();
  if(b.A0.isOne()&&b.A1.isZero())           //odin
    { *this%=PG;return *this;}
  if(b.A1.isOne()&&b.A0.isZero())       //kvadrat
    { Mul(a,a);
      *this%=PG;
      return *this;
    }
  if((s0==2)&&(b.A1.isZero())&&((b.A0&one).isZero()))  //kub
    { Mul(a,a);
      Mul(*this,a);
      *this%=PG;
      return *this;
    }
  for(uint i=0;i<s;i++)
    { temp1=res*res;
      temp1%=PG;
      res=temp1*res;
      res%=PG;
      if((s-1-i<s0)&&(((b.A0>>(s-1-i))&one).isOne()) )
        res=res*a;
      else if((s-1-i<s1)&&(((b.A1>>(s-1-i))&one).isOne()) )
        { temp1=a*a;
          temp1%=PG;
          res=temp1*res;
        }
      res%=PG;
		 }
  *this=res;
  return *this;
}
//----------------------------------------------------------------------------
PolynomGF3& PolynomGF3::Pow1(PolynomGF3 &a, PolynomGF3 &b)
{ uint s0=b.A0.getNumberBits();
  uint s1=b.A1.getNumberBits();
  uint s;
  if(s0>s1) s=s0;
  if(s1>s0) s=s1;
  PolynomGF3 res,copy_b(b),copy_a(a);
  Polynom one("1");
  PolynomGF3 two("2");
  res.setOne();
  *this=a;
  if(b.isZero())
    return setOne();
  if(b.A0.isOne()&&b.A1.isZero())           //odin
    return *this;
  if(b.A1.isOne()&&b.A0.isZero())       //kvadrat
    { Mul(a,a);
      return *this;
    }
  if((s0==2)&&(b.A1.isZero())&&((b.A0&one).isZero()))  //kub
    { Mul(a,a);
      Mul(*this,a);
      return *this;
    }
  for(uint i=0;i<s;i++)
    {
      res=res*res*res;
      if((s-1-i<s0)&&(((b.A0>>(s-1-i))&one).isOne()) )
        res=res*a;
      else if((s-1-i<s1)&&(((b.A1>>(s-1-i))&one).isOne()) )
        res=res*a*a;
		 }
  *this=res;
  return *this;
}
//------------------------------------------------------------------------------
PolynomGF3& PolynomGF3::InverseMod1(PolynomGF3 &a,PolynomGF3 &module)
{ std::string A;
  uint len=module.getNumberBits()-3;
  A.append("1");
  for(uint i1=0;i1<len+1;i1++)
    { A.append("2");}
      PolynomGF3 bb(A);
      this->ModPow1(a,bb,module);
      return *this;
    }
//------------------------------------------------------------------------------
PolynomGF3& PolynomGF3::InverseMod(PolynomGF3 &a,PolynomGF3 &module)
{ if(module.isIrreducible())
  { uint len=module.getNumberBits()-1;
    Integer AA,BB,CC;
    AA.Parse("3");
    BB=len;
    CC.Pow(AA,BB);
    CC=CC-2;
    this->ModPow(a,CC,module);
    return *this;
  }
  else
  throw new Exception("f(x) должен быть неприводимым.");
}
//------------------------------------------------------------------------------
PolynomGF3& PolynomGF3::Square1(PolynomGF3 &a,PolynomGF3 &module)
{PolynomGF3 aa(a),m(module);
  uint len=m.getNumberBits()-1;
            if(len % 2 != 1)
                       throw new Exception("n чётное");
  uint k=len/2;
  AAL:: Integer pp("3"),p1(2*k),pp1("3"),p2("2"),one("1"),six("6");
  pp.Pow(pp,p1);
  pp.Sub(pp,one);
  pp1.Pow(pp1,p2);
  pp1.Sub(pp1,one);
  pp=pp/pp1;
  PolynomGF3 res(aa);
  res.ModPow(res,pp,m);
  res.ModPow(res,six,m);
  res.Mul(res,aa);
  res%=m;
  PolynomGF3 temp(res);
  temp=res*res;
  temp%=m;
  if(temp!=aa) {*this=m;return *this;}
  *this=res;
  return *this;
}

//------------------------------------------------------------------------------

   PolynomGF3& PolynomGF3::LegendreSymbol( PolynomGF3 &a, PolynomGF3 &module)
   {
        if(module.isIrreducible() == false)
                        throw new Exception("f(x) - ?????? ???? ??????????");
       PolynomGF3 result,minus_one("2");
        uint m = module.getNumberBits() - 1;
        Integer power("1");
        power.Pow(3,(m));
        power = (power-1)/2;
        std::string s;
        result.ModPow(a,power,module);
          s = result.A0.ToString();
          s = result.A1.ToString();
        *this = result;
        return *this;
   }
//-------------------------------------------------------------------------------
   PolynomGF3& PolynomGF3::Sqrt(PolynomGF3 &x, PolynomGF3 &module,Integer &ss,Integer &T)

   {
        if(module.isIrreducible() == false)
                        throw new Exception("f(x) - должен быть неприводим");

        bool rez;
        Integer s;
        s = ss;
        PolynomGF3 test;
        PolynomGF3 zero("0");
        test.LegendreSymbol(x,module);
        if(test.isOne() != true)
        {
                *this = zero;
                return *this;
        }
        PolynomGF3 result,a,b("0"),e1,e2,e3,e4,e5;
        result.setOne();
        PolynomGF3 minus_one("2");
        uint m = module.getNumberBits() - 1;
        Integer power("1"),t("0");
        power.Pow(3,(m));
        power = (power-1)/2;

        std::string st;
        while(result != minus_one)
        {
          a.Generate(module);
          result.LegendreSymbol(a,module);
        }
        st = a.A0.ToString();
        st = a.A1.ToString();
        a = a.ModPow(a,s,module);
        st = a.A0.ToString();
        st = a.A1.ToString();

        b.setOne();
        st = b.A0.ToString();
        st = b.A1.ToString();
        b.ModPow(x,(s-1)/2,module);
        st = b.A0.ToString();
        st = b.A1.ToString();

        Integer two("2"), c("1"),e("1");
        Integer k("0"),t0("0");
        for(Integer i = 0; i < T; i++)
        {
                e1.ModPow(a,t0,module);
                st = e1.A0.ToString();
                st = e1.A1.ToString();
                e2.ModMul(e1,b,module);
                st = e2.A0.ToString();
                st = e2.A1.ToString();
                e3.ModMul(e2,e2,module);
                st = e3.A0.ToString();
                st = e3.A1.ToString();
                e4.ModMul(e3,x,module);
                st = e4.A0.ToString();
                st = e4.A1.ToString();
                two.Pow(2,T-k - 1);
                st = two.ToString();
                e5.ModPow(e4,two,module);
                st = e5.ToString();
                if(e5 == minus_one)
                        c = 1;
                if(e5.isOne())
                        c = 0;
                t = t + e.Pow(2,k)*c;
                t0 = t;
                k = k + 1;
        }
        PolynomGF3 r1,r2;
        a.ModPow(a,t,module);
        r1.ModMul(a,b,module);
        r2.ModMul(r1,x,module);
        *this = r2;
        st = A0.ToString();
        st = A1.ToString();
        st = r2.ToString();
        return *this;
   }

//**********************************************************************************************

        uint PolynomGF3::getNumberBits() const
	{
            uint numA1,numA0;
            numA1 = A1.getNumberBits();
            numA0 = A0.getNumberBits();
	    if( numA1 > numA0 )
	    	return numA1;
            else
                return numA0;
     	}

        uint PolynomGF3::getFirstTrueBit() const
        {
            uint numA1,numA0;
            numA1 = A1.getFirstTrueBit();
            numA0 = A0.getFirstTrueBit();
	    if( numA1 > numA0 )
	    	return numA0;
            else
                return numA1;
     	}

        void PolynomGF3::setNumberDigits(uint numberDigits)
	{
                A0.setNumberDigits(numberDigits);
                A1.setNumberDigits(numberDigits);
	}

//-------------------------------------------------------------------------------
  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // перевод числа в строку
  std::string PolynomGF3::i_to_str(uint x) const
  {
    std::string str = "";
    char s[11];
    ltoa(x, s, 10);
    str += s;
    return str;
  }

    // получить список степеней
  //(c) Chernysheva
  std::list<std::pair<uint,uint> > PolynomGF3::getPowersOfPolynom() const
  {
    std::list<std::pair<uint,uint> > powers;
    uint count = this->getNumberBits();
    for (uint i = 0; i < count; ++i)
    {
      uint val = this->getBit(i);
      if (val)
        powers.push_back(std::make_pair(val,i));

    }
    return powers;
  }

  // строка степеней
  //(c) Chernysheva
  // в строку парами <коэффициент, степень>
  std::string PolynomGF3::ToStringByPowers() const
  {
    std::list<std::pair<uint,uint> > powers(getPowersOfPolynom());
    std::string str = "";
    for (std::list<std::pair<uint,uint> >::iterator i = powers.begin(); i != powers.end(); ++i)
    {
	  str += "{";
      str += i_to_str(i->first);
	  str += ",";
	  str += i_to_str(i->second);
	  str += "}";
      str += " ";
    }
    str += "\n";
    return str;
  }


   // Тесты степеней поля на образование ОНБ и ГНБ
  // ОНБ 1
  // (c) Chernysheva, TEST(PolynomGF3, ONB1)
  bool PolynomGF3::ONB1Test(const uint n) const
  {
    Integer p(n + 1);
    if (p.isPrime())
    {
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(n));
      Integer number, mod, pow;
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        number = i->getNumber();
        pow = (p - 1)/number;
        mod.ModPow(Integer(3), pow, p);
        if (mod == 1)
          return false;
      }
      return true;
    }
    else
      return false;
  }

  // ОНБ 2
  // (c) Chernysheva, TEST(PolynomGF3, ONB2)
  bool PolynomGF3::ONB2Test(const uint n) const
  {
    Integer p(2*n + 1);
    if (p.isPrime())
    {
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(2*n));
      Integer number, mod, pow;
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        number = i->getNumber();
        pow = (p - 1)/number;
        mod.ModPow(Integer(3), pow, p);
        if (mod == 1)
          return false;
      }
      return true;
    }
    else
      return false;
  }
  // ОНБ 3
  // (c) Chernysheva, TEST(PolynomGF3, ONB3)
  bool PolynomGF3::ONB3Test(const uint n) const
  {
    // n - нечетно
    if (n%2)
    {
      Integer p(2*n + 1), condition;
      condition.ModPow(Integer(3), Integer(n), p);
      if (p.isPrime() && condition == 1)
      {
        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(n));
        Integer number, mod, pow;
        for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
        {
          number = i->getNumber();
          pow = n/number;
          mod.ModPow(Integer(3), pow, p);
          if (mod == 1)
            return false;
        }
        return true;
      }
      else
        return false;
    }
    else
      return false;
  }

  // ГНБ
  bool PolynomGF3::GNBTest(const uint n, const int type) const
  {
    if (type < 3 || type > 6)
      throw new Exception("Тип ГНБ должен быть от 3 до 6");

    Integer p(type*n + 1);
    if (p.isPrime())
    {
      // проверку неделимости 3 на p опускаем, т.к. это очевидно
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(n));
      Integer number, mod, pow;
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        number = i->getNumber();
        pow = (p - 1)/number;
        mod.ModPow(Integer(3), pow, p);
        if (mod == 1)
          return false;
      }
      return true;
    }
    else
      return false;
  }
  //-----------------------------------------------------------------------------
Integer& PolynomGF3::elementOrder(PolynomGF3 &groupModule, PolynomGF3 &polynom,std::vector<DecompositionMember> vector, const Integer &ord )
{
 // if(!polynom. InMulGroup(groupModule))
 //   throw new Exception("полином не принадлежит мультипликативной группе");
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    PolynomGF3 *m  = new PolynomGF3(groupModule);
    PolynomGF3 *a = new PolynomGF3(polynom);
    Integer t =  ord;
    for(it = vector.begin(); it != vector.end();it++)
    {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.Pow(p,e);
      t = t/(ex);
      PolynomGF3 a1;
      a1.ModPow(*a,t,*m);
      while(!Mod(a1,*m).isOne())
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
bool PolynomGF3::isGenerator(PolynomGF3 &groupModule, PolynomGF3 &polynom,std::vector<DecompositionMember> vector,const Integer &ord)
{
//  if(!polynom.InMulGroup(groupModule))
//    throw new Exception("полином не принадлежит мультипликативной группе");
	if (vector.size()==1) return true;
    if(vector.size() > 1)
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

//----------------------------------------------------------------------------------------

};
