
//#include "stdafx.h"
#include "funCPG.h"
#include "funTD.h"
#include <iostream>
#include <iostream>
#include "./AAF/AAL/Polynom.h"
#include "./AAF/AAL/PolynomGF2_mY_7.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace AAL;
using namespace std;


// Функция формирования нулевого блока (разностного множества)
vector<int> diffset(int vv, Polynom f, int v, int d, PolynomGF2_mY_7 x, PolynomGF2_mY_7 mod)
{
	int num = 0;
	vector<int> dfst(vv);
	//dfst[0] = 0;
	PolynomGF2_mY_7 y("1", "0", "0", "0", "0", "0", "0", f.ToString());
	y.setModule(f);
	for (int i = 0; i < v; i++)
	{
		Polynom yy;
		if (d == 2)
			yy = y.getA2();
		if (d == 3)
			yy = y.getA3();
		if (yy.ToString() == "0")
		{
			dfst[num] = i % v;
			num++;
		}
		y = y.FullMul(y, x);
		if ((d == 2) && (y.getA3().ToString() != "0"))
		{
			PolynomGF2_mY_7 mod1 = mod;
			mod1.setA0(mod.getA0()*y.getA3());
			mod1.setA1(mod.getA1()*y.getA3());
			mod1.setA2(mod.getA2()*y.getA3());
			mod1.setA3(mod.getA3()*y.getA3());
			y = y + mod1;
		}
		if ((d == 3) && (y.getA4().ToString() != "0"))
		{
			PolynomGF2_mY_7 mod1 = mod;
			mod1.setA0(mod.getA0()*y.getA4());
			mod1.setA1(mod.getA1()*y.getA4());
			mod1.setA2(mod.getA2()*y.getA4());
			mod1.setA3(mod.getA3()*y.getA4());
			y = y + mod1;
		}
	}
	return dfst;
}

// Функция синтеза блока с номером s циклической проективной плоскости
vector<int> CPGBlockCreation(int s, vector<int> dfst, int v, int vv)
{
	vector<int> block(vv);
	int num = 0;
	for (const auto &item : dfst)
	{
		block[num] = (s + item) % v;
		num++;
	}
	return block;
}

// Функция синтеза блока с номером s циклической дуальной проективной плоскости
vector<int> DCPGBlockCreation(int s, vector<int> dfst, int v, int vv)
{
	vector<int> block(vv);
	int num = 0;
	for (const auto &item : dfst)
	{
		int it = (s - item) % v;
		if (it < 0)
			it = v + it;
		block[num] = it;
		num++;
	}
	return block;
}

