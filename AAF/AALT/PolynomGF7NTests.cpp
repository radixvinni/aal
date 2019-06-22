/*
    MPEI Algebraic Abstractions Library,
    2007-2019,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:
		AAL::PolynomGF7N

*/
#include "./CppUnitLite/TestHarness.h"

#include <iostream>
#include <chrono>
#include <time.h>
#include "AAF/AAL/PolynomGF7N.h"
#include <fstream>

using namespace AAL;
using namespace std;

TEST(PolynomGF7N, Add) {
	PolynomGF7N p1("1234525");
	PolynomGF7N p2("1321425");
	PolynomGF7N p3("2555243");
	PolynomGF7N res_1("5413551");
	PolynomGF7N res_2("3012456");
	PolynomGF7N res_3("142523");
	PolynomGF7N pol_0("0");

	PolynomGF7N c;

	CHECK(!(p1.ToString() != "1234525"));
	CHECK(!(p2.ToString() != "1321425"));
	CHECK(!(c.Add(p1, p2) != p3));
	CHECK(!(c.Add(res_3, pol_0) != res_3));
	CHECK(!(c.Add(res_1, res_2) != res_3));
	
}

TEST(PolynomGF7N, Mul) {
	PolynomGF7N p1("1232563");
	PolynomGF7N p2("1");
	PolynomGF7N p3("2");
	PolynomGF7N res_1("1232563");
	PolynomGF7N res_2("2464356");
	PolynomGF7N pol_0("0");

	PolynomGF7N c;

	CHECK(!(c.Mul(p1, p2) != res_1));
	CHECK(!(c.Mul(p1, p3) != res_2));
	CHECK(!(c.Mul(res_1, pol_0) != pol_0));
}

TEST(PolynomGF7N, Div) {
	PolynomGF7N p1("1232563");
	PolynomGF7N p2("13213");
	PolynomGF7N p3("222222");
	PolynomGF7N res_1;
	PolynomGF7N res_2;
	PolynomGF7N quot, rem, c;

	res_1.Mul(p1, p2);
	res_2.Mul(p2, p3);

	// Проверка частного
	rem.Div(res_1, p1, quot);
	CHECK(!(quot != p2));
	// Проверка остатка
	rem.Div(res_2, p3, quot);
	c.Mul(p3, quot);
	c.Add(c, rem);
	CHECK(!(c != res_2));
}

TEST(PolynomGF7N, isIrreducible) {
	PolynomGF7N p10("101");
	PolynomGF7N p11("2000000001");
	PolynomGF7N p12("2000000000000000000000000001");
	PolynomGF7N p1_not("24121434");
	PolynomGF7N p1_big1("3000000000000000000000000000000000000000000000000000000000000000000000000000000001");
	PolynomGF7N p1_big2("4000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

	PolynomGF7N p20("311");
	PolynomGF7N p21("65001");
	PolynomGF7N p22("540000001");
	PolynomGF7N p23("20300000000000000001");
	PolynomGF7N p2_not("320001421");
	PolynomGF7N p2_big1("4050000000000000000000000000000000000001");
	PolynomGF7N p2_big2("600000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000005000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");

	CHECK(p12.isIrreducible());
	CHECK(p10.isIrreducible());
	CHECK(p11.isIrreducible());
	CHECK(!(p1_not.isIrreducible()));
	CHECK(p1_big1.isIrreducible());
	CHECK(p1_big2.isIrreducible());
	CHECK(p20.isIrreducible());
	CHECK(p21.isIrreducible());
	CHECK(p22.isIrreducible());
	CHECK(p23.isIrreducible());
	CHECK(!(p2_not.isIrreducible()));
	CHECK(p2_big1.isIrreducible());
	CHECK(p2_big2.isIrreducible());
}

TEST(PolynomGF7N, MUL_GNB) {
	PolynomGF7N x1, x2, prod, xbetalon, irr;

	for (int i = 3; i <= 510; i++) {
		if (x1.GNB_Test(i) != 0) {
			irr.GenerateGNBIrreducible(i);
			x1.Generate(irr);
			x2.Generate(irr);

			prod.Mul(x1, x2);
			xbetalon.Div(prod, irr);

			prod.PolynomialToReduced(prod, i);
			prod.ReducedToRedundant(prod, i);
			prod.RedundantToReduced(prod, i);
			prod.ReducedToPolynomial(prod, i);

			CHECK (prod == xbetalon);
		}
	}
}
/*
TEST(PolynomGF7N, POW_GNB) {
	PolynomGF7N x1, x2, pol, irr;

	for (int i = 3; i <= 510; i++) {
		printf("\r%2.1f%%",i/5.1);
		fflush(stdout);
		if (x1.GNB_Test(i) != 0) {

			irr.GenerateGNBIrreducible(i);
			if (irr.isIrreducible()) {

				pol.Generate(irr);
				int deg = rand();

				x1.ModPow(pol, deg, irr);
				x2.PowGF7_n_ONB(pol, deg, irr);

				if (x1 == x2) {
					continue;
				}
				else {
					cout << i << endl;
					CHECK(false);
				}
			}

		}
	}
}
/*
int main()
{
	// Тестирование операции сложения
	cout << "Add() test: " << Add_TEST() << endl;
	// Тестирование операции умножения
	cout << "Mul() test: " << Mul_TEST() << endl;
	// Тест операции деления
	cout << "Div() test: " << Div_TEST() << endl;
	// Тест проверки неприводимости
	cout << "isIrreducible() test: " << isIrreducible_TEST() << endl;
	
	// ТЕСТ ПРЕОБРАЗОВАНИЙ БАЗИСОВ С ИСПОЛЬЗОВАНИЕМ УМНОЖЕНИЯ
	cout << "MUL_GNB_TEST() test: " << MUL_GNB_TEST() << endl;

	// ТЕСТ ПРЕОБРАЗОВАНИЙ БАЗИСОВ С ИСПОЛЬЗОВАНИЕМ ВОЗВЕДЕНИЯ В СТЕПЕНЬ
	cout << "POW_GNB_TEST() test: " << POW_GNB_TEST() << endl;

    return 0;
}

*/