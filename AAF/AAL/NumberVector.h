/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __NUMBERVECTOR_H__
#define __NUMBERVECTOR_H__

#include "Integer.h"
#include <vector>

namespace AAL
{
	class Converter;

	class NumberVector
    {
	private:
		std::vector<Integer *> _integers;
		friend class Converter;

	//Конструкторы
	public:
		NumberVector();
		NumberVector(const NumberVector &numberVector);
		NumberVector(const std::string dataString, NumericSystem system=Dec);
	
	//Преобразование и считывание из сторк
	public:
		NumberVector& Parse(const std::string dataString, NumericSystem system=Dec);
		std::string ToString(NumericSystem system=Dec) const;
	
	//Унарные операции
	public:
		NumberVector& operator= (const NumberVector& numberVector);

	//Операции сравнения
	public:
		NumberVector Compare(const NumberVector& numberVector) const;
		friend bool operator==(const NumberVector& a, const NumberVector& b);
		friend bool operator!=(const NumberVector& a, const NumberVector& b);

	//Методы акцепторы
	public:
		NumberVector& setZero();
		bool isZero() const;
		uint getNumberBits();
		uint getNumberBytes() const;
		std::vector<Integer *>::size_type getNumberDigits() const;
		Integer getNumber(std::vector<Integer *>::size_type position) const;
		void setNumber(std::vector<Integer *>::size_type position, Integer &integer);

	//Логические операции
	public:
		/*
		friend NumberVector operator^(const NumberVector &a, const NumberVector &b);
		NumberVector& operator^=(NumberVector &numberVector);
		NumberVector& Xor(NumberVector &a, NumberVector &b);
		friend NumberVector operator|(const NumberVector &a, const NumberVector &b);
		NumberVector& operator|=(NumberVector &numberVector);
		NumberVector& Or(NumberVector &a, NumberVector &b);
		friend NumberVector operator&(const NumberVector &a, const NumberVector &b);
		NumberVector& operator&=(NumberVector &numberVector);
		NumberVector& And(NumberVector &a, NumberVector &b);
		friend NumberVector operator!(const NumberVector &numberVector);
		NumberVector& Not(NumberVector &numberVector);
		*/

	//Операция сложения
	public:
		friend NumberVector operator+(const NumberVector &a, const NumberVector &b);
		NumberVector& operator+=(NumberVector &numberVector);
		NumberVector& Add(NumberVector &a, NumberVector &b);
		NumberVector& ModAdd(NumberVector &a, NumberVector &b, Integer &module);
	
	//Операция вычитания
	public:
		friend NumberVector operator-(const NumberVector &a, const NumberVector &b);
		NumberVector& operator-=(NumberVector &numberVector);
		NumberVector& Sub(NumberVector &a, NumberVector &b);
		NumberVector& ModSub(NumberVector &a, NumberVector &b, Integer &module);
    };
};
#endif