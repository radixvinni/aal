//#include "stdafx.h"
#include <iostream>
#include <iostream>
#include "./AAF/AAL/Polynom.h"
//#include "./AAF/AAL/PolynomGF2_mY_7.h"
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
Polynom xPowGF2_n(int i, int l, int p, Polynom x, Polynom f);
int ind(string ell, int l, int p, Polynom x, Polynom f);
int Phi(Polynom poly_el[], int len, int n, int l, int p, Polynom x, Polynom f);
vector<int> TDknBlockcreation(int numer, int l, int p, int n, int k, Polynom f, Polynom x);
vector<int> GTDknN(int key, int l, int p, int n, int m, Polynom f, Polynom x);
vector<int> TD3knBlockcreation(int numer, int l, int p, int n, int k, Polynom f, Polynom x);
vector<int> GTD3knN(int key, int l, int p, int n, int m, Polynom f, Polynom x);
vector<int> blocksWith(int j1, int j2, int m, int l, int p, int n, int k, Polynom f, Polynom x);
vector<int> TDBlockcreation(int numer,int m, int l, int p, int n, int k, Polynom f, Polynom x);
int ALG1(int p, int l, Polynom ff, vector<DecompositionMember> s, vector<DecompositionMember> d);
bool NextSet(vector<int> &a, int n, int m);
Polynom razlP(int p, int num, int l);
Polynom genPrimitiveF2l(int p, int l);
string outF2l(Polynom pol);


vector<int> decToN(int a,int n);
vector<string> PhiInverse(int j, int l, int p, int m, int n, Polynom x, Polynom f);
vector<string> id_block(int j, int l, int p, int m, int n, Polynom x, Polynom f);
Polynom tr(Polynom x_poly, int l, Polynom f);
Polynom SqrtGF2_n(Polynom a, int n, Polynom f);
vector<string> SolveQuadraticEquationGF2N(vector<string> idj1, vector<string> idj2, int l, int p, int n, Polynom x, Polynom f);
vector<int> cens(vector<string> idj1, vector<string> idj2, int l, int p, int k, int n, int m, Polynom x, Polynom f);
bool kel(int kn, vector<int> L_key);
bool bkel(int bn, int kn, set<vector<int>> L_blockkey);
bool bbel(int bn1, int bn2, set<vector<int>> L_blockblock);
bool blockexistence(int bn, vector<int> L_block);
vector<int> psiinv(int j, int l, int p, int k, int n, int m, Polynom x, Polynom f);
vector<int> dualhiinv(int key, int l, int p, int n, int m, Polynom x, Polynom f);
vector<int> algoritm1(int j1, int j2, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block,
	int l, int p, int k, int n, int m, Polynom x, Polynom f);
string out_alg1(int j1, int j2, vector<int> out);
vector<vector<string>> algoritm2(int j1, int j2, vector<int> L_key, set<vector<int>> L_blockkey, set<vector<int>> L_blockblock, vector<int> L_block,
	int l, int p, int k, int n, int m, Polynom x, Polynom f);
vector<vector<int>> algoritm3(vector<int> j1, vector<int> j2, int l, int p, int k, int n, int m, Polynom x, Polynom f);
//string out_alg2(vector<vector<string>> out, int len, int n, int l, int p, Polynom x, Polynom f);
string out_alg2(vector<vector<string>> out);
string out_alg3(vector<vector<int>> out);
string out_set_vector_dig2(set<vector<int>> out);
string out_vector(vector<int> out);
//set<vector<int>> split_str_in_set_vec_int(string str_sp);

vector<int> censfa3(vector<int> arr, bool dual, int m, int l, int p, int n, int k, Polynom f, Polynom x);
vector<vector<int>> Algoritm3_normalTD(vector<int> j1, vector<int> j2, int n, int l, int p, int m, int k, Polynom x, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock);
vector<vector<int>> Algoritm3TD(vector<int> j1, vector<int> j2, int n, int l, int p, int m, int k, Polynom x, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock);