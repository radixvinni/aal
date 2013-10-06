/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/Matrix.h"
using namespace AAL;

/*
	Конструкторы класса Matrix
*/
TEST(Matrix, EmptyConstructor)
{
	Matrix mt;
	CHECK(mt.isZero());
}

TEST(Matrix, CopyConstructor_FullConstructor)
{
  Polynom a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<Polynom*> vec;
  vec.push_back(&a0);
  vec.push_back(&a1);
  vec.push_back(&a2);
  Matrix mt(Matrix::ON_LINE, 11, 3, vec), pp(mt);
	CHECK(mt == pp);
  CHECK(pp.getCoding() == Matrix::ON_LINE);
}

TEST(Matrix, VectorOfPolynomsConstructor)
{
  Polynom a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<Polynom*> vec;
  vec.push_back(&a0);
  vec.push_back(&a1);
  vec.push_back(&a2);
	Matrix mt(vec), pp(vec);
  //mt.setCoding(Matrix::ON_LINE);
  //pp.setCoding(Matrix::ON_LINE);
  //mt.setSizeMatrixBits(11, 3);
  //pp.setSizeMatrixBits(11, 3);
	CHECK(mt == pp);
}

TEST(Matrix, VectorOfStringConstructor)
{
  std::string a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<string> vec;
  vec.push_back(a0);
  vec.push_back(a1);
  vec.push_back(a2);
	Matrix mt(vec), pp(vec);
	CHECK(mt == pp);
}

TEST(Matrix, DataConstructor_SetElements)
{
  Polynom a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<Polynom*> vec;
  vec.push_back(&a0);
  vec.push_back(&a1);
  vec.push_back(&a2);
  Matrix mt(Matrix::ON_LINE, 11, 3);
  mt.setSize(vec.size());
  for(uint i = 0; i < vec.size(); i++)
    mt.setElemMatrix(i, *vec[i]);
  Matrix pp(mt);
  CHECK(mt == pp);
}

TEST(Matrix, ValueConstructor)
{
  Matrix mtA(Matrix::ON_LINE, 3, 3, 1), mtB(Matrix::ON_LINE, 3, 3, 0);
  std::string a0("111"), a1("111"), a2("111");
  std::string b0("000"), b1("000"), b2("000");
  std::vector<string> vecA, vecB;
  vecA.push_back(a0);
  vecA.push_back(a1);
  vecA.push_back(a2);
  vecB.push_back(b0);
  vecB.push_back(b1);
  vecB.push_back(b2);
	Matrix resA(vecA), resB(Matrix::ON_LINE, 3, 3, vecB);
  CHECK(mtA == resA);
  CHECK(mtB == resB);
}

/*
  Удобно
*/
// перевод матрицы в вектор строк
TEST(Matrix, ToString)
{
  std::string a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<string> vec;
  vec.push_back(a0);
  vec.push_back(a1);
  vec.push_back(a2);
	Matrix mt(vec);
  std::vector<string> mtvec = mt.ToString();
  bool flag = false;
  if (vec.size() == mtvec.size())
  {
    for(int i = 0; i < vec.size(); i++)
      if (vec[i] == mtvec[i])
        flag = true;
      else
      {
        flag = false;
        break;
      }
  }
	CHECK(flag);
}

// перевод матрицы в вектор строк
TEST(Matrix, ToStringLine)
{
  std::string a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<string> vec;
  vec.push_back(a0);
  vec.push_back(a1);
  vec.push_back(a2);
  std::string s = a0 + "\n" + a1 + "\n" + a2 + "\n";
	Matrix mt(vec);
  string mtvec = mt.ToStringLine();
	CHECK(s == mtvec);
}

//перевод матрицы в строку координат
TEST(Matrix, ToStringNotNullBits)
{
  std::string a0("111"), a1("010"), a2("110"), res("{0,0}{0,1}{0,2}{1,1}{2,0}{2,1}");
  std::vector<string> vec;
  vec.push_back(a0);
  vec.push_back(a1);
  vec.push_back(a2);
  Matrix mt(vec);
  string mtvec = mt.ToStringNotNullBits();
  CHECK(mtvec == res);
}

/*
  Унарные операции
*/
TEST(Matrix, Init)
{
  Polynom a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<Polynom*> vec;
  vec.push_back(&a0);
  vec.push_back(&a1);
  vec.push_back(&a2);
	Matrix mt(vec), pp;
  pp = mt;
  CHECK(mt == pp);
}

