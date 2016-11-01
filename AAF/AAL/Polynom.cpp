#include "Polynom.h"
#include "Converter.h"
#include "Algorithms.h"
#include "Matrix.h"
#include "TableManager.h"
#include <stdlib.h>
#include <math.h>
#include "DecompositionManager.h"



namespace AAL
{
  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // ïðèâåäåíèå ÷èñëà ïî ìîäóëþ
  int mod(int x, int module)
  {
    if (x >= 0)
    {
      return x%module;
    }
    else
    {
      while (x < 0)
        x += module;
      return x;
    }
  }

//***********************************  Êîíñòðóêòîðû  *******************************************
	//(c) Mamontov, TEST(Polynom, EmptyConstructor)
	Polynom::Polynom() : BasicType<uchar>()
	{}
//------------------------------------------------------------------------------
	//(c) Mamontov, TEST(Polynom, CopyConstructor)
	Polynom::Polynom(const Polynom &polynom) : BasicType<uchar>(polynom)
	{}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, StringConstructor)
	Polynom::Polynom(const std::string dataString, PolynomSystem system)
	{
		SetData(0, 0);
		Parse(dataString, system);
	}
//------------------------------------------------------------------------------

        //(c) Belova, TEST(Polynom, DegreeStringConstructor)
        Polynom::Polynom(const std::string dataString, bool in_degres, bool cancel){
                if(in_degres == true) {
                        int cancelling_from_deg = cancel ? 1 : 0;
                        std::vector<int> polynom_degrees;
                        std::string result;
                        int degree_count = 0;
                        char* copy_string = new char[dataString.length()];
                        strcpy(copy_string, dataString.c_str());
                        for(char* pos=strtok(copy_string," "); pos != NULL; pos = strtok(NULL," "))
                        {
                                int a = atoi(pos);
                                polynom_degrees.push_back(a);
                                degree_count++ ;
                        }
                        if(polynom_degrees[0] == 0 ) {
                        result.push_back('1');
                        }else {
                                for(int j = 0;j < (polynom_degrees[0]-cancelling_from_deg); j++)
                                        result.push_back('0');
                                result.push_back('1');
                                }
                        for(int i = 0; i < degree_count-1; i++) {
                                int a = polynom_degrees[i];
                                int b = polynom_degrees[i+1];
                                if(b-a != 1){
                                        for(int j = 0;j < b-a-1; j++)
                                                result.push_back('0');
                                }
                                result.push_back('1');
                        }
        		SetData(0, 0);
        		Parse(result, BackBin);
                }
}
//**********************************************************************************************

//*************************  Ïðåîáðàçîâàíèå è ñ÷èòûâàíèå èç ñòîðê ******************************
	///(c) Mamontov
	Polynom& Polynom::Parse(const std::string dataString, PolynomSystem system, bool cancel)
	{
    if (system == Dec)
    {
      Polynom pl(dataString, true, cancel);
      *this = pl;
    }
    else
		  *this = Converter::ToPolynom(dataString, system);
		return *this;
	}
//------------------------------------------------------------------------------
//TEST(Polynom, getPowersString)
        std::string Polynom::ToString(const std::string dataString) const {
                        std::string result = "";
                        int degree_count = -1;
                        for(unsigned int i = 0  ; i < dataString.length(); i++)
                        {
                                degree_count++ ;
                                char string[20];
                                if(dataString[i] == '1' && i != dataString.length()-1){
                                        itoa(degree_count,string,10);
                                        //result.push_back(*string);
                                        result += std::string(string);
                                        result += " ";
                                }
                                if(i == dataString.length()-1) {
                                        itoa(degree_count,string,10);
                                        //result.push_back(*string);
                                        result += std::string(string);
                                }
                        }
         return  result;
        }

//------------------------------------------------------------------------------
	//(c) Mamontov
	std::string Polynom::ToString(PolynomSystem system) const
	{
                if(system == Dec){
                        std::string polynom_str = Converter::ToString(*this, BackBin);
                        if(polynom_str == "0")
                        {
                            polynom_str = "";
                        }
                        return  Polynom::ToString(polynom_str);
                }
		return Converter::ToString(*this, system);
	}
