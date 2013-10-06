/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "NumberVector.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <stdlib.h>
#include <string>

namespace AAL
{
//***********************************  Конструкторы  *******************************************
	//(c) Mamontov, TEST(NumberVector, EmptyConstructor)
	NumberVector::NumberVector()
	{}

	//(c) Mamontov, TEST(NumberVector, CopyConstructor)
	NumberVector::NumberVector(const NumberVector &numberVector)
	{
		_integers = numberVector._integers;
	}

	//(c) Mamontov, TEST(NumberVector, StringConstructor)
	NumberVector::NumberVector(const std::string dataString, NumericSystem system)
	{
		Parse(dataString, system);
	}
//**********************************************************************************************

//*************************  Преобразование и считывание из сторк ******************************
	NumberVector& NumberVector::Parse(const std::string dataString, NumericSystem system)
	{
		_integers.clear();
		if(!dataString.empty())
		{
			std::string integerData;
			std::string::size_type next, prev=0;
			for(next=dataString.find(" ", prev); next!=prev; next=dataString.find(" ", prev))
			{
				integerData = dataString.substr(prev, next-prev);
				Integer* integer = new Integer(integerData, system);
				_integers.push_back(integer);
				if(next==std::string::npos)
					break;
				prev = next+1;
			}
		}
		return *this;
	}

	std::string NumberVector::ToString(NumericSystem system) const
	{
		std::string resultString = "";
		for (std::vector<Integer *>::const_iterator it = _integers.begin(); it != _integers.end(); ++it)
		{
			if(resultString.empty())
				resultString = (*it)->ToString(system);
			else
				resultString += " " + (*it)->ToString(system);
		}
		return resultString;
	}
//**********************************************************************************************

//************************************  Унарные операции   *************************************
	NumberVector& NumberVector::operator= (const NumberVector& numberVector)
	{
		if(this == &numberVector)
			return *this;

		_integers = numberVector._integers;
		return *this;
	}
//**********************************************************************************************

//*****************************    Операции сравнения    ***************************************
	NumberVector NumberVector::Compare(const NumberVector& numberVector) const
	{
		return *this;// - numberVector;
	}

	bool operator==(const NumberVector& a, const NumberVector& b)
	{
		if(&a == &b || (a.isZero() && b.isZero()))
			return true;
		if(a._integers.size()!=b._integers.size())
			return false;

		std::vector<Integer *>::const_iterator it_a = a._integers.begin();
		std::vector<Integer *>::const_iterator it_b = b._integers.begin();
		for (; it_a != a._integers.end();)
		{
			if(*(*it_a) != *(*it_b))
				return false;

			++it_a;
			++it_b;
		}
		return true;
	}

	bool operator!=(const NumberVector& a, const NumberVector& b)
	{
		return !(a == b);
	}
//**********************************************************************************************

//***************************************  Методы акцепторы   **********************************
	//simple method
	NumberVector& NumberVector::setZero()
	{
		_integers.clear();
		return *this;
	}

	//simple method
	bool NumberVector::isZero() const
	{
		return _integers.size() == 0;
	}

	uint NumberVector::getNumberBits()
	{
		uint numberBits=0;
		for(std::vector<Integer *>::iterator it = _integers.begin(); it != _integers.end(); ++it)
			numberBits += (*it)->getNumberBits();
		return numberBits;
	}

	uint NumberVector::getNumberBytes() const
	{
		uint numberBytes=0;
		for(std::vector<Integer *>::const_iterator it = _integers.begin(); it != _integers.end(); ++it)
			numberBytes += (*it)->getNumberBytes();
		return numberBytes;
	}

	std::vector<Integer *>::size_type NumberVector::getNumberDigits() const
	{
		return _integers.size();
	}

	Integer NumberVector::getNumber(std::vector<Integer *>::size_type position) const
	{
		if(position < _integers.size())
			return *_integers.at(position);
		else
		{
			Integer res;
			return res;
		}
	}

