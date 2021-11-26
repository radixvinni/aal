#include "funAPG.h"
#include "funTD.h"
#include "funCPG.h"
#include <iostream>
#include "./AAF/AAL/Polynom.h"
#include "./AAF/AAL/PolynomGF2_m_4.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include <set>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>

using namespace AAL;
using namespace std;


Polynom Setf(int l)
{
	Polynom f, bf;
	if (l > 1)
	{
		f = bf.GenerateIrreduciblePrimitivity(3, 3, l);
	}
	else
	{
		Polynom prtst("11");
		f = prtst;
	}
	return f;
}

// Возведение образующего элемента в нужную степень
Polynom xPow(int i, Polynom f)
{
	Polynom s("0");
	Polynom x("01");
	if (i != 0)
	{
		Polynom r;
		Integer ii = Integer(i);
		s = r.PowGF2_n(x, ii, f);
	}
	return s;
}

// Определение индекса элемента
int ind(Polynom ell, Polynom f)
{
	int i = 0;
	if (ell.ToString() != "0")
	{
		i = 1;
		while (xPow(i, f) != ell)
		{
			i++;
		}
	}
	return i;
}

// Получение номера пси элемента блока
int Psi(PolynomGF2_m_4 el, Polynom f, int d, int n)
{
	int ret = 0;
	bool flag = false;
	Integer nn = Integer(n);
	Integer dd = Integer(d);
	Integer buf;
	for (int i = 0; i <= d; i++)
	{
		if (!flag && i == d)
		{
			ret = 0;
		}
		if (!flag && el.getByIndex(i).ToString() == "1")
		{
			flag = true;
			for (int j = 0; j < d - i; j++)
			{
				Integer jj = Integer(j);
				Integer rt = Integer(ret);
				rt += buf.Pow(nn, jj);
				ret = stoi(rt.ToString());
			}
		}
		else
		{
			if (el.getByIndex(i).ToString() != "0")
			{
				Integer ii = Integer(i);
				Integer rt = Integer(ret);
				rt = rt + buf.Pow(nn, dd - ii) * ind(el.getByIndex(i), f);
				ret = stoi(rt.ToString());
			}
		}
	}
	return ret;
}

// Преобразование целого неотрицательного числа в элемент пси при d == 2
PolynomGF2_m_4 PsiInverse(int N, Polynom f, int n)
{
	Polynom t1("1");
	PolynomGF2_m_4 ret;
	ret.setZero();
	if (N == 0)
	{
		ret.setByIndex(t1, 2);
	}
	else
	{
		if (N <= n)
		{
			ret.setByIndex(t1, 1);
			ret.setByIndex(xPow(N - 1, f), 2);
		}
		else
		{
			int M = N - n - 1;
			int M0 = M % n;
			int M1;
			M1 = M / n;
			ret.setByIndex(t1, 0);
			ret.setByIndex(xPow(M1, f), 1);
			ret.setByIndex(xPow(M0, f), 2);
		}
	}
	return ret;
}

// Преобразование целого неотрицательного числа в элемент пси при d == 3
PolynomGF2_m_4 Psi3Inverse(int N, Polynom f, int n, int k)
{
	Polynom t1("1");
	PolynomGF2_m_4 ret;
	ret.setZero();
	if (N == 0)
	{
		ret.setByIndex(t1, 3);
	}
	else
	{
		if (N <= n)
		{
			ret.setByIndex(t1, 2);
			ret.setByIndex(xPow(N - 1, f), 3);
		}
		else
		{
			if (N < k)
			{
				int M = N - n - 1;
				int M0 = M % n;
				int M1 = M / n;
				ret.setByIndex(t1, 1);
				ret.setByIndex(xPow(M1, f), 2);
				ret.setByIndex(xPow(M0, f), 3);
			}
			else
			{
				int M = N - k;
				int M0 = M % n;
				int M1 = (M - M0) % (n * n);
				int M2 = M / (n * n);
				ret.setByIndex(t1, 0);
				ret.setByIndex(xPow(M2, f), 1);
				ret.setByIndex(xPow(M1, f), 2);
				ret.setByIndex(xPow(M0, f), 3);
			}
		}
	}
	return ret;
}

