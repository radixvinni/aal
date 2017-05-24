/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "Integer.h"
#include "Algorithms.h"
#include <memory>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include "./AAF/AAL/PrimeTester.h"


#if defined(__GNUC__) || defined (__APPLE_CC__)
    /*
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukas Chmela
	 * Released under GPLv3.
	 */
	void _ui64toa(int value, char* result, int base){
        // check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
	}
	char* itoa(int value, char* result, int base){_ui64toa(value, result, base);return result;}
	char* ltoa(unsigned int value, char* result, int base){_ui64toa(value, result, base);return result;}
	#define SWAP(T, a, b) \
        do { T save = (a); (a) = (b); (b) = save; } while (0)
	char* strrev(char *s)
    {
        size_t len = strlen(s);

        if (len > 1) {
            char *a = s;
            char *b = s + len - 1;

            for (; a < b; ++a, --b)
                SWAP(char, *a, *b);
        }

        return s;
    }
#endif

namespace AAL
{
//***********************************  Конструкторы  *******************************************
	//private метод
	Integer::Integer(bool sign, uint numberDigits, uint maximumDigits)
	{
		SetData(numberDigits, maximumDigits, maximumDigits != 0);
		_sign = sign;
	}

	//(c) Mamontov, TEST(Integer, EmptyConstructor)
	Integer::Integer() : BasicType<uint>()
	{
		_sign = false;
	}

	//(c) Mamontov, TEST(Integer, CopyConstructor)
	Integer::Integer(const Integer &integer) : BasicType<uint>(integer)
	{
		_sign = integer._sign;
	}

	//(c) Mamontov, TEST(Integer, IntConstructor)
	Integer::Integer(const int number) : BasicType<uint>(number>0 ? number : -number)
	{
		_sign = number<0;
	}

	//(c) Mamontov, TEST(Integer, StringConstructor)
	Integer::Integer(const std::string dataString, NumericSystem system)
	{
		SetData(0, 0);
		_sign = false;
		Parse(dataString, system);
	}
//**********************************************************************************************

//*************************  Преобразование и считывание из сторк ******************************
	//(c) Mamontov
	Integer& Integer::Parse(const std::string dataString, NumericSystem system)
	{
		if(system != Bin && system != Oct && system != Dec && system != Hex && system != Tern)
			throw new Exception("основание не определено");	//std::invalid_argument(system + " - основание не определено");
		setZero();
		uint length = (uint)dataString.length();
		if(length)
		{
			Integer base(1), digit(1);
			base._digits[0] = system;
			for(uint i=dataString[0]=='-'; i<length; i++)
			{
				digit._digits[0] = base._digits[0];

				if(dataString[i] >= '0' && dataString[i] <= '9')
					digit._digits[0] = dataString[i] - '0';
				else if(dataString[i] >= 'A' && dataString[i] <= 'F')
					digit._digits[0] = dataString[i] - 'A' + 10;
				else if(dataString[i] >= 'a' && dataString[i] <= 'f')
					digit._digits[0] = dataString[i] - 'a' + 10;

				if(digit._digits[0] < base._digits[0])
				{
					Mul(*this, base);
					if(digit._digits[0] != 0)
						Add(*this, digit);
				}
				else
					throw new Exception(std::string("Число задано в непредусмотренном формате:(")+dataString+std::string(")"));
			}
			_sign = dataString[0] == '-';
		}
		return *this;
	}

	//(c) Mamontov
	std::string Integer::ToString(NumericSystem system) const
	{
		if(system != Bin && system != Oct && system != Dec && system != Hex && system != Tern)
			throw new Exception(system + " - основание не определено");

		std::string dataString;
		if(!isZero())
		{
			dataString = "";
			char digit[2];
			Integer quotient(*this), remainder, base(system);

			while(!quotient.isZero())
			{
				remainder.Mod(quotient, base);
				if(!remainder.isZero())
					_ui64toa(remainder._digits[0], &digit[0], system);
				else
					strcpy(&digit[0],"0");

				dataString = digit + dataString;
				quotient.Div(quotient, base);
			}
			if(isNegative())
				dataString = "-" + dataString;
		}
		else
			dataString = "0";
		return dataString;
	}

//**********************************************************************************************

//***************************************  Методы акцепторы   **********************************
	//simple method
	Integer& Integer::setOne(bool sign)
	{
		setOne_Base();
		_sign = sign;
		return *this;
	}

	//simple method
	Integer& Integer::setNumber(uint number, bool sign)
	{
		setNumber_Base(number);
		_sign = sign;
		return *this;
	}

    //simple method
	Integer& Integer::setZero()
	{
		setZero_Base();
		return *this;
	}

	//simple method
	Integer& Integer::setPositive()
	{
		_sign = false;
		return *this;
	}

	//simple property
	bool Integer::isOne() const
	{
		return _numberDigits == 1 && _digits[0] == 1 && !_sign;
	}

	//simple method
	bool Integer::isNumber(uint number, bool sign) const
	{
		return isNumber_Base(number) && _sign == sign;
	}

	//simple property
	bool Integer::isNegative() const
	{
		return !isZero() && _sign;
	}

	//simple property
	bool Integer::isPositive() const
	{
		return !isZero() && !_sign;
	}

	//simple property
	bool Integer::isEven() const
	{
		return !isOdd();
	}

	//simple property
	bool Integer::isOdd() const
	{
		return _numberDigits && (_digits[0]&1);
	}

	//private method
	bool Integer::DivTest() const
	{
		for(uint i=3; i<_digits[0]; i=i+2)
			if(_digits[0]%i == 0)
				return false;
		return true;
	}

	//private method
	int Integer::milerRabinParameter() const
	{
		uint numberBits = getNumberBits();
		if(numberBits <= 75)
			return 100;
		if(numberBits <= 100)
			return 27;
		if(numberBits <= 150)
			return 18;
		if(numberBits <= 200)
			return 15;
		if(numberBits <= 250)
			return 12;
		if(numberBits <= 300)
			return 9;
		if(numberBits <= 350)
			return 8;
		if(numberBits <= 400)
			return 7;
		if(numberBits <= 500)
			return 6;
		if(numberBits <= 600)
			return 5;
		if(numberBits <= 800)
			return 4;
		if(numberBits <= 1250)
			return 3;
		if(numberBits < 2048)
			return 2;
		return 1;
	}

