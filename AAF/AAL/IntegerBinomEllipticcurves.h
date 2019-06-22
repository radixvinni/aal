/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __INTEGERBINOMELLIPTICCURVES_H__
#define __INTEGERBINOMELLIPTICCURVES_H__

#include "IntegerBinom.h"

namespace AAL
{
        // Класс для представления эллиптической над GF(p^2) кривой вида Y^2 = X^3 + aX + b, где
        // a, b принадлежат GF(p^2)
        class IntegerBinomEllipticPoint;
        class IntegerBinomEllipticCurve
        {
        private:
                IntegerBinom * _a;
                IntegerBinom * _b;
        // Конструкторы
        public:
                // default: TODO: заполнить
                IntegerBinomEllipticCurve();
                IntegerBinomEllipticCurve(const IntegerBinom & a, const IntegerBinom & b);
                IntegerBinomEllipticCurve(const IntegerBinomEllipticCurve & curve);
                ~IntegerBinomEllipticCurve();
        //Методы акцепторы
	public:
		const Integer& getModule() const;
                const IntegerBinomModulePolynom& getModulePolynom() const;
		const IntegerBinom& getA() const;
		const IntegerBinom& getB() const;
		/*Integer& setModule(Integer &module);
		Integer& setA(Integer &a);
		Integer& setB(Integer &b);
		EllipticCurve& setCurve(Integer &module);*/
        //Унарные операции
	public:
		IntegerBinomEllipticCurve& operator=(const IntegerBinomEllipticCurve &eCurve);
        //Операции сравнения
	public:
		friend bool operator==(const IntegerBinomEllipticCurve &eCurve1, const IntegerBinomEllipticCurve &eCurve2);
		friend bool operator!=(const IntegerBinomEllipticCurve &eCurve1, const IntegerBinomEllipticCurve &eCurve2);
        //Принадлежность точки к кривой
	public:
		bool inGroup(const IntegerBinom &x, const IntegerBinom &y) const;
        private:
                IntegerBinom getLeftSide(const IntegerBinom &y) const;
                IntegerBinom getRightSide(const IntegerBinom &x) const;
        // создание групп точек кривой
        private:
                uint getMaxModuleForGroupCreation() const;
                bool isGroupSmallEnoughForGroupCreation() const;
        public:
                std::vector<IntegerBinomEllipticPoint> CreateGroup() const;
        // создание групп точек n-кручения кривой
        public:
                std::vector<IntegerBinomEllipticPoint> CreateSpinningGroup(const Integer &n) const;
        private:
                std::vector<IntegerBinomEllipticPoint> CreateSpinningGroup(const Integer &n, std::vector<IntegerBinomEllipticPoint> &group) const;
        // создание группы n*EC(GF(p^2))
        public:
                std::vector<IntegerBinomEllipticPoint> CreateMultipliedGroup(const Integer &n) const;
        private:
                std::vector<IntegerBinomEllipticPoint> CreateMultipliedGroup(const Integer &n, std::vector<IntegerBinomEllipticPoint> &group) const;
                bool isInMultitude(IntegerBinomEllipticPoint & point, std::vector<IntegerBinomEllipticPoint> &multitude) const;
        // создание фактор группы EC(GF(p^2)) / n*EC(GF(p^2))
        public:
                std::vector<std::vector<IntegerBinomEllipticPoint> >  CreateFactorGroup(const Integer &n) const;
        private:
                std::vector<std::vector<IntegerBinomEllipticPoint> >  CreateFactorGroup(const Integer &n, std::vector<IntegerBinomEllipticPoint> &group) const;
                std::vector<IntegerBinomEllipticPoint> AddToMultitude(IntegerBinomEllipticPoint & point, std::vector<IntegerBinomEllipticPoint> & multitude) const;
        // Операция работы со строками
        public:
                static std::string MultitudeToTexString(std::vector<IntegerBinomEllipticPoint> & multitude);
                static std::string FactorToTexString(std::vector<std::vector<IntegerBinomEllipticPoint> > & factor);
        };

        class IntegerBinomEllipticPoint
	{
	private:
		IntegerBinomEllipticCurve *_curve;
		IntegerBinom *_x;
		IntegerBinom *_y;
		bool _infinite;
        //Конструкторы
	public:
		IntegerBinomEllipticPoint();
		IntegerBinomEllipticPoint(const IntegerBinomEllipticCurve &eCurve);
		IntegerBinomEllipticPoint(const IntegerBinomEllipticPoint &ePoint);
		~IntegerBinomEllipticPoint();
        //Методы акцепторы
	public:
		const IntegerBinomEllipticCurve& getCurve();
		const IntegerBinom& getX();
		const IntegerBinom& getY();
		IntegerBinomEllipticCurve& setCurve(IntegerBinomEllipticCurve &eCurve);
		IntegerBinomEllipticPoint& setXY(const IntegerBinom &x, const IntegerBinom &y);
		bool isInfinite() const;
		IntegerBinomEllipticPoint& setInfinite(bool infinite);
                bool isSelfnegative();
        //Унарные операции
	public:
		IntegerBinomEllipticPoint& operator=(const IntegerBinomEllipticPoint &ePoint);

	//Операции сравнения
	public:
		friend bool operator==(const IntegerBinomEllipticPoint &ePoint1, const IntegerBinomEllipticPoint &ePoint2);
		friend bool operator!=(const IntegerBinomEllipticPoint &ePoint1, const IntegerBinomEllipticPoint &ePoint2);
        //Операция взятия противоположной точки (-P)
        public:
                IntegerBinomEllipticPoint& Negate();
		IntegerBinomEllipticPoint& Negate(IntegerBinomEllipticPoint& ePoint);
        //Операция сложение
	public:
		friend IntegerBinomEllipticPoint operator+(IntegerBinomEllipticPoint &ePoint1, IntegerBinomEllipticPoint &ePoint2);
		IntegerBinomEllipticPoint& operator+=(IntegerBinomEllipticPoint &ePoint);
		IntegerBinomEllipticPoint& Add(IntegerBinomEllipticPoint &ePoint1, IntegerBinomEllipticPoint &ePoint2);
        //Операция удвоения
	public:
		IntegerBinomEllipticPoint& Double();
		IntegerBinomEllipticPoint& Double(IntegerBinomEllipticPoint &e);
        //Операция умножения на константу
	public:
		IntegerBinomEllipticPoint& Mul(IntegerBinomEllipticPoint &ePoint, Integer &i);
        //Операция нахождения порядка точки
	public:
		Integer Order();
        //Операция функции искажающего отображения ((x,0),(y,0)) => ((-x,0),(0,y))
	public:
		IntegerBinomEllipticPoint& Distortion();
                IntegerBinomEllipticPoint& Distortion(IntegerBinomEllipticPoint& point);
        //Операция генерации точки
	public:
		IntegerBinomEllipticPoint& Generate();
       // IntegerBinomEllipticPoint& WrapingGenerate(Integer& const xforwrap);
        // Операция работы со строками
        public:
                std::string ToString();
                std::string ToTexString();
        };

}
#endif


