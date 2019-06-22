/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __POLYNOMGF3N6_H__
#define __POLYNOMGF3N6_H__

#include "Integer.h"
#include "PolynomGF3.h"
#include "Algorithms.h"
#include "DecompositionManager.h"
#include <vector>

namespace AAL
{

        class PolynomN6
        {
        private:
                PolynomGF3 _a1;
                PolynomGF3 _a2;
                PolynomGF3 _a3;
                PolynomGF3 _a4;
                PolynomGF3 _a5;
                PolynomGF3 _a6;
                PolynomGF3 _module;
                PolynomGF3 _modulePolynom;
        //Конструкторы
        public:
                // (0,0) по модулю 1 + X^2, p = 7
                PolynomN6();
                PolynomN6(const PolynomN6 & polynom);
                PolynomN6(const PolynomGF3& a1, const PolynomGF3& a2, const PolynomGF3& a3, const PolynomGF3& a4,const PolynomGF3& a5,const PolynomGF3& a6,const PolynomGF3& mpolynom ,const PolynomGF3& modulePolynom);
                PolynomN6(const std::string dataString,const PolynomGF3& mpolynom ,const PolynomGF3& modulePolynom);
                ~PolynomN6();
        //Преобразование и считывание из строк
	public:
		std::string ToString() const;
                void FromString(std::string s);
        //Методы акцепторы
        public:
                bool isZero() const;
                bool isOne() const;
                void setZero();
                void setOne();
                void setTwo();
                const PolynomGF3& getA1() const;
                const PolynomGF3& getA2() const;
                const PolynomGF3& getA3() const;
                const PolynomGF3& getA4() const;
                const PolynomGF3& getA5() const;
                const PolynomGF3& getA6() const;
                void setA1(const PolynomGF3 & a);
                void setA2(const PolynomGF3 & a);
                void setA3(const PolynomGF3 & a);
                void setA4(const PolynomGF3 & a);
                void setA5(const PolynomGF3 & a);
                void setA6(const PolynomGF3 & a);
                const PolynomGF3& getModule() const;
                const PolynomGF3& getModulePolynom() const;
                void setModulePolynom(const PolynomGF3& modulePolynom);
                void setModule(const PolynomGF3& modulePolynom);
                Integer getMulGroupOrder() const;
                bool isPrimitivity() const;
        //Унарные операции
	public:
		PolynomN6& operator= (const PolynomN6& polynom);
	//Операции сравнения
	public:
                friend bool operator==(const PolynomN6& a, const PolynomN6& b);
		friend bool operator!=(const PolynomN6& a, const PolynomN6& b);
        //Операция сложения
	public:
		friend PolynomN6 operator+(const PolynomN6 &a, const PolynomN6 &b);
		PolynomN6& operator+=(PolynomN6 & polynom);
		PolynomN6& Add(PolynomN6 &a, PolynomN6 &b);
        //Операция вычитания
	public:
		friend PolynomN6 operator-(const PolynomN6 &a, const PolynomN6 &b);
		PolynomN6& operator-=(PolynomN6 & polynom);
		PolynomN6& Sub(PolynomN6 &a, PolynomN6 &b);
        //Операция взятия противоположного элемента
	public:
		PolynomN6& Negate();
		PolynomN6& Negate(PolynomN6 &polynom);
        //Операция умножения
	public:
		friend PolynomN6 operator*(const PolynomN6 &a, const PolynomN6 &b);
		PolynomN6& operator*=(PolynomN6 & polynom);
		PolynomN6& Mul(PolynomN6 &a, PolynomN6 &b);
        //Операция возведения в степень
	public:
		PolynomN6& Pow(PolynomN6 &a, Integer &n);
        //Операция взятия обратного элемента
	public:
                PolynomN6& Inverse();
		PolynomN6& Inverse(PolynomN6 &a);
        // Операции генерации
        public:
		PolynomN6& Generate();
            PolynomN6& Square(PolynomN6 &a);
        
                
        
        };
};

#endif