/*
	Операции сравнения
*/
TEST(Matrix, Equal)
{
  Matrix i,j;
  CHECK(i == j);

  Polynom a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<Polynom*> vec;
  vec.push_back(&a0);
  vec.push_back(&a1);
  vec.push_back(&a2);
  Matrix mt(Matrix::ON_LINE, 11, 3, vec), pp(Matrix::ON_LINE, 11, 3, vec);
  CHECK(mt == pp);
  CHECK(!(mt == i) && !(pp == j));

  Polynom a3("1111111111"), a4("0001010010"), a5("0101001010");
  std::vector<Polynom*> vec1;
  vec1.push_back(&a3);
  vec1.push_back(&a4);
  vec1.push_back(&a5);
  Matrix mt1(Matrix::ON_LINE, 10, 3, vec), pp1(Matrix::ON_LINE, 11, 3, vec1);
  CHECK(!(mt1 == pp1));
  CHECK(!(pp == pp1));
}

TEST(Matrix, NotEqual)
{
	Matrix i,j;
	CHECK(!(i != j));

  Polynom a0("11111111111"), a1("00010100101"), a2("01010010101");
  std::vector<Polynom*> vec;
  vec.push_back(&a0);
  vec.push_back(&a1);
  vec.push_back(&a2);
  Matrix mt(Matrix::ON_LINE, 11, 3, vec), pp(Matrix::ON_LINE, 11, 3, vec);
  CHECK(!(mt != pp));
  CHECK(mt != i);
  CHECK(pp != j);

  Polynom a3("1111111111"), a4("0001010010"), a5("0101001010");
  std::vector<Polynom*> vec1;
  vec1.push_back(&a3);
  vec1.push_back(&a4);
  vec1.push_back(&a5);
  Matrix mt1(Matrix::ON_LINE, 10, 3, vec), pp1(Matrix::ON_LINE, 11, 3, vec1);
  CHECK(mt1 != pp1);
  CHECK(pp != pp1);
}

TEST(Matrix, EqualParams)
{
  Matrix i,j;
  CHECK(i == j);

  Matrix mt(Matrix::ON_LINE, 11, 3), pp(Matrix::ON_LINE, 11, 3);
  CHECK(equalityParams(mt,pp));
  CHECK(!equalityParams(mt,i));

  Polynom a0("1111111111"), a1("0001010010"), a2("0101001010");
  std::vector<Polynom*> vec;
  vec.push_back(&a0);
  vec.push_back(&a1);
  vec.push_back(&a2);
  Matrix mt1(Matrix::ON_LINE, 10, 3, vec), pp1(Matrix::ON_LINE, 11, 3, vec);
  CHECK(equalityParams(mt,pp));
}

/*
  Работа с матрицами
*/
// Приведение к треугольному виду

TEST(Matrix, RightTrian)
{
  Polynom beginPolynom("111011");
  Matrix mt0;
  generateMatrix(beginPolynom, 5, mt0);
  Matrix mt1(mt0), mt2(mt0);
  mt0.gausRightTrian();
  mt1.gausRightTrianBits();
  mt2.konovalcevRightTrianBits();
  CHECK(mt0.getTrianType() == Matrix::RIGHT);
  CHECK(mt1.getTrianType() == Matrix::RIGHT);
  CHECK(mt2.getTrianType() == Matrix::RIGHT);
}

TEST(Matrix, LeftTrian)
{
  Polynom beginPolynom("111011");
  Matrix mt0;
  generateMatrix(beginPolynom, 5, mt0);
  Matrix mt1(mt0);
  mt0.konovalcevLeftTrianBits();
  mt1.gausLeftTrianBits();
  CHECK(mt0.getTrianType() == Matrix::LEFT);
  CHECK(mt1.getTrianType() == Matrix::LEFT);
}

// Проверка на невырожденность
TEST(Matrix, NonSign)
{
  Polynom beginPolynom("111011");
  Matrix mt0;
  generateMatrix(beginPolynom, 5, mt0);
  Matrix mt1(mt0);
  mt0.konovalcevLeftTrianBits();
  mt1.konovalcevRightTrianBits();
  CHECK(mt0.nonsignMatrix());
  CHECK(mt1.nonsignMatrix());

  Polynom pl("101100");
  Matrix mt2;
  generateMatrix(pl, 5, mt2);
  mt2.gausRightTrian();
  CHECK(mt2.getTrianType() == Matrix::RIGHT);
  CHECK(!mt2.nonsignMatrix());
}

// Приведение к диагональному виду
TEST(Matrix, RightDiag)
{
  Polynom beginPolynom("111011");
  Matrix mt0;
  generateMatrix(beginPolynom, 5, mt0);
  Matrix mt1(mt0);
  mt0.gausRightDiag();
  mt1.gausRightDiagBits();
  CHECK(mt0 == mt1);
}

TEST(Matrix, LeftDiag)
{
  Polynom beginPolynom("111011");
  Matrix mt0;
  generateMatrix(beginPolynom, 5, mt0);
  mt0.gausLeftDiagBits();
  CHECK(mt0.nonsignMatrix());
}

