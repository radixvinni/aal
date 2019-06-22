/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:
        AAL::Exception class used for handling exceptions.
        AAL::BasicType class implements an basic dinamic array structure. It is the base
        class for Polynom and Integer.

*/

#ifndef __BASICTYPE_H__
#define __BASICTYPE_H__

#include <memory>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>

/*
    ISO C99 supports data types for integers that are at least 64 bits wide, and as an extension
    GCC supports them in C90 mode and in C++. Simply write long long int for a signed integer, or
    unsigned long long int for an unsigned integer. To make an integer constant of type long long int,
    add the suffix `LL' to the integer. To make an integer constant of type unsigned long long int,
    add the suffix `ULL' to the integer.

    Мне нравится фраза "at least 64 bits wide", на linux x86_64 это будет работать или там будет long??
    Я пробовал использовать int64_t, он гарантировано 64 бита, но он объявляется через typedef, поэтому если
    "unsigned __int64" написано, то это не будет работать
*/
#if defined(__GNUC__) || defined (__APPLE_CC__)
#define __int64 long long
#endif

/*
		Это мой набросок класса исключений
*/
namespace AAL
{
	class Exception:public std::exception{
	public:
		Exception(const char* str):error_message(str){}
		Exception(std::string str):error_message(str){}
		virtual ~Exception()throw(){}
		virtual const char* what() const throw(){return error_message.c_str();}
	private:
		std::string error_message;
	};
}

namespace AAL
{
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;

	enum CompareIndicator { Smaller=-1, Equal=0, Bigger=1 };

	/*
		Данный класс может использоваться с размером 1<=sizof(Type)<=4
		это связанно с реализацией битовых сдвигов

		В силу ограничений Visual C++ и C++ Builder, реализация должна
		находиться в классе, что является весьма не понятным явлением.
	*/

	template <class Type>
	class BasicType
    {
	public://это очень плохо!!! это ужасно!!! но по другому никак.
		uint  _numberDigits;
		uint  _maximumDigits;
		Type* _digits;

	//***********************************  Конструкторы  *******************************************
	protected:

		//protected метод
		void SetData(uint numberDigits, uint maximumDigits, bool isSetDigits=false)
		{
			if(numberDigits > maximumDigits)
				throw new Exception("Аргументы numberDigits и maximumDigits не входят в интервал допустимых значений: numberDigits > maximumDigits");

			_numberDigits = numberDigits;
			_maximumDigits = maximumDigits;
			_digits = isSetDigits ? new Type[_maximumDigits] : NULL;
		}

	public:

		//(c) Mamontov, TEST(BasicType, EmptyConstructor)
		BasicType()
		{
			SetData(0, 0);
		}

		//(c) Mamontov, TEST(BasicType, CopyConstructor)
		BasicType(const BasicType& basicType)
		{
			bool isCopyDigits = basicType._maximumDigits != 0;
			SetData(basicType._numberDigits, basicType._maximumDigits, isCopyDigits);
			if(isCopyDigits)
				std::memcpy(_digits, basicType._digits, getDigitSizeInBytes()*basicType._numberDigits);
		}

		//(c) Mamontov, TEST(BasicType, NumberConstructor)
		BasicType(const Type number)
		{
			bool isNotZero = number != 0;
			SetData(isNotZero , isNotZero, isNotZero);
			if(isNotZero)
				_digits[0] = number;
		}

		//simple method
		~BasicType()
		{
			delete[] _digits;
		}
	//**********************************************************************************************

	//********************************  Методы для работы с памятью  *******************************
	protected:

		//protected метод
		void RemoveElderNulls()
		{
			while(_numberDigits && !_digits[_numberDigits-1])
				_numberDigits--;
		}

		//protected метод
		void setNumberDigits(uint numberDigits)
		{
			_numberDigits = numberDigits;
			if(_maximumDigits < _numberDigits)
			{
				delete[] _digits;
 //               int x = sizeof( Type );
				_maximumDigits = _numberDigits;
				_digits = new Type[_maximumDigits];
			}
		}

		//protected метод
		void setNumberDigitsWithSetElderNulls(uint numberDigits)
		{
			if(numberDigits == _numberDigits)
				return;

			if(_maximumDigits < numberDigits)
			{
				_maximumDigits = numberDigits;
				Type *digits = new Type[_maximumDigits];
				std::memcpy(digits, _digits, getDigitSizeInBytes()*_numberDigits);
				delete[] _digits;
				_digits = digits;
			}

			if(numberDigits > _numberDigits)
				std::memset(_digits + _numberDigits, 0, getDigitSizeInBytes()*(numberDigits - _numberDigits));
			_numberDigits = numberDigits;
		}

