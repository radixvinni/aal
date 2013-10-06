/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __POLYNOMGF3_H__
#define __POLYNOMGF3_H__
#include <list>
#include "BasicType.h"
#include "Integer.h"
#include "Polynom.h"

namespace AAL
{
	class Converter;
	//enum PolynomSystem {BackHex=16, BackBin=2 };

	class PolynomGF3
	{
	private:
		friend class Converter;
        public:
                Polynom A0;
                Polynom A1;
	//Конструкторы
	public:
		PolynomGF3();
    PolynomGF3(const PolynomGF3 &polynom);
		PolynomGF3(const std::string dataString);
    ~PolynomGF3();

	//Преобразование и считывание из сторк
	public:
		PolynomGF3& Parse(const std::string dataString);
		std::string i_to_str(uint x) const;
		std::string ToString() const;
        public:
                bool isZero() const;
                bool isOne() const;
  //Унарные операции
	public:
		//Polynom operator~() const;
		//Polynom& OnesComplement();
		PolynomGF3& operator= (const PolynomGF3& polynom);

        //Методы акцепторы
	public:
    bool isIrreducible() const;
    bool isPrimitivity() const;
    PolynomGF3& setTwo();
		PolynomGF3& setOne();
		PolynomGF3& setZero();
    uint getBit(uint index) const;
    void setBit(uint index, uint bit);
        //Операции сравнения
	public:
    friend bool operator==(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator!=(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator<(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator<=(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator>(const PolynomGF3& a, const PolynomGF3& b);
		friend bool operator>=(const PolynomGF3& a, const PolynomGF3& b);

       //Операции побитового сдвига
	public:
		PolynomGF3 operator<<(int numberBits) const;
		PolynomGF3& operator<<=(int numberBits);
		PolynomGF3 operator>>(int numberBits) const;
		PolynomGF3& operator>>=(int numberBits);


       //Операция сложения
	public:
		friend PolynomGF3 operator+(const PolynomGF3 &a, const PolynomGF3 &b);
		PolynomGF3& operator+=(PolynomGF3 &polynom);
		PolynomGF3& Add(PolynomGF3 &a, PolynomGF3 &b);
    PolynomGF3& ModAdd(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module);
    PolynomGF3& AddInGF3_n(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module);
       //Операция вычитания
	public:
		friend PolynomGF3 operator-(const PolynomGF3 &a, const PolynomGF3 &b);
		PolynomGF3& operator-=(PolynomGF3 &polynom);
		PolynomGF3& Sub(PolynomGF3 &a, PolynomGF3 &b);
		PolynomGF3& ModSub(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3& module);

        //Операция умножения
	public:
		friend PolynomGF3 operator*(const PolynomGF3 &a, const PolynomGF3 &b);
		PolynomGF3& operator*=(PolynomGF3 &polynom);
		PolynomGF3& Mul(PolynomGF3 &a, PolynomGF3 &b);
    PolynomGF3& ModMul(PolynomGF3 a, PolynomGF3 b, PolynomGF3 &module);
    PolynomGF3& MulGF3_n(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 &module);

        //Операция деление
 	public:
		friend PolynomGF3 operator/(const PolynomGF3 &a, const PolynomGF3 &b);
		PolynomGF3& operator/=(PolynomGF3 &polynom);
		PolynomGF3& Div(PolynomGF3 &a, PolynomGF3 &b, PolynomGF3 *remainder = NULL);

        //Операция приведения по модулю
	public:
		friend PolynomGF3 operator%(const PolynomGF3 &a, const PolynomGF3 &b);
		PolynomGF3& operator%=(PolynomGF3 &polynom);
		PolynomGF3& Mod(PolynomGF3 &a, PolynomGF3 &b);
    PolynomGF3& ModPositive(PolynomGF3 &module);
    PolynomGF3& ModPow(PolynomGF3 &a, const Integer &n, PolynomGF3 &module);
    PolynomGF3& Pow(PolynomGF3 &a, Integer &n);
    PolynomGF3& FastCube(PolynomGF3 &a1,int len);

    PolynomGF3& ModPow1(PolynomGF3 &a, PolynomGF3 &b,PolynomGF3 &module);
    PolynomGF3& PowGF3_n(PolynomGF3 &a, Integer &n, PolynomGF3 &module);
    PolynomGF3& Pow1(PolynomGF3 &a, PolynomGF3 &b);
    PolynomGF3& InverseMod1(PolynomGF3 &a,PolynomGF3 &module);
    PolynomGF3& InverseMod(PolynomGF3 &a,PolynomGF3 &module);
  public:
    uint getNumberBits() const;
    uint getFirstTrueBit() const;
    void setNumberDigits(uint numberDigits);
       //Generation
  public:
    PolynomGF3& Generate(const PolynomGF3& module);
    PolynomGF3& Generate(const PolynomGF3& module, const PolynomGF3& m);
    PolynomGF3& GenerateIrreducible(const uint nDegree);
  public:
        PolynomGF3& LegendreSymbol(PolynomGF3 &a, PolynomGF3 &module);
        PolynomGF3& Sqrt(PolynomGF3 &a, PolynomGF3 &module,Integer &s,Integer &T);

  public:
    PolynomGF3& Square1(PolynomGF3 &a,PolynomGF3 &module);
  public:
    //PolynomGF3& ModNew(PolynomGF3 &a, PolynomGF3 &b);

  public:

    PolynomGF3& GCD(const PolynomGF3 &a, PolynomGF3 &b);

//--------------------------------------------------------------------------------
     std::list< std::pair<uint,uint> > getPowersOfPolynom() const;
     std::string ToStringByPowers() const;


	  // Тесты поля на образование ОНБ и ГНБ
      // ОНБ 1
      bool ONB1Test(const uint n) const;
      // ОНБ 2
      bool ONB2Test(const uint n) const;
      // ОНБ 3
      bool ONB3Test(const uint n) const;
      // ГНБ
      bool GNBTest(const uint n, const int type) const;

     //тест образующего элемента и определение порядка элемента в группе
     Integer& elementOrder(PolynomGF3 &groupModule, PolynomGF3 &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
     bool isGenerator(PolynomGF3 &groupModule, PolynomGF3 &polynom,std::vector<DecompositionMember> vector, const Integer &ord);

  };
};
#endif
