/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
//---------------------------------------------------------------------------

#ifndef ClassesH
#define ClassesH
#include <stdio.h>
#include <memory>
//---------------------------------------------------------------------------
#endif

class Hash
{
  public:
        char *digest;
        Hash()
        {
			digest=new char[64];
			//digest=(char*)malloc(64);
        }

        ~Hash()
		{
           if(digest) delete[]digest;
			//free((void*)digest);
        };
        void Clear();
        void Set(char digest[64]);
        void MD2_Generate(FILE *hashfile);
        void MD2_GenerateFromString(char *string);
        void MD4_Generate(FILE *hashfile);
        void MD4_GenerateFromString(char *string);
        void MD5_Generate(FILE *hashfile);
        void MD5_GenerateFromString(char *string);
        void SHA1_Generate(FILE *hashfile);
        void SHA1_GenerateFromString(char *string);
        void GOST_Generate(FILE *hashfile);
        void GOST_GenerateFromString(char *string);
        void CRC32B_Generate(FILE *hashfile);
        void CRC32B_GenerateFromString(char *string);

};

