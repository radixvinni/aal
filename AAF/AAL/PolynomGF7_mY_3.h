/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF7_mY_3H
#define PolynomGF7_mY_3H
//---------------------------------------------------------------------------
#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include "PolynomGF7.h"
#include "PolynomGF7_m_14.h"
#include "PolynomGF7_m_2.h"
#include <set>

namespace AAL
{	
	class Converter;
    class Matrix;
    class PolynomGF7;
    class PolynomGF7_m_14;
    class PolynomGF7_m_2;
	class PolynomGF7_mY_3
	{	
	    private:
            PolynomGF7 _a0;
            PolynomGF7 _a1;
            PolynomGF7 _a2;

            PolynomGF7 _module;
            PolynomGF7 _modPolynom;
	//Конструкторы
	public:
		PolynomGF7_mY_3();
		PolynomGF7_mY_3(const PolynomGF7_mY_3 &polynom);
		PolynomGF7_mY_3(const std::string a0, const std::string a1, const std::string a2,const std::string module);
	//Преобразование и считывание из строк
	public:
/*		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin);
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string ToString(const std::string dataString);
*/
	//Методы акцепторы
	public:
		PolynomGF7_mY_3& setOne();
		PolynomGF7_mY_3& setPolynom(uchar);
		PolynomGF7_mY_3& setZero();
		PolynomGF7_mY_3& setZero(PolynomGF7 &module);

        bool isZero() const;
        bool isZero(PolynomGF7 &module) const;

        bool isOne() const;
        int deg() const;
        const PolynomGF7& getA0() const;
        const PolynomGF7& getA1() const;
        const PolynomGF7& getA2() const;

        const PolynomGF7& getByIndex(int index) const;
        void setByIndex(const PolynomGF7 & a, int index);
        void setA0(const PolynomGF7 & a);
        void setA1(const PolynomGF7 & a);
        void setA2(const PolynomGF7 & a);

        const PolynomGF7& getModule() const;
        const PolynomGF7& getModPolynom() const;
        void setModPolynom(const PolynomGF7& modPolynom);
        void setModule(const PolynomGF7& module);
	//Унарные операции
	public:
		PolynomGF7_mY_3& operator= (const PolynomGF7_mY_3& polynom);

	//Операции сравнения
	public:
		friend bool operator==(const PolynomGF7_mY_3& a, const PolynomGF7_mY_3& b);
		friend bool operator!=(const PolynomGF7_mY_3& a, const PolynomGF7_mY_3& b);

	//Операция сложения
	public:
	 	friend PolynomGF7_mY_3 operator+(const PolynomGF7_mY_3 &a, const PolynomGF7_mY_3 &b);
		PolynomGF7_mY_3& operator+=(PolynomGF7_mY_3 &polynom);
		PolynomGF7_mY_3& Add(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b);
    //Операция умножения
	public:
        PolynomGF7_mY_3& Mul(PolynomGF7 &a, PolynomGF7 &b);
        PolynomGF7_mY_3& FullMul(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b);
        PolynomGF7_mY_3& MonomialMul(PolynomGF7_mY_3 &a, PolynomGF7 &b);
        PolynomGF7_mY_3& NormalMonomialMul(PolynomGF7_mY_3 &a, int d);
    //Деление с остатком
        PolynomGF7_mY_3& Div(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b, PolynomGF7 &module, PolynomGF7_mY_3 *remainder);
        PolynomGF7_mY_3& GCD(PolynomGF7_mY_3 &a, PolynomGF7_mY_3 &b, PolynomGF7 &module);

 	};
};
#endif


