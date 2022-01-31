
//#include "stdafx.h"
#include "funTD.h"
#include "funCPG.h"
#include <iostream>
#include <iostream>
#include "./AAF/AAL/Polynom.h"
//#include "./AAF/AAL/PolynomGF2_mY_7.h"
#include "./AAF/AAL/Integer.h"
#include "./AAF/AAL/DecompositionManager.h"
#include <set>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <sstream>
using namespace AAL;
using namespace std;
////////////////////////////////////  GLOBAL PARAMS  ///////////////////////////////
//Uni.p=2;Uni.l=4;Uni.f=[1,0,0,1,1];k=3;Uni.x=[0,1]
/*
int p = 2;
int l = 3;
Polynom f, buf;
int k = 3;
Polynom x = Polynom("01");
int n = pow(p, l);
int m = 3; //степень трансверсальной блок-схемы; = кол-ву идентификаторов в блоке; 
//= степени списка передаваемого в функцию Phi при расчёте номера блока при формировании дуального трансверсального блока 
//заданного номера(равного номеру ключа!)
*/


//Функция возведения: x^i
Polynom xPowGF2_n(int i,int l,int p, Polynom x, Polynom f)
{
	Polynom res;
	Integer ii = Integer(i);
	if(l!=1)
	{
		if (i == 0) { return Polynom("0"); }
		else
			return res.PowGF2_n(x, ii, f);
	}
	else
	{
		if (i == 0) { return Polynom("0"); }
		else
		{
			Integer res_;
			Integer one(1);
			Integer ii(i);
			Integer pp(p);
			res_.PowInFp(one, ii, pp);
			return Polynom(res_.ToString());
		}
	}
}

//Вход - строка, для удобства как это было на Python
int ind(string ell, int l, int p, Polynom x, Polynom f)
{
	//string str_ell = { ell };
	//Polynom poly_ell = Polynom(str_ell);
	Polynom poly_ell = Polynom(ell);
	if (poly_ell == Polynom("0")) { return 0; }
	else
	{
		int i = 1;
		while (!(xPowGF2_n(i,l,p,x,f) == poly_ell)) { i = i + 1; }
		return i;
	}
}

int Phi(Polynom poly_el[], int len, int n, int l, int p, Polynom x, Polynom f)
{
	//int lenght = sizeof(poly_el) / (sizeof(poly_el[0])/8);// в будущем можно использовать m - хар-ет TD(m,k,n)
	//cout <<"lenPhi="<< sizeof(poly_el)  << "," << sizeof(poly_el[0]) << endl;
	int res = 0;
	for (int i = 0; i < len; i++)
	{
		//cout << "poly_el[i].ToString()=" << poly_el[i].ToString() << endl;
		//cout << "ind(poly_el[i].ToString())=" << ind(poly_el[i].ToString()) << ", (n^i)" << (pow(n,i)) << endl;
		res += (pow(n, i))*ind(poly_el[i].ToString(),l,p,x,f);
	}
	return res;
}
/*
//Создание блока TD(2,k,n)
set<int> TDknBlockcreation(int numer,int n, int k, Polynom f, Polynom x)
{
	set<int> block;
	int a = numer % n;
	int b = (numer - a) / n;
	//cout << "a,b=" << a << "," << b << endl;
	Polynom buf1, buf2;
	for (int t = 0; t < k; t++)
	{
		Polynom poly[2] = { buf2.AddInGF2_n(buf1.MulGF2_n(xPowGF2_n(a,x,f),xPowGF2_n(t,x,f),f),xPowGF2_n(b,x,f),f),xPowGF2_n(t,x,f) };
		block.insert(Phi(poly,2,n,x,f));
	}
	//getch();
	return block;
}
*/
vector<int> TDknBlockcreation(int numer, int l, int p, int n, int k, Polynom f, Polynom x)
{
	vector<int> block;
	int a = numer % n;
	int b = (numer - a) / n;
	//cout << "a,b=" << a << "," << b << endl;
	Polynom buf1, buf2;
	for (int t = 0; t < k; t++)
	{
		Polynom a1(xPowGF2_n(a,l,p,x,f));
		Polynom a2(xPowGF2_n(t,l,p,x,f));
		Polynom a3(xPowGF2_n(b,l,p,x,f));
		Polynom a4(xPowGF2_n(t,l,p,x,f));
		
		Polynom poly[2] = { buf2.AddInGF2_n(buf1.MulGF2_n(a1,a2,f),a3,f),a4 };
		block.push_back(Phi(poly, 2, n,l,p, x, f));
	}
	//getch();
	return block;
}
//Создание дуального блока TD(2,k,n)
vector<int> GTDknN(int key, int l, int p, int n, int m, Polynom f,Polynom x)
{
	vector<int> dualblock;
	Polynom buf1, buf2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Polynom a1(xPowGF2_n(i,l,p,x,f));
			Polynom a2(xPowGF2_n(key / n,l,p,x,f));
			Polynom a3(xPowGF2_n(j,l,p,x,f));
			Polynom a4(xPowGF2_n(key / n,l,p,x,f));
			Polynom poly[2] = { buf2.AddInGF2_n(buf1.MulGF2_n(a1,a2,f),a3,f),a4 };
			if (Phi(poly, 2,n,l,p, x, f) == key)
			{
				Polynom poly[2] = { xPowGF2_n(i,l,p,x,f), xPowGF2_n(j,l,p,x,f) };
				dualblock.push_back(Phi(poly, m,n,l,p, x, f));
			}
		}
	}
	return dualblock;
}
//Создание блока TD(3,k,n)
vector<int> TD3knBlockcreation(int numer, int l, int p, int n, int k, Polynom f,Polynom x)
{
	vector<int> block;
	int a = (numer % (n*n)) % n;
	int b = ((numer % (n*n)) - a) / n;
	int c = (numer - b - a) / (n*n);
	//cout << "a,b,c=" << a << "," << b << "," << c << endl;

	for (int t = 0; t < k; t++)
	{
		Polynom buf0, buf1, buf2, buf3;
		Polynom a1(xPowGF2_n(b,l,p,x,f)),a2(xPowGF2_n(t,l,p,x,f)), a3(xPowGF2_n(a,l,p,x,f)),a4(xPowGF2_n(2 * t,l,p,x,f)), a5(xPowGF2_n(c,l,p,x,f));
		Polynom poly[2] = { buf0.AddInGF2_n(
	buf1.AddInGF2_n(buf2.MulGF2_n(a3,a4,f),buf3.MulGF2_n(a1,a2,f),f),a5,f),
	xPowGF2_n(t,l,p,x,f) };
		block.push_back(Phi(poly, 2,n, l, p, x, f));
	}

	//getch();
	return block;
}

