/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __INTEGER_H__
#define __INTEGER_H__

#include "./AAF/AAL/BasicType.h"
#include <vector>

#if defined(__GNUC__) && !defined(__MINGW32__) || defined (__APPLE_CC__)
	char *itoa(int value, char* result, int base);
	char *ltoa(unsigned int value, char* result, int base);
	char *strrev(char *s);
#endif

namespace AAL
{
	class Converter;
    class DecompositionMember;
    class PrimeTester;
	enum NumericSystem {Hex=16, Dec=10, Oct=8, Bin=2, Tern=3};

	class Integer : public BasicType<AAL::uint>
    {
	private:
		friend class Converter;
		bool _sign;


	//Конструкторы
	private:
		Integer(bool sign, uint numberDigits, uint maximumDigits);
	public:
		Integer();
		Integer(const Integer &integer);
		Integer(const int number);
		Integer(const std::string dataString, NumericSystem system=Dec);

	//Преобразование и считывание из сторк
	public:
		Integer& Parse(const std::string dataString, NumericSystem system=Dec);
		std::string ToString(NumericSystem system=Dec) const;
		std::string strr() { return ToString(Dec); }

	//Методы акцепторы
	private:
		//TODO: Продумать составление таблиц простых чисел меньше 2000!!! :-))
		bool DivTest() const;
		int milerRabinParameter() const;
    bool MillerRabinTest();
  //Методы тестирования простоты
  public:
      bool TestLukaLemera(Integer degree);
      bool ModifiedTestLuka(std::vector<DecompositionMember> vector, Integer Mersen_Number);
      bool TestPoklingtona(std::vector<DecompositionMember> vector, Integer Mersen_Number);
  //Получение разложения из базы
  public:
     friend std::vector<DecompositionMember> GetDecomposition(Integer number, bool &composite);
 //Функция Эйлера
  Integer& Euler(std::vector<DecompositionMember> vector);

 	public:
		Integer& setOne(bool sign = false);
		Integer& setNumber(AAL::uint number, bool sign = false);
		Integer& setZero();
		Integer& setPositive();
		virtual bool isOne() const;
		bool isNumber(AAL::uint number, bool sign=false) const;
		bool isNegative() const;
		bool isPositive() const;
		bool isEven() const;
		bool isOdd() const;
		bool isPrime();
		bool isGenerator(Integer & module, std::vector<DecompositionMember>& mulGroupOrdDecomposition) const;

	//Унарные операции
	public:
		Integer operator-() const;
		Integer& Negate();
		Integer operator+() const;
		Integer operator~() const;
		Integer& OnesComplement();
		Integer& operator++();
		Integer& operator++(int i);
		Integer& operator--();
		Integer& operator--(int i);
		Integer& operator= (const Integer& integer);

	//Операции сравнения
	public:
		Integer Compare(const Integer& integer) const;
		friend bool operator==(const Integer& a, const Integer& b);
		friend bool operator!=(const Integer& a, const Integer& b);
		friend bool operator<(const Integer& a, const Integer& b);
		friend bool operator<=(const Integer& a, const Integer& b);
		friend bool operator>(const Integer& a, const Integer& b);
		friend bool operator>=(const Integer& a, const Integer& b);

	//Логические операции
	private:
		const Integer* Max(const Integer &a, const Integer &b, CompareIndicator ind);
		const Integer* Min(const Integer &a, const Integer &b, CompareIndicator ind);
		void Disposal(const Integer &a, const Integer &b);
	public:
		friend Integer operator^(const Integer &a, const Integer &b);
		Integer& operator^=(Integer &integer);
		Integer& Xor(Integer &a, Integer &b);
		friend Integer operator|(const Integer &a, const Integer &b);
		Integer& operator|=(Integer &integer);
		Integer& Or(Integer &a, Integer &b);
		friend Integer operator&(const Integer &a, const Integer &b);
		Integer& operator&=(Integer &integer);
		Integer& And(Integer &a, Integer &b);
		friend Integer operator!(const Integer &integer);
		Integer& Not(Integer &integer);

	//Операции побитового сдвига
	public:
		Integer operator<<(int numberBits) const;
		Integer& operator<<=(int numberBits);
		Integer operator>>(int numberBits) const;
		Integer& operator>>=(int numberBits);

	//Операция сложения
	private:
		void AddImpl(const Integer *a, const Integer *b);
	public:
		friend Integer operator+(const Integer &a, const Integer &b);
		Integer& operator+=(Integer &integer);
		Integer& Add(const Integer &a, const Integer &b);
		Integer& ModAdd(Integer &a, Integer &b, Integer &module);
  	Integer& ModAddInFp(Integer &a, Integer &b, Integer &module);