// Умножение над GF(2^l) по модулю многочлена степени d
PolynomGF2_mY_7 ModMul(PolynomGF2_mY_7 a, PolynomGF2_mY_7 b, PolynomGF2_mY_7 modf, int d)
{
	if (a.getModPolynom() != b.getModPolynom() || a.getModule() != b.getModule())
		throw new Exception("модулярные многочлены должны быть равны");
	if (a.getModPolynom().isIrreducible() == false || b.getModPolynom().isIrreducible() == false)
		throw new Exception("f(x) - должен быть неприводим");
	PolynomGF2_mY_7 rez;
	Polynom buf, md;
	md = a.getModule();
	rez.setModPolynom(a.getModPolynom());
	rez.setModule(a.getModule());
	Polynom mas[13], a0, a1, a2, a3, a4, a5, a6, b0, b1, b2, b3, b4, b5, b6;
	Polynom m[7][7];
	a0 = a.getA0();
	a1 = a.getA1();
	a2 = a.getA2();
	a3 = a.getA3();
	a4 = a.getA4();
	a5 = a.getA5();
	a6 = a.getA6();
	b0 = b.getA0();
	b1 = b.getA1();
	b2 = b.getA2();
	b3 = b.getA3();
	b4 = b.getA4();
	b5 = b.getA5();
	b6 = b.getA6();
	mas[0] = m[0][0].ModMul(a0, b0, md);
	mas[1] = m[0][1].ModMul(a0, b1, md) + m[1][0].ModMul(a1, b0, md);
	mas[2] = m[0][2].ModMul(a0, b2, md) + m[1][1].ModMul(a1, b1, md) + m[2][0].ModMul(a2, b0, md);
	mas[3] = m[0][3].ModMul(a0, b3, md) + m[1][2].ModMul(a1, b2, md) + m[2][1].ModMul(a2, b1, md) + m[3][0].ModMul(a3, b0, md);
	mas[4] = m[0][4].ModMul(a0, b4, md) + m[1][3].ModMul(a1, b3, md) + m[2][2].ModMul(a2, b2, md) + m[3][1].ModMul(a3, b1, md) + m[4][0].ModMul(a4, b0, md);
	mas[5] = m[0][5].ModMul(a0, b5, md) + m[1][4].ModMul(a1, b4, md) + m[2][3].ModMul(a2, b3, md) + m[3][2].ModMul(a3, b2, md) + m[4][1].ModMul(a4, b1, md) + m[5][0].ModMul(a5, b0, md);
	mas[6] = m[0][6].ModMul(a0, b6, md) + m[1][5].ModMul(a1, b5, md) + m[2][4].ModMul(a2, b4, md) + m[3][3].ModMul(a3, b3, md) + m[4][2].ModMul(a4, b2, md) + m[5][1].ModMul(a5, b1, md) + m[6][0].ModMul(a6, b0, md);
	mas[7] = m[1][6].ModMul(a1, b6, md) + m[2][5].ModMul(a2, b5, md) + m[3][4].ModMul(a3, b4, md) + m[4][3].ModMul(a4, b3, md) + m[5][2].ModMul(a5, b2, md) + m[6][1].ModMul(a6, b1, md);
	mas[8] = m[2][6].ModMul(a2, b6, md) + m[3][5].ModMul(a3, b5, md) + m[4][4].ModMul(a4, b4, md) + m[5][3].ModMul(a5, b3, md) + m[6][2].ModMul(a6, b2, md);
	mas[9] = m[3][6].ModMul(a3, b6, md) + m[4][5].ModMul(a4, b5, md) + m[5][4].ModMul(a5, b4, md) + m[6][3].ModMul(a6, b3, md);
	mas[10] = m[4][6].ModMul(a4, b6, md) + m[5][5].ModMul(a5, b5, md) + m[6][4].ModMul(a6, b4, md);
	mas[11] = m[5][6].ModMul(a5, b6, md) + m[6][5].ModMul(a6, b5, md);
	mas[12] = m[6][6].ModMul(a6, b6, md);
	for (int i = 12; i >= d; i--)
	{
		PolynomGF2_mY_7 prom = modf;
		for (int j = 0; j < d + 1; j++)
		{
			prom.setByIndex(buf.ModMul(prom.getByIndex(j), mas[i], md), j);
		}
		for (int j = 0; j < d + 1; j++)
		{
			mas[i - j] = mas[i - j] + prom.getByIndex(d - j);
		}
	}
	for (int i = 0; i <= 6; i++)
	{
		rez.setByIndex(mas[i], i);
	}
	return rez;
}

// Возведение в степень над GF(2^l) по модулю многочлена степени d
PolynomGF2_mY_7 ModPow(PolynomGF2_mY_7 a, int n, PolynomGF2_mY_7 modf, int d, Polynom f)
{
	Integer nn = Integer(n);
	if (nn.isNegative())
		throw new Exception("Число n - отрицательное результат не определен");
	if (nn == 1)
	{
		return a;
	}
	if (a.getModPolynom().isIrreducible() == false)
		throw new Exception("f(x) - должен быть неприводим");
	PolynomGF2_mY_7 rez(a);
	PolynomGF2_mY_7 c, result("1", "0", "0", "0", "0", "0", "0", f.ToString());
	PolynomGF2_mY_7 one("1", "0", "0", "0", "0", "0", "0", f.ToString());
	Integer copy_n(nn);
	uint s = copy_n.getNumberBits();
	for (uint i = 0; i < s; i++)
	{
		c = ModMul(result, result, modf, d);
		result = c;
		if (copy_n.getBit(s - 1 - i))
			result = ModMul(result, a, modf, d);
		else
			result = ModMul(result, one, modf, d);
	}
	return result;
}

// Алгоритм Евклида
PolynomGF2_mY_7 Euclid(const PolynomGF2_mY_7 &a, PolynomGF2_mY_7 &b)
{
	if (a.isZero() && b.isZero())
		throw new Exception("a и b не могут быть оба равны 0");
	PolynomGF2_mY_7 u, v; // текущие значение
	PolynomGF2_mY_7 e;   // e = НОД(a,b)
	PolynomGF2_mY_7 r;   // остаток от деления
	PolynomGF2_mY_7 buf; // буфер обмена
	u = a;
	v = b;
	Polynom md = v.getModule();
	if (a.isZero())
	{
		u = v;
		v.setZero();
	}
	while (!v.isZero())
	{
		buf.Div(u, v, md, &r);
		u = v;
		v = r;
	}
	e = u;
	return e;
}