vector<int> TDBlockcreation(int numer, int m, int l, int p, int n, int k, Polynom f, Polynom x)
{
	if (m == 2)
	{
		return TDknBlockcreation(numer, l, p, n, k, f, x);
	}
	else
		if(m==3)
		{
			return TD3knBlockcreation(numer, l, p, n, k, f, x);
		}
}
//Создание дуального блока TD(3,k,n)
vector<int> GTD3knN(int key, int l, int p, int n, int m, Polynom f,Polynom x)
{
	vector<int> dualblock;
	Polynom buf0, buf1, buf2, buf3, buf4;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int ii = 0; ii < n; ii++)
			{
				//Phi([Uni.addFpl(Uni.mulFpl(Uni.xPow(i),Uni.xPow(Uni.mulZ(2,int(t/Uni.n)))),Uni.addFpl(Uni.mulFpl(Uni.xPow(j),Uni.xPow(int(t/Uni.n))),Uni.xPow(ss))),Uni.xPow(int(t/Uni.n))])==t:
				//G.append(Phi([Uni.xPow(i), Uni.xPow(j), Uni.xPow(ss)]))
				Polynom a1(xPowGF2_n(j,l,p,x,f)), a2(xPowGF2_n(key / n,l,p,x,f)), a3(xPowGF2_n(i,l,p,x,f)), a4(xPowGF2_n(2 * (key / n),l,p,x,f)), a5(xPowGF2_n(ii,l,p,x,f));
				Polynom poly[2] = { buf0.AddInGF2_n(
													buf1.MulGF2_n(
																  a3,
																  a4,
																  f),
													buf2.AddInGF2_n(
																	buf3.MulGF2_n(
																				  a1,
																				  a2,
																				  f),
																	a5,
																	f),
													f),
									xPowGF2_n(key / n,l,p,x,f) };
				//cout << Phi(poly,2) <<","<< key << endl;
				if (Phi(poly, 2,n, l, p, x, f) == key)
				{
					Polynom poly1[3] = { xPowGF2_n(i,l,p,x,f), xPowGF2_n(j,l,p,x,f), xPowGF2_n(ii,l,p,x,f) };
					//for (int a = 0; a < 3; a++) { cout << outF2l(poly1[a]) << ' , '; }
					dualblock.push_back(Phi(poly1, m,n, l, p, x, f));
					//cout << Phi(poly1) << endl;
				}
				//getch();
			}
		}
		//getch();
	}
	return dualblock;
}

vector<int> blocksWith(int j1, int j2, int m, int l, int p, int n, int k, Polynom f, Polynom x)
{
	vector<int> dual1, dual2, commonblocks;
	dual1 = dualhiinv(j1, l, p, n, m, x, f);
	dual2 = dualhiinv(j2, l, p, n, m, x, f);
	set_intersection(dual1.begin(), dual1.end(), dual2.begin(), dual2.end(), back_inserter(commonblocks));
	return commonblocks;
}

vector<int> decToN(int a,int n) 
{
	vector<int> Blist;
	Integer q1;
	int buf;
	while (int(a) != 0)
	{
		Integer aa(a), nn(n);
		buf = stoi(q1.Mod(aa,nn).ToString());
		Blist.push_back(buf);
		a = (a - buf) / n;
	}
	return Blist;
}

vector<string> PhiInverse(int j, int l, int p, int m,int n, Polynom x, Polynom f)
{
	vector<int> decN = decToN(j,n);
	while (decN.size() != m)
	{
		decN.push_back(0);
	}
	vector<string> res;
	for (auto i : decN)
	{
		res.push_back(xPowGF2_n(i,l,p,x,f).ToString());//в коде ASCII числа (цифры) начинаются с 48 
	}
	return res;
}

vector<string> id_block(int j, int l, int p, int m, int n, Polynom x, Polynom f)
{
	return PhiInverse(j,l,p,m,n,x,f);
}

Polynom tr(Polynom x_poly,int l, Polynom f)
{
	Polynom res = Polynom("0");
	Polynom buf1;
	Integer buf2;
	for (int i = 0; i < l; i++)
	{
		res.AddInGF2_n(res, buf1.PowGF2_n(x_poly, buf2.Pow(Integer(2), Integer(i)), f), f);
	}
	return res;
}

Polynom SqrtGF2_n(Polynom a,int n,Polynom f)
{
	Polynom res;
	Integer st;
	Integer nn(n), two(2);
	return res.PowGF2_n(a, st.Div(nn, two), f);//Uni.powerFpl(a, Uni.divZ(Uni.n, 2)[0])
}

vector<string> SolveQuadraticEquationGF2N(vector<string> idj1, vector<string> idj2,int l,int p,int n, Polynom x,Polynom f)
{
	Polynom ainv, A, B, buf1;
	Polynom zero = Polynom("0");
	vector<string> res;
	Polynom a1(idj1[0]), a2(idj2[0]), a3(idj1[1]), a4(idj2[1]), a5(idj1[2]), a6(idj2[2]);
	ainv.InverseGF2_n(buf1.SubInGF2_n(a1, a2, f), f);
	A.MulGF2_n(buf1.SubInGF2_n(a3, a4, f), ainv, f);
	B.MulGF2_n(buf1.SubInGF2_n(a5, a6, f), ainv, f);
	//cout << "ainv,A,B=" << ainv.ToString() << "," << A.ToString() << "," << B.ToString() << endl;
	if (A == zero && B == zero)
	{
		res = { "0" };
		return res;
	}
	else
		if (A == zero && B != zero)
		{
			res = { SqrtGF2_n(B,n,f).ToString() };//Пользуемся тем, что корень в GF2_n у любого элемента корень - единственный
			return res;
		}

	Polynom buf2, C, t;
	C.MulGF2_n(B, buf1.InverseGF2_n(buf2.MulGF2_n(A, A, f), f), f);
	//cout << C.ToString() << endl;
	t = tr(C,l,f);
	//cout <<"C = "<< t.ToString()<<endl;
	if (t != zero)
	{
		res = { "Нет решения!" };
		return res;
	}

	Integer l1, l2, l3; Polynom buf3;
	Integer ll(l), two(2);
	if (l1.Mod(ll, two) == 1)
	{

		Polynom g = Polynom("0");
		l2.Div(ll, two);
		for (int i = 1; i < l2 + 1; i++)
		{
			//g = Uni.addFpl(g, Uni.powerFpl(c, Uni.powerZ(2, Uni.powerZ(2, i))))
			g.AddInGF2_n(g, buf1.PowGF2_n(C, l3.Pow(Integer(2), Integer(i)), f), f);
		}
		res = { buf1.MulGF2_n(A,buf2.AddInGF2_n(C,g,f),f).ToString(),buf3.AddInGF2_n(A,buf1,f).ToString() };
		return res;
	}
	//5 
	int j = 0;
	Polynom u;
	t = Polynom("0");
	while (t != Polynom("1"))
	{
		//cout << "NEnnnnnn" << endl;
		u = xPowGF2_n(j,l,p,x,f);
		t = tr(u,l,f);
		//cout << "t=" << t.ToString() << endl;
		//getch();
		j++;
	}
	//6
	Polynom w = Polynom("0");
	Polynom res_poly;
	for (int i = 1; i < l; i++)
	{
		res_poly = Polynom("0");
		for (int r = 0; r < i; r++)
		{
			res_poly.AddInGF2_n(res_poly, buf1.PowGF2_n(u, l3.Pow(2, r), f), f);
		}
		w.AddInGF2_n(w, buf2.MulGF2_n(buf3.PowGF2_n(C, l3.Pow(2, i), f), res_poly, f), f);
	}
	Polynom one("1");
	res = { buf1.MulGF2_n(A,buf2.AddInGF2_n(one,w,f),f).ToString(),buf3.AddInGF2_n(A,buf1,f).ToString() };
	return res;
}