PolynomGF2_m_4 vectorsum(PolynomGF2_m_4 a, PolynomGF2_m_4 b, int d, Polynom f)
{
	Polynom bf;
	PolynomGF2_m_4 ret;
	ret.setZero();
	for (int i = 0; i <= d; i++)
	{
		Polynom ra = a.getByIndex(i);
		Polynom rb = b.getByIndex(i);
		ret.setByIndex(bf.AddInGF2_n(ra, rb, f), i);
	}
	return ret;
}

PolynomGF2_m_4 vectorproduct(PolynomGF2_m_4 a, PolynomGF2_m_4 b, int d, Polynom f)
{
	Polynom bf;
	PolynomGF2_m_4 ret;
	ret.setZero();
	for (int i = 0; i <= d; i++)
	{
		Polynom ra = a.getByIndex(i);
		Polynom rb = b.getByIndex(i);
		ret.setByIndex(bf.MulGF2_n(ra, rb, f), i);
	}
	return ret;
}

PolynomGF2_m_4 vectorsub(PolynomGF2_m_4 a, PolynomGF2_m_4 b, int d, Polynom f)
{
	Polynom bf;
	PolynomGF2_m_4 ret;
	ret.setZero();
	for (int i = 0; i <= d; i++)
	{
		Polynom ra = a.getByIndex(i);
		Polynom rb = b.getByIndex(i);
		ret.setByIndex(bf.SubInGF2_n(ra, rb, f), i);
	}
	return ret;
}

PolynomGF2_m_4 mulbyscalar(PolynomGF2_m_4 a, Polynom b, int d, Polynom f)
{
	Polynom bf;
	PolynomGF2_m_4 ret;
	ret.setZero();
	for (int i = 0; i <= d; i++)
	{
		Polynom r = a.getByIndex(i);
		ret.setByIndex(bf.MulGF2_n(r, b, f), i);
	}
	return ret;
}

vector<int> ProjectivePlaneBlokCreation(int s, int n, int d, Polynom f)
{
	vector<int> B;
	if (s <= n)
	{
		B.push_back(0);
		B.push_back(s * n + 1);
	}
	else
	{
		B.push_back((s - 1) / n);
		B.push_back((s - 1) % n + n + 1);
	}
	for (int i = 1; i < n; i++)
	{
		B.push_back(Psi(vectorsum(mulbyscalar(PsiInverse(B[0], f, n), xPow(i, f), d, f), PsiInverse(B[1], f, n), d, f), f, d, n));
	}
	return B;
}

int newelement(int r, int s, int n, int d, Polynom f)
{
	int res = -1;
	if (r == 0)
	{
		PolynomGF2_m_4 xpt;
		xpt.setZero();
		for (int t = 0; t < n; t++)
		{
			xpt.setByIndex(xPow(t, f), 2);
			PolynomGF2_m_4 vsub = vectorsub(PsiInverse(s, f, n), xpt, d, f);
			int newel = Psi(vsub, f, d, n);
			if (newel % n == 1)
			{
				res = newel / n;
			}
		}
	}
	else
	{
		for (int t = 0; t < n; t++)
		{
			PolynomGF2_m_4 vsub = vectorsub(PsiInverse(s, f, n), mulbyscalar(PsiInverse(r, f, n), xPow(t, f), d, f), d, f);
			int newel = Psi(vsub, f, d, n);
			if (newel <= 2 * n)
			{
				res = (r - 1) * n + newel;
			}
		}
	}
	return res;
}

vector<int> DualProjectivePlaneBlokCreation(int s, int n, int d, Polynom f)
{
	vector<int> D;
	if (s <= n)
	{
		D.push_back(0);
		for (int t = 1; t <= n; t++)
		{
			D.push_back(s * n + t);
		}
	}
	else
	{
		for (int r = 0; r <= n; r++)
		{
			D.push_back(newelement(r, s, n, d, f));
		}
	}
	return D;
}

