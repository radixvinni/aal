/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF7_m_14H
#define PolynomGF7_m_14H
//---------------------------------------------------------------------------
#include <list>
#include "BasicType.h"
#include "Integer.h"
#include "Polynom.h"
#include "PolynomGF7.h"
#include "PolynomGF7_m_2.h"
namespace AAL
{
	class Converter;

	class PolynomGF7_m_14
	{
	private:
		friend class Converter;
        public:
                PolynomGF7_m_2 _a0;
                PolynomGF7_m_2 _a1;
                PolynomGF7_m_2 _a2;
                PolynomGF7_m_2 _a3;
                PolynomGF7_m_2 _a4;
                PolynomGF7_m_2 _a5;
                PolynomGF7_m_2 _a6;
                PolynomGF7 _module;
                PolynomGF7 _modPolynom;


	//Конструкторы
	public:
		PolynomGF7_m_14();
		PolynomGF7_m_14(const PolynomGF7_m_14 &polynom);
		PolynomGF7_m_14(const std::string a0, const std::string a1, const std::string a2, const std::string a3, const std::string a4, const std::string a5, const std::string a6, const std::string a7, const std::string a8, const std::string a9, const std::string a10, const std::string a11, const std::string a12, const std::string a13, const std::string module);

	//Преобразование и считывание из сторк
	public:
       		PolynomGF7_m_14& Parse(const std::string dataString);
		std::string ToString() const;
        public:
                bool isZero() const;
                bool isOne() const;
  //Унарные операции
	public:
		PolynomGF7_m_14& operator= (const PolynomGF7_m_14& polynom);

        //Методы акцепторы
	public:
    PolynomGF7_m_14& setTwo();
    PolynomGF7_m_14& setOne();
    PolynomGF7_m_14& setZero();
    uint getBit(uint index) const;
    void setBit(uint index, uint bit);
        //Операции сравнения
	public:
    PolynomGF7_m_14& Generate(PolynomGF7& module);
    friend bool operator==(const PolynomGF7_m_14& a, const PolynomGF7_m_14& b);
       const PolynomGF7_m_2& getA0() const;
        const PolynomGF7_m_2& getA1() const;
        const PolynomGF7_m_2& getA2() const;
        const PolynomGF7_m_2& getA3() const;
        const PolynomGF7_m_2& getA4() const;
        const PolynomGF7_m_2& getA5() const;
        const PolynomGF7_m_2& getA6() const;


        void setA0(const PolynomGF7_m_2 & a);
        void setA1(const PolynomGF7_m_2 & a);
        void setA2(const PolynomGF7_m_2 & a);
        void setA3(const PolynomGF7_m_2 & a);
        void setA4(const PolynomGF7_m_2 & a);
        void setA5(const PolynomGF7_m_2 & a);
        void setA6(const PolynomGF7_m_2 & a);


        const PolynomGF7& getModule() const;
        const PolynomGF7& getModPolynom() const;
        void exist(PolynomGF7_m_2& a, PolynomGF7& module);
        void setModPolynom(const PolynomGF7& modPolynom);
        void setModule(const PolynomGF7& module);
        void setByIndex(const PolynomGF7_m_2 & a, int index);
        const PolynomGF7_m_2& getByIndex(int index) const;
        int deg() const;

       //Операции побитового сдвига
       //Операция сложения
	public:
		friend PolynomGF7_m_14 operator+(const PolynomGF7_m_14 &a, const PolynomGF7_m_14 &b);
		PolynomGF7_m_14& operator+=(PolynomGF7_m_14 &polynom);
		PolynomGF7_m_14& Add(PolynomGF7_m_14 &a, PolynomGF7_m_14 &b);
        //Операция умножения
	public:
		friend PolynomGF7_m_14 operator*(const PolynomGF7_m_14 &a, const PolynomGF7_m_14 &b);
		PolynomGF7_m_14& operator*=(PolynomGF7_m_14 &polynom);
		PolynomGF7_m_14& Mul(PolynomGF7_m_14 &a, PolynomGF7_m_14 &b);

//--------------------------------------------------------------------------------
    //Операция возведение в степень
	public:
		PolynomGF7_m_14& Seven(PolynomGF7_m_14 &a);
		PolynomGF7_m_14& Pow(PolynomGF7_m_14 &a, const Integer &n);
    //символ Лежандра
        PolynomGF7_m_14& LegendreSymbol(PolynomGF7_m_14 &a, PolynomGF7 &module);
    //извлечение квадратного корня
    public:
         PolynomGF7_m_14& Sqrt(PolynomGF7_m_14 &x, PolynomGF7_m_14 &a,PolynomGF7 &module,Integer &s,Integer &T);
    //инвертирование
    public:
        PolynomGF7_m_14& Inverse(PolynomGF7 &module);
        PolynomGF7_m_14& Inverse(PolynomGF7_m_14 &polynom, PolynomGF7 &module);

    //Тест образующего элемента
    Integer& elementOrder(PolynomGF7 &groupModule, PolynomGF7_m_14 &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
    bool isGenerator(PolynomGF7 &groupModule, PolynomGF7_m_14 &polynom,std::vector<DecompositionMember> vector, Integer &ord);
    public:
        PolynomGF7_m_14& getRo(PolynomGF7_m_14 &polynom,PolynomGF7& mod);
	int sevendiv(std::vector<Integer>* m, Integer n);

  };
};

#endif