vector<int> cens(vector<string> idj1, vector<string> idj2,int l, int p, int k,int n,int m, Polynom x, Polynom f)
{
	vector<int> res;
	Polynom x_;
	Polynom buf1, buf2, buf3, buf4, buf5, buf6;
	if (m == 2)
	{
		if (idj1[0] != idj2[0])
		{
			Polynom a3(idj1[0]);
			Polynom a4(idj2[1]);
			Polynom a5(idj2[0]);
			Polynom a6(idj1[1]);
			x_ = buf1.MulGF2_n(buf2.SubInGF2_n(a4, a6, f),
				buf3.InverseGF2_n(buf4.SubInGF2_n(a3, a5, f), f), f);
			if (ind(x_.ToString(),l,p,x,f) <= k - 1)
			{
				Polynom a1(idj1[0]);
				Polynom a2(idj1[1]);
				Polynom poly_mas[2] = { buf1.AddInGF2_n(buf2.MulGF2_n(a1,x_,f),a2,f),x_ };
				res.push_back(Phi(poly_mas, 2,n,l,p,x,f));
				return res;
			}
			else
			{
				return res;
			}
		}
		return res;
	}
	else
		if (m == 3)
		{
			if (idj1[0] != idj2[0])
			{
				vector<string> squares;

				squares = SolveQuadraticEquationGF2N(idj1, idj2,l,p,n,x,f);
				//cout << "NEnnnnnn" << endl;
				if (squares[0] != "Нет решения!")
				{
					if (squares.size() == 1)
					{
						if (ind(squares[0],l,p,x,f) <= k - 1)
						{
							Polynom x1 = squares[0];
							Polynom a1(idj1[0]);
							Polynom a2(idj1[1]);
							Polynom a3(idj1[2]);
							Polynom poly_mas[2] = { buf1.AddInGF2_n(buf2.AddInGF2_n(buf3.MulGF2_n(a1,buf4.MulGF2_n(x1,x1,f),f),
																				   buf5.MulGF2_n(a2,x1,f),f),
																   a3,f),
												   x1 };
							res.push_back(Phi(poly_mas, 2,n,l,p,x,f));
							return res;
						}
						else
							return res;
					}
					else
						if (squares.size() == 2)
						{
							if (ind(squares[0], l,p,x, f) <= k - 1)
							{
								Polynom x1 = squares[0];
								Polynom a1(idj1[0]);
								Polynom a2(idj1[1]);
								Polynom a3(idj1[2]);
								Polynom poly_mas[2] = { buf1.AddInGF2_n(buf2.AddInGF2_n(buf3.MulGF2_n(a1,buf4.MulGF2_n(x1,x1,f),f),
																					   buf5.MulGF2_n(a2,x1,f),f),
																	   a3,f),
													   x1 };
								res.push_back(Phi(poly_mas, 2,n,l,p, x, f));
							}
							if (ind(squares[1],l,p, x, f) <= k - 1)
							{
								Polynom x2 = squares[1];
								Polynom a1(idj1[0]);
								Polynom a2(idj1[1]);
								Polynom a3(idj1[2]);
								Polynom poly_mas[2] = { buf1.AddInGF2_n(buf2.AddInGF2_n(buf3.MulGF2_n(a1,buf4.MulGF2_n(x2,x2,f),f),
																					   buf5.MulGF2_n(a2,x2,f),f),
																	   a3,f),
													   x2 };
								res.push_back(Phi(poly_mas, 2,n,l,p, x, f));
							}
							if (res.size() == 0)
							{
								return res;
							}
							sort(res.begin(), res.end());
							return res;
						}
				}
				else
					return res;
			}
			else
				if (idj1[1] != idj2[1])
				{
					Polynom a1(idj2[2]);
					Polynom a2(idj1[2]);
					Polynom a3(idj1[1]);
					Polynom a4(idj2[1]);
					x_ = buf1.MulGF2_n(buf2.SubInGF2_n(a1, a2, f),
						buf3.InverseGF2_n(buf4.SubInGF2_n(a3, a4, f), f), f);
					if (ind(x_.ToString(), l,p,x, f) <= k - 1)
					{
						Polynom a5(idj1[0]);
						Polynom a6(idj1[1]);
						Polynom a7(idj1[2]);
						Polynom poly_mas[2] = { buf1.AddInGF2_n(buf2.AddInGF2_n(buf3.MulGF2_n(a5,buf4.MulGF2_n(x_,x_,f),f),
																				buf5.MulGF2_n(a6,x_,f),f),
																a7,f),
												x_ };
						res.push_back(Phi(poly_mas, 2,n,l,p, x, f));
						return res;
					}
				}
			return res;
		}
}

bool bkel(int bn, int kn, set<vector<int>> L_blockkey)
{
	bool bl;
	//vector<int> v = { bn,kn };
	for (auto i : L_blockkey)
	{
		bl = ((i[0] == bn) && (i[1] == kn));
		if (bl)
		{
			return bl;
		};
	}
	return 0;
}

