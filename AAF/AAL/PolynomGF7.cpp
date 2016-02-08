/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PolynomGF7.h"
#include "PolynomGF7_mY_3.h"
#include "Converter.h"
#include "DecompositionManager.h"
#include <string>
#include <stdlib.h>
namespace AAL
{
  int sevendiv(std::vector<Integer>* m, Integer n)
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
//***********************************  Êîíñòðóêòîðû  *******************************************
	PolynomGF7::PolynomGF7()// : BasicType<uchar>()
	{}
  PolynomGF7::PolynomGF7(const PolynomGF7 &polynom) //: BasicType<uchar>(polynom)
	{
    A0 = polynom.A0;
    A1 = polynom.A1;
    A2 = polynom.A2;
  }

  PolynomGF7::PolynomGF7(const std::string dataString)
  {
		Parse(dataString);
  }
  PolynomGF7::~PolynomGF7()
  {
  }
//**********************************************************************************************


//*************************  Ïðåîáðàçîâàíèå è ñ÷èòûâàíèå èç ñòîðê ******************************
	///(c) Mamontov
	PolynomGF7& PolynomGF7::Parse(const std::string dataString)
	{

                std::string polynomA0;
                std::string polynomA1;
                std::string polynomA2;
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
                               polynomA2.append(zero);
                          }
			  else if(dataString[i] == '1')
                          {
                               polynomA1.append(zero);
                               polynomA0.append(one);
                               polynomA2.append(zero);
			  }
			  else if(dataString[i] == '2' )
                          {
                               polynomA1.append(one);
                               polynomA0.append(zero);
                               polynomA2.append(zero);
			  }
			  else if(dataString[i] == '3' )
                          {
                               polynomA1.append(one);
                               polynomA0.append(one);
                               polynomA2.append(zero);
			  }
			  else if(dataString[i] == '4' )
                          {
                               polynomA1.append(zero);
                               polynomA0.append(zero);
                               polynomA2.append(one);
			  }
			  else if(dataString[i] == '5' )
                          {
                               polynomA1.append(zero);
                               polynomA0.append(one);
                               polynomA2.append(one);
			  }
			  else if(dataString[i] == '6' )
                          {
                               polynomA1.append(one);
                               polynomA0.append(zero);
                               polynomA2.append(one);
			  }
                          else
                               throw new Exception("×èñëî çàäàíî â íåïðåäóñìîòðåííîì ôîðìàòå");

		     }
		}
                const std::string strA0(polynomA0);
                const std::string strA1(polynomA1);
                const std::string strA2(polynomA2);

		A0.Parse(strA0, BackBin);
                A1.Parse(strA1, BackBin);
                A2.Parse(strA2, BackBin);

                return *this;
	}

	//(c) Mamontov
	std::string PolynomGF7::ToString() const
	{
    // removing elder nulls. if there are (1,1,1) set them to (0,0,0)
    for(int i=0; i < getNumberBits(); ++i) setBit(i,getBit(i));
    std::string StringA0;
    std::string StringA1;
    std::string StringA2;
    std::string dataString;
    const std::string zero("0");
    const std::string one("1");
    StringA0 = Converter::ToString(A0, BackBin);
    StringA1 = Converter::ToString(A1, BackBin);
    StringA2 = Converter::ToString(A2, BackBin);

    uint lengthA0 = (uint)StringA0.length();
    uint lengthA1 = (uint)StringA1.length();
    uint lengthA2 = (uint)StringA2.length();
    uint length;
    uint j = 0;
    if(lengthA0 >= lengthA1 && lengthA0 >= lengthA2)
    {
        length = lengthA0;
        for(uint i = lengthA1 + 1;i <= length;i++ )
                StringA1 = StringA1 + "0";
        for(uint i = lengthA2 + 1;i <= length;i++ )
                StringA2 = StringA2 + "0";

    }
    else if(lengthA1 >= lengthA0 && lengthA1 >= lengthA2)
    {
        length = lengthA1;
        for(uint i = lengthA0 + 1;i <= length;i++ )
                StringA0 = StringA0 + "0";
        for(uint i = lengthA2 + 1;i <= length;i++ )
                StringA2 = StringA2 + "0";

    }
    else if(lengthA2 >= lengthA1 && lengthA2 >= lengthA0)
    {
        length = lengthA2;
        for(uint i = lengthA1 + 1;i <= length;i++ )
                StringA1 = StringA1 + "0";
        for(uint i = lengthA0 + 1;i <= length;i++ )
                StringA0 = StringA0 + "0";
    }

    if (!A1.isZero() || !A0.isZero() || !A2.isZero())
      {
        for(uint i=0; i<length; i++)
        {
                if(StringA0[i] == '0' && StringA1[i] == '0' && StringA2[i] == '0')
              {
		            dataString=dataString + "0";
              }
                if(StringA0[i] == '1' && StringA1[i] == '1' && StringA2[i] == '1')
              {
		            dataString=dataString + "0";
              }

              else if(StringA0[i] == '1' && StringA1[i] == '0' && StringA2[i] == '0')
              {
                dataString = dataString + "1";
              }
              else if(StringA0[i] == '0' && StringA1[i] == '1'  && StringA2[i] == '0')
              {
                dataString = dataString + "2";
              }
              else if(StringA0[i] == '1' && StringA1[i] == '1'  && StringA2[i] == '0')
              {
                dataString = dataString + "3";
              }
              else if(StringA0[i] == '0' && StringA1[i] == '0'  && StringA2[i] == '1')
              {
                dataString = dataString + "4";
              }
              else if(StringA0[i] == '1' && StringA1[i] == '0'  && StringA2[i] == '1')
              {
                dataString = dataString + "5";
              }
              else if(StringA0[i] == '0' && StringA1[i] == '1'  && StringA2[i] == '1')
              {
                dataString = dataString + "6";
              }
          }
      }
    else
      {
        dataString = "0";
        if( A1.isZero() && A0.isZero()  && A2.isZero())
        {
          return dataString;
        }
      }
    return dataString;
}

