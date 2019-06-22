/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef PolynomGF7_m14H
#define PolynomGF7_m14H
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

	class PolynomGF7_m14
	{
	private:
		friend class Converter;
        public:
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

                PolynomGF7 _module;
                PolynomGF7 _modPolynom;


	//Конструкторы
	public:
		PolynomGF7_m14();
		PolynomGF7_m14(const PolynomGF7_m14 &polynom);
		PolynomGF7_m14(const std::string a0, const std::string a1, const std::string a2, const std::string a3, const std::string a4, const std::string a5, const std::string a6, const std::string a7, const std::string a8, const std::string a9, const std::string a10, const std::string a11, const std::string a12, const std::string a13, const std::string module);

	//Преобразование и считывание из сторк
	public:
       		PolynomGF7_m14& Parse(const std::string dataString);
		std::string ToString() const;
        public:
                bool isZero() const;
                bool isOne() const;
  //Унарные операции
	public:
		PolynomGF7_m14& operator= (const PolynomGF7_m14& polynom);

        //Методы акцепторы
	public:
    PolynomGF7_m14& setTwo();
    PolynomGF7_m14& setOne();
    PolynomGF7_m14& setZero();
    uint getBit(uint index) const;
    void setBit(uint index, uint bit);
        //Операции сравнения
	public:
    PolynomGF7_m14& Generate(PolynomGF7& module);
    friend bool operator==(const PolynomGF7_m14& a, const PolynomGF7_m14& b);
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
		friend PolynomGF7_m14 operator+(const PolynomGF7_m14 &a, const PolynomGF7_m14 &b);
		PolynomGF7_m14& operator+=(PolynomGF7_m14 &polynom);
		PolynomGF7_m14& Add(PolynomGF7_m14 &a, PolynomGF7_m14 &b);
        //Операция умножения
	public:
		friend PolynomGF7_m14 operator*(const PolynomGF7_m14 &a, const PolynomGF7_m14 &b);
		PolynomGF7_m14& operator*=(PolynomGF7_m14 &polynom);
		PolynomGF7_m14& Mul(PolynomGF7_m14 &a, PolynomGF7_m14 &b);

//--------------------------------------------------------------------------------
    //Операция возведение в степень
	public:
		PolynomGF7_m14& Seven(PolynomGF7_m14 &a);
		PolynomGF7_m14& SevenFast(PolynomGF7_m14 &a);
		PolynomGF7_m14& Pow(PolynomGF7_m14 &a, const Integer &n);
    //символ Лежандра
        PolynomGF7_m14& LegendreSymbol(PolynomGF7_m14 &a, PolynomGF7 &module);
    //извлечение квадратного корня
    public:
         PolynomGF7_m14& Sqrt(PolynomGF7_m14 &x, PolynomGF7_m14 &a,PolynomGF7 &module,Integer &s,Integer &T);
    //инвертирование
    public:
        PolynomGF7_m14& Inverse(PolynomGF7 &module);
        PolynomGF7_m14& Inverse(PolynomGF7_m14 &polynom, PolynomGF7 &module);

    //Тест образующего элемента
    Integer& elementOrder(PolynomGF7 &groupModule, PolynomGF7_m14 &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
    bool isGenerator(PolynomGF7 &groupModule, PolynomGF7_m14 &polynom,std::vector<DecompositionMember> vector, Integer &ord);
    public:
        PolynomGF7_m14& findRo(PolynomGF7_m14 &b ,PolynomGF7 &mod);
    public:
        PolynomGF7_m14& DLK(std::vector<PolynomGF7> vector_x,std::vector<PolynomGF7> vector_y,std::vector<PolynomGF7> vector_al,std::vector<PolynomGF7> vector_bt,PolynomGF7_m14 &ro,PolynomGF7_m14 &si,int n,PolynomGF7_m14 &b,PolynomGF7 &mod);
	int sevendiv(std::vector<Integer>* m, Integer n);
  };
};

#endif