bool bbel(int bn1, int bn2, set<vector<int>> L_blockblock)
{
	bool bl;
	if (bn1 < bn2)
	{
		for (auto i : L_blockblock)
		{
			bl = ((i[0] == bn1) && (i[1] == bn2));
			if (bl)
			{
				//cout << "bl=" << bl;
				return bl;
			};
		}
	}
	else
	{
		for (auto i : L_blockblock)
		{
			bl = ((i[0] == bn2) && (i[1] == bn1));
			if (bl)
			{
				return bl;
			};
		}
	}
	return 0;
}

bool kel(int kn, vector<int> L_key)
{
	sort(L_key.begin(), L_key.end());
	return binary_search(L_key.begin(), L_key.end(), kn);
}

bool blockexistence(int bn, vector<int> L_block)
{
	sort(L_block.begin(), L_block.end());
	return binary_search(L_block.begin(), L_block.end(), bn);
}
vector<int> psiinv(int j, int l, int p, int k, int n, int m, Polynom x, Polynom f)
{
	if (m == 2)
	{
		return TDknBlockcreation(j,l,p,n,k,f,x);
	}
	else
		if (m == 3)
		{
			return TD3knBlockcreation(j,l,p, n, k, f, x);
		}
}
vector<int> dualhiinv(int key, int l, int p, int n, int m, Polynom x, Polynom f)
{
	if (m == 2)
	{
		vector<int> res = GTDknN(key,l,p, n, m, f, x);
		sort(res.begin(), res.end());
		return res;
	}
	else
		if (m == 3)
		{
			vector<int> res = GTD3knN(key,l,p, n, m, f, x);
			sort(res.begin(), res.end());
			return res;
		}
}

//vector<int> algoritm1(int j1, int j2, vector<int> L_key, vector<string> L_blockkey, vector<string> L_blockblock, vector<int> L_block)
vector<int> algoritm1(int j1, int j2, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block,int l,int p, int k,int n,int m,Polynom x,Polynom f)
{

	vector<int> keys = cens(id_block(j1,l,p,m,n,x,f), id_block(j2,l,p,m, n, x, f),l,p,k,n,m,x,f);
	//vector<int> res;
	vector<int> keysofj1, keysofj2;
	for (auto it : keys)
	{

		//cout <<"it="<< it << endl;
		//cout << !kel(it, L_key) << !bkel(j1, it, L_blockkey) << !bkel(j2, it, L_blockkey) << !bbel(j1, j2, L_blockblock) << endl;
		//cout << (!kel(it, L_key) && !bkel(j1, it, L_blockkey) && !bkel(j2, it, L_blockkey) && !bbel(j1, j2, L_blockblock)) << endl;
		if (!kel(it, L_key) && !bkel(j1, it, L_blockkey) && !bkel(j2, it, L_blockkey) && !bbel(j1, j2, L_blockblock))
		{
			//res = { it };
			//cout << !kel(it, L_key) << !bkel(j1, it, L_blockkey) << !bkel(j2, it, L_blockkey) << !bbel(j1, j2, L_blockblock) << endl;
			return { it };
		}
	}
	//cout << 2 << endl;
	keysofj1 = psiinv(j1,l,p,k,n,m,x,f);
	keysofj2 = psiinv(j2,l,p, k, n, m, x, f);
	for (auto it1 : keysofj1)
	{
		//cout << "it1=" << it1;
		for (auto it2 : keysofj2)
		{
			//cout << "it2=" << it2;
			if (it1 == it2)
			{
				//cout << "it1=" << it1 << endl;
				if (!kel(it1, L_key) && !bkel(j1, it1, L_blockkey) && !bkel(j2, it1, L_blockkey))
				{
					//cout << "2" << endl;
					int ckey = it1;
					vector<int> commonblocks = dualhiinv(ckey,l,p,n, m, x, f);
					for (auto it3 : commonblocks)
					{
						//if (!bkel(it3, ckey, L_blockkey) && !(it3 == j1) && !(it3 == j2) &&
						//	!bbel(it3, j1, L_blockblock) && !bbel(it3, j1, L_blockblock))
						if (!bkel(it3, ckey, L_blockkey) && !(it3 == j1) && !(it3 == j2) && 
							!bbel(it3, j1, L_blockblock) && !bbel(it3, j1, L_blockblock) && blockexistence(it3,L_block))
						{
							//res = { ckey,it3 };
							return { ckey,it3 };
						}
					}
				}
			}
		}
	}

	for (auto it1 : keysofj1)
	{
		for (auto it2 : keysofj2)
		{
			if (it1 != it2 && !bkel(j1, it1, L_blockkey) && !bkel(j2, it2, L_blockkey) && !kel(it1, L_key) && !kel(it2, L_key))
			{
				vector<int> dual1, dual2, commonblocks;
				dual1 = dualhiinv(it1,l,p, n, m, x, f);
				dual2 = dualhiinv(it2,l,p, n, m, x, f);
				set_intersection(dual1.begin(), dual1.end(), dual2.begin(), dual2.end(), back_inserter(commonblocks));
				sort(commonblocks.begin(), commonblocks.end());
				if (commonblocks.size() != 0)
				{
					for (auto it3 : commonblocks)
					{
						//if (!bkel(it3, it1, L_blockkey) && !bkel(it3, it2, L_blockkey) && !bbel(it3, j2, L_blockblock) &&
						//	!(it3 == j1) && !(it3 == j2) && !bbel(it3, j1, L_blockblock))
						if (!bkel(it3, it1, L_blockkey) && !bkel(it3, it2, L_blockkey) && !bbel(it3, j2, L_blockblock) && 
							!(it3 == j1) && !(it3 == j2) && !bbel(it3, j1, L_blockblock) && blockexistence(it3, L_block))
						{
							//res = {j1,it1,it3,it2,j2};
							return { j1,it1,it3,it2,j2 };
						}
					}
				}
			}
		}
	}
	//cout << "exit" << endl;
	return {};
}

