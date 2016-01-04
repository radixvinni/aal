/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __POLYNOMGF7_H__
#define __POLYNOMGF7_H__
#include <list>
#include "BasicType.h"
#include "Integer.h"
#include "Polynom.h"

namespace AAL
{
	class Converter;

	class PolynomGF7
	{
	private:
		friend class Converter;
        public:
                Polynom A0;
                Polynom A1;
                Polynom A2;

	//Êîíñòðóêòîðû
	public:
		PolynomGF7();
    PolynomGF7(const PolynomGF7 &polynom);
		PolynomGF7(const std::string dataString);
    ~PolynomGF7();

	//Ïðåîáðàçîâàíèå è ñ÷èòûâàíèå èç ñòîðê
	public:
       		PolynomGF7& Parse(const std::string dataString);
		std::string ToString() const;
        public:
                bool isZero(PolynomGF7 &module) const;
                bool isZero() const;
                bool isOne() const;

  //Óíàðíûå îïåðàöèè
	public:
		//Polynom operator~() const;
		//Polynom& OnesComplement();
		PolynomGF7& operator= (const PolynomGF7& polynom);

        //Ìåòîäû àêöåïòîðû
	public:
//    bool isIrreducible() const;
//    bool isPrimitivity() const;
    PolynomGF7& setTwo();
		PolynomGF7& setOne();
		PolynomGF7& setZero();
		PolynomGF7& setZero(PolynomGF7 &module);

    uint getBit(uint index) const;
    void setBit(uint index, uint bit);
        //Îïåðàöèè ñðàâíåíèÿ
	public:
    friend bool operator==(const PolynomGF7& a, const PolynomGF7& b);
		friend bool operator!=(const PolynomGF7& a, const PolynomGF7& b);
/*		friend bool operator<(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator<=(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator>(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator>=(const PolynomGF3& a, const PolynomGF3& b);
*/
       //Îïåðàöèè ïîáèòîâîãî ñäâèãà
	public:
		PolynomGF7 operator<<(int numberBits) const;
		PolynomGF7& operator<<=(int numberBits);
		PolynomGF7 operator>>(int numberBits) const;
		PolynomGF7& operator>>=(int numberBits);


       //Îïåðàöèÿ ñëîæåíèÿ
	public:
		PolynomGF7 operator-(const PolynomGF7 &b) const;
		PolynomGF7& operator-=(const PolynomGF7 &polynom);
		PolynomGF7& Sub(const PolynomGF7 &a, const PolynomGF7 &b);

		friend PolynomGF7 operator+(const PolynomGF7 &a, const PolynomGF7 &b);
		PolynomGF7& operator+=(PolynomGF7 &polynom);
		PolynomGF7& Add(PolynomGF7 &a, PolynomGF7 &b);
    PolynomGF7& ModAdd(PolynomGF7 &a, PolynomGF7 &b, PolynomGF7 &module);
/*    PolynomGF3& AddInGF3_n(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module);
       //Îïåðàöèÿ âû÷èòàíèÿ
	public:
		friend PolynomGF3 operator-(const PolynomGF3 &a, const PolynomGF3 &b);
		PolynomGF3& operator-=(PolynomGF3 &polynom);
		PolynomGF3& Sub(PolynomGF3 &a, PolynomGF3 &b);
*/
        //Îïåðàöèÿ óìíîæåíèÿ
	public:
		friend PolynomGF7 operator*(const PolynomGF7 &a, const PolynomGF7 &b);
		PolynomGF7& operator*=(PolynomGF7 &polynom);
		PolynomGF7& Mul(PolynomGF7 a, PolynomGF7 b);
		PolynomGF7& MulToConstant(PolynomGF7 &a, PolynomGF7 &b);

                PolynomGF7& ModMul(PolynomGF7 &a, PolynomGF7 &b, PolynomGF7 &module);