	public:

		//(c) Mamontov, TEST(BasicType, Relocation)
		void Relocation(uint maximumDigits)
		{
			if(maximumDigits != _maximumDigits)
			{
				if(_numberDigits > maximumDigits)
					throw new Exception("Аргумент maximumDigits не входит в интервал допустимых значений: _numberDigits > maximumDigits");

				_maximumDigits = maximumDigits;
				Type* digits = NULL;
				if(_maximumDigits)
				{
					digits = new Type[_maximumDigits];
					std::memcpy(digits, _digits, getDigitSizeInBytes()*_numberDigits);
				}
				delete[] _digits;
				_digits = digits;
			}
		}

		//(c) Mamontov, TEST(BasicType, PressMemory)
		void PressMemory()
		{
			Relocation(_numberDigits);
		}
	//**********************************************************************************************

	//***************************************  Методы акцепторы   **********************************
		int getDigitSizeInBytes() const
		{
			return sizeof(Type);
		}

		int getDigitSizeInBits() const
		{
			return sizeof(Type)*8;
		}

		protected:
	  //protected метод
		uint getElderBit() const
		{
			uint i = getDigitSizeInBits() - 1;
			while(i && !((_digits[_numberDigits - 1]>>i)&1))
				i--;
			return i+1;
		}

		//protected метод
		void setOne_Base()
		{
			setNumberDigits(1);
			_digits[0] = 1;
		}

		//protected метод
		void setNumber_Base(Type number)
		{
			setNumberDigits(1);
			_digits[0] = number;
		}

		//protected метод
		void setZero_Base()
		{
			_numberDigits = 0;
		}

		//protected метод
		bool isNumber_Base(Type number) const
		{
			return _numberDigits == 1 && _digits[0] == number;
		}

	public:

		//(c) Mamontov, TEST(BasicType, getNumberBits)
		uint getNumberBits() const
		{
			if(!_numberDigits)
				return 0;
			return (_numberDigits-1)*getDigitSizeInBits() + getElderBit();
		}

		//(c) Mamontov, TEST(BasicType, getNumberBytes)
		uint getNumberBytes() const
		{
			if(!_numberDigits)
				return 0;
			int elderBit = getElderBit();
			return (_numberDigits-1)*getDigitSizeInBytes() + elderBit/8 + (elderBit%8 != 0);
		}

		//simple method
		uint getNumberDigits() const
		{
			return _numberDigits;
		}

		//simple method
		uint getMaximumDigits() const
		{
			return _maximumDigits;
		}

		//(c) Mamontov, TEST(BasicType, getFirstTrueBit)
		uint getFirstTrueBit() const
		{
			if(!_numberDigits)
				return -1;

			uint i = 0;
			while(!_digits[i] && i<_numberDigits)
				i++;
			uint j = 0;
			uint countBit = getDigitSizeInBits() - 1;
			while(j!=countBit && !((_digits[i]>>j)&1))
				j++;

			return i*(countBit+1) + j;
		}

		//(c) Mamontov, TEST(BasicType, getBit)
		bool getBit(uint position) const
		{
			uint numberDigit = position/getDigitSizeInBits();
			if(numberDigit >= _numberDigits)
				return false;
			int bitPosition = position%getDigitSizeInBits();
			return (_digits[numberDigit]>>bitPosition)&1;
		}

		//(c) Mamontov, TEST(BasicType, setBit)
		void setBit(uint position, bool value=true)
		{
			uint numberDigit = position/getDigitSizeInBits();
			if(numberDigit >= _numberDigits)
				setNumberDigitsWithSetElderNulls(numberDigit + 1);

			int bitPosition = position%getDigitSizeInBits();
			Type mask = 1<<bitPosition;
			if(value)
				_digits[numberDigit] |= mask;
			else
				_digits[numberDigit] &= ~mask;

			RemoveElderNulls();
		}

		//(c) Mamontov, TEST(BasicType, getDigit)
		Type getDigit(uint position) const
		{
			if(position >= _numberDigits)
				return 0;
			return _digits[position];
		}

		//(c) Mamontov, TEST(BasicType, setDigit)
		void setDigit(uint position, Type value)
		{
			if(position >= _numberDigits)
				setNumberDigitsWithSetElderNulls(position + 1);

			_digits[position] = value;
			RemoveElderNulls();
		}