	void NumberVector::setNumber(std::vector<Integer *>::size_type position, Integer &integer)
	{
		if(position < _integers.size())
			*_integers.at(position) = integer;
	}
//**********************************************************************************************

//********************************    Логические операции    ***********************************
	/*friend NumberVector operator^(const NumberVector &a, const NumberVector &b)
	{
	}

	NumberVector& NumberVector::operator^=(NumberVector &numberVector)
	{
	}

	NumberVector& NumberVector::Xor(NumberVector &a, NumberVector &b)
	{
	}

	friend NumberVector operator|(const NumberVector &a, const NumberVector &b)
	{
	}

	NumberVector& NumberVector::operator|=(NumberVector &numberVector)
	{
	}

	NumberVector& NumberVector::Or(NumberVector &a, NumberVector &b)
	{
	}

	friend NumberVector operator&(const NumberVector &a, const NumberVector &b)
	{
	}

	NumberVector& NumberVector::operator&=(NumberVector &numberVector)
	{
	}

	NumberVector& NumberVector::And(NumberVector &a, NumberVector &b)
	{
	}

	friend NumberVector operator!(const NumberVector &numberVector)
	{
	}

	NumberVector& NumberVector::Not(NumberVector &numberVector)
	{
	}*/
//**********************************************************************************************

//******************************    Операция сложения    ***************************************
	NumberVector operator+(const NumberVector &a, const NumberVector &b)
	{
		NumberVector result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}

	NumberVector& NumberVector::operator+=(NumberVector &numberVector)
	{
		return Add(*this, numberVector);
	}

	NumberVector& NumberVector::Add(NumberVector &a, NumberVector &b)
	{
		if(a.isZero() || b.isZero())
		{
			*this = !a.isZero() ? a : b;
			return *this;
		}

		if(a.getNumberDigits() >= b.getNumberDigits())
		{
			_integers = a._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_b;
			for (it_b = b._integers.begin(); it_b != b._integers.end(); ++it_b)
			{
				(*it)->Add(*(*it), *(*it_b));
				++it;
			}
		}
		if(b.getNumberDigits() > a.getNumberDigits())
		{
			_integers = b._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_a;
			for (it_a = a._integers.begin(); it_a != a._integers.end(); ++it_a)
			{
				(*it)->Add(*(*it), *(*it_a));
				++it;
			}
		}

		return *this;
	}

	NumberVector& NumberVector::ModAdd(NumberVector &a, NumberVector &b, Integer &module)
	{
		if(a.isZero() || b.isZero())
		{
			*this = !a.isZero() ? a : b;
			return *this;
		}

		if(a.getNumberDigits() >= b.getNumberDigits())
		{
			_integers = a._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_b;
			for (it_b = b._integers.begin(); it_b != b._integers.end(); ++it_b)
			{
				(*it)->ModAdd(*(*it), *(*it_b), module);
				++it;
			}
		}
		if(b.getNumberDigits() > a.getNumberDigits())
		{
			_integers = b._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_a;
			for (it_a = a._integers.begin(); it_a != a._integers.end(); ++it_a)
			{
				(*it)->ModAdd(*(*it), *(*it_a), module);
				++it;
			}
		}

		return *this;
	}
//**********************************************************************************************

//******************************    Операция вычитания    **************************************
	NumberVector operator-(const NumberVector &a, const NumberVector &b)
	{
		NumberVector result, copy_a(a), copy_b(b);
		return result.Sub(copy_a, copy_b);
	}

	NumberVector& NumberVector::operator-=(NumberVector &numberVector)
	{
			return Sub(*this, numberVector);
	}

	NumberVector& NumberVector::Sub(NumberVector &a, NumberVector &b)
	{
		if(a.isZero() || b.isZero())
		{
			*this = !a.isZero() ? a : b;
			return *this;
		}

		if(a.getNumberDigits() >= b.getNumberDigits())
		{
			_integers = a._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_b;
			for (it_b = b._integers.begin(); it_b != b._integers.end(); ++it_b)
			{
				(*it)->Sub(*(*it), *(*it_b));
				++it;
			}
		}
		if(b.getNumberDigits() > a.getNumberDigits())
		{
			_integers = b._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_a;
			for (it_a = a._integers.begin(); it_a != a._integers.end(); ++it_a)
			{
				(*it)->Sub(*(*it), *(*it_a));
				++it;
			}
		}

		return *this;
	}

	NumberVector& NumberVector::ModSub(NumberVector &a, NumberVector &b, Integer &module)
	{
		if(a.isZero() || b.isZero())
		{
			*this = !a.isZero() ? a : b;
			return *this;
		}

		if(a.getNumberDigits() >= b.getNumberDigits())
		{
			_integers = a._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_b;
			for (it_b = b._integers.begin(); it_b != b._integers.end(); ++it_b)
			{
				(*it)->ModSub(*(*it), *(*it_b), module);
				++it;
			}
		}
		if(b.getNumberDigits() > a.getNumberDigits())
		{
			_integers = b._integers;
			std::vector<Integer *>::iterator it = _integers.begin();
			std::vector<Integer *>::iterator it_a;
			for (it_a = a._integers.begin(); it_a != a._integers.end(); ++it_a)
			{
				(*it)->ModSub(*(*it), *(*it_a), module);
				++it;
			}
		}

		return *this;
	}
//**********************************************************************************************
};