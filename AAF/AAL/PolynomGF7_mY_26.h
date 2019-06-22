/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF7_mY_26H
#define PolynomGF7_mY_26H
//---------------------------------------------------------------------------
#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include "PolynomGF7.h"
#include "PolynomGF7_m14.h"
#include "PolynomGF7.h"
#include <set>

namespace AAL
{	
	class Converter;
    class Matrix;
    class PolynomGF7;
    class PolynomGF7_m14;
    class PolynomGF7;
	class PolynomGF7_mY_26
	{	
	    private:
            PolynomGF7 _a0;
            PolynomGF7 _a1;
            PolynomGF7 _a2;
            PolynomGF7 _a3;
            PolynomGF7 _a4;
            PolynomGF7 _a5;
            PolynomGF7 _a6;
            PolynomGF7 _a7;
            PolynomGF7 _a8;
            PolynomGF7 _a9;
            PolynomGF7 _a10;
            PolynomGF7 _a11;
            PolynomGF7 _a12;
            PolynomGF7 _a13;
            PolynomGF7 _a14;
            PolynomGF7 _a15;
            PolynomGF7 _a16;
            PolynomGF7 _a17;
            PolynomGF7 _a18;
            PolynomGF7 _a19;
            PolynomGF7 _a20;
            PolynomGF7 _a21;
            PolynomGF7 _a22;
            PolynomGF7 _a23;
            PolynomGF7 _a24;
            PolynomGF7 _a25;

            PolynomGF7 _module;
            PolynomGF7 _modPolynom;
	//Конструкторы
	public:
		PolynomGF7_mY_26();
		PolynomGF7_mY_26(const PolynomGF7_mY_26 &polynom);
		PolynomGF7_mY_26(const std::string a0, const std::string a1, const std::string a2, const std::string a3,  const std::string a4, const std::string a5, const std::string a6,const std::string a7, const std::string a8,const std::string a9, const std::string a10,const std::string a11, const std::string a12,const std::string a13, const std::string a14, const std::string a15, const std::string a16,  const std::string a17, const std::string a18, const std::string a19,const std::string a20, const std::string a21,const std::string a22, const std::string a23,const std::string a24, const std::string a25,const std::string module);
	//Преобразование и считывание из строк
	public:
/*		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin);
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string ToString(const std::string dataString);
*/
	//Методы акцепторы
	public:
		PolynomGF7_mY_26& setOne();
		PolynomGF7_mY_26& setPolynom(uchar);
		PolynomGF7_mY_26& setZero();
		PolynomGF7_mY_26& setZero(PolynomGF7 &module);

        bool isZero() const;
        bool isZero(PolynomGF7 &module) const;

        bool isOne() const;
        int deg() const;
        const PolynomGF7& getA0() const;
        const PolynomGF7& getA1() const;
        const PolynomGF7& getA2() const;
        const PolynomGF7& getA3() const;
        const PolynomGF7& getA4() const;
        const PolynomGF7& getA5() const;
        const PolynomGF7& getA6() const;
        const PolynomGF7& getA7() const;
        const PolynomGF7& getA8() const;
        const PolynomGF7& getA9() const;
        const PolynomGF7& getA10() const;
        const PolynomGF7& getA11() const;
        const PolynomGF7& getA12() const;
        const PolynomGF7& getA13() const;
        const PolynomGF7& getA14() const;
        const PolynomGF7& getA15() const;
        const PolynomGF7& getA16() const;
        const PolynomGF7& getA17() const;
        const PolynomGF7& getA18() const;
        const PolynomGF7& getA19() const;
        const PolynomGF7& getA20() const;
        const PolynomGF7& getA21() const;
        const PolynomGF7& getA22() const;
        const PolynomGF7& getA23() const;
        const PolynomGF7& getA24() const;
        const PolynomGF7& getA25() const;

        const PolynomGF7& getByIndex(int index) const;
        void setByIndex(const PolynomGF7 & a, int index);
        void setA0(const PolynomGF7 & a);
        void setA1(const PolynomGF7 & a);
        void setA2(const PolynomGF7 & a);
        void setA3(const PolynomGF7 & a);
        void setA4(const PolynomGF7 & a);
        void setA5(const PolynomGF7 & a);
        void setA6(const PolynomGF7 & a);
        void setA7(const PolynomGF7 & a);
        void setA8(const PolynomGF7 & a);
        void setA9(const PolynomGF7 & a);
        void setA10(const PolynomGF7 & a);
        void setA11(const PolynomGF7 & a);
        void setA12(const PolynomGF7 & a);
        void setA13(const PolynomGF7 & a);
        void setA14(const PolynomGF7 & a);
        void setA15(const PolynomGF7 & a);
        void setA16(const PolynomGF7 & a);
        void setA17(const PolynomGF7 & a);
        void setA18(const PolynomGF7 & a);
        void setA19(const PolynomGF7 & a);
        void setA20(const PolynomGF7 & a);
        void setA21(const PolynomGF7 & a);
        void setA22(const PolynomGF7 & a);
        void setA23(const PolynomGF7 & a);
        void setA24(const PolynomGF7 & a);
        void setA25(const PolynomGF7 & a);

        const PolynomGF7& getModule() const;
        const PolynomGF7& getModPolynom() const;
        void setModPolynom(const PolynomGF7& modPolynom);
        void setModule(const PolynomGF7& module);
	//Унарные операции
	public:
		PolynomGF7_mY_26& operator= (const PolynomGF7_mY_26& polynom);

	//Операции сравнения
	public:
		friend bool operator==(const PolynomGF7_mY_26& a, const PolynomGF7_mY_26& b);
		friend bool operator!=(const PolynomGF7_mY_26& a, const PolynomGF7_mY_26& b);

	//Операция сложения
	public:
	 	friend PolynomGF7_mY_26 operator+(const PolynomGF7_mY_26 &a, const PolynomGF7_mY_26 &b);
		PolynomGF7_mY_26& operator+=(PolynomGF7_mY_26 &polynom);
		PolynomGF7_mY_26& Add(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b);
    //Операция умножения
	public:
        PolynomGF7_mY_26& Mul(PolynomGF7_m14 &a, PolynomGF7_m14 &b);
        PolynomGF7_mY_26& FullMul(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b);
        PolynomGF7_mY_26& MonomialMul(PolynomGF7_mY_26 &a, PolynomGF7_m14 &b);
        PolynomGF7_mY_26& NormalMonomialMul(PolynomGF7_mY_26 &a, int d);
    //Деление с остатком
        PolynomGF7_mY_26& Div(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b, PolynomGF7 &module, PolynomGF7_mY_26 *remainder);
        PolynomGF7_mY_26& GCD(PolynomGF7_mY_26 &a, PolynomGF7_mY_26 &b, PolynomGF7 &module);

 	};
};
#endif


