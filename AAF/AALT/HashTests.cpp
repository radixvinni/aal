/*
    MPEI Algebraic Abstractions Library,
    2007-2011,
    Moscow Power Engineering Institute

        This file contains tests of the following classes:

*/
#include <iostream>
#include <stdio.h>
#include "./CppUnitLite/TestHarness.h"
#include "./AAF/AAL/HashClass.h"
#include <set>
#include <string.h>

TEST(Hash, MD2)
{
	FILE *file;

        Hash TestHash;
        file = fopen ("../HashTestFile.txt", "rb");
	TestHash.MD2_Generate(file);
        fclose(file);
	CHECK(!strcmp(TestHash.digest,"ef1fedf5d32ead6b7aaf687de4ed1b71"));
}

TEST(Hash, MD4)
{
	FILE *file;

        Hash TestHash;
        file = fopen ("../HashTestFile.txt", "rb");
	TestHash.MD4_Generate(file);
        fclose(file);
	CHECK(!strcmp(TestHash.digest,"c58cda49f00748a3bc0fcfa511d516cb"));
}

TEST(Hash, MD5)
{
	FILE *file;

        //strcpy(string,"123");
        Hash TestHash;
        file = fopen ("../HashTestFile.txt", "rb");
	TestHash.MD5_Generate(file);
    TestHash.digest[32]=0;
 	CHECK(!strcmp(TestHash.digest,"202cb962ac59075b964b07152d234b70"));
	fclose(file);
}

TEST(Hash, SHA1)
{
	FILE *file;
        Hash TestHash;
        file = fopen ("../HashTestFile.txt", "rb");
	TestHash.SHA1_Generate(file);
        fclose(file);
	CHECK(!strcmp(TestHash.digest,"3e13dd3fbcaa58c0b7a7be8a0b16d77d5c08ab5d"));
}


TEST(Hash, GOST)
{
	FILE *file;
        Hash TestHash;
        file = fopen ("../HashTestFile.txt", "rb");
	TestHash.GOST_Generate(file);
        fclose(file);
	CHECK(!strcmp(TestHash.digest,"b79465edbb2036fa2cb1f488c01747ab1b808939ac2973d275968c38b00254d2"));
}

TEST(Hash, CRC32B)
{
	FILE *file;
        Hash TestHash;
        file = fopen ("../HashTestFile.txt", "rb");
	TestHash.CRC32B_Generate(file);
        fclose(file);
	CHECK(!strcmp(TestHash.digest,"884863d2"));
}


char *string;
//strcpy(string,"123");


TEST(Hash, MD2_String)
{

        char *string = "123";
	    Hash TestHash;
		TestHash.MD2_GenerateFromString(string);
		CHECK(!strcmp(TestHash.digest,"ef1fedf5d32ead6b7aaf687de4ed1b71"));
}

TEST(Hash, MD4_String)
{

	char *string="123";
        Hash TestHash;
	TestHash.MD4_GenerateFromString(string);
	CHECK(!strcmp(TestHash.digest,"c58cda49f00748a3bc0fcfa511d516cb"));
}

TEST(Hash, MD5_String)
{

	char *string="123";
        Hash TestHash;
	TestHash.MD5_GenerateFromString(string);
	CHECK(!strcmp(TestHash.digest,"202cb962ac59075b964b07152d234b70"));
}

TEST(Hash, SHA1_String)
{

	char *string="123";
        Hash TestHash;
	TestHash.SHA1_GenerateFromString(string);
	CHECK(!strcmp(TestHash.digest,"3e13dd3fbcaa58c0b7a7be8a0b16d77d5c08ab5d"));
}


TEST(Hash, GOST_String)
{

	char *string="123";
        Hash TestHash;
	TestHash.GOST_GenerateFromString(string);
	CHECK(!strcmp(TestHash.digest,"b79465edbb2036fa2cb1f488c01747ab1b808939ac2973d275968c38b00254d2"));
}

TEST(Hash, CRC32B_String)
{

	char *string="123";
        Hash TestHash;
	TestHash.CRC32B_GenerateFromString(string);
	CHECK(!strcmp(TestHash.digest,"884863d2"));
}