//**********************************************************************************************
//***************************************  Ìåòîäû àêöåïòîðû   **********************************
       bool PolynomGF7::isZero(PolynomGF7 &module) const
       {
            std::string s = A0.ToString();
            s = A1.ToString();
            s = A2.ToString();
            uint m = module.getNumberBits() - 1;
            std::string o_st,e_st;
            for(int i = 0  ; i < m; i++)
            {
                o_st.append("0");
                e_st.append("1");
            }
            if( A0.ToString() == o_st && A1.ToString() == o_st && A2.ToString() == o_st)
               return true;
            else if( A0.ToString() == e_st && A1.ToString() == e_st && A2.ToString() == e_st)
                return true;
            else
               return false;
       }
       bool PolynomGF7::isZero() const
       {
            if( A0.isZero() && A1.isZero() && A2.isZero())
               return true;
            else if( A0.isOne() && A1.isOne() && A2.isOne())
                return true;
            else
               return false;
       }

       bool PolynomGF7::isOne() const
       {
            std::string s = A0.ToString();
            s = A1.ToString();
            s = A2.ToString();
            //if(A0.ToString() == "1" && A0.ToString() == "0" && A0.ToString() == "0")
              //  return true;
            if( A0.isOne() && A1.isZero()  && A2.isZero() )
               return true;
            else
               return false;
       }
    //(c) Chernysheva
  uint PolynomGF7::getBit(uint index) const
  {
    bool a0bit = A0.getBit(index), a1bit = A1.getBit(index), a2bit = A2.getBit(index);
    if (!a0bit && !a1bit && !a2bit)
      return 0;
    if (a0bit && a1bit && a2bit)
      return 0;
    if (!a0bit && a1bit && !a2bit)
      return 2;
    if (a0bit && !a1bit && !a2bit)
      return 1;
    if (a0bit && a1bit && !a2bit)
      return 3;
    if (!a0bit && !a1bit && a2bit)
      return 4;
    if (a0bit && !a1bit && a2bit)
      return 5;
    if (!a0bit && a1bit && a2bit)
      return 6;
  }

  //(c) Chernysheva
  void PolynomGF7::setBit(uint index, uint bit)
  {
    switch(bit)
    {
      case 0:
        A0.setBit(index, false);
        A1.setBit(index, false);
        A2.setBit(index, false);
        break;
      case 1:
        A0.setBit(index, true);
        A1.setBit(index, false);
        A2.setBit(index, false);
        break;
      case 2:
        A0.setBit(index, false);
        A1.setBit(index, true);
        A2.setBit(index, false);
        break;
      case 3:
        A0.setBit(index, true);
        A1.setBit(index, true);
        A2.setBit(index, false);
        break;
      case 4:
        A0.setBit(index, false);
        A1.setBit(index, false);
        A2.setBit(index, true);
        break;
      case 5:
        A0.setBit(index, true);
        A1.setBit(index, false);
        A2.setBit(index, true);
        break;
      case 6:
        A0.setBit(index, false);
        A1.setBit(index, true);
        A2.setBit(index, true);
        break;
      default:
        throw new Exception("????? ?????? ? ????????????????? ???????");
        break;
    }
  }



//************************************  Óíàðíûå îïåðàöèè   *************************************
	//(c) Mamontov, TEST(Polynom, operatorEqual)
	PolynomGF7& PolynomGF7::operator= (const PolynomGF7& polynom)
	{
		A0 = polynom.A0;
                A1 = polynom.A1;
                A2 = polynom.A2;
		return *this;
	}
//**********************************************************************************************

//***************************************  Ìåòîäû àêöåïòîðû   **********************************
	//simple method
	PolynomGF7& PolynomGF7::setOne()
	{
		A0.setOne();
                A1.setZero();
                A2.setZero();
		return *this;
	}

        	//simple method
	PolynomGF7& PolynomGF7::setTwo()
	{
		A0.setZero();
                A1.setOne();
                A2.setZero();
		return *this;
	}
	//simple method
	PolynomGF7& PolynomGF7::setZero()
	{
		A0.setZero();
                A1.setZero();
                A2.setZero();
		return *this;
	}
	PolynomGF7& PolynomGF7::setZero(PolynomGF7 &module)
	{
                uint m = module.getNumberBits() - 1;
                std::string o_st,s;
                for(int i  = 0; i< m;i++)
                {
                        o_st.append("0");
                }
                Polynom zr(o_st);
		A0 = zr;
                s = A0.ToString();
                A1 = zr;
                s = A1.ToString();
                A2 = zr;
                s = A2.ToString();
		return *this;
	}

//**********************************************************************************************

//*****************************    Îïåðàöèè ñðàâíåíèÿ    ***************************************
	//(c) Mamontov, TEST(Polynom, Equal)
	bool operator==(const PolynomGF7& a, const PolynomGF7& b)
	{
               std::string A = a.ToString();
               std::string B = b.ToString();
		if((a.A0==b.A0) && (a.A1==b.A1) && (a.A2==b.A2))// && a.CmpImpl(b) == Equal )
			return true;
		return false;
	}

      	//simple method
	bool operator!=(const PolynomGF7& a, const PolynomGF7& b)
	{
		return !(a == b);
	}
/*
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
*/
//***************************    Îïåðàöèè ïîáèòîâîãî ñäâèãà    *********************************
	//simple method
	PolynomGF7 PolynomGF7::operator<<(int numberBits) const
	{
		PolynomGF7 result(*this);
		return result<<=numberBits;
	}

	//(c) Mamontov, TEST(Polynom, SHL)
	PolynomGF7& PolynomGF7::operator<<=(int numberBits)
	{
	        A0<<=numberBits;
                A1<<=numberBits;
		A2<<=numberBits;
		return *this;
	}

	//simple method
	PolynomGF7 PolynomGF7::operator>>(int numberBits) const
	{
		PolynomGF7 result(*this);
		return result>>=numberBits;
	}

	//(c) Mamontov, TEST(Polynom, SHR)
	PolynomGF7& PolynomGF7::operator>>=(int numberBits)
	{
	        A0>>=numberBits;
                A1>>=numberBits;
                A2>>=numberBits;
                return *this;
	}
   
//**********************************************************************************************
	//simple method
	PolynomGF7 PolynomGF7::operator-(const PolynomGF7 &b) const
	{
		PolynomGF7 result;
		return result.Sub(*this, b);
	}

	//simple method
	PolynomGF7& PolynomGF7::operator-=(const PolynomGF7 &polynom)
	{
		return Sub(*this, polynom);
	}

	//simple method
	PolynomGF7& PolynomGF7::Sub(const PolynomGF7 &a, const PolynomGF7 &b)
	{
		PolynomGF7 copy_a(a), copy_b(b);
		for (int i=0;i<b.getNumberBits();++i) 
			if (b.getBit(i)) copy_b.setBit(i, 7-b.getBit(i));
		return Add(copy_a, copy_b);
	}

