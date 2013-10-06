/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include <set>

namespace AAL
{

       struct TWord
  {
   union
   {
     unsigned int a;
      struct
         {
           unsigned int b1:16;
           unsigned int b2:16;

         };
      struct
        {
          unsigned int a1:1;
          unsigned int a2:1;
          unsigned int a3:1;
          unsigned int a4:1;
          unsigned int a5:1;
          unsigned int a6:1;
          unsigned int a7:1;
          unsigned int a8:1;
          unsigned int a9:1;
          unsigned int a10:1;
          unsigned int a11:1;
          unsigned int a12:1;
          unsigned int a13:1;
          unsigned int a14:1;
          unsigned int a15:1;
          unsigned int a16:1;
          unsigned int a17:1;
          unsigned int a18:1;
          unsigned int a19:1;
          unsigned int a20:1;
          unsigned int a21:1;
          unsigned int a22:1;
          unsigned int a23:1;
          unsigned int a24:1;
          unsigned int a25:1;
          unsigned int a26:1;
          unsigned int a27:1;
          unsigned int a28:1;
          unsigned int a29:1;
          unsigned int a30:1;
          unsigned int a31:1;
          unsigned int a32:1;
        };


   };
   };


	class Converter;
  class Matrix;
	enum PolynomSystem {BackHex=16, BackBin=2, BackDec=10};
	class Polynom : public BasicType<uint>
	{
	private:
    friend class Converter;
    friend class PolynomGF3;
    friend class Matrix;
	//Конструкторы
	public:
                static unsigned int *TAB();
                static unsigned int **Pos();
                static unsigned int *GenerateTab();
                static unsigned int **GeneratePos();

		Polynom();
		Polynom(const Polynom &polynom);
		Polynom(const std::string dataString, PolynomSystem system=BackBin);
		Polynom(const std::string dataString, bool in_degres, bool cancel = false);

	//Преобразование и считывание из строк
	public:
		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin, bool cancel = false);
		std::string ToString(PolynomSystem system=BackBin) const;
                std::string ToString(const std::string dataString) const;
                std::string tostring() const;
std::string i_to_str(uint x) const;
	//Методы акцепторы
	public:
		Polynom& setOne();
		Polynom& setPolynom(uint);
		Polynom& setZero();
                Polynom& setUnit(uint degree);
                std::set<uint> getPowersOfPolynom() const;
		bool isPolynom(uint polynom) const;
		bool isNormal() const;
		bool isIrreducible() const;
    bool isPrimitivity() const;
   // Polynom& setUnit(uint degree);

	//Унарные операции
	public:
		Polynom operator~() const;
		Polynom& OnesComplement();
		Polynom& operator= (const Polynom& polynom);

	//Операции сравнения
	public:
		Polynom Compare(const Polynom& polynom) const;
		friend bool operator==(const Polynom& a, const Polynom& b);
		friend bool operator!=(const Polynom& a, const Polynom& b);
		friend bool operator<(const Polynom& a, const Polynom& b);
		friend bool operator<=(const Polynom& a, const Polynom& b);
		friend bool operator>(const Polynom& a, const Polynom& b);
		friend bool operator>=(const Polynom& a, const Polynom& b);

	//Логические операции
	private:
		Polynom* Max(Polynom &a, Polynom &b, CompareIndicator ind);
		Polynom* Min(Polynom &a, Polynom &b, CompareIndicator ind);
		void Disposal(Polynom &a, Polynom &b);
	public:
		friend Polynom operator^(const Polynom &a, const Polynom &b);
		Polynom& operator^=(Polynom &polynom);
		Polynom& Xor(Polynom &a, Polynom &b);
		friend Polynom operator|(const Polynom &a, const Polynom &b);
		Polynom& operator|=(Polynom &polynom);
		Polynom& Or(Polynom &a, const Polynom &b);
		friend Polynom operator&(const Polynom &a, const Polynom &b);
		Polynom& operator&=(Polynom &polynom);
		Polynom& And(Polynom &a, Polynom &b);
		friend Polynom operator!(const Polynom &polynom);
		Polynom& Not(Polynom &polynom);

	//Операции побитового сдвига
	public:
		Polynom operator<<(int numberBits) const;
		Polynom& operator<<=(int numberBits);
		Polynom operator>>(int numberBits) const;
		Polynom& operator>>=(int numberBits);

	//Операция сложения
	public:
		friend Polynom operator+(const Polynom &a, const Polynom &b);
		Polynom& operator+=(Polynom &polynom);
		Polynom& Add(Polynom &a, Polynom &b);
		Polynom& ModAdd(Polynom &a, Polynom &b, Polynom &module);
    Polynom& AddInGF2_n(Polynom &a, Polynom &b, Polynom &module);
	//Операция вычитания
	public:
		friend Polynom operator-(const Polynom &a, const Polynom &b);
		Polynom& operator-=(Polynom &polynom);
		Polynom& Sub(Polynom &a, Polynom &b);
		Polynom& ModSub(Polynom &a, Polynom &b, Polynom &module);
    Polynom& SubInGF2_n(Polynom &a, Polynom &b, Polynom &module);

	//Операция умножения
	//TODO: рефакторинг умножения элементарных многолчленов(создание таблиц умножения).
	private:
		Polynom *Copy(Polynom &polynom, Polynom *polynomNotEqual = NULL);
		void DisposalCopy(Polynom &polynom, Polynom *polynomNotEqual = NULL);
        public:
                  static TWord *WordByWord(TWord a,TWord b,int n);
                  TWord Lop16(TWord a,TWord b);
                  TWord *Lop32(TWord a,TWord b);
                  ushort MulElemPolynoms(uchar u, uchar v);
	public:
		friend Polynom operator*(const Polynom &a, const Polynom &b);
		Polynom& operator*=(Polynom &polynom);
		Polynom& Mul(Polynom &a, Polynom &b);
		Polynom& ModMul(Polynom a, Polynom b, Polynom &module);
        Polynom& MulGF2_n(Polynom &a, Polynom &b, Polynom &module);

