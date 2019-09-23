/*
	MPEI Algebraic Abstractions Library,
	2007-2019,
	Moscow Power Engineering Institute
	This file contains definitions and implementations of the following classes:
		PolynomGF7N
*/
#include "PolynomGF7.h"
#include <iostream>

namespace AAL {
	PolynomGF7N::PolynomGF7N() {
		m_deg = -1;
		m_pcoeffs = NULL;

		memset(m_b0, 0x0, sizeof(m_b0));
		memset(m_b1, 0x0, sizeof(m_b1));
		memset(m_b2, 0x0, sizeof(m_b2));

		return;
	}

	PolynomGF7N::PolynomGF7N(int a_deg) {
		m_deg = a_deg;

		m_pcoeffs = new aal_uint16[a_deg + 1];
		memset(m_pcoeffs, 0x0, sizeof(aal_uint16)*(m_deg + 1));
		memset(m_b0, 0x0, sizeof(m_b0));
		memset(m_b1, 0x0, sizeof(m_b1));
		memset(m_b2, 0x0, sizeof(m_b2));

		return;
	}

	PolynomGF7N::PolynomGF7N(const PolynomGF7N & a_pol) {
		m_deg = a_pol.GetDeg();
		m_pcoeffs = new aal_uint16[m_deg + 1];
		memcpy(m_pcoeffs, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(m_deg + 1));
		memcpy(m_b0, a_pol.GetParCoeffsPtr(0), sizeof(m_b0));
		memcpy(m_b1, a_pol.GetParCoeffsPtr(1), sizeof(m_b1));
		memcpy(m_b2, a_pol.GetParCoeffsPtr(2), sizeof(m_b2));

		return;
	}

	PolynomGF7N::PolynomGF7N(aal_uint16 * a_coeffs, int a_size) {
		m_deg = a_size - 1;

		m_pcoeffs = new aal_uint16[a_size];
		memcpy(m_pcoeffs, a_coeffs, sizeof(aal_uint16)*a_size);

		memset(m_b0, 0x0, sizeof(m_b0));
		memset(m_b1, 0x0, sizeof(m_b1));
		memset(m_b2, 0x0, sizeof(m_b2));

		UnPackToParPack();

		return;
	}

	PolynomGF7N::PolynomGF7N(string & a_str) {
		m_deg = a_str.size() - 1;

		m_pcoeffs = new aal_uint16[m_deg + 1];
		memset(m_pcoeffs, 0x0, sizeof(aal_uint16)*(m_deg + 1));
		for (int i = 0; i <= m_deg; i++) {
			char s[2] = { a_str[i], 0 };
			m_pcoeffs[i] = atoi(s);
		}
		memset(m_b0, 0x0, sizeof(m_b0));
		memset(m_b1, 0x0, sizeof(m_b1));
		memset(m_b2, 0x0, sizeof(m_b2));

		UnPackToParPack();

		return;
	}

	PolynomGF7N::PolynomGF7N(char *a_str) {
		m_deg = strlen(a_str) - 1;
		m_pcoeffs = new aal_uint16[m_deg + 1];
		memset(m_pcoeffs, 0x0, sizeof(aal_uint16)*(m_deg + 1));
		for (int i = 0; i <= m_deg; i++) {
			char s[2] = { a_str[i], 0 };
			m_pcoeffs[i] = atoi(s);
		}

		memset(m_b0, 0x0, sizeof(m_b0));
		memset(m_b1, 0x0, sizeof(m_b1));
		memset(m_b2, 0x0, sizeof(m_b2));

		UnPackToParPack();

		return;
	}

	PolynomGF7N::~PolynomGF7N() {
		if (m_pcoeffs != NULL) {
			delete[] m_pcoeffs;
		}
	}

	void PolynomGF7N::ParPackToUnPack() {
		memset(m_pcoeffs, 0x0, sizeof(aal_uint16)*(m_deg + 1));
		aal_int32 ind, offset;

		for (int i = 0; i <= m_deg; i++) {
			ind = i / TYPE_LEN;
			offset = i % TYPE_LEN;

			m_pcoeffs[i] ^= (m_b0[ind] >> offset) & 0x01;
			m_pcoeffs[i] ^= ((m_b1[ind] >> offset) & 0x01) << 1;
			m_pcoeffs[i] ^= ((m_b2[ind] >> offset) & 0x01) << 2;
		}

		return;
	}

	void PolynomGF7N::UnPackToParPack() {
		memset(m_b0, 0x0, sizeof(m_b0));
		memset(m_b1, 0x0, sizeof(m_b1));
		memset(m_b2, 0x0, sizeof(m_b2));

		aal_int32 ind, offset;

		for (int i = 0; i <= m_deg; i++) {
			ind = i / TYPE_LEN;
			offset = i % TYPE_LEN;

			m_b0[ind] ^= (m_pcoeffs[i] & 0x01) << offset;
			m_b1[ind] ^= ((m_pcoeffs[i] >> 1) & 0x01) << offset;
			m_b2[ind] ^= ((m_pcoeffs[i] >> 2) & 0x01) << offset;
		}

		return;
	}

	void PolynomGF7N::TrimZero() {
		for (int i = m_deg; i > 0; i--) {
			if (m_pcoeffs[i] == 0) {
				m_deg--;
			}
			else {
				UnPackToParPack();
				return;
			}
		}
		UnPackToParPack();
		return;
	}

	void PolynomGF7N::Shift_R_ParallelPack(aal_uint32 a_val) {

		if (a_val <= 0) {
			return;
		}
		if (m_deg + a_val > DEG_MAX) {
			return;
		}

		int  deg_cop = m_deg;

		// Индекс предыдущего элемента
		int i_1 = 0;
		// Маска для копирования старшего коэффициента
		int a = 0x80000000;

		for (int j = 0; j < a_val; j++) {
			// Количество заполненных элементов упакованного массива
			int num = (m_deg + 1) % TYPE_LEN != 0 ? (m_deg + 1) / TYPE_LEN + 1 : (m_deg + 1) / TYPE_LEN;
			// Сдвиг на 1 коэффициент влево
			for (int i = num, i_1 = i - 1; i > 0; i--, i_1--) {
				m_b0[i] <<= 1;
				m_b1[i] <<= 1;
				m_b2[i] <<= 1;

				m_b0[i] ^= (m_b0[i_1] & a) >> 31;
				m_b1[i] ^= (m_b1[i_1] & a) >> 31;
				m_b2[i] ^= (m_b2[i_1] & a) >> 31;

			}
			m_b0[0] <<= 1;
			m_b1[0] <<= 1;
			m_b2[0] <<= 1;

			// корректировка степени полинома
			m_deg++;
		}

		if (deg_cop < m_deg) {
			delete[] m_pcoeffs;
			m_pcoeffs = new aal_uint16[m_deg + 1];
		}

		ParPackToUnPack();

		return;
	}

	void PolynomGF7N::Shift_L_ParallelPack(aal_uint32 a_val) {

		if (a_val <= 0) {
			return;
		}
		if (m_deg + 1 < static_cast<int>(a_val)) {
			return;
		}

		// Количество заполненных элементов упакованного массива
		int num = (m_deg + 1) % TYPE_LEN != 0 ? (m_deg + 1) / TYPE_LEN + 1 : (m_deg + 1) / TYPE_LEN;

		// Индекс следующего элемента
		int i_1 = 0;
		// Макска для копирования младшего коэффициента
		int a = 0x00000001;

		for (aal_uint32 j = 0; j< a_val; j++) {
			// Сдвиг на 1 коэффициент вправо
			for (int i = 0, i_1 = i + 1; i < num; i++, i_1++) {
				m_b0[i] >>= 1;
				m_b1[i] >>= 1;
				m_b2[i] >>= 1;

				m_b0[i] ^= (m_b0[i_1] & a) << 31;
				m_b1[i] ^= (m_b1[i_1] & a) << 31;
				m_b2[i] ^= (m_b2[i_1] & a) << 31;
			}
			m_b0[num] >>= 1;
			m_b1[num] >>= 1;
			m_b2[num] >>= 1;

			m_deg--;
		}

		ParPackToUnPack();

		return;
	}

	PolynomGF7N& PolynomGF7N::Generate(const PolynomGF7N& a_mod_pol) {

		int deg = a_mod_pol.GetDeg() - 1;
		PolynomGF7N tmp = a_mod_pol;

		PolynomGF7N pol(deg), res;
		aal_uint16* ptr = pol.GetCoeffsPtr();

		for (int i = 0; i <= deg; i++) {
			ptr[i] = rand() % 7;
		}
		pol.TrimZero();
		pol.UnPackToParPack();
		res.Div(pol, tmp);
		*this = res;
		return *this;
	}

	bool PolynomGF7N::isNull() const {
		for (int i = 0; i < m_deg + 1; i++) {
			if (m_pcoeffs[i] > 0) {
				return false;
			}
		}
		return true;
	}

	aal_uint16 * PolynomGF7N::GetCoeffsPtr()const {
		return m_pcoeffs;
	}

	int PolynomGF7N::GetDeg()const {
		return m_deg;
	}

