/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __ELLIPTICCURVESGF3_H__
#define __ELLIPTICCURVESGF3_H__

#include "PolynomGF3.h"
#include "PolynomGF3_m_6.h"
#include "PolynomGF3_mY_9.h"


namespace AAL
{       // класс эллиптических кривых над полем GF(3^n)
        // вид: Y^2 = X^3 + a2*X^2 +a4*X + a6
        class EllipticCurveGF3
	{
        private:
                PolynomGF3 *_a2;
                PolynomGF3 *_a4;
                PolynomGF3 *_a6;
                PolynomGF3 *_module;
	//Конструкторы
	public:
		//default: Y^2 = X^3 + X^2 +X + 1 (mod m(x) = 1+x+x^3)
		EllipticCurveGF3();
		EllipticCurveGF3(PolynomGF3 &module, PolynomGF3 &a2, PolynomGF3 &a4, PolynomGF3 &a6);
		EllipticCurveGF3(const EllipticCurveGF3 &eCurve);
		~EllipticCurveGF3();
	//Методы акцепторы
	public:
    PolynomGF3& setModule(PolynomGF3 &module);
    PolynomGF3& getModule() const;
		PolynomGF3& getA2() const;
		PolynomGF3& getA4() const;
		PolynomGF3& getA6() const;
		PolynomGF3& setA2(PolynomGF3 &a2);
		PolynomGF3& setA4(PolynomGF3 &a4);
		PolynomGF3& setA6(PolynomGF3 &a6);

	//Унарные операции
	public:
		EllipticCurveGF3& operator=(const EllipticCurveGF3 &eCurve);
	//Операции сравнения
	public:
    bool equals(const EllipticCurveGF3 &eCurve) const;
    friend bool operator==(const EllipticCurveGF3 &eCurve1, const EllipticCurveGF3 &eCurve2);
		friend bool operator!=(const EllipticCurveGF3 &eCurve1, const EllipticCurveGF3 &eCurve2);
	//Принадлежность точки к кривой
	public:
		bool inGroup(PolynomGF3 &x, PolynomGF3 &y) const;
        };
 //*****************************************************************************
 // класс точки эллиптических кривых над полем GF(3^n)
 class EllipticPointGF3
 {
  protected:
    EllipticCurveGF3 *_curve;
    bool _infinite;
    PolynomGF3 *_x;
    PolynomGF3 *_y;

  public:
    EllipticPointGF3();
    EllipticPointGF3(const EllipticCurveGF3 &eCurve);
    EllipticPointGF3(const EllipticPointGF3 &ePoint);
    ~EllipticPointGF3();
  //Методы акцепторы
  public:
    EllipticCurveGF3& getCurve();
    EllipticCurveGF3& setCurve(EllipticCurveGF3& curve);
    PolynomGF3& getX();
    PolynomGF3& getY();
    EllipticPointGF3& setXY(PolynomGF3 &x, PolynomGF3 &y);
    bool isInfinite() const;
    EllipticPointGF3& setInfinite(bool infinite);

  public:
    friend bool operator==(const EllipticPointGF3 &ePoint1, const EllipticPointGF3 &ePoint2);
    friend bool operator!=(const EllipticPointGF3 &ePoint1, const EllipticPointGF3 &ePoint2);

  //Операция взятия противоположной точки (-P)
  public:
    EllipticPointGF3& Negate();
    EllipticPointGF3& Negate(EllipticPointGF3 &ePoint);
  //Операция сложение
  public:
    EllipticPointGF3& operator+=(EllipticPointGF3 &ePoint);
    EllipticPointGF3& Add(EllipticPointGF3 &ePoint1, EllipticPointGF3 &ePoint2);

  //Операция удвоения
	public:
		EllipticPointGF3& Double();
		EllipticPointGF3& Double(EllipticPointGF3 &ePoint);

	//Операция умножения на константу
	public:
    EllipticPointGF3& operator*=(Integer &i);
    EllipticPointGF3& Mul(EllipticPointGF3 &ePoint,Integer &integer);

  // Генерация точки
  public:
    EllipticPointGF3& Generate();
    EllipticPointGF3& Generate(const PolynomGF3 &mes);

  //Унарные операции
  private:
    EllipticPointGF3& operator=(const EllipticPointGF3 &ePoint);// запертил автогенерацию
  public:
  AAL::PolynomGF3_m_6& DLK(EllipticPointGF3 &ePoint1,EllipticPointGF3 &ePoint2,AAL::PolynomGF3_m_6 &ro,AAL::PolynomGF3_m_6 &si,int n,AAL::PolynomGF3_m_6 &b,PolynomGF3 &mod);
  public:
  PolynomGF3_m_6& findRo(PolynomGF3 &module, PolynomGF3_m_6 &b );
  //Извлечение корня
//public:
  // EllipticPointGF3& Square1()
  };

}
#endif