	//private method
	bool Integer::MillerRabinTest()
	{
		if((isEven() && !isNumber(2)) || isOne())
			return false;
		if(*this < 2000)
			return DivTest();

		uint countIteration = milerRabinParameter();
		Integer N1 = *this;
		--N1;
		uint firstTrueBit_N1 = N1.getFirstTrueBit();
		Integer shrN1 = N1;
		shrN1 >>= firstTrueBit_N1;

		Integer y[2], oDword;
		y[0].Relocation(_numberDigits<<1);
		y[1].Relocation(_numberDigits<<1);

		for(uint i=0,j=3,k,dest=1,source=0; i<countIteration; ++i, j+=2, dest=1, source=0)
		{
			for(k=2; j%k!=0; j+=2)
				for(;k<=std::sqrt((double)j) && j%k!=0; k++);

			oDword.setNumber(j);
			y[0].ModPow(oDword, shrN1, *this);
			if(!y[0].isOne() && y[0] != N1)
			{
				for(k=1; k<firstTrueBit_N1 && y[source]!=N1; k++)
				{
					y[dest].ModMul(y[source],y[source], *this);
					source=dest;
					dest=1-dest;
					if(y[source].isOne())
						return false;
				}
				if(y[source]!=N1)
					return false;
			}
		}
		return true;
	}
//Методы тестирования простоты
      bool Integer::TestLukaLemera(Integer degree){
          Integer  Mersen_Number = Pow(2,degree) - 1;
          if(Mersen_Number.MillerRabinTest())
          {
            PrimeTester tester(Mersen_Number);
            return tester.TestLukaLemera( degree);
          }
          return false;
      }
      bool Integer::ModifiedTestLuka(std::vector<DecompositionMember> vector, Integer Mersen_Number){
        if(vector.size() >=1)
          {
            PrimeTester tester(Mersen_Number);
            if(Mersen_Number.MillerRabinTest() == true)
            {
                return tester.ModifiedTestLuka( vector);
            }
            return false;
           }
        else
           throw new Exception("Введите разложение n-1 (или p-1)");
      }
      bool Integer::TestPoklingtona(std::vector<DecompositionMember> vector, Integer Mersen_Number){
          if(vector.size() >=1)
          {
           PrimeTester tester(Mersen_Number);
           if(Mersen_Number.MillerRabinTest() == true)
           {
                return tester.TestPoklingtona(vector);
           }
           return false;
          }
          else
           throw new Exception("Введите разложение n-1 (или p-1)");
      }
//Получение разложения из базы
      std::vector<DecompositionMember> GetDecomposition(const Integer number, bool &composite)
	  {
		return DecompositionManager::Instance().getDecomposition(number, &composite);
      }
 //Функция Эйлера
  Integer& Integer::Euler(std::vector<DecompositionMember> vector)
  {
    if(vector.size() >= 1)
    { std::vector<DecompositionMember>::iterator it;
     Integer euler = 1;
     for(it = vector.begin(); it != vector.end(); it++)
     {
      Integer num(it->getNumber());
      Integer deg(it->getDegree());
      Integer rez;
      if(deg == 1)
        rez = euler*(num - 1);
      else
        rez = euler*Mul(num,deg - 1)*(num - 1);
      euler = rez;
     }
     return *this = euler;
    }
    else
      throw new Exception("Введите разложение порядка группы");
  }

	//(c) Mamontov, TEST(Integer, isPrime)
	bool Integer::isPrime()
	{
		if(isNegative())
			return (-(*this)).MillerRabinTest();
		return MillerRabinTest();
	}
        //(c) Morozov, TEST(Integer, isGenerator)
        bool Integer::isGenerator(Integer & module, std::vector<DecompositionMember>& mulGroupOrdDecomposition) const
        {
                if(!module.isPrime())
                        throw new Exception("Модуль должен быть простым числом");

                if(isZero() || isOne())
                        return false;

                Integer mulGroupOrd(module);
                mulGroupOrd--;

                if(!DecompositionMember::isRightDecomposition(mulGroupOrd, mulGroupOrdDecomposition))
                        throw new Exception("Введите разложение порядка группы");

                std::vector<DecompositionMember>::iterator it = mulGroupOrdDecomposition.begin();
                while(it != mulGroupOrdDecomposition.end())
                {
                        Integer number(it->getNumber());
                        Integer degree;
                        degree.Div(mulGroupOrd, number, NULL);
                        Integer result;
                        if(result.ModPow(const_cast<Integer &>(*this), degree, module).isOne())
                                return false;

                        ++it;
                }

                return true;
        }
//**********************************************************************************************

//************************************  Унарные операции   *************************************
	//(c) Mamontov, TEST(Integer, unaryOperatorSub)
	Integer Integer::operator-() const
	{
		Integer result(*this);
		return result.Negate();
	}

	//(c) Mamontov, TEST(Integer, Negate)
	Integer& Integer::Negate()
	{
		_sign = !_sign;
		return *this;
	}

	//simple method
	Integer Integer::operator+() const
	{
		return *this;
	}

	//(c) Mamontov, TEST(Integer, unaryOperatorOnesComplement)
	Integer Integer::operator~() const
	{
		Integer result(*this);
		return result.OnesComplement();
	}

	//(c) Mamontov, TEST(Integer, OnesComplement)
	Integer& Integer::OnesComplement()
	{
		OnesComplement_Base();
		_sign = !_sign;
		return *this;
	}

	//(c) Mamontov, TEST(Integer, Increment)
	Integer& Integer::operator++()
	{
		Integer e(1);
		return Add(*this,e);
	}

	//(c) Mamontov, TEST(Integer, Increment)
	Integer& Integer::operator++(int i)
	{
		++(*this);
		return *this;
	}

	//(c) Mamontov, TEST(Integer, Decrement)
	Integer& Integer::operator--()
	{
		Integer e(1);
		return Sub(*this,e);
	}

	//(c) Mamontov, TEST(Integer, Decrement)
	Integer& Integer::operator--(int i)
	{
		--(*this);
		return *this;
	}

	//(c) Mamontov, TEST(Integer, operatorEqual)
	Integer& Integer::operator= (const Integer& integer)
	{
		Assign_Base(integer);
		_sign = integer._sign;
		return *this;
	}
//**********************************************************************************************

//*****************************    Операции сравнения    ***************************************
	//(c) Mamontov, TEST(Integer, Compare)
	Integer Integer::Compare(const Integer& integer) const
	{
		return *this - integer;
	}

	//(c) Mamontov, TEST(Integer, Equal)
	bool operator==(const Integer& a, const Integer& b)
	{
		if(&a == &b || (a.isZero() && b.isZero()))
			return true;
		if(a._sign != b._sign)
			return false;
		return a.CmpImpl(b) == Equal;
	}

	//simple method
	bool operator!=(const Integer& a, const Integer& b)
	{
		return !(a == b);
	}