	//Операция деление
	//TODO: провести рефакторинг Div - можно ли убрать первую проверку.
	public:
		friend Polynom operator/(const Polynom &a, const Polynom &b);
		Polynom& operator/=(Polynom &polynom);
		Polynom& Div(Polynom &a, const Polynom &b, Polynom *remainder = NULL);
		Polynom& ModDiv(Polynom &a, Polynom &b, Polynom &module, Polynom *remainder = NULL);
    Polynom& DivInGF2_n(Polynom &a, Polynom &b, Polynom &module, Polynom *remainder);
	//Операция приведения по модулю
	//TODO: провести рефакторинг Mod - не считать частное.
	public:
		friend Polynom operator%(const Polynom &a, const Polynom &b);
		Polynom& operator%=(Polynom &polynom);
		Polynom& Mod(Polynom &a, const Polynom &b);
		Polynom& Mod(Polynom &module);
        Polynom& FastMod(Polynom &a, Polynom &b);

	//Операция возведение в степень
	//TODO: провести рефакторинг(создание таблиц).
	private:
		ushort SquareElemPolynom(uchar u);
		Polynom& Square(Polynom &a, Integer &n, Polynom *module = NULL);
		Polynom& PowImpl(Polynom &a, Integer &n, Polynom *module = NULL);
	public:		
		Polynom& Pow(Polynom &a, Integer &n);
		Polynom& ModPow(Polynom &a, Integer &n, Polynom &module);
   	Polynom& PowGF2_n(Polynom &a, Integer &n, Polynom &module);

	//Алгоритмы Евклида
	//TODO: реализовать обычный алгоритм Евклида
        //TODO: Добавить методы для умного копирования объектов
        private:
       		Polynom &simpleExEuclid(Polynom &i, Polynom &x, Polynom &y);
	public:
		Polynom& Euclid(const Polynom &a, Polynom &b);
		Polynom& BinaryGCD(const Polynom &a, Polynom &b);
		Polynom& ExEuclid(Polynom &a, Polynom &b, Polynom &x, Polynom &y);
                
	//Генерация полиномов
	//TODO: Доработать добавив новые методы
	public:
		Polynom& Generate(uint numberBits);
		Polynom& Generate(const Polynom& module);
    Polynom& WrappingGenerate(const Polynom& forwrap, const Polynom &module);
    Polynom& GenerateIrreducible(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree);
    Polynom& GenerateIrreduciblePrimitivity(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree);
    Polynom& GenerateIrreducibleTrinomial(const uint nDegree);
		Polynom& GenerateNormal(uint numberBits);
		Polynom& GenerateNormal(const Polynom& module);
    Polynom& GenerateNormal(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree);
  // Теорема Штильберга-Суона
    bool SchtilbergSuonTheorem(const uint k, const uint n) const;

    std::string ToStringByPowers() const;
 //Арифметика в оптимальных нормальных базисах
  public:
    // Тесты степеней поля на образование ОНБ
    // ОНБ 1
    bool ONB1Test(const uint n) const;
    // ОНБ 2
    bool ONB2Test(const uint n) const;
    // ОНБ 3
    bool ONB3Test(const uint n) const;
    // Генерации оптимального нормального базиса, заданной степени расширения поля
    // вход: n - степень расширения поля
    // выход: b - полином, A - таблица умножения или false - ОНБ 1го типа не существует
    bool GenerateONB1(const uint n, Polynom& b, Matrix& A);
    // вход: n - степень расширения поля
    // выход: b - полином, A - таблица умножения или false - ОНБ 2го типа не существует
    bool GenerateONB2(const uint n, Polynom& b, Matrix& A);
    // вход: n - степень расширения поля
    // выход: b - полином, A - таблица умножения или false - ОНБ 3го типа не существует
    bool GenerateONB3(const uint n, Polynom& b, Matrix& A);
    // вход: n - степень расширения поля
    // выход: b - полином или false - ОНБ 1го типа не существует
    bool GenerateONB1Polynom(const uint n, Polynom& b);
    // вход: n - степень расширения поля
    // выход: b - полином или false - ОНБ 2го типа не существует
    bool GenerateONB2Polynom(const uint n, Polynom& b);
    // вход: n - степень расширения поля
    // выход: b - полином или false - ОНБ 3го типа не существует
    bool GenerateONB3Polynom(const uint n, Polynom& b);

  //Арифметика в гауссовых нормальных базисах
  public:
    // Тесты степеней поля на образование ГНБ
    bool GNBTest(const uint n, const int type) const;

	//Операции мультипликативной группы и поля
	public:
		bool InMulGroup(Polynom &groupModule);
		Polynom& Inverse(Polynom &module);
		Polynom& Inverse(Polynom &polynom, Polynom &module);
    Polynom& InverseGF2_n(Polynom &polynom, Polynom &module);
    Polynom& Trace(Polynom &module);
		Polynom& Trace(Polynom &polynom, Polynom &module);
    Integer& elementOrder(Polynom &groupModule, Polynom &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
    bool isGenerator(Polynom &groupModule, Polynom &polynom,std::vector<DecompositionMember> vector, const Integer &ord);
         Polynom Impl(Polynom& a, Polynom& b);
	};	
};
#endif