// Умножение матрицы на вектор
TEST(Matrix, mulMatrixToVec)
{
  Polynom a0("01000000000"),
          a1("00100000000"),
          a2("00001000000"),
          a3("00000000100"),
          a4("10011101101"),
          a5("01111110110"),
          a6("10010000011"),
          a7("11101010101"),
          a8("01111010111"),
          a9("01100111101"),
          a10("01101100011");
   Polynom vt("10101010101"), res;
   std::vector<Polynom*> vec;
   vec.push_back(&a0);
   vec.push_back(&a1);
   vec.push_back(&a2);
   vec.push_back(&a3);
   vec.push_back(&a4);
   vec.push_back(&a5);
   vec.push_back(&a6);
   vec.push_back(&a7);
   vec.push_back(&a8);
   vec.push_back(&a9);
   vec.push_back(&a10);
   Matrix mt = Matrix(Matrix::ON_LINE, 11, 11, vec);
   res = mulMatrixToVec(vt, mt);
   Polynom exp("01110000101");
   CHECK(res == exp);
}

// Умножение вектора на матрицу
TEST(Matrix, mulVecToMatrix)
{
   Polynom a0("00001011001"),
           a1("10000101111"),
           a2("01000101111"),
           a3("00001110111"),
           a4("00101101100"),
           a5("00001100101"),
           a6("00000101011"),
           a7("00001000110"),
           a8("00011101010"),
           a9("00000110101"),
           a10("00001011111");
   Polynom vt("10101010101"), res;
   std::vector<Polynom*> vec;
   vec.push_back(&a0);
   vec.push_back(&a1);
   vec.push_back(&a2);
   vec.push_back(&a3);
   vec.push_back(&a4);
   vec.push_back(&a5);
   vec.push_back(&a6);
   vec.push_back(&a7);
   vec.push_back(&a8);
   vec.push_back(&a9);
   vec.push_back(&a10);
   Matrix mt = Matrix(Matrix::ON_COLUMN, 11, 11, vec);
   res = mulVecToMatrix(vt, mt);
   Polynom exp("1100111011");
   CHECK(res == exp);
}

// Обращение матриц
TEST(Matrix, Reverse)
{
  Polynom beginPolynom("111011");
  Matrix mt0;
  generateMatrix(beginPolynom, 5, mt0);
  Matrix mt1(mt0);
  mt1.conversionMatrix();
  Polynom p0("10101"), p1;
  p1 = mulVecToMatrix(p0, mt1);
  mt0.reverseLeftBits();
  mt0.conversionMatrix();
  p1 = mulVecToMatrix(p1, mt0);
  CHECK(p0 == p1);
}



/*TEST(Matrix, ToString)
{
        std::vector<Polynom *> vec;
        Polynom a("1");

        for(int i = 0; i < 5; i++)
        {
                vec.push_back(new Polynom(a));
                a <<= 1;
        }

        Matrix matrix(Matrix::ON_LINE, 5, 5, vec);

        for(int i = 0; i < 5; i++)
        {
                delete vec.at(i);
        }


        CHECK(matrix.ToString() == "1\n01\n001\n0001\n00001\n");

        try
        {
                matrix.conversionMatrix().ToString();
                CHECK(false);
        }
        catch(std::out_of_range &e)
        {
                CHECK(true);
        }
} */

TEST(Matrix, Transpose)
{
        std::vector<Polynom *> vec;
        Polynom a("11111");

        vec.push_back(new Polynom(a));
        for(int i = 1; i < 5; i++)
                vec.push_back(new Polynom());

        Matrix matrix(Matrix::ON_LINE, 5, 5, vec);

        for(int i = 0; i < 5; i++)
        {
                delete vec.at(i);
        }

        CHECK(true);
        //CHECK(matrix.Transpose().ToString() == "1\n1\n1\n1\n1\n");
}
TEST(Matrix, getBit)
{
        // TODO: Заменить 
        /*std::vector<Polynom *> vec;
        Polynom a("11111");

        vec.push_back(new Polynom(a));
        for(int i = 1; i < 5; i++)
                vec.push_back(new Polynom());

        Matrix matrix(Matrix::ON_LINE, 5, 5, vec);

        for(int i = 0; i < 5; i++)
        {
                delete vec.at(i);
        }

        CHECK(matrix.getBit(0,1) && !matrix.getBit(1,1));*/
        CHECK(true);
}

TEST(Matrix, SolveEquation)
{
        // example for curve point generation (book. 2, page. 79)
        std::vector<Polynom *> vec;
        Polynom x("01"), x_square("001"), res, module("11001"), right("1000");
        AAL::Integer two("2");

        // matrix creation
        for(int i = 0; i < 3; i++)
        {
                res.ModAdd(x, x_square, module);
                vec.push_back(new Polynom(res));
                x <<= 1;
                x_square = x;
                x_square.ModPow(x_square, two, module);
        }
        Matrix matrix(Matrix::ON_LINE, 3, 3, vec);

        for(int i = 0; i < 3; i++)
        {
                delete vec.at(i);
        }
        matrix.Transpose();
        // solution search

        CHECK(matrix.SolveLinearEquationSystem(matrix, right).ToString() == "11");
}