vector<int> ProjectiveGeometryBlokCreation(int s, int n, int k, int d, Polynom f)
{
	vector<int> B;
	int n2;
	if (s < k)
	{
		B.push_back(0);
		B.push_back(1 + ((s - 1) / n) * n);
	}
	else
	{
		int n1 = (s - n - 1) / (n * n);
		n2 = (s - 1) / n - (n1 - 1) * n;
		B.push_back(n1);
		B.push_back(n2);
	}
	for (int i = 1; i < n; i++)
	{
		B.push_back(Psi(vectorsum(mulbyscalar(Psi3Inverse(B[0], f, n, k), xPow(i, f), d, f), Psi3Inverse(B[1], f, n, k), d, f), f, d, n));
	}
	if (s <= n)
	{
		B.push_back(s * n * n + n + 1);
	}
	else {
		if (s < k)
		{
			B.push_back(n * n + ((s - 1) % n + 1) * n + 1);
		}
		else
		{
			B.push_back(s - (n2 - n - 1) * n);
		}
	}
	for (int i = 0; i <= n; i++)
	{
		for (int j = 1; j < n; j++)
		{
			B.push_back(Psi(vectorsum(mulbyscalar(Psi3Inverse(B[i], f, n, k), xPow(j, f), d, f), Psi3Inverse(B[n + 1], f, n, k), d, f), f, d, n));
		}
	}
	return B;
}

vector<int> NumsOfBlocksWithBas(int el, int n, int k)
{
	vector<int> ret;
	int n_sqr = n * n;
	if (el == 0)
	{
		for (int i = 0; i < k; i++)
		{
			ret.push_back(i);
		}
	}
	else if (el == 1)
	{
		for (int i = 0; i < n + 1; i++)
		{
			ret.push_back(i);
		}
		for (int i = k; i < 2 * n_sqr + n + 1; i++)
		{
			ret.push_back(i);
		}
	}
	else if (el <= n)
	{
		for (int i = el * n_sqr + n + 1; i < (el + 1) * n_sqr + n + 1; i++)
		{
			ret.push_back(i);
		}
	}
	else if (el == n + 1)
	{
		for (int i = n + 1; i < 2 * n + 1; i++)
		{
			ret.push_back(i);
		}
		for (int j = 1; j < n + 1; j++)
		{
			for (int i = j * n_sqr + n + 1; i < j * n_sqr + 2 * n + 1; i++)
			{
				ret.push_back(i);
			}
		}
	}
	else if (el <= 2 * n)
	{
		for (int j = 1; j < n + 1; j++)
		{
			for (int i = j * n_sqr + (el - n) * n + 1; i < j * n_sqr + (el - n + 1) * n + 1; i++)
			{
				ret.push_back(i);
			}
		}
	}
	else if (el <= n_sqr + 1)
	{
		for (int i = ((el - 1) / n) * n + 1; i < ((el - 1) / n) * n + n + 1; i++)
		{
			ret.push_back(i);
		}
	}
	return ret;
}

vector<int> InterOfTwoBasEl(int el1, int el2, int n, int k)
{
	vector<int> v1 = NumsOfBlocksWithBas(el1, n, k);
	vector<int> v2 = NumsOfBlocksWithBas(el2, n, k);
	vector<int> ret;
	for (int i = 0; i < v1.size(); i++)
	{
		if (find(v2.begin(), v2.end(), v1[i]) != v2.end())
		{
			ret.push_back(v1[i]);
		}
	}
	return ret;
}

int Predic(PolynomGF2_m_4 el, int b1, int b2, int n, int k, int d, Polynom f)
{
	vector<int> nb = InterOfTwoBasEl(b1, b2, n, k);
	int ret = -1;
	PolynomGF2_m_4 n3;
	Integer bbf, bfb;
	for (int i = 0; i < nb.size(); i++)
	{
		if (nb[i] <= n)
		{
			n3 = Psi3Inverse(1 + (nb[i]) * n * n + n, f, n, k);
		}
		else if (nb[i] < n * n + n + 1)
		{
			n3 = Psi3Inverse(1 + n * n + ((nb[i] - 1) % n + 1) * n, f, n, k);
		}
		else if (nb[i] < n * n * n + n * n + n + 1)
		{
			n3 = Psi3Inverse(nb[i] - ((nb[i] - 1) / n - ((nb[i] - n - 1) / (n*n) - 1) * n - n - 1) * n, f, n, k);
		}
		for (int ii = 0; ii < n; ii++)
		{
			bool flag = false;
			for (int iii = 0; iii < n; iii++)
			{
				PolynomGF2_m_4 prom = vectorsum(mulbyscalar(Psi3Inverse(b1, f, n, k), xPow(ii, f), d, f), mulbyscalar(Psi3Inverse(b2, f, n, k), xPow(iii, f), d, f), d, f);
				if (vectorsum(el, prom, d, f) == n3)
				{
					ret = nb[i];
					flag = true;
					break;
				}
			}
			if (flag) { break; }
		}
	}
	return ret;
}