                PolynomGF7& MulGF7_2n(PolynomGF7 &a, PolynomGF7 &b,PolynomGF7 &c, PolynomGF7 &d, PolynomGF7 &module,PolynomGF7 *g = NULL);
                PolynomGF7& MulGF7_14n(PolynomGF7 &a, PolynomGF7 &b,PolynomGF7 &module);

        //Îïåðàöèÿ äåëåíèå
/* 	public:
		friend PolynomGF3 operator/(const PolynomGF3 &a, const PolynomGF3 &b);
		PolynomGF3& operator/=(PolynomGF3 &polynom);
		PolynomGF3& Div(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 *remainder = NULL);
*/
        //Îïåðàöèÿ ïðèâåäåíèÿ ïî ìîäóëþ
	public:
		friend PolynomGF7 operator%(const PolynomGF7 &a, const PolynomGF7 &b);
		PolynomGF7& operator%=(PolynomGF7 &polynom);
		PolynomGF7& Mod(PolynomGF7 &a, PolynomGF7 &b);
                PolynomGF7& Pow(PolynomGF7 &a, const Integer &n,PolynomGF7 &module);
                PolynomGF7& PowSeven_29(PolynomGF7 &a,PolynomGF7 &module,PolynomGF7 &b,PolynomGF7 &ax);

                /*    PolynomGF3& ModPositive(PolynomGF3 &module);
    PolynomGF3& ModPow(PolynomGF3 &a, Integer &n, PolynomGF3 &module);
    PolynomGF3& Pow(PolynomGF3 &a, Integer &n);
    PolynomGF3& ModPow1(PolynomGF3 &a, PolynomGF3 &b,PolynomGF3 &module);
    PolynomGF3& PowGF3_n(PolynomGF3 &a, Integer &n, PolynomGF3 &module);
    PolynomGF3& Pow1(PolynomGF3 &a, PolynomGF3 &b);
    PolynomGF3& InverseMod1(PolynomGF3 &a,PolynomGF3 &module);
    PolynomGF3& InverseMod(PolynomGF3 &a,PolynomGF3 &module);  */
  public:
    uint getNumberBits() const;
/*    uint getFirstTrueBit() const;
    void setNumberDigits(uint ); */
       //Generation
  public:
    PolynomGF7& Generate(const PolynomGF7& module);
    PolynomGF7& Generate(const PolynomGF7& module, const PolynomGF7& m);
    PolynomGF7& Inverse(PolynomGF7 &module);
    PolynomGF7& Inverse(PolynomGF7 &polynom, PolynomGF7 &module);
//    PolynomGF7& GenerateIrreducible(const uint nDegree);
 /*
  public:
    PolynomGF3& Square1(PolynomGF3 &a,PolynomGF3 &module);
  public:
    PolynomGF3& ModNew(PolynomGF3 &a, PolynomGF3 &b);

  public:

    PolynomGF3& GCD(PolynomGF3 &a, PolynomGF3 &b);

//--------------------------------------------------------------------------------
     std::list< std::pair<uint,uint> > getPowersOfPolynom() const;
     std::string ToStringByPowers() const;


	  // Òåñòû ïîëÿ íà îáðàçîâàíèå ÎÍÁ è ÃÍÁ
      // ÎÍÁ 1
      bool ONB1Test(const uint n) const;
      // ÎÍÁ 2
      bool ONB2Test(const uint n) const;
      // ÎÍÁ 3
      bool ONB3Test(const uint n) const;
      // ÃÍÁ
      bool GNBTest(const uint n, const int type) const;

     //òåñò îáðàçóþùåãî ýëåìåíòà è îïðåäåëåíèå ïîðÿäêà ýëåìåíòà â ãðóïïå
     Integer& elementOrder(PolynomGF3 &groupModule, PolynomGF3 &polynom,std::vector<DecompositionMember> vector, Integer &ord );
     bool isGenerator(PolynomGF3 &groupModule, PolynomGF3 &polynom,std::vector<DecompositionMember> vector, Integer &ord);
   */
  };
};
#endif

