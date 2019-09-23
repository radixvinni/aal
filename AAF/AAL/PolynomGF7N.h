/*
		MPEI Algebraic Abstractions Library,
		2007-2019,
		Moscow Power Engineering Institute
		This file contains definitions and definitions of the following classes:
			PolynomGF7N
*/
#ifndef _include_PolynomGF7N_h
#define _include_PolynomGF7N_h

#include <list>
#include <string>
#include <math.h>
#include <exception>
#include <vector>
#include <unordered_set>
#include <set>
#include <fstream>
#include "BasicType.h"
namespace AAL {
	typedef short int             aal_int16;
	typedef unsigned short int    aal_uint16;
	typedef int                   aal_int32;
	typedef unsigned int          aal_uint32;
	typedef unsigned __int64      aal_uint64;

	using namespace std;

	// Макс. степень полинома
	const aal_int16 DEG_MAX = 4150;

	/** КОНСТАНТЫ ПАРАЛЛЕЛЬНОЙ УПАКОВКИ ЭЛЕМЕНТОВ В ТРИ МАССИВА */
	// Размер массива упакованных коэффициентов полинома
	const int TYPE_LEN = 32;
	const int LOG2_TYPE_LEN = 5;
	const int PAR_PACK_LEN = DEG_MAX / TYPE_LEN + 1;

	// таблица частного для различных сочетаний делимого и делителя в поле GF7
	// индекс строки - значение делителя-1, индекс столбца - значение делимого
	const aal_uint16 qcoeff[6][7] = { { 0, 1, 2, 3, 4, 5, 6 },
	{ 0, 4, 1, 5, 2, 6, 3 },
	{ 0, 5, 3, 1, 6, 4, 2 },
	{ 0, 2, 4, 6, 1, 3, 5 },
	{ 0, 3, 6, 2, 5, 1, 4 },
	{ 0, 6, 5, 4, 3, 2, 1 } };

	// Структура для хранения множителей при разложении чисел
	struct DecompositionMemberN {
		aal_uint32 value; // значение множителя
		aal_uint32 deg; // степень множителя
	};