string out_alg1(int j1, int j2, vector<int> out)
{
	string res;
	if (out.size() == 1)
	{
		res = "Ключ непосредственной связи узлов " + to_string(j1) + " и " + to_string(j2)
			+ " : " + to_string(out[0]);
	}
	else
		if (out.size() == 2)
		{
			res = "Ключ связи узлов " + to_string(j1) + " и " + to_string(j2)
				+ " через узел " + to_string(out[1]) + " : " + to_string(out[0]);
		}
		else
			if (out.size() == 5)
			{
				res = "Узел " + to_string(out[0]) + " по ключу " + to_string(out[1]) +
					" связан с узлом " + to_string(out[2]) + " связанным по ключу " + to_string(out[3]) +
					" c узлом " + to_string(out[4]);
			}
			else
				res = "Связи(непосредственной или через одного посредника) между узлами " + to_string(j1) +
				" и " + to_string(j2) + " нет !";
	return res+"\n\n";
}

//vector<vector<string>> algoritm2(int j1, int j2, vector<int> L_key, vector<string> L_blockkey, vector<string> L_blockblock, vector<int> L_block)
vector<vector<string>> algoritm2(int j1, int j2, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block,
								 int l,int p,int k,int n,int m, Polynom x, Polynom f)
{
	int v = pow(n, m);
	vector<string> id1 = id_block(j1,l,p, m, n, x, f);
	vector<string> id2 = id_block(j2,l,p, m, n, x, f);
	vector<int> comelementnumbers = cens(id1, id2, l,p, k, n, m, x, f);
	for (auto it : comelementnumbers)
	{
		if (!kel(it, L_key) && !bkel(j1, it, L_blockkey) && !bkel(j2, it, L_blockkey) && !bbel(j1, j2, L_blockblock))
		{
			return { id1, id2};
			//return { id1, id2, {} };
		}
	}

	for (int j = 0; j < v; j++)
	{
		//if (j != j1 && j != j2 && !bbel(j, j1, L_blockblock) && !bbel(j, j2, L_blockblock))
		if (j != j1 && j != j2 && !bbel(j, j1, L_blockblock) && !bbel(j, j2, L_blockblock) && blockexistence(j, L_block))
		{
			vector<string> id3 = id_block(j,l,p, m, n, x, f);
			//for (auto i : id3) { cout << i << " "; } cout << endl;
			vector<int> cens1 = cens(id1, id3, l,p, k, n, m, x, f);
			vector<int> cens2 = cens(id2, id3, l,p, k, n, m, x, f);
			sort(cens1.begin(), cens1.end());
			sort(cens2.begin(), cens2.end());
			if (cens1.size() != 0 && cens2.size() != 0)
			{
				//cout << "no_empty cens1 and cens2" << endl;
				for (auto k1 : cens1)
				{
					//cout << "j,k1,j1=" <<j<<k1<<j1<< endl;
					if (!bkel(j, k1, L_blockkey) && !bkel(j1, k1, L_blockkey))//&& (!kel(k1))-?
					{

						for (auto k2 : cens2)
						{
							if (!bkel(j, k2, L_blockkey) && !bkel(j2, k2, L_blockkey))//&& (!kel(k1))-?
							{
								//cout << "j=" << j << endl;
								return { id1, id2, id3 };
							}
						}
					}
				}
			}
		}
	}

	return {};
	//return { {},{},{} };
}

vector<vector<int>> algoritm3(vector<int> j1, vector<int> j2, int l, int p, int k, int n, int m, Polynom x, Polynom f)
{
	vector<vector<int>> rez;
	//Если заданные номера блоков или дуальных блоков равны
	if ((j1[0] == j2[0]) || (j1[1] == j2[1]))
	{
		//тогда связь непосредственная через полносвязную сеть блока или дуального блока соответственно
		return { j1 , j2 };
	}
	//Пересекаем блоки
	vector<int> keys = cens(id_block(j1[0], l, p, m, n, x, f), id_block(j2[0], l, p, m, n, x, f), l, p, k, n, m, x, f);
	for (auto el : keys)
	{
		if (el == j1[1])
		{
			return { j1 , {j2[0],el}, j2 };
		}
		else
			if (el == j2[1])
			{
				return { j1 , {j1[0],el}, j2 };
			}
			else
			{
				return { j1 , {j1[0],el},{j2[0],el}, j2 };
			}
	}
	//Пересекаем дуальные блоки с заданными номерами
	vector<int> cens1 = blocksWith(j1[1], j2[1], m, l, p, n, k, f, x);
	for (const auto &el : cens1)
	{
		if (el == j1[0])
		{
			return { j1 , {el, j2[1]}, j2 };
		}
		else if (el == j2[0])
		{
			return { j1 , {el, j1[1]}, j2 };
		}
		else
		{
			return { j1 , {el, j1[1]},{el, j2[1]}, j2 };
		}
	}
	
	//Блоки с заданынми номерами не пересекаются и дуальные блоки не пересекаются!
	vector<int> keysofj1, keysofj2, keysofj3;
	keysofj1 = psiinv(j1[0], l, p, k, n, m, x, f);
	keysofj2 = psiinv(j2[0], l, p, k, n, m, x, f);
	for (auto it1 : keysofj1)
	{
		for (auto it2 : keysofj2)
		{
			vector<int> cens2 = blocksWith(it1, it2, m, l, p, n, k, f, x);
			if (cens2.size() != 0)
			{
				for (auto el : cens2)
				{
					if (it1 == j1[1])
					{
						return { j1 , {el,it1},{el,it2},{j2[0],it2},j2 };
					}
					else
						if (it2 == j2[1])
						{
							return { j1 , {j1[0],it1},{el,it1},{el,it2},j2 };
						}
				}
			}
		}
	}
	
	rez = vector<vector<int>>(0);
	return rez;
}

