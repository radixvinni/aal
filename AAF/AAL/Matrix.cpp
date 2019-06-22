/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------
#include <stdlib.h>


#include "Matrix.h"

//---------------------------------------------------------------------------
namespace AAL
{
//***************************************************************************

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // определение степени числа
  uint degree(uint x)
  {
    uint r = 0;
    while (x != 1)
    {
      x >>= 1;
      r++;
    }
    return r;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // перевод числа в строку
  string Matrix::i_to_str(uint x) const
  {
    string str = "";
    char s[11];
    ltoa(x, s, 10);
    str += s;
    return str;
  }

  //------------------------- конструкторы/деструкторы ----------------------
  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  Matrix::Matrix()
        : IsTrian(NONE),
          IsNonSign(true),
          CodeWord(ON_LINE),
          ColCount(0),
          RowCount(0)
  {
    plMatrix.resize(0);
  }

  //(c) Chernysheva, TEST(Matrix, CopyConstructor_FullConstructor)
  //------->>>>>>>>>-----------------
  // конструктор копирования
  Matrix::Matrix(const Matrix& matrix)
  {
    CodeWord = matrix.getCoding();
    matrix.getSizeMatrixBits(ColCount, RowCount);
    IsTrian = matrix.getTrianType();
    IsNonSign = matrix.getIsNonSign();
    uint size = matrix.getSize();
    plMatrix.resize(size);
    for (uint i = 0; i < size; i ++)
      plMatrix[i] = new Polynom(*matrix.plMatrix[i]);
  }

  //(c) Chernysheva, TEST(Matrix, DataConstructor_SetElements)
  //------->>>>>>>>>-----------------
  Matrix::Matrix(CodingSystem aCodeWord, uint aColCount, uint aRowCount)
        : IsTrian(NONE),
          IsNonSign(true)
  {
    CodeWord = aCodeWord;
    ColCount = aColCount;
    RowCount = aRowCount;
    plMatrix.resize(0);
  }

  //(c) Chernysheva, TEST(Matrix, ValueConstructor)
  //------->>>>>>>>>-----------------
  Matrix::Matrix(CodingSystem aCodeWord, uint aColCount, uint aRowCount, bool aValue)
        : IsTrian(NONE),
          IsNonSign(true)
  {
    CodeWord = aCodeWord;
    ColCount = aColCount;
    RowCount = aRowCount;
    switch(CodeWord)
    {
      case ON_LINE:
        plMatrix.resize(ColCount);
        for (int i = 0; i < ColCount; i++)
        {
          plMatrix[i] = new Polynom();
          if (aValue)
            plMatrix[i]->setUnit(RowCount - 1);
          else
            plMatrix[i]->setZero();
        }
        break;
      case ON_COLUMN:
        plMatrix.resize(RowCount);
        for (int j = 0; j < RowCount; j++)
        {
          plMatrix[j] = new Polynom();
          if (aValue)
            plMatrix[j]->setUnit(ColCount - 1);
          else
            plMatrix[j]->setZero();  
        }
        break;
    }
  }

  //(c) Chernysheva, TEST(Matrix, CopyConstructor_FullConstructor)
  //------->>>>>>>>>-----------------
  Matrix::Matrix(CodingSystem aCodeWord, uint aColCount, uint aRowCount, vector<Polynom*> aNewMatrix)
        : IsTrian(NONE),
          IsNonSign(true)
  {
    uint size = aNewMatrix.size();
    CodeWord = aCodeWord;
    ColCount = aColCount;
    RowCount = aRowCount;
    plMatrix.resize(size);
    for (uint i = 0; i < size; i ++)
      plMatrix[i] = new Polynom(*aNewMatrix[i]);
  }

  //(c) Chernysheva
  Matrix::Matrix(CodingSystem aCodeWord, uint aColCount, uint aRowCount, vector<string> aNewMatrix)
        : IsTrian(NONE),
          IsNonSign(true)
  {
    uint size = aNewMatrix.size();
    CodeWord = aCodeWord;
    ColCount = aColCount;
    RowCount = aRowCount;
    plMatrix.resize(size);
    for (uint i = 0; i < size; i ++)
      plMatrix[i] = new Polynom(aNewMatrix[i]);
  }

  //(c) Chernysheva, TEST(Matrix, VectorOfPolynomsConstructor)
  //------->>>>>>>>>-----------------
  // конструктор записывает вектор полиномов
  // размеры матрицы определяются во время записи, упаковка по строкам
  Matrix::Matrix(vector<Polynom*> aNewMatrix)
        : IsTrian(NONE),
          IsNonSign(true),
          CodeWord(ON_LINE)
  {
    uint size = aNewMatrix.size();
    plMatrix.resize(size);
    uint max = 0;
    for (uint i = 0; i < size; i ++)
    {
      plMatrix[i] = new Polynom(*aNewMatrix[i]);
      if (max < plMatrix[i]->getNumberBits())
        max = plMatrix[i]->getNumberBits();
    }
    ColCount = max;
    RowCount = size;
  }

  //(c) Chernysheva, TEST(Matrix, VectorOfStringConstructor)
  //------->>>>>>>>>-----------------
  // конструктор записывает вектор полиномов, полученный из вектора строк
  // размеры матрицы определяются во время записи, упаковка по строкам
  Matrix::Matrix(vector<string> aNewMatrix)
        : IsTrian(NONE),
          IsNonSign(true),
          CodeWord(ON_LINE)
  {
    uint size = aNewMatrix.size();
    plMatrix.resize(size);
    uint max = 0;
    for (uint i = 0; i < size; i ++)
    {
      Polynom p(aNewMatrix[i]);
      plMatrix[i] = new Polynom(p);
      if (max < plMatrix[i]->getNumberBits())
        max = plMatrix[i]->getNumberBits();
    }
    ColCount = max;
    RowCount = size;
  }
  //-----------------------------------------------------------------------------
  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  Matrix::~Matrix()
  {
    for (int i = 0; i < plMatrix.size(); i++)
      delete plMatrix[i];
  }

  //------------------------- accessors/mutators ----------------------------
  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  void Matrix::setSize(uint aSize)
  {
    if (plMatrix.empty())
      plMatrix.resize(aSize);
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  uint Matrix::getSize() const
  {
    return plMatrix.size();
  }
  
  //(c) Chernysheva, TEST(Matrix, DataConstructor_SetElements)
  //------->>>>>>>>>-----------------
  void Matrix::setElemMatrix(uint i, Polynom& newElem)
  {
    if (i < plMatrix.size())
    {
      if (!plMatrix[i])
        plMatrix[i] = new Polynom;
      if (newElem != *plMatrix[i])
        *plMatrix[i] = newElem;
    }
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  Polynom& Matrix::getElemMatrix(int i) const
  {
    if (i < (int)plMatrix.size())
    {
      if (plMatrix[i])
        return *plMatrix[i];
    }
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  void Matrix::setCoding(CodingSystem aCodeWord)
  {
    CodeWord = aCodeWord;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  Matrix::CodingSystem Matrix::getCoding() const
  {
    return CodeWord;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  void Matrix::setTrianType(TrianType aIsTrian)
  {
    IsTrian = aIsTrian;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  Matrix::TrianType Matrix::getTrianType() const
  {
    return IsTrian;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  void Matrix::setIsNonSign(bool bIsNonSign)
  {
    IsNonSign = bIsNonSign;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  bool Matrix::getIsNonSign() const
  {
    return IsNonSign;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  void Matrix::setSizeMatrixBits(uint nCol, uint nRowCount)
  {
    ColCount = nCol;
    RowCount = nRowCount;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  void Matrix::getSizeMatrixBits(uint &nColCount, uint &nRowCount) const
  {
    nColCount = ColCount;
    nRowCount = RowCount;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  uint Matrix::getColCount() const
  {
    return ColCount;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  uint Matrix::getRowCount() const
  {
    return RowCount;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  uint Matrix::getSizeWordInBits() const
  {
    return Len_Word;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  bool Matrix::getBit(uint nRowPosition, uint nColPosition) const
  {
    return plMatrix[nRowPosition]->getBit(nColPosition);
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  void Matrix::setBit(uint nRowPosition, uint nColPosition, bool bValue)
  {
    plMatrix[nRowPosition]->setBit(nColPosition, bValue);
  }

  // -------------------- служебные функции ---------------------------------
  //(c) Chernysheva, TEST(Matrix, ToString)
  //------->>>>>>>>>-----------------
  //перевод матрицы в строку, возвращает вектор из строк
  vector<string> Matrix::ToString()
  {
    vector<string> res;
    switch (CodeWord)
    {
      case ON_LINE:
        for (int i = 0; i < (int)plMatrix.size(); i++)
        {
          string s = plMatrix[i]->ToString(AAL::BackBin);
          res.push_back(s);
        }
        break;
      case ON_COLUMN:
        Matrix buf(*this);
        buf.conversionMatrix();
        for (int i = 0; i < buf.getSize(); i++)
        {
          string s = buf.getElemMatrix(i).ToString(AAL::BackBin);
          res.push_back(s);
        }
        break;
    }
    return res;
  }

  //(c) Chernysheva, TEST(Matrix, ToStringNotNullBits)
  //------->>>>>>>>>-----------------
  //перевод матрицы в строку,
  //возвращает строку c номерами строк и столбцов с ненулевыми значениям
  //в формате {строка, столбец}
  string Matrix::ToStringNotNullBits()
  {
    string res = "";
    switch (CodeWord)
    {
      case ON_LINE:
        for (int i = 0; i < RowCount; i++)
        {
          for (int j = 0; j < ColCount; j++)
          {
            bool val = this->getBit(i, j);
            if (val)
              res += "{" + i_to_str(i) + "," + i_to_str(j) + "}";
          }
        }
        break;
      case ON_COLUMN:
        Matrix buf(*this);
        buf.conversionMatrix();
        for (int i = 0; i < buf.getRowCount(); i++)
        {
          for (int j = 0; j < buf.getColCount(); j++)
          {
            bool val = buf.getBit(i, j);
            if (val)
              res += "{" + i_to_str(i) + "," + i_to_str(j) + "}";
          }
        }
        break;
    }
    return res;
  }

  //(c) Chernysheva, TEST(Matrix, ToStringLine)
  //------->>>>>>>>>-----------------
  //перевод матрицы в строку, возвращает строку, разделитель \n
  string Matrix::ToStringLine()
  {
    string res = "";
    switch (CodeWord)
    {
      case ON_LINE:
        for (int i = 0; i < plMatrix.size(); i++)
        {
          string s = plMatrix[i]->ToString(AAL::BackBin);
          res += s + "\n";
        }
        break;
      case ON_COLUMN:
        Matrix buf(*this);
        buf.conversionMatrix();
        for (int i = 0; i < buf.getSize(); i++)
        {
          string s = buf.getElemMatrix(i).ToString(AAL::BackBin);
          res += s + "\n";
        }
        break;
    }
    return res;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // пуста ли матрица
  bool Matrix::isZero() const
  {
    if (plMatrix.empty())
      return true;
    else
      return false;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  uint Matrix::getColCountMatrixByte() const
  {
    if (CodeWord == ON_LINE)
    {
      uint ost = ColCount%8;
      if (ost != 0)
        return ColCount/8 +1;
      else
        return ColCount/8;
    }
    else
      return 0;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  uint Matrix::getRowCountMatrixByte() const
  {
    if (CodeWord == ON_COLUMN)
    {
      uint ost = RowCount%8;
      if (ost != 0)
        return RowCount/8 + 1;
      else
        return RowCount/8;
    }
    else
      return 0;
  }

  // -------------------- унарные операции ---------------------------------
  //(c) Chernysheva, TEST(Matrix, Init)
  //------->>>>>>>>>-----------------
  Matrix& Matrix::operator= (const Matrix& matrix)
  {
    if (this != &matrix)
    {
      this->setCoding(matrix.getCoding());
      uint unCol, unRowCount;
      matrix.getSizeMatrixBits(unCol, unRowCount);
      this->setSizeMatrixBits(unCol, unRowCount);
      this->setTrianType(matrix.getTrianType());
      this->setIsNonSign(matrix.getIsNonSign());
      uint size = matrix.getSize();
      this->setSize(size);
      for (uint i = 0; i < size; i++)
        this->setElemMatrix(i, matrix.getElemMatrix(i));
    }
    return *this;
  }

  // -------------------- операции сравнения ---------------------------------
  //(c) Chernysheva, TEST(Matrix, Equal)
  //------->>>>>>>>>-----------------
  bool operator==(const Matrix& a, const Matrix& b)
	{
		if ((a.isZero() && b.isZero()))
			return true;
    else
    {
      if (a.CodeWord == b.CodeWord && a.IsTrian == b.IsTrian &&
          a.IsNonSign == b.IsNonSign && a.ColCount == b.ColCount && a.RowCount == b.RowCount)
      {
        uint i = 0, sizeA = a.getSize(), sizeB = b.getSize();
        if (sizeA == sizeB)
        {
          bool isEqual = true;
          while (isEqual && i < sizeA)
          {
            if (*a.plMatrix[i] != *b.plMatrix[i])
            {
              isEqual = false;
              break;
            }
            i++;
          }
          if (isEqual)
            return true;
          else
            return false;
        }
      }
      else
        return false;
    }
	}

  //(c) Chernysheva, TEST(Matrix, NotEqual)
  //------->>>>>>>>>-----------------
  bool operator!= (const Matrix& a, const Matrix& b)
  {
    return !(a == b);
  }

  //(c) Chernysheva, TEST(Matrix, EqualParams)
  //------->>>>>>>>>-----------------
  // сравнение матриц на равество параметров
  // внутренне содержание при этом не сравнивается
  bool equalityParams(const Matrix& a, const Matrix& b)
  {
    return (a.CodeWord == b.CodeWord && a.IsTrian == b.IsTrian &&
            a.IsNonSign == b.IsNonSign && a.ColCount == b.ColCount &&
            a.RowCount == b.RowCount && a.getSize() == b.getSize());
  }


  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // генерация матрицы для нормальной системы
  void generateMatrix(const Polynom& plBegin, int nPow, Matrix& A)
  {
    int n = nPow;
    if (A.getSize())
    {
      for (uint i = 0; i < A.getSize(); i++)
        delete A.plMatrix[i];
    }
    A.plMatrix.clear();
    A.setTrianType(Matrix::NONE);
    A.setCoding(Matrix::ON_LINE);
    A.setIsNonSign(true);
    A.ColCount = n;
    A.RowCount = n;
    A.plMatrix.resize(n);
    A.plMatrix[0] = new Polynom;
    A.setBit(0, 1, true);
    for (int i = 1; i < n; i++)
    {
      A.plMatrix[i] = new Polynom((*A.plMatrix[i-1])*(*A.plMatrix[i-1]));
      *A.plMatrix[i] = (*A.plMatrix[i])%plBegin;
    }
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // создание единичной матрицы слева направо
  void Matrix::createUnitaryMatrixLeft(uint aRowCount, uint aColCount, CodingSystem aCodeWord, Matrix& A)
  {
    A.setCoding(aCodeWord);
    A.setSizeMatrixBits(aColCount, aRowCount);
    switch (A.CodeWord)
    {
      case ON_LINE: // ON_LINE
        A.setSize(A.RowCount);
        for (uint i = 0; i < A.RowCount; i++)
        {
          if (A.plMatrix[i] == NULL)
            A.plMatrix[i] = new Polynom;
          A.setBit(i, i, true);
        }
        break;
      case ON_COLUMN: // ON_COLUMN
        A.setSize(A.ColCount);
        for (uint i = 0; i < A.ColCount; i++)
        {
          A.plMatrix[i] = new Polynom;
          A.setBit(i, i, true);
        }
        break;
    }
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // создание единичной матрицы cправа налево
  void Matrix::createUnitaryMatrixRight(uint aRowCount, uint aColCount, CodingSystem aCodeWord, Matrix& A)
  {
    A.setCoding(aCodeWord);
    A.setSizeMatrixBits(aColCount, aRowCount);
    switch (A.getCoding())
    {
      case ON_LINE: // ON_LINE
        A.setSize(aRowCount);
        for (uint i = 0; i < aRowCount  ; i++)
        {
          if (A.plMatrix[i] == NULL)
            A.plMatrix[i] = new Polynom;
          A.setBit(i, aRowCount - i - 1, true);
        }
        break;
      case ON_COLUMN: // ON_COLUMN
        A.setSize(aColCount);
        for (uint i = 0; i < aColCount; i++)
        {
          if (A.plMatrix[i] == NULL)
            A.plMatrix[i] = new Polynom;
          A.setBit(i, aColCount - i - 1, true);
        }
        break;
    }
  }

  //-------------------- алгоритмы работы  с матрицей -----------------------

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // переход из зашифровки по строкам к зашифровке по столбцам и наоборот
  Matrix& Matrix::conversionMatrix()
  {
    Matrix Con;
    switch (this->getCoding())
    {
      case ON_LINE: //ON_LINE
        Con.setSize(this->ColCount);
        for (uint i = 0; i < this->ColCount; i++)
        {
          Con.plMatrix[i] = new Polynom;
          bool bit;
          for (uint j = 0; j < this->RowCount; j++)
          {
            bit = this->getBit(j, i);
            if (bit)
              Con.setBit(i, j, bit);
          } // for j
        } // for i
        this->plMatrix.resize(this->ColCount);
        for (uint i = 0; i < this->ColCount; i++)
          this->setElemMatrix(i, *Con.plMatrix[i]);
        this->setCoding(ON_COLUMN);
        break;
      case ON_COLUMN: //ON_COLUMN
        Con.setSize(this->RowCount);
        for (uint i = 0; i < this->RowCount; i++)
        {
          Con.plMatrix[i] = new Polynom;
          bool bit;
          for (uint j = 0; j < this->ColCount; j++)
          {
            bit = this->getBit(j, i);
            if (bit)
              Con.setBit(i, j, bit);
          } // for j
        } // for i
        this->plMatrix.resize(this->RowCount);
        for (uint i = 0; i < this->RowCount; i++)
          this->setElemMatrix(i, *Con.plMatrix[i]);
        this->setCoding(ON_LINE);
        break;
    }
    return *this;
  }

  //(c) Chernysheva, TEST(Matrix, RightTrian)
  //------->>>>>>>>>-----------------
  // приведение матрицы к треугольному виду алгоритмом Гаусса
  // для упакованных матриц
  // на выходе получаем верхнетреугольную матрицу справа-налево
  Matrix& Matrix::gausRightTrian()
  {
    if ((this->getCoding() == ON_LINE)&&(this->getTrianType() == NONE))
    {
      uint maxDigits = 0, row = this->getRowCount();
      for (uint i = 0; i < row; i++)
        if (maxDigits < this->plMatrix[i]->getNumberDigits())
          maxDigits = this->plMatrix[i]->getNumberDigits();

      uint activeRow = 0;
      int activeCol = maxDigits - 1;
      while ((activeRow < row)&&(activeCol >= 0))
      {
        uint max = 0, j = activeRow, digit;
        for (uint i = activeRow; i < row; i++)
        {
          digit = this->plMatrix[i]->getDigit(activeCol);
          if (max < digit)
          {
            max = digit;
            j = i;
          }
        }
        if (max)
        {
          uint r = degree(max);
          uint ar = 1<<r;
          if (this->plMatrix[activeRow]->getDigit((uint)activeCol) < ar)
            this->plMatrix[activeRow]->Xor(*this->plMatrix[j], *this->plMatrix[activeRow]);
          for (uint i = activeRow + 1; i < row; i++)
          {
            if (this->plMatrix[i]->getDigit((uint)activeCol) >= ar)
              this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
          }
          activeRow++;
        }
        else
          activeCol--;
      }
      this->setTrianType(RIGHT);
    }
    //else
    // должно быть какое-нибудь исключение
    return *this;
  }


  //(c) Chernysheva, TEST(Matrix, LeftTrian)
  //------->>>>>>>>>-----------------
  // приведение матрицы к треугольному виду алгоритмом Гаусса, работаем
  // с самими битами, не прибегая к интерпритации digits как чисел
  // на выходе получаем верхнетреугольную матрицу слева-направо
  Matrix& Matrix::gausLeftTrianBits()
  {
    if ((this->getCoding() == ON_LINE)&&(this->getTrianType() == NONE))
    {
      uint activeRow = 0, activeCol = 0;
      while ((activeRow < this->RowCount)&&(activeCol < this->ColCount))
      {
        bool bitActiveRow = this->getBit(activeRow, activeCol);
        if (bitActiveRow)
        {
          bool bit;
          for (uint i = activeRow + 1; i < this->RowCount; i++)
          {
            bit = this->getBit(i, activeCol);
            if (bit)
              this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
          }
          activeCol++;
          activeRow++;
        }
        else
        {
          bool bit;
          // так как мы уже знаем, что бит, находящийся на пересечении
          // activeRow и activeCol равен 0, то мы можем воспользоваться этим
          uint firstTrueBit = activeRow;
          for (uint i = activeRow + 1; i < this->RowCount; i++)
          {
            bit = this->getBit(i, activeCol);
            if (bit)
            {
              firstTrueBit = i;
              break;
            }
          }
          // не состоит ли весь столбец из нулей
          if (firstTrueBit != activeRow)
            this->plMatrix[activeRow]->Xor(*this->plMatrix[activeRow], *this->plMatrix[firstTrueBit]);
          else
            activeCol++;
        }
      }
      this->setTrianType(LEFT);
    }
    //else
    // должно быть какое-нибудь исключение
    return *this;
  }


  //(c) Chernysheva, TEST(Matrix, RightTrian)
  //------->>>>>>>>>-----------------
  // приведение матрицы к треугольному виду алгоритмом Гаусса, работаем
  // с самими битами, не прибегая к интерпритации digits как чисел
  // на выходе получаем верхнетреугольную матрицу справа-налево
  Matrix& Matrix::gausRightTrianBits()
  {
    if ((this->getCoding() == ON_LINE)&&(this->getTrianType() == NONE))
    {
      uint activeRow = 0;
      int activeCol = this->ColCount - 1;
      while ((activeRow < this->RowCount)&&(activeCol >= 0))
      {
        bool bitActiveRow = this->getBit(activeRow, activeCol);
        if (bitActiveRow)
        {
          bool bit;
          for (uint i = activeRow + 1; i < this->RowCount; i++)
          {
            bit = this->getBit(i, activeCol);
            if (bit)
              this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
          }
          activeCol--;
          activeRow++;
        }
        else
        {
          bool bit;
          // так как мы уже знаем, что бит, находящийся на пересечении
          // activeRow и activeCol равен 0, то мы можем воспользоваться этим
          uint firstTrueBit = activeRow;
          for (uint i = activeRow + 1; i < this->RowCount; i++)
          {
            bit = this->getBit(i, activeCol);
            if (bit)
            {
              firstTrueBit = i;
              break;
            }
          }
          // не состоит ли весь столбец из нулей
          if (firstTrueBit != activeRow)
            this->plMatrix[activeRow]->Xor(*this->plMatrix[activeRow], *this->plMatrix[firstTrueBit]);
          else
            activeCol--;
        }
      }
      this->setTrianType(RIGHT);
    }
    //else
    // должно быть какое-нибудь исключение
    return *this;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // приведение матрицы к треугольному виду алгоритмом Коновальцева,
  // внутри применяется алгоритм Гаусса для "упакованных" матриц
  // на выходе получаем верхнетреугольную матрицу справа-налево
  Matrix& Matrix::konovalcevRightTrian()
  {
    if ((this->getCoding() == ON_LINE)&&(this->getTrianType() == NONE))
    {
      //int r = (log(n)/log(P)) - 3*(log(log(n)/log(P))/log(P));
      int r = abs(r);
    }
    return *this;
  }

  //(c) Chernysheva, TEST(Matrix, LeftTrian)
  //------->>>>>>>>>-----------------
  // приведение матрицы к треугольному виду алгоритмом Коновальцева,
  // внутри применяется бинарный алгоритм Гаусса
  // на выходе получаем верхнетреугольную матрицу слева-направо
  Matrix& Matrix::konovalcevLeftTrianBits()
  {
    if ((this->getCoding() == ON_LINE)&&(this->getTrianType() == NONE))
    {
      //int r = (log(n)/log(P)) - 3*(log(log(n)/log(P))/log(P));
      // длина кортежа
      uint r = 3;

      uint activeRow = 0, activeCol = 0;
      Polynom *cortege = new Polynom, *nul = new Polynom;
      while ((activeRow < this->RowCount)&&(activeCol < this->ColCount))
      {
        uint aRow = activeRow, aCol = activeCol, notNulCortegeRow = 0;
        bool allCortegeNul = false;
        uint NumNotNulCortege = 0;
        // работа с кортежами
        while ((aRow < this->RowCount)&&(!allCortegeNul))
        {
          // ищем первый ненулевой кортеж
          for (uint i = aRow; i < this->RowCount; i++)
          {
            // прохождение по кортежу
            uint rc = 0;
            for (uint ri = aCol; ri < aCol + r; ri++)
            {
              bool bit = this->getBit(i, ri);
              cortege->setBit(rc, bit);
              rc++;
            }
            if (*cortege != *nul)
            {
              notNulCortegeRow = i;
              NumNotNulCortege++;
              break;
            }
          }
          // все кортежи нулевые
          if (*cortege == *nul)
            allCortegeNul = true;
          else
          {
            Polynom *buf = new Polynom, *curCortege = new Polynom;
            // меняем местами активную строку со строкой с ненулевым кортежем
            if (notNulCortegeRow != aRow)
            {
              *buf = *this->plMatrix[notNulCortegeRow];
              *this->plMatrix[notNulCortegeRow] = *this->plMatrix[aRow];
              *this->plMatrix[aRow] = *buf;
            }
            // удаление одинаковых с активным кортежей
            for (uint i = aRow + 1; i < this->RowCount; i++)
            {
              uint rc = 0;
              for (uint ri = aCol; ri < aCol + r; ri++)
              {
                bool bit = this->getBit(i, ri);
                curCortege->setBit(rc, bit);
                rc++;
              }
              uint t = 0;
              for (uint rc = 0;  rc < r; rc++)
              {
                bool y = (cortege->getBit(rc) == curCortege->getBit(rc));
                if (y)
                  t++;
              }
              if (t == r)
                *this->plMatrix[i] = *this->plMatrix[i] - *this->plMatrix[aRow];
            }
            aRow++;
          }
        }

          aRow = activeRow, aCol = activeCol;
          // метод Гаусса для приведения к треугольному виду
          while ((aRow < activeRow + NumNotNulCortege)&&(aCol < this->ColCount))
          {
            bool bitActiveRow = this->getBit(aRow, aCol);
            if (bitActiveRow)
            {
              bool bit;
              for (uint i = aRow + 1; i < this->RowCount; i++)
              {
                bit = this->getBit(i, aCol);
                if (bit)
                  this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[aRow]);
              }
              aCol++;
              aRow++;
            }
            else
            {
              bool bit;
              // так как мы уже знаем, что бит, находящийся на пересечении
              // activeRow и activeCol равен 0, то мы можем воспользоваться этим
              uint firstTrueBit = aRow;
              for (uint i = aRow + 1; i < this->RowCount; i++)
              {
                bit = this->getBit(i, aCol);
                if (bit)
                {
                  firstTrueBit = i;
                  break;
                }
              }
              // не состоит ли весь столбец из нулей
              if (firstTrueBit != aRow)
                this->plMatrix[aRow]->Xor(*this->plMatrix[aRow], *this->plMatrix[firstTrueBit]);
              else
                aCol++;
            }
          }
        activeCol += r;
        activeRow += r;
      }
      this->setTrianType(LEFT);
    }
    return *this;
  }

  //(c) Chernysheva, TEST(Matrix, RightTrian)
  //------->>>>>>>>>-----------------
  // приведение матрицы к треугольному виду алгоритмом Коновальцева,
  // внутри применяется бинарный алгоритм Гаусса
  // на выходе получаем верхнетреугольную матрицу справа-налево
  Matrix& Matrix::konovalcevRightTrianBits()
  {
    if ((this->getCoding() == ON_LINE)&&(this->getTrianType() == NONE))
    {
      //int r = (log(n)/log(P)) - 3*(log(log(n)/log(P))/log(P));
      // длина кортежа
      int r = 3;

      uint activeRow = 0, activeCol = this->ColCount - 1;;
      Polynom *cortege = new Polynom, *nul = new Polynom;
      while ((activeRow < this->RowCount)&&(activeCol >= 0))
      {
        uint aRow = activeRow, aCol = activeCol, notNulCortegeRow = 0;
        bool allCortegeNul = false;
        uint NumNotNulCortege = 0;
        // работа с кортежами
        while ((aRow < this->RowCount)&&(!allCortegeNul))
        {
          // ищем первый ненулевой кортеж
          for (uint i = aRow; i < this->RowCount; i++)
          {
            // прохождение по кортежу
            uint rc = 0;
            for (uint ri = aCol + 1 - r; ri < aCol + 1; ri++)
            {
              bool bit = this->getBit(i, ri);
              cortege->setBit(rc, bit);
              rc++;
            }
            if (*cortege != *nul)
            {
              notNulCortegeRow = i;
              NumNotNulCortege++;
              break;
            }
          }
          // все кортежи нулевые
          if (*cortege == *nul)
            allCortegeNul = true;
          else
          {
            Polynom *buf = new Polynom, *curCortege = new Polynom;
            // меняем местами активную строку со строкой с ненулевым кортежем
            if (notNulCortegeRow != aRow)
            {
              *buf = *this->plMatrix[notNulCortegeRow];
              *this->plMatrix[notNulCortegeRow] = *this->plMatrix[aRow];
              *this->plMatrix[aRow] = *buf;
            }
            // удаление одинаковых с активным кортежей
            for (uint i = aRow + 1; i < this->RowCount; i++)
            {
              uint rc = 0;
              for (uint ri = aCol + 1 - r; ri < aCol + 1; ri++)
              {
                bool bit = this->getBit(i, ri);
                curCortege->setBit(rc, bit);
                rc++;
              }
              uint t = 0;
              for (uint rc = 0;  rc < r; rc++)
              {
                bool y = (cortege->getBit(rc) == curCortege->getBit(rc));
                if (y)
                  t++;
              }
              if (t == r)
              {
                *this->plMatrix[i] = *this->plMatrix[i] - *this->plMatrix[aRow];
              }
            }
            aRow++;
          }
        }

        aRow = activeRow, aCol = activeCol;
        // метод Гаусса для приведения к треугольному виду
        while ((aRow < activeRow + NumNotNulCortege)&&(aCol >= 0))
        {
          bool bitActiveRow = this->getBit(aRow, aCol);
          if (bitActiveRow)
          {
            bool bit;
            for (uint i = aRow + 1; i < this->RowCount; i++)
            {
              bit = this->getBit(i, aCol);
              if (bit)
                this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[aRow]);
            }
            aCol--;
            aRow++;
          }
          else
          {
            bool bit;
            // так как мы уже знаем, что бит, находящийся на пересечении
            // activeRow и activeCol равен 0, то мы можем воспользоваться этим
            uint firstTrueBit = activeRow;
            for (uint i = aRow + 1; i < this->RowCount; i++)
            {
              bit = this->getBit(i, aCol);
              if (bit)
              {
                firstTrueBit = i;
                break;
              }
            }
            // не состоит ли весь столбец из нулей
            if (firstTrueBit != activeRow)
              this->plMatrix[aRow]->Xor(*this->plMatrix[aRow], *this->plMatrix[firstTrueBit]);
            else
              aCol--;
          }
        }
        activeCol -= r;
        activeRow += r;
      }
      this->setTrianType(RIGHT);
    }
    return *this;
  }

  //(c) Chernysheva, TEST(Matrix, NonSign)
  //------->>>>>>>>>-----------------
  // проверка на невырожденность
  bool Matrix::nonsignMatrix()
  {
    if (this->getIsNonSign())
    {
      switch (this->IsTrian)
      {
        case NONE:
          gausRightTrian();
          return nonsignMatrix();
          break;
        case RIGHT:
        {
          bool bit;
          uint activeRow = 0;
          int activeCol = this->ColCount - 1;
          while ((activeRow < this->RowCount)||(activeCol >= 0))
          {
            bit = this->getBit(activeRow, activeCol);
            if (!bit)
            {
              this->setIsNonSign(false);
              return false;
            }
            activeRow++;
            activeCol--;
          }
          this->setIsNonSign(true);
          return true;
        }
        case LEFT:
        {
          bool bit;
          uint activeRow = 0, activeCol = 0;
          while ((activeRow < this->RowCount)||(activeCol < this->ColCount))
          {
            bit = this->getBit(activeRow, activeCol);
            if (!bit)
            {
              this->setIsNonSign(false);
              return false;
            }
            activeRow++;
            activeCol++;
          }
          this->setIsNonSign(true);
          return true;
        }
      }
    }
    this->setIsNonSign(false);
    return false;
  }

  //(c) Chernysheva, TEST(Matrix, RightDiag)
  //------->>>>>>>>>-----------------
  // приведение матрицы к диагональному виду алгоритмом Гаусса,
  // интерпретируем полиномы как многочлены,
  // если степени многочленов совпадаюn, то скаладываем строки
  // на выходе получаем диагональную матрицу справа-налево
  Matrix& Matrix::gausRightDiag()
  {
    switch (this->getTrianType())
    {
      case NONE:
        gausRightTrian();
        if (nonsignMatrix())
          gausRightDiag();
        break;
      case RIGHT:
        if (nonsignMatrix())
        {
          if (this->ColCount == this->RowCount)
          {
            int activeRow = this->RowCount - 1;
            while (activeRow >= 0)
            {
              bool bit;
              uint degActive = this->plMatrix[activeRow]->getFirstTrueBit();
              for (int i = activeRow - 1; i >= 0; i--)
              {
                uint degCur = this->plMatrix[i]->getFirstTrueBit();
                if (degActive == degCur)
                  this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
              }
              activeRow--;
            }
          }
        }
        break;
      case LEFT:
        if (nonsignMatrix())
          gausLeftDiagBits();
        break;
    }
    return *this;
  }

  //(c) Chernysheva, TEST(Matrix, LeftDiag)
  //------->>>>>>>>>-----------------
  // приведение матрицы к диагональному виду алгоритмом Гаусса, работаем
  // с самими битами, не прибегая к интерпритации digits как чисел
  // на выходе получаем диагональную матрицу слева-направо
  Matrix& Matrix::gausLeftDiagBits()
  {
    switch (this->getTrianType())
    {
      case NONE:
        gausRightTrian();
        if (nonsignMatrix())
          gausRightDiag();
        break;
      case RIGHT:
        if (nonsignMatrix())
          gausRightDiag();
        break;
      case LEFT:
        if (nonsignMatrix())
        {
          if (this->ColCount == this->RowCount)
          {
            uint activeCol = 0, activeRow = 0;
            while ((activeRow < this->RowCount)||(activeCol < this->ColCount))
            {
              bool bit;
              for (uint i = 0; i < activeRow; i++)
              {
                bit = this->getBit(i, activeCol);
                if (bit)
                  this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
              }
              activeRow++;
              activeCol++;
            }
          }
        }
        break;
    }
    return *this;
  }

  //(c) Chernysheva, TEST(Matrix, RightDiag)
  //------->>>>>>>>>-----------------
  // приведение матрицы к диагональному виду алгоритмом Гаусса, работаем
  // с самими битами, не прибегая к интерпритации digits как чисел
  // на выходе получаем диагональную матрицу справа-налево
  Matrix& Matrix::gausRightDiagBits()
  {
    switch (this->getTrianType())
    {
      case NONE:
        gausRightTrian();
        if (nonsignMatrix())
          gausRightDiagBits();
        break;
      case RIGHT:
        if (nonsignMatrix())
        {
          if (this->ColCount == this->RowCount)
          {
            uint activeRow = 0;
            int activeCol = this->ColCount - 1;
            while ((activeRow < this->RowCount)||(activeCol >= 0))
            {
              bool bit;
              for (uint i = 0; i < activeRow; i++)
              {
                bit = this->getBit(i, activeCol);
                if (bit)
                  this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
              }
              activeRow++;
              activeCol--;
            }
          }
        }
        break;
      case LEFT:
        if (nonsignMatrix())
          gausLeftDiagBits();
        break;
    }
    return *this;
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // приведение матрицы к диагональному виду алгоритмом Гаусса
  // без учета невырожденности
  Matrix& Matrix::diagWithoutNonsign()
  {
    switch (this->getTrianType())
    {
      case NONE:
        gausRightTrian();
        gausRightDiag();
        break;
      case RIGHT:
        if (this->ColCount == this->RowCount)
        {
          int activeRow = this->RowCount - 1;
          while (activeRow >= 0)
          {
            bool bit;
            uint degActive = this->plMatrix[activeRow]->getFirstTrueBit();
            for (int i = activeRow - 1; i >= 0; i--)
            {
              uint degCur = this->plMatrix[i]->getFirstTrueBit();
              if (degActive == degCur)
                this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
            }
            activeRow--;
          }
        }
        break;
      case LEFT:
        gausLeftDiagBits();
        break;
    }
    return *this;
  }


  //(c) Chernysheva, TEST(Matrix, Reverse)
  //------->>>>>>>>>-----------------
  // обращение матрицы
  // внутри используется битовый алгоритм Гаусса для приведения
  // к треугольному виду
  // на выходе получаем обратную матрицу
  Matrix& Matrix::reverseLeftBits()
  {
    if (this->ColCount == this->RowCount)
    {
      Matrix E;
      createUnitaryMatrixLeft(this->RowCount, this->ColCount, this->getCoding(), E);
      if (this->getCoding() == ON_LINE)
      {
        // треугольный вид
        uint activeRow = 0, activeCol = 0;
        while ((activeRow < this->RowCount)||(activeCol < this->ColCount))
        {
          bool bitActiveRow = this->getBit(activeRow, activeCol);
          if (bitActiveRow)
          {
            bool bit;
            for (uint i = activeRow + 1; i < this->RowCount; i++)
            {
              bit = this->getBit(i, activeCol);
              if (bit)
              {
                this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
                E.plMatrix[i]->Xor(*E.plMatrix[i], *E.plMatrix[activeRow]);
              }
            }
            activeCol++;
            activeRow++;
          }
          else
          {
            bool bit;
            // так как мы уже знаем, что бит, находящийся на пересечении
            // activeRow и activeCol равен 0, то мы можем воспользоваться этим
            uint firstTrueBit = activeRow;
            for (uint i = activeRow + 1; i < this->RowCount; i++)
            {
              bit = this->getBit(i, activeCol);
              if (bit)
              {
                firstTrueBit = i;
                break;
              }
            }
            // проверка не состоит ли весь столбец из нулей
            if (firstTrueBit != activeRow)
            {
              this->plMatrix[activeRow]->Xor(*this->plMatrix[activeRow], *this->plMatrix[firstTrueBit]);
              E.plMatrix[activeRow]->Xor(*E.plMatrix[activeRow], *E.plMatrix[firstTrueBit]);
            }
            else
              activeCol++;
          }
        }//while

        // проверка невырожденности
        bool bit;
        activeRow = 0, activeCol = 0;
        while ((activeRow < this->RowCount)||(activeCol < this->ColCount))
        {
          bit = this->getBit(activeRow, activeCol);
          if (!bit)
            this->setIsNonSign(false);
          activeRow++;
          activeCol++;
        } // while
        this->setIsNonSign(true);

        if (this->IsNonSign)
        {
          // диагольный вид
          activeCol = 0, activeRow = 0;
          while ((activeRow < this->RowCount)||(activeCol < this->ColCount))
          {
            bool bit;
            for (uint i = 0; i < activeRow; i++)
            {
              bit = this->getBit(i, activeCol);
              if (bit)
              {
                this->plMatrix[i]->Xor(*this->plMatrix[i], *this->plMatrix[activeRow]);
                E.plMatrix[i]->Xor(*E.plMatrix[i], *E.plMatrix[activeRow]);
              }
            }
            activeRow++;
            activeCol++;
          }// while
        }
      }//if
      else
        // переход матрица в зашифровку по строкам
        conversionMatrix();

      for (uint i = 0; i < this->RowCount; i++)
        this->setElemMatrix(i, *E.plMatrix[i]);
      return *this;
    }//if
  }

  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // обращение матрицы
  // внутри используется алгоритм Гаусса для "упакованных" матриц
  // для приведения к треугольному виду
  // на выходе получаем обратную матрицу
  Matrix& Matrix::reverseRight()
  {
    if (this->ColCount == this->RowCount)
    {
      Matrix E;
      createUnitaryMatrixRight(this->RowCount, this->ColCount, this->getCoding(), E);
      if (this->getCoding() == ON_LINE)
      {
      }
      else
        // переход к матрице зашифровка по строкам
        conversionMatrix();
    }//if
    return *this;
  }

  //-------------------- операции с матрицами и векторами -------------------

  //(c) Chernysheva, TEST(Matrix, mulVecToMatrix)
  //------->>>>>>>>>-----------------
  // умножение вектор-строки на матрицу
  Polynom mulVecToMatrix(const Polynom& plA, const Matrix& mtB)
  {
    Polynom vec;
    if (mtB.CodeWord == Matrix::ON_COLUMN)
    {
      if (mtB.RowCount >= plA.getNumberBits())
      {
        for (uint j = 0; j < mtB.ColCount; j++)
        {
          uint sum = 0, elem, a, b;
          for (uint i = 0; i < plA.getNumberDigits(); i++)
          {
            elem =  plA.getDigit(i) & mtB.plMatrix[j]->getDigit(i);
            sum = sum ^ elem;
          }
          vec.setDigit(j, sum);
        }

        Polynom res;
        uint s = 0;
        for (uint j = 0; j < vec.getNumberDigits(); j++)
        {
          bool bit = 0;
          for (uint i = 0; i < vec.getDigitSizeInBits(); i++)
          {
            bit = bit  ^ vec.getBit(s);
            s++;
          }
          res.setBit(j, bit);
        }
        return res;
      }
    }
    vec = plA;
    return vec;
  }

  //(c) Chernysheva, TEST(Matrix, mulMatrixToVec)
  //------->>>>>>>>>-----------------
  // умножение матрицы на вектор-столбец
  Polynom mulMatrixToVec(const Polynom& plA, const Matrix& mtB)
  {
    Polynom vec;
    if (mtB.CodeWord == Matrix::ON_LINE)
    {
      if (mtB.ColCount >= plA.getNumberBits())
      {
        for (uint j = 0; j < mtB.RowCount; j++)
        {
          uint sum = 0, elem;
          for (uint i = 0; i < mtB.getColCountMatrixByte(); i++)
          {
            elem = mtB.plMatrix[j]->getDigit(i) & plA.getDigit(i);
            sum = sum ^ elem;
          }
          vec.setDigit(j, sum);
        }

        Polynom res;
        uint s = 0;
        for (uint j = 0; j < vec.getNumberDigits(); j++)
        {
          bool bit = 0;
          for (uint i = 0; i < vec.getDigitSizeInBits(); i++)
          {
            bit = bit  ^ vec.getBit(s);
            s++;
          }
          res.setBit(j, bit);
        }
        return res;
      }
    }
    vec = plA;
    return vec;
  }


  //(c) Chernysheva
  //------->>>>>>>>>-----------------
  // умножение двух матриц
  Matrix& Matrix::mul(const Matrix& mtA, const Matrix& mtB)
  {
    return *this;
  }
//**********************************    Транспонирование матрицы   *******************************************
  //TEST(Matrix, Transpose)
  Matrix & Matrix::Transpose()
  {
    Matrix::CodingSystem oldCoding = getCoding();
    conversionMatrix();
    setCoding(oldCoding);
    return *this;
  }

//************************************************************************************************************
//**********************************    Решение СЛАУ               *******************************************

  Polynom Matrix::SolveLinearEquationSystem(const Matrix & A, const Polynom & b)
  {
        Polynom copy_b(b), result;
        Matrix copy_A(A);
        copy_A.gausRightDiagForEquation(copy_b);
        // перестановка битов в противоположном порядке (можно будет избавиться если приводить к главной диагоняли)
        for(uint i = 0; i < copy_A.RowCount; i++)
                result.setBit(i, copy_b.getBit(copy_A.RowCount - i - 1));
        return result;
  }


  Matrix& Matrix::gausRightTrianForEquation(Polynom & right)
  {
    if ((getCoding() == ON_LINE) && (getTrianType() == NONE))
    {
      uint maxDigits = 0, row = getRowCount();
      for (uint i = 0; i < row; i++)
        if (maxDigits < plMatrix[i]->getNumberDigits())
          maxDigits = plMatrix[i]->getNumberDigits();

      uint activeRow = 0;
      int activeCol = maxDigits - 1;
      while ((activeRow < row)&&(activeCol >= 0))
      {
        uint max = 0, j = activeRow, digit;
        for (uint i = activeRow; i < row; i++)
        {
          digit = plMatrix[i]->getDigit(activeCol);
          if (max < digit)
          {
            max = digit;
            j = i;
          }
        }
        if (max)
        {
          uint r = degree(max);
          uint ar = 1<<r;
          if (plMatrix[activeRow]->getDigit((uint)activeCol) < ar)
          {
            plMatrix[activeRow]->Xor(*plMatrix[j], *plMatrix[activeRow]);
            right.setBit(activeRow, right.getBit(j)^right.getBit(activeRow));
          }
          for (uint i = activeRow + 1; i < row; i++)
          {
            if (plMatrix[i]->getDigit((uint)activeCol) >= ar)
            {
              plMatrix[i]->Xor(*plMatrix[i], *plMatrix[activeRow]);
              right.setBit(i, right.getBit(i)^right.getBit(activeRow));
            }
          }
          activeRow++;
        }
        else
          activeCol--;
      }
      setTrianType(RIGHT);
    }
    else
        throw new Exception("Матрица должна быть упакована по строкам и не приведена к треугольному виду");
    return *this;
  }

  
  Matrix& Matrix::gausRightDiagForEquation(Polynom & right)
  {
    switch(getTrianType())
    {
      case NONE:
        gausRightTrianForEquation(right);
        if (nonsignMatrix())
          gausRightDiagForEquation(right);
        break;
      case RIGHT:
        if (nonsignMatrix())
        {
          if (ColCount == RowCount)
          {
            int activeRow = RowCount - 1;
            while (activeRow >= 0)
            {
              bool bit;
              uint degActive = plMatrix[activeRow]->getFirstTrueBit();
              for (int i = activeRow - 1; i >= 0; i--)
              {
                uint degCur = plMatrix[i]->getFirstTrueBit();
                if (degActive == degCur)
                {
                  plMatrix[i]->Xor(*plMatrix[i], *plMatrix[activeRow]);
                  right.setBit(i, right.getBit(i)^right.getBit(activeRow));
                }
              }
              activeRow--;
            }
          }
        }
        break;
      case LEFT:
        throw new Exception("Матрица не должна быть приведена к левому треугольному виду");
    }
    return *this;
  }
//************************************************************************************************************
//**********************************    Приведение к строке        *******************************************
  //(c) Chernysheva
  string Matrix::ToString() const
  {
        if(CodeWord != Matrix::ON_LINE)
                throw new Exception("Матрица должна быть упакована по строкам");
        string str;

        for(uint i = 0; i < RowCount; i++)
                str += plMatrix.at(i)->ToString() + "\n";
        return str;
  }
};
