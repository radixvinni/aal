/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "IntegerBinom.h"
#include "Converter.h"
#include <string>
namespace AAL
{
        IntegerBinomModulePolynom::IntegerBinomModulePolynom() :
        _a0("1"), _a1(), _module("7")
        {
        }

        IntegerBinomModulePolynom::IntegerBinomModulePolynom(const Integer& a0, const Integer& a1, const Integer& module) :
        _a0(a0), _a1(a1), _module(module)
        {
                if(a0.isNegative() || a0 >= module || a1.isNegative() || a1 >= module)
                        throw new Exception("Коэффицениы должны принадлежать GF(module)");
                if(module.isNegative())
                        throw new Exception("Характеристика поля p  должена быть пололжительным числом");
                if(!(const_cast<Integer &>(module)).isPrime())
                        throw new Exception("Характеристика поля p  должена быть простым числом");
                if(!isIrreducible())
                        throw new Exception("Многочлен должен быть неприводимым");

        }

        IntegerBinomModulePolynom::IntegerBinomModulePolynom(const IntegerBinomModulePolynom & polynom) :
        _a0(polynom._a0), _a1(polynom._a1), _module(polynom._module)
        {
        }

        IntegerBinomModulePolynom::~IntegerBinomModulePolynom()
        {        
        }
        
        const Integer& IntegerBinomModulePolynom::getA0() const
        {
                return _a0;
        }

        const Integer& IntegerBinomModulePolynom::getA1() const
        {
                return _a1;
        }

        const Integer& IntegerBinomModulePolynom::getModule() const
        {
                return _module;
        }

        void IntegerBinomModulePolynom::setModule(const Integer& module)
        {
                if(module.isNegative())
                        throw new Exception("Характеристика поля p  должена быть пололжительным числом");
                if(!(const_cast<Integer &>(module)).isPrime())
                        throw new Exception("Характеристика поля p  должена быть простым числом");
                _module = module;
                _a0.ModPositive(_module);
                _a1.ModPositive(_module);
                
                if(!isIrreducible())
                        throw new Exception("Многочлен должен быть неприводим");
        }

        void IntegerBinomModulePolynom::setA0A1(const Integer& a0, const Integer& a1)
        {
                if(a0.isNegative() || a0 >= _module || a1.isNegative() || a1 >= _module)
                        throw new Exception("Коэффицениы должны принадлежать GF(module)");

                _a0 = a0;
                _a1 = a1;
        }

        IntegerBinomModulePolynom& IntegerBinomModulePolynom::operator= (const IntegerBinomModulePolynom& polynom)
        {
                if(this == &polynom)
                        return *this; 

                _a0 = polynom._a0;
                _a1 = polynom._a1;
                _module = polynom._module;

                return *this;
        }


        bool operator==(const IntegerBinomModulePolynom& a, const IntegerBinomModulePolynom& b)
        {
                if(&a == &b)
                        return true; 

                return a._a0 == b._a0 && a._a1 == b._a1 && a._module == b._module;
        }

        bool operator!=(const IntegerBinomModulePolynom& a, const IntegerBinomModulePolynom& b)
        {
                return !(a==b);
        }

        std::string IntegerBinomModulePolynom::ToString() const
        {
                std::string str;

                str += "(" + _a0.ToString() + "," + _a1.ToString() + ")" + " module = " + _module.ToString();

                return str; 
        }
        bool IntegerBinomModulePolynom::isIrreducible() const
        {
                if(_a0.isZero() && _a1.isZero())
                        return false; 

                if(_a1.isZero())
                {
                        Integer negativeA0(_module - _a0);
                        return (negativeA0.LegendreSymbol(const_cast<Integer &>(_module)) == -1);
                }

                        
                // TODO: полностью реализовать
                return true; 
        }
//**********************************************************************************************
//***********************************  Конструкторы  *******************************************


//(c) Morozov, TEST(IntegerBinom, EmptyConstructor)
        IntegerBinom::IntegerBinom() :
        _a(), _b(), _modulePolynom()
        {
        }

//(c) Morozov, TEST(IntegerBinom, CopyConstructor)
        IntegerBinom::IntegerBinom(const IntegerBinom & binom) :
        _a(binom._a), _b(binom._b), _modulePolynom(binom._modulePolynom)
        {
        }