	//(c) Mamontov, TEST(Integer, Smaller)
	bool operator<(const Integer& a, const Integer& b)
	{
		if(a.isZero())
			return b.isPositive();
		if(b.isZero())
			return a.isNegative();
		if(a._sign != b._sign)
			return a._sign > b._sign;

		if(a.isNegative())
			return a.CmpImpl(b) == Bigger;
		return a.CmpImpl(b) == Smaller;
	}

	//simple method
	bool operator<=(const Integer& a, const Integer& b)
	{
		return !(b < a);
	}

	//simple method
	bool operator>(const Integer& a, const Integer& b)
	{
		return b < a;
	}

	//simple method
	bool operator>=(const Integer& a, const Integer& b)
	{
		return !(a < b);
	}
//**********************************************************************************************

//********************************    Логические операции    ***********************************
	//private method
	const Integer* Integer::Max(const Integer& a, const Integer &b, CompareIndicator ind)
	{
		const Integer* max = (ind == Bigger) ? &a : &b;
		if(this == max)
			max = new Integer(*this);
		return max;
	}

	//private method
	const Integer* Integer::Min(const Integer& a, const Integer &b, CompareIndicator ind)
	{
		const Integer* min = (ind == Bigger) ? &b : &a;
		if(this == min)
			min = new Integer(*this);
		return min;
	}

	//private method
	void Integer::Disposal(const Integer& a, const Integer &b)
	{
		if(this != &a && this != &b)
			delete this;
	}

	//simple method
	Integer operator^(const Integer& a, const Integer& b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.Xor(copy_a, copy_b);
	}

	//simple method
	Integer& Integer::operator^=(Integer& integer)
	{
		return this->Xor(*this, integer);
	}

	//(c) Mamontov, TEST(Integer, Xor)
	Integer& Integer::Xor(Integer& a, Integer& b)
	{
		if(a.isNegative() || b.isNegative())
			throw new Exception("Числа a и b не должны быть отрицательными");

		Xor_Base(a, b);
		return *this;
	}

	//simple method
	Integer operator|(const Integer& a, const Integer& b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.Or(copy_a, copy_b);
	}

	//simple method
	Integer& Integer::operator|=(Integer& integer)
	{
		return this->Or(*this, integer);
	}

	//(c) Mamontov, TEST(Integer, Or)
	Integer& Integer::Or(Integer& a, Integer& b)
	{
		if(a.isNegative() || b.isNegative())
			throw new Exception("Числа a и b не должны быть отрицательными");

		Or_Base(a, b);
		return *this;
	}

	//simple method
	Integer operator&(const Integer& a, const Integer& b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.And(copy_a, copy_b);
	}

	Integer& Integer::operator&=(Integer& integer)
	{
		return this->And(*this, integer);
	}

	//(c) Mamontov, TEST(Integer, And)
	Integer& Integer::And(Integer& a, Integer& b)
	{
		if(a.isNegative() || b.isNegative())
			throw new Exception("Числа a и b не должны быть отрицательными");

		And_Base(a, b);
		return *this;
	}

	//simple method
	Integer operator!(const Integer &integer)
	{
		Integer copy_integer(integer), result;
		return result.Not(copy_integer);
	}

	//(c) Mamontov, TEST(Integer, Not)
	Integer& Integer::Not(Integer &integer)
	{
		if(integer.isNegative())
			throw new Exception("Число integer не должно быть отрицательным");

		Not_Base(integer);
		return *this;
	}
//**********************************************************************************************

//***************************    Операции побитового сдвига    *********************************
	//simple method
	Integer Integer::operator<<(int numberBits) const
	{
		Integer result(*this);
		return result<<=numberBits;
	}

	//(c) Mamontov, TEST(Integer, SHL)
	Integer& Integer::operator<<=(int numberBits)
	{
		LeftShift_Base(numberBits);
		return *this;
	}

	//simple method
	Integer Integer::operator>>(int numberBits) const
	{
		Integer result(*this);
		return result>>=numberBits;
	}

	//(c) Mamontov, TEST(Integer, SHR)
	Integer& Integer::operator>>=(int numberBits)
	{
		RightShift_Base(numberBits);
		return *this;
	}
//**********************************************************************************************

//******************************    Операция сложения    ***************************************
	//private method
	void Integer::AddImpl(const Integer *a, const Integer *b)
	{
		setNumberDigits(a->_numberDigits + 1);
		std::memcpy(_digits, a->_digits, getDigitSizeInBytes()*a->_numberDigits);

		int addOverflow=0;
		uint j=0;

		for(j=0; j<b->_numberDigits; j++)
		{
			_digits[j] += (b->_digits[j] + addOverflow);
			addOverflow = (_digits[j] < a->_digits[j] || (addOverflow && _digits[j] == a->_digits[j]));
		}

		for(; j<_numberDigits-1; j++)
		{
			if(!addOverflow)
				break;
			_digits[j] += addOverflow;
			addOverflow=(addOverflow && !_digits[j]);
		}

		if(!addOverflow)
			_numberDigits--;
		else
			_digits[_numberDigits - 1] = addOverflow;
	}

	//simple method
	Integer operator+(const Integer &a, const Integer &b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}

	//simple method
	Integer& Integer::operator+=(Integer &integer)
	{
		return Add(*this, integer);
	}

	//(c) Mamontov, TEST(Integer, Add)
	Integer& Integer::Add(const Integer &a, const Integer &b)
	{
		if(a.isZero() || b.isZero())
		{
			*this = !a.isZero() ? a : b;
			return *this;
		}

		CompareIndicator compare = a.CmpImpl(b);
		if(a._sign != b._sign && compare == Equal)
			return setZero();

		if(a._sign == b._sign && compare == Equal)
		{
			*this = a;
			return *this <<= 1;
		}

		const Integer *max = Max(a, b, compare);
		const Integer *min = Min(a, b, compare);

		_sign = max->_sign;
		if(max->_sign == min->_sign)
			AddImpl(max, min);
		else
			SubImpl(max, min);

		//max->Disposal(a, b);
		//min->Disposal(a, b);

		return *this;
	}