		//simple method
		bool isZero() const
		{
			return !_numberDigits;
		}

		//simple method
		virtual bool isOne() const
		{
			return _numberDigits == 1 && _digits[0] == 1;
		}
	//**********************************************************************************************

	//************************************  Унарные операции   *************************************
	protected:

		//protected метод
		void OnesComplement_Base()
		{
			for(uint i=0; i<_numberDigits; i++)
				_digits[i] = ~_digits[i];
			RemoveElderNulls();
		}

		//protected метод
		void Assign_Base(const BasicType& basicType)
		{
			if(this->CmpImpl(basicType) == Equal)
				return;
			if(basicType.isZero())
			{
				setZero_Base();
				return;
			}

			setNumberDigits(basicType._numberDigits);
			std::memcpy(_digits, basicType._digits, getDigitSizeInBytes()*_numberDigits);
		}
	//**********************************************************************************************

	//*****************************    Операции сравнения    ***************************************
	protected:

		//protected метод
		CompareIndicator CmpImpl(const BasicType& basicType) const
		{
			if(this == &basicType)
				return Equal;
			if(_numberDigits > basicType._numberDigits)
				return Bigger;
			if(_numberDigits < basicType._numberDigits )
				return Smaller;
			if(!_numberDigits)
				return Equal;

			uint n = _numberDigits;
			while(n && _digits[n-1] == basicType._digits[n-1])
				n--;

			if(!n)
				return Equal;
			if(_digits[n-1] > basicType._digits[n-1])
				return Bigger;
			return Smaller;
		}
	//**********************************************************************************************

	//********************************    Логические операции    ***********************************
	protected:

		//protected метод
		BasicType* Max(BasicType& a, BasicType& b, CompareIndicator ind)
		{
			BasicType* max = (ind == Bigger) ? &a : &b;
			if(this == max)
				max = new BasicType(*this);
			return max;
		}

		//protected метод
		BasicType* Min(BasicType& a, BasicType& b, CompareIndicator ind)
		{
			BasicType* min = (ind == Bigger) ? &b : &a;
			if(this == min)
				min = new BasicType(*this);
			return min;
		}

		//protected метод
		void Disposal(BasicType& a, BasicType& b)
		{
			if(this != &a && this != &b)
				delete this;
		}

		//protected метод
		void Xor_Base(BasicType& a, BasicType& b)
		{
			CompareIndicator compare = a.CmpImpl(b);
			if(compare == Equal)
			{
				setZero_Base();
				return;
			}

			BasicType* max = Max(a, b, compare);
			BasicType* min = Min(a, b, compare);
			setNumberDigits(max->_numberDigits);

			uint i;
			for(i=0; i < min->_numberDigits; i++)
				_digits[i] = min->_digits[i]^max->_digits[i];
			for(; i < _numberDigits; i++)
				_digits[i] = max->_digits[i]^0;

			RemoveElderNulls();
			max->Disposal(a, b);
			min->Disposal(a, b);
		}

		//protected метод
		void Or_Base(BasicType& a, BasicType& b)
		{
			CompareIndicator compare = a.CmpImpl(b);
			if(compare == Equal)
			{
				this->Assign_Base(a);
				return;
			}
			else if(a.isZero() || b.isZero())
			{
				if(a.isZero())
					this->Assign_Base(b);
				else
					this->Assign_Base(a);
				return;
			}

			BasicType* max = Max(a, b, compare);
			BasicType* min = Min(a, b, compare);
			setNumberDigits(max->_numberDigits);
			std::memcpy(_digits, max->_digits, getDigitSizeInBytes()*_numberDigits);

			for(uint i=0; i < min->_numberDigits; i++)
				_digits[i] |= min->_digits[i];

			RemoveElderNulls();
			max->Disposal(a, b);
			min->Disposal(a, b);
		}

		//protected метод
		void And_Base(BasicType& a, BasicType& b)
		{
			if(a.isZero() || b.isZero())
			{
				setZero_Base();
				return;
			}
			CompareIndicator compare = a.CmpImpl(b);
			if(compare == Equal)
			{
				this->Assign_Base(a);
				return;
			}

			BasicType* max = Max(a, b, compare);
			BasicType* min = Min(a, b, compare);
			setNumberDigits(min->_numberDigits);

			for(uint i=0; i<_numberDigits; i++)
				_digits[i] = min->_digits[i] & max->_digits[i];

			RemoveElderNulls();
			max->Disposal(a, b);
			min->Disposal(a, b);
		}