        IntegerBinom::IntegerBinom(const Integer& a, const Integer& b, const IntegerBinomModulePolynom& modulePolynom) :
        _a(a), _b(b), _modulePolynom(modulePolynom)
        {
                if(a.isNegative() || a >= getModule() || b.isNegative() || b >= getModule())
                        throw new Exception("Коэффициенты должны принадлежать GF(p)");
        }
        IntegerBinom::~IntegerBinom()
        {
        }
                                                                                                
//**********************************************************************************************
//*************************  Преобразование и считывание из сторк ******************************        
        std::string IntegerBinom::ToString() const
        {
                std::string str;

                //str += "(" + _a.ToString() + "," + _b.ToString() + ")" +  " modPol: " + _modulePolynom.ToString();
                str += "(" + _a.ToString() + "," + _b.ToString() + ")";

                return str; 
        }        
//**********************************************************************************************
//***************************************  Методы акцепторы   **********************************
        bool IntegerBinom::isZero() const
        {
                return _a.isZero() && _b.isZero();
        }
        bool IntegerBinom::isOne() const
        {
                return _a.isOne() && _b.isZero();
        }
        void IntegerBinom::setZero()
        {
                _a.setZero();
                _b.setZero();
        }
        void IntegerBinom::setOne()
        {
                _a.setOne();
                _b.setZero();
        }
        const Integer& IntegerBinom::getA() const
        {
                return _a;
        }
        const Integer& IntegerBinom::getB() const
        {
                return _b;
        }
        const IntegerBinomModulePolynom& IntegerBinom::getModulePolynom() const
        {
                return _modulePolynom;
        }
        const Integer& IntegerBinom::getModule() const
        {
                return _modulePolynom.getModule();
        }
        void IntegerBinom::setA(const Integer & a)
        {
                if(a.isNegative() || a >= getModule())
                        throw new Exception("Коэффициент должн принадлежать GF(p)");

                _a = a;
        }
        void IntegerBinom::setB(const Integer & b)
        {
                if(b.isNegative() || b >= getModule())
                        throw new Exception("Коэффициент должн принадлежать GF(p)");

                _b = b;
        }
        void IntegerBinom::setModulePolynom(const IntegerBinomModulePolynom& modulePolynom)
        {
                _modulePolynom = modulePolynom;
                Integer module(getModule());
                _a.ModPositive(module);
                _b.ModPositive(module);
        }
        bool IntegerBinom::isGenerative(std::vector<DecompositionMember>& mulGroupOrdDecomposition) const
        {
                if(isZero() || isOne())
                        return false;


                Integer mulGroupOrd(getMulGroupOrder());

                if(!DecompositionMember::isRightDecomposition(mulGroupOrd, mulGroupOrdDecomposition))
                        throw new Exception("Введите разложние");

                std::vector<DecompositionMember>::iterator it = mulGroupOrdDecomposition.begin();
                while(it != mulGroupOrdDecomposition.end())
                {
                        Integer number(it->getNumber());
                        Integer degree;
                        degree.Div(mulGroupOrd, number, NULL);
                        IntegerBinom result;
                        if(result.Pow(const_cast<IntegerBinom &>(*this), degree).isOne())
                                return false;

                        ++it;
                }          

                return true;
        }
        Integer IntegerBinom::getMulGroupOrder() const
        {
                Integer order(getModule()*getModule());
                order--;

                return order;
        }
//**********************************************************************************************
//************************************  Унарные операции   *************************************
        IntegerBinom& IntegerBinom::operator= (const IntegerBinom& binom)
        {
                if(this == &binom)
                        return *this;
                        
                _a = binom._a;
                _b = binom._b;
                _modulePolynom = binom._modulePolynom;                
                return *this;
        }

//**********************************************************************************************
//*****************************    Операции сравнения    ***************************************
        bool operator==(const IntegerBinom& a, const IntegerBinom& b)
        {
                if(&a == &b)
                        return true;

                return a._a == b._a && a._b == b._b && a._modulePolynom == b._modulePolynom;
        }
        bool operator!=(const IntegerBinom& a, const IntegerBinom& b)
        {
                return !(a==b);
        }

//**********************************************************************************************
//******************************    Операция сложения    ***************************************
        IntegerBinom operator+(const IntegerBinom &a, const IntegerBinom &b)
        {
                IntegerBinom result, copy_a(a), copy_b(b);
                return result.Add(copy_a, copy_b);
        }
	IntegerBinom& IntegerBinom::operator+=(IntegerBinom & binom)
        {
                return Add(*this, binom);
        }
	IntegerBinom& IntegerBinom::Add(IntegerBinom &a, IntegerBinom &b)
        {
                if(a.getModulePolynom() != b.getModulePolynom())
                        throw new Exception("Поля и модулярные многочлены должны быть равны");

                _modulePolynom = a._modulePolynom;

                Integer module(getModule());

                _a.ModAdd(a._a, b._a, module);
                _b.ModAdd(a._b, b._b, module);

                return *this;
        }
//**********************************************************************************************
//******************************    Операция вычитания   ***************************************
        IntegerBinom operator-(const IntegerBinom &a, const IntegerBinom &b)
        {
                IntegerBinom result, copy_a(a), copy_b(b);
                return result.Sub(copy_a, copy_b);
        }
	IntegerBinom& IntegerBinom::operator-=(IntegerBinom & binom)
        {
                return Sub(*this, binom);
        }
	IntegerBinom& IntegerBinom::Sub(IntegerBinom &a, IntegerBinom &b)
        {
                if(a.getModulePolynom() != b.getModulePolynom())
                        throw new Exception("Поля и модулярные многочлены должны быть равны");

                _modulePolynom = a._modulePolynom;

                Integer module(getModule());

                _a.ModSub(a._a, b._a, module);
                _a.ModPositive(module);
                _b.ModSub(a._b, b._b, module);
                _b.ModPositive(module);

                return *this;
        }
//**********************************************************************************************
//******************************    Операция взятия противоположного элемента    ***************        
        IntegerBinom& IntegerBinom::Negate()
        {
                return Negate(*this);
        }
	IntegerBinom& IntegerBinom::Negate(IntegerBinom &binom)
        {
                _modulePolynom = binom._modulePolynom;
                _a = binom._a;
                _b = binom._b;

                Integer module(getModule());
                _a.Negate();
                _a.ModPositive(module);
                _b.Negate();
                _b.ModPositive(module);
                return *this;
        }

//**********************************************************************************************
//******************************    Операция умножения   ***************************************

