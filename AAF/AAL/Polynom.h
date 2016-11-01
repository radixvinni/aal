#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "BasicType.h"
#include "Integer.h"
//#include "Matrix.h"
#include <set>

namespace AAL
{
	class Converter;
  class Matrix;
	enum PolynomSystem {BackHex=16, BackBin=2 };
	class Polynom : public BasicType<uchar>
	{
	private:
    friend class Converter;
    friend class PolynomGF3;
    friend class Matrix;
	//Êîíñòðóêòîðû
	public:
		Polynom();
		Polynom(const Polynom &polynom);
		Polynom(const std::string dataString, PolynomSystem system=BackBin);
		Polynom(const std::string dataString, bool in_degres, bool cancel = false);

	//Ïðåîáðàçîâàíèå è ñ÷èòûâàíèå èç ñòðîê
	public:
		Polynom& Parse(const std::string dataString, PolynomSystem system=BackBin, bool cancel = false);
		std::string ToString(const std::string dataString) const;
		std::string ToString(PolynomSystem system=BackBin) const;
        std::string i_to_str(uint x) const;
	//Ìåòîäû àêöåïòîðû
	public:
		Polynom& setOne();
		Polynom& setPolynom(uchar);
		Polynom& setZero();
                Polynom& setUnit(uint degree);
                std::set<uint> getPowersOfPolynom() const;
		bool isPolynom(uchar polynom) const;
		bool isNormal() const;
		bool isIrreducible() const;
    bool isPrimitivity() const;
   // Polynom& setUnit(uint degree);

	//Óíàðíûå îïåðàöèè
	public:
		Polynom operator~() const;
		Polynom& OnesComplement();
		Polynom& operator= (const Polynom& polynom);

	//Îïåðàöèè ñðàâíåíèÿ
	public:
		Polynom Compare(const Polynom& polynom) const;
		friend bool operator==(const Polynom& a, const Polynom& b);
		friend bool operator!=(const Polynom& a, const Polynom& b);
		friend bool operator<(const Polynom& a, const Polynom& b);
		friend bool operator<=(const Polynom& a, const Polynom& b);
		friend bool operator>(const Polynom& a, const Polynom& b);
		friend bool operator>=(const Polynom& a, const Polynom& b);

	//Ëîãè÷åñêèå îïåðàöèè
	private:
		Polynom* Max(Polynom &a, Polynom &b, CompareIndicator ind);
		Polynom* Min(Polynom &a, Polynom &b, CompareIndicator ind);
		void Disposal(Polynom &a, Polynom &b);
	public:
		friend Polynom operator^(const Polynom &a, const Polynom &b);
		Polynom& operator^=(Polynom &polynom);
		Polynom& Xor(Polynom &a, Polynom &b);
		friend Polynom operator|(const Polynom &a, const Polynom &b);
		Polynom& operator|=(Polynom &polynom);
		Polynom& Or(Polynom &a, const Polynom &b);
		friend Polynom operator&(const Polynom &a, const Polynom &b);
		Polynom& operator&=(Polynom &polynom);
		Polynom& And(Polynom &a, Polynom &b);
		friend Polynom operator!(const Polynom &polynom);
		Polynom& Not(Polynom &polynom);

	//Îïåðàöèè ïîáèòîâîãî ñäâèãà
	public:
		Polynom operator<<(int numberBits) const;
		Polynom& operator<<=(int numberBits);
		Polynom operator>>(int numberBits) const;
		Polynom& operator>>=(int numberBits);

	//Îïåðàöèÿ ñëîæåíèÿ
	public:
		friend Polynom operator+(const Polynom &a, const Polynom &b);
		Polynom& operator+=(Polynom &polynom);
		Polynom& Add(Polynom &a, Polynom &b);
		Polynom& ModAdd(Polynom &a, Polynom &b, Polynom &module);
    Polynom& AddInGF2_n(Polynom &a, Polynom &b, Polynom &module);
	//Îïåðàöèÿ âû÷èòàíèÿ
	public:
		friend Polynom operator-(const Polynom &a, const Polynom &b);
		Polynom& operator-=(Polynom &polynom);
		Polynom& Sub(Polynom &a, Polynom &b);
		Polynom& ModSub(Polynom &a, Polynom &b, Polynom &module);
    Polynom& SubInGF2_n(Polynom &a, Polynom &b, Polynom &module);