// Алгоритм2: Проверка неприводимости и примитивности многочлена степени n над полем GF(2^l)
int ALG2(int q, int n, Polynom fprim, PolynomGF2_mY_7 ff, vector<DecompositionMember> s, vector<DecompositionMember> dd,
	int d)
{
	PolynomGF2_mY_7 x("0", "1", "0", "0", "0", "0", "0", fprim.ToString()), buf;
	Polynom f = fprim;
	if (d != 1)
	{
		int k = s.size();
		PolynomGF2_mY_7 mod = ff;
		PolynomGF2_mY_7 ft = x;
		for (int t = 1; t < n; t++)
		{
			ft = ModPow(ft, q, ff, d, f);
			for (int i = 0; i < k; i++)
			{
				PolynomGF2_mY_7 pr = ft + x;
				PolynomGF2_mY_7 euc = Euclid(ff, pr);
				int deg = euc.deg();
				if (((t == n / s[i].getNumber()) & (ft == x)) || (deg != 0))
					return 0;
			}
		}
		PolynomGF2_mY_7 fn = ModPow(ft, q, ff, d, f);
		if (fn != x)
			return 0;
	}
	int r = dd.size();
	for (int i = 0; i < r; i++)
	{
		Integer ii = (pow(q, n) - 1) / dd[i].getNumber();
		string str = ii.ToString();
		int ch = atoi(str.c_str());
		PolynomGF2_mY_7 prom = ModPow(x, ch, ff, d, f);
		if (prom == PolynomGF2_mY_7("1", "0", "0", "0", "0", "0", "0", fprim.ToString()))
			return 1;
	}
	return 2;
}

// Генерация всех неприводимых многочленов над GF(2)
vector<Polynom> genAllIrreducibleF2l(int l, int p)
{
	vector<int> a(l + 1);
	string st = "";
	for (int i = 0; i < l; i++)
	{
		st = st + to_string(0);
	}
	a[l] = 1;
	st = st + to_string(1);
	Polynom f = Polynom(st);
	int N = pow(p, l) - 1;
	vector<Polynom> rez(pow(2, l));
	int num = 0;
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(l));
	vector<DecompositionMember> d(DecompositionManager::Instance().getPrimeDecomposition(N));
	if ((ALG1(p, l, f, s, d) == 1) || (ALG1(p, l, f, s, d) == 2))
	{
		rez[num] = f;
		num++;
	}
	while (NextSet(a, p - 1, l))
	{
		st = "";
		for (int i = 0; i < l + 1; i++)
			st = st + to_string(a[i]);
		f = Polynom(st);
		if ((ALG1(p, l, f, s, d) == 1) || (ALG1(p, l, f, s, d) == 2))
		{
			rez[num] = f;
			num++;
		}
	}
	return rez;
}

// Генерация неприводимого многочлена над GF(2)
Polynom genIrreducibleF2l(int l, int p)
{
	vector<int> a(l + 1);
	string st = "";
	for (int i = 0; i < l; i++)
	{
		st = st + to_string(0);
	}
	a[l] = 1;
	st = st + to_string(1);
	Polynom f = Polynom(st);
	int N = pow(p, l) - 1;
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(l));
	vector<DecompositionMember> d(DecompositionManager::Instance().getPrimeDecomposition(N));
	if ((ALG1(p, l, f, s, d) == 1) || (ALG1(p, l, f, s, d) == 2))
		return f;
	while (NextSet(a, p - 1, l))
	{
		st = "";
		for (int i = 0; i < l + 1; i++)
			st = st + to_string(a[i]);
		f = Polynom(st);
		if ((ALG1(p, l, f, s, d) == 1) || (ALG1(p, l, f, s, d) == 2))
			return f;
	}
	return Polynom();
}

// Генерация всех примитивных многочленов над GF(2)
vector<Polynom> genAllPrimitiveF2l(int l, int p)
{
	vector<int> a(l + 1);
	string st = "";
	for (int i = 0; i < l; i++)
	{
		st = st + to_string(0);
	}
	a[l] = 1;
	st = st + to_string(1);
	Polynom f = Polynom(st);
	int N = pow(p, l) - 1;
	vector<Polynom> rez(pow(2, l));
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(l));
	vector<DecompositionMember> d(DecompositionManager::Instance().getPrimeDecomposition(N));
	int num = 0;
	if (ALG1(p, l, f, s, d) == 2)
	{
		rez[num] = f;
		num++;
	}
	while (NextSet(a, p - 1, l))
	{
		st = "";
		for (int i = 0; i < l + 1; i++)
			st = st + to_string(a[i]);
		f = Polynom(st);
		if (ALG1(p, l, f, s, d) == 2)
		{
			rez[num] = f;
			num++;
		}
	}
	return rez;
}