        IntegerBinom operator*(const IntegerBinom &a, const IntegerBinom &b)
        {
                IntegerBinom result, copy_a(a), copy_b(b);
                return result.Mul(copy_a, copy_b);
        }
	IntegerBinom& IntegerBinom::operator*=(IntegerBinom & binom)
        {
                return Mul(*this, binom);
        }
	IntegerBinom& IntegerBinom::Mul(IntegerBinom &a, IntegerBinom &b)
        {
                if(a.getModulePolynom() != b.getModulePolynom())
                        throw new Exception("поля и модулярные многочлены должны быть равны");

                _modulePolynom = a._modulePolynom;

                IntegerBinom copy_a(a), copy_b(b);
                Integer squareCoef, temp1, temp2;
                Integer module(getModule());

                // умножение многочленов и приведение по модулю p
                _a.ModMul(copy_a._a, copy_b._a, module);
                temp1.ModMul(copy_a._a, copy_b._b, module);
                temp2.ModMul(copy_a._b, copy_b._a, module);
                _b.ModAdd(temp1, temp2, module);
                squareCoef.ModMul(copy_a._b, copy_b._b, module);

                if(squareCoef.isZero())
                        return *this;
		
		// исправлено 13.07.2019
                _a.ModSub(_a, squareCoef, module);
                
		// редуцирование
                /*
		Integer multiplier(module - squareCoef);
		temp1.ModMul(multiplier, const_cast<Integer &>(_modulePolynom.getA0()), module);
                temp2.ModMul(multiplier, const_cast<Integer &>(_modulePolynom.getA1()), module);
                _a.ModAdd(_a, temp1, module);
                _b.ModAdd(_b, temp2, module);                
		*/
                return *this;
        }

//**********************************************************************************************
//******************************    Операция возведения в степень    ***************************        
        IntegerBinom& IntegerBinom::Pow(IntegerBinom &a, Integer &n)
        {
                if(n.isNegative())
			throw new Exception("Число n - отрицательное, результат не определен");

                _modulePolynom = a._modulePolynom;
                
                IntegerBinom copy_a(a);
		Integer copy_n(n);

		setOne();
                
		uint s = copy_n.getNumberBits();
		for(uint i=0;i<s;i++)
		{
                        Mul(*this, *this);
			if(copy_n.getBit(s-1-i))
			        Mul(*this, copy_a);
		}

                return *this;
        }
//**********************************************************************************************
//******************************    Операция взятия обратного элемента    **********************
        IntegerBinom& IntegerBinom::Inverse()
        {
                return Inverse(*this);
        }
        // алгоритм вычисления обратного элемента по т. ферма
        IntegerBinom& IntegerBinom::Inverse(IntegerBinom &a)
        {
                IntegerBinom copy_a(a);

                Integer mulGroupOrderWithoutOne(copy_a.getMulGroupOrder());
                mulGroupOrderWithoutOne--;

                return Pow(copy_a, mulGroupOrderWithoutOne);
        }
//**********************************************************************************************
//******************************           Операции генерации             **********************
        IntegerBinom& IntegerBinom::Generate()
        {
                _a.Generate(getModule());
                _b.Generate(getModule());

                return *this;
        }
        IntegerBinom& IntegerBinom::GenerateGenerative(std::vector<DecompositionMember>& mulGroupOrdDecomposition)
        {

                do
                {
                       Generate();
                } while (!isGenerative(mulGroupOrdDecomposition));

                return *this;
        }
//**********************************************************************************************
//***************************    Операции генерации группы корней из единицы   *****************
        uint IntegerBinom::getMaxFactorizableGroupOrder() const
        {
                return 400;
        }
        bool IntegerBinom::isParentGroupSmallEnoughForFactorization() const
        {
                if(getMulGroupOrder() > getMaxFactorizableGroupOrder())
                        return false;
                return true;
        }
        std::vector<IntegerBinom> IntegerBinom::GenerateOneRootGroup(const Integer & rootDegree, std::vector<DecompositionMember>& mulGroupOrdDecomposition)
        {
                if(!isParentGroupSmallEnoughForFactorization())
                        throw new Exception("Порядок группы должен быть меньше " + Integer(getMaxFactorizableGroupOrder()).ToString());
                if(rootDegree.isZero())
                        throw new Exception("Показатель степени корня не должен быть равен 0");
                if((rootDegree >= getMulGroupOrder()) || (getMulGroupOrder() % rootDegree) != 0)
                        throw new Exception("Показатель степени корня должен делить порядок группы");

                IntegerBinom generative(*this);
                generative.GenerateGenerative(mulGroupOrdDecomposition);

                std::vector<IntegerBinom> group;

                Integer mulGroupOrder(generative.getMulGroupOrder());
                Integer degree(mulGroupOrder / rootDegree);

                IntegerBinom binom(*this);
                binom.setOne();
                group.push_back(binom);
                if(!rootDegree.isOne())
                {
                        binom.Pow(const_cast<IntegerBinom &>(generative), degree);
                        group.push_back(binom);
                }
                IntegerBinom member(binom);
                for(Integer i("2"); i < rootDegree;i++)
                {
                        member.Mul(member, binom);
                        group.push_back(member);
                }
                return group;
        }
//**********************************************************************************************
//***************************          Операции генерации подгруппы            *****************
        std::vector<IntegerBinom> IntegerBinom::GenerateSubGroup(const Integer & subGroupOrder, std::vector<DecompositionMember>& mulGroupOrdDecomposition)
        {
                if(!isParentGroupSmallEnoughForFactorization())
                        throw new Exception("Порядок группы должен быть меньше " + Integer(getMaxFactorizableGroupOrder()).ToString());
                if(subGroupOrder.isZero())
                        throw new Exception("Порядок подгруппы не должен быть равен 0");
                if((subGroupOrder >= getMulGroupOrder()) && (getMulGroupOrder() % subGroupOrder) != 0)
                        throw new Exception("Порядок подгруппы должен делить порядок группы");

                IntegerBinom generative(*this);
                generative.GenerateGenerative(mulGroupOrdDecomposition);

                std::vector<IntegerBinom> group;

                Integer mulGroupOrder(generative.getMulGroupOrder());
                Integer degree(mulGroupOrder / subGroupOrder);
                IntegerBinom binom(*this);
                binom.Pow(generative, degree);

                group.push_back(binom);
                IntegerBinom member(binom);
                for(Integer i("1"); i < subGroupOrder;i++)
                {
                        member.Mul(member, binom);
                        group.push_back(member);
                }
                return group;
        }
//**********************************************************************************************
//***************************          Операции умнжения множества             *****************
        std::vector<IntegerBinom> IntegerBinom::MulMultitude(std::vector<IntegerBinom> & multitude, const IntegerBinom & binom)
        {
                std::vector<IntegerBinom> newMultitude;

                for(std::vector<IntegerBinom>::iterator it = multitude.begin();
                it != multitude.end(); ++it)
                {
                        IntegerBinom member(*it);
                        member.Mul(member, const_cast<IntegerBinom &>(binom));
                        newMultitude.push_back(member);
                }
                return newMultitude;
        }
//**********************************************************************************************
//***************************              Операции работы со строками         *****************
        std::string IntegerBinom::MultitudeToString(std::vector<IntegerBinom> & multitude)
        {
                return Converter::MultitudeToString(multitude);
        }
        std::string IntegerBinom::FactorToString(std::vector<IntegerBinom> & factor, std::vector<std::vector<IntegerBinom> > & subGroups)
        {
                return Converter::FactorToString(factor, subGroups);
        }
        std::string IntegerBinom::FactorToTexString(std::vector<IntegerBinom> & factor, std::vector<std::vector<IntegerBinom> > & subGroups)
        {
                return Converter::FactorToTexString(factor, subGroups);
        }
        std::string IntegerBinom::FactorToTexString(const Integer & rootDegree, std::vector<DecompositionMember>& mulGroupOrdDecomposition)
        {
                std::vector<IntegerBinom> oneRootGroup(GenerateOneRootGroup(rootDegree, mulGroupOrdDecomposition));

                Integer groupOrd(getMulGroupOrder() / rootDegree);
                std::vector<IntegerBinom> subGroup(GenerateSubGroup(groupOrd, mulGroupOrdDecomposition));

                std::vector<std::vector<IntegerBinom> > subGroups;
                for(std::vector<IntegerBinom>::iterator it = oneRootGroup.begin();
                it != oneRootGroup.end(); ++it)
                {
                        std::vector<IntegerBinom> group(MulMultitude(subGroup, (*it)));
                        subGroups.push_back(group);
                }

                return FactorToTexString(oneRootGroup, subGroups);
        }


};
