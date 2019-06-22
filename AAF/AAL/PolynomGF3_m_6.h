/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/

                                            #ifndef PolynomGF3_m_6H
#define PolynomGF3_m_6H
//---------------------------------------------------------------------------
#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include "Polynom.h"
#include "PolynomGF3.h"

#include <set>

namespace AAL
{
	class Converter;
    class Matrix;
    class Polynom;
    class PolynomGF3;
	class PolynomGF3_m_6
	{
	    private:
            PolynomGF3 _a0;
            PolynomGF3 _a1;
            PolynomGF3 _a2;
            PolynomGF3 _a3;
            PolynomGF3 _a4;
            PolynomGF3 _a5;
            PolynomGF3 _module;
            PolynomGF3 _modPolynom;
	//Конструкторы
	public:
		PolynomGF3_m_6();
		PolynomGF3_m_6(const PolynomGF3_m_6 &polynom);
		PolynomGF3_m_6(const std::string a0, const std::string a1, const std::string a2, const std::string a3, const std::string a4, const std::string a5, const std::string module);
	//Преобразование и считывание из строк
	public:
/*		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin);
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string ToString(const std::string dataString);
*/
	//Методы акцепторы
	public:
		PolynomGF3_m_6& setOne();
		    PolynomGF3_m_6& setZero();
        bool isZero() const;
        bool isOne() const;
        const PolynomGF3& getA0() const;
        const PolynomGF3& getA1() const;
        const PolynomGF3& getA2() const;
        const PolynomGF3& getA3() const;
        const PolynomGF3& getA4() const;
        const PolynomGF3& getA5() const;
        void setA0(const PolynomGF3 & a);
        void setA1(const PolynomGF3 & a);
        void setA2(const PolynomGF3 & a);
        void setA3(const PolynomGF3 & a);
        void setA4(const PolynomGF3 & a);
        void setA5(const PolynomGF3 & a);
        const PolynomGF3& getModule() const;
        const PolynomGF3& getModPolynom() const;
        void exist(PolynomGF3& a, PolynomGF3& module);
        void setModPolynom(const PolynomGF3& modPolynom);
        void setModule(const PolynomGF3& module);
        void setByIndex(const PolynomGF3 & a, int index);
        const PolynomGF3& getByIndex(int index) const;
        int deg() const;
        //Generation
        public:
        PolynomGF3_m_6& Generate(PolynomGF3& module);
	//Унарные операции
	public:
		PolynomGF3_m_6& operator= (const PolynomGF3_m_6& polynom);

	//Операции сравнения
	public:
		friend bool operator==(const PolynomGF3_m_6& a, const PolynomGF3_m_6& b);
		friend bool operator!=(const PolynomGF3_m_6& a, const PolynomGF3_m_6& b);

	//Операция сложения
	public:
		friend PolynomGF3_m_6 operator+(const PolynomGF3_m_6 &a, const PolynomGF3_m_6 &b);
		PolynomGF3_m_6& operator+=(PolynomGF3_m_6 &polynom);
		PolynomGF3_m_6& Add(PolynomGF3_m_6 &a, PolynomGF3_m_6 &b);
    //Операция умножения
	public:
		friend PolynomGF3_m_6 operator*(const PolynomGF3_m_6 &a, const PolynomGF3_m_6 &b);
		PolynomGF3_m_6& operator*=(PolynomGF3_m_6 &polynom);
		PolynomGF3_m_6& Mul(PolynomGF3_m_6 &a, const PolynomGF3_m_6 &b);
    //Операция возведение в степень
	public:
		PolynomGF3_m_6& Cube(PolynomGF3_m_6 &a);
		PolynomGF3_m_6& Pow(PolynomGF3_m_6 &a, const Integer &n);
    //символ Лежандра
        PolynomGF3_m_6& LegendreSymbol(PolynomGF3_m_6 &a, PolynomGF3 &module);
    //извлечение квадратного корня
    public:
         PolynomGF3_m_6& CubeRoot(PolynomGF3_m_6 &a, PolynomGF3 &module);
         PolynomGF3_m_6& Sqrt(PolynomGF3_m_6 &a, PolynomGF3 &module,Integer &s,Integer &T);
    //инвертирование
    public:
        PolynomGF3_m_6& Inverse(PolynomGF3 &module);
        PolynomGF3_m_6& Inverse(PolynomGF3_m_6 &polynom, PolynomGF3 &module);

    //Тест образующего элемента
    Integer& elementOrder(PolynomGF3 &groupModule, PolynomGF3_m_6 &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
    bool isGenerator(PolynomGF3 &groupModule, PolynomGF3_m_6 &polynom,std::vector<DecompositionMember> vector, Integer &ord);
    public:
        PolynomGF3_m_6& getRo(PolynomGF3_m_6 &polynom,PolynomGF3& mod);
 	};
};
#endif

