/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#ifndef __TABLEMANAGER_H__
#define __TABLEMANAGER_H__

#include "BasicType.h"

// Класс для хранения таблиц
// (например таблиц умножения элементарных многочленов над GF(2))
// реализован с использованием паттерна Singleton(см. "Шаблоны проектирования" GOF)
namespace AAL
{
        class TableManager {
        private:
                ushort  _gf2MultiplicationTable[256][256];
        private:
                TableManager();                
        public:
                //
                static TableManager& Instance();
                ushort getElementaryPolynomsMultiplication(uchar u, uchar v);
        private:
//                void TableManager::createMultiplicationTableForGF2();
        };
};
#endif