	//Îïåðàöèÿ óìíîæåíèÿ
	//TODO: ðåôàêòîðèíã óìíîæåíèÿ ýëåìåíòàðíûõ ìíîãîë÷ëåíîâ(ñîçäàíèå òàáëèö óìíîæåíèÿ).
	private:
		Polynom *Copy(Polynom &polynom, Polynom *polynomNotEqual = NULL);
		void DisposalCopy(Polynom &polynom, Polynom *polynomNotEqual = NULL);
        public:

                static ushort MulElemPolynoms(uchar u, uchar v);
	public:
		friend Polynom operator*(const Polynom &a, const Polynom &b);
		Polynom& operator*=(Polynom &polynom);
		Polynom& Mul(Polynom &a, Polynom &b);
		Polynom& ModMul(Polynom a, Polynom b, Polynom &module);
        Polynom& MulGF2_n(Polynom &a, Polynom &b, Polynom &module);

	//Îïåðàöèÿ äåëåíèå
	//TODO: ïðîâåñòè ðåôàêòîðèíã Div - ìîæíî ëè óáðàòü ïåðâóþ ïðîâåðêó.
	public:
		friend Polynom operator/(const Polynom &a, const Polynom &b);
		Polynom& operator/=(Polynom &polynom);
		Polynom& Div(Polynom &a, const Polynom &b, Polynom *remainder = NULL);
		Polynom& ModDiv(Polynom &a, Polynom &b, Polynom &module, Polynom *remainder = NULL);
    Polynom& DivInGF2_n(Polynom &a, Polynom &b, Polynom &module, Polynom *remainder);
	//Îïåðàöèÿ ïðèâåäåíèÿ ïî ìîäóëþ
	//TODO: ïðîâåñòè ðåôàêòîðèíã Mod - íå ñ÷èòàòü ÷àñòíîå.
	public:
		friend Polynom operator%(const Polynom &a, const Polynom &b);
		Polynom& operator%=(Polynom &polynom);
		Polynom& Mod(Polynom &a, const Polynom &b);
		Polynom& Mod(Polynom &module);
        Polynom& FastMod(Polynom &a, Polynom &b);

	//Îïåðàöèÿ âîçâåäåíèå â ñòåïåíü
	//TODO: ïðîâåñòè ðåôàêòîðèíã(ñîçäàíèå òàáëèö).
	private:
		ushort SquareElemPolynom(uchar u);
		Polynom& Square(Polynom &a, Integer &n, Polynom *module = NULL);
		Polynom& PowImpl(Polynom &a, Integer &n, Polynom *module = NULL);
	public:
		Polynom& Pow(Polynom &a, Integer &n);
		Polynom& ModPow(Polynom &a, Integer &n, Polynom &module);
   	Polynom& PowGF2_n(Polynom &a, Integer &n, Polynom &module);

	//Àëãîðèòìû Åâêëèäà
	//TODO: ðåàëèçîâàòü îáû÷íûé àëãîðèòì Åâêëèäà
        //TODO: Äîáàâèòü ìåòîäû äëÿ óìíîãî êîïèðîâàíèÿ îáúåêòîâ
        private:
       		Polynom &simpleExEuclid(Polynom &i, Polynom &x, Polynom &y);
	public:
		Polynom& Euclid(const Polynom &a, Polynom &b);
		Polynom& BinaryGCD(const Polynom &a, Polynom &b);
		Polynom& ExEuclid(Polynom &a, Polynom &b, Polynom &x, Polynom &y);

