/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include "FactorizationAlgorithms.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include "ProbingDivisionAlgorithmDecompositionThread.h"
#include <stdio.h>

#include "./Bindings/config.h"
#ifndef USE_MSIEVE
#include <windows.h>
#endif

namespace AAL
{
  FactorizationAlgorithms::FactorizationAlgorithms(Integer number)
  {
    this->number =  number;
  }
//-----------------------------------------------------------------------------

DecVector FactorizationAlgorithms::ProbingDivisionAlgorithmDecomposition() {
  DecVector result;
  Integer sqrtNum;
  Integer F("2");
  Integer divNum(number);
  sqrtNum.SquareRoot(divNum);
  while(divNum != 1) {
    if(divNum%F == 0)
    {
      Integer Int_degree(1);
      divNum = divNum/F;
      while(divNum%F == 0) {
        Int_degree++;
        divNum = divNum/F;
      }
      sqrtNum.SquareRoot(divNum);
      DecompositionMember a(F,Int_degree);
      result.push_back(a);
    }
    if(F > sqrtNum + 1) {
      F = divNum;
    } else {
      F++;
    }
  }
  return result;
}
//-----------------------------------------------------------------------------

Integer FactorizationAlgorithms::FermaAlgorithm(Integer number){

Integer num(number);
Integer x;
Integer powNum;
Integer powNum1;
Integer y;
Integer yy;
Integer two("2");
Integer one("1");
x.SquareRoot(num);
  if(number == powNum.Pow(x, two)){
    return  x;
  }else{
    x++;
    if(x == ((number + one)/two)){
      return  number;
    }else{
      yy=(powNum.Pow(x,two)- number);
      y.SquareRoot(yy);
      while(powNum.Pow(y,two) != (powNum1.Pow(x,two)-number)) {
            x++;
           if(x == ((number + one)/two)){
            return  number;
           }
            yy=(powNum.Pow(x,two) - number);
            y.SquareRoot(yy);
      }
      return x - y;
    }
  }
}
//-----------------------------------------------------------------------------

DecVector FactorizationAlgorithms::FermaAlgorithmDecomposition(){
if (!number.isOdd())
     throw new Exception("Число четно");
else{
DecVector vector;
Integer Int_degree("1");
Integer divNum(number);
  while(divNum != 1){
    Int_degree = 1;
    Integer rez = FermaAlgorithm(divNum);
    divNum = divNum/rez;
    while(divNum%rez == 0) {
       Int_degree++;
       divNum = divNum/rez;
    }
    DecompositionMember a(rez,Int_degree);
    vector.push_back(a);
  }
return vector;
}
}
//-----------------------------------------------------------------------------

DecVector FactorizationAlgorithms::P0AlgorithmDecomposition(){
std::vector<Integer> vector;
Integer xPriv("1");
Integer rez("1");
vector.push_back(1);
std::vector<Integer>::iterator it;
Integer x;
Integer two("2");
DecVector result;
Integer Int_degree("1");
Integer divNum(number);


  while(divNum != 1){
    Int_degree = 1;
    x = xPriv.Pow(xPriv,two) + 1;
    vector.push_back(x);
    for(it = vector.begin(); it != vector.end(); it++ ){
      if((*it) != x){
        if(rez.Euclid(x-(*it) ,divNum) != 1){
          divNum = divNum/rez;
          while(divNum%rez == 0) {
            Int_degree++;
            divNum = divNum/rez;
          }
          DecompositionMember a(rez,Int_degree);
          result.push_back(a);
          break;
        }
      }
    }
    xPriv = x;
  }
return result;
}
//-------------------------------------------------------------------------------
DecVector FactorizationAlgorithms::FastP0AlgorithmDecomposition() {
  //std::vector<Integer> vector;
  Integer xPriv;
  Integer k("1");
  //vector.push_back(1);
  //std::vector<Integer>::iterator it;
  Integer x("1"),eucl, r, i, rez;
  Integer two("2");
  DecVector result;
  Integer Int_degree("1");
  Integer divNum(number);

  xPriv =  xPriv.Pow(x,two) + 1;
  rez = eucl.Euclid(x - xPriv ,divNum);
  while(divNum != 1) {
     x =  xPriv;
     for( i = 0; i < r.Pow(2, k); i++ ) {
        xPriv = xPriv.Pow(xPriv,two) + 1;
        rez = eucl.Euclid(x - xPriv ,divNum);
        if(rez != 1) {
          divNum = divNum/rez;
          while(divNum%rez == 0) {
            Int_degree++;
            divNum = divNum/rez;
          }
          DecompositionMember a(rez,Int_degree);
          result.push_back(a);
          k = 0;
          xPriv = 2;
          Int_degree = 1;
          break;
        }
     }
     k++;
  }
return result;
}
//------------------------------------------------------------------------------



DecVector FactorizationAlgorithms::MsieveDecomposition()
{
 DecVector result;
 DecVector fail;
 bool complite_factorize=true;
 std::string s1=number.strr();
if (s1.length()>275 )
  {
   throw new Exception("Разлагаемое число не должно содержать более чем 275 десятичных знаков!");
   return fail;

  }
if (FileExists("msieve.log"))
 remove ("msieve.log");
#ifndef USE_MSIEVE
if (!FileExists("msieve.exe"))
 {
 //throw std::domain_error("Не найден файл msieve.exe!");
 throw new Exception("Не найден файл msieve.exe");
 return fail;
 }
 std::string s= "msieve.exe -e -v -m -p ";
 s.append(" ");
 s.append(number.strr() );
 STARTUPINFOA StInfo;
 PROCESS_INFORMATION PrInfo;
 ZeroMemory(&StInfo,sizeof(StInfo));
 StInfo.cb=sizeof(StInfo);
  if (!CreateProcessA(NULL,const_cast<char *>(s.c_str()) ,NULL,NULL,FALSE,CREATE_NEW_CONSOLE | IDLE_PRIORITY_CLASS,
                     NULL,
                     NULL,
                     &StInfo,
                     &PrInfo))
    {
        return fail;
    }
  // Ждём, пока процесс не выполнится:
  WaitForSingleObject(PrInfo.hProcess,INFINITE);
#else
	//ref:msieve_main
	char** argv=new char*[6];
	for(int i=0;i<6;i++)argv[i]=new char[256];
	strcpy(argv[0],"./msieve.exe");
	strcpy(argv[1],"-e");
	strcpy(argv[2],"-v");
	strcpy(argv[3],"-m");
	strcpy(argv[4],"-p");
	strcpy(argv[5],number.strr().c_str());
	msieve_main(6,argv);
	for(int i=0;i<6;i++)delete[] argv[i];
	delete[] argv;
#endif
  std::vector<std::string> res;
   std::vector<std::string> factors;
   try
        {
         std::ifstream ifs("msieve.log");
		 std::string temp;
		 while( getline( ifs, temp ) )
			res.push_back( temp );
        }
        catch(Exception *E)
        {
         return fail;
        }
   std::string isfinished =res[res.size()-1];
   if (isfinished.find("elapsed time")==std::string::npos) throw new Exception("Операция отменена пользователем");
   for (int j=0;j<res.size();j++)
    {
      std::string str=res[j];
       int pos=str.find("factor:");
        if (pos!=std::string::npos)
          factors.push_back(str.substr(pos+8,str.size()-pos-7));
    }

if (factors.size()==0)
{
   DecompositionMember a(number ,1);
   result.push_back(a);
   if (!number.isPrime()) complite_factorize=false;
}
else
 {
     int pos=0;
        while ( pos < factors.size())
                {
                        Integer exp(0);
                        std::string tmpfactor=factors[pos];
                        while ( (pos < factors.size()) && (factors[pos]==tmpfactor) )
                                {
                                        exp=exp+1;
                                        pos++;
                                }
                                /* forming factor-exponent struction */
                                        Integer n(tmpfactor.c_str());
                                        if (!n.isPrime()) complite_factorize=false;
                                         DecompositionMember a(n ,exp);
                                         result.push_back(a);

                }
   };

 if(complite_factorize==false)
     throw new Exception("В разложении присутствуют составные множители");

return result;

}




}