vector<int> NotZero(int b1, int b2, int s, int n, int k, int d, Polynom f)
{
	vector<int> ret;
	PolynomGF2_m_4 sp = Psi3Inverse(s, f, n, k);
	for (int i = 1; i < n; i++)
	{
		for (int ii = 1; ii < n; ii++)
		{
			if (vectorsum(mulbyscalar(Psi3Inverse(b1, f, n, k), xPow(i, f), d, f), mulbyscalar(Psi3Inverse(b2, f, n, k), xPow(ii, f), d, f), d, f) == sp)
			{
				ret = InterOfTwoBasEl(b1, b2, n, k);
			}
		}
	}
	return ret;
}

vector<int> DualProjectiveGeometryBlokCreation(int s, int n, int k, int d, Polynom f)
{
	vector<int> D;
	PolynomGF2_m_4 sp = Psi3Inverse(s, f, n, k);
	if (s < k)
	{
		vector<int> pr = NumsOfBlocksWithBas(s, n, k);
		if (!pr.empty())
		{
			for (const auto& i : pr)
			{
				D.push_back(i);
			}
		}
		if (D.size() < k)
		{
			vector<int> b2;
			b2.push_back(1);
			for (int i = 1; i <= n; i++)
			{
				b2.push_back(n * i + 1);
			}
			for (int i = 0; i < b2.size(); i++)
			{
				pr = NotZero(0, b2[i], s, n, k, d, f);
				if (!pr.empty())
				{
					for (int j = 0; j < pr.size(); j++)
					{
						if (find(D.begin(), D.end(), pr[j]) == D.end())
						{
							D.push_back(pr[j]);
						}
					}
				}
			}
			b2.clear();
			for (int i = 1; i <= n; i++)
			{
				b2.push_back(n + i);
			}
			for (int i = 1; i <= n; i++)
			{
				for (int ii = 0; ii < b2.size(); ii++)
				{
					pr = NotZero(i, b2[ii], s, n, k, d, f);
					if (!pr.empty())
					{
						for (int j = 0; j < pr.size(); j++)
						{
							if (find(D.begin(), D.end(), pr[j]) == D.end())
							{
								D.push_back(pr[j]);
							}
						}
					}
				}
			}
		}
		if (D.size() < k)
		{
			D.push_back(0);
		}
	}
	else
	{
		vector<int> b2;
		b2.push_back(1);
		for (int i = 1; i <= n; i++)
		{
			b2.push_back(n * i + 1);
		}
		for (int i = 0; i < b2.size(); i++)
		{
			D.push_back(Predic(sp, 0, b2[i], n, k, d, f));
		}
		b2.clear();
		for (int i = 1; i <= n; i++)
		{
			b2.push_back(n + i);
		}
		for (int i = 1; i <= n; i++)
		{
			for (int ii = 0; ii < b2.size(); ii++)
			{
				D.push_back(Predic(sp, i, b2[ii], n, k, d, f));
			}
		}
	}
	return D;
}

vector<int> AcicleBlok(int s, int n, int k, int d, Polynom f)
{
	vector<int> ret;
	if (d == 2)
	{
		ret = ProjectivePlaneBlokCreation(s, n, d, f);
	}
	else
	{
		ret = ProjectiveGeometryBlokCreation(s, n, k, d, f);
	}
	return ret;
}

vector<int> DualAcicleBlok(int s, int n, int k, int d, Polynom f)
{
	vector<int> ret;
	if (d == 2)
	{
		ret = DualProjectivePlaneBlokCreation(s, n, d, f);
	}
	else
	{
		ret = DualProjectiveGeometryBlokCreation(s, n, k, d, f);
	}
	return ret;
}