	//Ãåíåðàöèÿ ïîëèíîìîâ
	//TODO: Äîðàáîòàòü äîáàâèâ íîâûå ìåòîäû
	public:
		Polynom& Generate(uint numberBits);
		Polynom& Generate(const Polynom& module);
    Polynom& WrappingGenerate(const Polynom& forwrap, const Polynom &module);
    Polynom& GenerateIrreducible(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree);
    Polynom& GenerateIrreduciblePrimitivity(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree);
    Polynom& GenerateIrreducibleTrinomial(const uint nDegree);
		Polynom& GenerateNormal(uint numberBits);
		Polynom& GenerateNormal(const Polynom& module);
    Polynom& GenerateNormal(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree);
  // Òåîðåìà Øòèëüáåðãà-Ñóîíà
    bool SchtilbergSuonTheorem(const uint k, const uint n) const;

    std::string ToStringByPowers() const;
 //Àðèôìåòèêà â îïòèìàëüíûõ íîðìàëüíûõ áàçèñàõ
  public:
    // Òåñòû ñòåïåíåé ïîëÿ íà îáðàçîâàíèå ÎÍÁ
    // ÎÍÁ 1
    bool ONB1Test(const uint n) const;
    // ÎÍÁ 2
    bool ONB2Test(const uint n) const;
    // ÎÍÁ 3
    bool ONB3Test(const uint n) const;
    // Ãåíåðàöèè îïòèìàëüíîãî íîðìàëüíîãî áàçèñà, çàäàííîé ñòåïåíè ðàñøèðåíèÿ ïîëÿ
    // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
    // âûõîä: b - ïîëèíîì, A - òàáëèöà óìíîæåíèÿ èëè false - ÎÍÁ 1ãî òèïà íå ñóùåñòâóåò
    bool GenerateONB1(const uint n, Polynom& b, Matrix& A);
    // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
    // âûõîä: b - ïîëèíîì, A - òàáëèöà óìíîæåíèÿ èëè false - ÎÍÁ 2ãî òèïà íå ñóùåñòâóåò
    bool GenerateONB2(const uint n, Polynom& b, Matrix& A);
    // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
    // âûõîä: b - ïîëèíîì, A - òàáëèöà óìíîæåíèÿ èëè false - ÎÍÁ 3ãî òèïà íå ñóùåñòâóåò
    bool GenerateONB3(const uint n, Polynom& b, Matrix& A);
    // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
    // âûõîä: b - ïîëèíîì èëè false - ÎÍÁ 1ãî òèïà íå ñóùåñòâóåò
    bool GenerateONB1Polynom(const uint n, Polynom& b);
    // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
    // âûõîä: b - ïîëèíîì èëè false - ÎÍÁ 2ãî òèïà íå ñóùåñòâóåò
    bool GenerateONB2Polynom(const uint n, Polynom& b);
    // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
    // âûõîä: b - ïîëèíîì èëè false - ÎÍÁ 3ãî òèïà íå ñóùåñòâóåò
    bool GenerateONB3Polynom(const uint n, Polynom& b);

  //Àðèôìåòèêà â ãàóññîâûõ íîðìàëüíûõ áàçèñàõ
  public:
    // Òåñòû ñòåïåíåé ïîëÿ íà îáðàçîâàíèå ÃÍÁ
    bool GNBTest(const uint n, const int type) const;


	//Îïåðàöèè ìóëüòèïëèêàòèâíîé ãðóïïû è ïîëÿ
	public:
		bool InMulGroup(Polynom &groupModule);
		Polynom& Inverse(Polynom &module);
		Polynom& Inverse(Polynom &polynom, Polynom &module);
    Polynom& InverseGF2_n(Polynom &polynom, Polynom &module);
    Polynom& Trace(Polynom &module);
		Polynom& Trace(Polynom &polynom, Polynom &module);
    Integer elementOrder(Polynom &groupModule, Polynom &polynom,std::vector<DecompositionMember> vector, const Integer &ord );
    bool isGenerator(Polynom &groupModule, Polynom &polynom,std::vector<DecompositionMember> vector, const Integer &ord);

	};
};
#endif