/*
vector<vector<int>> algoritm33(vector<int> j1, vector<int> j2, int l, int p, int k, int n, int m, Polynom x, Polynom f)
{
	vector<vector<int>> rez;
	if ((j1[0] == j2[0]) || (j1[1] == j2[1]))
	{
		rez = vector<vector<int>>(2);
		rez[0] = j1;
		rez[1] = j2;
		return rez;
	}
	vector<int> keys = cens(id_block(j1[0], l, p, m, n, x, f), id_block(j2[0], l, p, m, n, x, f), l, p, k, n, m, x, f);
	for (const auto &el : keys)
	{
		if (el == j1[1])
		{
			rez = vector<vector<int>>(3);
			rez[0] = j1;
			rez[1] = vector<int>(2);
			rez[1][0] = j2[0];
			rez[1][1] = el;
			rez[2] = vector<int>(2);
			rez[3] = j2;
			return rez;
		}
		else 
			if (el == j2[1])
			{
				rez = vector<vector<int>>(3);
				rez[0] = j1;
				rez[1] = vector<int>(2);
				rez[1][0] = j1[0];
				rez[1][1] = el;
				rez[2] = vector<int>(2);
				rez[3] = j2;
				return rez;
			}
			else
			{
				rez = vector<vector<int>>(4);
				rez[0] = j1;
				rez[1] = vector<int>(2);
				rez[1][0] = j1[0];
				rez[1][1] = el;
				rez[2] = vector<int>(2);
				rez[2][0] = j2[0];
				rez[2][1] = el;
				rez[3] = j2;
				return rez;
			}
	}

	vector<int> cens1 = blocksWith(j1[1], j2[1],m, l, p, n, k, f, x);
	for (const auto &el : cens1)
	{
		if (el == j1[0])
		{
			rez = vector<vector<int>>(3);
			rez[0] = j1;
			rez[1] = vector<int>(2);
			rez[1][0] = el;
			rez[1][1] = j2[1];
			rez[2] = j2;
			return rez;
		}
		else if (el == j2[0])
		{
			rez = vector<vector<int>>(3);
			rez[0] = j1;
			rez[1] = vector<int>(2);
			rez[1][0] = el;
			rez[1][1] = j1[1];
			rez[2] = j2;
			return rez;
		}
		else
		{
			rez = vector<vector<int>>(4);
			rez[0] = j1;
			rez[1] = vector<int>(2);
			rez[1][0] = el;
			rez[1][1] = j1[1];
			rez[2] = vector<int>(2);
			rez[2][0] = el;
			rez[2][1] = j2[1];
			rez[3] = j2;
			return rez;
		}
	}

	rez = vector<vector<int>>(0);
	return rez;

}
*/
/*
string out_alg2(vector<vector<string>> out, int len, int n, int l, int p, Polynom x, Polynom f)
{
	int j1, j2, j3;
	if (out.size() == 2)
	{
		if (len == 2)
		{
			Polynom poly_el1[2] = { Polynom(out[0][0]),Polynom(out[0][1])};
			Polynom poly_el2[2] = { Polynom(out[1][0]),Polynom(out[1][1]) };
			j1 = Phi(poly_el1, len, n, l, p, x, f); j2 = Phi(poly_el2, len, n, l, p, x, f);
		}
		else
			if (len == 3)
			{
					Polynom poly_el1[3] = { Polynom(out[0][0]),Polynom(out[0][1]),Polynom(out[0][2]) };
					Polynom poly_el2[3] = { Polynom(out[1][0]),Polynom(out[1][1]),Polynom(out[1][2]) };
					j1 = Phi(poly_el1, len, n, l, p, x, f); j2 = Phi(poly_el2, len, n, l, p, x, f);
			}
		return "Компьюетры с номерами j1 = " + to_string(j1) + " и j2 = " +
			to_string(j2) + " соединены по каналу связи [" + to_string(j1) + ", " + to_string(j2) + "]";
	}
	else
		if (out.size() == 3)
		{
			if (len == 2)
			{
				Polynom poly_el1[2] = { Polynom(out[0][0]),Polynom(out[0][1]) };
				Polynom poly_el2[2] = { Polynom(out[1][0]),Polynom(out[1][1]) };
				Polynom poly_el3[2] = { Polynom(out[2][0]),Polynom(out[2][1]) };
				j1 = Phi(poly_el1, len, n, l, p, x, f); j2 = Phi(poly_el2, len, n, l, p, x, f);
				j3 = Phi(poly_el3, len, n, l, p, x, f);
			}
			else
				if (len == 3)
				{
					Polynom poly_el1[3] = { Polynom(out[0][0]),Polynom(out[0][1]),Polynom(out[0][2]) };
					Polynom poly_el2[3] = { Polynom(out[1][0]),Polynom(out[1][1]),Polynom(out[1][2]) };
					Polynom poly_el3[3] = { Polynom(out[2][0]),Polynom(out[2][1]),Polynom(out[2][2]) };
					j1 = Phi(poly_el1, len, n, l, p, x, f); j2 = Phi(poly_el2, len, n, l, p, x, f);
					j3 = Phi(poly_el3, len, n, l, p, x, f);
				}
			return "Компьюетры с номерами j1 = " + to_string(j1) + " и j2 = " + to_string(j2) +
				" соединены через компьтер c номером " + to_string(j3)
				+ " по каналу связи [" + to_string(j1) + ", " + to_string(j3) + ", " + to_string(j2) + "]";
		}
	return "Между указанными компьюетрами нет соединения!";
	
}*/

string out_alg2(vector<vector<string>> out)
{
	string res = "[ ";
	if (out.size() == 2)
	{
		res += "[ ";
		for (auto i : out[0])
		{
			res += i + " ";
		}
		res += "],[ ";
		for (auto j : out[1])
		{
			res += j + " ";
		}
		res += "],[ ] ]\n\n";
		return res;
	}
	else
		if (out.size() == 3)
		{
			res += "[ ";
			for (auto i : out[0])
			{
				res += i + " ";
			}
			res += "],[ ";
			for (auto j : out[1])
			{
				res += j + " ";
			}
			res += "],[ ";;
			for (auto z : out[2])
			{
				res += z + " ";
			}
			res += "] ]\n\n";
			return res;
		}
	return "[ [ ],[ ],[ ] ]\n\n";
}

string out_set_vector_dig2(set<vector<int>> out)
{
	if (out.size() == 0)
	{
		return "[ ]";
	}
	else
	{
		string res="[";
		string res1;
		for (auto i : out)
		{
			res += to_string(i[0]) + "," + to_string(i[1]) + ";";
		}
		res1 = res.substr(0, res.size() - 1);
		return res1 + "]";
	}
}

string out_vector(vector<int> out)
{
	if (out.size() == 0)
	{
		return "[ ]";
	}
	else
	{
		string res = "[";
		for (int i=0;i<out.size()-1;i++)
		{
			res += to_string(out[i]) + ",";
		}
		return res += to_string(out[out.size() - 1]) + "]";
	}
}

