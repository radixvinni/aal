/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF7_m_2H
#define PolynomGF7_m_2H
//---------------------------------------------------------------------------
#include <list>
#include "BasicType.h"
#include "Integer.h"
#include "Polynom.h"
#include "PolynomGF7.h"

namespace AAL
{
	class Converter;

	class PolynomGF7_m_2
	{
	private:
		friend class Converter;
        public:
                PolynomGF7 _a0;
                PolynomGF7 _a1;
                PolynomGF7 _module;
                PolynomGF7 _modPolynom;


	//Конструкторы
	public:
		PolynomGF7_m_2();
		PolynomGF7_m_2(const PolynomGF7_m_2 &polynom);
		PolynomGF7_m_2(const std::string a0, const std::string a1, const std::string module);

	//Преобразование и считывание из сторк
	public:
       		PolynomGF7_m_2& Parse(const std::string dataString);
	 //	std::string ToString() const;
        public:
                bool isZero() const;
                bool isZero(PolynomGF7 &module) const;

                bool isOne() const;
  //Унарные операции
	public:
		PolynomGF7_m_2& operator= (const PolynomGF7_m_2& polynom);

        //Методы акцепторы
	public:
    PolynomGF7_m_2& setTwo();
    PolynomGF7_m_2& setOne();
    PolynomGF7_m_2& setZero();
    PolynomGF7_m_2& setZero(PolynomGF7 &module);

    uint getBit(uint index) const;
    void setBit(uint index, uint bit);
        //Операции сравнения
	public:
    PolynomGF7_m_2& Generate(PolynomGF7& module);
    friend bool operator==(const PolynomGF7_m_2& a, const PolynomGF7_m_2& b);

		friend PolynomGF7_m_2 operator%(const PolynomGF7_m_2 &a, const PolynomGF7 &b);
		PolynomGF7_m_2& operator%=(PolynomGF7 &polynom);
		PolynomGF7_m_2& Mod(PolynomGF7_m_2 &a, PolynomGF7 &b);

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

        const PolynomGF7& getModule() const;
        const PolynomGF7& getModPolynom() const;
        void exist(PolynomGF7& a, PolynomGF7& module);
        void setModPolynom(const PolynomGF7& modPolynom);
        void setModule(const PolynomGF7& module);
        void setByIndex(const PolynomGF7 & a, int index);
        const PolynomGF7& getByIndex(int index) const;
        int deg() const;

       //Операции побитового сдвига
       //Операция сложения
	public:
		friend PolynomGF7_m_2 operator+(const PolynomGF7_m_2 &a, const PolynomGF7_m_2 &b);
		PolynomGF7_m_2& operator+=(PolynomGF7_m_2 &polynom);
		PolynomGF7_m_2& Add(PolynomGF7_m_2 &a, PolynomGF7_m_2 &b);
        //Операция умножения
	public:
		friend PolynomGF7_m_2 operator*(const PolynomGF7_m_2 &a, const PolynomGF7_m_2 &b);
		PolynomGF7_m_2& operator*=(PolynomGF7_m_2 &polynom);
		PolynomGF7_m_2& Mul(PolynomGF7_m_2 a, PolynomGF7_m_2 b);

//--------------------------------------------------------------------------------
    //Операция возведение в степень
	public:
		PolynomGF7_m_2& Seven(PolynomGF7_m_2 &a);
		PolynomGF7_m_2& Pow(PolynomGF7_m_2 &a, const Integer &n);
    //символ Лежандра
        PolynomGF7_m_2& LegendreSymbol(PolynomGF7_m_2 &a, PolynomGF7 &module);
    //извлечение квадратного корня
    public:
         PolynomGF7_m_2& Sqrt(PolynomGF7_m_2 &a, PolynomGF7 &module,Integer &s,Integer &T);
    //инвертирование
        PolynomGF7_m_2& Inverse(PolynomGF7 &module);
        PolynomGF7_m_2& Inverse(PolynomGF7_m_2 &polynom, PolynomGF7 &module);

    //Тест образующего элемента
    Integer& elementOrder(PolynomGF7 &groupModule, PolynomGF7_m_2 &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
    bool isGenerator(PolynomGF7 &groupModule, PolynomGF7_m_2 &polynom,std::vector<DecompositionMember> vector, Integer &ord);
	int sevendiv(std::vector<Integer>* m, Integer n);
  };
};


#endif