vector<string> PolAcicleBlok(int s, int n, int k, int d, Polynom f)
{
	vector<string> ret;
	vector<int> pr;
	pr = AcicleBlok(s, n, k, d, f);
	for (const auto& i : pr)
	{
		if (d == 2)
		{
			ret.push_back(PsiInverse(i, f, n).getByIndex(0).ToString() + " " + PsiInverse(i, f, n).getByIndex(1).ToString() + " " + PsiInverse(i, f, n).getByIndex(2).ToString());
		}
		else
		{
			ret.push_back(Psi3Inverse(i, f, n, k).getByIndex(0).ToString() + " " + Psi3Inverse(i, f, n, k).getByIndex(1).ToString() + " " + Psi3Inverse(i, f, n, k).getByIndex(2).ToString() + " " + Psi3Inverse(i, f, n, k).getByIndex(3).ToString());
		}
	}
	return ret;
}

vector<string> PolDualAcicleBlok(int s, int n, int k, int d, Polynom f)
{
	vector<string> ret;
	vector<int> pr;
	pr = DualAcicleBlok(s, n, k, d, f);
	for (const auto& i : pr)
	{
		if (d == 2)
		{
			ret.push_back(PsiInverse(i, f, n).getByIndex(0).ToString() + " " + PsiInverse(i, f, n).getByIndex(1).ToString() + " " + PsiInverse(i, f, n).getByIndex(2).ToString());
		}
		else
		{
			ret.push_back(Psi3Inverse(i, f, n, k).getByIndex(0).ToString() + " " + Psi3Inverse(i, f, n, k).getByIndex(1).ToString() + " " + Psi3Inverse(i, f, n, k).getByIndex(2).ToString() + " " + Psi3Inverse(i, f, n, k).getByIndex(3).ToString());
		}
	}
	return ret;
}

// Пересечение блоков, содержащихся в списке arr
vector<int> cens(vector<int> arr, bool dual, int n, int k, int d, Polynom f)
{
	vector<int> rez;
	if (dual == false)
	{
		rez = AcicleBlok(arr[0], n, k, d, f);
	}
	else
	{
		rez = DualAcicleBlok(arr[0], n, k, d, f);
	}
	for (int i = 1; i < arr.size(); i++)
	{
		vector<int> prom;
		vector<int> dbl = DualAcicleBlok(arr[i], n, k, d, f);
		for (auto j : rez)
		{
			if (find(dbl.begin(), dbl.end(), j) != dbl.end())
			{
				prom.push_back(j);
			}
		}
		rez = prom;
	}
	return rez;
}

int id(int j)
{
	return j;
}

vector<int> psiinv(int s, int n, int k, int d, Polynom f)
{
	return AcicleBlok(s, n, k, d, f);
}

vector<int> dualhiinv(int s, int n, int k, int d, Polynom f)
{
	return DualAcicleBlok(s, n, k, d, f);
}

string id_str(int num, int n, int k, int d, Polynom f)
{
	vector<int> block = AcicleBlok(num, n, k, d, f);
	string str = to_string(num) + ",[";
	for (int i = 0; i < block.size(); i++)
	{
		str = str + to_string(block[i]) + ",";
	}
	str.erase(str.size() - 1);
	str = str + "]";
	return str;
}

