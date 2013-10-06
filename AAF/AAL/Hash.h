/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#include <stdio.h>
#include <string.h>
#ifndef PROTOTYPES
#define PROTOTYPES 1
#endif

/* POINTER defines a generic pointer type */
#define POINTER unsigned char*

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
   If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
     returns an empty list.  
 */
#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif




typedef struct
 {
  unsigned char state[16];                                         /* state */
  unsigned char checksum[16];                                   /* checksum */
  unsigned int count;                         /* number of bytes, modulo 16 */
  unsigned char buffer[16];                                 /* input buffer */
}MD2_CTX;

void MD2Init PROTO_LIST ((MD2_CTX *));
void MD2Update PROTO_LIST ((MD2_CTX *, unsigned char *, unsigned int));
void MD2Final PROTO_LIST ((unsigned char [16], MD2_CTX *));
void MD2 (FILE *file, char buf[16]);
void MD2_String (char *string, char buf[16]);

/* MD4 context. */
typedef struct {
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
} MD4_CTX;

void MD4Init PROTO_LIST ((MD4_CTX *));
void MD4Update PROTO_LIST
  ((MD4_CTX *, unsigned char *, unsigned int));
void MD4Final PROTO_LIST ((unsigned char [16], MD4_CTX *));
void MD4 (FILE *file, char buf[16]);
void MD4_String (char *string, char buf[16]);

/* MD5 context. */
typedef struct {
  UINT4 state[4];                                           /* state (ABCD) */
  UINT4 count[2];                /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                                 /* input buffer */
} MD5_CTX;

void MD5Init PROTO_LIST ((MD5_CTX *));
void MD5Update PROTO_LIST ((MD5_CTX *, unsigned char *, unsigned int));
void MD5Final PROTO_LIST ((unsigned char [16], MD5_CTX *));
void MD5 (FILE *file, char buf[16]);
void MD5_String (char *string, char buf[16]);

/* SHA1 context. */
typedef struct {
    unsigned long state[5];
    unsigned long count[2];
    unsigned char buffer[64];
} SHA1_CTX;

void SHA1Transform(unsigned long state[5], unsigned char buffer[64]);
void SHA1Init(SHA1_CTX* context);
void SHA1Update(SHA1_CTX* context, unsigned char* data, unsigned int len);
void SHA1Final(unsigned char digest[20], SHA1_CTX* context);
void SHA1 (FILE *file, char buf[32]);
void SHA1_String (char *string, char buf[32]);

/****************************GOST***********************************************/

/* State structure */

typedef struct 
{
  unsigned long sum[8];
  unsigned long hash[8];
  unsigned long len[8];
  unsigned char partial[32];
  size_t partial_bytes;  
} GostHashCtx;
  
/* Compute some lookup-tables that are needed by all other functions. */

void gosthash_init();     

/* Clear the state of the given context structure. */

void gosthash_reset(GostHashCtx *ctx);  

/* Mix in len bytes of data for the given buffer. */

void gosthash_update(GostHashCtx *ctx, const unsigned char *buf, size_t len);

/* Compute and save the 32-byte digest. */

void gosthash_final(GostHashCtx *ctx, unsigned char *digest);

void gosthash (FILE *file, char buf[32]);
void gosthash_String (char *string, char buf[32]);

/***********************************CRC32B**************************************/

void CRC32B (FILE *file, char buf[32]);
void CRC32B_String (char *string, char buf[32]);