	bool PolynomGF7N::operator == (const PolynomGF7N & a_pol) const{

		if (m_deg != a_pol.GetDeg()) {
			return false;
		}
		else {
			// Количество заполненных элементов (групп) массивов
			int num = (m_deg + 1) % TYPE_LEN != 0 ? (m_deg + 1) / TYPE_LEN + 1 : (m_deg + 1) / TYPE_LEN;
			// Сумма пар сложенных по модулю 2 групп
			int sum = 0;

			// Указатели на массивы полинома, с которым происходит сравнение
			aal_uint32 * pol0 = a_pol.GetParCoeffsPtr(0);
			aal_uint32 * pol1 = a_pol.GetParCoeffsPtr(1);
			aal_uint32 * pol2 = a_pol.GetParCoeffsPtr(2);

			for (int i = 0; i < num; i++) {
				sum += ((m_b0[i] ^ pol0[i]) + (m_b1[i] ^ pol1[i]) + (m_b2[i] ^ pol2[i]));
			}

			if (sum == 0) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	bool PolynomGF7N::operator != (const PolynomGF7N & a_pol) const{

		if (m_deg != a_pol.GetDeg()) {
			return true;
		}
		else {
			// Количество заполненных элементов (групп) массивов
			int num = (m_deg + 1) % TYPE_LEN != 0 ? (m_deg + 1) / TYPE_LEN + 1 : (m_deg + 1) / TYPE_LEN;
			// Сумма пар сложенных по модулю 2 групп
			int sum = 0;

			// Указатели на массивы полинома, с которым происходит сравнение
			aal_uint32 * pol0 = a_pol.GetParCoeffsPtr(0);
			aal_uint32 * pol1 = a_pol.GetParCoeffsPtr(1);
			aal_uint32 * pol2 = a_pol.GetParCoeffsPtr(2);

			for (int i = 0; i < num; i++) {
				sum += ((m_b0[i] ^ pol0[i]) + (m_b1[i] ^ pol1[i]) + (m_b2[i] ^ pol2[i]));
			}

			if (sum == 0) {
				return false;
			}
			else {
				return true;
			}
		}
	}

	PolynomGF7N & PolynomGF7N::operator = (const PolynomGF7N& a_pol){

		if (*this == a_pol) return (*this);

		if (m_deg != a_pol.GetDeg()) {
			if (m_pcoeffs != NULL) {
				delete[] m_pcoeffs;
				m_pcoeffs = NULL;
			}
			m_pcoeffs = new aal_uint16[a_pol.GetDeg() + 1];
		}

		m_deg = a_pol.GetDeg();

		memcpy(m_pcoeffs, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(m_deg + 1));
		memcpy(m_b0, a_pol.GetParCoeffsPtr(0), sizeof(m_b0));
		memcpy(m_b1, a_pol.GetParCoeffsPtr(1), sizeof(m_b1));
		memcpy(m_b2, a_pol.GetParCoeffsPtr(2), sizeof(m_b2));

		return (*this);
	}

	aal_uint32 * PolynomGF7N::GetParCoeffsPtr(int a_num) const {
		if (a_num == 0) {
			return (aal_uint32 *)m_b0;
		}
		else if (a_num == 1) {
			return (aal_uint32 *)m_b1;
		}
		else if (a_num == 2) {
			return (aal_uint32 *)m_b2;
		}
		return nullptr;
	}

	string PolynomGF7N::ToString() {

		ParPackToUnPack();
		string str_coeff = "";
		char tmp;

		if (!isNull()) {
			for (int i = 0; i <= m_deg; i++) {
				str_coeff += to_string(m_pcoeffs[i]);
			}
		}

		return str_coeff;
	}

	aal_uint16 PolynomGF7N::gf7_mul_coeffs(aal_uint16 & a_val1, aal_uint16 & a_val2) {

		// вычисление знакового бита
		aal_uint16 c1 = (a_val2 ^ (a_val2 >> 1)) & 0x0001;
		aal_uint16 c2 = (a_val2 ^ (a_val2 >> 2)) & 0x0001;
		aal_uint16 m = (c1 & c2) ^ (a_val2 & 0x0001);
		m ^= (m << 1) ^ (m << 2);

		// u1, u0
		aal_uint16 u1 = c1 ^ 0x0001;
		aal_uint16 u0 = c2 ^ 0x0001;

		aal_uint16 d0 = c1 & u0;
		aal_uint16 d1 = u1 & c2;
		aal_uint16 d2 = c1 & c2;

		aal_uint16 x2 = (a_val1 >> 2) & 0x0001;
		aal_uint16 x1 = (a_val1 >> 1) & 0x0001;
		aal_uint16 x0 = a_val1 & 0x0001;

		aal_uint16 a = d2&x0 | d1&x1 | d0&x2;
		a ^= (d2&x1 | d1&x2 | d0&x0) << 1;
		a ^= (d2&x2 | d1&x0 | d0&x1) << 2;

		aal_uint16 out = a ^ m;
		return out;
	}

	aal_uint16 PolynomGF7N::gf7_add_coeffs(aal_uint16 & a_val1, aal_uint16 & a_val2) {

		// биты 1-го операнда
		aal_uint16 a0 = (a_val1 & 0x0001);
		aal_uint16 a1 = (a_val1 & 0x0002) >> 1;
		aal_uint16 a2 = (a_val1 & 0x0004) >> 2;

		// биты 2-го операнда
		aal_uint16 b0 = (a_val2 & 0x0001);
		aal_uint16 b1 = (a_val2 & 0x0002) >> 1;
		aal_uint16 b2 = (a_val2 & 0x0004) >> 2;

		// биты 0-2 суммы
		aal_uint16 e0, e1, e2;
		// бит 3 суммы
		aal_uint16 sigma;
		// биты суммы по модулю 7
		aal_uint16 z0, z1, z2;

		e0 = a0 ^ b0;
		// перенос в 1-й бит
		aal_uint16 d0 = a0 & b0;
		e1 = (a1 ^ b1) ^ d0;
		// перенос в 2-й бит
		aal_uint16 d1 = (a1 & b1) | (d0 & (a1 | b1));
		e2 = a2 ^ b2 ^ d1;
		// перенос в 3-й бит
		sigma = (a2 & b2) | (d1 & (a2 | b2)) | (e0&e1&e2);

		z0 = e0 ^ sigma;
		z1 = e1 ^ (e0 & sigma);
		z2 = e2 ^ e1 & (e0 & sigma);

		// сумма по модулю 7
		aal_uint16 out = z0;
		out |= z1 << 1;
		out |= z2 << 2;

		return out;
	}

	PolynomGF7N & PolynomGF7N::gf7_mult_num_ParPack(PolynomGF7N & a_pol, aal_uint32 a_val) {
		// полином-произведение    
		PolynomGF7N prod_pol(a_pol.GetDeg());

		// упаковка коэффициентов полинома
		a_pol.UnPackToParPack();
		// указатели на массивы коэффициентов в упакованном формате
		aal_uint32 * p1_0 = a_pol.GetParCoeffsPtr(0);
		aal_uint32 * p1_1 = a_pol.GetParCoeffsPtr(1);
		aal_uint32 * p1_2 = a_pol.GetParCoeffsPtr(2);

		*this = prod_pol;
		aal_uint32 * prod0 = m_b0;
		aal_uint32 * prod1 = m_b1;
		aal_uint32 * prod2 = m_b2;

		// вспомогательные переменные
		aal_uint32 u0, u1, d0, d1, d2, sigma, h0, h1, h2, q0, q1, q2, p0, p1, p2;

		// Константы для выбора второго множителя
		const aal_uint32 a1 = 0xFFFFFFFF;
		const aal_uint32 a0 = 0x00000000;

		// Массив значений второго множителя (от 0 до 6)
		const aal_uint32 sf[7][3] = { { a0, a0, a0 },{ a0, a0, a1 },{ a0, a1, a0 },{ a0, a1, a1 },
		{ a1, a0, a0 },{ a1, a0, a1 },{ a1, a1, a0 } };

		// количество групп в полиноме-сомножителе
		int num_p = (a_pol.GetDeg() + 1) % TYPE_LEN != 0 ? (a_pol.GetDeg() + 1) / TYPE_LEN + 1 : (a_pol.GetDeg() + 1) / TYPE_LEN;

		// установка группы-константы
		p0 = sf[a_val][2];
		p1 = sf[a_val][1];
		p2 = sf[a_val][0];

		for (int i = 0; i < num_p; i++) {
			q0 = p1_0[i];
			q1 = p1_1[i];
			q2 = p1_2[i];
			// Константы для перемножения НАЧАЛО
			sigma = (p0 ^ p1) & (p0 ^ p2) ^ p0;
			u0 = p0 ^ p2 ^ a1;
			u1 = p0 ^ p1 ^ a1;

			d0 = ~u1 & u0;
			d1 = u1 & ~u0;
			d2 = ~u1 & ~u0;
			// Константы для перемножения ОКОНЧАНИЕ

			h0 = (d2 & q0) | (d1 & q1) | (d0 & q2);
			h1 = (d2 & q1) | (d1 & q2) | (d0 & q0);
			h2 = (d2 & q2) | (d1 & q0) | (d0 & q1);

			h0 ^= sigma;
			h1 ^= sigma;
			h2 ^= sigma;

			// накопление в группе prod[i]
			gf7_sum_Parallelpack(prod0[i], prod1[i], prod2[i],
				h0, h1, h2,
				&prod0[i], &prod1[i], &prod2[i]);

			//обнуление текущей группы-произведения
			h0 ^= h0;
			h1 ^= h1;
			h2 ^= h2;
		}

		ParPackToUnPack();
		TrimZero();
		return *this;
	}

	void PolynomGF7N::gf7_sum_Parallelpack(const aal_uint32 a_val10,
		const aal_uint32 a_val11,
		const aal_uint32 a_val12,
		const aal_uint32 a_val20,
		const aal_uint32 a_val21,
		const aal_uint32 a_val22,
		aal_uint32 *a_sum1,
		aal_uint32 *a_sum2,
		aal_uint32 *a_sum3) {
		aal_uint32 s1, s2, d0, d1, d2, h0, h1, h2, sigma;

		s1 = a_val11 ^ a_val21;
		s2 = a_val12 ^ a_val22;
		d0 = a_val10 & a_val20;
		d1 = a_val11 & a_val21;
		d2 = a_val12 & a_val22;

		h0 = a_val10   ^ a_val20;
		h1 = s1        ^ d0;
		h2 = (s2 ^ d1) ^ (s1 & d0);

		sigma = (d2 ^ (s2 & d1)) ^ (s2 & (s1 & d0)) | (h0 & h1 & h2);

		*a_sum1 = h0 ^ sigma;
		*a_sum2 = h1 ^ (h0 & sigma);
		*a_sum3 = h2 ^ (h1 & (h0 & sigma));

		return;
	}


	void PolynomGF7N::gf7_mul_Parallelpack(const aal_uint32 a_val11,
		const aal_uint32 a_val12,
		const aal_uint32 a_val13,
		const aal_uint32 a_val21,
		const aal_uint32 a_val22,
		const aal_uint32 a_val23,
		aal_uint32 *a_prod1,
		aal_uint32 *a_prod2,
		aal_uint32 *a_prod3) {


		// вспомогательные переменные
		aal_uint32 u0, u1, d0, d1, d2, sigma,
			h0, h1, h2;


		const  aal_uint32 c_FFFFFFFF = 0xFFFFFFFF;
		const  aal_uint32 c_16 = 16;  // смещение

										// Константы для пересножения НАЧАЛО
		sigma = (a_val21 ^ a_val22) & (a_val21 ^ a_val23) ^ a_val21;
		u0 = a_val21 ^ a_val23 ^ c_FFFFFFFF;
		u1 = a_val21 ^ a_val23 ^ c_FFFFFFFF;

		d0 = ~u1 & u0;
		d1 = u1 & ~u0;
		d2 = ~u1 & ~u0;
		// Константы для пересножения ОКОНЧАНИЕ

		h0 = (d2 & a_val11) | (d1 & a_val12) | (d0 & a_val13);
		h1 = (d2 & a_val12) | (d1 & a_val13) | (d0 & a_val11);
		h2 = (d2 & a_val13) | (d1 & a_val11) | (d0 & a_val12);

		*a_prod1 = h0 ^ sigma;
		*a_prod2 = h1 ^ sigma;
		*a_prod3 = h2 ^ sigma;

		return;
	}

	PolynomGF7N & PolynomGF7N::Add(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2) {

		// создание полинома суммы, из полинома большей степени
		*this = a_pol1.GetDeg() >= a_pol2.GetDeg() ? a_pol1 : a_pol2;
		// полином с меньшей степенью
		PolynomGF7N& rp = a_pol1.GetDeg() < a_pol2.GetDeg() ? a_pol1 : a_pol2;

		aal_uint32 s1, s2, d0, d1, d2, h0, h1, h2, sigma;
		aal_uint32 * b0, *b1, *b2;

		b0 = rp.GetParCoeffsPtr(0);
		b1 = rp.GetParCoeffsPtr(1);
		b2 = rp.GetParCoeffsPtr(2);

		// количество элементов в упакованном массиве полинома меньшей степени
		int i_max = (rp.GetDeg() + 1) % TYPE_LEN != 0 ? (rp.GetDeg() + 1) / TYPE_LEN + 1 : (rp.GetDeg() + 1) / TYPE_LEN;
		for (int i = 0; i < i_max; i++) {
			s1 = m_b1[i] ^ b1[i];
			s2 = m_b2[i] ^ b2[i];
			d0 = m_b0[i] & b0[i];
			d1 = m_b1[i] & b1[i];
			d2 = m_b2[i] & b2[i];

			h0 = m_b0[i] ^ b0[i];
			h1 = s1        ^ d0;
			h2 = (s2 ^ d1) ^ (s1 & d0);

			sigma = (d2 ^ (s2 & d1)) ^ (s2 & (s1 & d0)) | (h0 & h1 & h2);

			m_b0[i] = h0 ^ sigma;
			m_b1[i] = h1 ^ (h0 & sigma);
			m_b2[i] = h2 ^ (h1 & (h0 & sigma));
		}

		ParPackToUnPack();
		TrimZero();
		return *this;
	}

	PolynomGF7N & PolynomGF7N::ModAdd(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2, PolynomGF7N & a_pol_mod) {

		// создание полинома суммы, из полинома большей степени
		*this = a_pol1.GetDeg() >= a_pol2.GetDeg() ? a_pol1 : a_pol2;
		// полином с меньшей степенью
		PolynomGF7N & rp = a_pol1.GetDeg() < a_pol2.GetDeg() ? a_pol1 : a_pol2;

		aal_uint32 s1, s2, d0, d1, d2, h0, h1, h2, sigma;
		aal_uint32 * b0, *b1, *b2;

		b0 = rp.GetParCoeffsPtr(0);
		b1 = rp.GetParCoeffsPtr(1);
		b2 = rp.GetParCoeffsPtr(2);

		// количество элементов в упакованном массиве полинома меньшей степени
		int i_max = (rp.GetDeg() + 1) % TYPE_LEN != 0 ? (rp.GetDeg() + 1) / TYPE_LEN + 1 : (rp.GetDeg() + 1) / TYPE_LEN;
		for (int i = 0; i < i_max; i++) {
			s1 = m_b1[i] ^ b1[i];
			s2 = m_b2[i] ^ b2[i];
			d0 = m_b0[i] & b0[i];
			d1 = m_b1[i] & b1[i];
			d2 = m_b2[i] & b2[i];

			h0 = m_b0[i] ^ b0[i];
			h1 = s1        ^ d0;
			h2 = (s2 ^ d1) ^ (s1 & d0);

			sigma = (d2 ^ (s2 & d1)) ^ (s2 & (s1 & d0)) | (h0 & h1 & h2);

			m_b0[i] = h0 ^ sigma;
			m_b1[i] = h1 ^ (h0 & sigma);
			m_b2[i] = h2 ^ (h1 & (h0 & sigma));
		}

		ParPackToUnPack();
		TrimZero();

		(*this).Div(*this, a_pol_mod);

		return *this;
	}

	PolynomGF7N & PolynomGF7N::AddInGF7_n(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2, PolynomGF7N & a_pol_mod) {

		if (a_pol_mod.isIrreducible()) {
			// создание полинома суммы, из полинома большей степени
			*this = a_pol1.GetDeg() >= a_pol2.GetDeg() ? a_pol1 : a_pol2;
			// полином с меньшей степенью
			PolynomGF7N & rp = a_pol1.GetDeg() < a_pol2.GetDeg() ? a_pol1 : a_pol2;

			aal_uint32 s1, s2, d0, d1, d2, h0, h1, h2, sigma;
			aal_uint32 * b0, *b1, *b2;

			b0 = rp.GetParCoeffsPtr(0);
			b1 = rp.GetParCoeffsPtr(1);
			b2 = rp.GetParCoeffsPtr(2);

			// количество элементов в упакованном массиве полинома меньшей степени
			int i_max = (rp.GetDeg() + 1) % TYPE_LEN != 0 ? (rp.GetDeg() + 1) / TYPE_LEN + 1 : (rp.GetDeg() + 1) / TYPE_LEN;
			for (int i = 0; i < i_max; i++) {
				s1 = m_b1[i] ^ b1[i];
				s2 = m_b2[i] ^ b2[i];
				d0 = m_b0[i] & b0[i];
				d1 = m_b1[i] & b1[i];
				d2 = m_b2[i] & b2[i];

				h0 = m_b0[i] ^ b0[i];
				h1 = s1        ^ d0;
				h2 = (s2 ^ d1) ^ (s1 & d0);

				sigma = (d2 ^ (s2 & d1)) ^ (s2 & (s1 & d0)) | (h0 & h1 & h2);

				m_b0[i] = h0 ^ sigma;
				m_b1[i] = h1 ^ (h0 & sigma);
				m_b2[i] = h2 ^ (h1 & (h0 & sigma));
			}

			ParPackToUnPack();
			TrimZero();

			(*this).Div(*this, a_pol_mod);

			return *this;
		}
		else {
			throw new exception("f(x) должен быть неприводимым.");
		}

	}

	PolynomGF7N & PolynomGF7N::Mul(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2) {

		// объединение для произведения дввух 32-разрядных переменных
		PolynomGF7N prod_pol(a_pol1.GetDeg() + a_pol2.GetDeg());

		// указатели на массивы коэффициентов в упакованном формате
		aal_uint32 * p1_0 = a_pol1.GetParCoeffsPtr(0);
		aal_uint32 * p1_1 = a_pol1.GetParCoeffsPtr(1);
		aal_uint32 * p1_2 = a_pol1.GetParCoeffsPtr(2);

		// указатель на массив коэффициентов в неупакованном формате
		aal_uint16 * pol2 = a_pol2.GetCoeffsPtr();

		aal_uint32 * prod0 = prod_pol.GetParCoeffsPtr(0);
		aal_uint32 * prod1 = prod_pol.GetParCoeffsPtr(1);
		aal_uint32 * prod2 = prod_pol.GetParCoeffsPtr(2);

		// вспомогательные переменные
		aal_uint32 u0, u1, d0, d1, d2, sigma, h0, h1, h2, q0, q1, q2, p0, p1, p2;

		// Константы для выбора второго множителя
		const aal_uint32 a1 = 0xFFFFFFFF;
		const aal_uint32 a0 = 0x00000000;

		// Массив значений второго множителя (от 0 до 6)
		const aal_uint32 sf[7][3] = { { a0, a0, a0 },{ a0, a0, a1 },{ a0, a1, a0 },{ a0, a1, a1 },
		{ a1, a0, a0 },{ a1, a0, a1 },{ a1, a1, a0 } };

		// количество групп в первом сомножителе
		int num_p1 = (a_pol1.GetDeg() + 1) % TYPE_LEN != 0 ? (a_pol1.GetDeg() + 1) / TYPE_LEN + 1 : (a_pol1.GetDeg() + 1) / TYPE_LEN;

		for (int i = 0; i < num_p1; i++) {
			q0 = p1_0[i];
			q1 = p1_1[i];
			q2 = p1_2[i];

			for (int j = 0; j < a_pol2.GetDeg() + 1; j++) {

				p0 = sf[pol2[j]][2];
				p1 = sf[pol2[j]][1];
				p2 = sf[pol2[j]][0];

				// Константы для перемножения НАЧАЛО
				sigma = (p0 ^ p1) & (p0 ^ p2) ^ p0;
				u0 = p0 ^ p2 ^ a1;
				u1 = p0 ^ p1 ^ a1;

				d0 = ~u1 & u0;
				d1 = u1 & ~u0;
				d2 = ~u1 & ~u0;
				// Константы для перемножения ОКОНЧАНИЕ

				h0 = (d2 & q0) | (d1 & q1) | (d0 & q2);
				h1 = (d2 & q1) | (d1 & q2) | (d0 & q0);
				h2 = (d2 & q2) | (d1 & q0) | (d0 & q1);

				h0 ^= sigma;
				h1 ^= sigma;
				h2 ^= sigma;

				aal_int32 index = i + (j >> LOG2_TYPE_LEN);  // Второе слагаемое обозначает номер группы второго множителя 
				aal_int32 index_1 = index + 1;
				aal_uint32 shift = j ^ ((j >> LOG2_TYPE_LEN) << LOG2_TYPE_LEN); // остаток от деления j на TYPE_LEN

																				// накопление в группе prod[index] (старшие разряды переходят в следующую группу)
				gf7_sum_Parallelpack(prod0[index], prod1[index], prod2[index],
					h0 << shift, h1 << shift, h2 << shift,
					&prod0[index], &prod1[index], &prod2[index]);

				if (shift > 0) {
					// накопление в группе prod[index + 1]
					gf7_sum_Parallelpack(prod0[index_1], prod1[index_1], prod2[index_1],
						h0 >> (TYPE_LEN - shift), h1 >> (TYPE_LEN - shift), h2 >> (TYPE_LEN - shift),
						&prod0[index_1], &prod1[index_1], &prod2[index_1]);
				}

				h0 ^= h0;
				h1 ^= h1;
				h2 ^= h2;

			} // for j
		} // for i

		*this = prod_pol;
		ParPackToUnPack();
		TrimZero();
		return *this;
	}

	PolynomGF7N & PolynomGF7N::ModMul(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2, PolynomGF7N & a_pol_mod) {

		// объединение для произведения дввух 32-разрядных переменных
		PolynomGF7N prod_pol(a_pol1.GetDeg() + a_pol2.GetDeg());

		// указатели на массивы коэффициентов в упакованном формате
		aal_uint32 * p1_0 = a_pol1.GetParCoeffsPtr(0);
		aal_uint32 * p1_1 = a_pol1.GetParCoeffsPtr(1);
		aal_uint32 * p1_2 = a_pol1.GetParCoeffsPtr(2);

		// указатель на массив коэффициентов в неупакованном формате
		aal_uint16 * pol2 = a_pol2.GetCoeffsPtr();

		aal_uint32 * prod0 = prod_pol.GetParCoeffsPtr(0);
		aal_uint32 * prod1 = prod_pol.GetParCoeffsPtr(1);
		aal_uint32 * prod2 = prod_pol.GetParCoeffsPtr(2);

		// вспомогательные переменные
		aal_uint32 u0, u1, d0, d1, d2, sigma, h0, h1, h2, q0, q1, q2, p0, p1, p2;

		// Константы для выбора второго множителя
		const aal_uint32 a1 = 0xFFFFFFFF;
		const aal_uint32 a0 = 0x00000000;

		// Массив значений второго множителя (от 0 до 6)
		const aal_uint32 sf[7][3] = { { a0, a0, a0 },{ a0, a0, a1 },{ a0, a1, a0 },{ a0, a1, a1 },
		{ a1, a0, a0 },{ a1, a0, a1 },{ a1, a1, a0 } };

		// количество групп в первом сомножителе
		int num_p1 = (a_pol1.GetDeg() + 1) % TYPE_LEN != 0 ? (a_pol1.GetDeg() + 1) / TYPE_LEN + 1 : (a_pol1.GetDeg() + 1) / TYPE_LEN;

		for (int i = 0; i < num_p1; i++) {
			q0 = p1_0[i];
			q1 = p1_1[i];
			q2 = p1_2[i];

			for (int j = 0; j < a_pol2.GetDeg() + 1; j++) {

				p0 = sf[pol2[j]][2];
				p1 = sf[pol2[j]][1];
				p2 = sf[pol2[j]][0];

				// Константы для перемножения НАЧАЛО
				sigma = (p0 ^ p1) & (p0 ^ p2) ^ p0;
				u0 = p0 ^ p2 ^ a1;
				u1 = p0 ^ p1 ^ a1;

				d0 = ~u1 & u0;
				d1 = u1 & ~u0;
				d2 = ~u1 & ~u0;
				// Константы для перемножения ОКОНЧАНИЕ

				h0 = (d2 & q0) | (d1 & q1) | (d0 & q2);
				h1 = (d2 & q1) | (d1 & q2) | (d0 & q0);
				h2 = (d2 & q2) | (d1 & q0) | (d0 & q1);

				h0 ^= sigma;
				h1 ^= sigma;
				h2 ^= sigma;

				aal_int32 index = i + (j >> LOG2_TYPE_LEN);  // Второе слагаемое обозначает номер группы второго множителя 
				aal_int32 index_1 = index + 1;
				aal_uint32 shift = j ^ ((j >> LOG2_TYPE_LEN) << LOG2_TYPE_LEN); // остаток от деления j на TYPE_LEN

																				// накопление в группе prod[index] (старшие разряды переходят в следующую группу)
				gf7_sum_Parallelpack(prod0[index], prod1[index], prod2[index],
					h0 << shift, h1 << shift, h2 << shift,
					&prod0[index], &prod1[index], &prod2[index]);

				if (shift > 0) {
					// накопление в группе prod[index + 1]
					gf7_sum_Parallelpack(prod0[index_1], prod1[index_1], prod2[index_1],
						h0 >> (TYPE_LEN - shift), h1 >> (TYPE_LEN - shift), h2 >> (TYPE_LEN - shift),
						&prod0[index_1], &prod1[index_1], &prod2[index_1]);
				}

				h0 ^= h0;
				h1 ^= h1;
				h2 ^= h2;

			} // for j
		} // for i

		*this = prod_pol;
		ParPackToUnPack();
		TrimZero();

		(*this).Div(*this, a_pol_mod);

		return *this;
	}

	PolynomGF7N & PolynomGF7N::MulGF7_n(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2, PolynomGF7N & a_pol_mod) {

		if (a_pol_mod.isIrreducible()) {
			// объединение для произведения дввух 32-разрядных переменных
			PolynomGF7N prod_pol(a_pol1.GetDeg() + a_pol2.GetDeg());

			// указатели на массивы коэффициентов в упакованном формате
			aal_uint32 * p1_0 = a_pol1.GetParCoeffsPtr(0);
			aal_uint32 * p1_1 = a_pol1.GetParCoeffsPtr(1);
			aal_uint32 * p1_2 = a_pol1.GetParCoeffsPtr(2);

			// указатель на массив коэффициентов в неупакованном формате
			aal_uint16 * pol2 = a_pol2.GetCoeffsPtr();

			aal_uint32 * prod0 = prod_pol.GetParCoeffsPtr(0);
			aal_uint32 * prod1 = prod_pol.GetParCoeffsPtr(1);
			aal_uint32 * prod2 = prod_pol.GetParCoeffsPtr(2);

			// вспомогательные переменные
			aal_uint32 u0, u1, d0, d1, d2, sigma, h0, h1, h2, q0, q1, q2, p0, p1, p2;

			// Константы для выбора второго множителя
			const aal_uint32 a1 = 0xFFFFFFFF;
			const aal_uint32 a0 = 0x00000000;

			// Массив значений второго множителя (от 0 до 6)
			const aal_uint32 sf[7][3] = { { a0, a0, a0 },{ a0, a0, a1 },{ a0, a1, a0 },{ a0, a1, a1 },
			{ a1, a0, a0 },{ a1, a0, a1 },{ a1, a1, a0 } };

			// количество групп в первом сомножителе
			int num_p1 = (a_pol1.GetDeg() + 1) % TYPE_LEN != 0 ? (a_pol1.GetDeg() + 1) / TYPE_LEN + 1 : (a_pol1.GetDeg() + 1) / TYPE_LEN;

			for (int i = 0; i < num_p1; i++) {
				q0 = p1_0[i];
				q1 = p1_1[i];
				q2 = p1_2[i];

				for (int j = 0; j < a_pol2.GetDeg() + 1; j++) {

					p0 = sf[pol2[j]][2];
					p1 = sf[pol2[j]][1];
					p2 = sf[pol2[j]][0];

					// Константы для перемножения НАЧАЛО
					sigma = (p0 ^ p1) & (p0 ^ p2) ^ p0;
					u0 = p0 ^ p2 ^ a1;
					u1 = p0 ^ p1 ^ a1;

					d0 = ~u1 & u0;
					d1 = u1 & ~u0;
					d2 = ~u1 & ~u0;
					// Константы для перемножения ОКОНЧАНИЕ

					h0 = (d2 & q0) | (d1 & q1) | (d0 & q2);
					h1 = (d2 & q1) | (d1 & q2) | (d0 & q0);
					h2 = (d2 & q2) | (d1 & q0) | (d0 & q1);

					h0 ^= sigma;
					h1 ^= sigma;
					h2 ^= sigma;

					aal_int32 index = i + (j >> LOG2_TYPE_LEN);  // Второе слагаемое обозначает номер группы второго множителя 
					aal_int32 index_1 = index + 1;
					aal_uint32 shift = j ^ ((j >> LOG2_TYPE_LEN) << LOG2_TYPE_LEN); // остаток от деления j на TYPE_LEN

																					// накопление в группе prod[index] (старшие разряды переходят в следующую группу)
					gf7_sum_Parallelpack(prod0[index], prod1[index], prod2[index],
						h0 << shift, h1 << shift, h2 << shift,
						&prod0[index], &prod1[index], &prod2[index]);

					if (shift > 0) {
						// накопление в группе prod[index + 1]
						gf7_sum_Parallelpack(prod0[index_1], prod1[index_1], prod2[index_1],
							h0 >> (TYPE_LEN - shift), h1 >> (TYPE_LEN - shift), h2 >> (TYPE_LEN - shift),
							&prod0[index_1], &prod1[index_1], &prod2[index_1]);
					}

					h0 ^= h0;
					h1 ^= h1;
					h2 ^= h2;

				} // for j
			} // for i

			*this = prod_pol;
			ParPackToUnPack();
			TrimZero();

			(*this).Div(*this, a_pol_mod);

			return *this;
		}
		else {
			throw new exception("f(x) должен быть неприводимым.");
		}

	}

	PolynomGF7N & PolynomGF7N::MulGF7_n_ONB(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2, int a_n) {
		// объединение для произведения дввух 32-разрядных переменных
		PolynomGF7N prod_pol(a_pol1.GetDeg() + a_pol2.GetDeg());

		// указатели на массивы коэффициентов в упакованном формате
		aal_uint32 * p1_0 = a_pol1.GetParCoeffsPtr(0);
		aal_uint32 * p1_1 = a_pol1.GetParCoeffsPtr(1);
		aal_uint32 * p1_2 = a_pol1.GetParCoeffsPtr(2);

		// указатель на массив коэффициентов в неупакованном формате
		aal_uint16 * pol2 = a_pol2.GetCoeffsPtr();

		aal_uint32 * prod0 = prod_pol.GetParCoeffsPtr(0);
		aal_uint32 * prod1 = prod_pol.GetParCoeffsPtr(1);
		aal_uint32 * prod2 = prod_pol.GetParCoeffsPtr(2);

		// вспомогательные переменные
		aal_uint32 u0, u1, d0, d1, d2, sigma, h0, h1, h2, q0, q1, q2, p0, p1, p2;

		// Константы для выбора второго множителя
		const aal_uint32 a1 = 0xFFFFFFFF;
		const aal_uint32 a0 = 0x00000000;

		// Массив значений второго множителя (от 0 до 6)
		const aal_uint32 sf[7][3] = { { a0, a0, a0 },{ a0, a0, a1 },{ a0, a1, a0 },{ a0, a1, a1 },
		{ a1, a0, a0 },{ a1, a0, a1 },{ a1, a1, a0 } };

		// количество групп в первом сомножителе
		int num_p1 = (a_pol1.GetDeg() + 1) % TYPE_LEN != 0 ? (a_pol1.GetDeg() + 1) / TYPE_LEN + 1 : (a_pol1.GetDeg() + 1) / TYPE_LEN;

		for (int i = 0; i < num_p1; i++) {
			q0 = p1_0[i];
			q1 = p1_1[i];
			q2 = p1_2[i];

			for (int j = 0; j < a_pol2.GetDeg() + 1; j++) {

				p0 = sf[pol2[j]][2];
				p1 = sf[pol2[j]][1];
				p2 = sf[pol2[j]][0];

				// Константы для перемножения НАЧАЛО
				sigma = (p0 ^ p1) & (p0 ^ p2) ^ p0;
				u0 = p0 ^ p2 ^ a1;
				u1 = p0 ^ p1 ^ a1;

				d0 = ~u1 & u0;
				d1 = u1 & ~u0;
				d2 = ~u1 & ~u0;
				// Константы для перемножения ОКОНЧАНИЕ

				h0 = (d2 & q0) | (d1 & q1) | (d0 & q2);
				h1 = (d2 & q1) | (d1 & q2) | (d0 & q0);
				h2 = (d2 & q2) | (d1 & q0) | (d0 & q1);

				h0 ^= sigma;
				h1 ^= sigma;
				h2 ^= sigma;

				aal_int32 index = i + (j >> LOG2_TYPE_LEN);  // Второе слагаемое обозначает номер группы второго множителя 
				aal_int32 index_1 = index + 1;
				aal_uint32 shift = j ^ ((j >> LOG2_TYPE_LEN) << LOG2_TYPE_LEN); // остаток от деления j на TYPE_LEN

																				// накопление в группе prod[index] (старшие разряды переходят в следующую группу)
				gf7_sum_Parallelpack(prod0[index], prod1[index], prod2[index],
					h0 << shift, h1 << shift, h2 << shift,
					&prod0[index], &prod1[index], &prod2[index]);

				if (shift > 0) {
					// накопление в группе prod[index + 1]
					gf7_sum_Parallelpack(prod0[index_1], prod1[index_1], prod2[index_1],
						h0 >> (TYPE_LEN - shift), h1 >> (TYPE_LEN - shift), h2 >> (TYPE_LEN - shift),
						&prod0[index_1], &prod1[index_1], &prod2[index_1]);
				}

				h0 ^= h0;
				h1 ^= h1;
				h2 ^= h2;

			} // for j
		} // for i

			// Приведение по модулю с использованием оптимальных нормальных базисов
		prod_pol.ParPackToUnPack();
		prod_pol.PolynomialToReduced(prod_pol, a_n);
		prod_pol.ReducedToRedundant(prod_pol, a_n);
		prod_pol.RedundantToReduced(prod_pol, a_n);
		prod_pol.ReducedToPolynomial(prod_pol, a_n);

		*this = prod_pol;

		return *this;
	}

	PolynomGF7N & PolynomGF7N::Sub(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2) {

		// Работа с упакованными коэффициентами
		PolynomGF7N pol2_1;
		pol2_1.gf7_mult_num_ParPack(a_pol2, 6); // умножение на -1 Mod 7
		(*this) = Add(a_pol1, pol2_1);

		TrimZero();
		return *this;
	}

	PolynomGF7N PolynomGF7N::default_quot;
	PolynomGF7N & PolynomGF7N::Div(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2, PolynomGF7N & a_pol_quot) {

		// если степень делимого меньше степени делителя,
		// частное не вычисляется
		if (a_pol1.GetDeg() < a_pol2.GetDeg()) {
			(*this) = a_pol1;           // остаток от деления

			PolynomGF7N p_null("0");     // частное
			a_pol_quot = p_null;
			return (*this);
		}

		// Степень частного
		aal_uint16 deg_quot = a_pol1.GetDeg() - a_pol2.GetDeg();

		// Создание полинома-частного
		PolynomGF7N quot_pol(deg_quot);
		// Указатель на массив коэффициентов частного
		aal_uint16* pquot = quot_pol.GetCoeffsPtr();

		// Копия делимого
		PolynomGF7N p1_cop = a_pol1;

		// Указатель на массив коэффициентов делимого
		aal_uint16* p1 = p1_cop.GetCoeffsPtr();

		// Старший коэффициент делителя
		aal_uint16 eld_coef = a_pol2.GetCoeffsPtr()[a_pol2.GetDeg()];

		aal_uint16 deg_p1 = p1_cop.GetDeg();
		// Вспомогательная переменная
		aal_uint16 max_deg_p1 = deg_p1;

		aal_uint16 deg_p2 = a_pol2.GetDeg();
		int val = 0;
		for (int i = deg_quot; i >= 0; i -= val) {
			aal_uint16 mul_cf = qcoeff[eld_coef - 1][p1[deg_p1]];
			pquot[i] = mul_cf;
			PolynomGF7N p2_cop = gf7_mult_num_ParPack(a_pol2, mul_cf);
			p2_cop.Shift_R_ParallelPack(i);
			p1_cop.Sub(p1_cop, p2_cop);
			p1 = p1_cop.GetCoeffsPtr();
			deg_p1 = p1_cop.GetDeg();
			val = max_deg_p1 - deg_p1;
			max_deg_p1 = deg_p1;
			if (val == 0) break;
		}
		// частное
		quot_pol.TrimZero();
		quot_pol.UnPackToParPack();
		a_pol_quot = quot_pol;

		// остаток
		(*this) = p1_cop;
		return (*this);
	}

	PolynomGF7N & PolynomGF7N::GCD(PolynomGF7N & a_pol1, PolynomGF7N & a_pol2) {

		if (a_pol1.isNull() && a_pol2.isNull()) {
			throw exception("Оба полинома нулевые.");
		}
		else {
			if (!a_pol1.isNull() && !a_pol2.isNull()) {
				PolynomGF7N u = a_pol1;
				PolynomGF7N v = a_pol2;

				while (!v.isNull()) {
					PolynomGF7N rem_pol;
					rem_pol.Div(u, v);
					u = v;
					v = rem_pol;
				}

				(*this) = u;
				return (*this);
			}
			if (a_pol1.isNull() && !a_pol2.isNull()) {
				(*this) = a_pol1;
				return (*this);
			}
			if (!a_pol1.isNull() && a_pol2.isNull()) {
				(*this) = a_pol2;
				return (*this);
			}

		}
	}

	bool PolynomGF7N::isIrreducible() const {

		int deg = GetDeg();
		if (deg == -1) {
			return false;
		}

		PolynomGF7N q0("01");
		PolynomGF7N qk = q0;
		PolynomGF7N plA = (*this);

		bool flagNOD = true;

		for (int i = 1; i <= deg; i++) {
			qk.ModPow(qk, 7, plA);
			int s = deg / i;

			if ((s != 1) && (s < deg) && (deg%s == 0) && (deg % i == 0) && (PrimeNumbersSet.find(s) != PrimeNumbersSet.end())) {
				if (qk == q0) {
					return false;
				}
				else {
					PolynomGF7N NOD, SUB, polOne("1"), polTwo("2"), polThree("3"), polFour("4"), polFive("5"), polSix("6");
					SUB.Sub(qk, q0);
					NOD.GCD(SUB, plA);
					if (NOD == polOne || NOD == polTwo || NOD == polThree || NOD == polFour || NOD == polFive || NOD == polSix) {
						flagNOD = true;
					}
					else {
						return false;
					}
				}
			}
		}
		q0.Div(q0, plA);
		if (qk == q0 && flagNOD) {
			return true;
		}
		else {
			return false;
		}
	}

	PolynomGF7N & PolynomGF7N::InverseMod(PolynomGF7N & a_pol, PolynomGF7N & a_simple_pol, bool a_is_irr) {

		// Копия обращаемого полинома
		PolynomGF7N pol_U = a_pol;
		PolynomGF7N * pU = &pol_U;
		// Если его степень больше или равна степени неприводимого полинома, приводим его по модулю
		if (a_pol.GetDeg() >= a_simple_pol.GetDeg()) {
			PolynomGF7N a_pol_quot;
			pol_U.Div(pol_U, a_simple_pol, a_pol_quot);
		}

		// проверка взаимной простоты для использования расширенного Алгоритма Евклида
		if (!a_is_irr) {
			PolynomGF7N pol_nod = GCD(a_pol, a_simple_pol);
			if (pol_nod.GetDeg() != 0) {
				(*this);
				return (*this);
			}
		}

		// Вспомогательная переменная
		aal_uint16 val;

		// Вспомогательные полиномы
		PolynomGF7N pol_B("1");
		PolynomGF7N pol_C("0");
		PolynomGF7N * pB = &pol_B;
		PolynomGF7N * pC = &pol_C;


		// Копия неприводимого полинома
		PolynomGF7N pol_V = a_simple_pol;
		PolynomGF7N * pV = &pol_V;
		// Обратное к младшему коэффициенту неприводимого полинома
		aal_uint16 f0_1 = qcoeff[a_simple_pol.GetCoeffsPtr()[0] - 1][1];

		aal_uint16 *p_u = (*pU).GetCoeffsPtr(); // массив коэффициентов U
		aal_uint16 *p_v = (*pV).GetCoeffsPtr(); // массив коэффициентов V
		aal_uint16 *p_b = (*pB).GetCoeffsPtr(); // массив коэффициентов B

												//(*pU).ParPackToUnPack();
												//(*pB).ParPackToUnPack();

		while ((*pU).GetDeg() > 0) {

			while (p_u[0] == 0) {
				(*pU).Shift_L_ParallelPack(1);                               // U/X

				if (p_b[0] == 0) {
					(*pB).Shift_L_ParallelPack(1);                           // B/X
				}
				else {
					aal_uint32 q = gf7_mul_coeffs(f0_1, p_b[0]);
					PolynomGF7N pol_Z = gf7_mult_num_ParPack(a_simple_pol, q);
					(*pB) = Sub((*pB), pol_Z);
					(*pB).Shift_L_ParallelPack(1);
					p_b = (*pB).GetCoeffsPtr();                 // массив коэффициентов B
				}
			} // while

			if ((*pU).GetDeg() > 0) {
				if ((*pU).GetDeg() < (*pV).GetDeg()) {
					PolynomGF7N * p_temp = pU;
					pU = pV;
					pV = p_temp;

					p_temp = pB;
					pB = pC;
					pC = p_temp;

					p_u = (*pU).GetCoeffsPtr();
					p_v = (*pV).GetCoeffsPtr();
					p_b = (*pB).GetCoeffsPtr();
				}

				val = p_v[0] > 0 ? -p_v[0] + 7 : p_v[0];
				PolynomGF7N pol_Z = gf7_mult_num_ParPack((*pB), val);
				PolynomGF7N pol_S = gf7_mult_num_ParPack((*pC), p_u[0]);
				(*pB) = Add(pol_Z, pol_S);
				p_b = (*pB).GetCoeffsPtr();

				val = p_v[0] > 0 ? -p_v[0] + 7 : p_v[0];
				PolynomGF7N pol_L = gf7_mult_num_ParPack((*pU), val);
				p_u = (*pU).GetCoeffsPtr();
				PolynomGF7N pol_M = gf7_mult_num_ParPack((*pV), p_u[0]);
				p_v = (*pV).GetCoeffsPtr();
				(*pU) = Add(pol_L, pol_M);
				p_u = (*pU).GetCoeffsPtr();
			} // if

		} // while

		aal_uint16 u0_1 = qcoeff[p_u[0] - 1][1];
		(*this) = gf7_mult_num_ParPack((*pB), u0_1);

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::Pow(PolynomGF7N & a_pol, aal_uint32 a_deg) {
		PolynomGF7N pow_pol("1");

		// если показатель приадлежит {0,1,2,3,4,5,6}
		// то возведение производится умножением (n-1) раз
		switch (a_deg) {
		case 0:
			(*this) = PolynomGF7N("1");
			return (*this);
		case 1:
			(*this) = a_pol;
			return (*this);
		case 2:
			pow_pol.Mul(a_pol, a_pol);
			(*this) = pow_pol;
			return (*this);
		case 3:
			pow_pol.Mul(a_pol, a_pol);
			pow_pol.Mul(pow_pol, a_pol);
			(*this) = pow_pol;
			return (*this);
		case 4:
			pow_pol.Mul(a_pol, a_pol);
			pow_pol.Mul(pow_pol, pow_pol);
			(*this) = pow_pol;
			return (*this);
		case 5:
			pow_pol.Mul(a_pol, a_pol);
			pow_pol.Mul(pow_pol, pow_pol);
			pow_pol.Mul(pow_pol, a_pol);
			(*this) = pow_pol;
			return (*this);
		case 6: {
			PolynomGF7N pol2;
			pol2.Mul(a_pol, a_pol);
			pow_pol.Mul(pol2, pol2);
			pow_pol.Mul(pow_pol, pol2);
			(*this) = pow_pol;
			return (*this);
		}
		case 7:
			pow_pol.Pow7(a_pol);
			(*this) = pow_pol;
			return (*this);
		}

		// Если показатель больше 6, то раскладываем его по осн. 7
		// и возводим в степень по алгоритму

		// количество элементов в массиве разложения по осн. 7
		int len = DegDecompLength(a_deg, 7);
		// массив разложения степени
		aal_uint32 *deg_fact = new aal_uint32[len];

		// заполнение массива разложения степени по осн. 7
		// коэффициентами при степенях 7
		DegDecomp(deg_fact, a_deg, 7);

		// Вспомогательный полином
		PolynomGF7N q;

		for (int i = 1; i <= len; i++) {
			pow_pol.Pow7(pow_pol);
			if (deg_fact[len - i] != 0) {
				q.Pow(a_pol, deg_fact[len - i]);
				pow_pol.Mul(pow_pol, q);
			}
		}

		if (deg_fact != NULL) {
			delete[] deg_fact;
		}

		(*this) = pow_pol;
		return (*this);

	}

	PolynomGF7N & PolynomGF7N::ModPow(PolynomGF7N & a_pol, aal_uint32 a_deg, PolynomGF7N & a_pol_mod) {
		PolynomGF7N pow_pol("1");

		// если показатель приадлежит {0,1,2,3,4,5,6}
		// то возведение производится умножением (n-1) раз
		switch (a_deg) {
		case 0:
			(*this) = PolynomGF7N("1");
			return (*this);
		case 1:
			(*this) = a_pol;
			return (*this);
		case 2:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 3:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, a_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 4:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, pow_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 5:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, pow_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, a_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 6: {
			PolynomGF7N pol2;
			pol2.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pol2, pol2, a_pol_mod);
			pow_pol.ModMul(pow_pol, pol2, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		}
		case 7:
			pow_pol.Pow7(a_pol);
			pow_pol.Div(pow_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		}

		// Если показатель больше 6, то раскладываем его по осн. 7
		// и возводим в степень по алгоритму

		// количество элементов в массиве разложения по осн. 7
		int len = DegDecompLength(a_deg, 7);
		// массив разложения степени
		aal_uint32 *deg_fact = new aal_uint32[len];

		// заполнение массива разложения степени по осн. 7
		// коэффициентами при степенях 7
		DegDecomp(deg_fact, a_deg, 7);

		// Вспомогательный полином
		PolynomGF7N q;

		for (int i = 1; i <= len; i++) {
			pow_pol.ModPow(pow_pol, 7, a_pol_mod);

			if (deg_fact[len - i] != 0) {
				q.Pow(a_pol, deg_fact[len - i]);
				q.Div(q, a_pol_mod);
				pow_pol.ModMul(pow_pol, q, a_pol_mod);
			}
		}

		if (deg_fact != NULL) {
			delete[] deg_fact;
		}

		(*this) = pow_pol;
		return (*this);

	}

	PolynomGF7N & PolynomGF7N::PowGF7_n(PolynomGF7N & a_pol, aal_uint32 a_deg, PolynomGF7N & a_pol_mod) {

		if (a_pol_mod.isIrreducible()) {
			PolynomGF7N pow_pol("1");

			// если показатель приадлежит {0,1,2,3,4,5,6}
			// то возведение производится умножением (n-1) раз
			switch (a_deg) {
			case 0:
				(*this) = PolynomGF7N("1");
				return (*this);
			case 1:
				(*this) = a_pol;
				return (*this);
			case 2:
				pow_pol.MulGF7_n(a_pol, a_pol, a_pol_mod);
				(*this) = pow_pol;
				return (*this);
			case 3:
				pow_pol.MulGF7_n(a_pol, a_pol, a_pol_mod);
				pow_pol.MulGF7_n(pow_pol, a_pol, a_pol_mod);
				(*this) = pow_pol;
				return (*this);
			case 4:
				pow_pol.MulGF7_n(a_pol, a_pol, a_pol_mod);
				pow_pol.MulGF7_n(pow_pol, pow_pol, a_pol_mod);
				(*this) = pow_pol;
				return (*this);
			case 5:
				pow_pol.MulGF7_n(a_pol, a_pol, a_pol_mod);
				pow_pol.MulGF7_n(pow_pol, pow_pol, a_pol_mod);
				pow_pol.MulGF7_n(pow_pol, a_pol, a_pol_mod);
				(*this) = pow_pol;
				return (*this);
			case 6: {
				PolynomGF7N pol2;
				pol2.MulGF7_n(a_pol, a_pol, a_pol_mod);
				pow_pol.MulGF7_n(pol2, pol2, a_pol_mod);
				pow_pol.MulGF7_n(pow_pol, pol2, a_pol_mod);
				(*this) = pow_pol;
				return (*this);
			}
			case 7:
				pow_pol.Pow7(a_pol);
				pow_pol.Div(pow_pol, a_pol_mod);
				(*this) = pow_pol;
				return (*this);
			}

			// Если показатель больше 6, то раскладываем его по осн. 7
			// и возводим в степень по алгоритму

			// количество элементов в массиве разложения по осн. 7
			int len = DegDecompLength(a_deg, 7);
			// массив разложения степени
			aal_uint32 *deg_fact = new aal_uint32[len];

			// заполнение массива разложения степени по осн. 7
			// коэффициентами при степенях 7
			DegDecomp(deg_fact, a_deg, 7);

			// Вспомогательный полином
			PolynomGF7N q;

			for (int i = 1; i <= len; i++) {
				pow_pol.PowGF7_n(pow_pol, 7, a_pol_mod);
				if (deg_fact[len - i] != 0) {
					q.PowGF7_n(a_pol, deg_fact[len - i], a_pol_mod);
					pow_pol.MulGF7_n(pow_pol, q, a_pol_mod);
				}
			}

			if (deg_fact != NULL) {
				delete[] deg_fact;
			}

			(*this) = pow_pol;
			return (*this);
		}
		else {
			throw new exception("f(x) должен быть неприводимым.");
		}


	}

	PolynomGF7N & PolynomGF7N::PowGF7_n_ONB(PolynomGF7N & a_pol, aal_uint32 a_deg, PolynomGF7N & a_pol_mod) {
		PolynomGF7N pow_pol("1");

		// если показатель приадлежит {0,1,2,3,4,5,6}
		// то возведение производится умножением (n-1) раз
		switch (a_deg) {
		case 0:
			(*this) = PolynomGF7N("1");
			return (*this);
		case 1:
			(*this) = a_pol;
			return (*this);
		case 2:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 3:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, a_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 4:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, pow_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 5:
			pow_pol.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, pow_pol, a_pol_mod);
			pow_pol.ModMul(pow_pol, a_pol, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		case 6: {
			PolynomGF7N pol2;
			pol2.ModMul(a_pol, a_pol, a_pol_mod);
			pow_pol.ModMul(pol2, pol2, a_pol_mod);
			pow_pol.ModMul(pow_pol, pol2, a_pol_mod);
			(*this) = pow_pol;
			return (*this);
		}
		}

		// Если показатель больше 6, то раскладываем его по осн. 7
		// и возводим в степень по алгоритму
		// количество элементов в массиве разложения по осн. 7
		int len = DegDecompLength(a_deg, 7);
		// массив разложения степени
		aal_uint32 *deg_fact = new aal_uint32[len];
		// заполнение массива разложения степени по осн. 7
		// коэффициентами при степенях 7
		DegDecomp(deg_fact, a_deg, 7);

		// Вычисление прямой и обратной подстановок для возведения в степень 7 в ОНБ
		int n = a_pol_mod.GetDeg();
		vector<int> permutation = GetPermutation(n);
		vector<int> invPermutation = InversePermutation(permutation);

		// Вспомогательный полином
		PolynomGF7N q;
		// Вспомогательные полиномы для переводов в нормальные базисы
		PolynomGF7N x_red;
		PolynomGF7N x_perm;

		//счётчик 0-х коэффициентов
		int num_null_coeff = 1;

		for (int i = 1; i <= len; i++) {
			if (deg_fact[len - i] == 0) {
				num_null_coeff++;
			}
			else {
				// ВОЗВЕДЕНИЕ В СТЕПЕНЬ ХАРАКТЕРИСТИКИ ПОЛЯ В ОНБ - НАЧАЛО
				x_red.PolynomialToReduced(pow_pol, n);
				x_perm.ReducedToPermuted(x_red, n);
				x_perm.Pow7_NB_TEST(x_perm, permutation, invPermutation, num_null_coeff, n);
				x_red.PermutedToReduced(x_perm, n);
				pow_pol.ReducedToPolynomial(x_red, n);
				// ВОЗВЕДЕНИЕ В СТЕПЕНЬ ХАРАКТЕРИСТИКИ ПОЛЯ В ОНБ - КОНЕЦ

				q.PowGF7_n_ONB(a_pol, deg_fact[len - i], a_pol_mod);
				pow_pol.ModMul(pow_pol, q, a_pol_mod);
				num_null_coeff = 1;
			}
		}

		if (deg_fact[0] == 0) {
			num_null_coeff--;
			// ВОЗВЕДЕНИЕ В СТЕПЕНЬ ХАРАКТЕРИСТИКИ ПОЛЯ В ОНБ - НАЧАЛО
			x_red.PolynomialToReduced(pow_pol, n);
			x_perm.ReducedToPermuted(x_red, n);
			x_perm.Pow7_NB_TEST(x_perm, permutation, invPermutation, num_null_coeff, n);
			x_red.PermutedToReduced(x_perm, n);
			pow_pol.ReducedToPolynomial(x_red, n);
			// ВОЗВЕДЕНИЕ В СТЕПЕНЬ ХАРАКТЕРИСТИКИ ПОЛЯ В ОНБ - КОНЕЦ
		}

		if (deg_fact != NULL) {
			delete[] deg_fact;
		}

		(*this) = pow_pol;
		return (*this);

	}

	void PolynomGF7N::DegDecomp(aal_uint32 *a_decomp, aal_uint32 a_deg, int a_p) const{
		aal_uint32 i = 0;

		while (a_deg > (a_p - 1)) {
			a_decomp[i] = a_deg % a_p;
			a_deg /= a_p;
			i++;
		}
		a_decomp[i] = a_deg % a_p;

		return;
	}

	int PolynomGF7N::DegDecompLength(aal_uint32 a_val, int a_p) const{
		aal_uint32 i = 0;

		while (a_val > (a_p - 1)) {
			a_val /= a_p;
			i++;
		}
		i++;

		return i;
	}

	PolynomGF7N & PolynomGF7N::Pow7(PolynomGF7N & a_pol) {
		// Степень результирующего полинома
		aal_uint32 deg = a_pol.GetDeg() * 7;
		// Результирующий полином
		PolynomGF7N res(deg);
		// Указатель на массив коэффициентов результирующего полинома
		aal_uint16 *res_ptr = res.GetCoeffsPtr();

		// Указатель на массив коэффициентов возводимого в 7 степень полинома
		aal_uint16 *pol_ptr = a_pol.GetCoeffsPtr();
		int j = 0;
		for (int i = 0; i <= a_pol.GetDeg(); i++) {
			res_ptr[j] = pol_ptr[i];
			j += 7;
		}

		(*this) = res;
		UnPackToParPack();
		TrimZero();

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::Pow7_NB(PolynomGF7N & a_pol, aal_uint32 a_7deg, PolynomGF7N & a_pol_mod) {

		int n = a_pol_mod.GetDeg();
		PolynomGF7N tmpPol(n - 1);
		aal_uint16* tmpPolPtr = tmpPol.GetCoeffsPtr();
		// Копирование коэффициентов из входного полинома в увеличенный полином
		memcpy(tmpPolPtr, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		// Результат
		PolynomGF7N resPol(n - 1);
		aal_uint16* resPolPtr = resPol.GetCoeffsPtr();

		// Вычисление прямой и обратной подстановок
		vector<int> permutation = GetPermutation(n);
		vector<int> invPermutation = InversePermutation(permutation);

		// Вычисление финальных позиций коэффициентов при возведении в степень
		for (int i = 0; i < invPermutation.size(); i++) {
			invPermutation[i] -= a_7deg;
			if (invPermutation[i] <= 0) {
				if ((invPermutation[i] % n) == 0) {
					invPermutation[i] = n;
				}
				else {
					invPermutation[i] = abs((invPermutation[i] / n - 1) * n - invPermutation[i]);
				}
			}
		}

		// Заполнение результирующего полинома с учётом финальной перестановки
		for (int i = 0; i <= resPol.GetDeg(); i++) {
			resPolPtr[i] = tmpPolPtr[permutation[invPermutation[i] - 1] - 1];
		}

		(*this) = resPol;

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::Pow7_NB_TEST(PolynomGF7N & a_pol, vector<int>& a_perm, vector<int> a_inv_perm, int a_7deg, int a_n) {

		PolynomGF7N tmpPol(a_n - 1);
		aal_uint16* tmpPolPtr = tmpPol.GetCoeffsPtr();
		// Копирование коэффициентов из входного полинома в увеличенный полином
		memcpy(tmpPolPtr, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		// Результат
		PolynomGF7N resPol(a_n - 1);
		aal_uint16* resPolPtr = resPol.GetCoeffsPtr();

		// Вычисление финальных позиций коэффициентов при возведении в степень
		for (int i = 0; i < a_inv_perm.size(); i++) {
			a_inv_perm[i] -= a_7deg;
			if (a_inv_perm[i] <= 0) {
				if ((a_inv_perm[i] % a_n) == 0) {
					a_inv_perm[i] = a_n;
				}
				else {
					a_inv_perm[i] = abs((a_inv_perm[i] / a_n - 1) * a_n - a_inv_perm[i]);
				}
			}
		}

		// Заполнение результирующего полинома с учётом финальной перестановки
		for (int i = 0; i <= resPol.GetDeg(); i++) {
			resPolPtr[i] = tmpPolPtr[a_perm[a_inv_perm[i] - 1] - 1];
		}

		(*this) = resPol;
		TrimZero();
		UnPackToParPack();

		return (*this);
	}

	vector<int> PolynomGF7N::GetPermutation(int a_n) const{

		vector<int> perm;

		int p = 2 * a_n + 1;
		int tmp;
		int val = 0;

		for (int i = 1; i <= a_n; i++) {
			tmp = PowGFp(7, i, p);
			if (tmp <= a_n) {
				val = tmp;
			}
			else {
				val = -tmp + p;
			}
			perm.push_back(val);
		}


		return perm;
	}

	vector<int> PolynomGF7N::InversePermutation(std::vector<int>& a_perm) const{
		vector<int> result(a_perm.size());

		for (int i = 0; i < a_perm.size(); i++) {
			result[a_perm[a_perm[i] - 1] - 1] = a_perm[i];
		}

		return result;
	}

	void PolynomGF7N::Factorization(std::vector<DecompositionMemberN>& a_fact, aal_uint32 a_val, bool degreeFlag) const{

		DecompositionMemberN divider = { 2,0 };

		while (a_val > 1) {
			while (a_val % divider.value == 0) {
				a_val /= divider.value;
				if (degreeFlag) {
					divider.deg++;
				}
				else {
					divider.deg = 1;
					a_fact.push_back(divider);
				}
			}
			if (degreeFlag && divider.deg != 0) {
				a_fact.push_back(divider);
			}

			if (divider.value == 2) {
				divider.value++;
				divider.deg = 0;
			}
			else {
				divider.value++;
				divider.deg = 0;
			}
		}

		return;
	}

	PolynomGF7N & PolynomGF7N::GenerateBinIrreducible(const aal_uint32 a_deg) {
		if (a_deg < 2)
			throw new exception("Степень полинома меньше 2.");

		PolynomGF7N X(a_deg);
		aal_uint16 *p = X.GetCoeffsPtr();
		p[a_deg] = 1;

		// Свободный член полинома
		aal_uint16 free_member = 1;

		bool flag = false;

		while (!flag && free_member < 7) {
			p[0] = free_member;
			flag = X.isIrreducible();
			free_member++;
		}

		(*this) = X;
		return (*this);
	}

	PolynomGF7N & PolynomGF7N::GenerateTrinIrreducible(const aal_uint32 a_deg) {
		if (a_deg < 2)
			throw new exception("Степень полинома меньше 2.");
		PolynomGF7N X(a_deg);
		aal_uint16 *p = X.GetCoeffsPtr();
		p[a_deg] = 1;

		// Вычисление предельной позиции второго ненулевого коэффициента в массиве,
		// до которой его необходимо сдвигать
		int position = (a_deg % 2 != 0) ? (a_deg / 2 + 1) : a_deg / 2;

		// Свободный член
		aal_uint16 free_member;

		bool flag = false;

		for (int i = 1; i <= position; i++) {
			for (int sec = 1; sec < 7; sec++) {
				free_member = 1;
				while (!flag && free_member < 7) {
					p[0] = free_member;
					p[i] = sec;
					flag = X.isIrreducible();
					free_member++;
				}

				if (flag) { break; }
			}

			if (flag) { break; }

			p[i] = 0;
		}

		(*this) = X;
		return (*this);
	}

	PolynomGF7N & PolynomGF7N::GenerateGNBIrreducible(const aal_uint32 a_deg) {
		if (a_deg < 2)
			throw new exception("Степень полинома меньше 2.");
		PolynomGF7N f0("1");
		PolynomGF7N f1("11");
		PolynomGF7N f;

		PolynomGF7N X("01");
		PolynomGF7N nullPol("0");

		if (GNB_Test(a_deg) != 0) {
			for (int i = 0; i < a_deg - 1; i++) {
				f.Mul(X, f1);
				f.Sub(f, f0);
				f0.Add(f1, nullPol);
				f1.Add(f, nullPol);
			}
		}
		else {
			throw new exception("Для указанной степени расширения поля не существует оптимальных нормальных базисов.");
		}

		(*this) = f;
		return (*this);
	}

	int PolynomGF7N::ElementOrder(PolynomGF7N & a_pol, PolynomGF7N & a_pol_mod, const int a_ord) {

		if (a_ord < 1)
			throw new exception("Порядок группы не может быть меньше 1.");

		UnPackToParPack();

		// Разложение порядка группы
		std::vector<DecompositionMemberN> factOrd;
		Factorization(factOrd, a_ord, true);

		// Единица мультипликативной группы
		PolynomGF7N X("1");
		// Порядок элемента мультипликативной группы
		int res = a_ord;

		PolynomGF7N A1;

		for (int i = 0; i < factOrd.size(); i++) {
			res /= pow((double)factOrd[i].value, (double)factOrd[i].deg);
			A1.PowGF7_n(a_pol, res, a_pol_mod);

			while (A1 != X) {
				A1.PowGF7_n(A1, factOrd[i].value, a_pol_mod);
				res *= factOrd[i].value;
			}
		}

		return res;
	}

	bool PolynomGF7N::IsGenerator(PolynomGF7N & a_pol, PolynomGF7N & a_pol_mod, const int a_ord) {
		return ((a_pol.ElementOrder(a_pol, a_pol_mod, a_ord - 1) == a_ord - 1) ? true : false);
	}

	bool PolynomGF7N::isPrimitivity() const{
		if ((*this).isIrreducible()) {
			PolynomGF7N p1("1"), pol, X("01");
			PolynomGF7N irr = (*this);

			std::vector<DecompositionMemberN> factOrd;
			aal_uint32 pn_1 = (int)(pow(7.0, (double)(*this).GetDeg())) - 1;
			Factorization(factOrd, pn_1, true);

			int deg, val;
			for (int i = 0; i < factOrd.size(); i++) {
				deg = pn_1 / factOrd[i].value;
				pol.ModPow(X, deg, irr);

				if (pol == p1) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}


	PolynomGF7N & PolynomGF7N::PolynomialToReduced(const PolynomGF7N & a_pol, int a_n) {

		// Степень произведения. Подразумевается, что она не превышает (2n-2) - удвоенный п. базис.
		int prod_deg = a_pol.GetDeg();
		// Количество 7-ок в результирующем полиноме
		int seven_groups_count = ((prod_deg + 1) % 7 == 0) ? (prod_deg + 1) / 7 : ((prod_deg + 1) / 7) + 1;
		int len = seven_groups_count * 7;
		aal_uint16* y = new aal_uint16[len]{ {} };
		aal_uint16* v = new aal_uint16[len]{ {} };

		PolynomGF7N tmpPol(len - 1);
		aal_uint16* pol = tmpPol.GetCoeffsPtr();
		memcpy(pol, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		int n;
		if (prod_deg <= a_n - 1) {
			n = DegDecompLength(a_n - 1, 7) == 1 ? 2 : DegDecompLength(a_n - 1, 7);
		}
		else if (prod_deg >= a_n && prod_deg <= (2 * a_n - 2)) {
			n = DegDecompLength(2 * a_n - 2, 7) == 1 ? 2 : DegDecompLength(2 * a_n - 2, 7);
		}

		int l, q, dd;

		for (int i = 0; i < seven_groups_count; i++) {
			y[i * 7 + 0] = (((pol[i * 7 + 0] + 2 * pol[i * 7 + 2] - pol[i * 7 + 4] - pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 1] = (((pol[i * 7 + 1] - 4 * pol[i * 7 + 3] - 4 * pol[i * 7 + 5]) % 7) + 7) % 7;
			y[i * 7 + 2] = (((pol[i * 7 + 2] + 4 * pol[i * 7 + 4] + pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 3] = (((pol[i * 7 + 3] - 2 * pol[i * 7 + 5]) % 7) + 7) % 7;
			y[i * 7 + 4] = (((pol[i * 7 + 4] - pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 5] = pol[i * 7 + 5];
			y[i * 7 + 6] = pol[i * 7 + 6];
		}

		// Количество коэффициентов, которое необходимо рассчитать
		// на последней итерации цикла по m (7 по умолчанию)
		int num_oper;

		for (int j = 2; j < n + 1; j++) {
			l = pow(7, j);
			q = pow(7, j - 1);
			dd = j == n ? 4 : 1;

			int max_index = (prod_deg / q) * q;

			// Количество итераций по m
			int m_max;
			if (max_index > 6 * q) {
				m_max = ((max_index - 6 * q) % l) == 0 ? ((max_index - 6 * q) / l) : ((max_index - 6 * q) / l) + 1;
			}
			else {
				m_max = 0;
			}

			// вспомогательные переменные для хранения коэффициентов
			// если индекс элемента y будет > len, то заменить его на 0
			aal_uint16 y0, y1, y2, y3, y4, y5, y6;
			aal_uint16 y0i, y1i, y2i, y3i, y4i, y5i, y6i, y7i;
			aal_uint16 y2_i, y3_i, y4_i, y5_i, y6_i, y7_i;

			for (int m = 0; m < m_max + 1; m++) {
				num_oper = 7;
				// Определение количества коэффициентов, которое необходимо рассчитать на последней итерации
				if (m == m_max) {
					if ((m*l + 6 * q) == max_index) {
						num_oper = 7;
					}
					else if ((m*l + 5 * q) == max_index) {
						num_oper = 6;
					}
					else if ((m*l + 4 * q) == max_index) {
						num_oper = 5;
					}
					else if ((m*l + 3 * q) == max_index) {
						num_oper = 4;
					}
					else if ((m*l + 2 * q) == max_index) {
						num_oper = 3;
					}
					else if ((m*l + 1 * q) == max_index) {
						num_oper = 2;
					}
					else if ((m*l + 0) == max_index) {
						num_oper = 1;
					}
				}

				// установка переменных y0-y6, участвующих в расчётах
				y0 = (m*l + 0) < len ? y[m*l + 0] : 0;
				y1 = (m*l + 1 * q) < len ? y[m*l + 1 * q] : 0;
				y2 = (m*l + 2 * q) < len ? y[m*l + 2 * q] : 0;
				y3 = (m*l + 3 * q) < len ? y[m*l + 3 * q] : 0;
				y4 = (m*l + 4 * q) < len ? y[m*l + 4 * q] : 0;
				y5 = (m*l + 5 * q) < len ? y[m*l + 5 * q] : 0;
				y6 = (m*l + 6 * q) < len ? y[m*l + 6 * q] : 0;
				// Вычисление каждого q-го коэффициента
				// Вспомогательный цикл из 1 итерации
				for (int p1 = 0; p1 < 1; p1++) {
					v[m*l + 0 + 0] = (((dd * (y0 + 2 * y2 - y4 - y6)) % 7) + 7) % 7;
					if (num_oper == 1) break;

					v[m*l + 1 * q + 0] = (((y1 - 4 * y3 - 4 * y5) % 7) + 7) % 7;
					if (num_oper == 2) break;

					v[m*l + 2 * q + 0] = (((y2 + 4 * y4 + y6) % 7) + 7) % 7;
					if (num_oper == 3) break;

					v[m*l + 3 * q + 0] = (((y3 - 2 * y5) % 7) + 7) % 7;
					if (num_oper == 4) break;

					v[m*l + 4 * q + 0] = (((y4 - y6) % 7) + 7) % 7;
					if (num_oper == 5) break;

					v[m*l + 5 * q + 0] = y5;
					if (num_oper == 6) break;

					v[m*l + 6 * q + 0] = y6;
					if (num_oper == 7) break;
				}


				for (int i = 1; i < q; i++) {
					// установка переменных y0i-y6i, участвующих в расчётах промежуточных коэффициентов
					y0i = (m*l + i) < len ? y[m*l + i] : 0;
					y1i = (m*l + 1 * q + i) < len ? y[m*l + 1 * q + i] : 0;
					y2i = (m*l + 2 * q + i) < len ? y[m*l + 2 * q + i] : 0;
					y2_i = (m*l + 2 * q - i) < len ? y[m*l + 2 * q - i] : 0;
					y3i = (m*l + 3 * q + i) < len ? y[m*l + 3 * q + i] : 0;
					y3_i = (m*l + 3 * q - i) < len ? y[m*l + 3 * q - i] : 0;
					y4i = (m*l + 4 * q + i) < len ? y[m*l + 4 * q + i] : 0;
					y4_i = (m*l + 4 * q - i) < len ? y[m*l + 4 * q - i] : 0;
					y5i = (m*l + 5 * q + i) < len ? y[m*l + 5 * q + i] : 0;
					y5_i = (m*l + 5 * q - i) < len ? y[m*l + 5 * q - i] : 0;
					y6i = (m*l + 6 * q + i) < len ? y[m*l + 6 * q + i] : 0;
					y6_i = (m*l + 6 * q - i) < len ? y[m*l + 6 * q - i] : 0;
					y7i = (m*l + 7 * q + i) < len ? y[m*l + 7 * q + i] : 0;
					y7_i = (m*l + 7 * q - i) < len ? y[m*l + 7 * q - i] : 0;

					for (int p2 = 0; p2 < 1; p2++) {
						if ((m*l + 0 * q + i) < len) {
							v[m*l + 0 * q + i] = (((y0i + y2_i + 2 * y2i - 4 * y4_i - y4i - 4 * y6_i - y6i) % 7) + 7) % 7;
						}
						if (num_oper == 1) break;

						if ((m*l + 1 * q + i) < len) {
							v[m*l + 1 * q + i] = (((y1i + y3_i - 4 * y3i + 4 * y5_i - 4 * y5i + y7_i) % 7) + 7) % 7;
						}
						if (num_oper == 2) break;

						if ((m*l + 2 * q + i) < len) {
							v[m*l + 2 * q + i] = (((y2i + y4_i + 4 * y4i - 2 * y6_i + y6i) % 7) + 7) % 7;
						}
						if (num_oper == 3) break;

						if ((m*l + 3 * q + i) < len) {
							v[m*l + 3 * q + i] = (((y3i + y5_i - 2 * y5i - y7_i) % 7) + 7) % 7;
						}
						if (num_oper == 4) break;

						if ((m*l + 4 * q + i) < len) {
							v[m*l + 4 * q + i] = (((y4i + y6_i - y6i) % 7) + 7) % 7;
						}
						if (num_oper == 5) break;

						if ((m*l + 5 * q + i) < len) {
							v[m*l + 5 * q + i] = (y5i + y7_i) % 7;
						}
						if (num_oper == 6) break;

						if ((m*l + 6 * q + i) < len) {
							v[m*l + 6 * q + i] = y6i;
						}
						if (num_oper == 7) break;
					}
				}

			}
			memcpy(y, v, sizeof(aal_uint16) * len);
		}

		(*this) = PolynomGF7N(v, len);

		delete[] y;
		delete[] v;

		TrimZero();
		//UnPackToParPack();

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::PToR_TEST(PolynomGF7N & a_pol, int a_n, int& add_f0, int& add_fk, int& mul_f0, int& mul_fk, int& b_size, int& k_step) {
		// Степень произведения. Подразумевается, что она не превышает (2n-2) - удвоенный п. базис.
		int prod_deg = a_pol.GetDeg();
		// Количество 7-ок в результирующем полиноме
		int seven_groups_count = ((prod_deg + 1) % 7 == 0) ? (prod_deg + 1) / 7 : ((prod_deg + 1) / 7) + 1;
		int len = seven_groups_count * 7;
		aal_uint16* y = new aal_uint16[len]{ {} };
		aal_uint16* v = new aal_uint16[len]{ {} };

		PolynomGF7N tmpPol(len - 1);
		aal_uint16* pol = tmpPol.GetCoeffsPtr();
		memcpy(pol, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));


		int n = DegDecompLength(2 * a_n - 2, 7) == 1 ? 2 : DegDecompLength(2 * a_n - 2, 7);
		int l, q, dd;

		b_size = 2 * a_n - 2;
		k_step = n;

		add_f0 = 0;
		add_fk = 0;
		mul_f0 = 0;
		mul_fk = 0;

		for (int i = 0; i < seven_groups_count; i++) {
			y[i * 7 + 0] = (((pol[i * 7 + 0] + 2 * pol[i * 7 + 2] - pol[i * 7 + 4] - pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 1] = (((pol[i * 7 + 1] - 4 * pol[i * 7 + 3] - 4 * pol[i * 7 + 5]) % 7) + 7) % 7;
			y[i * 7 + 2] = (((pol[i * 7 + 2] + 4 * pol[i * 7 + 4] + pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 3] = (((pol[i * 7 + 3] - 2 * pol[i * 7 + 5]) % 7) + 7) % 7;
			y[i * 7 + 4] = (((pol[i * 7 + 4] - pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 5] = pol[i * 7 + 5];
			y[i * 7 + 6] = pol[i * 7 + 6];
			add_f0 += 9;
			mul_f0 += 5;
		}

		// Количество коэффициентов, которое необходимо рассчитать
		// на последней итерации цикла по m (7 по умолчанию)
		int num_oper;

		for (int j = 2; j < n + 1; j++) {
			l = pow(7, j);
			q = pow(7, j - 1);
			dd = j == n ? 4 : 1;

			int max_index = (prod_deg / q) * q;

			// Количество итераций по m
			int m_max;
			if (max_index > 6 * q) {
				m_max = ((max_index - 6 * q) % l) == 0 ? ((max_index - 6 * q) / l) : ((max_index - 6 * q) / l) + 1;
			}
			else {
				m_max = 0;
			}

			// вспомогательные переменные для хранения коэффициентов
			// если индекс элемента y будет > len, то заменить его на 0
			aal_uint16 y0, y1, y2, y3, y4, y5, y6;
			aal_uint16 y0i, y1i, y2i, y3i, y4i, y5i, y6i, y7i;
			aal_uint16 y2_i, y3_i, y4_i, y5_i, y6_i, y7_i;

			for (int m = 0; m < m_max + 1; m++) {
				num_oper = 7;
				// Определение количества коэффициентов, которое необходимо рассчитать на последней итерации
				if (m == m_max) {
					if ((m*l + 6 * q) == max_index) {
						num_oper = 7;
					}
					else if ((m*l + 5 * q) == max_index) {
						num_oper = 6;
					}
					else if ((m*l + 4 * q) == max_index) {
						num_oper = 5;
					}
					else if ((m*l + 3 * q) == max_index) {
						num_oper = 4;
					}
					else if ((m*l + 2 * q) == max_index) {
						num_oper = 3;
					}
					else if ((m*l + 1 * q) == max_index) {
						num_oper = 2;
					}
					else if ((m*l + 0) == max_index) {
						num_oper = 1;
					}
				}

				// установка переменных y0-y6, участвующих в расчётах
				y0 = (m*l + 0) < len ? y[m*l + 0] : 0;
				y1 = (m*l + 1 * q) < len ? y[m*l + 1 * q] : 0;
				y2 = (m*l + 2 * q) < len ? y[m*l + 2 * q] : 0;
				y3 = (m*l + 3 * q) < len ? y[m*l + 3 * q] : 0;
				y4 = (m*l + 4 * q) < len ? y[m*l + 4 * q] : 0;
				y5 = (m*l + 5 * q) < len ? y[m*l + 5 * q] : 0;
				y6 = (m*l + 6 * q) < len ? y[m*l + 6 * q] : 0;
				// Вычисление каждого q-го коэффициента
				// Вспомогательный цикл из 1 итерации
				for (int p1 = 0; p1 < 1; p1++) {
					v[m*l + 0 + 0] = (((dd * (y0 + 2 * y2 - y4 - y6)) % 7) + 7) % 7;
					add_fk += 3;
					mul_fk += 2;
					if (num_oper == 1) break;

					v[m*l + 1 * q + 0] = (((y1 - 4 * y3 - 4 * y5) % 7) + 7) % 7;
					add_fk += 2;
					mul_fk += 2;
					if (num_oper == 2) break;

					v[m*l + 2 * q + 0] = (((y2 + 4 * y4 + y6) % 7) + 7) % 7;
					add_fk += 2;
					mul_fk += 1;
					if (num_oper == 3) break;

					v[m*l + 3 * q + 0] = (((y3 - 2 * y5) % 7) + 7) % 7;
					add_fk += 1;
					mul_fk += 1;
					if (num_oper == 4) break;

					v[m*l + 4 * q + 0] = (((y4 - y6) % 7) + 7) % 7;
					add_fk += 1;
					mul_fk += 0;
					if (num_oper == 5) break;

					v[m*l + 5 * q + 0] = y5;
					if (num_oper == 6) break;

					v[m*l + 6 * q + 0] = y6;
					if (num_oper == 7) break;
				}


				for (int i = 1; i < q; i++) {
					// установка переменных y0i-y6i, участвующих в расчётах промежуточных коэффициентов
					y0i = (m*l + i) < len ? y[m*l + i] : 0;
					y1i = (m*l + 1 * q + i) < len ? y[m*l + 1 * q + i] : 0;
					y2i = (m*l + 2 * q + i) < len ? y[m*l + 2 * q + i] : 0;
					y2_i = (m*l + 2 * q - i) < len ? y[m*l + 2 * q - i] : 0;
					y3i = (m*l + 3 * q + i) < len ? y[m*l + 3 * q + i] : 0;
					y3_i = (m*l + 3 * q - i) < len ? y[m*l + 3 * q - i] : 0;
					y4i = (m*l + 4 * q + i) < len ? y[m*l + 4 * q + i] : 0;
					y4_i = (m*l + 4 * q - i) < len ? y[m*l + 4 * q - i] : 0;
					y5i = (m*l + 5 * q + i) < len ? y[m*l + 5 * q + i] : 0;
					y5_i = (m*l + 5 * q - i) < len ? y[m*l + 5 * q - i] : 0;
					y6i = (m*l + 6 * q + i) < len ? y[m*l + 6 * q + i] : 0;
					y6_i = (m*l + 6 * q - i) < len ? y[m*l + 6 * q - i] : 0;
					y7i = (m*l + 7 * q + i) < len ? y[m*l + 7 * q + i] : 0;
					y7_i = (m*l + 7 * q - i) < len ? y[m*l + 7 * q - i] : 0;

					for (int p2 = 0; p2 < 1; p2++) {
						if ((m*l + 0 * q + i) < len) {
							v[m*l + 0 * q + i] = (((y0i + y2_i + 2 * y2i - 4 * y4_i - y4i - 4 * y6_i - y6i) % 7) + 7) % 7;
							add_fk += 6;
							mul_fk += 3;
						}
						if (num_oper == 1) break;

						if ((m*l + 1 * q + i) < len) {
							v[m*l + 1 * q + i] = (((y1i + y3_i - 4 * y3i + 4 * y5_i - 4 * y5i + y7_i) % 7) + 7) % 7;
							add_fk += 5;
							mul_fk += 3;
						}
						if (num_oper == 2) break;

						if ((m*l + 2 * q + i) < len) {
							v[m*l + 2 * q + i] = (((y2i + y4_i + 4 * y4i - 2 * y6_i + y6i) % 7) + 7) % 7;
							add_fk += 4;
							mul_fk += 2;
						}
						if (num_oper == 3) break;

						if ((m*l + 3 * q + i) < len) {
							v[m*l + 3 * q + i] = (((y3i + y5_i - 2 * y5i - y7_i) % 7) + 7) % 7;
							add_fk += 3;
							mul_fk += 1;
						}
						if (num_oper == 4) break;

						if ((m*l + 4 * q + i) < len) {
							v[m*l + 4 * q + i] = (((y4i + y6_i - y6i) % 7) + 7) % 7;
							add_fk += 2;
							mul_fk += 0;
						}
						if (num_oper == 5) break;

						if ((m*l + 5 * q + i) < len) {
							v[m*l + 5 * q + i] = (y5i + y7_i) % 7;
							add_fk += 1;
							mul_fk += 0;
						}
						if (num_oper == 6) break;

						if ((m*l + 6 * q + i) < len) {
							v[m*l + 6 * q + i] = y6i;
						}
						if (num_oper == 7) break;
					}
				}

			}
			memcpy(y, v, sizeof(aal_uint16) * len);
		}

		(*this) = PolynomGF7N(v, len);

		delete[] y;
		delete[] v;

		TrimZero();

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::PToR_TEST_OLD(PolynomGF7N & a_pol, int a_n, int& add_f0, int& add_fk, int& mul_f0, int& mul_fk, int& b_size, int& k_step) {

		aal_uint16* y = new aal_uint16[2401]{ {} };
		aal_uint16* v = new aal_uint16[2401]{ {} };

		PolynomGF7N tmpPol(2400);
		aal_uint16* pol = tmpPol.GetCoeffsPtr();
		memcpy(pol, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		int n = 4;
		int l, q, dd;

		b_size = 2 * a_n - 2;
		k_step = n;

		add_f0 = 0;
		add_fk = 0;
		mul_f0 = 0;
		mul_fk = 0;

		for (int i = 0; i < 343; i++) {
			y[i * 7 + 0] = (((pol[i * 7 + 0] + 2 * pol[i * 7 + 2] - pol[i * 7 + 4] - pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 1] = (((pol[i * 7 + 1] - 4 * pol[i * 7 + 3] - 4 * pol[i * 7 + 5]) % 7) + 7) % 7;
			y[i * 7 + 2] = (((pol[i * 7 + 2] + 4 * pol[i * 7 + 4] + pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 3] = (((pol[i * 7 + 3] - 2 * pol[i * 7 + 5]) % 7) + 7) % 7;
			y[i * 7 + 4] = (((pol[i * 7 + 4] - pol[i * 7 + 6]) % 7) + 7) % 7;
			y[i * 7 + 5] = pol[i * 7 + 5];
			y[i * 7 + 6] = pol[i * 7 + 6];
			add_f0 += 9;
			mul_f0 += 5;
		}

		for (int j = 2; j < n + 1; j++) {
			l = pow(7, j);
			q = pow(7, j - 1);
			dd = j == n ? 4 : 1;

			// вспомогательные переменные для хранения коэффициентов
			// если индекс элемента y будет > len, то заменить его на 0
			aal_uint16 y0, y1, y2, y3, y4, y5, y6;
			aal_uint16 y0i, y1i, y2i, y3i, y4i, y5i, y6i, y7i;
			aal_uint16 y2_i, y3_i, y4_i, y5_i, y6_i, y7_i;

			for (int m = 0; m < pow(7, n - j); m++) {
				// установка переменных y0-y6, участвующих в расчётах
				y0 = y[m*l + 0];
				y1 = y[m*l + 1 * q];
				y2 = y[m*l + 2 * q];
				y3 = y[m*l + 3 * q];
				y4 = y[m*l + 4 * q];
				y5 = y[m*l + 5 * q];
				y6 = y[m*l + 6 * q];

				v[m*l + 0 + 0] = (((dd * (y0 + 2 * y2 - y4 - y6)) % 7) + 7) % 7;
				add_fk += 3;
				mul_fk += 2;

				v[m*l + 1 * q + 0] = (((y1 - 4 * y3 - 4 * y5) % 7) + 7) % 7;
				add_fk += 2;
				mul_fk += 2;

				v[m*l + 2 * q + 0] = (((y2 + 4 * y4 + y6) % 7) + 7) % 7;
				add_fk += 2;
				mul_fk += 1;

				v[m*l + 3 * q + 0] = (((y3 - 2 * y5) % 7) + 7) % 7;
				add_fk += 1;
				mul_fk += 1;

				v[m*l + 4 * q + 0] = (((y4 - y6) % 7) + 7) % 7;
				add_fk += 1;
				mul_fk += 0;

				v[m*l + 5 * q + 0] = y5;
				v[m*l + 6 * q + 0] = y6;

				for (int i = 1; i < q; i++) {
					// установка переменных y0i-y6i, участвующих в расчётах промежуточных коэффициентов
					y0i = y[m*l + i];
					y1i = y[m*l + 1 * q + i];
					y2i = y[m*l + 2 * q + i];
					y2_i = y[m*l + 2 * q - i];
					y3i = y[m*l + 3 * q + i];
					y3_i = y[m*l + 3 * q - i];
					y4i = y[m*l + 4 * q + i];
					y4_i = y[m*l + 4 * q - i];
					y5i = y[m*l + 5 * q + i];
					y5_i = y[m*l + 5 * q - i];
					y6i = y[m*l + 6 * q + i];
					y6_i = y[m*l + 6 * q - i];
					y7_i = y[m*l + 7 * q - i];

					v[m*l + 0 * q + i] = (((y0i + y2_i + 2 * y2i - 4 * y4_i - y4i - 4 * y6_i - y6i) % 7) + 7) % 7;
					add_fk += 6;
					mul_fk += 3;

					v[m*l + 1 * q + i] = (((y1i + y3_i - 4 * y3i + 4 * y5_i - 4 * y5i + y7_i) % 7) + 7) % 7;
					add_fk += 5;
					mul_fk += 3;

					v[m*l + 2 * q + i] = (((y2i + y4_i + 4 * y4i - 2 * y6_i + y6i) % 7) + 7) % 7;
					add_fk += 4;
					mul_fk += 2;

					v[m*l + 3 * q + i] = (((y3i + y5_i - 2 * y5i - y7_i) % 7) + 7) % 7;
					add_fk += 3;
					mul_fk += 1;

					v[m*l + 4 * q + i] = (((y4i + y6_i - y6i) % 7) + 7) % 7;
					add_fk += 2;
					mul_fk += 0;

					v[m*l + 5 * q + i] = (y5i + y7_i) % 7;
					add_fk += 1;
					mul_fk += 0;

					v[m*l + 6 * q + i] = y6i;
				}
			}
			memcpy(y, v, sizeof(aal_uint16) * 2401);
		}

		(*this) = PolynomGF7N(v, 2401);

		delete[] y;
		delete[] v;

		TrimZero();

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::ReducedToPolynomial(const PolynomGF7N & a_pol, int a_n) {
		// Степень произведения. Подразумевается, что она не превышает (2n-2) - удвоенный п. базис.
		int prod_deg = a_pol.GetDeg();
		// Количество 7-ок в результирующем полиноме
		int seven_groups_count = ((prod_deg + 1) % 7 == 0) ? (prod_deg + 1) / 7 : ((prod_deg + 1) / 7) + 1;
		int len = seven_groups_count * 7;
		aal_uint16* y = new aal_uint16[len]{ {} };
		aal_uint16* v = new aal_uint16[len]{ {} };

		PolynomGF7N tmpPol(len - 1);
		aal_uint16* pol = tmpPol.GetCoeffsPtr();
		memcpy(pol, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		int n;
		if (prod_deg <= a_n - 1) {
			n = DegDecompLength(a_n - 1, 7) == 1 ? 2 : DegDecompLength(a_n - 1, 7);
		}
		else if (prod_deg >= a_n && prod_deg <= (2 * a_n - 2)) {
			n = DegDecompLength(2 * a_n - 2, 7) == 1 ? 2 : DegDecompLength(2 * a_n - 2, 7);
		}

		int l, m, cc;

		// Количество коэффициентов, которое необходимо рассчитать
		// на последней итерации цикла по m (7 по умолчанию)
		int num_oper;

		for (int j = n; j > 1; j--) {
			l = pow(7, j);
			m = pow(7, j - 1);
			cc = j == n ? 2 : 1;

			int max_index = (prod_deg / m) * m;

			// Количество итераций по m
			int i_max;
			if (max_index > 6 * m) {
				i_max = ((max_index - 6 * m) % l) == 0 ? ((max_index - 6 * m) / l) : ((max_index - 6 * m) / l) + 1;
			}
			else {
				i_max = 0;
			}

			// вспомогательные переменные для хранения коэффициентов
			// если индекс элемента y будет > len, то заменить его на 0
			aal_uint16 p0, p1, p2, p3, p4, p5, p6;
			aal_uint16 p0q, p1q, p2q, p3q, p4q, p5q, p6q, p7q;
			aal_uint16 p2_q, p3_q, p4_q, p5_q, p6_q, p7_q;

			for (int i = 0; i < i_max + 1; i++) {
				num_oper = 7;
				// Определение количества коэффициентов, которое необходимо рассчитать на последней итерации
				if (i == i_max) {
					if ((i*l + 6 * m) == max_index) {
						num_oper = 7;
					}
					else if ((i*l + 5 * m) == max_index) {
						num_oper = 6;
					}
					else if ((i*l + 4 * m) == max_index) {
						num_oper = 5;
					}
					else if ((i*l + 3 * m) == max_index) {
						num_oper = 4;
					}
					else if ((i*l + 2 * m) == max_index) {
						num_oper = 3;
					}
					else if ((i*l + 1 * m) == max_index) {
						num_oper = 2;
					}
					else if ((i*l + 0) == max_index) {
						num_oper = 1;
					}
				}

				// установка переменных y0-y6, участвующих в расчётах
				p0 = (i*l + 0) < len ? pol[i*l + 0] : 0;
				p1 = (i*l + 1 * m) < len ? pol[i*l + 1 * m] : 0;
				p2 = (i*l + 2 * m) < len ? pol[i*l + 2 * m] : 0;
				p3 = (i*l + 3 * m) < len ? pol[i*l + 3 * m] : 0;
				p4 = (i*l + 4 * m) < len ? pol[i*l + 4 * m] : 0;
				p5 = (i*l + 5 * m) < len ? pol[i*l + 5 * m] : 0;
				p6 = (i*l + 6 * m) < len ? pol[i*l + 6 * m] : 0;
				// Вычисление каждого m-го коэффициента
				// Вспомогательный цикл из 1 итерации
				for (int a1 = 0; a1 < 1; a1++) {
					y[i*l + 0 * m + 0] = (((cc*p0 - 2 * p2 + 2 * p4 - 2 * p6) % 7) + 7) % 7;
					if (num_oper == 1) break;

					y[i*l + 1 * m + 0] = (((p1 + 4 * p3 - 2 * p5) % 7) + 7) % 7;
					if (num_oper == 2) break;

					y[i*l + 2 * m + 0] = (((p2 - 4 * p4 + 2 * p6) % 7) + 7) % 7;
					if (num_oper == 3) break;

					y[i*l + 3 * m + 0] = (p3 + 2 * p5) % 7;
					if (num_oper == 4) break;

					y[i*l + 4 * m + 0] = (p4 + p6) % 7;
					if (num_oper == 5) break;

					y[i*l + 5 * m + 0] = p5;
					if (num_oper == 6) break;

					y[i*l + 6 * m + 0] = p6;
					if (num_oper == 7) break;
				}

				for (int q = 1; q < m; q++) {
					p0q = (i*l + 0 * m + q) < len ? pol[i*l + 0 * m + q] : 0;
					p1q = (i*l + 1 * m + q) < len ? pol[i*l + 1 * m + q] : 0;
					p2q = (i*l + 2 * m + q) < len ? pol[i*l + 2 * m + q] : 0;
					p2_q = (i*l + 2 * m - q) < len ? pol[i*l + 2 * m - q] : 0;
					p3q = (i*l + 3 * m + q) < len ? pol[i*l + 3 * m + q] : 0;
					p3_q = (i*l + 3 * m - q) < len ? pol[i*l + 3 * m - q] : 0;
					p4q = (i*l + 4 * m + q) < len ? pol[i*l + 4 * m + q] : 0;
					p4_q = (i*l + 4 * m - q) < len ? pol[i*l + 4 * m - q] : 0;
					p5q = (i*l + 5 * m + q) < len ? pol[i*l + 5 * m + q] : 0;
					p5_q = (i*l + 5 * m - q) < len ? pol[i*l + 5 * m - q] : 0;
					p6q = (i*l + 6 * m + q) < len ? pol[i*l + 6 * m + q] : 0;
					p6_q = (i*l + 6 * m - q) < len ? pol[i*l + 6 * m - q] : 0;
					p7q = (i*l + 7 * m + q) < len ? pol[i*l + 7 * m + q] : 0;
					p7_q = (i*l + 7 * m - q) < len ? pol[i*l + 7 * m - q] : 0;

					for (int a2 = 0; a2 < 1; a2++) {
						if ((i*l + 0 * m + q) < len) {
							y[i*l + 0 * m + q] = (((p0q - p2_q - p2q + p4_q + p4q - p6_q - p6q) % 7) + 7) % 7;
						}
						if (num_oper == 1) break;

						if ((i*l + 1 * m + q) < len) {
							y[i*l + 1 * m + q] = (((p1q - p3_q - 2 * p3q + 2 * p5_q - 4 * p5q + 4 * p7_q) % 7) + 7) % 7;
						}
						if (num_oper == 2) break;

						if ((i*l + 2 * m + q) < len) {
							y[i*l + 2 * m + q] = (((p2q - p4_q + 4 * p4q - 4 * p6_q - p6q) % 7) + 7) % 7;
						}
						if (num_oper == 3) break;

						if ((i*l + 3 * m + q) < len) {
							y[i*l + 3 * m + q] = (((p3q - p5_q - 4 * p5q + 4 * p7_q) % 7) + 7) % 7;
						}
						if (num_oper == 4) break;

						if ((i*l + 4 * m + q) < len) {
							y[i*l + 4 * m + q] = (((p4q - p6_q + 2 * p6q) % 7) + 7) % 7;
						}
						if (num_oper == 5) break;

						if ((i*l + 5 * m + q) < len) {
							y[i*l + 5 * m + q] = (((p5q - p7_q) % 7) + 7) % 7;
						}
						if (num_oper == 6) break;

						if ((i*l + 6 * m + q) < len) {
							y[i*l + 6 * m + q] = p6q;
						}
						if (num_oper == 7) break;
					}
				}
			}
			memcpy(pol, y, sizeof(aal_uint16) * len);
		}

		for (int j = 0; j < seven_groups_count; j++) {
			v[j * 7 + 0] = (((y[j * 7 + 0] - 2 * y[j * 7 + 2] + 2 * y[j * 7 + 4] - 2 * y[j * 7 + 6]) % 7) + 7) % 7;
			v[j * 7 + 1] = (((y[j * 7 + 1] + 4 * y[j * 7 + 3] - 2 * y[j * 7 + 5]) % 7) + 7) % 7;
			v[j * 7 + 2] = (((y[j * 7 + 2] - 4 * y[j * 7 + 4] + 2 * y[j * 7 + 6]) % 7) + 7) % 7;
			v[j * 7 + 3] = (y[j * 7 + 3] + 2 * y[j * 7 + 5]) % 7;
			v[j * 7 + 4] = (y[j * 7 + 4] + y[j * 7 + 6]) % 7;
			v[j * 7 + 5] = y[j * 7 + 5];
			v[j * 7 + 6] = y[j * 7 + 6];
		}


		(*this) = PolynomGF7N(v, len);

		delete[] y;
		delete[] v;

		TrimZero();
		//UnPackToParPack();

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::RToP_TEST(PolynomGF7N & a_pol, int a_n, int& add_f0, int& add_fk, int& mul_f0, int& mul_fk, int& b_size, int& k_step) {
		// Степень произведения. Подразумевается, что она не превышает (2n-2) - удвоенный п. базис.
		int prod_deg = a_pol.GetDeg();
		// Количество 7-ок в результирующем полиноме
		int seven_groups_count = ((prod_deg + 1) % 7 == 0) ? (prod_deg + 1) / 7 : ((prod_deg + 1) / 7) + 1;
		int len = seven_groups_count * 7;
		aal_uint16* y = new aal_uint16[len]{ {} };
		aal_uint16* v = new aal_uint16[len]{ {} };

		PolynomGF7N tmpPol(len - 1);
		aal_uint16* pol = tmpPol.GetCoeffsPtr();
		memcpy(pol, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		int n = DegDecompLength(2 * a_n - 2, 7) == 1 ? 2 : DegDecompLength(2 * a_n - 2, 7);

		int l, m, cc;

		// Количество коэффициентов, которое необходимо рассчитать
		// на последней итерации цикла по m (7 по умолчанию)
		int num_oper;

		b_size = a_n - 1;
		k_step = n;

		add_f0 = 0;
		add_fk = 0;
		mul_f0 = 0;
		mul_fk = 0;

		for (int j = n; j > 1; j--) {
			l = pow(7, j);
			m = pow(7, j - 1);
			cc = j == n ? 2 : 1;

			int max_index = (prod_deg / m) * m;

			// Количество итераций по m
			int i_max;
			if (max_index > 6 * m) {
				i_max = ((max_index - 6 * m) % l) == 0 ? ((max_index - 6 * m) / l) : ((max_index - 6 * m) / l) + 1;
			}
			else {
				i_max = 0;
			}

			// вспомогательные переменные для хранения коэффициентов
			// если индекс элемента y будет > len, то заменить его на 0
			aal_uint16 p0, p1, p2, p3, p4, p5, p6;
			aal_uint16 p0q, p1q, p2q, p3q, p4q, p5q, p6q, p7q;
			aal_uint16 p2_q, p3_q, p4_q, p5_q, p6_q, p7_q;

			for (int i = 0; i < i_max + 1; i++) {
				num_oper = 7;
				// Определение количества коэффициентов, которое необходимо рассчитать на последней итерации
				if (i == i_max) {
					if ((i*l + 6 * m) == max_index) {
						num_oper = 7;
					}
					else if ((i*l + 5 * m) == max_index) {
						num_oper = 6;
					}
					else if ((i*l + 4 * m) == max_index) {
						num_oper = 5;
					}
					else if ((i*l + 3 * m) == max_index) {
						num_oper = 4;
					}
					else if ((i*l + 2 * m) == max_index) {
						num_oper = 3;
					}
					else if ((i*l + 1 * m) == max_index) {
						num_oper = 2;
					}
					else if ((i*l + 0) == max_index) {
						num_oper = 1;
					}
				}

				// установка переменных y0-y6, участвующих в расчётах
				p0 = (i*l + 0) < len ? pol[i*l + 0] : 0;
				p1 = (i*l + 1 * m) < len ? pol[i*l + 1 * m] : 0;
				p2 = (i*l + 2 * m) < len ? pol[i*l + 2 * m] : 0;
				p3 = (i*l + 3 * m) < len ? pol[i*l + 3 * m] : 0;
				p4 = (i*l + 4 * m) < len ? pol[i*l + 4 * m] : 0;
				p5 = (i*l + 5 * m) < len ? pol[i*l + 5 * m] : 0;
				p6 = (i*l + 6 * m) < len ? pol[i*l + 6 * m] : 0;
				// Вычисление каждого m-го коэффициента
				// Вспомогательный цикл из 1 итерации
				for (int a1 = 0; a1 < 1; a1++) {
					y[i*l + 0 * m + 0] = (((cc*p0 - 2 * p2 + 2 * p4 - 2 * p6) % 7) + 7) % 7;
					add_fk += 3;
					mul_fk += 4;
					if (num_oper == 1) break;

					y[i*l + 1 * m + 0] = (((p1 + 4 * p3 - 2 * p5) % 7) + 7) % 7;
					add_fk += 2;
					mul_fk += 2;
					if (num_oper == 2) break;

					y[i*l + 2 * m + 0] = (((p2 - 4 * p4 + 2 * p6) % 7) + 7) % 7;
					add_fk += 2;
					mul_fk += 2;
					if (num_oper == 3) break;

					y[i*l + 3 * m + 0] = (p3 + 2 * p5) % 7;
					add_fk += 1;
					mul_fk += 1;
					if (num_oper == 4) break;

					y[i*l + 4 * m + 0] = (p4 + p6) % 7;
					add_fk += 1;
					mul_fk += 0;
					if (num_oper == 5) break;

					y[i*l + 5 * m + 0] = p5;
					if (num_oper == 6) break;

					y[i*l + 6 * m + 0] = p6;
					if (num_oper == 7) break;
				}

				for (int q = 1; q < m; q++) {
					p0q = (i*l + 0 * m + q) < len ? pol[i*l + 0 * m + q] : 0;
					p1q = (i*l + 1 * m + q) < len ? pol[i*l + 1 * m + q] : 0;
					p2q = (i*l + 2 * m + q) < len ? pol[i*l + 2 * m + q] : 0;
					p2_q = (i*l + 2 * m - q) < len ? pol[i*l + 2 * m - q] : 0;
					p3q = (i*l + 3 * m + q) < len ? pol[i*l + 3 * m + q] : 0;
					p3_q = (i*l + 3 * m - q) < len ? pol[i*l + 3 * m - q] : 0;
					p4q = (i*l + 4 * m + q) < len ? pol[i*l + 4 * m + q] : 0;
					p4_q = (i*l + 4 * m - q) < len ? pol[i*l + 4 * m - q] : 0;
					p5q = (i*l + 5 * m + q) < len ? pol[i*l + 5 * m + q] : 0;
					p5_q = (i*l + 5 * m - q) < len ? pol[i*l + 5 * m - q] : 0;
					p6q = (i*l + 6 * m + q) < len ? pol[i*l + 6 * m + q] : 0;
					p6_q = (i*l + 6 * m - q) < len ? pol[i*l + 6 * m - q] : 0;
					p7q = (i*l + 7 * m + q) < len ? pol[i*l + 7 * m + q] : 0;
					p7_q = (i*l + 7 * m - q) < len ? pol[i*l + 7 * m - q] : 0;

					for (int a2 = 0; a2 < 1; a2++) {
						if ((i*l + 0 * m + q) < len) {
							y[i*l + 0 * m + q] = (((p0q - p2_q - p2q + p4_q + p4q - p6_q - p6q) % 7) + 7) % 7;
							add_fk += 6;
							mul_fk += 0;
						}
						if (num_oper == 1) break;

						if ((i*l + 1 * m + q) < len) {
							y[i*l + 1 * m + q] = (((p1q - p3_q - 2 * p3q + 2 * p5_q - 4 * p5q + 4 * p7_q) % 7) + 7) % 7;
							add_fk += 5;
							mul_fk += 4;
						}
						if (num_oper == 2) break;

						if ((i*l + 2 * m + q) < len) {
							y[i*l + 2 * m + q] = (((p2q - p4_q + 4 * p4q - 4 * p6_q - p6q) % 7) + 7) % 7;
							add_fk += 4;
							mul_fk += 2;
						}
						if (num_oper == 3) break;

						if ((i*l + 3 * m + q) < len) {
							y[i*l + 3 * m + q] = (((p3q - p5_q - 4 * p5q + 4 * p7_q) % 7) + 7) % 7;
							add_fk += 3;
							mul_fk += 2;
						}
						if (num_oper == 4) break;

						if ((i*l + 4 * m + q) < len) {
							y[i*l + 4 * m + q] = (((p4q - p6_q + 2 * p6q) % 7) + 7) % 7;
							add_fk += 2;
							mul_fk += 1;
						}
						if (num_oper == 5) break;

						if ((i*l + 5 * m + q) < len) {
							y[i*l + 5 * m + q] = (((p5q - p7_q) % 7) + 7) % 7;
							add_fk += 1;
							mul_fk += 0;
						}
						if (num_oper == 6) break;

						if ((i*l + 6 * m + q) < len) {
							y[i*l + 6 * m + q] = p6q;
						}
						if (num_oper == 7) break;
					}
				}
			}
			memcpy(pol, y, sizeof(aal_uint16) * len);
		}

		for (int j = 0; j < seven_groups_count; j++) {
			v[j * 7 + 0] = (((y[j * 7 + 0] - 2 * y[j * 7 + 2] + 2 * y[j * 7 + 4] - 2 * y[j * 7 + 6]) % 7) + 7) % 7;
			v[j * 7 + 1] = (((y[j * 7 + 1] + 4 * y[j * 7 + 3] - 2 * y[j * 7 + 5]) % 7) + 7) % 7;
			v[j * 7 + 2] = (((y[j * 7 + 2] - 4 * y[j * 7 + 4] + 2 * y[j * 7 + 6]) % 7) + 7) % 7;
			v[j * 7 + 3] = (y[j * 7 + 3] + 2 * y[j * 7 + 5]) % 7;
			v[j * 7 + 4] = (y[j * 7 + 4] + y[j * 7 + 6]) % 7;
			v[j * 7 + 5] = y[j * 7 + 5];
			v[j * 7 + 6] = y[j * 7 + 6];
			add_f0 += 9;
			mul_f0 += 8;
		}


		(*this) = PolynomGF7N(v, len);

		delete[] y;
		delete[] v;

		TrimZero();

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::ReducedToRedundant(const PolynomGF7N & a_pol, int a_n) {
		PolynomGF7N pol(a_n);
		aal_uint16* polPtr = pol.GetCoeffsPtr();

		PolynomGF7N tmpPol(2 * pol.GetDeg() - 2);
		aal_uint16* tmpPolPtr = tmpPol.GetCoeffsPtr();
		// Копирование коэффициентов из входного полинома в увеличенный полином
		memcpy(tmpPolPtr, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		for (int i = 0; i < 3; i++) {
			polPtr[i] = tmpPolPtr[i];
		}

		for (int i = 3; i <= a_n; i++) {
			polPtr[i] = (tmpPolPtr[i] + tmpPolPtr[2 * a_n - i + 1]) % 7;
		}

		pol.TrimZero();
		//pol.UnPackToParPack();
		(*this) = pol;

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::RedundantToReduced(const PolynomGF7N & a_pol, int a_n) {

		PolynomGF7N param(a_n);
		aal_uint16* paramPtr = param.GetCoeffsPtr();
		// Копирование коэффициентов из входного полинома в увеличенный полином
		memcpy(paramPtr, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));
		int deg_param = param.GetDeg();

		PolynomGF7N pol(a_n);
		aal_uint16* polPtr = pol.GetCoeffsPtr();

		polPtr[0] = (paramPtr[0] + 3 * paramPtr[deg_param]) % 7;

		for (int i = 1; i < deg_param; i++) {
			polPtr[i] = (paramPtr[i] + 6 * paramPtr[deg_param]) % 7;
		}

		pol.TrimZero();
		//pol.UnPackToParPack();

		(*this) = pol;

		return (*this);

	}

	PolynomGF7N & PolynomGF7N::ReducedToPermuted(const PolynomGF7N & a_pol, int a_n) {

		PolynomGF7N tmpPol(a_n - 1);
		aal_uint16* tmpPolPtr = tmpPol.GetCoeffsPtr();

		PolynomGF7N redPol(a_n - 1);
		aal_uint16* redPtr = redPol.GetCoeffsPtr();
		// Копирование коэффициентов из входного полинома в увеличенный полином
		memcpy(redPtr, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		for (int i = 0; i < tmpPol.GetDeg(); i++) {
			tmpPolPtr[i] = (redPtr[i + 1] + 5 * redPtr[0]) % 7;
		}

		tmpPolPtr[a_n - 1] = (5 * redPtr[0]) % 7;

		tmpPol.TrimZero();
		//tmpPol.UnPackToParPack();

		(*this) = tmpPol;

		return (*this);
	}

	PolynomGF7N & PolynomGF7N::PermutedToReduced(const PolynomGF7N & a_pol, int a_n) {

		PolynomGF7N tmpPol(a_n - 1);
		aal_uint16* tmpPolPtr = tmpPol.GetCoeffsPtr();

		PolynomGF7N permPol(a_n - 1);
		aal_uint16* permPtr = permPol.GetCoeffsPtr();
		// Копирование коэффициентов из входного полинома в увеличенный полином
		memcpy(permPtr, a_pol.GetCoeffsPtr(), sizeof(aal_uint16)*(a_pol.GetDeg() + 1));

		tmpPolPtr[0] = (3 * permPtr[a_n - 1]) % 7;

		for (int i = 0; i < a_n - 1; i++) {
			tmpPolPtr[i + 1] = (permPtr[i] + 6 * permPtr[a_n - 1]) % 7;
		}

		tmpPol.TrimZero();
		//tmpPol.UnPackToParPack();

		(*this) = tmpPol;

		return (*this);
	}

	aal_uint32 PolynomGF7N::PowGFp(aal_uint32 a_elem, int a_deg, int a_p) const{

		aal_uint32 res = 1;
		if (a_deg == 0) {
			return res;
		}
		else if (a_deg == 1) {
			return a_elem;
		}

		// количество элементов в массиве разложения по осн. 2
		int len = DegDecompLength(a_deg, 2);
		// массив разложения степени
		aal_uint32 *deg_fact = new aal_uint32[len];
		// заполнение массива разложения степени по осн. 2
		// коэффициентами при степенях 2
		DegDecomp(deg_fact, a_deg, 2);

		for (int i = 1; i <= len; i++) {
			res = (res * res) % a_p;
			if (deg_fact[len - i] != 0) {
				res = (res * a_elem) % a_p;
			}
		}

		if (deg_fact != NULL) {
			delete[] deg_fact;
		}

		return res;
	}

	int PolynomGF7N::GNB_Test(const int a_n) const{
		int p = 2 * a_n + 1;
		int p1 = a_n + 1;

		if (!(PrimeNumbersSet.find(p) != PrimeNumbersSet.end()) && !(PrimeNumbersSet.find(p1) != PrimeNumbersSet.end())) {
			return 0;
		}

		int q = PowGFp(7, (2 * a_n), p);
		bool flag_onb1 = false;
		bool flag_onb2 = true;
		bool flag_onb3 = false;

		int val, deg;
		if (PrimeNumbersSet.find(p1) != PrimeNumbersSet.end() && p1 > 7) {
			// Проверка, является ли 7 образующим в GF(p1)
			std::vector<DecompositionMemberN> factOrd_p1;
			Factorization(factOrd_p1, (p1 - 1), true);
			for (int i = 0; i < factOrd_p1.size(); i++) {
				deg = (p1 - 1) / factOrd_p1[i].value;
				val = PowGFp(7, deg, p1);

				if (val != 1) {
					flag_onb1 = true;
				}
				else {
					flag_onb1 = false;
					break;
				}
			}
		}

		if ((q - 1 == 0) && PrimeNumbersSet.find(p) != PrimeNumbersSet.end() && p > 7) {
			// Проверка, является ли 7 образующим в GF(p)
			std::vector<DecompositionMemberN> factOrd_p;
			Factorization(factOrd_p, (p - 1), true);
			for (int i = 0; i < factOrd_p.size(); i++) {
				deg = (p - 1) / factOrd_p[i].value;
				val = PowGFp(7, deg, p);

				if (val == 1 && factOrd_p[i].value != 2) {
					flag_onb2 = false;
					break;
				}
			}

			if (flag_onb2 && PowGFp(7, (p - 1) / 2, p) == 1) {
				flag_onb2 = false;
				flag_onb3 = true;
			}
		}
		else {
			flag_onb2 = false;
		}

		if (flag_onb1 && flag_onb2) {
			return 3;
		}
		else if (flag_onb1 && flag_onb3) {
			return 3;
		}
		else if (flag_onb1 && !flag_onb2 && !flag_onb3) {
			return 1;
		}
		else if (!flag_onb1 && flag_onb2 && !flag_onb3) {
			return 2;
		}
		else if (!flag_onb1 && !flag_onb2 && flag_onb3) {
			return 2;
		}

		return 0;
	}

};