vector<int> Algoritm1(int j1, int j2, vector<int> Lkey, vector<int> Lblock, set<vector<int>> Lblockkey, set<vector<int>> Lblockblock, int n, int k, int d, Polynom f)
{
	if (blockexistence(j1, Lblock) && blockexistence(j2, Lblock))
	{
		vector<int> keys = cens({ id(j1), id(j2) }, false, n, k, d, f);
		for (const auto& it : keys)
		{
			if ((!kel(it, Lkey)) && (!bkel(j1, it, Lblockkey)) && (!bkel(j2, it, Lblockkey)) && (!bbel(j1, j2, Lblockblock)))
			{
				return { it };
			}
		}
		vector<int> keysofj1 = psiinv(j1, n, k, d, f);
		vector<int> keysofj2 = psiinv(j2, n, k, d, f);
		for (const auto& it1 : keysofj1)
		{
			for (const auto& it2 : keysofj2)
			{
				if (it1 == it2)
				{
					if ((!kel(it1, Lkey)) && (!bkel(j1, it1, Lblockkey)) && (!bkel(j2, it1, Lblockkey)))
					{
						int ckey = it1;
						vector<int> commonblocks = dualhiinv(ckey, n, k, d, f);
						for (const auto& it3 : commonblocks)
						{
							if ((!bkel(it3, ckey, Lblockkey)) && (!(it3 == j1)) && (!(it3 == j2)) && (!bbel(it3, j1, Lblockblock)) && (!bbel(it3, j2, Lblockblock)) && (!bbel(it1, it3, Lblockblock)) && (!bbel(it2, it3, Lblockblock)) && ((blockexistence(it3, Lblock))))
							{
								return { ckey,it3 };
							}
						}
					}
				}
			}
		}
		for (const auto& it1 : keysofj1)
		{
			for (const auto& it2 : keysofj2)
			{
				if ((it1 != it2) && (!bkel(j1, it1, Lblockkey)) && (!bkel(j2, it2, Lblockkey)) && (!kel(it1, Lkey)) && (!kel(it2, Lkey)))
				{
					vector<int> commonblocks = cens({ id(it1), id(it2) }, true, n, k, d, f);
					if (commonblocks.size() != 0)
					{
						for (const auto& it3 : commonblocks)
						{
							if ((!bkel(it3, it1, Lblockkey)) && (!bkel(it3, it2, Lblockkey)) && (!(it3 == j1)) && (!(it3 == j2)) && (!bbel(j1, it3, Lblockblock)) && (!bbel(j2, it3, Lblockblock)) && (blockexistence(it3, Lblock)))
							{
								return { j1,it1,it3,it2,j2 };
							}
						}
					}
				}
			}
		}
	}
	vector<int> rez(0);
	return rez;
}

vector<string> Algoritm2(int j1, int j2, vector<int> Lkey, vector<int> Lblock, set<vector<int>> Lblockkey, set<vector<int>> Lblockblock, int n, int v, int k, int d, Polynom f)
{
	vector<string> rez(3);
	rez[0] = { "" };
	rez[1] = { "" };
	rez[2] = { "" };
	if (blockexistence(j1, Lblock) && blockexistence(j2, Lblock))
	{
		int id1 = id(j1);
		int id2 = id(j2);
		vector<int>comelementnumbers = cens({ id1, id2 }, false, n, k, d, f);
		for (const auto& it : comelementnumbers)
		{
			if ((!kel(it, Lkey)) && (!bkel(id1, it, Lblockkey)) && (!bkel(id2, it, Lblockkey)) && (!bbel(id1, id2, Lblockblock)))
			{
				rez[0] = id_str(id1, n, k, d, f);
				rez[1] = id_str(id2, n, k, d, f);
				return rez;
			}
		}
		for (int j = 0; j < v; j++)
		{
			if ((j != id1) && (j != id2) && (blockexistence(j, Lblock)))
			{
				int id3 = id(j);
				vector<int> cens1 = cens({ id1, id3 }, false, n, k, d, f);
				vector<int> cens2 = cens({ id2, id3 }, false, n, k, d, f);
				if ((cens1.size() != 0) && (cens2.size() != 0) && (!bbel(id1, j, Lblockblock)) && (!bbel(id2, j, Lblockblock)))
				{
					for (const auto& k1 : cens1)
					{
						if ((!bkel(j, k1, Lblockkey)) && (!bkel(id1, k1, Lblockkey)) && (!kel(k1, Lkey)))
						{
							for (const auto& k2 : cens2)
							{
								if ((!bkel(j, k2, Lblockkey)) && (!bkel(id2, k2, Lblockkey)) && (!kel(k2, Lkey)))
								{
									rez[0] = id_str(id1, n, k, d, f);
									rez[1] = id_str(id2, n, k, d, f);
									rez[2] = id_str(id3, n, k, d, f);
									return rez;
								}
							}
						}
					}
				}
			}
		}
	}
	return rez;
}