// Генерация всех неприводимых многочленов над GF(2^l)
vector<PolynomGF2_mY_7> genAllIrreducibleF2ld(int d, int l, int p, Polynom f)
{
	vector<int> a(7);
	a[d] = 1;
	PolynomGF2_mY_7 mod;
	mod.setModule(f);
	for (int i = 0; i < 7; i++)
	{
		mod.setByIndex(Polynom(to_string(a[i])), i);
	}
	int q = pow(p, l);
	int N = pow(q, d) - 1;
	vector<PolynomGF2_mY_7> rez(pow(pow(2, l), d));
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(d));
	vector<DecompositionMember> dd(DecompositionManager::Instance().getPrimeDecomposition(N));
	int num = 0;
	if ((ALG2(q, d, f, mod, s, dd, d) == 1) || (ALG2(q, d, f, mod, s, dd, d) == 2))
	{
		rez[num] = mod;
		num++;
	}
	while (NextSet(a, q - 1, d))
	{
		for (int i = 0; i < 7; i++)
		{
			mod.setByIndex(razlP(a[i], l, p), i);
		}
		if ((ALG2(q, d, f, mod, s, dd, d) == 1) || (ALG2(q, d, f, mod, s, dd, d) == 2))
		{
			rez[num] = mod;
			num++;
		}
	}
	return rez;
}

// Генерация неприводимого многочлена над GF(2^l)
PolynomGF2_mY_7 genIrreducibleF2ld(int d, int l, int p, Polynom f)
{
	vector<int> a(7);
	a[d] = 1;
	PolynomGF2_mY_7 mod;
	for (int i = 0; i < 7; i++)
	{
		mod.setByIndex(Polynom(to_string(a[i])), i);
	}
	int q = pow(p, l);
	int N = pow(q, d) - 1;
	set<PolynomGF2_mY_7> rez;
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(d));
	vector<DecompositionMember> dd(DecompositionManager::Instance().getPrimeDecomposition(N));
	if ((ALG2(q, d, f, mod, s, dd, d) == 1) || (ALG2(q, d, f, mod, s, dd, d) == 2))
		return mod;
	while (NextSet(a, q - 1, d))
	{
		for (int i = 0; i < 7; i++)
		{
			mod.setByIndex(razlP(p, a[i], l), i);
		}
		if ((ALG2(q, d, f, mod, s, dd, d) == 1) || (ALG2(q, d, f, mod, s, dd, d) == 2))
			return mod;
	}
	return PolynomGF2_mY_7();
}

// Генерация всех примитивных многочленов над GF(2^l)
vector<PolynomGF2_mY_7> genAllPrimitiveF2ld(int d, int l, int p, Polynom f)
{
	vector<int> a(7);
	a[d] = 1;
	PolynomGF2_mY_7 mod;
	mod.setModule(f);
	for (int i = 0; i < 7; i++)
	{
		mod.setByIndex(Polynom(to_string(a[i])), i);
	}
	int q = pow(p, l);
	int N = pow(q, d) - 1;
	vector<PolynomGF2_mY_7> rez(pow(pow(2, l), d));
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(d));
	vector<DecompositionMember> dd(DecompositionManager::Instance().getPrimeDecomposition(N));
	int num = 0;
	if (ALG2(q, d, f, mod, s, dd, d) == 2)
	{
		rez[num] = mod;
		num++;
	}
	while (NextSet(a, q - 1, d))
	{
		for (int i = 0; i < 7; i++)
		{
			mod.setByIndex(razlP(p, a[i], l), i);
		}
		if (ALG2(q, d, f, mod, s, dd, d) == 2)
		{
			rez[num] = mod;
			num++;
		}
	}
	return rez;
}

// Генерация примитивного многочлена над GF(2^l)
PolynomGF2_mY_7 genPrimitiveF2ld(int d, int l, int p, Polynom f)
{
	vector<int> a(7);
	a[d] = 1;
	PolynomGF2_mY_7 mod;
	mod.setModule(f);
	for (int i = 0; i < 7; i++)
	{
		mod.setByIndex(Polynom(to_string(a[i])), i);
	}
	int q = pow(p, l);
	int N = pow(q, d) - 1;
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(d));
	vector<DecompositionMember> dd(DecompositionManager::Instance().getPrimeDecomposition(N));
	if (ALG2(q, d, f, mod, s, dd, d) == 2)
		return mod;
	while (NextSet(a, q - 1, d))
	{
		for (int i = 0; i < 7; i++)
		{
			mod.setByIndex(razlP(p, a[i], l), i);
		}
		if (ALG2(q, d, f, mod, s, dd, d) == 2)
			return mod;
	}
	return PolynomGF2_mY_7();
}