	//Операция вычитания
	private:
		void SubImpl(const Integer *a, const Integer *b);
	public:
		friend Integer operator-(const Integer &a, const Integer &b);
		Integer& operator-=(Integer &integer);
		Integer& Sub(Integer &a, Integer &b);
		Integer& ModSub(Integer &a, Integer &b, Integer &module);
    Integer& SubInFp(Integer& a, Integer& b, Integer& module);
	//Операция умножения
	private:
		const Integer *Copy(const Integer &integer, Integer *integerNotEqual = NULL);
		void DisposalCopy(const Integer &integer, Integer *integerNotEqual = NULL);
	public:
		friend Integer operator*(const Integer &a, const Integer &b);
		Integer& operator*=(Integer &integer);
		Integer& Mul(const Integer &a, const Integer &b);
		Integer& ModMul(Integer &a, Integer &b, Integer &module);
    Integer& MulInFp(Integer &a, Integer &b, Integer &module);
	//Операция деление
	private:
		void Div_by_SmallDivider(const Integer *a, const Integer *b, Integer *remainder);
		void DivImpl(const Integer *a, const Integer *b, Integer *remainder);
	public:
		friend Integer operator/(const Integer &a, const Integer &b);
		Integer& operator/=(Integer &integer);
		Integer& Div(Integer &a, Integer &b, Integer *remainder = NULL);
		Integer& ModDiv(Integer &a, Integer &b, Integer &module, Integer *remainder = NULL);
    Integer& DivInFp(Integer &a, Integer &b, Integer &module, Integer *remainder);
	//Операция приведения по модулю
	public:
		friend Integer operator%(const Integer &a, const Integer &b);
		Integer& operator%=(Integer &integer);
		Integer& Mod(Integer &a, Integer &b);
		Integer& ModPositive(Integer &module);

	//Операция возведение в степень
	private:
		Integer& PowImpl(const Integer &a, const Integer &b, const Integer *module = NULL);
	public:
		Integer& Pow(const Integer &a, const Integer &b);
		Integer& ModPow(const Integer &a, const Integer &b, const Integer &module);
    Integer& PowInFp(Integer &a, Integer &b, Integer &module);
	//Операция извлечения квадратного корня
	public:
		Integer& Sqrt();
		Integer& Sqrt(Integer &integer);
    Integer& SquareRoot(Integer &integer);
	//Алгоритмы Евклида
	private:
		Integer &simpleExEuclid(Integer &i, Integer &x, Integer &y);
		Integer *Copy(Integer &i, Integer &iNotEqual_a, Integer &iNotEqual_b);
		void DisposalCopy(Integer &integer, Integer &iNotEqual_a, Integer &iNotEqual_b);
	public:
		Integer& Euclid(const Integer &a, Integer &b);
		Integer& BinaryGCD(Integer &a, Integer &b);
		Integer& ExEuclid(Integer &a, Integer &b, Integer &x, Integer &y);
    Integer& SCM(Integer &a, Integer &b);
	//Генерация чисел
	public:
		//TODO: сделать свой генератор см. Страуструп
		Integer& Generate(AAL::uint numberBits);
		Integer& Generate(const Integer& module);
		Integer& GenerateOdd(AAL::uint numberBits);
		Integer& GenerateOdd(const Integer& module);
		Integer& GeneratePrime(AAL::uint numberBits);
		Integer& GeneratePrime(const Integer& module);
        Integer& GeneratePrime(const Integer& module,std::vector<DecompositionMember> vector);
        Integer& WrappingGenerate(Integer& forwrap, const Integer &module);
	//Вычисление символов Якоби и Лежандра
	public:
		int LegendreSymbol(Integer& module);
		int JacobySymbol(Integer& n);

	//Операции мультипликативной группы и поля
	public:
		bool InMulGroup(Integer &groupModule);
    bool InMulGroupInFp(Integer& groupModule);
		Integer& Inverse(Integer &module);
		Integer& Inverse(Integer &integer, Integer &module);
    Integer& InverseInFp(Integer &integer, Integer &module);
		Integer& ModSqrt(Integer &module);
		//TODO: подрефакторить! :-))
		Integer& ModSqrt(Integer &integer, Integer &module);
    Integer& elementOrder(Integer &groupModule, Integer &num,std::vector<DecompositionMember> vector,const Integer &ord );
    bool isGenerator(Integer &groupModule, Integer &num,std::vector<DecompositionMember> vector, Integer &ord );

    };

};

#include "./AAF/AAL/Algorithms.h"



#endif