vector<vector<int>> Algoritm3_normal(vector<int> j1, vector<int> j2, int n, int v, int k, int d, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock)
{
	vector<vector<int>> rez;
	rez = vector<vector<int>>(0);
	if (pcel(j1, L_pc) || pcel(j2, L_pc))
	{
		return rez;
	}
	if ((j1[0] == j2[0]) && (!blockpcel(j1, L_blpc)) && (!blockpcel(j2, L_blpc)) && blockexistence(j1[0], L_block))
	{
		rez = vector<vector<int>>(2);
		rez[0] = j1;
		rez[1] = j2;
		return rez;
	}
	if ((j1[1] == j2[1]) && (!dblockpcel(j1, L_dblpc)) && (!dblockpcel(j2, L_dblpc)) && dblockexistance(j2[1], L_dblock)
		&& blockexistence(j1[0], L_block) && blockexistence(j2[0], L_block))
	{
		rez = vector<vector<int>>(2);
		rez[0] = j1;
		rez[1] = j2;
		return rez;
	}
	vector<int> cc(2);
	cc[0] = j1[0];
	cc[1] = j2[0];
	vector<int> cens0 = cens(cc, false, n, k, d, f);
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
				&& (blockexistence(j1[0], L_block)) && (blockexistence(j2[0], L_block)))
			{
				rez = vector<vector<int>>(3);
				rez[0] = j1;
				rez[1] = prom1;
				rez[2] = j2;
				return rez;
			}
			else if ((el == j2[1]) && (!pcel(prom2, L_pc)) && (!blockpcel(j1, L_blpc)) && (!blockpcel(prom2, L_blpc))
				&& (!dblockpcel(prom2, L_dblpc)) && (!dblockpcel(j2, L_dblpc)) && (!blockpcel(j2, L_blpc))
				&& (blockexistence(j1[0], L_block)) && (blockexistence(j2[0], L_block)))
			{
				rez = vector<vector<int>>(3);
				rez[0] = j1;
				rez[1] = prom2;
				rez[2] = j2;
				return rez;
			}
			else if ((!pcel(prom2, L_pc)) && (!blockpcel(j1, L_blpc)) && (!blockpcel(prom2, L_blpc))
				&& (!dblockpcel(prom2, L_dblpc)) && (!dblockpcel(prom1, L_dblpc)) && (!blockpcel(prom1, L_blpc)) && (!blockpcel(j2, L_blpc))
				&& (blockexistence(j1[0], L_block)) && (blockexistence(j2[0], L_block)))
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


vector<vector<int>> Algoritm3(vector<int> j1, vector<int> j2, int n, int v, int k, int d, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock)
{
	vector<vector<int>> rez;
	rez = vector<vector<int>>(0);
	if (pcel(j1, L_pc) || pcel(j2, L_pc) || (!blockexistence(j1[0], L_block)) || (!blockexistence(j2[0], L_block)))
	{
		return rez;
	}
	rez = Algoritm3_normal(j1, j2, n, v, k, d, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
	if (rez.size() != 0)
	{
		return rez;
	}
	vector<int> cc(2);
	vector<int> bl1 = AcicleBlok(j1[0], n, k, d, f);
	vector<int> bl2 = AcicleBlok(j2[0], n, k, d, f);
	for (int el1 = 0; el1 < k; el1++)
	{
		for (int el2 = 0; el2 < k; el2++)
		{
			cc[0] = bl1[el1];
			cc[1] = bl1[el2];
			vector<int> cens1 = cens(cc, true, n, k, d, f);
			for (int j = 0; j < cens1.size(); j++)
			{
				if ((blockexistence(j, L_block)))
				{
					vector<int> prom1(2);
					prom1[0] = cens1[j];
					prom1[1] = bl1[el1];
					vector<int> prom2(2);
					prom2[0] = cens1[j];
					prom2[1] = bl1[el2];
					vector<vector<int>> rez1 = Algoritm3_normal(j1, prom1, n, v, k, d, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez2 = Algoritm3_normal(prom2, j2, n, v, k, d, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez3(0);
					if (prom1 != prom2)
						rez3 = Algoritm3_normal(prom1, prom2, n, v, k, d, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
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