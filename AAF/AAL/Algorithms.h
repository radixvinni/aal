/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <vector>
#include "Integer.h"

namespace AAL
{
   // функция реализующая алгоритм Евклида вычисления НОД(a,b) элементов a и b
  // кольца R
  template <class Type>
  Type SimpleEuclid(const Type &a,Type  &b)
  {
        if(a.isZero() && b.isZero())
                throw new Exception("a и b не могут быть оба равны 0");

        Type u,v; // текущие значение
        Type e;   // e = НОД(a,b)
        Type r;   // остаток от деления
        Type buf; // буфер обмена

        u = a;
        v = b;

        if ( a.isZero())
        {
           u = v;
           v.setZero();
        }

        while (!v.isZero())
        {
                if ( u < v )
                {
                   buf = u;
                   u = v;
                   v = buf;
                }

                r.Mod(u,v);
                u = v;
                v = r;
         }
         e = u;

        return e;
    }

    // Простой класс для предствавления члена разложения числа
        class DecompositionMember
        {
        private:
                Integer _number;
                Integer _degree;
        public:
				DecompositionMember() {}
				DecompositionMember(const Integer & number, const Integer & degree) :
        _number(number), _degree(degree) {}
                DecompositionMember(const DecompositionMember &member) :
        _number(member._number), _degree(member._degree) {}
                ~DecompositionMember() {}
        public:
                const Integer & getNumber() const { return _number; }
                const Integer & getDegree() const { return _degree; }
        public:
                DecompositionMember& operator= (const DecompositionMember &member)
                {
                       if(this == &member)
                                return * this;

                        _number = member._number;
                        _degree = member._degree;

                        return * this;
                }
        public:
                static bool isRightDecomposition(Integer &number, std::vector<DecompositionMember>& decomposition)
                {
                        // 1) проверка что произведение даёт число
                        // 2) проверка что числа простые

                        //TODO: реализовать
                        // 3) проверить что нет повторябщихся членов
                        Integer multiplication("1");
                        std::vector<DecompositionMember>::iterator it = decomposition.begin();
                        while(it != decomposition.end())
                        {
                                Integer number(it->getNumber());
                                if(!number.isPrime())
                                        return false;

                                Integer degree(it->getDegree());
                                Integer result;
                                result.Pow(number, degree);
                                multiplication *= result;
                                ++it;
                        }
                        return (multiplication == number);
                }
        };
};

#endif
