/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "Converter.h"
#include <memory>
#include <stdlib.h>
#include <math.h>
#include <string>
namespace AAL
{
//*************************     Преобразования в класс Integer    ******************************
	Integer Converter::ToInteger(const std::string &dataString, NumericSystem system)
	{
		return Integer(dataString, system);
	}
//---------------------------------------------------------------------------------
	Integer Converter::ToInteger(const Polynom &polynom)
	{
		Integer result;
		if(!polynom.isZero())
		{
			uint numberDigits = polynom.getNumberBytes() / result.getDigitSizeInBytes() + ((polynom.getNumberBytes() % result.getDigitSizeInBytes()) != 0);
			result.setNumberDigits(numberDigits);
			result._digits[result._numberDigits-1] = 0;
			std::memcpy(result._digits, polynom._digits, polynom.getNumberBytes());
		}
		return result;
	}
//-----------------------------------------------------------------------------------
 Integer Converter::ToInteger(std::string &polynom) {
   Integer result;
   if(polynom.length() != 0) {
      int last_nonzero = polynom.find_last_of("1");
      result.Pow(2,last_nonzero);
   }
  return result;
 }
//---------------------------------------------------------------------------------
  Integer Converter::ToInteger(const PolynomGF3 &polynom) {
		Integer result=1;
    Integer p_num;
    std::string polynom_number = polynom.ToString();
    int last_nonzero = polynom_number.find_last_of("1,2");
    if( last_nonzero != -1)
      result.Pow(3,last_nonzero);
		return result;
  }
//**********************************************************************************************

//*************************     Преобразования в класс Polynom    ******************************
	Polynom Converter::ToPolynom(const std::string &dataString, PolynomSystem system)
	{
		std::string invertData(dataString.rbegin(), dataString.rend());
		Integer integer(invertData, (NumericSystem)system);
		return Converter::ToPolynom(integer);
	}

	Polynom Converter::ToPolynom(const Integer &integer)
	{
		Polynom result;
		if(!integer.isZero())
		{
			uint numberDigits = integer.getNumberBytes() / result.getDigitSizeInBytes() + ((integer.getNumberBytes() % result.getDigitSizeInBytes()) != 0);
			result.setNumberDigits(numberDigits);
			result._digits[result._numberDigits-1] = 0;
			std::memcpy(result._digits, integer._digits, integer.getNumberBytes());
		}
		return result;
	}
//**********************************************************************************************
//***********************Преобразование в класс PolynomGF3*************************************
 PolynomGF3 Converter::ToPolynomGF3(const Integer &integer)
{
  Integer sustem("3");
  Integer num(integer);
  Integer div(integer);
  unsigned int count;
  std::string tern = "";
  while(div > 2)
  {
    tern.append((num%sustem).ToString());
    div = num/sustem;
    num = div;
  }
  tern.append(div.ToString());
  std::string overtern(tern.rbegin(),tern.rend());
  return 	 PolynomGF3(overtern);
}
//**********************************************************************************************
//*************************         Преобразование в строку       ******************************
	std::string Converter::ToString(const Integer &integer, NumericSystem system)
	{
		return integer.ToString(system);
	}

	std::string Converter::ToString(const Polynom &polynom, PolynomSystem system)
	{
		std::string dataString = Converter::ToInteger(polynom).ToString((NumericSystem)system);
 		return std::string(dataString.rbegin(), dataString.rend());
	}
//**********************************************************************************************
        std::string Converter::FactorToString(std::vector<IntegerBinom> & factor, std::vector<std::vector<IntegerBinom> > & subGroups)
        {
                std::string result;

                std::vector<std::vector<IntegerBinom> >::iterator groupIt = subGroups.begin();
                for(std::vector<IntegerBinom>::iterator it = factor.begin();
                it != factor.end(); ++it, ++groupIt)
                {
                        if(!(*it).isOne())
                                result += (*it).ToString() + "x";

                        result += "GF(";
                        result += (*(*groupIt).begin()).getModule().ToString();
                        result += "^2)^";
                        result += Integer(factor.size()).ToString();
                        result += "=";
                        result += "{";
                        result += MultitudeToString(*groupIt);
                        result += "}";
                        result += "\n";
                }

                return result;
        }
        std::string Converter::MultitudeToString(std::vector<IntegerBinom> & multitude)
        {
                std::string result;

                std::vector<IntegerBinom>::iterator it = multitude.begin();
                result += (*(it++)).ToString();
                for(;
                it != multitude.end(); ++it)
                {
                        result +=  "," + (*it).ToString();
                }
                return result;
        }
        std::string Converter::FactorToTexString(std::vector<IntegerBinom> & factor, std::vector<std::vector<IntegerBinom> > & subGroups)
        {
                std::string result;

                std::vector<std::vector<IntegerBinom> >::iterator groupIt = subGroups.begin();
                for(std::vector<IntegerBinom>::iterator it = factor.begin();
                it != factor.end(); ++it, ++groupIt)
                {
                        result += "\\begin{eqnarray}\\nonumber\n";
                        if(!(*it).isOne())
                                result += (*it).ToString() + "\\times ";

                        result += "GF(";
                        result += (*(*groupIt).begin()).getModule().ToString();
                        result += "^2)^";
                        result += Integer(factor.size()).ToString();
                        result += "=";
                        result += "\\{";
                        result += MultitudeToString(*groupIt);
                        result += "\\}\\end{eqnarray}\\nonumber";
                        result += "\n";
                }

                return result;
        }

        std::string Converter::MultitudeToTexString(std::vector<IntegerBinomEllipticPoint> & multitude)
        {
/*
\begin{equation}

\left(

\begin{array}

{clll}
{\bf \cal O}

&

\end{array}
\right)
\end{equation}
*/
                std::string result;

                result += "\\begin{equation}\n";
                result += "\\left(\n";
                result += "\\begin{array}";

                std::vector<IntegerBinomEllipticPoint>::iterator it = multitude.begin();
                result += "{clll}";

                int pointNumber = 2;
                result += "\n";
                result += (*(it++)).ToTexString();
                for(;
                it != multitude.end(); ++it, ++pointNumber)
                {
                        if((pointNumber > 4) && (pointNumber % 4 == 1))
                                result +=  "\\\\\n";
                        else
                                result +=  " & ";
                        result += (*it).ToTexString();
                }

                result += "\\end{array}\n";
                result += "\\right)\n";
                result += "\\end{equation}\n";

                return result;
        }
        std::string Converter::FactorToTexString(std::vector<std::vector<IntegerBinomEllipticPoint> > & factor)
        {
                std::string result;

                std::vector<std::vector<IntegerBinomEllipticPoint> >::iterator it = factor.begin();
                result += MultitudeToTexString(*(it++));
                for(;
                it != factor.end(); ++it)
                {
                        result +=  "\n\n" + MultitudeToTexString(*it);
                }

                return result;
        }
//**********************************************************************************************
};