string outFpld(PolynomGF2_mY_7 pol, int d)
{
	string rez = "";
	for (int i = d ; i >=0 ; i--)
	{
		rez = rez + pol.getByIndex(i).ToString()+" ";
	}
	return rez;
}

vector<int> blocksWith(int j1, int j2, vector<int> dfst, int v, int vv)
{
	vector<int> dual1, dual2, commonblocks;
	dual1 = DCPGBlockCreation(j1, dfst, v, vv);
	sort(dual1.begin(), dual1.end());
	dual2 = DCPGBlockCreation(j2, dfst, v, vv);
	sort(dual2.begin(), dual2.end());
	set_intersection(dual1.begin(), dual1.end(), dual2.begin(), dual2.end(), back_inserter(commonblocks));
	return commonblocks;
}

vector<int> id(int j, bool dual, vector<int> dfst, int v, int k)
{
	vector<int> vec(1 + k);
	vec[0] = j;
	int s = j;
	vector<int> bl;
	if (dual == false)
		bl = CPGBlockCreation(s, dfst, v, k);
	else
		bl = DCPGBlockCreation(s, dfst, v, k);
	for (int i = 0; i < k; i++)
	{
		vec[i + 1] = bl[i];
	}
	return(vec);
}

string id_str(vector<int> idd)
{
	string str = to_string(idd[0]) + ",[";
	for (int i = 0; i < idd.size() - 1; i++)
	{
		str = str + to_string(idd[i+1]) + ",";
	}
	str.erase(str.size() - 1);
	str = str + "]";
	return str;
}

vector<int> psiinv(int j, vector<int> dfst, int v, int k)
{
		return CPGBlockCreation(j, dfst, v, k);
}

vector<int> dualhiinv(int j, vector<int> dfst, int v, int k)
{
	return DCPGBlockCreation(j, dfst, v, k);
}

vector<int> Algoritm1(int j1, int j2, vector<int> dfst, int v, int k, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block)
{
	vector<int> cc(2);
	cc[0] = id(j1, false, dfst, v, k)[0];
	cc[1] = id(j2, false, dfst, v, k)[0];
	vector<int> keys = cens(cc, false, dfst, v, k);
	for (const auto &it : keys)
	{
		if ((!kel(it, L_key)) && (!bkel(j1, it, L_blockkey)) && (!bkel(j2, it, L_blockkey)) && (!bbel(j1, j2, L_blockblock)))
		{
			vector<int> rez(1);
			rez[0] = it;
			return rez;
		}
	}
	vector<int>keysofj1 = psiinv(j1, dfst, v,  k);
	vector<int>keysofj2 = psiinv(j2, dfst, v, k);
	for (const auto &it1 : keysofj1)
	{
		for (const auto &it2 : keysofj2)
		{
			if (it1 == it2)
			{
				if ((!kel(it1, L_key)) && (!bkel(j1, it1, L_blockkey)) && (!bkel(j2, it1, L_blockkey)))
				{
					int ckey = it1;
					vector<int>commonblocks = dualhiinv(ckey, dfst, v, k);
					for (const auto &it3 : commonblocks)
					{
						if ((!bkel(it3, ckey, L_blockkey)) && (!(it3 == j1)) && (!(it3 == j2)) && ((blockexistence(it3, L_block))) && (!bbel(j1, it3, L_blockblock)) && (!bbel(j2, it3, L_blockblock)))
						{
							vector<int> rez(2);
							rez[0] = ckey;
							rez[1] = it3;
							return rez;
						}
					}
				}
			}
		}
	}
	for (const auto &it1 : keysofj1)
	{
		for (const auto &it2 : keysofj2)
		{
			if ((it1 != it2) && (!bkel(j1, it1, L_blockkey)) && (!bkel(j2, it2, L_blockkey)) && (!kel(it1, L_key)) && (!kel(it2, L_key)))
			{
				cc[0] = id(it1, false, dfst, v, k)[0];
				cc[1] = id(it2, false, dfst, v, k)[0];
				vector<int>commonblocks = cens(cc, true, dfst, v, k);
				if (commonblocks.size() != 0)
				{
					for (const auto &it3 : commonblocks)
					{
						if ((!bkel(it3, it1, L_blockkey)) && (!bkel(it3, it2, L_blockkey)) && (!bbel(it3, it2, L_blockblock)) && (!bbel(it2, it3, L_blockblock)) && (!(it3 == j1)) && (!(it3 == j2)) && (!bbel(j1, it3, L_blockblock)) && (!bbel(it3, j1, L_blockblock)) && (!bbel(j2, it3, L_blockblock)) && (!bbel(it3, j2, L_blockblock)) && (blockexistence(it3, L_block)))
						{
							vector<int> rez(5);
							rez[0] = j1;
							rez[1] = it1;
							rez[2] = it3;
							rez[3] = it2;
							rez[4] = j2;
							return rez;
						}
					}
				}
			}
		}
	}
	vector<int> rez(0);
	return rez;
}