//******************************    Îïåðàöèÿ ñëîæåíèÿ    ***************************************
	//simple method
	PolynomGF7 operator+(const PolynomGF7 &a, const PolynomGF7 &b)
	{
		PolynomGF7 result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}

	//simple method
	PolynomGF7& PolynomGF7::operator+=(PolynomGF7 &polynom)
	{
		return Add(*this, polynom);
	}

	//simple method
	PolynomGF7& PolynomGF7::Add(PolynomGF7 &a, PolynomGF7 &b)
	{
                Polynom s1,s2,s0;
                Polynom l1,l2,l0;
                Polynom z1,z2,z3,z0;
                Polynom r1,r2,r3;
                std::string st;
                PolynomGF7 copy_a(a), copy_b(b);
/*                st = copy_a.A2.ToString();
                st = copy_b.A2.ToString();
                st = copy_a.A1.ToString();
                st = copy_b.A1.ToString();
                st = copy_a.A0.ToString();
                st = copy_b.A0.ToString();
*/
                s2 = copy_a.A2 & copy_b.A2;
                s1 = copy_a.A1 & copy_b.A1;
                s0 = copy_a.A0 & copy_b.A0;
                l2 = copy_a.A2 + copy_b.A2;
//                st = l2.ToString();
                l1 = copy_a.A1 ^ copy_b.A1;
//                st = l1.ToString();
                l0 = copy_a.A0 ^ copy_b.A0;
//                st = l0.ToString();
                z0 = l0;
                z1 = l1 ^ s0;
                z2 = l2 ^ s1 ^ l1&s0;
                z3= s2 ^ l2&s1 ^ l2&l1&s0;
                z2 = z2 ^ z0&z1&z3;
                z1 = z1 ^ z0&z3;
                z0 = z0 ^ z3;

//                std::string str = z0.ToString(); // 011101
 //               str = z1.ToString();//0101
  //              str = z2.ToString();//0011
                A0 = z0;
                A1 = z1;
                A2 = z2;

                return *this;
         }
    PolynomGF7& PolynomGF7::ModAdd(PolynomGF7 &a, PolynomGF7 &b, PolynomGF7 &module)
    {
        PolynomGF7 copy_a(a), copy_b(b);
        return Add(copy_a, copy_b) %= module;

    }