string out_alg3(vector<vector<int>> out)
{
	string res;
	if (out.size() == 2)
	{
		res = "(" + to_string(out[0][0]) + "," + to_string(out[0][1]) + ")->("+to_string(out[1][0]) +","+ to_string(out[1][1]) + ")";
	}
	else
		if (out.size() == 3)
		{
			res = "(" + to_string(out[0][0]) + "," + to_string(out[0][1]) + ")->(" + to_string(out[1][0]) + "," + to_string(out[1][1]) +
				")->(" + to_string(out[2][0]) + "," + to_string(out[2][1]) + ")";
		}
		else
			if (out.size() == 4)
			{
				res = "(" + to_string(out[0][0]) + "," + to_string(out[0][1]) + ")->(" + to_string(out[1][0]) + "," + to_string(out[1][1]) +
					")->(" + to_string(out[2][0]) + "," + to_string(out[2][1]) + ")->(" + to_string(out[3][0]) + "," + to_string(out[3][1]) + ")";
			}
			else
				if (out.size() == 5)
				{
					res = "(" + to_string(out[0][0]) + "," + to_string(out[0][1]) + ")->(" + to_string(out[1][0]) + "," + to_string(out[1][1]) +
						")->(" + to_string(out[2][0]) + "," + to_string(out[2][1]) + ")->(" + to_string(out[3][0]) + "," + to_string(out[3][1]) +
						")->(" + to_string(out[4][0]) + "," + to_string(out[4][1]) + ")";
				}
				else
					res = "Связи между указанными компьютерами нет!";
	return res;
}

/*
set<vector<int>> split_str_in_set_vec_int(string str_sp)
{
	size_t pos1 = 0;
	set<vector<int>> set_vec;
	string token1, token2;
	string delimiter1 = ";"; string delimiter2 = ",";
	while ((pos1 = str_sp.find(delimiter1)) != std::string::npos)
	{
		token1 = str_sp.substr(0, pos1);//"n,m"
		size_t pos2 = 0;
		vector<int> vec;
		pos2 = token1.find(delimiter2);
		token2 = str_sp.substr(0, pos2);
		vec.push_back(stoi(token2));
		token1.erase(0, pos2 + delimiter2.length());
		vec.push_back(stoi(token1));
		sort(vec.begin(), vec.end());
		set_vec.insert(vec);//set - это множество которое автоматичсески сортирует!
		str_sp.erase(0, pos1 + delimiter1.length());
	}
	return set_vec;
}
*/


// Алгоритм1: Проверка неприводимости и примитивности многочлена степени l над полем GF(2)
int ALG1(int p, int l, Polynom ff, vector<DecompositionMember> s, vector<DecompositionMember> d)
{
	Polynom x("01"), buf;
	if (l != 1)
	{
		int k = s.size();
		Polynom ft = x;
		Integer pp(p);
		for (int t = 1; t < l; t++)
		{
			ft = buf.ModPow(ft, pp, ff);
			for (int i = 0; i < k; i++)
			{
				Polynom tmp(ft - x);
				if (((t == l / s[i].getNumber()) & (ft == x)) || (!(buf.Euclid(ff, tmp).ToString().length() == 1)))
					return 0;
			}
		}
		Polynom fl = buf.ModPow(ft, pp, ff);
		if (fl != x)
			return 0;
	}
	int r = d.size();
	for (int i = 0; i < r; i++) {
		Integer tmp((pow(p, l) - 1) / d[i].getNumber());
		if (buf.ModPow(x, tmp, ff) == Polynom("1"))
			return 1;
	}
	return 2;
}
// Генератор перестановок
bool NextSet(vector<int> &a, int n, int m)
{
	int j = m - 1;
	while ((j >= 0) && (a[j] == n))
		j = j - 1;
	if (j < 0)
		return false;
	if (a[j] >= n)
		j = j - 1;
	a[j] = a[j] + 1;
	if (j == m - 1)
		return true;
	for (int k = j + 1; k < m; k++)
		a[k] = 0;
	return true;
}
// Разложение номера по степеням p
Polynom razlP(int p,int num,int l)
{
	string rez = "";
	int* buf = new int[l];
	for (int i = 0; i < l; i++)
		buf[i] = 0;
	int s = p;
	int i = l - 1;
	while (!(num == 0))
	{
		if (pow(s, i) <= num)
		{
			buf[i] = int(num) / pow(s, i);
			num = num - pow(s, i)*buf[i];
		}
		i--;
	}
	for (int i = 0; i < l; i++)
		rez = rez + to_string(buf[i]);
	return Polynom(rez);
}

// Генерация примитивного многочлена над GF(2)
Polynom genPrimitiveF2l(int p,int l)
{
	vector<int> a(l + 1);
	string st = "";
	for (int i = 0; i < l; i++)
	{
		st = st + to_string(0);
	}
	a[l] = 1;
	st = st + to_string(1);
	Polynom f = Polynom(st);//Было f = Polynom(st);
	int N = pow(p, l) - 1;
	vector<DecompositionMember> s(DecompositionManager::Instance().getPrimeDecomposition(l));
	vector<DecompositionMember> d(DecompositionManager::Instance().getPrimeDecomposition(N));
	if (ALG1(p, l, f, s, d) == 2)
		return f;
	while (NextSet(a, p - 1, l))
	{
		st = "";
		for (int i = 0; i < l + 1; i++)
			st = st + to_string(a[i]);
		f = Polynom(st);
		if (ALG1(p, l, f, s, d) == 2)
			return f;
	}
	return Polynom();
}

// Вывод многочлена над GF(2)
string outF2l(Polynom pol)
{
	string pl = pol.ToString();
	string rez = "";
	if (pl[0] != '0')
		rez = rez + pl[0];
	for (int i = 1; i < pl.length(); i++)
	{
		if (rez != "")
		{
			if (pl[i] != '0')
				if (pl[i] != '1')
				{
					if (i > 1)
						rez = rez + " + " + pl[i] + "*z^" + to_string(i);
					else
						rez = rez + " + " + pl[i] + "*z";
				}
				else
				{
					if (i > 1)
						rez = rez + " + z^" + to_string(i);
					else
						rez = rez + " + z";
				}
		}
		else
		{
			if (pl[i] != '0')
				if (pl[i] != '1')
				{
					if (i > 1)
						rez = rez + pl[i] + "*z^" + to_string(i);
					else
						rez = rez + pl[i] + "*z";
				}
				else
				{
					if (i > 1)
						rez = rez + " z^" + to_string(i);
					else
						rez = rez + " z";
				}
		}
	}
	return rez;
}