string out_alg1_en(int j1, int j2, vector<int> out)
{
	string res;
	if (out.size() == 1)
	{
		res = "Key of direct connection of nodes " + to_string(j1) + " and " + to_string(j2)
			+ " : " + to_string(out[0]);
	}
	else
		if (out.size() == 2)
		{
			res = "Node connection key " + to_string(j1) + " and " + to_string(j2)
				+ " through node " + to_string(out[1]) + " : " + to_string(out[0]);
		}
		else
			if (out.size() == 5)
			{
				res = "Node " + to_string(out[0]) + " through node " + to_string(out[1]) +
					" connected to node " + to_string(out[2]) + ", that is connected with a key " + to_string(out[3]) +
					" to node " + to_string(out[4]);
			}
			else
				res = "There is no connection (direct or through one intermediary) between the nodes " + to_string(j1) +
				" and " + to_string(j2) + " !";
	return res + "\n\n";
}


vector<string> Algoritm2(int j1, int j2, vector<int> dfst, int v, int k, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block)
{
	int id1 = id(j1, false, dfst, v, k)[0];
	int id2 = id(j2, false, dfst, v, k)[0];
	vector<int> cc(2);
	vector<string> rez(3);
	rez[0] = { "" };
	rez[1] = { "" };
	rez[2] = { "" };
	cc[0] = id1;
	cc[1] = id2;
	vector<int>comelementnumbers = cens(cc, false, dfst, v, k);
	for (const auto &it : comelementnumbers)
	{
		if ((!kel(it, L_key)) && (!bkel(id1, it, L_blockkey)) && (!bkel(id2, it, L_blockkey)) && (!bbel(id1, j2, L_blockkey)))
		{
			rez[0] = id_str(id(j1, false, dfst, v, k));
			rez[1] = id_str(id(j2, false, dfst, v, k));
			return rez;
		}
	}
	for (int j = 0; j < v; j++)
	{
		if ((j != j1) && (j != j2) && (blockexistence(j, L_block)))
		{
			int id3 = id(j, false, dfst, v, k)[0];
			cc[0] = id1;
			cc[1] = id3;
			vector<int> cens1 = cens(cc, false, dfst, v, k);
			cc[0] = id2;
			cc[1] = id3;
			vector<int> cens2 = cens(cc, false, dfst, v, k);
			if ((cens1.size() != 0) && (cens2.size() != 0))
			{
				for (const auto &k1 : cens1)
				{
					if ((!bkel(j, k1, L_blockkey)) && (!bkel(j1, k1, L_blockkey)) && (!kel(k1, L_key)))
					{
						for (const auto &k2 : cens2)
						{
							if ((!bkel(j, k2, L_blockkey)) && (!bkel(j2, k2, L_blockkey)) && (!kel(k2, L_key)) && (!bbel(j2, id3, L_blockblock)) && (!bbel(id3, j2, L_blockblock)) && (!bbel(j1, id3, L_blockblock)) && (!bbel(id3, j1, L_blockblock)))
							{
								rez[0] = id_str(id(id1, false, dfst, v, k));
								rez[1] = id_str(id(id2, false, dfst, v, k));
								rez[2] = id_str(id(id3, false, dfst, v, k));
								return rez;
							}
						}
					}
				}
			}
		}
	}
	return rez;
}

string out_alg2(vector<string> out)
{
	string res = "[ ";
	res += "[";
	res += out[0];
	res += "], [";
	res += out[1];
	res += "], [";
	res += out[2];
	res += "] ]\n\n";
	return res;
}


//Исключенные компьютеры
bool pcel(vector<int> pc, set<vector<int>> L_pc)
{
	if (L_pc.find(pc) != L_pc.end())
		return true;
	else
		return false;
}

//Исключенные внутренние связи
bool blockpcel(vector<int> pc, set<vector<int>> L_blpc)
{
	if (L_blpc.find(pc) != L_blpc.end())
		return true;
	else
		return false;
}

//Исключенные внешние связи
bool dblockpcel(vector<int> pc, set<vector<int>> L_dblpc)
{
	if (L_dblpc.find(pc) != L_dblpc.end())
		return true;
	else
		return false;
}

