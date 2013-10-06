/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __ELLIPTICCURVESGF2_H__
#define __ELLIPTICCURVESGF2_H__

#include "Polynom.h"
#include "PolynomGF2_m_4.h"
#include "PolynomGF2_mY_7.h"

namespace AAL
{
        class Matrix;
        // абстрактный базовый класс эллиптических кривых над полем GF(2^n)
        class    EllipticCurveGF2
        {
        protected:
        	Polynom *_module;
        //виртуальный деструктор
        public:
                virtual ~EllipticCurveGF2() = 0;
        //Методы акцепторы
	public:
		Polynom& getModule() const;
                virtual Polynom& setModule(const Polynom &module) = 0;
                virtual bool isSuperSingular() const = 0;
                virtual bool isNonSuperSingular() const = 0;
        //Операции сравнения
        public:
                virtual bool equals(const EllipticCurveGF2 &eCurve) const = 0;
                friend bool operator==(const EllipticCurveGF2 &eCurve1, const EllipticCurveGF2 &eCurve2);
		friend bool operator!=(const EllipticCurveGF2 &eCurve1, const EllipticCurveGF2 &eCurve2);
        //Принадлежность точки к кривой
        public:
                virtual bool inGroup(Polynom &x, Polynom &y) const = 0;
        //Вычисление правой части уравнения
        public:
                virtual Polynom rightSide(Polynom &x) const = 0;
        // Проверка на существование Y для данного X
        public:
                virtual bool hasY(Polynom &x) const = 0;
        //Унарные операции
        private:
                EllipticCurveGF2& operator=(const EllipticCurveGF2 &eCurve);// запертил автогенерацию
        };
        // класс "суперсингулярных" эллиптических кривых над полем GF(2^n)
        // вид: Y^2 + a3*Y = X^3 + a4*X + a6
        class SuperSingularEllipticCurve : public EllipticCurveGF2
	{
        private:
                Polynom *_a3;
                Polynom *_a4;
                Polynom *_a6;
	//Конструкторы
	public:
		//default: Y^2 + Y = X^3 + X + 1 (mod m(x) = 1+x+x^3)
		SuperSingularEllipticCurve();
		SuperSingularEllipticCurve(Polynom &module, Polynom &a3, Polynom &a4, Polynom &a6);
		SuperSingularEllipticCurve(const SuperSingularEllipticCurve &eCurve);
		~SuperSingularEllipticCurve();
	//Методы акцепторы
	public:
                Polynom& setModule(const Polynom &module);
		Polynom& getA3() const;
		Polynom& getA4() const;
		Polynom& getA6() const;
		Polynom& setA3(Polynom &a3);
		Polynom& setA4(Polynom &a4);
		Polynom& setA6(Polynom &a6);
                bool isSuperSingular() const;
                bool isNonSuperSingular() const;
                Integer& getOrd(int step);
	//Унарные операции
	public:
		SuperSingularEllipticCurve& operator=(const SuperSingularEllipticCurve &eCurve);
	//Операции сравнения
	public:
                bool equals(const EllipticCurveGF2 &eCurve) const;
	//Принадлежность точки к кривой
	public:
		bool inGroup(Polynom &x, Polynom &y) const;
        //Вычисление правой части уравнения X^3 + a4*X + a6
        public:
                Polynom rightSide(Polynom &x) const;
        // Проверка на существование Y для данного X
        public:
                bool hasY(Polynom &x) const;
        };

        // абстрактный базовый класс точки эллиптических кривых над полем GF(2^n)
        class EllipticPointGF2
        {
        protected:
                EllipticCurveGF2 *_curve;
                bool _infinite;
                Polynom *_x;
		Polynom *_y;
        // виртуальный деструктор
        public:
                virtual ~EllipticPointGF2() = 0;
        //Методы акцепторы
        public:
		EllipticCurveGF2& getCurve();
                virtual EllipticCurveGF2& setCurve(EllipticCurveGF2& curve) = 0;
                Polynom& getX();
		Polynom& getY();
                EllipticPointGF2& setXY(Polynom &x, Polynom &y);
                bool isInfinite() const;
		EllipticPointGF2& setInfinite(bool infinite);

