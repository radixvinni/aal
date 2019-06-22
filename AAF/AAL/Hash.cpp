/*
		MPEI Algebraic Abstractions Library,
		2007-2011,
		Moscow Power Engineering Institute

        This file contains definitions and implementations of the following classes:

*/
#pragma hdrstop
#include "Hash.h"
#include <stdio.h>

static void MD2Transform PROTO_LIST
  ((unsigned char [16], unsigned char [16], unsigned char [16]));
static void MD2_memcpy PROTO_LIST ((POINTER, POINTER, unsigned int));
static void MD2_memset PROTO_LIST ((POINTER, int, unsigned int));

// Перестановка 0.. 255 построенная из цифр пи. Это дает "случайную" нелинейную операцию замены байта

static unsigned char PI_SUBST[256] = {
  41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
  19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
  76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
  138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
  245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
  148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
  39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
  181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
  150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
  112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
  96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
  85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
  234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
  129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
  8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
  203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
  166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
  31, 26, 219, 153, 141, 51, 159, 17, 131, 20
};

static unsigned char *PADDING_MD2[] = {
  (unsigned char *)"", (unsigned char *)"\001", (unsigned char *)"\002\002",
  (unsigned char *)"\003\003\003", (unsigned char *)"\004\004\004\004",
  (unsigned char *)"\005\005\005\005\005",
  (unsigned char *)"\006\006\006\006\006\006",
  (unsigned char *)"\007\007\007\007\007\007\007",
  (unsigned char *)"\010\010\010\010\010\010\010\010",
  (unsigned char *)"\011\011\011\011\011\011\011\011\011",
  (unsigned char *)"\012\012\012\012\012\012\012\012\012\012",
  (unsigned char *)"\013\013\013\013\013\013\013\013\013\013\013",
  (unsigned char *)"\014\014\014\014\014\014\014\014\014\014\014\014",
  (unsigned char *)"\015\015\015\015\015\015\015\015\015\015\015\015\015",
  (unsigned char *)"\016\016\016\016\016\016\016\016\016\016\016\016\016\016",
  (unsigned char *)
    "\017\017\017\017\017\017\017\017\017\017\017\017\017\017\017",
  (unsigned char *)
    "\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020\020"
};

// инициализация MD2. Начинаем операцию MD2, записываем нов. контекст.

void MD2Init (MD2_CTX *context)                                                /* контекст */
{
  context->count = 0;
  MD2_memset ((POINTER)context->state, 0, sizeof (context->state));
  MD2_memset ((POINTER)context->checksum, 0, sizeof (context->checksum));
}

// MD2 block update operation.

