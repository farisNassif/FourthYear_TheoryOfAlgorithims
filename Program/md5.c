// Author :     Faris Nassif
// Module :     Theory Of Algorithms
// Summary:     A program that executes a MD5 Hash on a given input
//              This program has been adapted based on the process outlined in https://tools.ietf.org/html/rfc1321

#include <stdio.h> // Input/Output
#include <stdint.h> // Req for uint(x) unsigned int
#include <inttypes.h> // Includes formatters for output

/* 
    https://tools.ietf.org/html/rfc1321 => Page 2

    Definitions of a Word and Byte
*/
#define WORD uint32_t
#define BYTE uint8_t

/* 
    https://tools.ietf.org/html/rfc1321 => Page 10

    Predefined constants for the MD5 Transform routine
*/
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

/*
    [Rotate Function]
    =>  Rotates (x) left by (n) bits
*/
#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

/* 
    https://tools.ietf.org/html/rfc1321 => Page 4
    http://www.boblandstrom.com/the-md5-hashing-algorithm/

    Auxillary function definitions. Each recieve three 'Words'
    and produce one 'Word' as their output
*/
#define F(X,Y,Z) = ((x & y) | (~x & z)) // XY v not(X) Z
#define G(X,Y,Z) = ((x & z) | (y & ~z)) // XZ v Y not(Z)
#define H(X,Y,Z) = (x ^ y ^ z)          // X xor Y xor Z
#define I(X,Y,Z) = (y ^ (x | ~z))       // Y xor (X v not(Z))

/* 
    https://tools.ietf.org/html/rfc1321 => Page 10

    [FF, GG, HH, II] => Transformations for rounds 1, 2, 3, and 4
    The first 4 Paramaters for each function are the four 16 bit Words
    The fifth Paramater consists of the union message
    The sixth Paramater contains one of the constants for the MD5 transform
    The final Paramater is the corresponding constant T defined below
*/
#define FF(a,b,c,d,m,s,t) { a += F(b,c,d) + m + t; a = b + ROTL(a,s); }
#define GG(a,b,c,d,m,s,t) { a += G(b,c,d) + m + t; a = b + ROTL(a,s); }
#define HH(a,b,c,d,m,s,t) { a += H(b,c,d) + m + t; a = b + ROTL(a,s); }
#define II(a,b,c,d,m,s,t) { a += I(b,c,d) + m + t; a = b + ROTL(a,s); }


/*
    https://tools.ietf.org/html/rfc1321 => Page 13 and 14

    Predefined hashing constants required for MD5
*/
const WORD T[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

/* 
    https://tools.ietf.org/html/rfc1321 => Page 4

    Four word buffer initialized with hex values used in the Message Digest computation
*/
WORD A = 0x67452301;
WORD B = 0xefcdab89;
WORD C = 0x98badcfe;
WORD D = 0x10325476;


