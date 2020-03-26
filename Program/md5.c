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
#define F(x,y,z) ((x & y) | (~x & z)) // XY v not(X) Z
#define G(x,y,z) ((x & z) | (y & ~z)) // XZ v Y not(Z)
#define H(x,y,z) (x ^ y ^ z)          // X xor Y xor Z
#define I(x,y,z) (y ^ (x | ~z))       // Y xor (X v not(Z))

/* 
    https://tools.ietf.org/html/rfc1321 => Page 10
    [FF, GG, HH, II] => Transformations for rounds 1, 2, 3, and 4
    The first 4 Paramaters for each function are the four 16 bit Words
    The fifth Paramater consists of the union block message (Input for MD5 is 64 bytes / 16 x 32 bit)
    The sixth Paramater contains one of the constants for the MD5 transform (SXX)
    The final Paramater is the corresponding constant T defined below
*/
#define FF(a,b,c,d,m,s,t) { a += F(b,c,d) + m + t; a = b + ROTL(a,s); }
#define GG(a,b,c,d,m,s,t) { a += G(b,c,d) + m + t; a = b + ROTL(a,s); }
#define HH(a,b,c,d,m,s,t) { a += H(b,c,d) + m + t; a = b + ROTL(a,s); }
#define II(a,b,c,d,m,s,t) { a += I(b,c,d) + m + t; a = b + ROTL(a,s); }