void MD2Update (MD2_CTX *context, unsigned char *input, unsigned int inputLen) /* контекст, входной блок, длина входного блока */
{
  unsigned int i, index, partLen;

  /* Оновляем кол-во байт mod 16 */
  index = context->count;
  context->count = (index + inputLen) & 0xf;

  partLen = 16 - index;

  // Преобразуем столько раз,сколько возможно
  if (inputLen >= partLen) {
    MD2_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
    MD2Transform (context->state, context->checksum, context->buffer);

    for (i = partLen; i + 15 < inputLen; i += 16)
      MD2Transform (context->state, context->checksum, &input[i]);

    index = 0;
  }
  else
    i = 0;

  /* Помещаем в буфер ост. часть вх. сообщения */
  MD2_memcpy
    ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* Окончание MD2. Завершение операции преобразование,
записываем преобразованное сообщение и зануляем контекст.
 */
void MD2Final (unsigned char digest[16], MD2_CTX *context)
/* преобразованное сообщение */
/* контекст */
{
  unsigned int index, padLen;

  /* Pad out to multiple of 16.
   */
  index = context->count;
  padLen = 16 - index;
  MD2Update (context, PADDING_MD2[padLen], padLen);

  /* Extend with checksum */
  MD2Update (context, context->checksum, 16);

  /* Store state in digest */
  MD2_memcpy ((POINTER)digest, (POINTER)context->state, 16);

  /* Zeroize sensitive information.
   */
  MD2_memset ((POINTER)context, 0, sizeof (*context));
}

/* MD2 basic transformation. Transforms state and updates checksum
     based on block.
 */
static void MD2Transform (unsigned char state[16], unsigned char checksum[16], unsigned char block[16])
{
  unsigned int i, j, t;
  unsigned char x[48];

  /* Form encryption block from state, block, state ^ block.
   */
  for (i = 0; i < 16; i++) {
    x[i] = state[i];
    x[i+16] = block[i];
    x[i+32] = state[i] ^ block[i];
  }

  /* Encrypt block (18 rounds).
   */
  t = 0;
  for (i = 0; i < 18; i++) {
    for (j = 0; j < 48; j++)
      t = x[j] ^= PI_SUBST[t];
    t = (t + i) & 0xff;
  }

  /* Save new state */
  for (i = 0; i < 16; i++)
    state[i] = x[i];

  /* Update checksum.
   */
  t = checksum[15];
  for (i = 0; i < 16; i++)
    t = checksum[i] ^= PI_SUBST[block[i] ^ t];

  /* Zeroize sensitive information.
   */
  MD2_memset ((POINTER)x, 0, sizeof (x));
}

static void MD2_memcpy (POINTER output, POINTER input, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
    output[i] = input[i];
}

static void MD2_memset (POINTER output, int value, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
    ((char *)output)[i] = (char)value;
}
void MD2 (FILE *file, char buf[16])
{
    unsigned char buffer[1024], digest[16];
    int len;
    char buf1[16];
    MD2_CTX context_MD2;
    MD2Init (&context_MD2);
    while (len = fread (buffer, 1, 1024, file))
     MD2Update (&context_MD2, buffer, len);
    MD2Final (digest, &context_MD2);
    strcpy(buf,"");
    for (int i=0;i<16;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

void MD2_String (char *string, char buf[16])
{
    unsigned char buffer[1024], digest[16];
    int len;
    char buf1[16];
    MD2_CTX context_MD2;
    MD2Init (&context_MD2);
    len=strlen(string);
    MD2Update (&context_MD2, (POINTER)string, len);
    MD2Final (digest, &context_MD2);
    strcpy(buf,"");
    for (int i=0;i<16;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}
/*************************MD4***************************************/

/* Constants for MD4Transform routine.
 */

#define S11 3
#define S12 7
#define S13 11
#define S14 19
#define S21 3
#define S22 5
#define S23 9
#define S24 13
#define S31 3
#define S32 9
#define S33 11
#define S34 15

static void MD4Transform PROTO_LIST ((UINT4 [4], unsigned char [64]));
static void Encode_MD4 PROTO_LIST
  ((unsigned char *, UINT4 *, unsigned int));
static void Decode_MD4 PROTO_LIST
  ((UINT4 *, unsigned char *, unsigned int));
static void MD4_memcpy PROTO_LIST ((POINTER, POINTER, unsigned int));
static void MD4_memset PROTO_LIST ((POINTER, int, unsigned int));

static unsigned char PADDING_MD4[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G and H are basic MD4 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG and HH are transformations for rounds 1, 2 and 3 */
/* Rotation is separate from addition to prevent recomputation */

#define FF(a, b, c, d, x, s) { \
    (a) += F ((b), (c), (d)) + (x); \
    (a) = ROTATE_LEFT ((a), (s)); \
  }
#define GG(a, b, c, d, x, s) { \
    (a) += G ((b), (c), (d)) + (x) + (UINT4)0x5a827999; \
    (a) = ROTATE_LEFT ((a), (s)); \
  }
#define HH(a, b, c, d, x, s) { \
    (a) += H ((b), (c), (d)) + (x) + (UINT4)0x6ed9eba1; \
    (a) = ROTATE_LEFT ((a), (s)); \
  }

/* MD4 initialization. Begins an MD4 operation, writing a new context.
 */
void MD4Init (MD4_CTX *context)
/* контекст */
{
  context->count[0] = context->count[1] = 0;

  /* Load initialization constants.
   */
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

/* MD4 block update operation. Continues an MD4 message-digest
     operation, processing another message block, and updating the
     context.
 */
void MD4Update (MD4_CTX *context, unsigned char *input, unsigned int inputLen)
/* контекст */
/* входной блок */
/* длина входного блока */
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);
  /* Update number of bits */
  if ((context->count[0] += ((UINT4)inputLen << 3))
      < ((UINT4)inputLen << 3))
    context->count[1]++;
  context->count[1] += ((UINT4)inputLen >> 29);

  partLen = 64 - index;

  /* Transform as many times as possible.
   */
  if (inputLen >= partLen) {
    MD4_memcpy
      ((POINTER)&context->buffer[index], (POINTER)input, partLen);
    MD4Transform (context->state, context->buffer);

    for (i = partLen; i + 63 < inputLen; i += 64)
      MD4Transform (context->state, &input[i]);

    index = 0;
  }
  else
    i = 0;

  /* Buffer remaining input */
  MD4_memcpy
    ((POINTER)&context->buffer[index], (POINTER)&input[i],
     inputLen-i);
}

/* MD4 finalization. Ends an MD4 message-digest operation, writing the
     the message digest and zeroizing the context.
 */
void MD4Final (unsigned char digest[16], MD4_CTX *context)
/* преобразованное сообщение */
/* контекст */
{
  unsigned char bits[8];
  unsigned int index, padLen;

  /* Save number of bits */
  Encode_MD4 (bits, context->count, 8);

  /* Pad out to 56 mod 64.
   */
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD4Update (context, PADDING_MD4, padLen);

  /* Append length (before padding) */
  MD4Update (context, bits, 8);
  /* Store state in digest */
  Encode_MD4 (digest, context->state, 16);

  /* Zeroize sensitive information.
   */
  MD4_memset ((POINTER)context, 0, sizeof (*context));
}

/* MD4 basic transformation. Transforms state based on block.
 */
static void MD4Transform (UINT4 state[4], unsigned char block[64])
{
  UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  Decode_MD4 (x, block, 64);

  /* Round 1 */
  FF (a, b, c, d, x[ 0], S11); /* 1 */
  FF (d, a, b, c, x[ 1], S12); /* 2 */
  FF (c, d, a, b, x[ 2], S13); /* 3 */
  FF (b, c, d, a, x[ 3], S14); /* 4 */
  FF (a, b, c, d, x[ 4], S11); /* 5 */
  FF (d, a, b, c, x[ 5], S12); /* 6 */
  FF (c, d, a, b, x[ 6], S13); /* 7 */
  FF (b, c, d, a, x[ 7], S14); /* 8 */
  FF (a, b, c, d, x[ 8], S11); /* 9 */
  FF (d, a, b, c, x[ 9], S12); /* 10 */
  FF (c, d, a, b, x[10], S13); /* 11 */
  FF (b, c, d, a, x[11], S14); /* 12 */
  FF (a, b, c, d, x[12], S11); /* 13 */
  FF (d, a, b, c, x[13], S12); /* 14 */
  FF (c, d, a, b, x[14], S13); /* 15 */
  FF (b, c, d, a, x[15], S14); /* 16 */

  /* Round 2 */
  GG (a, b, c, d, x[ 0], S21); /* 17 */
  GG (d, a, b, c, x[ 4], S22); /* 18 */
  GG (c, d, a, b, x[ 8], S23); /* 19 */
  GG (b, c, d, a, x[12], S24); /* 20 */
  GG (a, b, c, d, x[ 1], S21); /* 21 */
  GG (d, a, b, c, x[ 5], S22); /* 22 */
  GG (c, d, a, b, x[ 9], S23); /* 23 */
  GG (b, c, d, a, x[13], S24); /* 24 */
  GG (a, b, c, d, x[ 2], S21); /* 25 */
  GG (d, a, b, c, x[ 6], S22); /* 26 */
  GG (c, d, a, b, x[10], S23); /* 27 */
  GG (b, c, d, a, x[14], S24); /* 28 */
  GG (a, b, c, d, x[ 3], S21); /* 29 */
  GG (d, a, b, c, x[ 7], S22); /* 30 */
  GG (c, d, a, b, x[11], S23); /* 31 */
  GG (b, c, d, a, x[15], S24); /* 32 */

  /* Round 3 */
  HH (a, b, c, d, x[ 0], S31); /* 33 */
  HH (d, a, b, c, x[ 8], S32); /* 34 */
  HH (c, d, a, b, x[ 4], S33); /* 35 */
  HH (b, c, d, a, x[12], S34); /* 36 */
  HH (a, b, c, d, x[ 2], S31); /* 37 */
  HH (d, a, b, c, x[10], S32); /* 38 */
  HH (c, d, a, b, x[ 6], S33); /* 39 */
  HH (b, c, d, a, x[14], S34); /* 40 */
  HH (a, b, c, d, x[ 1], S31); /* 41 */
  HH (d, a, b, c, x[ 9], S32); /* 42 */
  HH (c, d, a, b, x[ 5], S33); /* 43 */
  HH (b, c, d, a, x[13], S34); /* 44 */
  HH (a, b, c, d, x[ 3], S31); /* 45 */
  HH (d, a, b, c, x[11], S32); /* 46 */
  HH (c, d, a, b, x[ 7], S33); /* 47 */
  HH (b, c, d, a, x[15], S34); /* 48 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  /* Zeroize sensitive information.
   */
  MD4_memset((unsigned char *)x, 0, sizeof(x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
     a multiple of 4.
 */
static void Encode_MD4 (unsigned char *output, UINT4 *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
     a multiple of 4.
 */
static void Decode_MD4 (UINT4 *output, unsigned char *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
      (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}


static void MD4_memcpy (POINTER output, POINTER input, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
    output[i] = input[i];
}

static void MD4_memset (POINTER output, int value, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
    ((char *)output)[i] = (char)value;
}

void MD4 (FILE *file, char buf[16])
{
    unsigned char buffer[1024], digest[32];
    int len;
    char buf1[32];
    MD4_CTX context_MD4;
    MD4Init (&context_MD4);
    while (len = fread (buffer, 1, 1024, file))
     MD4Update (&context_MD4, buffer, len);
    MD4Final (digest, &context_MD4);

    strcpy(buf,"");
    for (int i=0;i<16;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

void MD4_String (char *string, char buf[16])
{
    unsigned char buffer[1024], digest[32];
    int len;
    char buf1[16];
    MD4_CTX context_MD4;
    MD4Init (&context_MD4);
    len=strlen(string);
    MD4Update (&context_MD4,(POINTER) string, len);
    MD4Final (digest, &context_MD4);

    strcpy(buf,"");
    for (int i=0;i<16;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

/**************************************MD5********************************/


/* Constants for MD5Transform routine.
 */
#undef S11
#undef S12
#undef S13
#undef S14
#undef S21
#undef S22
#undef S23
#undef S24
#undef S31
#undef S32
#undef S33
#undef S34

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static void MD5Transform PROTO_LIST ((UINT4 [4], unsigned char [64]));
static void Encode_MD5 PROTO_LIST ((unsigned char *, UINT4 *, unsigned int));
static void Decode_MD5 PROTO_LIST ((UINT4 *, unsigned char *, unsigned int));
static void MD5_memcpy PROTO_LIST ((POINTER, POINTER, unsigned int));
static void MD5_memset PROTO_LIST ((POINTER, int, unsigned int));

static unsigned char PADDING_MD5[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#undef G
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
   Rotation is separate from addition to prevent recomputation.
 */
#undef FF
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#undef GG
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#undef HH
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }

/* MD5 initialization. Begins an MD5 operation, writing a new context.
 */
void MD5Init (MD5_CTX *context)
/* контекст */
{
  context->count[0] = context->count[1] = 0;

  /* Load magic initialization constants.
   */
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest operation,
     processing another message block, and updating the context.
 */
void MD5Update (MD5_CTX *context, unsigned char *input, unsigned int inputLen)
/* контекст */
/* входной блок */
/* длина входного блока */
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);

  /* Update number of bits */
  if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
    context->count[1]++;
  context->count[1] += ((UINT4)inputLen >> 29);

  partLen = 64 - index;

  /* Transform as many times as possible.
   */
  if (inputLen >= partLen) {
    MD5_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
    MD5Transform (context->state, context->buffer);

    for (i = partLen; i + 63 < inputLen; i += 64)
      MD5Transform (context->state, &input[i]);

    index = 0;
  }
  else
    i = 0;

  /* Buffer remaining input */
  MD5_memcpy
    ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
     the message digest and zeroizing the context.
 */
void MD5Final (unsigned char digest[16], MD5_CTX *context)
/* message digest */
/* контекст */
{
  unsigned char bits[8];
  unsigned int index, padLen;

  /* Save number of bits */
  Encode_MD5 (bits, context->count, 8);

  /* Pad out to 56 mod 64.
   */
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD5Update (context, PADDING_MD5, padLen);

  /* Append length (before padding) */
  MD5Update (context, bits, 8);

  /* Store state in digest */
  Encode_MD5 (digest, context->state, 16);

  /* Zeroize sensitive information.
   */
  MD5_memset ((POINTER)context, 0, sizeof (*context));
}

/* MD5 basic transformation. Transforms state based on block.
 */
static void MD5Transform (UINT4 state[4], unsigned char block[64])
{
  UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  Decode_MD5 (x, block, 64);

  /* Round 1 */
  FF ( a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF ( d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF ( c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF ( b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF ( a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF ( d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF ( c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF ( b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF ( a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF ( d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF ( c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF ( b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF ( a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF ( d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF ( c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF ( b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

  /* Round 2 */
  GG ( a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG ( d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG ( c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG ( b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG ( a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG ( d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  GG ( c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG ( b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG ( a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG ( d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG ( c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG ( b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG ( a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG ( d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG ( c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG ( b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  HH ( a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH ( d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH ( c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH ( b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH ( a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH ( d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH ( c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH ( b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH ( a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH ( d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH ( c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH ( b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  HH ( a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH ( d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH ( c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH ( b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

  /* Round 4 */
  II ( a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II ( d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II ( c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II ( b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II ( a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II ( d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II ( c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II ( b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II ( a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II ( d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II ( c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II ( b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II ( a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II ( d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II ( c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II ( b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  /* Zeroize sensitive information.
   */
  MD5_memset ((POINTER)x, 0, sizeof (x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
     a multiple of 4.
 */
static void Encode_MD5 (unsigned char *output, UINT4 *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
     a multiple of 4.
 */
static void Decode_MD5 (UINT4 *output, unsigned char *input, unsigned int len)
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
      (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}

static void MD5_memcpy (POINTER output, POINTER input, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
    output[i] = input[i];
}

static void MD5_memset (POINTER output, int value, unsigned int len)
{
  unsigned int i;

  for (i = 0; i < len; i++)
    ((char *)output)[i] = (char)value;
}

void MD5 (FILE *file, char buf[32])
{
    unsigned char buffer[1024], digest[32];
    int len;
    char buf1[32];
    MD5_CTX context_MD5;
    MD5Init (&context_MD5);
    while (len = fread (buffer, 1, 1024, file))
     MD5Update (&context_MD5, buffer, len);
    MD5Final (digest, &context_MD5);

    strcpy(buf,"");
    for (int i=0;i<32;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

void MD5_String (char *string, char buf[16])
{
    unsigned char digest[32];
    int len;
    char buf1[16];
    MD5_CTX context_MD5;
    MD5Init (&context_MD5);
    len=strlen(string);
     MD5Update (&context_MD5,(POINTER) string, len);
    MD5Final (digest, &context_MD5);

    strcpy(buf,"");
    for (int i=0;i<16;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

/*********************************************************SHA1*******************************************************/


#define rol(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

/* blk0() and blk() perform the initial expand. */

#ifdef LITTLE_ENDIAN
#define blk0(i) (block->l[i] = (rol(block->l[i],24)&0xFF00FF00) \
    |(rol(block->l[i],8)&0x00FF00FF))
#else
#define blk0(i) block->l[i]
#endif
#define blk(i) (block->l[i&15] = rol(block->l[(i+13)&15]^block->l[(i+8)&15] \
    ^block->l[(i+2)&15]^block->l[i&15],1))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk0(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);
#define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
#define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);
#define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);


/* Hash a single 512-bit block. This is the core of the algorithm. */

void SHA1Transform(unsigned long state[5], unsigned char buffer[64])
{
unsigned long a, b, c, d, e;
typedef union {
    unsigned char c[64];
    unsigned long l[16];
} CHAR64LONG16;
CHAR64LONG16* block;
#ifdef SHA1HANDSOFF
static unsigned char workspace[64];
    block = (CHAR64LONG16*)workspace;
    memcpy(block, buffer, 64);
#else
    block = (CHAR64LONG16*)buffer;
#endif
    /* Copy context->state[] to working vars */
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    /* 4 rounds of 20 operations each. Loop unrolled. */
    R0(a,b,c,d,e, 0); R0(e,a,b,c,d, 1); R0(d,e,a,b,c, 2); R0(c,d,e,a,b, 3);
    R0(b,c,d,e,a, 4); R0(a,b,c,d,e, 5); R0(e,a,b,c,d, 6); R0(d,e,a,b,c, 7);
    R0(c,d,e,a,b, 8); R0(b,c,d,e,a, 9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);
    R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);
    R1(e,a,b,c,d,16); R1(d,e,a,b,c,17); R1(c,d,e,a,b,18); R1(b,c,d,e,a,19);
    R2(a,b,c,d,e,20); R2(e,a,b,c,d,21); R2(d,e,a,b,c,22); R2(c,d,e,a,b,23);
    R2(b,c,d,e,a,24); R2(a,b,c,d,e,25); R2(e,a,b,c,d,26); R2(d,e,a,b,c,27);
    R2(c,d,e,a,b,28); R2(b,c,d,e,a,29); R2(a,b,c,d,e,30); R2(e,a,b,c,d,31);
    R2(d,e,a,b,c,32); R2(c,d,e,a,b,33); R2(b,c,d,e,a,34); R2(a,b,c,d,e,35);
    R2(e,a,b,c,d,36); R2(d,e,a,b,c,37); R2(c,d,e,a,b,38); R2(b,c,d,e,a,39);
    R3(a,b,c,d,e,40); R3(e,a,b,c,d,41); R3(d,e,a,b,c,42); R3(c,d,e,a,b,43);
    R3(b,c,d,e,a,44); R3(a,b,c,d,e,45); R3(e,a,b,c,d,46); R3(d,e,a,b,c,47);
    R3(c,d,e,a,b,48); R3(b,c,d,e,a,49); R3(a,b,c,d,e,50); R3(e,a,b,c,d,51);
    R3(d,e,a,b,c,52); R3(c,d,e,a,b,53); R3(b,c,d,e,a,54); R3(a,b,c,d,e,55);
    R3(e,a,b,c,d,56); R3(d,e,a,b,c,57); R3(c,d,e,a,b,58); R3(b,c,d,e,a,59);
    R4(a,b,c,d,e,60); R4(e,a,b,c,d,61); R4(d,e,a,b,c,62); R4(c,d,e,a,b,63);
    R4(b,c,d,e,a,64); R4(a,b,c,d,e,65); R4(e,a,b,c,d,66); R4(d,e,a,b,c,67);
    R4(c,d,e,a,b,68); R4(b,c,d,e,a,69); R4(a,b,c,d,e,70); R4(e,a,b,c,d,71);
    R4(d,e,a,b,c,72); R4(c,d,e,a,b,73); R4(b,c,d,e,a,74); R4(a,b,c,d,e,75);
    R4(e,a,b,c,d,76); R4(d,e,a,b,c,77); R4(c,d,e,a,b,78); R4(b,c,d,e,a,79);
    /* Add the working vars back into context.state[] */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    /* Wipe variables */
    a = b = c = d = e = 0;
}


/* SHA1Init - Initialize new context */

void SHA1Init(SHA1_CTX* context)
{
    /* SHA1 initialization constants */
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
    context->count[0] = context->count[1] = 0;
}


/* Run your data through this. */

void SHA1Update(SHA1_CTX* context, unsigned char* data, unsigned int len)
{
unsigned int i, j;

    j = (context->count[0] >> 3) & 63;
    if ((context->count[0] += len << 3) < (len << 3)) context->count[1]++;
    context->count[1] += (len >> 29);
    if ((j + len) > 63) {
        memcpy(&context->buffer[j], data, (i = 64-j));
        SHA1Transform(context->state, context->buffer);
        for ( ; i + 63 < len; i += 64) {
            SHA1Transform(context->state, &data[i]);
        }
        j = 0;
    }
    else i = 0;
    memcpy(&context->buffer[j], &data[i], len - i);
}


/* Add padding and return the message digest. */

void SHA1Final(unsigned char digest[20], SHA1_CTX* context)
{
unsigned long i, j;
unsigned char finalcount[8];

    for (i = 0; i < 8; i++) {
        finalcount[i] = (unsigned char)((context->count[(i >= 4 ? 0 : 1)]
         >> ((3-(i & 3)) * 8) ) & 255);  /* Endian independent */
    }
    SHA1Update(context, (unsigned char *)"\200", 1);
    while ((context->count[0] & 504) != 448) {
        SHA1Update(context, (unsigned char *)"\0", 1);
    }
    SHA1Update(context, finalcount, 8);  /* Should cause a SHA1Transform() */
    for (i = 0; i < 20; i++) {
        digest[i] = (unsigned char)
         ((context->state[i>>2] >> ((3-(i & 3)) * 8) ) & 255);
    }
    /* Wipe variables */
    i = j = 0;
    memset(context->buffer, 0, 64);
    memset(context->state, 0, 20);
    memset(context->count, 0, 8);
    memset(&finalcount, 0, 8);
#ifdef SHA1HANDSOFF  /* make SHA1Transform overwrite it's own static vars */
    SHA1Transform(context->state, context->buffer);
#endif
}


void SHA1 (FILE *file, char buf[20])
{
    unsigned char digest[20], buffer[16384];
    int len;
    char buf1[20];
    SHA1_CTX context_SHA1;
    SHA1Init (&context_SHA1);
    while (len = fread (buffer, 1, 16384, file))
     SHA1Update (&context_SHA1, buffer, len);
    SHA1Final (digest, &context_SHA1);

    strcpy(buf,"");
   for (int i=0;i<20;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}


void SHA1_String (char *string, char buf[20])
{
    unsigned char digest[20], buffer[16384];
    int len;
    char buf1[20];
    SHA1_CTX context_SHA1;
    SHA1Init (&context_SHA1);
    len=strlen(string);
     SHA1Update (&context_SHA1,(POINTER) string, len);
    SHA1Final (digest, &context_SHA1);

    strcpy(buf,"");
   for (int i=0;i<20;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

/****************************************GOST************************************/

/* lookup tables : each of these has two rotated 4-bit S-Boxes */

unsigned long gost_sbox_1[256];
unsigned long gost_sbox_2[256];
unsigned long gost_sbox_3[256];
unsigned long gost_sbox_4[256];

/* initialize the lookup tables */

void gosthash_init()
{
  int a, b, i;
  unsigned long ax, bx, cx, dx;

  /* 4-bit S-Boxes */

  unsigned long sbox[8][16] =
    {
	{  4, 10,  9,  2, 13,  8,  0, 14,  6, 11,  1, 12,  7, 15,  5,  3 },
	{ 14, 11,  4, 12,  6, 13, 15, 10,  2,  3,  8,  1,  0,  7,  5,  9 },
	{  5,  8,  1, 13, 10,  3,  4,  2, 14, 15, 12,  7,  6,  0,  9, 11 },
	{  7, 13, 10,  1,  0,  8,  9, 15, 14,  4,  6, 12, 11,  2,  5,  3 },
	{  6, 12,  7,  1,  5, 15, 13,  8,  4, 10,  9, 14,  0,  3, 11,  2 },
	{  4, 11, 10,  0,  7,  2,  1, 13,  3,  6,  8,  5,  9, 12, 15, 14 },
	{ 13, 11,  4,  1,  3, 15,  5,  9,  0, 10, 14,  7,  6,  8,  2, 12 },
	{  1, 15, 13,  0,  5,  7, 10,  4,  9,  2,  3, 14,  6, 11,  8, 12 }
    };

  /* s-box precomputation */

  i = 0;
  for (a = 0; a < 16; a++)
    {
      ax = sbox[1][a] << 15;
      bx = sbox[3][a] << 23;
      cx = sbox[5][a];
      cx = (cx >> 1) | (cx << 31);
      dx = sbox[7][a] << 7;

      for (b = 0; b < 16; b++)
	{
	  gost_sbox_1[i] = ax | (sbox[0][b] << 11);
	  gost_sbox_2[i] = bx | (sbox[2][b] << 19);
	  gost_sbox_3[i] = cx | (sbox[4][b] << 27);
	  gost_sbox_4[i++] = dx | (sbox[6][b] << 3);
	}
    }
}

/*
 *  A macro that performs a full encryption round of GOST 28147-89.
 *  Temporary variable t assumed and variables r and l for left and right
 *  blocks
 */

#define GOST_ENCRYPT_ROUND(k1, k2) \
t = (k1) + r; \
l ^= gost_sbox_1[t & 0xff] ^ gost_sbox_2[(t >> 8) & 0xff] ^ \
gost_sbox_3[(t >> 16) & 0xff] ^ gost_sbox_4[t >> 24]; \
t = (k2) + l; \
r ^= gost_sbox_1[t & 0xff] ^ gost_sbox_2[(t >> 8) & 0xff] ^ \
gost_sbox_3[(t >> 16) & 0xff] ^ gost_sbox_4[t >> 24]; \

/* encrypt a block with the given key */

#define GOST_ENCRYPT(key) \
GOST_ENCRYPT_ROUND(key[0], key[1]) \
GOST_ENCRYPT_ROUND(key[2], key[3]) \
GOST_ENCRYPT_ROUND(key[4], key[5]) \
GOST_ENCRYPT_ROUND(key[6], key[7]) \
GOST_ENCRYPT_ROUND(key[0], key[1]) \
GOST_ENCRYPT_ROUND(key[2], key[3]) \
GOST_ENCRYPT_ROUND(key[4], key[5]) \
GOST_ENCRYPT_ROUND(key[6], key[7]) \
GOST_ENCRYPT_ROUND(key[0], key[1]) \
GOST_ENCRYPT_ROUND(key[2], key[3]) \
GOST_ENCRYPT_ROUND(key[4], key[5]) \
GOST_ENCRYPT_ROUND(key[6], key[7]) \
GOST_ENCRYPT_ROUND(key[7], key[6]) \
GOST_ENCRYPT_ROUND(key[5], key[4]) \
GOST_ENCRYPT_ROUND(key[3], key[2]) \
GOST_ENCRYPT_ROUND(key[1], key[0]) \
t = r; \
r = l; \
l = t;

/*
 *  "chi" compression function. the result is stored over h
 */

void gosthash_compress(unsigned long *h, unsigned long *m)
{
  int i;
  unsigned long l, r, t, key[8], u[8], v[8], w[8], s[8];

  memcpy(u, h, sizeof(u));
  memcpy(v, m, sizeof(u));

  for (i = 0; i < 8; i += 2)
    {
      w[0] = u[0] ^ v[0];	       /* w = u xor v */
      w[1] = u[1] ^ v[1];
      w[2] = u[2] ^ v[2];
      w[3] = u[3] ^ v[3];
      w[4] = u[4] ^ v[4];
      w[5] = u[5] ^ v[5];
      w[6] = u[6] ^ v[6];
      w[7] = u[7] ^ v[7];

      /* P-Transformation */

      key[0] = (w[0]  & 0x000000ff) | ((w[2] & 0x000000ff) << 8) |
	((w[4] & 0x000000ff) << 16) | ((w[6] & 0x000000ff) << 24);
      key[1] = ((w[0] & 0x0000ff00) >> 8)  | (w[2]  & 0x0000ff00) |
	((w[4] & 0x0000ff00) << 8) | ((w[6] & 0x0000ff00) << 16);
      key[2] = ((w[0] & 0x00ff0000) >> 16) | ((w[2] & 0x00ff0000) >> 8) |
	(w[4] & 0x00ff0000) | ((w[6] & 0x00ff0000) << 8);
      key[3] = ((w[0] & 0xff000000) >> 24) | ((w[2] & 0xff000000) >> 16) |
	((w[4] & 0xff000000) >> 8) | (w[6] & 0xff000000);
      key[4] = (w[1] & 0x000000ff) | ((w[3] & 0x000000ff) << 8) |
	((w[5] & 0x000000ff) << 16) | ((w[7] & 0x000000ff) << 24);
      key[5] = ((w[1] & 0x0000ff00) >> 8) | (w[3]  & 0x0000ff00) |
	((w[5] & 0x0000ff00) << 8) | ((w[7] & 0x0000ff00) << 16);
      key[6] = ((w[1] & 0x00ff0000) >> 16) | ((w[3] & 0x00ff0000) >> 8) |
	(w[5] & 0x00ff0000) | ((w[7] & 0x00ff0000) << 8);
      key[7] = ((w[1] & 0xff000000) >> 24) | ((w[3] & 0xff000000) >> 16) |
	((w[5] & 0xff000000) >> 8) | (w[7] & 0xff000000);

      r = h[i];			       /* encriphering transformation */
      l = h[i + 1];
      GOST_ENCRYPT(key);

      s[i] = r;
      s[i + 1] = l;

      if (i == 6)
	break;

      l = u[0] ^ u[2];		       /* U = A(U) */
      r = u[1] ^ u[3];
      u[0] = u[2];
      u[1] = u[3];
      u[2] = u[4];
      u[3] = u[5];
      u[4] = u[6];
      u[5] = u[7];
      u[6] = l;
      u[7] = r;

      if (i == 2)		       /* Constant C_3 */
	{
	  u[0] ^= 0xff00ff00;
	  u[1] ^= 0xff00ff00;
	  u[2] ^= 0x00ff00ff;
	  u[3] ^= 0x00ff00ff;
	  u[4] ^= 0x00ffff00;
	  u[5] ^= 0xff0000ff;
	  u[6] ^= 0x000000ff;
	  u[7] ^= 0xff00ffff;
	}

      l = v[0];			       /* V = A(A(V)) */
      r = v[2];
      v[0] = v[4];
      v[2] = v[6];
      v[4] = l ^ r;
      v[6] = v[0] ^ r;
      l = v[1];
      r = v[3];
      v[1] = v[5];
      v[3] = v[7];
      v[5] = l ^ r;
      v[7] = v[1] ^ r;
    }

  /* 12 rounds of the LFSR (computed from a product matrix) and xor in M */

  u[0] = m[0] ^ s[6];
  u[1] = m[1] ^ s[7];
  u[2] = m[2] ^ (s[0] << 16) ^ (s[0] >> 16) ^ (s[0] & 0xffff) ^
    (s[1] & 0xffff) ^ (s[1] >> 16) ^ (s[2] << 16) ^ s[6] ^ (s[6] << 16) ^
    (s[7] & 0xffff0000) ^ (s[7] >> 16);
  u[3] = m[3] ^ (s[0] & 0xffff) ^ (s[0] << 16) ^ (s[1] & 0xffff) ^
    (s[1] << 16) ^ (s[1] >> 16) ^ (s[2] << 16) ^ (s[2] >> 16) ^
    (s[3] << 16) ^ s[6] ^ (s[6] << 16) ^ (s[6] >> 16) ^ (s[7] & 0xffff) ^
    (s[7] << 16) ^ (s[7] >> 16);
  u[4] = m[4] ^
    (s[0] & 0xffff0000) ^ (s[0] << 16) ^ (s[0] >> 16) ^
    (s[1] & 0xffff0000) ^ (s[1] >> 16) ^ (s[2] << 16) ^ (s[2] >> 16) ^
    (s[3] << 16) ^ (s[3] >> 16) ^ (s[4] << 16) ^ (s[6] << 16) ^
    (s[6] >> 16) ^(s[7] & 0xffff) ^ (s[7] << 16) ^ (s[7] >> 16);
  u[5] = m[5] ^ (s[0] << 16) ^ (s[0] >> 16) ^ (s[0] & 0xffff0000) ^
    (s[1] & 0xffff) ^ s[2] ^ (s[2] >> 16) ^ (s[3] << 16) ^ (s[3] >> 16) ^
    (s[4] << 16) ^ (s[4] >> 16) ^ (s[5] << 16) ^  (s[6] << 16) ^
    (s[6] >> 16) ^ (s[7] & 0xffff0000) ^ (s[7] << 16) ^ (s[7] >> 16);
  u[6] = m[6] ^ s[0] ^ (s[1] >> 16) ^ (s[2] << 16) ^ s[3] ^ (s[3] >> 16) ^
    (s[4] << 16) ^ (s[4] >> 16) ^ (s[5] << 16) ^ (s[5] >> 16) ^ s[6] ^
    (s[6] << 16) ^ (s[6] >> 16) ^ (s[7] << 16);
  u[7] = m[7] ^ (s[0] & 0xffff0000) ^ (s[0] << 16) ^ (s[1] & 0xffff) ^
    (s[1] << 16) ^ (s[2] >> 16) ^ (s[3] << 16) ^ s[4] ^ (s[4] >> 16) ^
    (s[5] << 16) ^ (s[5] >> 16) ^ (s[6] >> 16) ^ (s[7] & 0xffff) ^
    (s[7] << 16) ^ (s[7] >> 16);

  /* 16 * 1 round of the LFSR and xor in H */

  v[0] = h[0] ^ (u[1] << 16) ^ (u[0] >> 16);
  v[1] = h[1] ^ (u[2] << 16) ^ (u[1] >> 16);
  v[2] = h[2] ^ (u[3] << 16) ^ (u[2] >> 16);
  v[3] = h[3] ^ (u[4] << 16) ^ (u[3] >> 16);
  v[4] = h[4] ^ (u[5] << 16) ^ (u[4] >> 16);
  v[5] = h[5] ^ (u[6] << 16) ^ (u[5] >> 16);
  v[6] = h[6] ^ (u[7] << 16) ^ (u[6] >> 16);
  v[7] = h[7] ^ (u[0] & 0xffff0000) ^ (u[0] << 16) ^ (u[7] >> 16) ^
    (u[1] & 0xffff0000) ^ (u[1] << 16) ^ (u[6] << 16) ^ (u[7] & 0xffff0000);

  /* 61 rounds of LFSR, mixing up h (computed from a product matrix) */

  h[0] = (v[0] & 0xffff0000) ^ (v[0] << 16) ^ (v[0] >> 16) ^ (v[1] >> 16) ^
    (v[1] & 0xffff0000) ^ (v[2] << 16) ^ (v[3] >> 16) ^ (v[4] << 16) ^
    (v[5] >> 16) ^ v[5] ^ (v[6] >> 16) ^ (v[7] << 16) ^ (v[7] >> 16) ^
    (v[7] & 0xffff);
  h[1] = (v[0] << 16) ^ (v[0] >> 16) ^ (v[0] & 0xffff0000) ^ (v[1] & 0xffff) ^
    v[2] ^ (v[2] >> 16) ^ (v[3] << 16) ^ (v[4] >> 16) ^ (v[5] << 16) ^
    (v[6] << 16) ^ v[6] ^ (v[7] & 0xffff0000) ^ (v[7] >> 16);
  h[2] = (v[0] & 0xffff) ^ (v[0] << 16) ^ (v[1] << 16) ^ (v[1] >> 16) ^
    (v[1] & 0xffff0000) ^ (v[2] << 16) ^ (v[3] >> 16) ^ v[3] ^ (v[4] << 16) ^
    (v[5] >> 16) ^ v[6] ^ (v[6] >> 16) ^ (v[7] & 0xffff) ^ (v[7] << 16) ^
    (v[7] >> 16);
  h[3] = (v[0] << 16) ^ (v[0] >> 16) ^ (v[0] & 0xffff0000) ^
    (v[1] & 0xffff0000) ^ (v[1] >> 16) ^ (v[2] << 16) ^ (v[2] >> 16) ^ v[2] ^
    (v[3] << 16) ^ (v[4] >> 16) ^ v[4] ^ (v[5] << 16) ^ (v[6] << 16) ^
    (v[7] & 0xffff) ^ (v[7] >> 16);
  h[4] = (v[0] >> 16) ^ (v[1] << 16) ^ v[1] ^ (v[2] >> 16) ^ v[2] ^
    (v[3] << 16) ^ (v[3] >> 16) ^ v[3] ^ (v[4] << 16) ^ (v[5] >> 16) ^
    v[5] ^ (v[6] << 16) ^ (v[6] >> 16) ^ (v[7] << 16);
  h[5] = (v[0] << 16) ^ (v[0] & 0xffff0000) ^ (v[1] << 16) ^ (v[1] >> 16) ^
    (v[1] & 0xffff0000) ^ (v[2] << 16) ^ v[2] ^ (v[3] >> 16) ^ v[3] ^
    (v[4] << 16) ^ (v[4] >> 16) ^ v[4] ^ (v[5] << 16) ^ (v[6] << 16) ^
    (v[6] >> 16) ^ v[6] ^ (v[7] << 16) ^ (v[7] >> 16) ^ (v[7] & 0xffff0000);
  h[6] = v[0] ^ v[2] ^ (v[2] >> 16) ^ v[3] ^ (v[3] << 16) ^ v[4] ^
    (v[4] >> 16) ^ (v[5] << 16) ^ (v[5] >> 16) ^ v[5] ^ (v[6] << 16) ^
    (v[6] >> 16) ^ v[6] ^ (v[7] << 16) ^ v[7];
  h[7] = v[0] ^ (v[0] >> 16) ^ (v[1] << 16) ^ (v[1] >> 16) ^ (v[2] << 16) ^
    (v[3] >> 16) ^ v[3] ^ (v[4] << 16) ^ v[4] ^ (v[5] >> 16) ^ v[5] ^
    (v[6] << 16) ^ (v[6] >> 16) ^ (v[7] << 16) ^ v[7];
}

/* Clear the state of the given context structure. */

void gosthash_reset(GostHashCtx *ctx)
{
  memset(ctx->sum, 0, 32);
  memset(ctx->hash, 0, 32);
  memset(ctx->len, 0, 32);
  memset(ctx->partial, 0, 32);
  ctx->partial_bytes = 0;
}

/* Mix in a 32-byte chunk ("stage 3") */

void gosthash_bytes(GostHashCtx *ctx, const unsigned char *buf, size_t bits)
{
  int i, j;
  unsigned long a, c, m[8];

  /* convert bytes to a long words and compute the sum */

  j = 0;
  c = 0;
  for (i = 0; i < 8; i++)
    {
      a = ((unsigned long) buf[j]) |
	(((unsigned long) buf[j + 1]) << 8) |
	(((unsigned long) buf[j + 2]) << 16) |
	(((unsigned long) buf[j + 3]) << 24);
      j += 4;
      m[i] = a;
      c = a + c + ctx->sum[i];
      ctx->sum[i] = c;
      c = c < a ? 1 : 0;
    }

  /* compress */

  gosthash_compress(ctx->hash, m);

  /* a 64-bit counter should be sufficient */

  ctx->len[0] += bits;
  if (ctx->len[0] < bits)
    ctx->len[1]++;
}

/* Mix in len bytes of data for the given buffer. */

void gosthash_update(GostHashCtx *ctx, const unsigned char *buf, size_t len)
{
  size_t i, j;

  i = ctx->partial_bytes;
  j = 0;
  while (i < 32 && j < len)
    ctx->partial[i++] = buf[j++];

  if (i < 32)
    {
      ctx->partial_bytes = i;
      return;
    }
  gosthash_bytes(ctx, ctx->partial, 256);

  while ((j + 32) < len)
    {
      gosthash_bytes(ctx, &buf[j], 256);
      j += 32;
    }

  i = 0;
  while (j < len)
    ctx->partial[i++] = buf[j++];
  ctx->partial_bytes = i;
}


/* Compute and save the 32-byte digest. */

void gosthash_final(GostHashCtx *ctx, unsigned char *digest)
{
  int i, j;
  unsigned long a;

  /* adjust and mix in the last chunk */

  if (ctx->partial_bytes > 0)
    {
      memset(&ctx->partial[ctx->partial_bytes], 0, 32 - ctx->partial_bytes);
      gosthash_bytes(ctx, ctx->partial, ctx->partial_bytes << 3);
    }

  /* mix in the length and the sum */

  gosthash_compress(ctx->hash, ctx->len);
  gosthash_compress(ctx->hash, ctx->sum);

  /* convert the output to bytes */

  j = 0;
  for (i = 0; i < 8; i++)
    {
      a = ctx->hash[i];
      digest[j] = (unsigned char) a;
      digest[j + 1] = (unsigned char) (a >> 8);
      digest[j + 2] = (unsigned char) (a >> 16);
      digest[j + 3] = (unsigned char) (a >> 24);
      j += 4;
    }
}

void gosthash (FILE *file, char buf[32])
{
    unsigned char buffer[1024], digest[32];
    int len;
    char buf1[32];
    GostHashCtx hash;
    gosthash_init();
    gosthash_reset(&hash);
    while (len = fread (buffer, 1, 1024, file))
     gosthash_update(&hash, buffer, len);
    gosthash_final(&hash, digest);

    strcpy(buf,"");
    for (int i=0;i<32;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

void gosthash_String (char *string, char buf[32])
{
    unsigned char digest[32];
    int len;
    char buf1[32];
    GostHashCtx hash;
    gosthash_init();
    gosthash_reset(&hash);
    len=strlen(string);
    gosthash_update(&hash, (POINTER)string, len);
    gosthash_final(&hash, digest);

    strcpy(buf,"");
    for (int i=0;i<32;i++)
    {
     sprintf(buf1,"%02x",digest[i]);
     strcat(buf,buf1);
    }
}

/***************************************************CRC32B***********************/


unsigned long crcTable[256];


unsigned long getcrc( FILE *fp )
{
	register unsigned long crc;
	int c;

	crc = 0xFFFFFFFF;
	while( (c=getc(fp)) != EOF ) {
		crc = ((crc>>8) & 0x00FFFFFF) ^ crcTable[ (crc^c) & 0xFF ];
	}
	return( crc^0xFFFFFFFF );
}

unsigned long getcrc_string( char *string )
{
	register unsigned long crc;
	int c;
         char q;
	crc = 0xFFFFFFFF;
        int i=0;
        int len=strlen(string);
	while( i!=len )
        {
                q=string[i];
                i++;
                 c=q;
               //  c=c-48;
		crc = ((crc>>8) & 0x00FFFFFF) ^ crcTable[ (crc^c) & 0xFF ];
	}
	return( crc^0xFFFFFFFF );
}

void crcgen( )
{
	unsigned long	crc, poly;
	int	i, j;

	poly = 0xEDB88320L;
	for (i=0; i<256; i++) {
		crc = i;
		for (j=8; j>0; j--) {
			if (crc&1) {
				crc = (crc >> 1) ^ poly;
			} else {
				crc >>= 1;
			}
		}
		crcTable[i] = crc;
	}
}

void CRC32B (FILE *file, char buf[32])
{
     unsigned long crc;
     crcgen();
     crc = getcrc(file);

     sprintf(buf,"%08lx",crc);
}

void CRC32B_String (char *string, char buf[32])
{
     unsigned long crc;
     crcgen();
     crc = getcrc_string(string);

     sprintf(buf,"%08lx",crc);
}


