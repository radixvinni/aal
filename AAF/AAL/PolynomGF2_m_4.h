/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF2_m_4H
#define PolynomGF2_m_4H
//---------------------------------------------------------------------------
#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include "Polynom.h"

#include <set>

namespace AAL
{
	class Converter;
    class Matrix;
    class Polynom;
	class PolynomGF2_m_4
	{
	    private:
            Polynom _a0;
            Polynom _a1;
            Polynom _a2;
            Polynom _a3;
            Polynom _module;
            Polynom _modPolynom;
	//Конструкторы
	public:
        PolynomGF2_m_4() :
        _a0(), _a1(), _a2(), _a3(), _module(), _modPolynom("11001")
        {
        }
		//PolynomGF2_m_4();
		PolynomGF2_m_4(const PolynomGF2_m_4 &polynom);
		PolynomGF2_m_4(const std::string a0, const std::string a1, const std::string a2, const std::string a3, const std::string module);
	//Преобразование и считывание из строк
	public:
/*		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin);
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string ToString(const std::string dataString);
*/
	//Методы акцепторы
	public:
		PolynomGF2_m_4& setOne();
		PolynomGF2_m_4& setZero();
        bool isZero() const;
        bool isOne() const;
        const Polynom& getA0() const;
        const Polynom& getA1() const;
        const Polynom& getA2() const;
        const Polynom& getA3() const;
        void setA0(const Polynom & a);
        void setA1(const Polynom & a);
        void setA2(const Polynom & a);
        void setA3(const Polynom & a);
        const Polynom& getModule() const;
        const Polynom& getModPolynom() const;
        void setModPolynom(const Polynom& modPolynom);
        void setModule(const Polynom& module);
        void exist(Polynom& a, Polynom& module);
        const Polynom& getByIndex(int index) const;
        void setByIndex(const Polynom & a, int index);

	//Унарные операции
	public:
		PolynomGF2_m_4& operator= (const PolynomGF2_m_4& polynom);

	//Операции сравнения
	public:
		friend bool operator==(const PolynomGF2_m_4& a, const PolynomGF2_m_4& b);
		friend bool operator!=(const PolynomGF2_m_4& a, const PolynomGF2_m_4& b);

	//Операция сложения
	public:
		friend PolynomGF2_m_4 operator+(const PolynomGF2_m_4 &a, const PolynomGF2_m_4 &b);
		PolynomGF2_m_4& operator+=(PolynomGF2_m_4 &polynom);
		PolynomGF2_m_4& Add(PolynomGF2_m_4 &a, PolynomGF2_m_4 &b);
    //Операция умножения
	public:
		friend PolynomGF2_m_4 operator*(const PolynomGF2_m_4 &a, const PolynomGF2_m_4 &b);
		PolynomGF2_m_4& operator*=(PolynomGF2_m_4 &polynom);
		PolynomGF2_m_4& Mul(PolynomGF2_m_4 &a, PolynomGF2_m_4 &b);
    //Операция возведение в степень
	public:
		PolynomGF2_m_4& Square(PolynomGF2_m_4 &a);
		PolynomGF2_m_4& Pow(PolynomGF2_m_4 &a, Integer n);
    //извлечение квадратного корня
    public:
         PolynomGF2_m_4& Sqrt(PolynomGF2_m_4 &a, Polynom &module);
    public:
        PolynomGF2_m_4& Inverse(Polynom &module);
		PolynomGF2_m_4& Inverse(PolynomGF2_m_4 &polynom, Polynom &module);
        int deg() const;
    //Тест образующего элемента
    Integer& elementOrder(Polynom &groupModule, PolynomGF2_m_4 &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
    bool isGenerator(Polynom &groupModule, PolynomGF2_m_4 &polynom,std::vector<DecompositionMember> vector, const Integer &ord);
 	};
};
#endif
