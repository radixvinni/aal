#include "funTD.h"
#include <iostream>
#include "./AAF/AAL/Polynom.h"
#include "./AAF/AAL/PolynomGF2_m_4.h"
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

Polynom Setf(int l);
Polynom xPow(int i, Polynom f);
int ind(Polynom ell, Polynom f);
int Psi(PolynomGF2_m_4 el, Polynom f, int d, int n);
PolynomGF2_m_4 PsiInverse(int N, Polynom f, int n);
PolynomGF2_m_4 Psi3Inverse(int N, Polynom f, int n, int k);
PolynomGF2_m_4 vectorsum(PolynomGF2_m_4 a, PolynomGF2_m_4 b, int d, Polynom f);
PolynomGF2_m_4 vectorproduct(PolynomGF2_m_4 a, PolynomGF2_m_4 b, int d, Polynom f);
PolynomGF2_m_4 vectorsub(PolynomGF2_m_4 a, PolynomGF2_m_4 b, int d, Polynom f);
PolynomGF2_m_4 mulbyscalar(PolynomGF2_m_4 a, Polynom b, int d, Polynom f);
vector<int> ProjectivePlaneBlokCreation(int s, int n, int d, Polynom f);
int newelement(int r, int s, int n, int d, Polynom f);
vector<int> DualProjectivePlaneBlokCreation(int s, int n, int d, Polynom f);
vector<int> ProjectiveGeometryBlokCreation(int s, int n, int k, int d, Polynom f);
vector<int> NumsOfBlocksWithBas(int el, int n, int k);
vector<int> InterOfTwoBasEl(int el1, int el2, int n, int k);
int Predic(PolynomGF2_m_4 el, int b1, int b2, int n, int k, int d, Polynom f);
vector<int> NotZero(int b1, int b2, int s, int n, int k, int d, Polynom f);
vector<int> DualProjectiveGeometryBlokCreation(int s, int n, int k, int d, Polynom f);
vector<int> AcicleBlok(int s, int n, int k, int d, Polynom f);
vector<int> DualAcicleBlok(int s, int n, int k, int d, Polynom f);
vector<string> PolAcicleBlok(int s, int n, int k, int d, Polynom f);
vector<string> PolDualAcicleBlok(int s, int n, int k, int d, Polynom f);
vector<int> cens(vector<int> arr, bool dual, int n, int k, int d, Polynom f);
int id(int j);
vector<int> psiinv(int s, int n, int k, int d, Polynom f);
vector<int> dualhiinv(int s, int n, int k, int d, Polynom f);
string id_str(int num, int n, int k, int d, Polynom f);
vector<int> Algoritm1(int j1, int j2, vector<int> Lkey, vector<int> Lblock, set<vector<int>> Lblockkey, set<vector<int>> Lblockblock, int n, int k, int d, Polynom f);
vector<string> Algoritm2(int j1, int j2, vector<int> Lkey, vector<int> Lblock, set<vector<int>> Lblockkey, set<vector<int>> Lblockblock, int n, int v, int k, int d, Polynom f);
vector<vector<int>> Algoritm3_normal(vector<int> j1, vector<int> j2, int n, int v, int k, int d, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock);
vector<vector<int>> Algoritm3(vector<int> j1, vector<int> j2, int n, int v, int k, int d, Polynom f,
	set<vector<int>> L_pc, set<vector<int>> L_blpc, set<vector<int>> L_dblpc, vector<int> L_block, vector<int> L_dblock);