	//simple method
	Integer& Integer::ModAdd(Integer &a, Integer &b, Integer &module)
	{
		Integer copy_a(a), copy_b(b);
		return Add(copy_a, copy_b) %= module;
	}
  	//simple method
	Integer& Integer::ModAddInFp(Integer &a, Integer &b, Integer &module)
	{
                if(!module.isPrime())
                        throw new Exception("p должно быть простым.");

		return ModAdd(a, b, module);

	}

//**********************************************************************************************

//******************************    Операция вычитания    **************************************
	//private method
	void Integer::SubImpl(const Integer *a, const Integer *b)
	{
		setNumberDigits(a->_numberDigits);
		std::memcpy(_digits, a->_digits, getDigitSizeInBytes()*a->_numberDigits);

		int subOverflow=0;
		uint j=0;

		for(j=0;j<b->_numberDigits ;j++)
		{
			_digits[j] -= (b->_digits[j] + subOverflow);
			subOverflow=(_digits[j] > a->_digits[j] || (subOverflow && _digits[j] == a->_digits[j]));
		}

		for(;j<a->_numberDigits;j++)
		{
			if(!subOverflow)
				break;
			_digits[j] -= subOverflow;
			subOverflow = (subOverflow && _digits[j]==-1);
		}

		RemoveElderNulls();
	}

	//simple method
	Integer operator-(const Integer &a, const Integer &b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.Sub(copy_a, copy_b);
	}

	//simple method
	Integer& Integer::operator-=(Integer &integer)
	{
		return Sub(*this, integer);
	}

	//(c) Mamontov, TEST(Integer, Sub)
	Integer& Integer::Sub(Integer& a, Integer& b)
	{
		if(a.isZero() || b.isZero())
		{
			*this = !a.isZero() ? a : -b;
			return *this;
		}

		CompareIndicator compare = a.CmpImpl(b);
		if(a._sign == b._sign && compare == Equal)
			return setZero();

		if(a._sign != b._sign && compare == Equal)
		{
			*this = a;
			return *this <<= 1;
		}

		const Integer *max = Max(a, b, compare);
		const Integer *min = Min(a, b, compare);

		_sign = (compare == Bigger) ? a._sign : !b._sign;
		if(max->_sign == min->_sign)
			SubImpl(max, min);
		else
			AddImpl(max, min);

		//max->Disposal(a, b);
		//min->Disposal(a, b);

		return *this;
	}

	//simple method
	Integer& Integer::ModSub(Integer& a, Integer& b, Integer& module)
	{
		Integer copy_a(a), copy_b(b);
		return Sub(copy_a, copy_b) %= module;
	}
        Integer& Integer::SubInFp(Integer& a, Integer& b, Integer& module)
  	{
                if(!module.isPrime())
		{
                        throw new Exception("p должно быть простым.");
                }

                Sub(a, b);
                return ModPositive(module);
	}

//**********************************************************************************************

//******************************    Операция умножения    **************************************
	//private method
	const Integer *Integer::Copy(const Integer &integer, Integer *integerNotEqual)
	{
		return (this == &integer || integerNotEqual == &integer) ? new Integer(integer) : &integer;
	}

	//private method
	void Integer::DisposalCopy(const Integer &integer, Integer *integerNotEqual)
	{
		if(this != &integer && this != integerNotEqual)
			delete const_cast<Integer*>(this);
	}

	//simple method
	Integer operator*(const Integer &a, const Integer &b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.Mul(copy_a, copy_b);
	}

	//simple method
	Integer& Integer::operator*=(Integer &integer)
	{
		return Mul(*this, integer);
	}

	//(c) Mamontov, TEST(Integer, Mul)
	Integer& Integer::Mul(const Integer &a, const Integer &b)
	{
		if(a.isZero() || b.isZero())
			return setZero();

		Integer *aa = const_cast<Integer*>(Copy(a));
		Integer *bb = const_cast<Integer*>(Copy(b));

		setNumberDigits(aa->_numberDigits + bb->_numberDigits);
		std::memset(_digits, 0, getDigitSizeInBytes()*aa->_numberDigits);
		_sign = aa->_sign^bb->_sign;

		for(uint j=0; j<bb->_numberDigits; j++)
		{
			if(!bb->_digits[j])
				_digits[aa->_numberDigits+j] = 0;
			else
			{
				uint mulOverflow=0;
				unsigned __int64 t=0;
				for(uint i=0; i<aa->_numberDigits; i++, mulOverflow=(uint)(t>>getDigitSizeInBits()))
				{
					t = (unsigned __int64)aa->_digits[i]*(unsigned __int64)bb->_digits[j] + (unsigned __int64)_digits[i+j] + (unsigned __int64)mulOverflow;
					_digits[i+j] = (uint)t;
				}
				_digits[j+aa->_numberDigits] = mulOverflow;
			}
		}

		RemoveElderNulls();
		aa->DisposalCopy(a);
		bb->DisposalCopy(b);

		return *this;
	}

	//simple method
	Integer& Integer::ModMul(Integer &a, Integer &b, Integer &module)
	{
		Integer copy_a(a), copy_b(b);
		return Mul(copy_a, copy_b) %= module;
	}
  Integer& Integer::MulInFp(Integer &a, Integer &b, Integer &module)
	{
                if(!module.isPrime())
		{
                        throw new Exception("p должно быть простым.");
                }

                return ModMul(a, b, module);
	}

//**********************************************************************************************

//******************************    Операция деления    ****************************************
	//private method
	void Integer::Div_by_SmallDivider(const Integer *a, const Integer *b, Integer *remainder)
	{
		uint rr,j;
		for(rr=0, j=a->_numberDigits-1; j<a->_numberDigits; j--)
		{
			_digits[j] = (uint)(((unsigned __int64)rr*0x100000000+(unsigned __int64)a->_digits[j])/(unsigned __int64)b->_digits[0]);
			rr = (uint)(((unsigned __int64)rr*0x100000000+(unsigned __int64)a->_digits[j])%(unsigned __int64)b->_digits[0]);
		}
		if(remainder != NULL)
		{
			if(rr)
				remainder->_digits[0] = rr;
			else
				remainder->_numberDigits = 0;
		}
	}