/*
    https://tools.ietf.org/html/rfc1321 => Page 13 and 14

    Predefined hashing constants required for MD5
    Integer part of the sines of integers (in radians) * 2^32
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
    https://tools.ietf.org/html/rfc1321 => Page 10

    Predefined constants for the MD5 Transform routine
    Specifies the per-round shift amounts
*/
const WORD S[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

/* 
    https://tools.ietf.org/html/rfc1321 => Page 4

    Four 'Word' buffer initialized with hex values used in the Message Digest computation
*/
WORD A = 0x67452301;
WORD B = 0xefcdab89;
WORD C = 0x98badcfe;
WORD D = 0x10325476;

/*
    All union members will share the same memory location
    Different definitions depending on bit impelemtation

    Kind of an interface allowing the use of specific memory adresses.
    Takes up 64 bytes altogether
*/
typedef union { 
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
} BLOCK;

/*
    Status controller when reading the pad file

    READ: Still reading file, not EOF
    PAD0: Already started padding some 0's
    Finish: Finished all padding
*/
typedef enum {
    READ, 
    PAD0, 
    FINISH 
} PADFLAG;

/* ----------------------- MD5 Implementation ------------------------ */
void md5(BLOCK *M, uint32_t *H) {
    WORD a, b, c, d;
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];

    /* Round 1 */
    FF(H[0], H[1], H[2], H[3], M->threetwo[0] , S[0] , T[0]) ; /*  1 */
    FF(H[3], H[0], H[1], H[2], M->threetwo[1] , S[1] , T[1]) ; /*  2 */
    FF(H[2], H[3], H[0], H[1], M->threetwo[2] , S[2] , T[2]) ; /*  3 */
    FF(H[1], H[2], H[3], H[0], M->threetwo[3] , S[3] , T[3]) ; /*  4 */
    FF(H[0], H[1], H[2], H[3], M->threetwo[4] , S[4] , T[4]) ; /*  5 */
    FF(H[3], H[0], H[1], H[2], M->threetwo[5] , S[5] , T[5]) ; /*  6 */
    FF(H[2], H[3], H[0], H[1], M->threetwo[6] , S[6] , T[6]) ; /*  7 */
    FF(H[1], H[2], H[3], H[0], M->threetwo[7] , S[7] , T[7]) ; /*  8 */
    FF(H[0], H[1], H[2], H[3], M->threetwo[8] , S[8] , T[8]) ; /*  9 */
    FF(H[3], H[0], H[1], H[2], M->threetwo[9] , S[9] , T[9]) ; /* 10 */
    FF(H[2], H[3], H[0], H[1], M->threetwo[10], S[10], T[10]); /* 11 */
    FF(H[1], H[2], H[3], H[0], M->threetwo[11], S[11], T[11]); /* 12 */
    FF(H[0], H[1], H[2], H[3], M->threetwo[12], S[12], T[12]); /* 13 */
    FF(H[3], H[0], H[1], H[2], M->threetwo[13], S[13], T[13]); /* 14 */
    FF(H[2], H[3], H[0], H[1], M->threetwo[14], S[14], T[14]); /* 15 */
    FF(H[1], H[2], H[3], H[0], M->threetwo[15], S[15], T[15]); /* 16 */
    printf("\n");
//    /* Round 2 */
    GG(H[0], H[1], H[2], H[3], M->threetwo[1] , S[16], T[16]); /* 17 */
    GG(H[3], H[0], H[1], H[2], M->threetwo[6] , S[17], T[17]); /* 18 */
    GG(H[2], H[3], H[0], H[1], M->threetwo[11], S[18], T[18]); /* 19 */
    GG(H[1], H[2], H[3], H[0], M->threetwo[0] , S[19], T[19]); /* 20 */
    GG(H[0], H[1], H[2], H[3], M->threetwo[5] , S[20], T[20]); /* 21 */
    GG(H[3], H[0], H[1], H[2], M->threetwo[10], S[21], T[21]); /* 22 */
    GG(H[2], H[3], H[0], H[1], M->threetwo[15], S[22], T[22]); /* 23 */
    GG(H[1], H[2], H[3], H[0], M->threetwo[4] , S[23], T[23]); /* 24 */
    GG(H[0], H[1], H[2], H[3], M->threetwo[9] , S[24], T[24]); /* 25 */
    GG(H[3], H[0], H[1], H[2], M->threetwo[14], S[25], T[25]); /* 26 */
    GG(H[2], H[3], H[0], H[1], M->threetwo[3] , S[26], T[26]); /* 27 */
    GG(H[1], H[2], H[3], H[0], M->threetwo[8] , S[27], T[27]); /* 28 */
    GG(H[0], H[1], H[2], H[3], M->threetwo[13], S[28], T[28]); /* 29 */
    GG(H[3], H[0], H[1], H[2], M->threetwo[2] , S[29], T[29]); /* 30 */
    GG(H[2], H[3], H[0], H[1], M->threetwo[7] , S[30], T[30]); /* 31 */
    GG(H[1], H[2], H[3], H[0], M->threetwo[12], S[31], T[31]); /* 32 */
    printf("\n");
//    /* Round 3 */
    HH(H[0], H[1], H[2], H[3], M->threetwo[5] , S[32], T[32]); /* 33 */
    HH(H[3], H[0], H[1], H[2], M->threetwo[8] , S[33], T[33]); /* 34 */
    HH(H[2], H[3], H[0], H[1], M->threetwo[11], S[34], T[34]); /* 35 */
    HH(H[1], H[2], H[3], H[0], M->threetwo[14], S[35], T[35]); /* 36 */
    HH(H[0], H[1], H[2], H[3], M->threetwo[1] , S[36], T[36]); /* 37 */
    HH(H[3], H[0], H[1], H[2], M->threetwo[4] , S[37], T[37]); /* 38 */
    HH(H[2], H[3], H[0], H[1], M->threetwo[7] , S[38], T[38]); /* 39 */
    HH(H[1], H[2], H[3], H[0], M->threetwo[10], S[39], T[39]); /* 40 */
    HH(H[0], H[1], H[2], H[3], M->threetwo[13], S[40], T[40]); /* 41 */
    HH(H[3], H[0], H[1], H[2], M->threetwo[0] , S[41], T[41]); /* 42 */
    HH(H[2], H[3], H[0], H[1], M->threetwo[3] , S[42], T[42]); /* 43 */
    HH(H[1], H[2], H[3], H[0], M->threetwo[6] , S[43], T[43]); /* 44 */
    HH(H[0], H[1], H[2], H[3], M->threetwo[9] , S[44], T[44]); /* 45 */
    HH(H[3], H[0], H[1], H[2], M->threetwo[12], S[45], T[45]); /* 46 */
    HH(H[2], H[3], H[0], H[1], M->threetwo[15], S[46], T[46]); /* 47 */
    HH(H[1], H[2], H[3], H[0], M->threetwo[2] , S[47], T[47]); /* 48 */
    printf("\n");
//    /* Round 4 */
    II(H[0], H[1], H[2], H[3], M->threetwo[0] , S[48], T[48]); /* 49 */
    II(H[3], H[0], H[1], H[2], M->threetwo[7] , S[49], T[49]); /* 50 */
    II(H[2], H[3], H[0], H[1], M->threetwo[14], S[50], T[50]); /* 51 */
    II(H[1], H[2], H[3], H[0], M->threetwo[5] , S[51], T[51]); /* 52 */
    II(H[0], H[1], H[2], H[3], M->threetwo[12], S[52], T[52]); /* 53 */
    II(H[3], H[0], H[1], H[2], M->threetwo[3] , S[53], T[53]); /* 54 */
    II(H[2], H[3], H[0], H[1], M->threetwo[10], S[54], T[54]); /* 55 */
    II(H[1], H[2], H[3], H[0], M->threetwo[1] , S[55], T[55]); /* 56 */
    II(H[0], H[1], H[2], H[3], M->threetwo[8] , S[56], T[56]); /* 57 */
    II(H[3], H[0], H[1], H[2], M->threetwo[15], S[57], T[57]); /* 58 */
    II(H[2], H[3], H[0], H[1], M->threetwo[6] , S[58], T[58]); /* 59 */
    II(H[1], H[2], H[3], H[0], M->threetwo[13], S[59], T[59]); /* 60 */
    II(H[0], H[1], H[2], H[3], M->threetwo[4] , S[60], T[60]); /* 61 */
    II(H[3], H[0], H[1], H[2], M->threetwo[11], S[61], T[61]); /* 62 */
    II(H[2], H[3], H[0], H[1], M->threetwo[2] , S[62], T[62]); /* 63 */
    II(H[1], H[2], H[3], H[0], M->threetwo[9] , S[63], T[63]); /* 64 */
    printf("\n");

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
}