//Реализованные блоки
bool blockexistance(int bl, vector<int> L_block)
{
	sort(L_block.begin(), L_block.end());
	return binary_search(L_block.begin(), L_block.end(), bl);
}

//Реализованные дуальные блоки
bool dblockexistance(int dbl, vector<int> L_dblock)
{
	sort(L_dblock.begin(), L_dblock.end());
	return binary_search(L_dblock.begin(), L_dblock.end(), dbl);
}

// Пересечение блоков, содержащихся в списке arr
vector<int> cens(vector<int> arr, bool dual, vector<int> dfst, int v, int k)
{
	if (arr.size() == 0)
	{
		return {};
	}
	for (int i = 0; i < arr.size(); i++)
	{
		if ((arr[i] < 0))
		{
			return {};
		}
	}
	int s = arr[0];
	set<int> rez;
	set<int> buf;
	if (dual == false)
	{
		vector<int> bl = CPGBlockCreation(s, dfst, v, k);
		for (const auto &item : bl)
		{
			rez.insert(item);
		}
		//rez = Block();
	}
	else
	{
		vector<int> bl = DCPGBlockCreation(s, dfst, v, k);
		for (const auto &item : bl)
		{
			rez.insert(item);
		}
		//rez = dualBlock();
	}
	for (int i = 1; i < arr.size(); i++)
	{
		buf = rez;
		rez.clear();
		s = arr[i];
		set<int> bl;
		if (dual == false)
		{
			vector<int> blp = CPGBlockCreation(s, dfst, v, k);
			for (const auto &item : blp)
			{
				bl.insert(item);
			}
			//bl = Block();
		}
		else
		{
			vector<int> blp = DCPGBlockCreation(s, dfst, v, k);
			for (const auto &item : blp)
			{
				bl.insert(item);
			}
			//bl = dualBlock();
		}
		for (const auto &item : buf)
		{
			if (bl.find(item) != bl.end())
			{
				rez.insert(item);
			}
		}
	}
	vector<int> output(rez.size());
	copy(rez.begin(), rez.end(), output.begin());
	return output;
}

vector<vector<int>> Algoritm3_normal(vector<int> j1, vector<int> j2, vector<int> dfst, int v, int k, 
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock)
{
	vector<vector<int>> rez;
	rez = vector<vector<int>>(0);
	if (pcel(j1, L_pc) || pcel(j2, L_pc))
	{
		return rez;
	}
	if ((j1[0] == j2[0]) && (!blockpcel(j1, L_blpc)) && (!blockpcel(j2, L_blpc)) && blockexistance(j1[0], L_block))
	{
		rez = vector<vector<int>>(2);
		rez[0] = j1;
		rez[1] = j2;
		return rez;
	}
	if ((j1[1] == j2[1]) && (!dblockpcel(j1, L_dblpc)) && (!dblockpcel(j2, L_dblpc)) && dblockexistance(j2[1], L_dblock) 
		&& blockexistance(j1[0], L_block) && blockexistance(j2[0], L_block))
	{
		rez = vector<vector<int>>(2);
		rez[0] = j1;
		rez[1] = j2;
		return rez;
	}
	vector<int> cc(2);
	cc[0] = j1[0];
	cc[1] = j2[0];
	vector<int> cens0 = cens(cc, false, dfst, v, k);
	for (const auto &el : cens0)
	{
		if (dblockexistance(el, L_dblock))
		{
			vector<int> prom1(2);
			prom1[0] = j2[0];
			prom1[1] = el;
			vector<int> prom2(2);
			prom2[0] = j1[0];
			prom2[1] = el;
			if ((el == j1[1]) && (!pcel(prom1, L_pc)) && (!blockpcel(j1, L_blpc)) && (!dblockpcel(j1, L_dblpc))
				&& (!dblockpcel(prom1, L_dblpc)) && (!blockpcel(prom1, L_blpc)) && (!blockpcel(j2, L_blpc)) 
				&& (blockexistance(j1[0], L_block)) && (blockexistance(j2[0], L_block)))
			{
				rez = vector<vector<int>>(3);
				rez[0] = j1;
				rez[1] = prom1;
				rez[2] = j2;
				return rez;
			}
			else if ((el == j2[1]) && (!pcel(prom2, L_pc)) && (!blockpcel(j1, L_blpc)) && (!blockpcel(prom2, L_blpc))
				&& (!dblockpcel(prom2, L_dblpc)) && (!dblockpcel(j2, L_dblpc)) && (!blockpcel(j2, L_blpc))
				&& (blockexistance(j1[0], L_block)) && (blockexistance(j2[0], L_block)))
			{
				rez = vector<vector<int>>(3);
				rez[0] = j1;
				rez[1] = prom2;
				rez[2] = j2;
				return rez;
			}
			else if ((!pcel(prom2, L_pc)) && (!pcel(prom1, L_pc)) && (!blockpcel(j1, L_blpc)) && (!blockpcel(prom2, L_blpc))
				&& (!dblockpcel(prom2, L_dblpc)) && (!dblockpcel(prom1, L_dblpc)) && (!blockpcel(prom1, L_blpc)) && (!blockpcel(j2, L_blpc))
				&& (blockexistance(j1[0], L_block)) && (blockexistance(j2[0], L_block)))
			{
				if (prom1 == prom2)
				{
					rez = vector<vector<int>>(3);
					rez[0] = j1;
					rez[1] = prom2;
					rez[2] = j2;
					return rez;
				}
				rez = vector<vector<int>>(4);
				rez[0] = j1;
				rez[1] = prom2;
				rez[2] = prom1;
				rez[3] = j2;
				return rez;
			}
		}

	}

	return rez;
}