	//private method
	void Integer::DivImpl(const Integer *a, const Integer *b, Integer *remainder)
	{
		if(b->_numberDigits == 1)
			Div_by_SmallDivider(a, b, remainder);
		else
		{
			//Не объединять в одну строчку, т.к. компилятор C++ Builder-а, работает не правильно!
			double ee = (std::log((double)b->_digits[b->_numberDigits-1])/std::log(2.0));
			int e = getDigitSizeInBits() - 1 - (int)ee;

			uint j,i,flagOverflow,pr;
			uint vv1,vv2,uu1,uu2,uu3;
			unsigned __int64 qq,rr;

			uint *tempMassiv = new uint[a->_numberDigits+1];
			std::memcpy(tempMassiv, a->_digits, getDigitSizeInBytes()*a->_numberDigits);
			tempMassiv[a->_numberDigits]=0;

			if(!e)
			{
				vv1 = b->_digits[b->_numberDigits-1];
				vv2 = b->_digits[b->_numberDigits-2];
			}
			else
			{
				vv1 = ShiftedLeftWord_UpperByte(b->_numberDigits-1, b->_digits, e);
				vv2 = b->_numberDigits != 2 ? ShiftedLeftWord_UpperByte(b->_numberDigits-2, b->_digits, e) : ShiftedLeftByte_LowerByte(b->_numberDigits-2, b->_digits, e);
			}

			for(j=a->_numberDigits-b->_numberDigits; j!=-1; j--)
			{
				uu1 = ShiftedLeftWord_UpperByte(j+b->_numberDigits, tempMassiv, e);
				uu2 = ShiftedLeftWord_UpperByte(j+b->_numberDigits-1, tempMassiv, e);
				uu3 = b->_numberDigits!=2 ? ShiftedLeftWord_UpperByte(j+b->_numberDigits-2, tempMassiv, e) : ShiftedLeftByte_LowerByte(j+b->_numberDigits-2, tempMassiv, e);

				qq=(((unsigned __int64)uu1<<getDigitSizeInBits())+ uu2)/vv1;
				rr=(((unsigned __int64)uu1<<getDigitSizeInBits()) + uu2)%vv1;

                                if(qq == 0x100000001)
                                {
                                        qq--;
                                        rr += vv1;
                                }
                                if((qq>1)&&(qq==0x100000000 || (qq*vv2) > ((rr<<getDigitSizeInBits()) + uu3)))
				{
					qq--;
					if((rr+vv1)<0x100000000 && (qq*vv2) > (((rr+vv1)<<getDigitSizeInBits()) + uu3))
                                                qq--;
				}

				if(qq!=0)
				{
					flagOverflow=0;
					for(i=j; i<b->_numberDigits+j; i++)
					{
						pr = tempMassiv[i] - flagOverflow;
						flagOverflow = (pr > tempMassiv[i]);
						tempMassiv[i] = (uint)(pr - b->_digits[i-j]*qq);
						flagOverflow  += (uint)((((unsigned __int64)b->_digits[i-j]*qq)>>getDigitSizeInBits()) + (tempMassiv[i]>pr));
					}
					tempMassiv[b->_numberDigits+j] -= flagOverflow;

					if(tempMassiv[b->_numberDigits+j] > tempMassiv[b->_numberDigits+j]+flagOverflow)
					{
						tempMassiv[b->_numberDigits+j] += flagOverflow;
						qq--;
						flagOverflow = 0;

						for(i=j; i<b->_numberDigits+j; i++)
						{
							tempMassiv[i] += (b->_digits[i-j] + flagOverflow);
							flagOverflow = ( tempMassiv[i] < (b->_digits[i-j]+ flagOverflow) || (flagOverflow && b->_digits[i-j]==-1));
						}

						flagOverflow += (uint)(((unsigned __int64)b->_digits[b->_numberDigits-1]*qq)>>getDigitSizeInBits());
						tempMassiv[b->_numberDigits+j] -= flagOverflow;
					}
				}
				_digits[j] = (uint)qq;
			}

			if(remainder != NULL)
			{
				std::memcpy(remainder->_digits, tempMassiv, getDigitSizeInBytes()*b->_numberDigits);
				remainder->RemoveElderNulls();
			}
			delete[] tempMassiv;
		}
		RemoveElderNulls();
	}

	//sipmle method
	Integer operator/(const Integer &a, const Integer &b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.Div(copy_a, copy_b);
	}

	//simple method
	Integer &Integer::operator/=(Integer &integer)
	{
		return Div(*this, integer);
	}

	//(c) Morozov, TEST(Integer, Div)
	Integer &Integer::Div(Integer &a, Integer &b, Integer *remainder)
	{
		if(this == remainder)
			throw new Exception("Частное и остаток не могут быть одним числом");
		if(b.isZero())
			throw new Exception("Деление на ноль");

		CompareIndicator compare = a.CmpImpl(b);
		if(a.isZero() || compare == Smaller)
		{
			if(remainder != NULL)
				*remainder = a;
			return setZero();
		}
		if(compare == Equal)
		{
			if(remainder != NULL)
				remainder->setZero();
			return setOne(a._sign^b._sign);
		}

		Integer *aa = const_cast<Integer*>(Copy(a, remainder));
		Integer *bb = const_cast<Integer*>(Copy(b, remainder));

		_sign = aa->_sign^bb->_sign;
		setNumberDigits(aa->_numberDigits - bb->_numberDigits + 1);
		if(remainder != NULL)
		{
			remainder->_sign = aa->_sign;
			remainder->setNumberDigits(bb->_numberDigits);
		}
		DivImpl(aa, bb, remainder);
		aa->DisposalCopy(a, remainder);
		bb->DisposalCopy(b, remainder);

		return *this;
	}

	//simple method
	Integer& Integer::ModDiv(Integer &a, Integer &b, Integer &module, Integer *remainder)
	{ if(Euclid(a,module) == 1 && Euclid(b,module) == 1)
		  { Integer copy_a(a), copy_b(b), c;
		    Div(copy_a, copy_b, remainder) %= module;
                    c.Inverse(copy_b, module);
                    c = c*copy_a;
		    if(remainder != NULL)
			    *remainder %= module;
                    c.Mod(c, module);
                    *this = c;
		    return *this;
                }
                else
                        throw new Exception("А1 и А2 должны быть взаимно простыми с n");
	}

        Integer& Integer::DivInFp(Integer &a, Integer &b, Integer &module, Integer *remainder)
	{
                if(!module.isPrime())
                {
                        throw new Exception("р должно быть простым.");
                }

                Integer copy_a(a), copy_b(b), c;
		Div(copy_a, copy_b, remainder) %= module;
                c.Inverse(copy_b, module);
                c = c*copy_a;
		if(remainder != NULL)
		        *remainder %= module;
                c.Mod(c, module);
                *this = c;
                return *this;
	}

//**********************************************************************************************

//***************************    Операция приведения по модулю    ******************************
	//simple method
	Integer operator%(const Integer &a, const Integer &b)
	{
		Integer result, copy_a(a), copy_b(b);
		return result.Mod(copy_a, copy_b);
	}

	//simple method
	Integer& Integer::operator%=(Integer &integer)
	{
		return Mod(*this, integer);
	}

	//(c) Morozov, TEST(Integer, Mod)
	Integer& Integer::Mod(Integer &a, Integer &b)
	{
                if(b.isZero())
			throw new Exception("Деление на ноль");
                if(a.isZero())
			return setZero();


		CompareIndicator compare = a.CmpImpl(b);
		if(compare == Smaller)
		{
			*this = a;
			return *this;
		}
		if(compare == Equal)
			return setZero();

		Integer *aa = const_cast<Integer*>(Copy(a));
		Integer *bb = const_cast<Integer*>(Copy(b));
		Integer quotient(aa->_sign^bb->_sign, aa->_numberDigits-bb->_numberDigits+1, aa->_numberDigits-bb->_numberDigits+1);

		_sign = aa->_sign;
		setNumberDigits(bb->_numberDigits);
		quotient.DivImpl(aa, bb, this);

		aa->DisposalCopy(a);
		bb->DisposalCopy(b);
		return *this;
	}

