/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "PrimeTester.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
namespace AAL
{
  PrimeTester::PrimeTester(Integer number)
  {
    Mersen_Number = number;
  }
//-----------------------------------------------------------------------------
 //mersen number (2^s)-1
   bool PrimeTester::TestLukaLemera(Integer degree)
   {
    Integer Three("3");
    if (degree < Three)
      throw new Exception("Степень меньше 3");

    Integer s = degree;
    Integer sqrt = degree.Sqrt();

      for(Integer i("2"); i <= sqrt; i++)
        {
         Integer quotient = (Mersen_Number)/i;
         if( i*quotient == (Mersen_Number))
            return false;
        }
    Integer u("4");
    Integer j("2");
    for(Integer k("1"); k <= s - j; k++)
    {
      u = (u*u - j) % (Mersen_Number);
      if(u.isZero())
        return true;
    }

    return false;
  }
//-----------------------------------------------------------------------------
  //  number is odd
   bool PrimeTester::ModifiedTestLuka(std::vector<DecompositionMember> vector)
   {
     if (!Mersen_Number.isOdd())
      throw new Exception("Четное число");
    std::vector<DecompositionMember>::iterator it;
    Integer one("1");
    Integer rez;
    Integer rez2;
    Integer difference = (Mersen_Number - one);
    for( it = vector.begin(); it != vector.end(); it++)
        {
          Integer num(it->getNumber());
          Integer div = difference/num;
          Integer a("2");
         for(a; a <= Mersen_Number - one; a++)
          {
          rez.ModPow(a, difference, Mersen_Number);
          rez2.ModPow(a, div,Mersen_Number);
          if(rez%Mersen_Number == one && rez2%Mersen_Number != one) break;

          if(a == difference && (rez%Mersen_Number != one || rez2%Mersen_Number == one))
          {
            return false;
          }
          rez.setZero();
          rez2.setZero();
          }
        }
   return true;
   }

//------------------------------------------------------------------------------
bool PrimeTester::TestPoklingtona(std::vector<DecompositionMember> vector)
{
    std::vector<DecompositionMember>::iterator it;
    Integer one("1");
    Integer difference = (Mersen_Number - one);
    Integer sqrt = difference.Sqrt();
    Integer rez,rez2,rez3;
    for( it = vector.begin(); it != vector.end(); it++)
        {
          Integer num(it->getNumber());

          if(num >= sqrt)
          {
              for(Integer a("1");a <= Mersen_Number - one; a++)
              {
               rez.ModPow(a,Mersen_Number - one, Mersen_Number);
               rez2.ModPow(a,(Mersen_Number - one)/num, Mersen_Number);
               if(rez%Mersen_Number == 1)
               {
                 if(rez3.Euclid(rez2-one,Mersen_Number) == one)
                 {
                  return true;
                 }
               }
              }
          }
          else
            if(it == vector.end()-1)
              throw new Exception("Работа алгоритма невозможна,нет простых множителей, больших sqrt(n-1)");
        }
 return false;
}
};