//**********************************************************************************************
//***************************************  Ìåòîäû àêöåïòîðû   **********************************
	//simple method
	Polynom& Polynom::setOne()
	{
		setOne_Base();
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::setPolynom(uchar polynom)
	{
		setNumber_Base(polynom);
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::setZero()
	{
		setZero_Base();
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	bool Polynom::isPolynom(uchar polynom) const
	{
		return isNumber_Base(polynom);
	}
//------------------------------------------------------------------------------
//(c) Chernysheva
Polynom& Polynom::setUnit(uint degree)
{
  for (int i = 0; i <= degree; i++)
    this->setBit(i, true);
  return *this;
}

//------------------------------------------------------------------------------

  //(c) Chernysheva, TEST(Polynom, getPowersOfPolynom)
  std::set<uint> Polynom::getPowersOfPolynom() const
  {
    std::set<uint> powers;
    uint count = this->getNumberBits();
    for (uint i = 0; i < count; ++i)
    {
      bool val = this->getBit(i);
      if (val)
        powers.insert(i);
    }
    return powers;
  }
//------------------------------------------------------------------------------

	//(c) Chernysheva, TEST(Polynom, isNormal)
  //íîðìàëüíîñòü ìíîãî÷ëåíà
	bool Polynom::isNormal() const
	{
    uint n = this->getNumberBits();
    Matrix mtA;
    generateMatrix(*this, n-1, mtA);
    return mtA.nonsignMatrix();
	}
//------------------------------------------------------------------------------

	//(c) Chernysheva, TEST(Polynom, isIrreducible)
	//íåïðèâîäèìîñòü ìíîãî÷ëåíà
	bool Polynom::isIrreducible() const
	{
    std::set<uint> powers(getPowersOfPolynom());
    if (powers.size()!=2 && powers.size() % 2 == 0)
      return false;
    if (powers.size() == 3)
    {
      // åñëè ïîëèíîì - òðåõ÷ëåí
      // â ýòîì ñëó÷àå ïðåæäå ÷åì ïðèáåãàòü ê òðóäîåìêèì ïðîâåðêàì
      // ìîæíî èñïîëüçîâàòü ïðèçíàêè ïðèâîäèìîñòè
      std::set<uint>:: iterator i = powers.begin();
      if (*i == 0)
      {
        // íóëåâàÿ ñòåïåíü åñòü
        int k = 0, n = 0;
        i++;
        k = *i;
        // ìàêñèìàëüíàÿ ñòåïåíü òðåõ÷ëåíà
        i++;
        n = *i;
        if (k%2 == 0 && n%2 == 0)
          return false;
        if ((k%3 == 1 || k%3 == 2) && (n+k)%3 == 0 && n > 2)
          return false;
        if (SchtilbergSuonTheorem(k, n))
          return false;
      }
    }
    bool useFastMod = false;
    if (powers.size() >= 2)
    {
      // äëÿ âîçìîæíîñòè èñïîëüçîâàíèå fastmod íóæíî, ÷òîáû ðàçíèöà ìåæäó ïîñëåäíèì è ïðåäïîñëåäíèì áèòîì áûëà 32
      std::set<uint>:: iterator i = powers.begin();
      int k = 0, n = 0;
      k = *i;
      i++;
      n = *i;
      i++;
      while (i != powers.end())
      {
        k = n;
        n = *i;
        i++;
      }
      if (n-k >= 32)
        useFastMod = true;
    }
    uint n = this->getNumberBits() - 1;
    Polynom q0("01"), qk = q0, plA(*this);
    bool flagNOD = true;
    for (uint k = 1; k <= n; k++)
    {
      if (useFastMod)
      {
        qk = qk*qk;
        qk = qk.FastMod(qk, plA);
      }
      else
        qk = (qk * qk) % plA;
      uint s = n/k;
      Integer integer(s);
      if (s != 1 && s < n && n%s == 0 && integer.isPrime())
      {
        if (qk == q0)
          return false;
        else
        {
          Polynom NOD, polOne("1");
          NOD.BinaryGCD(qk+q0, plA);
          if (NOD != polOne)
            return false;
          else
            flagNOD = true;
        }
      }
    }
    if (qk == q0.Mod(plA) && flagNOD)
      return true;
    else
      return false;
	}
//------------------------------------------------------------------------------

  //(c) Chernysheva, TEST(Polynom, isPrimitivity)
  //ïðèìèòèâíîñòü ìíîãî÷ëåíà
  bool Polynom::isPrimitivity() const
  {
    Polynom plCur(*this);
    if  (plCur.isIrreducible())
    {
      uint n = this->getNumberBits() - 1;
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getTwoDegreeDecomposition(n,false));
      Integer number, mersen;
      Polynom res("1");
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        if (vector.size() == 1)
          return true;
        number = i->getNumber();
        Polynom p0("01"), p1;
        mersen = (mersen.Pow(2, n) - 1)/number;
        p1.ModPow(p0, mersen, plCur);
        if (p1 == res)
          return false;
      }
      return true;
    }
    else
      return false;
  }



//**********************************************************************************************

//************************************  Óíàðíûå îïåðàöèè   *************************************
	//(c) Mamontov, TEST(Polynom, unaryOperatorOnesComplement)
	Polynom Polynom::operator~() const
	{
		Polynom result(*this);
		return result.OnesComplement();
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, OnesComplement)
	Polynom& Polynom::OnesComplement()
	{
		OnesComplement_Base();
		return *this;
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, operatorEqual)
	Polynom& Polynom::operator= (const Polynom& polynom)
	{
		Assign_Base(polynom);
		return *this;
	}
//**********************************************************************************************

//*****************************    Îïåðàöèè ñðàâíåíèÿ    ***************************************
	//(c) Mamontov, TEST(Polynom, Compare)
	Polynom Polynom::Compare(const Polynom& polynom) const
	{
		return *this - polynom;
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, Equal)
	bool operator==(const Polynom& a, const Polynom& b)
	{
		if(&a == &b || (a.isZero() && b.isZero()))
			return true;
		return a.CmpImpl(b) == Equal;
	}
//------------------------------------------------------------------------------

	//simple method
	bool operator!=(const Polynom& a, const Polynom& b)
	{
		return !(a == b);
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, Smaller)
	bool operator<(const Polynom& a, const Polynom& b)
	{
		if(a.isZero())
			return !b.isZero();
		if(b.isZero())
			return !a.isZero();

		return a.CmpImpl(b) == Smaller;
	}
//------------------------------------------------------------------------------

	//simple method
	bool operator<=(const Polynom& a, const Polynom& b)
	{
		return !(b < a);
	}
//------------------------------------------------------------------------------

	//simple method
	bool operator>(const Polynom& a, const Polynom& b)
	{
		return b < a;
	}
//------------------------------------------------------------------------------

	//simple method
	bool operator>=(const Polynom& a, const Polynom& b)
	{
		return !(a < b);
	}
//**********************************************************************************************

//********************************    Ëîãè÷åñêèå îïåðàöèè    ***********************************
	//private method
	Polynom* Polynom::Max(Polynom &a, Polynom &b, CompareIndicator ind)
	{
		Polynom* max = (ind == Bigger) ? &a : &b;
		if(this == max)
			max = new Polynom(*this);
		return max;
	}
//------------------------------------------------------------------------------

	//private method
	Polynom* Polynom::Min(Polynom &a, Polynom &b, CompareIndicator ind)
	{
		Polynom* min = (ind == Bigger) ? &b : &a;
		if(this == min)
			min = new Polynom(*this);
		return min;
	}
//------------------------------------------------------------------------------

	//private method
	void Polynom::Disposal(Polynom &a, Polynom &b)
	{
		if(this != &a && this != &b)
			delete this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom operator^(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.Xor(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator^=(Polynom &polynom)
	{
		return this->Xor(*this, polynom);
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, Xor)
	Polynom& Polynom::Xor(Polynom &a, Polynom &b)
	{
		Xor_Base(a, b);
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom operator|(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.Or(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator|=(Polynom &polynom)
	{
		return this->Or(*this, polynom);
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, Or)
	Polynom& Polynom::Or(Polynom &a, const Polynom &b)
	{
		Polynom copy_b=Polynom(b);
		Or_Base(a, copy_b);
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom operator&(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.And(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator&=(Polynom &polynom)
	{
		return this->And(*this, polynom);
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, And)
	Polynom& Polynom::And(Polynom &a, Polynom &b)
	{
		And_Base(a, b);
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom operator!(const Polynom &polynom)
	{
		Polynom copy_polynom(polynom), result;
		return result.Not(copy_polynom);
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, Not)
	Polynom& Polynom::Not(Polynom &polynom)
	{
		Not_Base(polynom);
		return *this;
	}
//**********************************************************************************************

//***************************    Îïåðàöèè ïîáèòîâîãî ñäâèãà    *********************************
	//simple method
	Polynom Polynom::operator<<(int numberBits) const
	{
		Polynom result(*this);
		return result<<=numberBits;
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, SHL)
	Polynom& Polynom::operator<<=(int numberBits)
	{
		LeftShift_Base(numberBits);
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom Polynom::operator>>(int numberBits) const
	{
		Polynom result(*this);
		return result>>=numberBits;
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, SHR)
	Polynom& Polynom::operator>>=(int numberBits)
	{
		RightShift_Base(numberBits);
		return *this;
	}
//**********************************************************************************************

//******************************    Îïåðàöèÿ ñëîæåíèÿ    ***************************************
	//simple method
	Polynom operator+(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.Add(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator+=(Polynom &polynom)
	{
		return Add(*this, polynom);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::Add(Polynom &a, Polynom &b)
	{
		return Xor(a, b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::ModAdd(Polynom &a, Polynom &b, Polynom &module)
	{
		Polynom copy_a(a), copy_b(b);
		return Add(copy_a, copy_b) %= module;
	}
  Polynom& Polynom::AddInGF2_n(Polynom &a, Polynom &b, Polynom &module)
	{
                if(!module.isIrreducible())
                {
                        throw new AAL::Exception("Ïîëèíîì íå ÿâëÿåòñÿ íåïðèâîäèìûì.");
                }

                return ModAdd(a,b,module);
	}

//**********************************************************************************************

//******************************    Îïåðàöèÿ âû÷èòàíèÿ    **************************************
	//simple method
	Polynom operator-(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.Sub(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator-=(Polynom &polynom)
	{
		return Sub(*this, polynom);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::Sub(Polynom &a, Polynom &b)
	{
		return Xor(a, b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::ModSub(Polynom &a, Polynom &b, Polynom &module)
	{
		Polynom copy_a(a), copy_b(b);
		return Sub(copy_a, copy_b) %= module;
	}
  Polynom& Polynom::SubInGF2_n(Polynom &a, Polynom &b, Polynom &module)
	{
    if(module.isIrreducible())
    {
		  Polynom copy_a(a), copy_b(b);
		  return Sub(copy_a, copy_b) %= module;
    }
    else
     throw new AAL::Exception("Ïîëèíîì íå ÿâëÿåòñÿ íåïðèâîäèìûì.");
	}

//**********************************************************************************************

//******************************    Îïåðàöèÿ óìíîæåíèÿ    **************************************
	//private method
	Polynom* Polynom::Copy(Polynom &polynom, Polynom *polynomNotEqual)
	{
		return (this == &polynom || polynomNotEqual == &polynom) ? new Polynom(polynom) : &polynom;
	}
//------------------------------------------------------------------------------

	//private method
	void Polynom::DisposalCopy(Polynom &polynom, Polynom *polynomNotEqual)
	{
		if(this != &polynom && this != polynomNotEqual)
			delete this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom operator*(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.Mul(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator*=(Polynom &polynom)
	{
		return Mul(*this, polynom);
	}
//------------------------------------------------------------------------------

	// (c) Morozov, TEST(Polynom, Mul)
	Polynom& Polynom::Mul(Polynom &a, Polynom &b)
	{
		if(a.isZero() || b.isZero())
			return setZero();
		Polynom *aa = Copy(a), *bb =Copy(b);
		ushort cur_mul;

		setNumberDigits(aa->_numberDigits + bb->_numberDigits);
		std::memset(_digits, 0, getDigitSizeInBytes()*_numberDigits);

		for(uint j=0; j<aa->_numberDigits; j++)
		{
			for(uint i = 0; i<bb->_numberDigits;i++)
			{
				cur_mul = MulElemPolynoms(aa->_digits[j],bb->_digits[i]);
				_digits[i+j] ^= (uchar)(cur_mul % 256);
				_digits[i+j+1] ^= (uchar)(cur_mul >> 8);
			}
		}

		RemoveElderNulls();
		aa->DisposalCopy(a);
		bb->DisposalCopy(b);

		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::ModMul(Polynom a, Polynom b, Polynom &module)
	{
		Polynom copy_a(a), copy_b(b);
		//return Mul(copy_a, copy_b) %= module;
        return FastMod(Mul(copy_a, copy_b), module);
	}
  Polynom& Polynom::MulGF2_n(Polynom &a, Polynom &b, Polynom &module)
	{
                if(!module.isIrreducible())
                {
                        throw new AAL::Exception("Ïîëèíîì íå ÿâëÿåòñÿ íåïðèâîäèìûì.");
                }

                return ModMul(a, b, module);
	}

//------------------------------------------------------------------------------

	ushort Polynom::MulElemPolynoms(uchar u, uchar v)
	{
                return TableManager::Instance().getElementaryPolynomsMultiplication(u, v);
	}
//**********************************************************************************************

//******************************    Îïåðàöèÿ äåëåíèÿ    ****************************************
	//simple method
	Polynom operator/(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.Div(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator/=(Polynom &polynom)
	{
		return Div(*this, polynom);
	}
//------------------------------------------------------------------------------

	// (c) Morozov, TEST(Polynom, Div)
	// êëàññè÷åñêèé àëãîðèòì äåëåíèÿ
	Polynom& Polynom::Div(Polynom &a, const Polynom &b, Polynom *remainder)
	{
		if(this == remainder)
			throw new AAL::Exception("×àñòíîå è îñòàòîê íå ìîãóò áûòü îäíèì ïîëèíîìîì");
		if(b.isZero())
			throw new AAL::Exception("Äåëåíèå íà íîëü");

		CompareIndicator compare = a.CmpImpl(b);

		if(compare == Equal)
		{
			if(remainder != NULL)
				remainder->setZero();
			return setOne();
		}

		Polynom copy_a(a), copy_b(b);

		uint p = copy_a.getNumberBits();
		uint t = copy_b.getNumberBits();

		if(a.isZero() || (p < t))
		{
			if(remainder != NULL)
				*remainder = a;
			return setZero();
		}

		setNumberDigits((p-t+1)/getDigitSizeInBits() + (((p-t+1)%getDigitSizeInBits() == 0)?0:1));
		std::memset(_digits, 0, getDigitSizeInBytes()*_numberDigits);
		copy_b <<= (p-t);

		if(copy_a.getBit(p-1))// Ïî èäåå ìîæíî îò íåãî èçáàâèòüñÿ, ò.ê. ñòàðøèé áèò âñåãäà 1???
		{
			setBit(0,true);
			copy_a += copy_b;
		}
		for(uint i=0; i<(p-t);i++)
		{
			copy_a.setBit(p-1,false);// äëÿ òîãî ÷òîáû íå áûëî ñìåùåíèÿ 1.
			copy_a <<= 1;
			*this <<= 1;
			if(copy_a.getBit(p-1))
			{
				setBit(0,true);
				copy_a += copy_b;
			}
		}
		if(remainder != NULL)
		{
			copy_a.RemoveElderNulls();
			*remainder = copy_a >> (p-t);
		}
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::DivInGF2_n(Polynom &a, Polynom &b, Polynom &module, Polynom *remainder)
	{
                if(!module.isIrreducible())
                {
                        throw new AAL::Exception("f(X) íå ÿâëÿåòñÿ íåïðèâîäèìûì.");
                }

                return ModDiv(a, b, module, remainder);

	}
  Polynom& Polynom::ModDiv(Polynom &a, Polynom &b, Polynom &module, Polynom *remainder)
	{ if(Euclid(a,module).isOne() && Euclid(b,module).isOne())
		{  Polynom copy_a(a), copy_b(b);
		  Div(copy_a, copy_b, remainder) %= module;
		  if(remainder != NULL)
			  *remainder %= module;
		  return *this;
    }
    else
      throw new AAL::Exception("A1  è À2 äîëæíû áûòü âçàèìíî ïðîñòû ñ f(X).");
	}

//**********************************************************************************************

//***************************    Îïåðàöèÿ ïðèâåäåíèÿ ïî ìîäóëþ    ******************************
	//simple method
	Polynom operator%(const Polynom &a, const Polynom &b)
	{
		Polynom result, copy_a(a), copy_b(b);
		return result.Mod(copy_a, copy_b);
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::operator%=(Polynom &polynom)
	{
		return Mod(*this, polynom);
	}
//------------------------------------------------------------------------------

	//(c) Morozov, TEST(Polynom, Mod)
	Polynom& Polynom::Mod(Polynom &a, const Polynom &b)
	{
		//TODO: äîäóìàòü, îïòèìèçèðîâàòü, ò.ê. ìîæíî íå ñ÷èòàòü ÷àñòíîå.
		Polynom div;
		div.Div(a,b,this);
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::Mod(Polynom &module)
	{
		*this %= module;
		return *this;
	}
//--------------------------------------------------------------------------------
//(c) Mamontov, TEST(Polynom, Mod)
	Polynom& Polynom::FastMod(Polynom &a, Polynom &b)
	{	//error with: a=101001, b=11
                return Mod(a,b);
		int lengthA;
                int lengthB;
                lengthA = a.getNumberBits()-1;
                lengthB = b.getNumberBits()-1;
                if(lengthA<lengthB)
                 *this=a;
                else
                {
                Polynom copy_a(a), copy_b(b);
                Polynom result;
                Polynom Word("0");

                uint *Positions;
                uint AmountOfTrueBits=0;
                uint LengthOfWord=1;
                int i;
                int k;
                int j;
                int shift;

               i=lengthB-1;
               do
                 {
                  if( copy_b.getBit(i)==false)
                     LengthOfWord+=1;
                  i--;
                 }
                 while ((copy_b.getBit(i)==false) ||(i<0));

                i=lengthB;
                do
                 {
                  if( copy_b.getBit(i)==true)
                     AmountOfTrueBits+=1;
                  i--;
                 }
                 while (i!=-1);
               Positions=new uint[AmountOfTrueBits];
               i=lengthB;
               j=0;

               do
                 {
                  if( copy_b.getBit(i)==true)
                     {
                      Positions[j]=i;
                      j++;
                     }
                  i--;
                 }
                 while (i!=-1);

               do
               {

                if (lengthA-lengthB+1<LengthOfWord)
                 LengthOfWord=lengthA-lengthB+1;
                i=lengthB;
                 Word=copy_a>>(lengthA-LengthOfWord+1);

                 i=lengthB;
                 j=lengthA;

                 for (int l=0;l<AmountOfTrueBits;l++)
                 {
                  i=Positions[l];
                  j=i+lengthA-lengthB;
                  copy_a=copy_a-(Word<<j-LengthOfWord+1);
                  }
                lengthA = copy_a.getNumberBits()-1;
                 }
                while(lengthA>=lengthB);
                *this=copy_a;
                delete (Positions);
              }
		return *this;

	}
//**********************************************************************************************

//***************************    Îïåðàöèÿ âîçâåäåíèå â ñòåïåíü    ******************************
	//private method
	// ïðîñòîé ìåòîä âîçâåäåíèÿ â ñòåïåíü 2 ïî ìîäóëþ
	Polynom& Polynom::Square(Polynom &a, Integer &n, Polynom *module)
	{
		if(n.isNegative())
			throw new AAL::Exception("Ñòåïåíü íå ìîæåò áûòü îòðèöàòåëüíîé");

		if(n.isZero())
		{
			*this = a;
			return *this;
		}

		Polynom cur_pol(a);

		for(Integer k(0);k < n;k++)
		{
			setNumberDigits(cur_pol.getNumberDigits()*2);
			for(uint i = 0;i < cur_pol.getNumberDigits();i++)
			{
				ushort cur_square = cur_pol.SquareElemPolynom(cur_pol.getDigit(i));
				_digits[2*i] = (uchar)(cur_square % 256);
				_digits[2*i+1] = (uchar)(cur_square >> 8);
			}
			if(module != NULL)
                 *this = FastMod(*this, *module);
 //			   	*this %= *module;
			cur_pol = *this;
			RemoveElderNulls();
		}
		return *this;
	}
//------------------------------------------------------------------------------

	Polynom& Polynom::PowImpl(Polynom &a, Integer &n, Polynom *module)
	{
		if(n.isNegative())
			throw new AAL::Exception("Ñòåïåíü íå ìîæåò áûòü îòðèöàòåëüíîé");

		if(n.isZero())
			return setOne();

		if(a.isZero())
			return setZero();

		Polynom *aa = Copy(a);

		setOne();
		uint s = n.getNumberBits();

                Integer one(1);
                for(uint i=0;i<s;i++)
		{
			if(module == NULL)
			{
				Square(*this,one);
				if(n.getBit(s-1-i))
					Mul(*this, *aa);
			}
			else
			{
                //int tt = module->getNumberBits();
				Square(*this,one, module);
				if(n.getBit(s-1-i))
					ModMul(*this, *aa, *module);
			}
		}
		aa->DisposalCopy(a);

		return *this;
	}
//------------------------------------------------------------------------------

	//(c) Morozov, TEST(Polynom, Pow)
	Polynom& Polynom::Pow(Polynom &a, Integer &n)
	{
		return PowImpl(a, n);
	}
//------------------------------------------------------------------------------

	//(c) Morozov, TEST(Polynom, ModPow)
	Polynom& Polynom::ModPow(Polynom &a, Integer &n, Polynom &module)
	{
		return PowImpl(a, n, &module);
	}
	Polynom& Polynom::PowGF2_n(Polynom &a, Integer &n, Polynom &module)
	{
                if(!module.isIrreducible())
                {
                        throw new AAL::Exception("f(X) íå ÿâëÿåòñÿ íåïðèâîäèìûì.");
                }

                return ModPow(a, n, module);
	}

	ushort Polynom::SquareElemPolynom(uchar u)
	{
		ushort square = 0;
		uchar mask = 1;

		for(uint i = 0;i < 8;i++)
		{
                        if((u%2) == 1)
                        {
                               square += mask*mask;
                        }
			u >>= 1;
			mask <<= 1;
		}
                return square;
	}
//**********************************************************************************************

//********************************   Àëãîðèòìû Åâêëèäà   ***************************************
        //(c) Shilkin, TEST(Polynom, Euclid)
	Polynom& Polynom::Euclid(const Polynom &a, Polynom &b)
	{
                Polynom result = SimpleEuclid(a,b);
                *this = result;
		return *this;
	}
//------------------------------------------------------------------------------

	//(c) Morozov, TEST(Polynom, BinaryGCD)
	Polynom& Polynom::BinaryGCD(const Polynom &a, Polynom &b)
	{
		return this->Euclid(a, b);
	}
//------------------------------------------------------------------------------

        //private method
	Polynom& Polynom::simpleExEuclid(Polynom &i, Polynom &x, Polynom &y)
	{
		x.setZero();
		y.setOne();
		*this = i;
		return *this;
	}
//------------------------------------------------------------------------------

	//(c) Morozov, TEST(Polynom, ExEuclid)
	Polynom& Polynom::ExEuclid(Polynom &a, Polynom &b, Polynom &x, Polynom &y)
	{
		if(this == &x || this == &y || &x == &y)
			throw new AAL::Exception("ÍÎÄ(a,b) è ïîëèíîìû x è y òàêèå, ÷òî ax+by=ÍÎÄ(a,b) íå ìîãóò ñîâïàäàòü");
		if(a.isZero() && b.isZero())
			throw new AAL::Exception("a è b íå ìîãóò áûòü îáà ðàâíû 0");

		if(a.isZero())
			return simpleExEuclid(b, x, y);
		if(b.isZero())
			return simpleExEuclid(a, y, x);
		CompareIndicator compare = a.CmpImpl(b);
		if(compare == Equal)
			return simpleExEuclid(a, y, x);
		if(a.getNumberBits() < b.getNumberBits())
			return ExEuclid(b, a, y, x);

                Polynom u(a), v(b);
                Polynom c1, c2("1"), d1("1"), d2;
                Polynom q, r;
                Polynom prom;
                while(!v.isZero())
                {
                        r.Mod(u,v);
                        q.Div(prom.Add(u,r),v);
                        x.Add(c2,prom.Mul(q,c1));
                        y.Add(d2,prom.Mul(q,d1));
                        u = v;
                        v = r;
                        c2 = c1;
                        c1 = x;
                        d2 = d1;
                        d1 = y;
                }
                x = c2;
                y = d2;
                *this = u;

		return *this;
	}
//**********************************************************************************************

//*******************************   Ãåíåðàöèÿ ïîëèíîìîâ   **************************************
	//simple method
	//(c) Morozov
  // ãåíåðèðóåòñÿ ìíîãî÷ëåí ñ ñòàðøèì áèòîì <= numberBits
	Polynom& Polynom::Generate(uint numberBits)
	{
                if(!numberBits)
			_numberDigits = 0;
		else
		{
			uint upperBit = numberBits % getDigitSizeInBits();
			setNumberDigits(numberBits / getDigitSizeInBits() + (upperBit != 0));

			for(uint i=0; i<_numberDigits; i++)
				_digits[i] = ((rand() % 2)<<(getDigitSizeInBits()-1)) + (rand()<<(getDigitSizeInBits()/2)) + ((rand() % 2)<<(getDigitSizeInBits()/2 - 1)) + rand();

			int shift = (upperBit!=0)? getDigitSizeInBits()-upperBit : 0;
			_digits[_numberDigits-1] &= 0xFF>>shift;
			//_digits[_numberDigits-1] |= 0x80>>shift; // óñòàíîâëåíèå áèòà (numberBits - 1) â 1
		}
                RemoveElderNulls();
		return *this;
	}
//------------------------------------------------------------------------------

	//simple method
	//(c) Morozov
	Polynom& Polynom::Generate(const Polynom& module)
	{
		Generate(module.getNumberBits()-1);
		return *this;
	}
//------------------------------------------------------------------------------

	//(c) Morozov TEST(Polynom, WrappingGenerate)
        Polynom& Polynom::WrappingGenerate(const Polynom& forwrap, const Polynom &module)
        {
                if(forwrap.getNumberBits() >= module.getNumberBits())
                        throw new AAL::Exception("Â ðàçìåùàåìîé èíôîðìàöèè äîëæíî áûòü ìåíüøå áèòîâ ÷åì â ìîäóëå");

                Generate(module);

                *this >>= forwrap.getNumberBits();
                *this <<= forwrap.getNumberBits();
                this->Or(*this, (forwrap));
                return *this;
        }
//------------------------------------------------------------------------------

  //(c) Chernysheva, TEST(Polynom, GenerateIrreducible)
	// ãåíåðàöèÿ íåïðèâîäèìîãî ìíîãî÷ëåíà
  // nMinNumberBits - ìèíèìàëüíîå ÷èñëî 1 (ä.á. >= 3)
  // nMaxNumberBits - ìàêñèìàëüíîå ÷èñëî 1 (ä.á. nMaxNumberBits >= nMinNumberBits)
  // nDegree - ñòåïåíü ìíîãî÷ëåíà (ä.á. nDegree >= nMaxNumberBits-1)
  Polynom& Polynom::GenerateIrreducible(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree)
  {
    if (nMaxNumberBits < nMinNumberBits)
      throw new AAL::Exception("Ìèíèìàëüíîå ÷èñëî 1 â ïîëèíîìå áîëüøå ìàêñèìàëüíîãî");
    if (nMinNumberBits < 3)
      throw new AAL::Exception("Ìèíèìàëüíîå ÷èñëî 1 â ïîëèíîìå ìåíüøå 3");
    if (nDegree < nMaxNumberBits-1)
      throw new AAL::Exception("Ñòåïåíü ïîëèíîìà ìåíüøå ìàêñèìàëüíîãî ÷èñëà 1");

    Polynom plGen("1");
    plGen.setBit(nDegree, true);
    bool isGen = false;
    if (nMaxNumberBits >= 3)
    {
      bool isTrinominal = false;
      if (nMinNumberBits == 3)
      {
        try
        {
          Polynom plCur;
          plCur.GenerateIrreducibleTrinomial(nDegree);
          isGen = true;
          isTrinominal = true;
          *this = plCur;
        }
        catch(Exception *E)
        {
          // åñëè íå óäàëîñü ñãåíåðèðîâàòü òðåõ÷ëåí, òî ñðàçó çàäàåì óñëîâèÿ äëÿ ãåíåðàöèè ïÿòè÷ëåíà
          isTrinominal = false;
          nMinNumberBits = 5;
        }
      }
      if (nMinNumberBits > 3 || !isTrinominal)
      {
        // êîëè÷åñòâî çàíÿòûõ åäèíè÷åê
        uint CurOne = 2;
        // êîëè÷åñòâî ðàññòàâëÿåìûõ åäèíèö îò nMinNumberBits äî nMaxNumberBits
        uint FreeOne = nMinNumberBits - 2;
        while (CurOne + FreeOne <= nMaxNumberBits)
        {
          Polynom plCur(plGen);
          for (uint i = 1; i < FreeOne + 1; ++i)
            plCur.setBit(i, true);
          if (plCur.isIrreducible())
          {
            // ìíîãî÷ëåí íåïðèâîäèì
            isGen = true;
            *this = plCur;
            break;
          }
          else
          {
            Polynom plEndCicle(plGen);
            for (uint i = nDegree - 1; i >= nDegree - FreeOne; --i)
              plEndCicle.setBit(i, true);
            while (plCur != plEndCicle && !isGen)
            {
              bool bit = plCur.getBit(1);
              if (bit)
              {
                // òåêóùàÿ ïîçèöèÿ êóðñîðà â ïîëèíîìå
                uint pos = 2;
                // ïåðåìåùàåìñÿ äî ïåðâîãî 0 â ïîëèíîìå
                while (plCur.getBit(pos))
                  pos++;
                // ïåðåíîñèì 1 íà îäíó ïîçèöèþ âïåðåä
                plCur.setBit(pos, true);
                plCur.setBit(pos - 1, false);
                if (plCur.isIrreducible())
                {
                  // ìíîãî÷ëåí íåïðèâîäèì
                  isGen = true;
                  *this = plCur;
                  break;
                }
              }
              else
              {
                // òåêóùàÿ ïîçèöèÿ êóðñîðà â ïîëèíîìå
                uint pos = 2;
                // ñ÷åò÷èê 1
                uint numOne = 0;
                // ïåðåìåùàåìñÿ äî ïåðâîé 1
                while (!plCur.getBit(pos))
                  pos++;
                // ïåðåìåùàåìñÿ äî ïåðâîãî 0
                while (plCur.getBit(pos))
                {
                  pos++;
                  numOne++;
                }
                // ïåðåíîñèì 1 íà îäíó ïîçèöèþ âïåðåä
                plCur.setBit(pos, true);
                plCur.setBit(pos - 1, false);
                numOne -= 1;
                // â ñîîòâåòñòâèè ñ ïîêàçàíèÿìè ñ÷åò÷èêà, èçìåíèì îñòàâøóþñÿ ÷àñòü ïîëèíîìà
                if (numOne > 0)
                {
                  for (uint i = 1; i < numOne + 1; ++i)
                    plCur.setBit(i, true);
                  for (uint i = numOne + 1; i < pos; ++i)
                    plCur.setBit(i, false);
                  // ïðîâåðêà óñëîâèÿ
                  if (plCur.isIrreducible())
                  {
                    // ìíîãî÷ëåí íåïðèâîäèì
                    isGen = true;
                    *this = plCur;
                    break;
                  }
                }
                if (numOne == 0)
                {
                  // ïðîâåðêà óñëîâèÿ
                  if (plCur.isIrreducible())
                  {
                    // ìíîãî÷ëåí íåïðèâîäèì
                    isGen = true;
                    *this = plCur;
                    break;
                  }
                }
              }
            }
          }
          if (!isGen)
            FreeOne++;
          else
            break;
        }
      }
    }
    if (!isGen)
      throw new AAL::Exception("Íå óäàëîñü ñãåíåðèðîâàòü ìíîãî÷ëåí ñ äàííûìè ïàðàìåòðàìè");
    else
      return *this;
  }
//------------------------------------------------------------------------------

  // (c) Chernysheva, TEST(Polynom, GenerateIrreduciblePrimitivity)
  // Ãåíåðàöèÿ íåïðèâîäèìîãî ïðèìèòèâíîãî ìíîãî÷ëåíà
  Polynom& Polynom::GenerateIrreduciblePrimitivity(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree)
  {
    if (nMaxNumberBits < nMinNumberBits)
      throw new AAL::Exception("Ìèíèìàëüíîå ÷èñëî 1 â ïîëèíîìå áîëüøå ìàêñèìàëüíîãî");
    if (nMinNumberBits < 3)
      throw new AAL::Exception("Ìèíèìàëüíîå ÷èñëî 1 â ïîëèíîìå ìåíüøå 3");
    if (nDegree < nMaxNumberBits-1)
      throw new AAL::Exception("Ñòåïåíü ïîëèíîìà ìåíüøå ìàêñèìàëüíîãî ÷èñëà 1");

    Polynom plGen("1");
    plGen.setBit(nDegree, true);
    bool isGen = false;
    if (nMaxNumberBits >= 3)
    {
      // êîëè÷åñòâî çàíÿòûõ åäèíè÷åê
      uint CurOne = 2;
      // êîëè÷åñòâî ðàññòàâëÿåìûõ åäèíèö îò nMinNumberBits äî nMaxNumberBits
      uint FreeOne = nMinNumberBits - 2;
      while (CurOne + FreeOne <= nMaxNumberBits)
      {
        Polynom plCur(plGen);
        for (uint i = 1; i < FreeOne + 1; ++i)
          plCur.setBit(i, true);
        if (plCur.isIrreducible() && plCur.isPrimitivity())
        {
          // ìíîãî÷ëåí íåïðèâîäèì è ïðèìèòèâåí
          isGen = true;
          *this = plCur;
           break;
        }
        else
        {
          Polynom plEndCicle(plGen);
          for (uint i = nDegree - 1; i >= nDegree - FreeOne; --i)
            plEndCicle.setBit(i, true);
          while (plCur != plEndCicle && !isGen)
          {
            bool bit = plCur.getBit(1);
            if (bit)
            {
              // òåêóùàÿ ïîçèöèÿ êóðñîðà â ïîëèíîìå
              uint pos = 2;
              // ïåðåìåùàåìñÿ äî ïåðâîãî 0 â ïîëèíîìå
              while (plCur.getBit(pos))
                pos++;
              // ïåðåíîñèì 1 íà îäíó ïîçèöèþ âïåðåä
              plCur.setBit(pos, true);
              plCur.setBit(pos - 1, false);
              if (plCur.isIrreducible() && plCur.isPrimitivity())
              {
                // ìíîãî÷ëåí íåïðèâîäèì è ïðèìèòèâåí
                isGen = true;
                *this = plCur;
                break;
              }
            }
            else
            {
              // òåêóùàÿ ïîçèöèÿ êóðñîðà â ïîëèíîìå
              uint pos = 2;
              // ñ÷åò÷èê 1
              uint numOne = 0;
              // ïåðåìåùàåìñÿ äî ïåðâîé 1
              while (!plCur.getBit(pos))
                pos++;
              // ïåðåìåùàåìñÿ äî ïåðâîãî 0
              while (plCur.getBit(pos))
              {
                pos++;
                numOne++;
              }
              // ïåðåíîñèì 1 íà îäíó ïîçèöèþ âïåðåä
              plCur.setBit(pos, true);
              plCur.setBit(pos - 1, false);
              numOne -= 1;
              // â ñîîòâåòñòâèè ñ ïîêàçàíèÿìè ñ÷åò÷èêà, èçìåíèì îñòàâøóþñÿ ÷àñòü ïîëèíîìà
              if (numOne > 0)
              {
                for (uint i = 1; i < numOne + 1; ++i)
                  plCur.setBit(i, true);
                for (uint i = numOne + 1; i < pos; ++i)
                  plCur.setBit(i, false);
                // ïðîâåðêà óñëîâèÿ
                if (plCur.isIrreducible() && plCur.isPrimitivity())
                {
                  // ìíîãî÷ëåí íåïðèâîäèì è ïðèìèòèâåí
                  isGen = true;
                  *this = plCur;
                  break;
                }
              }
              if (numOne == 0)
              {
                // ïðîâåðêà óñëîâèÿ
                if (plCur.isIrreducible() && plCur.isPrimitivity())
                {
                  // ìíîãî÷ëåí íåïðèâîäèì è ïðèìèòèâåí
                  isGen = true;
                  *this = plCur;
                  break;
                }
              }
            }
          }
        }
        if (!isGen)
          FreeOne++;
        else
          break;
      }
    }
    if (!isGen)
      throw new AAL::Exception("Íå óäàëîñü ñãåíåðèðîâàòü ìíîãî÷ëåí ñ äàííûìè ïàðàìåòðàìè");
    else
      return *this;
  }
//------------------------------------------------------------------------------

    // (c) Chernysheva, TEST(Polynom, GenerateIrreducibleTrinomial)
  // Ãåíåðàöèÿ íåïðèâîäèìîãî òðåõ÷ëåíà
  Polynom& Polynom::GenerateIrreducibleTrinomial(const uint nDegree)
  {
    Polynom plGen("1"), plCur;
    plGen.setBit(nDegree, true);
    bool flag = false;
    uint k = 1;
    while ((nDegree%2 == 0 && k < nDegree/2 && !flag && nDegree > 2) ||
           (nDegree%2 != 0 && k <= nDegree/2 && !flag && nDegree > 2) ||
           (nDegree == 2 && !flag && k < nDegree))
    {
      bool Ben_Or = false; // ðåçóëüòàò îòñåèâàíèÿ
      if ((k%3 == 1 || k%3 == 2) && (nDegree+k)%3 == 0 && nDegree > 2)
        Ben_Or = true;
      bool chet = false; // îòñåèâàíèå ïî ÷åòíîñòè
      if (k%2 == 0 && nDegree%2 == 0)
        chet = true;
      if (!SchtilbergSuonTheorem(k, nDegree) && !Ben_Or && !chet)
      {
        plCur = plGen;
        plCur.setBit(k, true);
        Polynom q0("01"), qi = q0;
        bool flagNOD = true, curFlag = true;
        for (uint i = 1; i <= nDegree; i++)
        {
          if (nDegree >= 64)
          {
            qi = qi*qi;
            qi = qi.FastMod(qi, plCur);
          }
          else
            qi = (qi * qi) % plCur;
          uint s = nDegree/i;
          Integer integer(s);
          if (s != 1 && s < nDegree && nDegree%s == 0 && nDegree%i == 0 && integer.isPrime())
          {
            if (qi == q0)
              curFlag = false;
            else
            {
              Polynom NOD, polOne("1");
              NOD.BinaryGCD(qi+q0, plCur);
              if (NOD != polOne)
                curFlag = false;
              else
                flagNOD = true;
            }
          }
        }
        if (qi == q0 && flagNOD && curFlag)
          flag = true;
        else
          flag = false;
      }
      if (nDegree%2 != 0)
        k++;
      else
        k = k + 2;
    }
    if (flag)
    {
      *this = plCur;
      return *this;
    }
    else
      throw new AAL::Exception("Íå óäàëîñü ñãåíåðèðîâàòü íåïðèâîäèìûé òðåõ÷ëåí äàííîé ñòåïåíè");
  }
//------------------------------------------------------------------------------


	//(c) Mamontov, TEST(Polynom, GenerateNormal)
	//(c) Mamontov: ïîêà çàãëóøêà
	//TODO: ðåàëèçîâàòü
	Polynom& Polynom::GenerateNormal(uint numberBits)
	{
		return *this;
	}
//------------------------------------------------------------------------------

	//(c) Mamontov, TEST(Polynom, GenerateNormal)
	//(c) Mamontov: ïîêà çàãëóøêà
	//TODO: ðåàëèçîâàòü
	Polynom& Polynom::GenerateNormal(const Polynom& module)
	{
		return *this;
	}
//------------------------------------------------------------------------------
    //(c) Chernysheva, TEST(Polynom, GenerateIrreducible)
	// ãåíåðàöèÿ íîðìàëüíîãî ìíîãî÷ëåíà
  // nMinNumberBits - ìèíèìàëüíîå ÷èñëî 1 (ä.á. >= 3)
  // nMaxNumberBits - ìàêñèìàëüíîå ÷èñëî 1 (ä.á. nMaxNumberBits >= nMinNumberBits)
  // nDegree - ñòåïåíü ìíîãî÷ëåíà (ä.á. nDegree >= nMaxNumberBits-1)
  Polynom& Polynom::GenerateNormal(uint nMinNumberBits, uint nMaxNumberBits, uint nDegree)
  {
    if (nMaxNumberBits < nMinNumberBits)
      throw new AAL::Exception("Ìèíèìàëüíîå ÷èñëî 1 â ïîëèíîìå áîëüøå ìàêñèìàëüíîãî");
    if (nMinNumberBits < 3)
      throw new AAL::Exception("Ìèíèìàëüíîå ÷èñëî 1 â ïîëèíîìå ìåíüøå 3");
    if (nDegree < nMaxNumberBits-1)
      throw new AAL::Exception("Ñòåïåíü ïîëèíîìà ìåíüøå ìàêñèìàëüíîãî ÷èñëà 1");


    // âñå ïàðàìåòðû ñîãëàñîâàíû
    // íóëåâàÿ ñòåïåíü 1
    Polynom plGen("1");
    // êîýôôèöèåíòû ïðè ñòåïåíè ìíîãî÷ëåíà è ïðè ñòåïåíè nDegree - 1 â 1
    plGen.setBit(nDegree, true);
    plGen.setBit(nDegree - 1, true);
    bool isGen = false;
    if (nMaxNumberBits > 3)
    {
      // êîëè÷åñòâî çàíÿòûõ åäèíè÷åê
      uint CurOne = 3;
      // êîëè÷åñòâî ðàññòàâëÿåìûõ åäèíèö îò nMinNumberBits äî nMaxNumberBits
      uint FreeOne = nMinNumberBits - 3;
      while (CurOne + FreeOne <= nMaxNumberBits)
      {
        Polynom plCur(plGen);
        for (uint i = 1; i < FreeOne + 1; ++i)
          plCur.setBit(i, true);
        if (plCur.isNormal())
        {
          // ìíîãî÷ëåí íîðìàëüíûé
          isGen = true;
          *this = plCur;
           break;
        }
        else
        {
          Polynom plEndCicle(plGen);
          for (uint i = nDegree - 2; i >= nDegree - FreeOne - 1; --i)
            plEndCicle.setBit(i, true);
          while (plCur != plEndCicle && !isGen)
          {
            bool bit = plCur.getBit(1);
            if (bit)
            {
              // òåêóùàÿ ïîçèöèÿ êóðñîðà â ïîëèíîìå
              uint pos = 2;
              // ïåðåìåùàåìñÿ äî ïåðâîãî 0 â ïîëèíîìå
              while (plCur.getBit(pos))
                pos++;
              // ïåðåíîñèì 1 íà îäíó ïîçèöèþ âïåðåä
              plCur.setBit(pos, true);
              plCur.setBit(pos - 1, false);
              if (plCur.isNormal())
              {
                // ìíîãî÷ëåí íîðìàëüíûé
                isGen = true;
                *this = plCur;
                break;
              }
            }
            else
            {
              // òåêóùàÿ ïîçèöèÿ êóðñîðà â ïîëèíîìå
              uint pos = 2;
              // ñ÷åò÷èê 1
              uint numOne = 0;
              // ïåðåìåùàåìñÿ äî ïåðâîé 1
              while (!plCur.getBit(pos))
                pos++;
              // ïåðåìåùàåìñÿ äî ïåðâîãî 0
              while (plCur.getBit(pos))
              {
                pos++;
                numOne++;
              }
              // ïåðåíîñèì 1 íà îäíó ïîçèöèþ âïåðåä
              plCur.setBit(pos, true);
              plCur.setBit(pos - 1, false);
              numOne -= 1;
              // â ñîîòâåòñòâèè ñ ïîêàçàíèÿìè ñ÷åò÷èêà, èçìåíèì îñòàâøóþñÿ ÷àñòü ïîëèíîìà
              if (numOne > 0)
              {
                for (uint i = 1; i < numOne + 1; ++i)
                  plCur.setBit(i, true);
                for (uint i = numOne + 1; i < pos; ++i)
                  plCur.setBit(i, false);
                // ïðîâåðêà óñëîâèÿ
                if (plCur.isNormal())
                {
                  // ìíîãî÷ëåí íîðìàëüíûé
                  isGen = true;
                  *this = plCur;
                  break;
                }
              }
              if (numOne == 0)
              {
                // ïðîâåðêà óñëîâèÿ
                if (plCur.isNormal())
                {
                  // ìíîãî÷ëåí íîðìàëüíûé
                  isGen = true;
                  *this = plCur;
                  break;
                }
              }
            }
          }
        }
        if (!isGen)
          FreeOne++;
        else
          break;
      }
      if (!isGen)
        throw new AAL::Exception("Íå óäàëîñü ñãåíåðèðîâàòü ìíîãî÷ëåí ñ äàííûìè ïàðàìåòðàìè");
      else
        return *this;
    }
    else
    {
      // åñëè ÷èñëî 1 â ìíîãî÷ëåíå ðàâíî 3, ïðîâåðÿåì ïîëó÷åííûé ìíîãî÷ëåí íà íîðìàëüíîñòü
      if (plGen.isNormal())
        return *this;
      else
        throw new AAL::Exception("Íå óäàëîñü ñãåíåðèðîâàòü ìíîãî÷ëåí ñ äàííûìè ïàðàìåòðàìè");
    }
  }

//*******************************  Òåîðåìû, ïðîâåðêè è äð. âñïîìîæåíèå  ************************
  // Òåîðåìà Øòèëüáåðãà-Ñóîíà
  // Ïðèìåíÿåòñÿ äëÿ ïðîâåðêè òðåõ÷ëåíîâ ïîëÿ GF(2) âèäà 1 + X^k + X^n íà íåïðèâîäèìîñòü
  // Åñëè âåðíóëè true ìíîãî÷ëåí çàâåäîìî ïðèâîäèì
  // (c) Chernysheva
  bool Polynom::SchtilbergSuonTheorem(const uint k, const uint n) const
  {
    if (n%2 == 0 && k%2 == 0)
      return true;
    else
    {
      if (n%2 == 0 && k%2 == 1 && k != n/2)
      {
        if ((n*k/2)%4 == 0 || (n*k/2)%4 == 1)
          return true;
      }
      else
      {
        if (2*n%k == 0)
        {
          if (k%2 == 0 && (n%8 == 1 || n%8 == 7))
            return true;
        }
        else
        {
          if (k%2 == 0 && (n%8 == 3 || n%8 == 5))
            return true;
        }
      }
    }
    return false;
  }
//----------------------------------------------------------------------------------
  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // ïåðåâîä ÷èñëà â ñòðîêó
  std::string Polynom::i_to_str(uint x) const
  {
    std::string str = "";
    char s[11];
    ltoa(x, s, 10);
    str += s;
    return str;
  }

    //(c) Chernysheva, TEST(Polynom, getPowersString)
  std::string Polynom::ToStringByPowers() const
  {
    std::set<uint> powers(getPowersOfPolynom());
    std::string str = "";
    for (std::set<uint>::iterator i = powers.begin(); i != powers.end(); ++i)
    {
      str += i_to_str(*i);
      str += " ";
    }
    str += "\n";
    return str;
  }

    // Òåñòû ñòåïåíåé ïîëèíîìîâ íà îáðàçîâàíèå ÎÍÁ è ÃÍÁ
  // ÎÍÁ 1
  // (c) Chernysheva, TEST(Polynom, ONB1)
  bool Polynom::ONB1Test(const uint n) const
  {
    Integer p(n + 1);
    if (p.isPrime())
    {
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(n));
      Integer number, mod, pow;
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        number = i->getNumber();
        pow = (p - 1)/number;
        mod.ModPow(Integer(2), pow, p);
        if (mod == 1)
          return false;
      }
      return true;
    }
    else
      return false;
  }

  // ÎÍÁ 2
  // (c) Chernysheva, TEST(Polynom, ONB2)
  bool Polynom::ONB2Test(const uint n) const
  {
    Integer p(2*n + 1);
    if (p.isPrime())
    {
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(2*n));
      Integer number, mod, pow;
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        number = i->getNumber();
        pow = (p - 1)/number;
        mod.ModPow(Integer(2), pow, p);
        if (mod == 1)
          return false;
      }
      return true;
    }
    else
      return false;
  }

  // ÎÍÁ 3
  // (c) Chernysheva, TEST(Polynom, ONB3)
  bool Polynom::ONB3Test(const uint n) const
  {
    // n - íå÷åòíî
    if (n%2)
    {
      Integer p(2*n + 1), condition;
      condition.ModPow(Integer(2), Integer(n), p);
      if (p.isPrime() && condition == 1)
      {
        std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(n));
        Integer number, mod, pow;
        for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
        {
          number = i->getNumber();
          pow = n/number;
          mod.ModPow(Integer(2), pow, p);
          if (mod == 1)
            return false;
        }
        return true;
      }
      else
        return false;
    }
    else
      return false;
  }

   // Ãåíåðàöèè îïòèìàëüíîãî íîðìàëüíîãî áàçèñà, çàäàííîé ñòåïåíè ðàñøèðåíèÿ ïîëÿ
  // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
  // âûõîä: b - ïîëèíîì, A - òàáëèöà óìíîæåíèÿ èëè false - ÎÍÁ 1ãî òèïà íå ñóùåñòâóåò
  // (c) Chernysheva, TEST(Polynom, CreateONB)
  bool Polynom::GenerateONB1(const uint n, Polynom& b, Matrix& A)
  {
    bool beONB = b.ONB1Test(n);
    if (!beONB)
      return false;
    else
    {
      // åäèíè÷íûé âåêòîð
      b.setUnit(n);
      // ïóñòàÿ ìàòðèöà T
      Matrix T(Matrix::ON_LINE, n, n, 0);
      // âû÷èñëÿåì âåêòîð m = 2^i mod p, p = n + 1;
      vector<Integer> m;
      m.resize(n);
      for (int i = 0; i < n; ++i)
      {
        m[i].Parse("0", Dec);
        m[i].ModPow(Integer(2), Integer(i), Integer(n + 1));
      }

      for (int i = 0; i < n; ++i)
      {
        // ïðîâåðÿåì óñëîâèå m = 2^i mod p < n
        // è ïî ðåçóëüòàòàì çàïîëíÿåì ìàòðèöó T
        if (m[i] < n)
        {
          // óñëîâèå âûïîëåíî, íóæíî âêëþ÷èòü â ñïèñîê j = dlog(m + 1) mod p
          Integer m1 = m[i] + 1;
          // ïîèñê â âåêòîðå m
          int j = 0;
          for (int k = 0; k < n; ++k)
          {
            if (m[k] == m1)
            {
              j = k;
              break;
            }
          }
          T.setBit(i, j, true);
        }
        else
        {
          for (int j = 0; j < n; ++j)
            T.setBit(i, j, true);
        }
      }

      // çàïîëíÿåì ìàòðèöó À
      // îáÿçàòåëüíî íàäî, ÷òîáû íà âõîäå îíà áûëà íóëåâîé
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
          bool val = T.getBit(i, j);
          if (val)
            A.setBit(mod(i-j, n), mod(-j, n), true);
        }
      return true;
    }
  }

  // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
  // âûõîä: b - ïîëèíîì, A - òàáëèöà óìíîæåíèÿ èëè false - ÎÍÁ 2ãî òèïà íå ñóùåñòâóåò
  // (c) Chernysheva, TEST(Polynom, CreateONB)
  bool Polynom::GenerateONB2(const uint n, Polynom& b, Matrix& A)
  {
    bool beONB = b.ONB2Test(n);
    if (!beONB)
      return false;
    else
    {
      int p = 2*n + 1;
      // çàïîëíÿåì âåêòîð b
      for (int j = 0; j <= n; ++j)
      {
        int N = (n + j)/2, M = j;
        if (~N&M)
          b.setBit(j, false);
        else
          b.setBit(j, true);
      }

      // âû÷èñëÿåì âåêòîð m = 2^k mod p, p = 2n + 1;
      vector<Integer> m;
      m.resize(p);
      for (int k = 0; k <= 2*n; ++k)
      {
        m[k].Parse("0", Dec);
        m[k].ModPow(Integer(2), Integer(k), Integer(p));
      }

      // âû÷èñëÿåì delta(k) = dlog(m + 1) mod p mod n
      // è çàïîëíÿåì ìàòðèöó A
      for (int k = 0; k < n; ++k)
      {
        Integer dk = m[k] + 1;
        // ïîèñê â âåêòîðå m
        int j = 0;
        for (int i = 0; i <= 2*n; ++i)
        {
          if (m[i] == dk)
          {
            j = i;
            break;
          }
        }
        A.setBit(k, mod(j, n), true);
      }

      // âû÷èñëÿåì mu(k) = dlog(m - 1) mod p mod n
      // è çàïîëíÿåì ìàòðèöó A
      for (int k = 1; k < n; ++k)
      {
        Integer mk = m[k] - 1;
        // ïîèñê â âåêòîðå m
        int j = 0;
        for (int i = 0; i <= 2*n; ++i)
        {
          if (m[i] == mk)
          {
            j = i;
            break;
          }
        }
        A.setBit(k, mod(j, n), true);
      }
      return true;
    }
  }

  // âõîä: n - ñòåïåíü ðàñøèðåíèÿ ïîëÿ
  // âûõîä: b - ïîëèíîì, A - òàáëèöà óìíîæåíèÿ èëè false - ÎÍÁ 3ãî òèïà íå ñóùåñòâóåò
  // (c) Chernysheva
  bool Polynom::GenerateONB3(const uint n, Polynom& b, Matrix& A)
  {
    bool beONB = b.ONB3Test(n);
    if (!beONB)
      return false;
    else
    {
      int p = 2*n + 1;
      // çàïîëíÿåì âåêòîð b
      for (int j = 0; j <= n; ++j)
      {
        int N = (n + j)/2, M = j;
        if (~N&M)
          b.setBit(j, false);
        else
          b.setBit(j, true);
      }

      // âû÷èñëÿåì âåêòîð m = 2^k mod p, p = 2n + 1;
      vector<Integer> m;
      m.resize(p);
      std::string s;
      for (int k = 0; k <= 2*n; ++k)
      {
        m[k].Parse("0", Dec);
        m[k].ModPow(Integer(2), Integer(k), Integer(p));
        s = m[k].ToString(Dec);
      }

      // âû÷èñëÿåì delta(k) = dlog(1 + m) mod p mod n
      // è çàïîëíÿåì ìàòðèöó A
      for (int k = 0; k < n; ++k)
      {
        Integer dk = 1 + m[k];
        s = dk.ToString(Dec);
        // ïîèñê â âåêòîðå m
        int j = 0;
        // ôëàã íàëè÷èÿ ÷èñëà â âåêòîðå
        bool is = false;
        for (int i = 0; i <= 2*n; ++i)
        {
          if (m[i] == dk)
          {
            j = i;
            is = true;
            break;
          }
        }
        if (is)
          A.setBit(k, mod(j, n), true);
      }

      // âû÷èñëÿåì delta(k) = dlog(-1 - m) mod p mod n
      // è çàïîëíÿåì ìàòðèöó A
      for (int k = 0; k < n; ++k)
      {
        Integer dk = -1 - m[k];
        s = dk.ToString(Dec);
        // ò.ê. êëàññ Integer íå ïðèâîäèò îòðèöàòåëüíûå ÷èñëà ïî ìîäóëþ, ïðèâåäåì åãî ñëîæåíèåì
        dk = dk + p;
        s = dk.ToString(Dec);
        // ïîèñê â âåêòîðå m
        int j = 0;
        // ôëàã íàëè÷èÿ ÷èñëà â âåêòîðå
        bool is = false;
        for (int i = 0; i <= 2*n; ++i)
        {
          if (m[i] == dk)
          {
            j = i;
            is = true;
            break;
          }
        }
        if (is)
          A.setBit(k, mod(j, n), true);
      }

      // âû÷èñëÿåì mu(k) = dlog(-1 + m) mod p mod n
      // è çàïîëíÿåì ìàòðèöó A
      for (int k = 1; k < n; ++k)
      {
        Integer mk = -1 + m[k];
        s = mk.ToString(Dec);
        // ïîèñê â âåêòîðå m
        int j = 0;
        // ôëàã íàëè÷èÿ ÷èñëà â âåêòîðå
        bool is = false;
        for (int i = 0; i <= 2*n; ++i)
        {
          if (m[i] == mk)
          {
            j = i;
            is = true;
            break;
          }
        }
        if (is)
          A.setBit(k, mod(j, n), true);
      }

      // âû÷èñëÿåì mu(k) = dlog(1 - m) mod p mod n
      // è çàïîëíÿåì ìàòðèöó A
      for (int k = 1; k < n; ++k)
      {
        Integer mk = 1 - m[k];
        s = mk.ToString(Dec);
        mk = mk + p;
        s = mk.ToString(Dec);
        // ïîèñê â âåêòîðå m
        int j = 0;
        // ôëàã íàëè÷èÿ ÷èñëà â âåêòîðå
        bool is = false;
        for (int i = 0; i <= 2*n; ++i)
        {
          if (m[i] == mk)
          {
            j = i;
            is = true;
            break;
          }
        }
        if (is)
          A.setBit(k, mod(j, n), true);
      }
      return true;
    }
  }

  bool Polynom::GenerateONB1Polynom(const uint n, Polynom& b)
  {
    bool beONB = b.ONB1Test(n);
    if (!beONB)
      return false;
    else
    {
      // åäèíè÷íûé âåêòîð
      b.setUnit(n);
      return true;
    }
  }

  bool Polynom::GenerateONB2Polynom(const uint n, Polynom& b)
  {
    bool beONB = b.ONB2Test(n);
    if (!beONB)
      return false;
    else
    {
      int p = 2*n + 1;
      // çàïîëíÿåì âåêòîð b
      for (int j = 0; j <= n; ++j)
      {
        int N = (n + j)/2, M = j;
        if (~N&M)
          b.setBit(j, false);
        else
          b.setBit(j, true);
      }
      return true;
    }
  }

  bool Polynom::GenerateONB3Polynom(const uint n, Polynom& b)
  {
    bool beONB = b.ONB3Test(n);
    if (!beONB)
      return false;
    else
    {
      int p = 2*n + 1;
      // çàïîëíÿåì âåêòîð b
      for (int j = 0; j <= n; ++j)
      {
        int N = (n + j)/2, M = j;
        if (~N&M)
          b.setBit(j, false);
        else
          b.setBit(j, true);
      }
      return true;
    }
  }

   // ÃÍÁ
  // (c) Chernysheva, TEST(Polynom, GNB)
  bool Polynom::GNBTest(const uint n, const int type) const
  {
    if (type < 3 || type > 6)
      throw new AAL::Exception("Òèï ÃÍÁ äîëæåí áûòü îò 3 äî 6");

    Integer p(type*n + 1);
    if (p.isPrime())
    {
      // ïðîâåðêó íåäåëèìîñòè 2 íà p îïóñêàåì, ò.ê. ýòî î÷åâèäíî
      std::vector<DecompositionMember> vector(DecompositionManager::Instance().getPrimeDecomposition(n));
      Integer number, mod, pow;
      for (std::vector<DecompositionMember>::iterator i = vector.begin(); i != vector.end(); ++i)
      {
        number = i->getNumber();
        pow = (p - 1)/number;
        mod.ModPow(Integer(2), pow, p);
        if (mod == 1)
          return false;
      }
      return true;
    }
    else
      return false;
  }

//**********************************************************************************************

//************************  Îïåðàöèè ìóëüòèïëèêàòèâíîé ãðóïïû è ïîëÿ  **************************
	//simple method
        // TODO: ðåôàêòîðèòü ïîä ïðîñòîé àëãîðèòì Åâêëèäà
	bool Polynom::InMulGroup(Polynom &groupModule)
	{
		Polynom result, x, y;
		return result.ExEuclid(*this, groupModule, x , y).isOne();
	}
//------------------------------------------------------------------------------

	//simple method
	Polynom& Polynom::Inverse(Polynom &module)
	{
		return Inverse(*this, module);
	}
//------------------------------------------------------------------------------

	//(c) Morozov, TEST(Polynom, Inverse)
	Polynom& Polynom::Inverse(Polynom &polynom, Polynom &module)
	{
    Polynom *p = new Polynom(polynom);
    Polynom *m = new Polynom(module);
    if(Euclid(*p,*m).isOne())
    {
       polynom = *p;
       module = *m;
    if(!polynom.InMulGroup(module))
			throw new AAL::Exception("Ïîëèíîì íå ïðèíàäëåæèò ìóëüòèïëèêàòèâíîé ãðóïïå");

		Polynom temp,temp2,i(polynom);
                i.Mod(module);
		temp.ExEuclid(i, module, *this, temp2);

		return *this;
   }
   else
    throw new AAL::Exception("A1 è f(X) äîëæíû áûòü âçàèìíî ïðîñòû.");
	}

 	Polynom& Polynom::InverseGF2_n(Polynom &polynom, Polynom &module)
	{
                if(!module.isIrreducible())
                {
                        throw new AAL::Exception("f(X) äîëæíû áûòü íåïðèâîäèìûì.");
                }

		return Inverse(polynom, module);
	}

//------------------------------------------------------------------------------

  Polynom& Polynom::Trace(Polynom &module)
	{
		return Trace(*this, module);
	}
//------------------------------------------------------------------------------

	//(c) Morozov, TEST(Polynom, Inverse)
	Polynom& Polynom::Trace(Polynom &polynom, Polynom &module)
	{
                if(!module.isIrreducible())
                        throw new AAL::Exception("Ïîëèíîì äîëæåí áûòü íåïðèâîäèìûì");
                if(!polynom.InMulGroup(module))
			throw new AAL::Exception("Ïîëèíîì íå ïðèíàäëåæèò ìóëüòèïëèêàòèâíîé ãðóïïå");

		Polynom temp(polynom);
                Integer two(2);
                setZero();

                uint n = module.getNumberBits() - 1;
                for(uint i = 0; i < n; i++)
                {
                        *this += temp;
                        temp.ModPow(temp, two, module);
                }

		return *this;
	}
//-----------------------------------------------------------------------------
Integer& Polynom::elementOrder(Polynom &groupModule, Polynom &polynom,std::vector<DecompositionMember> vector, const Integer &ord )
{
  if(!polynom.InMulGroup(groupModule))
    throw new AAL::Exception("Ïîëèíîì íå ïðèíàäëåæèò ìóëüòèïëèêàòèâíîé ãðóïïå");
  if(vector.size() == 1 && vector[0].getDegree() == 1)
    return vector[0].getNumber();
  if(vector.size() >= 1)
  {
    std::vector<DecompositionMember>::iterator it;
    Polynom *m  = new Polynom(groupModule);
    Polynom *a = new Polynom(polynom);
    Integer t =  ord;
    Integer o =  Integer(ord);
    for(it = vector.begin(); it != vector.end();it++)
    {
      AAL::Integer p(it->getNumber());
      AAL::Integer e(it->getDegree());
      AAL::Integer ex ;
      ex.ModPow(p,e,o);
      std::string s = ex.ToString();
      t = t/(ex);
      Polynom a1;
      a1.ModPow(*a,t,*m);
      while(!a1.isOne())
      {
        a1.ModPow(a1,p, *m);
        t = t*p;
      }
    }
    AAL::Integer *rez =  new AAL::Integer(t);
    return *rez;
  }
  else
     throw new AAL::Exception("Ââåäèòå ðàçëîæåíèå ïîðÿäêà ãðóïïû.");
}
bool Polynom::isGenerator(Polynom &groupModule, Polynom &polynom,std::vector<DecompositionMember> vector, const Integer &ord)
{
  if(!polynom.InMulGroup(groupModule))
    throw new AAL::Exception("Ïîëèíîì íå ïðèíàäëåæèò ìóëüòèïëèêàòèâíîé ãðóïïå");
    if (vector.size() == 1) return true;
    if(vector.size() > 1)
    {   AAL::Integer m(ord-1);
       // AAL::Integer b(polynom.ToString(),Bin);
      Integer t = elementOrder(groupModule, polynom,vector,ord-1);
       if(t == m)
        return true;
    }
  else
   throw new AAL::Exception("Ââåäèòå ðàçëîæåíèå ïîðÿäêà ãðóïïû.");
return false;
}

//----------------------------------------------------------------------------------------

//**********************************************************************************************
};