	//simple method
	Integer& Integer::ModPositive(Integer& module)
	{
		if(module._sign)
			throw new Exception("Модуль - отрицательное число");

                if(isZero())
                        return *this;

		*this %= module;
		if(_sign)
			*this += module;
		return *this;
	}
//**********************************************************************************************

//***************************    Операция возведение в степень    ******************************
	//private method
	Integer& Integer::PowImpl(const Integer &a, const Integer &b,const Integer *module)
	{
		if(b.isNegative())
			throw new Exception("Число b - отрицательное, результат не определен");

		Integer *aa = const_cast<Integer*>(Copy(a));
		Integer *bb = const_cast<Integer*>(Copy(b));
		Integer *mm = (module == NULL) ? NULL : const_cast<Integer*>(Copy(*module));

		setOne();
		uint s = bb->getNumberBits();
		for(uint i=0;i<s;i++)
		{
			if(mm == NULL)
			{
				Mul(*this, *this);
				if(bb->getBit(s-1-i))
					Mul(*this, *aa);
			}
			else
			{
				ModMul(*this, *this, *mm);
				if(bb->getBit(s-1-i))
					ModMul(*this, *aa, *mm);
			}
		}

		aa->DisposalCopy(a);
		bb->DisposalCopy(b);
		if(mm != NULL)
			mm->DisposalCopy(*module);

		return *this;
	}

	//(c) Mamontov, TEST(Integer, Pow)
	Integer& Integer::Pow(const Integer &a, const Integer &b)
	{
		return PowImpl(a, b);
	}

	//(c) Mamontov, TEST(Integer, ModPow)
	Integer& Integer::ModPow(const Integer &a, const Integer &b, const Integer &module)
	{
		return PowImpl(a, b, &module);
	}
  Integer& Integer::PowInFp(Integer &a, Integer &b, Integer &module)
	{
                if(!module.isPrime())
                {
                        throw new Exception("р должно быть простым.");
                }

                return PowImpl(a, b, &module);
	}

//**********************************************************************************************

//*************************   Операция извлечения квадратного корня   **************************
	//simple method
	Integer& Integer::Sqrt()
	{
		return this->Sqrt(*this);
	}

	//(c) Mamontov, TEST(Integer, Sqrt)
	Integer& Integer::Sqrt(Integer& integer)
	{
		if(integer.isNegative())
			throw new Exception("Число integer не должно быть отрицательным");

		if(integer.isZero())
			return setZero();

		if(integer._numberDigits == 1)
		{
			*this = (int)std::sqrt((double)integer._digits[0]);
		}
		else
		{
			Integer approximate, end(2);
			Integer *i = const_cast<Integer*>(Copy(integer));

			*this = *i;
			*this >>= i->getNumberBits()/2;

			approximate.Div(*i, *this);
			end.Sub(approximate, *this);

			while(!end.isZero() && !end.isOne())
			{
				*this += approximate;
				*this >>= 1;
				approximate.Div(*i, *this);
				end.Sub(approximate, *this);
			}
			i->DisposalCopy(integer);
		}
		return *this;
	}
//-------------------------------------------------------------------------------------
 Integer& Integer::SquareRoot(Integer &integer) {
Integer X(integer);
Integer zero("0");
Integer one("1");
Integer two("2");
Integer power;
Integer mult;
Integer Y = (X + one)/two;
  if(X == zero) return *this = zero;
  if(X <= two) {
    return *this = one;
  } else {
      while(X != Y && (Y-X) != one) {
        X = Y;
        Y = (X + integer/ X)/2;
      }
  }
return *this = X;
}
//**********************************************************************************************

//********************************   Алгоритмы Евклида   ***************************************
	//(c) Mamontov, TEST(Integer, Euclid)
	Integer& Integer::Euclid(const Integer& a, Integer& b)
	{
		if(a.isZero() && b.isZero())
			throw new Exception("a и b не могут быть оба равны 0");

		if(a.isZero() || b.isZero())
		{
			*this = b.isZero() ? a : b;
			return setPositive();
		}
		CompareIndicator compare = a.CmpImpl(b);
		if(compare == Equal)
		{
			*this = a;
			return setPositive();
		}

		Integer min = compare == Bigger ? b : a;
		*this = compare == Bigger ? a : b;
		setPositive();
		min.setPositive();

		Integer temp, remainder;
		while(!min.isZero())
		{
			temp.Mod(*this, min);
			*this = min;
			min = temp;
		}

		return *this;
	}

	//(c) Mamontov, TEST(Integer, BinaryGCD)
	Integer& Integer::BinaryGCD(Integer& a, Integer& b)
	{
		if(a.isZero() && b.isZero())
			throw new Exception("a и b не могут быть оба равны 0 ");

		if(a.isZero() || b.isZero())
		{
			*this = b.isZero() ? a : b;
			return setPositive();
		}
		CompareIndicator compare = a.CmpImpl(b);
		if(compare == Equal)
		{
			*this = a;
			return setPositive();
		}

		uint countBitA = a.getFirstTrueBit();
		uint minCountBit = b.getFirstTrueBit();
		if(countBitA<minCountBit)
			minCountBit = countBitA;

		Integer min = (compare == Bigger)? b:a;
		*this = (compare == Bigger)? a:b;
		setPositive();
		min.setPositive();

		*this >>= minCountBit;
		min >>= minCountBit;

		Integer temp = (minCountBit==countBitA)? -min : *this;
		while(!temp.isZero())
		{
			temp >>= temp.getFirstTrueBit();
			if(temp.isPositive())
				*this = temp;
			else
				min = -temp;
			temp.Sub(*this, min);
		}

		return *this <<= minCountBit;
	}

	//private method
	Integer& Integer::simpleExEuclid(Integer &i, Integer &x, Integer &y)
	{
		x.setZero();
		y.setOne(i._sign);
		*this = i;
		return setPositive();
	}

	//private method
	Integer *Integer::Copy(Integer &i, Integer &iNotEqual_a, Integer &iNotEqual_b)
	{
		return (this == &i || &iNotEqual_a == &i || &iNotEqual_b == &i) ? new Integer(i):&i;
	}