vector<vector<int>> Algoritm3_normal(vector<int> j1, vector<int> j2, int n, int l, int p, int m, int k, Polynom x, Polynom f,
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
	vector<int> cens0 = cens(id_block(cc[0], l, p, m, n, x, f), id_block(cc[1], l, p, m, n, x, f), l, p, k, n, m, x, f);
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
			else if ((!pcel(prom2, L_pc)) && (!pcel(prom1, L_pc)) && (!blockpcel(j1, L_blpc)) && (!blockpcel(prom2, L_blpc))
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


vector<vector<int>> Algoritm3(vector<int> j1, vector<int> j2, int n, int l, int p, int m, int k, Polynom x, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock)
{
	vector<vector<int>> rez;
	rez = vector<vector<int>>(0);
	if (pcel(j1, L_pc) || pcel(j2, L_pc) || (!blockexistence(j1[0], L_block)) || (!blockexistence(j2[0], L_block)))
	{
		return rez;
	}
	rez = Algoritm3_normal(j1, j2, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
	if (rez.size() != 0)
	{
		return rez;
	}
	vector<int> cc(2);
	vector<int> bl1, bl2;
	if (m == 2) {
		vector<int> bl1 = TDknBlockcreation(j1[0], l, p, n, k, f, x);
		vector<int> bl2 = TDknBlockcreation(j2[0], l, p, n, k, f, x);
	}
	if (m == 3) {
		vector<int> bl1 = TD3knBlockcreation(j1[0], l, p, n, k, f, x);
		vector<int> bl2 = TD3knBlockcreation(j2[0], l, p, n, k, f, x);
	}
	for (int el1 = 0; el1 < k; el1++)
	{
		for (int el2 = 0; el2 < k; el2++)
		{
			cc[0] = bl1[el1];
			cc[1] = bl1[el2];
			vector<int> cens1 = cens(id_block(cc[0], l, p, m, n, x, f), id_block(cc[1], l, p, m, n, x, f), l, p, k, n, m, x, f); 
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
					vector<vector<int>> rez1 = Algoritm3_normal(j1, prom1, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez2 = Algoritm3_normal(prom2, j2, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez3(0);
					if (prom1 != prom2)
						rez3 = Algoritm3_normal(prom1, prom2, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
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

vector<int> censfa3(vector<int> arr, bool dual, int m, int l, int p,int n, int k, Polynom f, Polynom x) {
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
		vector<int> bl;
		if (m == 2) {
			bl = TDknBlockcreation(s,l,p,n,m,f,x);
		}
		if (m == 3) {
			bl = TD3knBlockcreation(s,l,p,n,m,f,x);
		}
		for (const auto &item : bl)
		{
			rez.insert(item);
		}
	}
	else
	{
		vector<int> bl;
		if (m == 2) {
			bl = GTDknN(s,l,p,n,m,f,x);
		}
		if (m == 3) {
			bl = GTD3knN(s,l,p,n,m,f,x);
		}
		for (const auto &item : bl)
		{
			rez.insert(item);
		}
	}
	for (int i = 1; i < arr.size(); i++)
	{
		buf = rez;
		rez.clear();
		s = arr[i];
		set<int> bl;
		if (dual == false)
		{
			vector<int> blp;
			if (m == 2) {
				blp = TDknBlockcreation(s,l,p,n,m,f,x);
			}
			if (m == 3) {
				blp = TD3knBlockcreation(s,l,p,n,m,f,x);
			}
			for (const auto &item : blp)
			{
				bl.insert(item);
			}
		}
		else
		{
			vector<int> blp;
			if (m == 2) {
				blp = GTDknN(s, l, p, n, m, f, x);
			}
			if (m == 3) {
				blp = GTD3knN(s, l, p, n, m, f, x);
			}
			for (const auto &item : blp)
			{
				bl.insert(item);
			}
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

vector<vector<int>> Algoritm3_normalTD(vector<int> j1, vector<int> j2, int n, int l, int p, int m, int k, Polynom x, Polynom f,
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
	vector<int> cens0 = censfa3(cc, false, m, l, p, n, k, f, x);
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
			if ((el == j1[1]) && (!pcel(prom1, L_pc)) && (!dblockpcel(j1, L_dblpc))
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
				&& (!dblockpcel(prom2, L_dblpc)) && (!dblockpcel(j2, L_dblpc))
				&& (blockexistence(j1[0], L_block)) && (blockexistence(j2[0], L_block)))
			{
				rez = vector<vector<int>>(3);
				rez[0] = j1;
				rez[1] = prom2;
				rez[2] = j2;
				return rez;
			}
			else if ((!pcel(prom2, L_pc)) && (!pcel(prom1, L_pc)) && (!blockpcel(j1, L_blpc)) && (!blockpcel(prom2, L_blpc))
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


vector<vector<int>> Algoritm3TD(vector<int> j1, vector<int> j2, int n, int l, int p, int m, int k, Polynom x, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock)
{
	vector<vector<int>> rez;
	rez = vector<vector<int>>(0);
	if (pcel(j1, L_pc) || pcel(j2, L_pc) || (!blockexistence(j1[0], L_block)) || (!blockexistence(j2[0], L_block)))
	{
		return rez;
	}
	rez = Algoritm3_normalTD(j1, j2, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
	if (rez.size() != 0)
	{
		return rez;
	}
	vector<int> cc(2);
	vector<int> bl1, bl2;
	if (m == 2) {
		bl1 = TDknBlockcreation(j1[0], l, p, n, k, f, x);
		bl2 = TDknBlockcreation(j2[0], l, p, n, k, f, x);
	}
	if (m == 3) {
		bl1 = TD3knBlockcreation(j1[0], l, p, n, k, f, x);
		bl2 = TD3knBlockcreation(j2[0], l, p, n, k, f, x);
	}
	for (int el1 = 0; el1 < k; el1++)
	{
		for (int el2 = 0; el2 < k; el2++)
		{
			cc[0] = bl1[el1];
			cc[1] = bl1[el2];
			vector<int> cens1 = censfa3(cc, true, m, l, p, n, k, f, x);
			for (int j = 0; j < cens1.size(); j++)
			{
				if ((blockexistence(cens1[j], L_block)))
				{
					vector<int> prom1(2);
					prom1[0] = cens1[j];
					prom1[1] = bl1[el1];
					vector<int> prom2(2);
					prom2[0] = cens1[j];
					prom2[1] = bl1[el2];
					vector<vector<int>> rez1 = Algoritm3_normalTD(j1, prom1, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez2 = Algoritm3_normalTD(prom2, j2, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
					vector<vector<int>> rez3(0);
					if (prom1 != prom2)
						rez3 = Algoritm3_normalTD(prom1, prom2, n, l, p, m, k, x, f, L_pc, L_blpc, L_dblpc, L_block, L_dblock);
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