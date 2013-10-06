/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __ELLIPTICCURVES_H__
#define __ELLIPTICCURVES_H__

#include "Integer.h"
#include <string>
#include <stdio.h>


namespace AAL
{
	class EllipticCurve
	{
	private:
		Integer *_module;
		Integer *_a;
		Integer *_b;

	//Конструкторы
	public:
		//default: y=x^3+x+b mod(5)
		EllipticCurve();
		EllipticCurve(Integer &module, Integer &J);
		//4a^3+27b^2 != 0 mod(module)
		EllipticCurve(Integer &module, Integer &a, Integer &b);
		EllipticCurve(const EllipticCurve &eCurve);
		~EllipticCurve();

	//Методы акцепторы
	private:
		bool isSmooth(Integer &module, Integer &a, Integer &b) const;
	public:
		Integer& getModule() const;
		Integer getInvariant() const;
		Integer& getA() const;
		Integer& getB() const;
		Integer& setModule(Integer &module);
		Integer& setA(Integer &a);
		Integer& setB(Integer &b);
                Integer getOrder();
		EllipticCurve& setCurve(Integer &module, Integer &J);
		EllipticCurve& setCurve(Integer &module);

	//Унарные операции
	public:
		EllipticCurve& operator=(const EllipticCurve &eCurve);

	//Операции сравнения
	public:
		friend bool operator==(const EllipticCurve &eCurve1, const EllipticCurve &eCurve2);
		friend bool operator!=(const EllipticCurve &eCurve1, const EllipticCurve &eCurve2);
	//Принадлежность точки к кривой
	public:
		bool inGroup(Integer &x, Integer &y) const;
	};

	class EllipticPoint
	{
	private:
		EllipticCurve *_curve;
		Integer *_x;
		Integer *_y;
		bool _infinite;

	//Конструкторы
	public:
		EllipticPoint();
		EllipticPoint(const EllipticCurve &eCurve);
		EllipticPoint(const EllipticPoint &ePoint);
		~EllipticPoint();

	//Методы акцепторы
	public:
		EllipticCurve& getCurve();
		Integer& getX();
		Integer& getY();
		EllipticCurve& setCurve(EllipticCurve &eCurve);
		EllipticPoint& setXY(Integer &x, Integer &y);
		bool isInfinite() const;
		EllipticPoint& setInfinite(bool infinite);

	//Унарные операции
	public:
		EllipticPoint& operator=(const EllipticPoint &ePoint);

	//Операции сравнения
	public:
		friend bool operator==(const EllipticPoint &ePoint1, const EllipticPoint &ePoint2);
		friend bool operator!=(const EllipticPoint &ePoint1, const EllipticPoint &ePoint2);

        //Операция взятия противоположной точки (-P)
                EllipticPoint& Negate();
		EllipticPoint& Negate(EllipticPoint& ePoint);
	//Операция сложение
	public:
		friend EllipticPoint operator+(EllipticPoint &ePoint1, EllipticPoint &ePoint2);
		EllipticPoint& operator+=(EllipticPoint &ePoint1);
		EllipticPoint& Add(EllipticPoint &ePoint1, EllipticPoint &ePoint2);

	//Операция удвоения
	public:
		EllipticPoint& Double();
		EllipticPoint& Double(EllipticPoint &e);

	//Операция умножения на константу
	public:
		friend EllipticPoint operator*(const EllipticPoint &ePoint, const Integer &i);
		friend EllipticPoint operator*(const Integer &i, const EllipticPoint &ePoint);
		EllipticPoint& operator*=(Integer &i);
		EllipticPoint& Mul(Integer &i, EllipticPoint &ePoint);
		EllipticPoint& Mul(EllipticPoint &ePoint, Integer &i);

	//Генерация точки
		EllipticPoint& Generate();
	};
}

#endif