		//protected метод
		void Not_Base(BasicType& basicType)
		{
			if(basicType.isOne())
			{
				setZero_Base();
				return;
			}
			if(basicType.isZero())
			{
				setOne_Base();
				return;
			}

			int elderBit = basicType.getElderBit();
			setNumberDigits(basicType._numberDigits);
			for(uint i=0; i<_numberDigits; i++)
				_digits[i] = ~basicType._digits[i];

			if(getDigitSizeInBits() - elderBit)
			{
				_digits[_numberDigits - 1] <<= getDigitSizeInBits() - elderBit;
				_digits[_numberDigits - 1] >>= getDigitSizeInBits() - elderBit;
			}
			RemoveElderNulls();
		}
	//**********************************************************************************************

	//***************************    Операции побитового сдвига    *********************************
	protected:

		//protected метод
		Type ShiftedLeftWord_UpperByte(uint numberDigit, Type *digits, int countShift)
		{
			return (Type)(((((unsigned __int64)digits[numberDigit]<<getDigitSizeInBits())+digits[numberDigit-1])<<countShift)>>getDigitSizeInBits());
		}

		//protected метод
		Type ShiftedRightWord_LowerByte(uint numberDigit, Type *digits, int countShift)
		{
			return (Type)((((unsigned __int64)digits[numberDigit]<<getDigitSizeInBits())+digits[numberDigit - 1])>>countShift);
		}

		//protected метод
		Type ShiftedLeftByte_LowerByte(uint numberDigit, Type *digits, int countShift)
		{
			return (Type)(digits[numberDigit]<<countShift);
		}

		//protected метод
		Type ShiftedRightByte_LowerByte(uint numberDigit, Type *digits, int countShift)
		{
			return (Type)(digits[numberDigit]>>countShift);
		}

		//protected метод
		Type ShiftedLeftByte_UpperByte(uint numberDigit, Type *digits, int countShift)
		{
			return (Type)((((unsigned __int64)digits[numberDigit])<<countShift)>>getDigitSizeInBits());
		}

		//protected метод
		void LeftShift_Base(int numberBits)
		{
			if(isZero() || !numberBits)
				return;
			if(numberBits < 0)
			{
				RightShift_Base(-numberBits);
				return;
			}

			int rightZeroDigits = numberBits / getDigitSizeInBits();
			int countShift = numberBits % getDigitSizeInBits();

			BasicType basicType(*this);
			setNumberDigits(rightZeroDigits + _numberDigits + 1);
			std::memset(_digits, 0, getDigitSizeInBytes()*rightZeroDigits);

			if(countShift)
			{
				_digits[rightZeroDigits] = ShiftedLeftByte_LowerByte(0, basicType._digits, countShift);
				for(uint i=rightZeroDigits+1; i<_numberDigits-1; i++)
					_digits[i] = ShiftedLeftWord_UpperByte(i-rightZeroDigits,  basicType._digits,  countShift);
				_digits[_numberDigits-1] = ShiftedLeftByte_UpperByte(basicType._numberDigits - 1,  basicType._digits, countShift);

				if(!_digits[_numberDigits-1])
					_numberDigits--;
			}
			else
			{
				std::memcpy(&_digits[rightZeroDigits], basicType._digits, getDigitSizeInBytes()*basicType._numberDigits);
				_numberDigits--;
			}
		}

		//protected метод
		void RightShift_Base(int numberBits)
		{
			if(isZero() || !numberBits)
				return;
			if(numberBits < 0)
			{
				LeftShift_Base(-numberBits);
				return;
			}

			int leftZeroDigits = numberBits / getDigitSizeInBits();
			if((uint)leftZeroDigits >= _numberDigits)
			{
				setZero_Base();
				return;
			}
			int countShift = numberBits % getDigitSizeInBits();

			BasicType basicType(*this);
			setNumberDigits(_numberDigits - leftZeroDigits);

			if(countShift)
			{
				for(uint i=0; i<_numberDigits-1; i++)
					_digits[i] = ShiftedRightWord_LowerByte(i+1+leftZeroDigits, basicType._digits, countShift);
				_digits[_numberDigits-1] = ShiftedRightByte_LowerByte(basicType._numberDigits - 1, basicType._digits, countShift);

				if(!_digits[_numberDigits - 1])
					_numberDigits--;
			}
			else
				std::memcpy(_digits, &basicType._digits[leftZeroDigits], getDigitSizeInBytes()*_numberDigits);
		}
		//**********************************************************************************************
    };
};
#endif