/* ----------------------- Read Block by Block ----------------------- */
int nextblock(BLOCK *M, FILE *infile, uint64_t *nobits, PADFLAG *status) {

  int i;
  size_t nobytesread = fread(&M->eight, 1, 64, infile);
  *nobits += nobytesread * 8;

    /* Before stuff gets read in, need to check the value of status */  
    switch(*status) {
    /* If finished, return */
    case FINISH:
        return 0;
    case PAD0:
        // We need an all-padding block without the 1 bit.
        for (i = 0; i < 57; i++) {
            M->eight[i] = 0;
        }
        M->sixfour[7] = *nobits;
        *status = FINISH;
        return 1;
        break;  
    default:
        if (nobytesread < 56) {
            // We can put all padding in this block.
            M->eight[nobytesread] = 0x80;
            for (i = nobytesread + 1; i < 56; i++){
                M->eight[i] = 0;
            }
            M->sixfour[7] = *nobits;
            *status = FINISH;
        } 
        else if (nobytesread < 64) {
            // Otherwise we have read between 56 (incl) and 64 (excl) bytes.
            M->eight[nobytesread] = 0x80;
            for (i = nobytesread + 1; i < 64; i++) {
                M->eight[i] = 0;
            }
            *status = PAD0;
        }
        return 1;
    }
}

/* -------------------------- Main Method ---------------------------- */
int main(int argc, char *argv[]) {
    // Expect and open a single filename.
    if (argc != 2) {
        printf("Error: expected single filename as argument.\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    if (!infile) {
        printf("Error: couldn't open file %s.\n", argv[1]);
        return 1;
    }
    // The current padded message block
    BLOCK M;
    uint64_t nobits = 0;
    PADFLAG status = READ;
    uint32_t H[] = {A, B, C, D};

    // Read through all of the padded message blocks.
    while (nextblock(&M, infile, &nobits, &status)) {
        // Calculate the next hash value.
        md5(&M, H);
    }

    for(int i=0;i<4;i++) {
        printf("%02x", H[i]);
    }

    fclose(infile);

    return 0;
} 

