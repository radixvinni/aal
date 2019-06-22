/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <vector>
#include "Integer.h"
#include "Polynom.h"
#include "IntegerBinom.h"
#include "IntegerBinomEllipticcurves.h"
#include "PolynomGF3.h"
class Integer;
class IntegerBinom;

namespace AAL
{
	class Converter
	{
	private:

		friend class Integer;
		friend class Polynom;
    friend class PolinomGF3;
	public:
		//Преобразования в класс Integer
		static Integer ToInteger(const std::string &dataString, NumericSystem system=Dec);
		static Integer ToInteger(const Polynom &polynom);
		static Integer ToInteger(const PolynomGF3 &polynom);
		static Integer ToInteger(std::string &polynom);

		//Преобразования в класс Polynom
		static Polynom ToPolynom(const std::string &dataString, PolynomSystem system=BackBin);
		static Polynom ToPolynom(const Integer &integer);
    //Преобразование в класс PolynomGF3
    static PolynomGF3 ToPolynomGF3(const Integer &integer);
		//Преобразование в строку
		static std::string ToString(const Integer &integer, NumericSystem system=Dec);
		static std::string ToString(const Polynom &polynom, PolynomSystem system=BackBin);

		static std::string FactorToString(std::vector<IntegerBinom> & factor, std::vector<std::vector<IntegerBinom> > & subGroups);
    static std::string FactorToTexString(std::vector<IntegerBinom> & factor, std::vector<std::vector<IntegerBinom> > & subGroups);
    static std::string MultitudeToString(std::vector<IntegerBinom> & multitude);

    static std::string MultitudeToTexString(std::vector<IntegerBinomEllipticPoint> & multitude);
    static std::string FactorToTexString(std::vector<std::vector<IntegerBinomEllipticPoint> > & factor);
	};
};
#endif