        public:
                friend bool operator==(const EllipticPointGF2 &ePoint1, const EllipticPointGF2 &ePoint2);
		friend bool operator!=(const EllipticPointGF2 &ePoint1, const EllipticPointGF2 &ePoint2);
        //Операция взятия противоположной точки (-P)
        public:
                virtual EllipticPointGF2& Negate();
                virtual EllipticPointGF2& Negate(EllipticPointGF2 &ePoint) = 0;
        //Операция сложение
        public:
                //friend EllipticPointGF2 operator+(EllipticPointGF2 &ePoint1, EllipticPointGF2 &ePoint2);
		EllipticPointGF2& operator+=(EllipticPointGF2 &ePoint);
                virtual EllipticPointGF2& Add(EllipticPointGF2 &ePoint1, EllipticPointGF2 &ePoint2) = 0;

        //Операция удвоения
	public:
		virtual EllipticPointGF2& Double();
		virtual EllipticPointGF2& Double(EllipticPointGF2 &ePoint) = 0;

	//Операция умножения на константу
	public:
		//friend EllipticPoint operator*(const EllipticPoint &ePoint, const Integer &i);
		//friend EllipticPoint operator*(const Integer &i, const EllipticPoint &ePoint);
		EllipticPointGF2& operator*=(Integer &i);
		//EllipticPoint& Mul(Integer &i, EllipticPoint &ePoint);
		virtual EllipticPointGF2& Mul(EllipticPointGF2 &ePoint, const Integer &i) = 0;
        // Генерация точки
        public:
                EllipticPointGF2& Generate();
        // Генерация точки с упаковкой данных
        public:
                EllipticPointGF2& WrappingGenerate(const Polynom & xforwrap);
        protected:
                virtual EllipticPointGF2& GenerateImpl(const Polynom * xforwrap = NULL) = 0;
        protected:
                Polynom findYOddCase(const Polynom & right); // решение уравнения Y^2 + Y = right, n = 2k+1
                Polynom findYEvenCase(const Polynom & right); // решение уравнения Y^2 + Y = right, n = 2k
                Matrix createGenerationMatrix(); // создание матрицы СЛАУ для n = 2k
        public:
                friend class SuperSingularEllipticPoint;
                friend class NonSuperSingularEllipticPoint;
        private:
                EllipticPointGF2& operator=(const EllipticPointGF2 &ePoint);// запертил автогенерацию
        public:
                AAL::PolynomGF2_m_4& DLK(EllipticPointGF2 &ePoint1,EllipticPointGF2 &ePoint2,AAL::PolynomGF2_m_4 &t,int n,AAL::PolynomGF2_m_4 &b,Polynom &mod);
        public:
                AAL::PolynomGF2_m_4& findRo(Polynom &module, AAL::PolynomGF2_m_4 &b );


        };
//***********************************************************************************************
        // класс точки "суперсингулярных" эллиптических кривых над полем GF(2^n)
        class SuperSingularEllipticPoint : public EllipticPointGF2
	{
	//Конструкторы
	public:
		SuperSingularEllipticPoint();
		SuperSingularEllipticPoint(const SuperSingularEllipticCurve &eCurve);
		SuperSingularEllipticPoint(const SuperSingularEllipticPoint &ePoint);
		~SuperSingularEllipticPoint();
        //Методы акцепторы
        public:
		SuperSingularEllipticCurve& setCurve(EllipticCurveGF2 &eCurve);

