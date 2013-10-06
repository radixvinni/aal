/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF3_mY_9H
#define PolynomGF3_mY_9H
//---------------------------------------------------------------------------
#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include "PolynomGF3.h"
#include "PolynomGF3_m_6.h"

#include <set>

namespace AAL
{	
	class Converter;
    class Matrix;
    class PolynomGF3;
    class PolynomGF3_m_6;
	class PolynomGF3_mY_9
	{	
	    private:
            PolynomGF3 _a0;
            PolynomGF3 _a1;
            PolynomGF3 _a2;
            PolynomGF3 _a3;
            PolynomGF3 _a4;
            PolynomGF3 _a5;
            PolynomGF3 _a6;
            PolynomGF3 _a7;
            PolynomGF3 _a8;
            PolynomGF3 _a9;
            PolynomGF3 _a10;

            PolynomGF3 _module;
            PolynomGF3 _modPolynom;
	//Конструкторы
	public:
		PolynomGF3_mY_9();
		PolynomGF3_mY_9(const PolynomGF3_mY_9 &polynom);
		PolynomGF3_mY_9(const std::string a0, const std::string a1, const std::string a2, const std::string a3,  const std::string a4, const std::string a5, const std::string a6,const std::string a7, const std::string a8,const std::string a9, const std::string a10,const std::string module);
	//Преобразование и считывание из строк
	public:
/*		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin);
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string ToString(const std::string dataString);
*/
	//Методы акцепторы
	public:
		PolynomGF3_mY_9& setOne();
		PolynomGF3_mY_9& setZero();
        bool isZero() const;
        bool isOne() const;
        int deg() const;
        const PolynomGF3& getA0() const;
        const PolynomGF3& getA1() const;
        const PolynomGF3& getA2() const;
        const PolynomGF3& getA3() const;
        const PolynomGF3& getA4() const;
        const PolynomGF3& getA5() const;
        const PolynomGF3& getA6() const;
        const PolynomGF3& getA7() const;
        const PolynomGF3& getA8() const;
        const PolynomGF3& getA9() const;
        const PolynomGF3& getA10() const;

        const PolynomGF3& getByIndex(int index) const;
        void setByIndex(const PolynomGF3 & a, int index);
        void setA0(const PolynomGF3 & a);
        void setA1(const PolynomGF3 & a);
        void setA2(const PolynomGF3 & a);
        void setA3(const PolynomGF3 & a);
        void setA4(const PolynomGF3 & a);
        void setA5(const PolynomGF3 & a);
        void setA6(const PolynomGF3 & a);
        void setA7(const PolynomGF3 & a);
        void setA8(const PolynomGF3 & a);
        void setA9(const PolynomGF3 & a);
        void setA10(const PolynomGF3 & a);

        const PolynomGF3& getModule() const;
        const PolynomGF3& getModPolynom() const;
        void setModPolynom(const PolynomGF3& modPolynom);
        void setModule(const PolynomGF3& module);
	//Унарные операции
	public:
		PolynomGF3_mY_9& operator= (const PolynomGF3_mY_9& polynom);

	//Операции сравнения
	public:
		friend bool operator==(const PolynomGF3_mY_9& a, const PolynomGF3_mY_9& b);
		friend bool operator!=(const PolynomGF3_mY_9& a, const PolynomGF3_mY_9& b);

	//Операция сложения
	public:
	 	friend PolynomGF3_mY_9 operator+(const PolynomGF3_mY_9 &a, const PolynomGF3_mY_9 &b);
		PolynomGF3_mY_9& operator+=(PolynomGF3_mY_9 &polynom);
		PolynomGF3_mY_9& Add(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b);
    //Операция умножения
	public:
        PolynomGF3_mY_9& Mul(PolynomGF3_m_6 &a, PolynomGF3_m_6 &b);
        PolynomGF3_mY_9& FullMul(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b);
        PolynomGF3_mY_9& MonomialMul(PolynomGF3_mY_9 &a, PolynomGF3_m_6 &b);
        PolynomGF3_mY_9& NormalMonomialMul(PolynomGF3_mY_9 &a, int d);
    //Деление с остатком
        PolynomGF3_mY_9& Div(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b, PolynomGF3 &module, PolynomGF3_mY_9 *remainder);
        PolynomGF3_mY_9& GCD(PolynomGF3_mY_9 &a, PolynomGF3_mY_9 &b, PolynomGF3 &module);

 	};
};
#endif

 