vector<vector<int>> Algoritm3(vector<int> j1, vector<int> j2, vector<int> dfst, int v, int k, int l,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock)
{
	vector<vector<int>> rez;
	rez = vector<vector<int>>(0);
	if (pcel(j1, L_pc) || pcel(j2, L_pc) || (!blockexistance(j1[0], L_block)) || (!blockexistance(j2[0], L_block)))
	{
		return rez;
	}
	rez = Algoritm3_normal(j1, j2, dfst, v, k, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
	if (rez.size() != 0)
	{
		return rez;
	}
	vector<int> cc(2);
	vector<int> bl1 = CPGBlockCreation(j1[0], dfst, v, k);
	vector<int> bl2 = CPGBlockCreation(j2[0], dfst, v, k);
	for (int el1 = 0; el1 < k; el1++)
	{
		for (int el2 = 0; el2 < k; el2++)
		{
			cc[0] = bl1[el1];
			cc[1] = bl1[el2];
			vector<int> cens1 = cens(cc, true, dfst, v, k);
			for (int j = 0; j < cens1.size(); j++)
			{
				if ((blockexistance(j, L_block)))
				{
					vector<int> prom1(2);
					prom1[0] = cens1[j];
					prom1[1] = bl1[el1];
					vector<int> prom2(2);
					prom2[0] = cens1[j];
					prom2[1] = bl1[el2];
					vector<vector<int>> rez1 = Algoritm3_normal(j1, prom1, dfst, v, k, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez2 = Algoritm3_normal(prom2, j2, dfst, v, k, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez3(0);
					if (prom1 != prom2)
						rez3 = Algoritm3_normal(prom1, prom2, dfst, v, k, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					int s1 = rez1.size();
					int s2 = rez2.size();
					int s3 = rez3.size();
					if ((s1 != 0) && (s2 != 0) && ((s3 != 0) || (prom1 == prom2)))
					{
						int ss = s1 + s2 + s3 - 1;
						if (s3 != 0)
							ss--;
						int num = 0;
						rez = vector<vector<int>>(ss);
						for (int i = 0; i < s1; i++)
						{
							rez[num] = rez1[i];
							num++;
						}
						for (int i = 1; i < s3; i++)
						{
							rez[num] = rez3[i];
							num++;
						}
						for (int i = 1; i < s2; i++)
						{
							rez[num] = rez2[i];
							num++;
						}
						return rez;
					}
				}
			}
		}
	}
	return rez;
}


string out_alg3_nat(vector<vector<int>> out)
{
	string res = "";
	int sz = out.size();
	vector<int> comp;
	if (sz > 1)
	{
		for (int i = 0; i < sz - 1; i++)
		{
			comp = out[i];
			res = res + "(" + to_string(comp[0]) + "," + to_string(comp[1]) + ")->";
		}
		comp = out[sz - 1];
		res = res + "(" + to_string(comp[0]) + "," + to_string(comp[1]) + ")";
	}
	else
		res = "Связи между указанными компьютерами нет!";
	return res;
}

string out_alg3_nat_en(vector<vector<int>> out)
{
	string res = "";
	int sz = out.size();
	vector<int> comp;
	if (sz > 1)
	{
		for (int i = 0; i < sz - 1; i++)
		{
			comp = out[i];
			res = res + "(" + to_string(comp[0]) + "," + to_string(comp[1]) + ")->";
		}
		comp = out[sz - 1];
		res = res + "(" + to_string(comp[0]) + "," + to_string(comp[1]) + ")";
	}
	else
		res = "There is no connection between the specified computers!";
	return res;
}