	//private method
	void Integer::DisposalCopy(Integer &i, Integer &iNotEqual_a, Integer &iNotEqual_b)
	{
		if(this != &i && &iNotEqual_a != &i && &iNotEqual_b != &i)
			delete this;
	}

	//(c) Mamontov, TEST(Integer, ExEuclid)
	Integer& Integer::ExEuclid(Integer &a, Integer &b, Integer &x, Integer &y)
	{
		if(this == &x || this == &y || &x == &y)
			throw new Exception("НОД(a,b) и числа x и y такие, что ax+by=НОД(a,b) не могут быть одним числом");
		if(a.isZero() && b.isZero())
			throw new Exception("a и b не могут быть оба равны 0 сразу");

		if(a.isZero())
			return simpleExEuclid(b, x, y);
		if(b.isZero())
			return simpleExEuclid(a, y, x);
		CompareIndicator compare = a.CmpImpl(b);
		if(compare == Equal)
			return simpleExEuclid(a, y, x);
		if(compare == Smaller)
			return ExEuclid(b, a, y, x);

		Integer v1,v3,t1,t3;
		Integer *u = Copy(a, x, y);
		Integer *v = Copy(b, x, y);

		bool a_sign = u->_sign;
		bool b_sign = v->_sign;
		u->setPositive();
		v->setPositive();

		*this = *u;
		v3 = *v;
		x.setOne();

		Integer q,prom;
		while(1)
		{
			q.Div(*this, v3);
			prom.Mul(v1, q);
			t1.Sub(x, prom);
			prom.Mul(v3, q);
			t3.Sub(*this, prom);
			x = v1;
			*this = v3;
			if(t3.isZero())
				break;
			v1 = t1;
			v3 = t3;
		}

		prom.Mul(*u, x);
		q.Sub(*this, prom);
		y.Div(q, *v);

		u->DisposalCopy(a, x, y);
		v->DisposalCopy(b, x, y);

		if(a_sign)
		{
			if(this != &a && &x != &a && &y != &a)
				a._sign=true;
			x.Negate();
		}
		if(b_sign)
		{
			if(this != &b && &x != &b && &y != &b)
				b._sign=true;
			y.Negate();
		}
		return *this;
	}
//------------------------------------------------------------------------------
//--------НОК------------------------------------------------------------------
Integer& Integer::SCM(Integer &a, Integer &b)
{
  Integer mult,evc;
  mult = Mul(a,b);
  evc = Euclid(a,b);
  Integer *rez = new Integer(mult/evc);
  return *this = *rez;
}
//**********************************************************************************************

//***********************************   Генерация чисел   **************************************
	//simple method
	Integer& Integer::Generate(uint numberBits)
	{
		if(!numberBits)
			_numberDigits = 0;
		else
		{
			uint upperBit = numberBits % getDigitSizeInBits();
			_sign = false;
			setNumberDigits(numberBits / getDigitSizeInBits() + (upperBit != 0));
      		for(uint i=0; i<_numberDigits; i++) {
				int r = rand();
				_digits[i] = ((r % 2)<<(getDigitSizeInBits()-1));
				r = rand();
				_digits[i] += (r<<(getDigitSizeInBits()/2));
				r = rand();
				_digits[i] += ((r % 2)<<(getDigitSizeInBits()/2 - 1));
				r = rand();
				_digits[i] += r;
			}

			int shift = (upperBit!=0)? getDigitSizeInBits()-upperBit : 0;
			_digits[_numberDigits-1] &= 0xFFFFFFFF>>shift;
			_digits[_numberDigits-1] |= 0x80000000>>shift;
		}
		return *this;
	}

	//simple method
	Integer& Integer::Generate(const Integer& module)
	{
		Generate(module.getNumberBits());
		Integer m(module);
		*this %= m;
		return *this;
	}

	//(c) Mamontov, TEST(Integer, GenerateOdd)
	Integer& Integer::GenerateOdd(uint numberBits)
	{
		if(!numberBits)
			throw new Exception("Нет нечетных чисел длины 0 бит");
		Generate(numberBits);
		_digits[0] |= 1;
		return *this;
}

	//(c) Mamontov, TEST(Integer, GenerateOdd)
	Integer& Integer::GenerateOdd(const Integer& module)
	{
		if(module.isZero())
			throw new Exception("Введите n или p");
		Generate(module);
		_digits[0] |= 1;
		return *this;
	}

	//simple method
	Integer& Integer::GeneratePrime(uint numberBits)
	{
		do
		{
			GenerateOdd(numberBits);
		} while(!isPrime());
		return *this;
	}

	//simple method
	Integer& Integer::GeneratePrime(const Integer& module)
	{
		do
		{
			GenerateOdd(module);
      std::string s = this->strr();
		} while(!isPrime());
		return *this;
	}
// генерация достоверного простого числа
Integer& Integer::GeneratePrime(const Integer& module,std::vector<DecompositionMember> vector)
{
 if(vector.size() >= 1)
 {
    Integer a = GeneratePrime(module);
    while(!ModifiedTestLuka(vector,a))
    {
     a = GeneratePrime(module);
    }
   return *this = a;
 }
 else
			throw new Exception("Введите разложение n-1 (или p-1)");
}
//-------------------------------------------------------------------------------
Integer& Integer::WrappingGenerate(Integer& forwrap, const Integer &module)
{
    if(forwrap.getNumberBits() >= module.getNumberBits())
        throw new Exception("В размещаемой информации должно быть меньше битов чем в модуле");


    unsigned int forwrapNumberDidgits = forwrap.ToString().length();
    Integer ten(10);
    Integer stepen(forwrapNumberDidgits);
    Integer delitel(1);
    delitel = Pow(ten,stepen);
    Generate(module);
    std::string s(this->ToString());
    *this = *this/delitel;
    *this = *this*delitel;
    *this = *this + forwrap;
    return *this;

}
//------------------------------------------------------------------------------

//**********************************************************************************************

//**************************  Вычисление символов Якоби и Лежандра  ****************************
	//(c) Mamontov, TEST(Integer, LegendreSymbol)
	int Integer::LegendreSymbol(Integer& module)
	{
        if(module.MillerRabinTest())
        {	if(isZero())
		  	throw new Exception("Входной параметр не может быть 0");
		if(module.isZero())
		  	throw new Exception("Модуль не может быть 0");

		  Integer degree(module);
		  --degree;
		  degree >>= 1;

		  Integer result;
		  result.ModPow(*this, degree, module);

		  if(result.isZero())
			  return 0;
		  if(result.isOne())
			  return 1;
		  if(result.isNumber(1, true) || (result-module).isNumber(1, true))
			  return -1;
                  return -2;
        }
        else
		throw new Exception("A2 не является простым числом");
	}

