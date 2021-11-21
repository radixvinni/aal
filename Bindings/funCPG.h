//#include "stdafx.h"
#include "funTD.h"
#include <iostream>
#include <iostream>
#include "./AAF/AAL/Polynom.h"
#include "./AAF/AAL/PolynomGF2_mY_7.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include <set>
#include <vector>
#include "./AAF/AAL/Integer.h"
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace AAL;
using namespace std;


// Функция формирования нулевого блока (разностного множества)
vector<int> diffset(int vv, Polynom f, int v, int d, PolynomGF2_mY_7 x, PolynomGF2_mY_7 mod);

// Функция синтеза блока с номером s циклической проективной плоскости
vector<int> CPGBlockCreation(int s, vector<int> dfst, int v, int vv);

// Функция синтеза блока с номером s циклической дуальной проективной плоскости
vector<int> DCPGBlockCreation(int s, vector<int> dfst, int v, int vv);

// Умножение над GF(2^l) по модулю многочлена степени d
PolynomGF2_mY_7 ModMul(PolynomGF2_mY_7 a, PolynomGF2_mY_7 b, PolynomGF2_mY_7 modf, int d);

// Возведение в степень над GF(2^l) по модулю многочлена степени d
PolynomGF2_mY_7 ModPow(PolynomGF2_mY_7 a, int n, PolynomGF2_mY_7 modf, int d, Polynom f);

// Алгоритм Евклида
PolynomGF2_mY_7 Euclid(const PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b);

// Алгоритм2: Проверка неприводимости и примитивности многочлена степени n над полем GF(2^l)
int ALG2(int q, int n, Polynom fprim, PolynomGF2_mY_7 ff, vector<DecompositionMember> s, vector<DecompositionMember> dd,
	int d);

// Генерация всех неприводимых многочленов над GF(2)
vector<Polynom> genAllIrreducibleF2l(int l, int p);

// Генерация неприводимого многочлена над GF(2)
Polynom genIrreducibleF2l(int l, int p);

// Генерация всех примитивных многочленов над GF(2)
vector<Polynom> genAllPrimitiveF2l(int l, int p);

// Генерация всех неприводимых многочленов над GF(2^l)
vector<PolynomGF2_mY_7> genAllIrreducibleF2ld(int d, int l, int p, Polynom f);

// Генерация неприводимого многочлена над GF(2^l)
PolynomGF2_mY_7 genIrreducibleF2ld(int d, int l, int p, Polynom f);

// Генерация всех примитивных многочленов над GF(2^l)
vector<PolynomGF2_mY_7> genAllPrimitiveF2ld(int d, int l, int p, Polynom f);

// Генерация примитивного многочлена над GF(2^l)
PolynomGF2_mY_7 genPrimitiveF2ld(int d, int l, int p, Polynom f);

string outFpld(PolynomGF2_mY_7 pol, int d);

vector<int> blocksWith(int j1, int j2, vector<int> dfst, int v, int vv);

// Пересечение блоков, содержащихся в списке arr
vector<int> cens(vector<int> arr, bool dual, vector<int> dfst, int v, int k);

vector<int> id(int j, bool dual, vector<int> dfst, int v, int k);

string id_str(vector<int> idd);

vector<int> psiinv(int j, vector<int> dfst, int v, int k);

vector<int> dualhiinv(int j, vector<int> dfst, int v, int k);

vector<int> Algoritm1(int j1, int j2, vector<int> dfst, int v, int k, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block);

vector<string> Algoritm2(int j1, int j2, vector<int> dfst, int v, int k, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block);

string out_alg2(vector<string> out);

//Исключенные компьютеры
bool pcel(vector<int> pc, set<vector<int>> L_pc);

//Исключенные внутренние связи
bool blockpcel(vector<int> pc, set<vector<int>> L_blpc);

//Исключенные внешние связи
bool dblockpcel(vector<int> pc, set<vector<int>> L_dblpc);

//Реализованные блоки
bool blockexistance(int bl, vector<int> L_block);

//Реализованные дуальные блоки
bool dblockexistance(int dbl, vector<int> L_dblock);

// Пересечение блоков, содержащихся в списке arr
vector<int> cens(vector<int> arr, bool dual, vector<int> dfst, int v, int k);

vector<vector<int>> Algoritm3_normal(vector<int> j1, vector<int> j2, vector<int> dfst, int v, int k,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock);

vector<vector<int>> Algoritm3(vector<int> j1, vector<int> j2, vector<int> dfst, int v, int k, int l,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock);

string out_alg3_nat(vector<vector<int>> out);