	// Таблица простых чисел до 2049, сгенерированных с помощью решета Эратосфена
	const unordered_set<int> PrimeNumbersSet = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
												89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
												181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
												281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
												397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
												503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617,
												619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
												743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859,
												863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
												997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091,
												1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201,
												1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301,
												1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433,
												1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531,
												1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621,
												1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747,
												1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873,
												1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997,
												1999, 2003, 2011, 2017, 2027, 2029, 2039 };

	// Полином над полем GF[7]
	class PolynomGF7N {

		// КОНСТРУКТОРЫ
	public:
		/** Конструктор нулевого полинома */
		PolynomGF7N();
		/** Конструктор нулевого полинома заданой длины */
		PolynomGF7N(int a_deg);
		/** Конструктор копирования*/
		PolynomGF7N(const PolynomGF7N& a_pgf7);

		/** Конструктор:
		* \param a_coeffs - массив коэффициентов полинома
		*  \param a_size   - размер массива: степень полинома + 1*/
		PolynomGF7N(aal_uint16 * a_coeffs, int a_size);
		/** Конструктор строковый */
		PolynomGF7N(string & a_strgf7);
		/** Конструктор строковый */
		PolynomGF7N(char *a_str);
		/** Деструктор */
		~PolynomGF7N();

		//###############################################################################################
		// ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ
	public:

		/** Возвращает степень полинома */
		int GetDeg() const;
		/** Устанавливает степень полинома */
		void SetDeg(int a_deg) { m_deg = a_deg; }

		/** Проверяется условие равенства '0' всех коэффициентов полинома
		*  \return             - true - все коэффициенты = 0 */
		bool isNull() const;

		/** Возвращает указатель на массив коэффициентов полинома */
		aal_uint16 * GetCoeffsPtr() const;
		/** Возвращает указатель на массив 0-х, 1-х или 2-х битов коэффициентов
		* \param a_num = {0, 1, 2}
		*/
		aal_uint32 * GetParCoeffsPtr(int a_num) const;

		/** Возвращает строку коэффициентов полинома */
		string ToString();

		/** Преобразование коэффициентов из трёх параллельных массивов в один линейный */
		void ParPackToUnPack();
		/** Преобразование коэффициентов из одного линейного в три параллельных массива */
		void UnPackToParPack();

		/** Удаление лишних нулей */
		void TrimZero();

		/** Генерация случайного полинома из кольца, образованным многочленом a_mod_pol, степень генерируемоо полинома на 1 меньше степени a_mod_pol */
		PolynomGF7N& Generate(const PolynomGF7N& a_mod_pol);

		/** Сдвиг полинома вправо на a_val коэффициентов (умножение на полином x^a_val) упаковка в 3 массива */
		void Shift_R_ParallelPack(aal_uint32 a_val);
		/** Сдвиг полинома влево на a_val коэффициентов (умножение на полином x^a_val) упаковка в 3 массива */
		void Shift_L_ParallelPack(aal_uint32 a_val);

		/** Разложение показателя степени по степеням a_p */
		void DegDecomp(aal_uint32 *a_decomp, aal_uint32 a_deg, int a_p) const;
		/** Количество элементов в массиве разложения */
		int DegDecompLength(aal_uint32 a_val, int a_p) const;

		/** Метод вычисления перестановки для переставленного базиса */
		vector<int> GetPermutation(int a_n) const;
		/** Метод вычисления обратной перестановки к заданной */
		vector<int> InversePermutation(std::vector<int>& a_perm) const;

		/** Разложение числа на простые множители
		*  \param  a_fact - вектор разложения
		*  \param  a_deg - разлагаемая степень
		*  \param  degreeFlag = false (по умолчанию), если требуется разложение без
		показателей степеней у множителей (с дублированием множителей)
		*  \param  degreeFlag = true, если требуется разложение с показателями степеней
		*  \return        - произведение */
		void Factorization(std::vector<DecompositionMemberN>& a_fact, aal_uint32 a_deg, bool degreeFlag = false) const;

	public:
		/** Перегрузка логических операторов: == */
		bool operator == (const PolynomGF7N& a_pol) const;
		/** Перегрузка логических операторов: != */
		bool operator != (const PolynomGF7N& a_pol) const;
		/** Перегрузка операторa = */
		PolynomGF7N& operator =  (const PolynomGF7N& a_pol);

		//###############################################################################################
		// ОСНОВНЫЕ АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ НАД ПОЛИНОМАМИ
	public:

		/** Побитовое умножение двух элементов поля GF(7)
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова
		*  \param  a_val1 - 1-е слагаемое
		*  \param  a_val1 - 2-е слагаемое
		*  \return произведение */
		aal_uint16 gf7_mul_coeffs(aal_uint16& a_val1, aal_uint16& a_val2);

		/** Побитовое сложение двух элементов поля GF(7)
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова
		*  \param  a_val1 - 1-е слагаемое
		*  \param  a_val1 - 2-е слагаемое
		*  \return произведение */
		aal_uint16 gf7_add_coeffs(aal_uint16& a_val1, aal_uint16& a_val2);

		static PolynomGF7N default_quot;
		/** Деление полиномов с остатком с использованием побитовых операций
		*  \param  a_pol1      - 1-й делимое
		*  \param  a_pol2      - 2-й делитель
		*  \param  a_pol_quot  - полином для хранения частного (необязательный параметр)
		*  \return             - остаток от деления a_pol1 на a_pol2 */
		PolynomGF7N& Div(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2, PolynomGF7N& a_pol_quot = default_quot);

		/** Обращение полинома на основании алгоритма Евклида
		*  с использованием побитовых операций
		*  \param  a_pol          - обращаемый полином
		*  \param  a_simple_pol   - полином, взаимно простой с первым
		*  \param  a_is_irr       - признак второго полинома (если =true - неприводимый)
		*  \return                - обратный полином */
		PolynomGF7N& InverseMod(PolynomGF7N& a_pol, PolynomGF7N& a_simple_pol, bool a_is_irr);

		/** побитовое сложение двух полиномов в кольце GF(7)[X]
		*  с упаковкой коэффициентов в три массива
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*  \param  a_pol1 - 1-е слагаемое
		*  \param  a_pol2 - 2-е слагаемое
		*  \return        - сумма */
		PolynomGF7N& Add(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2);

		/** побитовое сложение двух полиномов в кольце GF7[X](x)mod f(x)
		*  с упаковкой коэффициентов в три массива
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*
		*  \param  a_pol1 - 1-е слагаемое
		*  \param  a_pol2 - 2-е слагаемое
		*  \return        - сумма */
		PolynomGF7N& ModAdd(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2, PolynomGF7N& a_pol_mod);

		/** побитовое сложение двух полиномов в GF(7^n)
		*  с упаковкой коэффициентов в три массива
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*
		*  \param  a_pol1 - 1-е слагаемое
		*  \param  a_pol2 - 2-е слагаемое
		*  \return        - сумма */
		PolynomGF7N& AddInGF7_n(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2, PolynomGF7N& a_pol_mod);

		/** побитовое умножение двух полиномов в кольце GF(7)[X]
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*  с упаковкой в три массива типа aal_uint32 СТОЛБИКОМ
		*
		*  \param  a_pol1 - 1-й сомножитель
		*  \param  a_pol2 - 2-й сомножитель
		*  \return        - произведение */
		PolynomGF7N& Mul(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2);

		/** побитовое умножение двух полиномов в кольце GF(7)[X] mod f(x)
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*  с упаковкой в три массива типа aal_uint32 СТОЛБИКОМ
		*
		*  \param  a_pol1 - 1-й сомножитель
		*  \param  a_pol2 - 2-й сомножитель
		*  \return        - произведение */
		PolynomGF7N& ModMul(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2, PolynomGF7N& a_pol_mod);

		/** побитовое умножение двух полиномов в поле GF(7^n)
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*  с упаковкой в три массива типа aal_uint32 СТОЛБИКОМ
		*
		*  \param  a_pol1 - 1-й сомножитель
		*  \param  a_pol2 - 2-й сомножитель
		*  \return        - произведение */
		PolynomGF7N& MulGF7_n(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2, PolynomGF7N& a_pol_mod);

		/** побитовое умножение двух полиномов в поле GF(7^n)
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*  с упаковкой в три массива типа aal_uint32 СТОЛБИКОМ
		*  и с использованием оптимальных нормальных базисов для приведения по mod
		*
		*  \param  a_pol1 - 1-й сомножитель
		*  \param  a_pol2 - 2-й сомножитель
		*  \param  a_n    - степень расширения поля
		*  \return        - произведение */
		PolynomGF7N& MulGF7_n_ONB(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2, int a_n);

		/** побитовое вычитание двух полиномов над полем GF7[X]
		*  с упаковкой в три массива типа aal_uint32
		*  \param  a_pol1 - уменьшаемое
		*  \param  a_pol2 - вычитаемое
		*  \return        - разность */
		PolynomGF7N& Sub(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2);

		/** Вычисление НОД двух полиномов по алгоритму Евклида
		*  с использованием стандартных операций
		*  \param  a_pol1      - 1-й полином
		*  \param  a_pol2      - 2-й полином
		*  \return             - НОД a_pol1 и a_pol2 */
		PolynomGF7N& GCD(PolynomGF7N& a_pol1, PolynomGF7N& a_pol2);

		/** Возведение полинома a_pol в степень a_deg в кольце GF(7)[x]
		*  с использованием операций упаковки 3x32
		*  \param  a_pol      - полином
		*  \param  a_deg      - показатель степени
		*  \return             - степень полинома a_pol^a_deg */
		PolynomGF7N& Pow(PolynomGF7N& a_pol, aal_uint32 a_deg);

		/** Возведение полинома a_pol в степень a_deg в кольце GF(7)[x] mod f(x)
		*  с использованием операций упаковки 3x32
		*  \param  a_pol      - полином
		*  \param  a_deg      - показатель степени
		*  \param  a_pol_mod  - модулярный полином
		*  \return            - степень полинома a_pol^a_deg */
		PolynomGF7N& ModPow(PolynomGF7N& a_pol, aal_uint32 a_deg, PolynomGF7N& a_pol_mod);

		/** Возведение полинома a_pol в степень a_deg GF(7^n)
		*  с использованием операций упаковки 3x32
		*  \param  a_pol      - полином
		*  \param  a_deg      - показатель степени
		*  \param  a_pol_mod  - неприводимый модулярный полином
		*  \return            - степень полинома a_pol^a_deg */
		PolynomGF7N& PowGF7_n(PolynomGF7N& a_pol, aal_uint32 a_deg, PolynomGF7N& a_pol_mod);

		/** Возведение полинома a_pol в степень a_deg GF(7^n)
		*  с использованием ОНБ 2 или 3 типов при возведении в степень характеристики поля.
		*  Используется для теста и сравнения результатов со стандартной реализацией
		*  \param  a_pol      - полином в переставленном ОНБ
		*  \param  a_deg      - показатель степени
		*  \param  a_pol_mod  - неприводимый модулярный полином
		*  \return            - степень полинома a_pol^a_deg */
		PolynomGF7N& PowGF7_n_ONB(PolynomGF7N& a_pol, aal_uint32 a_deg, PolynomGF7N& a_pol_mod);

		/** Тестирование неприводимости многочлена
		* \param a_pol - тестируемый полином */
		bool isIrreducible() const;

		/** Генерация неприводимого двучлена
		*  \param  a_deg      - степень генерируемого полинома
		*  \return            - неприводимый двучлен над GF7 */
		PolynomGF7N& GenerateBinIrreducible(const aal_uint32 a_deg);

		/** Генерация неприводимого трёхчлена
		*  \param  a_deg      - степень генерируемого полинома
		*  \return            - неприводимый двучлен над GF7 */
		PolynomGF7N& GenerateTrinIrreducible(const aal_uint32 a_deg);

		/** Генерация неприводимого полинома для ОНБ 2-го или 3-го типа
		*  \param  a_deg      - степень генерируемого полинома
		*  \return            - неприводимый двучлен над GF7 */
		PolynomGF7N& GenerateGNBIrreducible(const aal_uint32 a_deg);

		/** Вычсление порядка элемента (полинома) мультипликативной группы поля GF(7^n)
		*  \param  a_pol      - элемент мультипликативной группы
		*  \param  a_pol_mod  - неприводимый многочлен над полем GF(7^n)
		*  \param  a_ord      - порядок мультипликативной группы поля
		*  \return            - порядок элемента мультипликативной группы поля GF(7^n) */
		int ElementOrder(PolynomGF7N& a_pol, PolynomGF7N& a_pol_mod, const int a_ord);

		/** Тестирование образующего элемента
		*  \param  a_pol      - элемент мультипликативной группы
		*  \param  a_pol_mod  - неприводимый многочлен над полем GF(7^n)
		*  \param  a_ord      - порядок поля
		*  \return            - неприводимый двучлен над GF7 */
		bool IsGenerator(PolynomGF7N& a_pol, PolynomGF7N& a_pol_mod, const int a_ord);

		/** Тестирование полинома на примитивность
		*  \param  a_pol      - многочлен над полем GF(7^n)
		*  \return            - true, если полином примитивный
		false - в противном случае */
		bool isPrimitivity() const;

		/** Функция, проверяющая существования гауссова нормального базиса
		*  1-го или 2-го порядка для указанной степени расширения поля
		*  \param  a_n - степень расширения поля
		*  \return 0 - гауссовых нормальных базисов не существует
		*		   1 - существует гауссов нормальный базис 1-го порядка
		*		   2 - существует гауссов нормальный базис 2-го порядка
		*		   3 - существуют гауссовы нормальные базисы 1-го и 2-го порядка*/
		int GNB_Test(const int a_n) const;

		/** побитовое сложение 32 чисел над полем GF7[X]
		*  с упаковкой в три массива типа aal_uint32
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*
		*  \param  a_val1 - 1-е слагаемое
		*  \param  a_val2 - 2-е слагаемое
		*  \return        - сумма */
		void gf7_sum_Parallelpack(const aal_uint32 a_val11,
			const aal_uint32 a_val12,
			const aal_uint32 a_val13,
			const aal_uint32 a_val21,
			const aal_uint32 a_val22,
			const aal_uint32 a_val23,
			aal_uint32 *a_sum1,
			aal_uint32 *a_sum2,
			aal_uint32 *a_sum3);

		/** побитовое умножение 32 чисел над полем GF7[X]
		*  с упаковкой в три массива типа aal_uint32
		*  по алгоритму из статьи С.Б.Гашкова, А.Б.Фролова и др.
		*
		*  \param  a_val1 - 1-е слагаемое
		*  \param  a_val2 - 2-е слагаемое
		*  \return        - произведение */
		void gf7_mul_Parallelpack(const aal_uint32 a_val11,
			const aal_uint32 a_val12,
			const aal_uint32 a_val13,
			const aal_uint32 a_val21,
			const aal_uint32 a_val22,
			const aal_uint32 a_val23,
			aal_uint32 *a_prod1,
			aal_uint32 *a_prod2,
			aal_uint32 *a_prod3);


		/** Побитовое умножение полинома на число в GF7[X]
		*  \param  a_pol1 - полином
		*  \param  a_val  - константа
		*  \return произведение */
		PolynomGF7N& gf7_mult_num_ParPack(PolynomGF7N& a_pol, aal_uint32 a_val);

		/** Возведение в 7 степень в полиномиальном базисе
		*  \param  a_pol - полином
		*  \return       - полином в степени 7 */
		PolynomGF7N& Pow7(PolynomGF7N& a_pol);

		/** Возведение в степень характеристики поля в переставленном базисе
		*  \param  a_pol      - полином
		*  \param  a_7deg     - показатель степени характеристики поля
		*  \param  a_pol_mod  - неприводимый многочлен
		*  \return            - полином в степени 7^a_7deg */
		PolynomGF7N& Pow7_NB(PolynomGF7N& a_pol, aal_uint32 a_7deg, PolynomGF7N& a_pol_mod);

		/** Возведение в степень характеристики поля в переставленном базисе
		*   используется в ТЕСТОВОМ методе возведения полинома в любую степень для сравнения
		*   со стандартной реализацией
		*  \param  a_pol      - полином
		*  \param  a_perm     - прямая перестановка
		*  \param  a_inv_perm - обратная перестановка
		*  \param  a_7deg     - показатель степени характеристики поля
		*  \param  a_n        - степень расширения поля
		*  \return            - полином в степени 7^a_7deg */
		PolynomGF7N& Pow7_NB_TEST(PolynomGF7N& a_pol, vector<int>& a_perm, vector<int> a_inv_perm, int a_7deg, int a_n);

		/** Возведение элемента поля в степень
		*  \param  a_elem - элемент поля GF(p)
		*  \param  a_deg  - показатель степени
		*  \param  a_p    - характеристика поля
		*  \return        - степень a_deg элемента поля a_elem */
		aal_uint32 PowGFp(aal_uint32 a_elem, int a_deg, int a_p) const; 

		// ###############################################################################################
		// МЕТОДЫ ПЕРЕВОДА В НОРМАЛЬНЫЕ БАЗИСЫ
	public:
		/** Перевод из полиномиального базиса в приведённый
		* param a_pol - полином в полиномиальном базисе
		*  \return полином в приведённом базисе */
		PolynomGF7N& PolynomialToReduced(const PolynomGF7N& a_pol, int a_n);
		/** тест */
		PolynomGF7N& PToR_TEST(PolynomGF7N& a_pol, int a_n, int& add_f0, int& add_fk, int& mul_f0, int& mul_fk, int& b_size, int& k_step);
		/** тест */
		PolynomGF7N& PToR_TEST_OLD(PolynomGF7N& a_pol, int a_n, int& add_f0, int& add_fk, int& mul_f0, int& mul_fk, int& b_size, int& k_step);

		/** Перевод из приведённого базиса в полиномиальный
		* param a_pol - полином в приведённом базисе
		*  \return полином в приведённом базисе */
		PolynomGF7N& ReducedToPolynomial(const PolynomGF7N& a_pol, int a_n);
		/** тест */
		PolynomGF7N& RToP_TEST(PolynomGF7N& a_pol, int a_n, int& add_f0, int& add_fk, int& mul_f0, int& mul_fk, int& b_size, int& k_step);

		/** Перевод из приведённого базиса в полиномиальный
		* param a_pol - полином в приведённом базисе
		* param a_n   - степень расширения поля
		*  \return полином в приведённом базисе */
		PolynomGF7N& ReducedToRedundant(const PolynomGF7N& a_pol, int a_n);

		/** Перевод из редундантного базиса в приведённый
		* param a_pol - полином в редундантном базисе
		* param a_n   - степень расширения поля
		*  \return полином в приведённом базисе */
		PolynomGF7N& RedundantToReduced(const PolynomGF7N& a_pol, int a_n);

		/** Перевод из приведённого базиса в переставленный
		* param a_pol - полином в приведённом базисе
		* param a_n   - степень расширения поля
		*  \return полином в переставленном базисе */
		PolynomGF7N& ReducedToPermuted(const PolynomGF7N& a_pol, int a_n);

		/** Перевод из переставленного базиса в приведённый
		* param a_pol - полином в переставленном базисе
		* param a_n   - степень расширения поля
		*  \return полином в приведённом базисе */
		PolynomGF7N& PermutedToReduced(const PolynomGF7N& a_pol, int a_n);

	private:
		// степень полинома
		int m_deg;

		// Представление полинома в виде массива коэффициентов.
		// Свободный член полинома - первый элемент массива.
		aal_uint16 * m_pcoeffs;

		// Массив 0-х битов коэффициентов
		aal_uint32 m_b0[PAR_PACK_LEN];
		// Массив 1-х битов коэффициентов
		aal_uint32 m_b1[PAR_PACK_LEN];
		// Массив 2-х битов коэффициентов
		aal_uint32 m_b2[PAR_PACK_LEN];

	};
}
#endif