	//(c) Mamontov, TEST(Integer, JacobySymbol)
	int Integer::JacobySymbol(Integer& n)
	{
		if(n.isZero())
			throw new Exception("n не может быть 0");

		if(isZero())
			return 0;
		if(isOne())
			return 1;

		Integer a(*this);
		if(isNegative())
            return (a+n).JacobySymbol(n);
        uint e = getFirstTrueBit();
		a >>= e;

		int s=1;
		if(e&1)
		{
			if((n._digits[0]&7)==3 || (n._digits[0]&7)==5)
				s=-1;
		}
		if((n._digits[0]&3)==3 && (!a.isZero() && (a._digits[0]&3)==3))
			s=-s;
		if(a.isOne())
			return s;
		Integer nn(n);
		nn %= a;
		return (s*nn.JacobySymbol(a));
	}
//**********************************************************************************************

//************************  Операции мультипликативной группы и поля  **************************
	//simple method
	bool Integer::InMulGroup(Integer& groupModule)
	{
		Integer result;
		return result.Euclid(*this, groupModule).isOne();
	}

 	bool Integer::InMulGroupInFp(Integer& groupModule)
	{
                if(!groupModule.isPrime())
                {
                        throw new Exception("р должно быть простым.");
                }

                // todo: заменить на проверку i mod p != 0
                return InMulGroup(groupModule);
	}
Integer& Integer::elementOrder(Integer &groupModule, Integer &num,std::vector<DecompositionMember> vector, const Integer &ord )
{
  if(!num.InMulGroup(groupModule))
    throw new Exception("элемент не принадлежит мультипликативной группе");
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    Integer *m  = new Integer(groupModule);
    Integer *a = new Integer(num);
    Integer t = ord;
    for(it = vector.begin(); it != vector.end();it++)
    {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.Pow(p,e);
      t = t/(ex);
      Integer a1;
      a1.ModPow(*a,t,*m);
      while(!a1.isOne())
      {
        a1.ModPow(a1,p,*m);
        t = t*p;
      }
    }
    AAL::Integer *rez =  new AAL::Integer(t);
    return *rez;
  }
  else
     throw new Exception("Введите разложение порядка группы.");
}
bool Integer::isGenerator(Integer &groupModule, Integer &num,std::vector<DecompositionMember> vector, Integer &ord)
{
  if(!num.InMulGroup(groupModule))
    throw new Exception("элемент не принадлежит мультипликативной группе");
    if(vector.size() >= 1)
    {   AAL::Integer m(ord);
       // AAL::Integer b(polynom.ToString(),Bin);
      Integer t = elementOrder(groupModule, num,vector,ord);
       if(t == m)
        return true;
    }
  else
   throw new Exception("Введите разложение порядка группы.");
return false;
}
	//simple method
	Integer& Integer::Inverse(Integer& module)
	{
		return Inverse(*this, module);
	}

	//(c) Mamontov, TEST(Integer, Inverse)
	Integer& Integer::Inverse(Integer &integer, Integer &module)
	{
    Integer *integ = new Integer(integer);
    Integer mod =  module;
    if(Euclid(*integ,mod) == 1)
    { integer = *integ;
    if(!integer.InMulGroup(module))
			  throw new Exception("Число не принадлежит мультипликативной группе");

      Integer *m = const_cast<Integer*>(Copy(module, &integer));

		  Integer temp,temp2,i(integer);
      i.ModPositive(module);
		  temp.ExEuclid(i, *m, *this, temp2);
		  if(isNegative())
			  *this += *m;

		  m->DisposalCopy(module, &integer);
		  return *this;
   }
    else
   throw new Exception("A1 и n должны быть взаимно просты.");
	}

 	Integer& Integer::InverseInFp(Integer &integer, Integer &module)
	{
                if(!module.isPrime())
                {
                        throw new Exception("p должно быть простым.");
                }

                return Inverse(integer, module);

	}
	//simple method
	Integer& Integer::ModSqrt(Integer& module)
	{
    if(module.isPrime())
		  {return ModSqrt(*this, module);}
    else
      throw new Exception("p должно быть простым.");
	}

	//(c) Morozov, TEST(Integer, ModSqrt)
	Integer& Integer::ModSqrt(Integer &integer, Integer &module)
	{
		if(!module.isPrime())
			throw new Exception("Модуль должен быть простым");
		if(integer.LegendreSymbol(module)!=1)
			throw new Exception("Число не является квадратичным вычетом");
		if(integer.isZero())
			return *this = integer;

		Integer prom(module);
		--prom;
		uint alpha = prom.getFirstTrueBit();

		Integer a(integer), *p = const_cast<Integer*>(Copy(module, &integer));

		if(alpha < 2)
		{
			++prom;
			++prom;
			prom >>= 2;
			ModPow(a, prom, *p);
		}
		else
		{
			Integer n(2);
			while(n.LegendreSymbol(*p) != -1) {
				n.Generate(*p);
				while(n.isZero()) n.Generate(*p); 
			}

			Integer s(prom);
			s >>= alpha;

			Integer b;
			b.ModPow(n, s, *p);

			s++;
			s >>= 1;

			ModPow(a, s, *p);

			Integer degree(1);
			degree <<= alpha-2;

			Integer ia(a);
			ia.Inverse(*p);

			uint i;
			Integer degreeJ(0);
                        Integer one(1);
			for(i=0; i<=alpha-2; i++)
			{
				prom.ModMul(*this, ia, *p);
				n.ModMul(prom, *this, *p);
				s.ModPow(n, degree, *p);
				if(!s.isOne())
        degreeJ.Add(degreeJ, Integer(one << i));// Integer(one << i), а не one << i, чтобы внутрь метода не пердавался временный объект который может быть удалён
				degree >>= 1;
        if(!degreeJ.isZero())
				{
					i++;
					break;
				}
			}
			for(; i<=alpha-2; i++)
			{
        prom.ModPow(b, degreeJ, *p);
				n.ModMul(prom, *this, *p);
				s.ModMul(n, ia, *p);
				prom.ModMul(n, s, *p);
				n.ModPow(prom, degree, *p);
				if(!n.isOne())
          degreeJ.Add(degreeJ, Integer(one << i)); // Integer(one << i), а не one << i, чтобы внутрь метода не пердавался временный объект который может быть удалён
				if(i!=alpha-2)
					degree >>= 1;
			}
                        if(!degreeJ.isZero())
			{
				prom.ModPow(b, degreeJ, *p);
				ModMul(prom, *this, *p);
			}
		}

		p->DisposalCopy(module, &integer);
		return *this;
	}


//**********************************************************************************************
};
