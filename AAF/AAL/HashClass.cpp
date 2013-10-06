/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------


#pragma hdrstop

#include "HashClass.h"
#include "Hash.h"
#include <math.h>
#include <time.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

void Hash::Clear()
{
 strcpy(digest,"");
}

void Hash::Set(char digest[64])
{
 strcpy(this->digest,digest);
}

void Hash::MD2_Generate(FILE *hashfile)
{
   MD2(hashfile,digest);
}

void Hash::MD2_GenerateFromString(char *string)
{
   MD2_String(string,digest);
}

void Hash::MD4_Generate(FILE *hashfile)
{
   MD4(hashfile,digest);
}

void Hash::MD4_GenerateFromString(char *string)
{
   MD4_String(string,digest);
}

void Hash::MD5_Generate(FILE *hashfile)
{
   MD5(hashfile,digest);
}

void Hash::MD5_GenerateFromString(char *string)
{
   MD5_String(string,digest);
}

void Hash::SHA1_Generate(FILE *hashfile)
{
   SHA1(hashfile,digest);
}

void Hash::SHA1_GenerateFromString(char *string)
{
   SHA1_String(string,digest);
}

void Hash::GOST_Generate(FILE *hashfile)
{
   gosthash(hashfile,digest);
}

void Hash::GOST_GenerateFromString(char *string)
{
   gosthash_String(string,digest);
}

void Hash::CRC32B_Generate(FILE *hashfile)
{
   CRC32B(hashfile,digest);
}

void Hash::CRC32B_GenerateFromString(char *string)
{
   CRC32B_String(string,digest);
}