//******************************    Îïåðàöèÿ óìíîæåíèÿ    **************************************

        //simple method
	PolynomGF7 operator*(const PolynomGF7 &a, const PolynomGF7 &b)
	{
		PolynomGF7 result, copy_a(a), copy_b(b);
		return result.Mul(copy_a, copy_b);
	}

	//simple method
	PolynomGF7& PolynomGF7::operator*=(PolynomGF7 &polynom)
	{
		return Mul(*this, polynom);
	}

        // Ôóíêöèÿ ðåàëèçóþùàÿ óìíîæåíèå ìíîãî÷ëåíîâ íàä ïîëåì GF(2)
	PolynomGF7& PolynomGF7::Mul(PolynomGF7 a, PolynomGF7 b)
	{
                if(a.isZero() || b.isZero())
                {
                       this->setZero();
		       return *this;
                }
               // *this = a;
               // return *this;
                PolynomGF7 copy_a(a), copy_b(b),rez,result("0"),r;
                Polynom x_i;
                int len_b = b.ToString().length();
                for(int i = 0; i < len_b; i++)
                {
                    x_i.setBit(i,false);
                }

                for(int i = 0; i < len_b; i++)
                {
                    PolynomGF7 mult(itoa(copy_b.getBit(i), new char[10], 10));
                    rez = r.MulToConstant(copy_a,mult);
                    x_i.setBit(i,true);
 //                   std::string st = rez.A0.ToString();
  //                  st = rez.A1.ToString();
  //                  st = rez.A2.ToString();
                    rez.A0 = x_i*rez.A0;
                    rez.A1 = x_i*rez.A1;
                    rez.A2 = x_i*rez.A2;
   //                 st = rez.A0.ToString();
    //                st = rez.A1.ToString();
    //                st = rez.A2.ToString();
                    result = result + rez;
                    x_i.setBit(i,false);
                }
  //              std::string str = result.A0.ToString();
  //              str = result.A1.ToString();
  //              str = result.A2.ToString();
                *this = result;
           	return *this;
	}

         //----------------------------------------------------------------------------------------
	PolynomGF7& PolynomGF7::MulToConstant(PolynomGF7 &a, PolynomGF7 &b)
	{
                if(a.isZero() || b.isZero())
                {
                       this->setZero();
		       return *this;
                }

                PolynomGF7 copy_a(a), copy_b(b);
                Polynom m1,m2,m3;
                Polynom u1,u0,d1,d2,d0,z1,z2,z0;
                 Polynom one;
                one.setOne();
                m1 = (copy_b.A0 ^ copy_b.A1)&(copy_b.A0 ^ copy_b.A2)^copy_b.A0;
                int len = copy_a.ToString().length();
                std::string m_str;
                for(int i = 0; i < len;i++)
                        m_str=m_str+m1.ToString();
                Polynom m(m_str);
                u1 = copy_b.A0 ^ copy_b.A1 ^ one;
                u0 = copy_b.A0 ^ copy_b.A2 ^ one;
                d2 = m2.Not(u1) & m3.Not(u0);
                d1 = u1 & m3.Not(u0);
                d0 = m2.Not(u1) & u0;
                std::string d0_str,d2_str,d1_str;
                for(int i = 0; i < len;i++)
                {
                        d0_str=d0_str+d0.ToString();
                        d1_str=d1_str+d1.ToString();
                        d2_str=d2_str+d2.ToString();
                }
                Polynom  d_0(d0_str),d_1(d1_str),d_2(d2_str);
                z2 = ((d_2&copy_a.A2)^(d_1&copy_a.A0))^((d_0&copy_a.A1)^m);
                z1 = ((d_2&copy_a.A1)^(d_1&copy_a.A2))^((d_0&copy_a.A0)^m);
                z0 = ((d_2&copy_a.A0)^(d_1&copy_a.A1))^((d_0&copy_a.A2)^m);
                A0 = z0;
                A1 = z1;
                A2 = z2;
               // std::string s = A0.ToString();
               // s = A1.ToString();
               // s = A2.ToString();
           	return *this;
	}
          PolynomGF7& PolynomGF7::ModMul(PolynomGF7 &a, PolynomGF7 &b, PolynomGF7 &module)
	{
                PolynomGF7 copy_a(a), copy_b(b);
		return Mul(copy_a, copy_b) %= module;
	}
         PolynomGF7& PolynomGF7::MulGF7_2n(PolynomGF7 &a, PolynomGF7 &b,PolynomGF7 &c, PolynomGF7 &d, PolynomGF7 &module,PolynomGF7 *g)
         {
           PolynomGF7 copy_a(a),copy_b(b),copy_c(c),copy_d(d);
           PolynomGF7 e,gg,r1,r2;
           e = r1.ModMul(copy_a,copy_c,module);
           gg = r2.ModMul(copy_b,copy_d,module);
           std::string s = gg.ToString();
           *g = gg;
           *this = e;
           return *this;
         }
         PolynomGF7& PolynomGF7::MulGF7_14n(PolynomGF7 &a, PolynomGF7 &b,PolynomGF7 &module)
         {
 /*          PolynomGF7 copy_a(a),copy_b(b);
           PolynomGF7 e,gg,r1,r2;
           e = r1.ModMul(copy_a,copy_c,module);
           gg = r2.ModMul(copy_b,copy_d,module);
           std::string s = gg.ToString();
           *g = gg;
           *this = e;   */
           return *this;
         }
	PolynomGF7 PolynomGF7::operator/(const PolynomGF7 &b) const
	{
		PolynomGF7 result;
		return result.Div(*this, b);
	}
	PolynomGF7& PolynomGF7::operator/=(const PolynomGF7 &polynom)
	{
		return Div(*this, polynom);
	}
	int intPow(int x, int p) {
	  if (p == 0) return 1;
	  if (p == 1) return x;
	  return x * intPow(x, p-1);
	}
	PolynomGF7& PolynomGF7::Div(const PolynomGF7 &a, const PolynomGF7 &b, PolynomGF7 *remainder)
	{
               	if(this == remainder)
			throw new Exception("×àñòíîå è îñòàòîê íå ìîãóò áûòü îäíèì ÷èñëîì");
		if(b.isZero())
			throw new Exception("Äåëåíèå íà íîëü");

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

		PolynomGF7 copy_a(a), copy_b(b);
                PolynomGF7 buf("1");
                PolynomGF7 result;
                
                uint lengthA;
                uint lengthB;

                lengthA = copy_a.getNumberBits()-1;
                lengthB = copy_b.getNumberBits()-1;
                copy_b <<= lengthA-lengthB;
                for (uint i=0;i<=(lengthA-lengthB);i++)
                {
                     buf.setBit(0, copy_a.getBit(lengthA-i)*intPow(copy_b.getBit(lengthA-i), 5) % 7);
                     result = result+buf;
                     
                     result<<=1;
                     copy_a = copy_a-copy_b*buf;
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

//***************************    Îïåðàöèÿ ïðèâåäåíèÿ ïî ìîäóëþ    ******************************
	//simple method
	PolynomGF7 operator%(const PolynomGF7 &a, const PolynomGF7 &b)
	{
		PolynomGF7 result, copy_a(a), copy_b(b);
		return result.Mod(copy_a, copy_b);
	}

	//simple method
	PolynomGF7& PolynomGF7::operator%=(PolynomGF7 &polynom)
	{
		return Mod(*this, polynom);
	}

	//(c) Mamontov, TEST(Polynom, Mod)
	PolynomGF7& PolynomGF7::Mod(PolynomGF7 &a, PolynomGF7 &f)
	{
                if(a.isZero() && f.isZero())
		  return setZero();
                uint aa,b,m,k,t,len_a;
                PolynomGF7 q,r,q1,r1;
                std::string f_str = f.ToString();
                k = f_str.find_first_not_of('0',1);
                b = f.getBit(k);
                m = f_str.length()-1;
                aa = f.getBit(0);
                //if(m%7 == 0 || m%2 == 0 || k > m/2)
                //      throw new Exception("îøèáêà âî âõîäíîì òðåõ÷ëåíå");
                //else
                {
                  t = m - 1 +k;
                  len_a = a.ToString().length();
                  int j = 0;
                  for(int i = t; i < len_a; i++)
                  {
                        q.setBit(j,a.getBit(i));
                        j++;
                  }
//                  std::string str = q.ToString();
                  for(int i = 0; i < t; i++)
                  {
                        r.setBit(i,a.getBit(i));
                  }
//                  str = r.ToString();
                  int deg_1,deg_2;
                  deg_1 = 2*t-2*m+1;
                  deg_2 = 2*t-2*m+1-k;
                  PolynomGF7 x1,x2,six("6"),bx,ax;
                  bx.setBit(0,b);
                  ax.setBit(0,aa);
                  x1.setBit(deg_1,1);
                  x2.setBit(deg_2,1);
                  r = r+six*bx*q*x1+six*ax*q*x2;
//                  str = (six*bx*q*x1).ToString();
//                  str = (ax*q*x2).ToString();
//                  str = r.ToString();
                  len_a = r.ToString().length();
                  if(len_a == m)
                  {
                        *this = r;
                        return *this;
                  }
                  else
                  {     j=0;
                        for(int i = m; i < len_a; i++)
                        {
                                q1.setBit(j,r.getBit(i));
                                j++;
                        }
//                        str = q1.ToString();

                       for(int i = 0; i < m; i++)
                        {
                                r1.setBit(i,r.getBit(i));
                        }
 //                       str = r1.ToString();
                        PolynomGF7 x3;
                        x3.setBit(k,1);
                        r1 = r1+six*bx*x3*q1+six*ax*q1;
                        *this = r1;
 //                       str = r1.ToString();
                        return *this;
                  }
                }
		return *this;
	}
//------------------------------------------------------------------------------
PolynomGF7& PolynomGF7::Generate(const PolynomGF7& module)
{   int q;
    std::string A;
    uint len=module.getNumberBits();
    for(uint i1=0;i1<len;i1++)
      {
        q=rand()%7;
        if(q==0) A.append("0");
        if(q==1) A.append("1");
        if(q==2) A.append("2");
        if(q==3) A.append("3");
        if(q==4) A.append("4");
        if(q==5) A.append("5");
        if(q==6) A.append("6");

       }
    PolynomGF7 res,m(module);
    res.Parse(A);
    res%=m;
    *this=res;
    return *this;
}

     PolynomGF7& PolynomGF7::Generate(const PolynomGF7& module, const PolynomGF7& m)
     {  int q;
        std::string A;
        uint len=module.getNumberBits();
        uint lenm=m.getNumberBits();
        A=m.ToString();
       for(uint i1=lenm+1;i1<len;i1++)
       {
         q=rand()%7;
         if(q==0) A.append("0");
         if(q==1) A.append("1");
         if(q==2) A.append("2");
         if(q==3) A.append("3");
        if(q==4) A.append("4");
        if(q==5) A.append("5");
        if(q==6) A.append("6");

       }
       PolynomGF7 res,mm(module);
       res.Parse(A);
       res%=mm;
       *this=res;
       return *this;
     }
        uint PolynomGF7::getNumberBits() const
	{
            uint numA1,numA0,numA2;
            numA1 = A1.getNumberBits();
            numA0 = A0.getNumberBits();
            numA2 = A2.getNumberBits();

	    if( numA1 >= numA0  && numA1 >= numA2)
	    	return numA1;
        else if( numA0 >= numA1  && numA0 >= numA2)
                return numA0;
        else
            return numA2;
     	}
  PolynomGF7& PolynomGF7::PowSeven_29(PolynomGF7 &a,PolynomGF7 &module,PolynomGF7 &b,PolynomGF7 &axx)
  {
        std::string ziro = "0";
        std::string aa = a.ToString();
        std::string a_0,a_1,a_2,a_3,a_4,a_5,a_6,a_7,a_8,a_9,a_10,a_11,a_12,a_13,a_14,a_15,a_16,a_17,a_18,a_19,a_20,a_21,a_22,a_23,a_24,a_25,a_26,a_27,a_28;
        a_0 = aa[0]; a_1 = aa[1];a_2 = aa[2];a_3 = aa[3];a_4 = aa[4];a_5 = aa[5];a_6 = aa[6];a_7 = aa[7];a_8 = aa[8];a_9 = aa[9];
        a_10 = aa[10];a_11 = aa[11];a_12 = aa[12];a_13 = aa[13];a_14 = aa[14];a_15 = aa[15];a_16 = aa[16];a_17 = aa[17];a_18 = aa[18];a_19 = aa[19];
        a_20 = aa[20];a_21 = aa[21];a_22 = aa[22];a_23 = aa[23];a_24 = aa[24];a_25 = aa[25];a_26 = aa[26];a_27 = aa[27];a_28 = aa[28];
        std::string c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23,c24,c25,c26,c27,c28;
        PolynomGF7 r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28;
        std::string bb_s,ax_s;
        bb_s = b.ToString();
        ax_s = axx.ToString();
        Integer bb(bb_s),ax(ax_s);
        Integer a0(a_0),a1(a_1),a2(a_2),a3(a_3),a4(a_4),a5(a_5),a6(a_6),a7(a_7),a8(a_8),a9(a_9),a10(a_10),a11(a_11),a12(a_12),a13(a_13),a14(a_14),a15(a_15),a16(a_16),a17(a_17),a18(a_18),a19(a_19),a20(a_20),a21(a_21),a22(a_22),a23(a_23),a24(a_24),a25(a_25),a26(a_26),a27(a_27),a28(a_28);
        Integer c0_0 , c0_1,c0_2,c0_3,c0_4,c0_5,c0_6,c0_7,c0_8,c0_9,c0_10,c0_11,c0_12,c0_13,c0_14,c0_15,c0_16,c0_17,c0_18,c0_19,c0_20,c0_21,c0_22,c0_23,c0_24,c0_25,c0_26,c0_27,c0_28;
        c0_0 = c0_1=c0_2=c0_3=c0_4=c0_5=c0_6=c0_7=c0_8=c0_9=c0_10=c0_11=c0_12=c0_13=c0_14=c0_15=c0_16=c0_17=c0_18=c0_19=c0_20=c0_21=c0_22=c0_23=c0_24=c0_25=c0_26=c0_27=c0_28=0;
        Integer c1_0 , c1_1,c1_2,c1_3,c1_4,c1_5,c1_6,c1_7,c1_8,c1_9,c1_10,c1_11,c1_12,c1_13,c1_14,c1_15,c1_16,c1_17,c1_18,c1_19,c1_20,c1_21,c1_22,c1_23,c1_24,c1_25,c1_26,c1_27,c1_28;
        c1_0 = c1_1=c1_2=c1_3=c1_4=c1_5=c1_6=c1_7=c1_8=c1_9=c1_10=c1_11=c1_12=c1_13=c1_14=c1_15=c1_16=c1_17=c1_18=c1_19=c1_20=c1_21=c1_22=c1_23=c1_24=c1_25=c1_26=c1_27=c1_28=0;
        Integer c2_0,c2_1,c2_2,c2_3,c2_4,c2_5,c2_6,c2_7,c2_8,c2_9,c2_10,c2_11,c2_12,c2_13,c2_14,c2_15,c2_16,c2_17,c2_18,c2_19,c2_20,c2_21,c2_22,c2_23,c2_24,c2_25,c2_26,c2_27,c2_28;
        c2_0=c2_1=c2_2=c2_3=c2_4=c2_5=c2_6=c2_7=c2_8=c2_9=c2_10=c2_11=c2_12=c2_13=c2_14=c2_15=c2_16=c2_17=c2_18=c2_19=c2_20=c2_21=c2_22=c2_23=c2_24=c2_25=c2_26=c2_27=c2_28=0;
        Integer c3_0,c3_1,c3_2,c3_3,c3_4,c3_5,c3_6,c3_7,c3_8,c3_9,c3_10,c3_11,c3_12,c3_13,c3_14,c3_15,c3_16,c3_17,c3_18,c3_19,c3_20,c3_21,c3_22,c3_23,c3_24,c3_25,c3_26,c3_27,c3_28;
        c3_0=c3_1=c3_2=c3_3=c3_4=c3_5=c3_6=c3_7=c3_8=c3_9=c3_10=c3_11=c3_12=c3_13=c3_14=c3_15=c3_16=c3_17=c3_18=c3_19=c3_20=c3_21=c3_22=c3_23=c3_24=c3_25=c3_26=c3_27=c3_28=0;
        Integer c4_0,c4_1,c4_2,c4_3,c4_4,c4_5,c4_6,c4_7,c4_8,c4_9,c4_10,c4_11,c4_12,c4_13,c4_14,c4_15,c4_16,c4_17,c4_18,c4_19,c4_20,c4_21,c4_22,c4_23,c4_24,c4_25,c4_26,c4_27,c4_28;
        c4_0=c4_1=c4_2=c4_3=c4_4=c4_5=c4_6=c4_7=c4_8=c4_9=c4_10=c4_11=c4_12=c4_13=c4_14=c4_15=c4_16=c4_17=c4_18=c4_19=c4_20=c4_21=c4_22=c4_23=c4_24=c4_25=c4_26=c4_27=c4_28=0;
        Integer c5_0,c5_1,c5_2,c5_3,c5_4,c5_5,c5_6,c5_7,c5_8,c5_9,c5_10,c5_11,c5_12,c5_13,c5_14,c5_15,c5_16,c5_17,c5_18,c5_19,c5_20,c5_21,c5_22,c5_23,c5_24,c5_25,c5_26,c5_27,c5_28;
        c5_0=c5_1=c5_2=c5_3=c5_4=c5_5=c5_6=c5_7=c5_8=c5_9=c5_10=c5_11=c5_12=c5_13=c5_14=c5_15=c5_16=c5_17=c5_18=c5_19=c5_20=c5_21=c5_22=c5_23=c5_24=c5_25=c5_26=c5_27=c5_28=0;
        Integer c6_0,c6_1,c6_2,c6_3,c6_4,c6_5,c6_6,c6_7,c6_8,c6_9,c6_10,c6_11,c6_12,c6_13,c6_14,c6_15,c6_16,c6_17,c6_18,c6_19,c6_20,c6_21,c6_22,c6_23,c6_24,c6_25,c6_26,c6_27,c6_28;
        c6_0=c6_1=c6_2=c6_3=c6_4=c6_5=c6_6=c6_7=c6_8=c6_9=c6_10=c6_11=c6_12=c6_13=c6_14=c6_15=c6_16=c6_17=c6_18=c6_19=c6_20=c6_21=c6_22=c6_23=c6_24=c6_25=c6_26=c6_27=c6_28=0;

        Integer minus("6"),three("3");
        //---------------------------------------------------------------------
         //a1 = a1 + minus*a5*three + a9*three + minus*three*a13 + a17*three + minus*a21*three + a25*three;
         //a2 = a2 + minus*a6*three + a10*three + minus*three*a14 + a18*three + minus*a22*three + a26*three;
         //a3 = a3 + minus*a7*three + a11*three + minus*three*a15 + a19*three + minus*three*a23  + a27*three;
         //a4 = a4 + minus*a8*three + a12*three + minus*a16*three + a20*three + minus*a24*three + a28*three;
        c0_0 = a0;
        c0_1 = a1;
        c0_2 = a2;
        c0_3 = a3;
        c0_4 = a4;
        c0_5 = a5;
        c0_6 = a6;
        c0_7 = a7;
        c0_8 = a8;
        c0_9 = a9;
        c0_10 = a10;
        c0_11 = a11;
        c0_12 = a12;
        c0_13 = a13;
        c0_14 = a14;
        c0_15 = a15;
        c0_16 = a16;
        c0_17 = a17;
        c0_18 = a18;
        c0_19 = a19;
        c0_20 = a20;
        c0_21 = a21;
        c0_22 = a22;
        c0_23 = a23;
        c0_24 = a24;
        c0_25 = a25;
        c0_26 = a26;
        c0_27 = a27;
        c0_28 = a28;

        //---------------------------------------------------------------------
        c0_0 = minus*4*bb;
        c0_1 = minus*5*bb;
        c0_2 = minus*6*bb;
        c0_3 = minus*7*bb;
        //---------------------------------------------------------------------
        c1_0 = minus*4*ax;
        c1_1 = minus*5*ax;
        c1_2 = minus*6*ax;
        c1_3 = minus*7*ax;
        //---------------------------------------------------------------------
        c2_0 = c2_0+minus*4*ax;
        c2_1 = c2_1+minus*5*ax;
        c2_2 = c2_2+minus*6*ax;
        c2_3 = c2_3+minus*7*ax;
        c2_4 = minus*8*bb;
        c2_5 = minus*9*bb;
        c2_6 = minus*10*bb;
        c2_7 = minus*11*bb;
        c2_2 = minus*6*bb+minus*c2_6*ax;
        c2_3 = minus*7*bb+minus*c2_7*ax;
        c2_0 = minus*4*bb+minus*c2_4*ax;
        c2_1 = minus*5*bb+minus*c2_5*ax;
        //---------------------------------------------------------------------
        c3_0 = c3_0+minus*4*ax+8*ax*ax;
        c3_1 = c3_1+minus*5*ax+9*ax*ax;
        c3_2 = c3_2+minus*6*ax+10*ax*ax;
        c3_3 = c3_3+minus*7*ax+11*ax*ax;
        c3_8 = minus*12*bb;
        c3_9 = minus*13*bb;
        c3_10 = minus*14*bb;
        c3_11 = minus*15*bb;
        c3_6 = minus*10*bb+minus*c3_10*ax;
        c3_7 = minus*11*bb+minus*c3_11*ax;
        c3_4 = minus*8*bb+minus*c3_8*ax;
        c3_5 = minus*9*bb+minus*c3_9*ax;
        //---------------------------------------------------------------------
        c4_0 = c4_0+minus*4*ax+8*ax*ax+minus*12*ax*ax*ax;
        c4_1 = c4_1+minus*5*ax+9*ax*ax+minus*13*ax*ax*ax;
        c4_2 = c4_2+minus*6*ax+10*ax*ax+minus*14*ax*ax*ax;
        c4_3 = c4_3+minus*7*ax+11*ax*ax+minus*15*ax*ax*ax;
        c4_12 = minus*16*bb;
        c4_13 = minus*17*bb;
        c4_14 = minus*18*bb;
        c4_15 = minus*19*bb;
        c4_10 = minus*14*bb+minus*c4_14*ax;
        c4_11 = minus*15*bb+minus*c4_15*ax;
        c4_8 = minus*12*bb+minus*c4_12*ax;
        c4_9 = minus*13*bb+minus*c4_13*ax;
        c4_6 = minus*10*bb+minus*c4_10*ax;
        c4_7 = minus*11*bb+minus*c4_11*ax;
        c4_4 = minus*8*bb+minus*c4_8*ax;
        c4_5 = minus*9*bb+minus*c4_9*ax;
        c4_2 = minus*6*bb+minus*c4_6*ax;
        c4_3 = minus*7*bb+minus*c4_7*ax;
        c4_0 = minus*4*bb+minus*c4_4*ax;
        c4_1 = minus*5*bb+minus*c4_5*ax;

        //---------------------------------------------------------------------
        c5_0 = c5_0+minus*4*ax+8*ax*ax+minus*12*ax*ax*ax+16*ax*ax*ax*ax;
        c5_1 = c5_1+minus*5*ax+9*ax*ax+minus*13*ax*ax*ax+17*ax*ax*ax*ax;
        c5_2 = c5_2+minus*6*ax+10*ax*ax+minus*14*ax*ax*ax+18*ax*ax*ax*ax;
        c5_3 = c5_3+minus*7*ax+11*ax*ax+minus*15*ax*ax*ax+19*ax*ax*ax*ax;
        c5_16 = minus*20*bb;
        c5_17 = minus*21*bb;
        c5_18 = minus*22*bb;
        c5_19 = minus*23*bb;
        c5_14 = minus*18*bb+minus*c5_18*ax;
        c5_15 = minus*19*bb+minus*c5_19*ax;
        c5_12 = minus*16*bb+minus*c5_16*ax;
        c5_13 = minus*17*bb+minus*c5_17*ax;
        c5_10 = minus*14*bb+minus*c5_14*ax;
        c5_11 = minus*15*bb+minus*c5_15*ax;
        c5_8 = minus*12*bb+minus*c5_12*ax;
        c5_9 = minus*13*bb+minus*c5_13*ax;
        c5_6 = minus*10*bb+minus*c5_10*ax;
        c5_7 = minus*11*bb+minus*c5_11*ax;
        c5_4 = minus*8*bb+minus*c5_8*ax;
        c5_5 = minus*9*bb+minus*c5_9*ax;
        c5_2 = minus*6*bb+minus*c5_6*ax;
        c5_3 = minus*7*bb+minus*c5_7*ax;
        c5_0 = minus*20*ax*ax*ax*ax;//minus*4*bb+minus*c5_4*ax;
        c5_1 = minus*5*bb+minus*c5_5*ax;
        //---------------------------------------------------------------------
        c6_0 = c6_0+minus*4*ax+8*ax*ax+minus*12*ax*ax*ax+16*ax*ax*ax*ax+minus*20*ax*ax*ax*ax*ax;
        c6_1 = c6_1+minus*5*ax+9*ax*ax+minus*13*ax*ax*ax+17*ax*ax*ax*ax+minus*21*ax*ax*ax*ax*ax;
        c6_2 = c6_2+minus*6*ax+10*ax*ax+minus*14*ax*ax*ax+18*ax*ax*ax*ax+minus*22*ax*ax*ax*ax*ax;
        c6_3 = c6_3+minus*7*ax+11*ax*ax+minus*15*ax*ax*ax+19*ax*ax*ax*ax+minus*23*ax*ax*ax*ax*ax;
        c6_20 = minus*25*bb;
        c6_21 = minus*26*bb;
        c6_22 = minus*27*bb;
        c6_23 = minus*28*bb;
        c6_18 = minus*23*bb+minus*c6_22*ax;
        c6_19 = minus*24*bb+minus*c6_23*ax;
        c6_16 = minus*21*bb+minus*c6_20*ax;
        c6_17 = minus*22*bb+minus*c6_21*ax;
        c6_14 = minus*19*bb+minus*c6_18*ax;
        c6_15 = minus*20*bb+minus*c6_19*ax;
        c6_12 = minus*17*bb+minus*c6_16*ax;
        c6_13 = minus*18*bb+minus*c6_17*ax;
        c6_10 = minus*15*bb+minus*c6_14*ax;
        c6_11 = minus*16*bb+minus*c6_15*ax;
        c6_8 = minus*13*bb+minus*c6_12*ax;
        c6_9 = minus*14*bb+minus*c6_13*ax;
        c6_6 = minus*11*bb+minus*c6_10*ax;
        c6_7 = minus*12*bb+minus*c6_11*ax;
        c6_4 = minus*9*bb+minus*c6_8*ax;
        c6_5 = minus*10*bb+minus*c6_9*ax;
        c6_2 = minus*7*bb+minus*c6_6*ax;
        c6_3 = minus*8*bb+minus*c6_7*ax;
        c6_0 = minus*5*bb+minus*c6_4*ax;
        c6_1 = minus*6*bb+minus*c6_5*ax;
        //---------------------------------------------------------------------
        c0_0 = c0_0;
        c0_1 = c0_1+minus*5*ax+9*ax*ax+minus*13*ax*ax*ax+17*ax*ax*ax*ax+minus*21*ax*ax*ax*ax*ax+25*ax*ax*ax*ax*ax*ax;
        c0_2 = c0_2+minus*6*ax+10*ax*ax+minus*14*ax*ax*ax+18*ax*ax*ax*ax+minus*22*ax*ax*ax*ax*ax+26*ax*ax*ax*ax*ax*ax;
        c0_3 = c0_3+minus*7*ax+11*ax*ax+minus*15*ax*ax*ax+19*ax*ax*ax*ax+minus*23*ax*ax*ax*ax*ax+27*ax*ax*ax*ax*ax*ax;
        c0_4 = c0_4+minus*8*ax+12*ax*ax+minus*16*ax*ax*ax+20*ax*ax*ax*ax+minus*24*ax*ax*ax*ax*ax+28*ax*ax*ax*ax*ax*ax;
        //-----------------------------------------------------------------------------
        c0 = (a0%7).ToString();
        c1 = (c1_0%7).ToString();
        c2 = (c2_0%7).ToString();
        c3 = (c3_0%7).ToString();
        c4 = (c4_0%7).ToString();
        c5 = (c5_0%7).ToString();
        c6 = (c6_0%7).ToString();
        c7 = (a1%7).ToString();
        c8 = (c1_1%7).ToString();;
        c9 = (c2_1%7).ToString();
        c10 = (c3_1%7).ToString();
        c11 = (c4_1%7).ToString();
        c12 = (c5_1%7).ToString();
        c13 = (c6_1%7).ToString();
        c14 = (a2%7).ToString();;
        c15 = (c1_2%7).ToString();
        c16 = (c2_2%7).ToString();
        c17 = (c3_2%7).ToString();
        c18 = (c4_2%7).ToString();
        c19 = (c5_2%7).ToString();
        c20 = (c6_2%7).ToString();
        c21 = (a3%7).ToString();
        c22 = (c1_3%7).ToString();
        c23 = (c2_3%7).ToString();
        c24 = (c3_3%7).ToString();
        c25 = (c1_4%7).ToString();
        c26 = (c1_5%7).ToString();
        c27 = (c1_6%7).ToString();
        c28 = (a4%7).ToString();

        std::string result_s;
        result_s.append(c0);result_s.append(c1);result_s.append(c2);result_s.append(c3);result_s.append(c4);result_s.append(c5);
        result_s.append(c6);result_s.append(c7);result_s.append(c8);result_s.append(c9);result_s.append(c10);result_s.append(c11);
        result_s.append(c12);result_s.append(c13);result_s.append(c14);result_s.append(c15);result_s.append(c16);result_s.append(c17);
        result_s.append(c18);result_s.append(c19);result_s.append(c20);result_s.append(c21);result_s.append(c22);result_s.append(c23);
        result_s.append(c24);result_s.append(c25);result_s.append(c26);result_s.append(c27);result_s.append(c28);
        PolynomGF7 rr(result_s);
        *this = rr;
        return *this;
  }

  PolynomGF7& PolynomGF7::Pow(PolynomGF7 &a, const Integer &n,PolynomGF7 &module)
  {
    if(a.isZero() == true)
    {
        *this = a;
        return *this;
    }
    if(n.isNegative())
        throw std::domain_error("×èñëî n - îòðèöàòåëüíîå ðåçóëüòàò íå îïðåäåëåí");
//    if(a.getModule().isIrreducible() == false)
//                        throw new Exception("f(x) - äîëæåí áûòü íåïðèâîäèì");
    //int len = atoi(n.ToString().c_str());
   std::vector<Integer> m;
    int num_bit;
    num_bit = sevendiv(&m,n);
    std::string s = m[0].ToString();
    PolynomGF7 c,result("1"),r2;
    s = module.ToString();
   // result.setOne();
    //    std::string m1 = a._module.ToString();
    PolynomGF7 one("1");
    PolynomGF7 a_2,a_3,a_4,a_5,a_6;
    a_2.ModMul(a,a,module);
    a_3.ModMul(a_2,a,module);
    a_4.ModMul(a_3,a,module);
    a_5.ModMul(a_4,a,module);
    a_6.ModMul(a_5,a,module);

    Integer copy_n(n);
    //result.setOne();
    for(int i=1;i<=num_bit+1;i++)
    {
        c.ModMul(result,result,module);
        s = c.ToString();
        c.ModMul(c,result,module);
        s = c.ToString();
        c.ModMul(c,result,module);
        s = c.ToString();
        c.ModMul(c,result,module);
        s = c.ToString();
        c.ModMul(c,result,module);
        s = c.ToString();
        c.ModMul(c,result,module);
        s = c.ToString();
        result = c;
        s = result.ToString();
        if(m[num_bit + 1 - i] == 1)
        {
            result.ModMul(result,a,module);
            s = result.ToString();
        }
        else if(m[num_bit + 1 - i] == 2)
        {
            //a = a*a;
            result.ModMul(result,a_2,module);
        }
        else if(m[num_bit + 1 - i] == 3)
        {
            //a = a*a*a;
            result.ModMul(result,a_3,module);
        }
        else if(m[num_bit + 1 - i] == 4)
        {
            //a = a*a*a*a;
            result.ModMul(result,a_4,module);
        }
        else if(m[num_bit + 1 - i] == 5)
        {
            //a = a*a*a*a*a;
            result.ModMul(result,a_5,module);
        }
        else if(m[num_bit + 1 - i] == 6)
        {
            //a = a*a*a*a*a*a;
            result.ModMul(result,a_6,module);
        }
        else
            result *= one;
    }
    s = module.ToString();
    result = r2.Mod(result,module);
    *this = result;
        s = result.ToString();
    m.clear();
    return *this;
  }
  //èíâåðòèðîâàíèå
  //------------------------------------------------------------------------------

	//simple method
	PolynomGF7& PolynomGF7::Inverse(PolynomGF7 &module)
	{
		return Inverse(*this, module);
	}
//------------------------------------------------------------------------------

	//(c) Belova, TEST(PolynomGF2_m_4, Inverse)
	PolynomGF7& PolynomGF7::Inverse(PolynomGF7 &polynom, PolynomGF7 &module)
	{
//        if(polynom.getModule().isIrreducible() == false || module.isIrreducible() == false)
//                        throw new Exception("f(x) - äîëæåí áûòü íåïðèâîäèì");
       PolynomGF7_mY_3 d2("000","000","000",module.ToString()),d1("100","000","000",module.ToString()),w1;
        PolynomGF7_mY_3 u("100","000","100",module.ToString()),w,r,c,_c;
        PolynomGF7_mY_3 two("600","000","000",module.ToString());
        int d = 0;
        PolynomGF7 result;
        PolynomGF7 _u,_v,inv,_q,_b,zr("000");
        PolynomGF7_mY_3 v("000","000","000",module.ToString());
        v.setA0(polynom);
        v.setA1(zr);
        v.setA2(zr);
        //u.setA0(module);
        PolynomGF7_mY_3 vv,d11;
         d1.setModule(module);
        d2.setModule(module);
        u.setModule(module);
        v.setModule(module);
         std::string s;
        while(u.deg() != 0 && v.isZero(module) != true)
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
            _v = inv.Pow(_v,Integer(5),module);
            s = _v.ToString();
            _q.Mul(u.getByIndex(u.deg()),inv);
            s = _q.ToString();
            PolynomGF7_mY_3 q;
            q.setModule(module);
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
            v.setModule(module);
            //q = minus.FullMul(two,q);
            r = u + vv.FullMul(v,q);
                   s = r.getA0().ToString();
                   s = r.getA1().ToString();
                   s = r.getA2().ToString();

            c = d2 + d11.FullMul(d1,q);
                   s = c.getA0().ToString();
                   s = c.getA0().ToString();
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
            PolynomGF7_mY_3 pr;
            pr.MonomialMul(c,polynom);
            PolynomGF7 p;
             p = pr.getByIndex(0);
            s = p.ToString();
           _b.Pow(p,Integer(5),module);
            s = _b.ToString();
             c = _c.MonomialMul(c,_b);
                   s = c.getA0().ToString();
                   s = c.getA1().ToString();
                   s = c.getA2().ToString();

        result = c.getA0();
        *this = result;
        return *this;
    }

};


