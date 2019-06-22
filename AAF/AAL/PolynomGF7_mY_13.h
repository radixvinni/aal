/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF7_mY_13H
#define PolynomGF7_mY_13H
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
	class PolynomGF7_mY_13
	{	
	    private:
            PolynomGF7_m_2 _a0;
            PolynomGF7_m_2 _a1;
            PolynomGF7_m_2 _a2;
            PolynomGF7_m_2 _a3;
            PolynomGF7_m_2 _a4;
            PolynomGF7_m_2 _a5;
            PolynomGF7_m_2 _a6;
            PolynomGF7_m_2 _a7;
            PolynomGF7_m_2 _a8;
            PolynomGF7_m_2 _a9;
            PolynomGF7_m_2 _a10;
            PolynomGF7_m_2 _a11;
            PolynomGF7_m_2 _a12;

            PolynomGF7 _module;
            PolynomGF7 _modPolynom;
	//Конструкторы
	public:
		PolynomGF7_mY_13();
		PolynomGF7_mY_13(const PolynomGF7_mY_13 &polynom);
		PolynomGF7_mY_13(const std::string a0, const std::string a1, const std::string a2, const std::string a3,  const std::string a4, const std::string a5, const std::string a6,const std::string a7, const std::string a8,const std::string a9, const std::string a10,const std::string a11, const std::string a12,const std::string a13, const std::string a14, const std::string a15, const std::string a16,  const std::string a17, const std::string a18, const std::string a19,const std::string a20, const std::string a21,const std::string a22, const std::string a23,const std::string a24, const std::string a25,const std::string module);
	//Преобразование и считывание из строк
	public:
/*		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin);
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string ToString(const std::string dataString);
*/
	//Методы акцепторы
	public:
		PolynomGF7_mY_13& setOne();
		PolynomGF7_mY_13& setPolynom(uchar);
		PolynomGF7_mY_13& setZero();
		PolynomGF7_mY_13& setZero(PolynomGF7 &module);

        bool isZero() const;
        bool isZero(PolynomGF7 &module) const;

        bool isOne() const;
        int deg() const;
        const PolynomGF7_m_2& getA0() const;
        const PolynomGF7_m_2& getA1() const;
        const PolynomGF7_m_2& getA2() const;
        const PolynomGF7_m_2& getA3() const;
        const PolynomGF7_m_2& getA4() const;
        const PolynomGF7_m_2& getA5() const;
        const PolynomGF7_m_2& getA6() const;
        const PolynomGF7_m_2& getA7() const;
        const PolynomGF7_m_2& getA8() const;
        const PolynomGF7_m_2& getA9() const;
        const PolynomGF7_m_2& getA10() const;
        const PolynomGF7_m_2& getA11() const;
        const PolynomGF7_m_2& getA12() const;

        const PolynomGF7_m_2& getByIndex(int index) const;
        void setByIndex(const PolynomGF7_m_2 & a, int index);
        void setA0(const PolynomGF7_m_2 & a);
        void setA1(const PolynomGF7_m_2 & a);
        void setA2(const PolynomGF7_m_2 & a);
        void setA3(const PolynomGF7_m_2 & a);
        void setA4(const PolynomGF7_m_2 & a);
        void setA5(const PolynomGF7_m_2 & a);
        void setA6(const PolynomGF7_m_2 & a);
        void setA7(const PolynomGF7_m_2 & a);
        void setA8(const PolynomGF7_m_2 & a);
        void setA9(const PolynomGF7_m_2 & a);
        void setA10(const PolynomGF7_m_2 & a);
        void setA11(const PolynomGF7_m_2 & a);
        void setA12(const PolynomGF7_m_2 & a);

        const PolynomGF7& getModule() const;
        const PolynomGF7& getModPolynom() const;
        void setModPolynom(const PolynomGF7& modPolynom);
        void setModule(const PolynomGF7& module);
	//Унарные операции
	public:
		PolynomGF7_mY_13& operator= (const PolynomGF7_mY_13& polynom);

	//Операции сравнения
	public:
		friend bool operator==(const PolynomGF7_mY_13& a, const PolynomGF7_mY_13& b);
		friend bool operator!=(const PolynomGF7_mY_13& a, const PolynomGF7_mY_13& b);

	//Операция сложения
	public:
	 	friend PolynomGF7_mY_13 operator+(const PolynomGF7_mY_13 &a, const PolynomGF7_mY_13 &b);
		PolynomGF7_mY_13& operator+=(PolynomGF7_mY_13 &polynom);
		PolynomGF7_mY_13& Add(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b);
    //Операция умножения
	public:
        PolynomGF7_mY_13& Mul(PolynomGF7_m_14 &a, PolynomGF7_m_14 &b);
        PolynomGF7_mY_13& FullMul(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b);
        PolynomGF7_mY_13& MonomialMul(PolynomGF7_mY_13 &a, PolynomGF7_m_14 &b);
        PolynomGF7_mY_13& NormalMonomialMul(PolynomGF7_mY_13 &a, int d);
    //Деление с остатком
        PolynomGF7_mY_13& Div(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b, PolynomGF7 &module, PolynomGF7_mY_13 *remainder);
        PolynomGF7_mY_13& GCD(PolynomGF7_mY_13 &a, PolynomGF7_mY_13 &b, PolynomGF7 &module);

 	};
};
#endif


