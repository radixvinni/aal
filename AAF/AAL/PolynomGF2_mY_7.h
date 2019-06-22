/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF2_mY_7H
#define PolynomGF2_mY_7H
//---------------------------------------------------------------------------
#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include "Polynom.h"
#include "PolynomGF2_m_4.h"

#include <set>

namespace AAL
{	
	class Converter;
    class Matrix;
    class Polynom;
    class PolynomGF2_m_4;
	class PolynomGF2_mY_7
	{	
	    private:
            Polynom _a0;
            Polynom _a1;
            Polynom _a2;
            Polynom _a3;
            Polynom _a4;
            Polynom _a5;
            Polynom _a6;
            Polynom _module;
            Polynom _modPolynom;
	//Конструкторы
	public:
		PolynomGF2_mY_7();
		PolynomGF2_mY_7(const PolynomGF2_mY_7 &polynom);
		PolynomGF2_mY_7(const std::string a0, const std::string a1, const std::string a2, const std::string a3,  const std::string a4, const std::string a5, const std::string a6,const std::string module);
	//Преобразование и считывание из строк
	public:
/*		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin);
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string ToString(const std::string dataString);
*/
	//Методы акцепторы
	public:
		PolynomGF2_mY_7& setOne();
		PolynomGF2_mY_7& setZero();
        bool isZero() const;
        bool isOne() const;
        int deg() const;
        const Polynom& getA0() const;
        const Polynom& getA1() const;
        const Polynom& getA2() const;
        const Polynom& getA3() const;
        const Polynom& getA4() const;
        const Polynom& getA5() const;
        const Polynom& getA6() const;
        const Polynom& getByIndex(int index) const;
        void setByIndex(const Polynom & a, int index);
        void setA0(const Polynom & a);
        void setA1(const Polynom & a);
        void setA2(const Polynom & a);
        void setA3(const Polynom & a);
        void setA4(const Polynom & a);
        void setA5(const Polynom & a);
        void setA6(const Polynom & a);
        const Polynom& getModule() const;
        const Polynom& getModPolynom() const;
        void setModPolynom(const Polynom& modPolynom);
        void setModule(const Polynom& module);
	//Унарные операции
	public:
		PolynomGF2_mY_7& operator= (const PolynomGF2_mY_7& polynom);

	//Операции сравнения
	public:
		friend bool operator==(const PolynomGF2_mY_7& a, const PolynomGF2_mY_7& b);
		friend bool operator!=(const PolynomGF2_mY_7& a, const PolynomGF2_mY_7& b);

	//Операция сложения
	public:
	 	friend PolynomGF2_mY_7 operator+(const PolynomGF2_mY_7 &a, const PolynomGF2_mY_7 &b);
		PolynomGF2_mY_7& operator+=(PolynomGF2_mY_7 &polynom);
		PolynomGF2_mY_7& Add(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b);
    //Операция умножения
	public:
        PolynomGF2_mY_7& Mul(PolynomGF2_m_4 &a, PolynomGF2_m_4 &b);
        PolynomGF2_mY_7& FullMul(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b);
        PolynomGF2_mY_7& MonomialMul(PolynomGF2_mY_7 &a, PolynomGF2_m_4 &b);
        PolynomGF2_mY_7& NormalMonomialMul(PolynomGF2_mY_7 &a, int d);
    //Деление с остатком
        PolynomGF2_mY_7& Div(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b, Polynom &module, PolynomGF2_mY_7 *remainder);
        PolynomGF2_mY_7& GCD(PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b, Polynom &module);

 	};
};
#endif

 