	//Унарные операции
	public:
		SuperSingularEllipticPoint& operator=(const SuperSingularEllipticPoint &ePoint);
        //Операция взятия противоположной точки (-P)
        public:
                EllipticPointGF2& Negate(); // нужно переопределить, иначе будет перекрыта
                EllipticPointGF2& Negate(EllipticPointGF2 &ePoint);
        //Операция сложение
        public:
                EllipticPointGF2& Add(EllipticPointGF2 &ePoint1, EllipticPointGF2 &ePoint2);
        //Операция удвоения
	public:
                EllipticPointGF2& Double();// нужно переопределить, иначе будет перекрыта
                EllipticPointGF2& Double(EllipticPointGF2 &e);
        //Операция умножения на константу
	public:
		EllipticPointGF2& Mul(EllipticPointGF2 &ePoint, const Integer &i);
        protected:
                SuperSingularEllipticPoint& GenerateImpl(const Polynom * xforwrap = NULL); // странно, требует ещё раз объявиьт значения по умолчанию
        };

//*******************************************************************************************************************************************************************************
        // класс "несуперсингулярных" эллиптических кривых над полем GF(2^n)
        // вид: Y^2 + X*Y = X^3 + a2*X^2 + a6
        class NonSuperSingularEllipticCurve : public EllipticCurveGF2
	{
        private:
                Polynom *_a2;
                Polynom *_a6;
	//Конструкторы
	public:
		//default: Y^2 + X*Y = X^3 + X^2 + 1 (mod m(x) = 1+x+x^3)
		NonSuperSingularEllipticCurve();
		NonSuperSingularEllipticCurve(Polynom &module, Polynom &a2, Polynom &a6);
		NonSuperSingularEllipticCurve(const NonSuperSingularEllipticCurve &eCurve);
		~NonSuperSingularEllipticCurve();
	//Методы акцепторы
	public:
                Polynom& setModule(const Polynom &module);
		Polynom& getA2() const;
		Polynom& getA6() const;
		Polynom& setA2(Polynom &a2);
		Polynom& setA6(Polynom &a6);
        bool isSuperSingular() const;
        bool isNonSuperSingular() const;
        Integer getOrder() const;
	//Унарные операции
	public:
		NonSuperSingularEllipticCurve& operator=(const NonSuperSingularEllipticCurve &eCurve);
	//Операции сравнения
	public:
                bool equals(const EllipticCurveGF2 &eCurve) const;
	//Принадлежность точки к кривой
	public:
		bool inGroup(Polynom &x, Polynom &y) const;
        //Вычисление правой части уравнения X^3 + a2*X^2 + a6
        public:
                Polynom rightSide(Polynom &x) const;
        // Проверка на существование Y для данного X
        public:
                bool hasY(Polynom &x) const;
        private:
                Polynom getInvertSquare(Polynom &x) const;
        public:
                friend class NonSuperSingularEllipticPoint;
        };
        // класс точки "несуперсингулярных" эллиптических кривых над полем GF(2^n)
        class NonSuperSingularEllipticPoint : public EllipticPointGF2
	{
        	//Конструкторы
	public:
		NonSuperSingularEllipticPoint();
		NonSuperSingularEllipticPoint(const NonSuperSingularEllipticCurve &eCurve);
		NonSuperSingularEllipticPoint(const NonSuperSingularEllipticPoint &ePoint);
		~NonSuperSingularEllipticPoint();
        //Методы акцепторы
        public:
		NonSuperSingularEllipticCurve& setCurve(EllipticCurveGF2 &eCurve);
	//Унарные операции
	public:
		NonSuperSingularEllipticPoint& operator=(const NonSuperSingularEllipticPoint &ePoint);
        //Операция взятия противоположной точки (-P)
        public:
                EllipticPointGF2& Negate(); // нужно переопределить, иначе будет перкрыта
                EllipticPointGF2& Negate(EllipticPointGF2 &ePoint);
        //Операция сложение
        public:
                EllipticPointGF2& Add(EllipticPointGF2 &ePoint1, EllipticPointGF2 &ePoint2);
        //Операция удвоения
	public:
                EllipticPointGF2& Double();// нужно переопределить, иначе будет перкрыта
                EllipticPointGF2& Double(EllipticPointGF2 &e);
        //Операция умножения на константу
	public:
		EllipticPointGF2& Mul(EllipticPointGF2 &ePoint, const Integer &i);
        protected:
                NonSuperSingularEllipticPoint& GenerateImpl(const Polynom * xforwrap = NULL); // странно, требует ещё раз объявиьт значения по умолчанию
        };
}

#endif
