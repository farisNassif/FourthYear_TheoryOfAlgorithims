// Author :     Faris Nassif
// Module :     Theory Of Algorithms
// Summary:     A program that executes a MD5 Hash on a given input
//              This program has been adapted based on the process outlined in https://tools.ietf.org/html/rfc1321

#include <stdlib.h>   // For additional getopt() functionality
#include <stdio.h>    // Input/Output
#include <stdint.h>   // Req for uint(x) unsigned int
#include <inttypes.h> // Includes formatters for output
#include <getopt.h>   // Command line argument functionality

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
    The four constant arrays below [AA, BB, CC, DD] represent 
    the first four paramaters for the above transformation functions.

    For example, FF will be performed 16 times, GG 16 times and so on,
    The first time FF(first round) will be performed, it's first paramater (a) will be the first
    index of AA. So FF(AA[0], BB[0], CC[0], DD[0]), then FF(AA[1], BB[1], CC[1], DD[1])
    After 16 iterations then it'll be GG(AA[15], BB[15], CC[15], DD[15]) and so on.

    It's kind of a chunky way of doing it, would probably be possible with a multi-dimensional
    array, however this way works and allows for the four hash rounds to be performed efficiently
    in a loop.
*/
const WORD AA[] = {
    0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1,
    0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1,
    0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1,
    0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1
};

const WORD BB[] = {
    1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2,
    1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2,
    1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2,
    1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2
};

const WORD CC[] = {
    2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3,
    2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3,
    2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3,
    2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3
};

const WORD DD[] = {
    3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0,
    3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0,
    3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0,
    3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0, 3, 2, 1, 0
};

/* 
    Fifth paramater for the transformation functions.
    MM being the index of the uint32_t block that needs to be accessed
*/
const WORD MM[] = {
    0, 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    1, 6, 11,  0,  5, 10, 15,  4,  9, 14,  3,  8, 13,  2,  7, 12,
    5, 8, 11, 14,  1,  4,  7, 10, 13,  0,  3,  6,  9, 12, 15,  2,
    0, 7, 14,  5, 12,  3, 10,  1,  8, 15,  6, 13,  4, 11,  2,  9
};

/* 
    Sixth paramater for the transformation functions.
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
    Seventh and final paramater for the transformation functions.
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
    https://tools.ietf.org/html/rfc1321 => Page 4

    Four 'Word' buffer initialized with hex values used in the Message Digest computation.
    These will be manipulated on each round of the MD5 hash.
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
    WORD threetwo[16];
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

/* 
    Adapted From: https://stackoverflow.com/questions/17912978/printing-integers-as-a-set-of-4-bytes-arranged-in-little-endian

    Output the MD5 result in little endian
*/ 
void output(WORD MD5_RES[]) {
    for (int i = 0; i < 4; ++i) {
        printf("%02x%02x%02x%02x", 
        (MD5_RES[i] >>  0) & 0xFF, 
        (MD5_RES[i] >>  8) & 0xFF, 
        (MD5_RES[i] >> 16) & 0xFF, 
        (MD5_RES[i] >> 24) & 0xFF);
    }
}

/* --------------------- Perform MD5 on Blocks ----------------------- */
void md5(BLOCK *M, WORD *MD5_RES) {
    WORD a, b, c, d;
    /* Initialize hash value for this chunk */
    a = MD5_RES[0];
    b = MD5_RES[1];
    c = MD5_RES[2];
    d = MD5_RES[3];

    /* Perform the four hash rounds for each chunk */
    for(int i = 0; i<64; i++) {
        if (i < 16) {
            FF(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]) ; /* ROUND 1 */
        } else if (i < 32) {
            GG(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]) ; /* ROUND 2 */
        } else if (i < 48) {
            HH(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]) ; /* ROUND 3 */
        } else {
            II(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]) ; /* ROUND 4 */
        }
    }
    
    /* Add this chunk's hash to result so far */
    MD5_RES[0] += a;
    MD5_RES[1] += b;
    MD5_RES[2] += c;
    MD5_RES[3] += d;
}

/* ----------------------- Read Block by Block ----------------------- */
int nextblock(BLOCK *M, FILE *infile, uint64_t *nobits, PADFLAG *status) {
  size_t nobytesread = fread(&M->eight, 1, 64, infile);
  *nobits += nobytesread * 8;

    /* Before stuff gets read in, need to check the value of status */  
    switch(*status) {
    /* If all message blocks are finished, return */
    case FINISH:
        return 0;
    case PAD0:
        /* We need an all-padding block without the 1 bit */
        for (int i = 0; i < 57; i++) {
            M->eight[i] = 0;
        }
        M->sixfour[7] = *nobits;
        *status = FINISH;
        return 1;
        break;  
    default:
        /* Check if under 56 bytes have been read
        ** If true, put all padding in this block */
        if (nobytesread < 56) {
            /* Insert 1 bit into the current block */
            M->eight[nobytesread] = 0x80; // 00000001
            /* Add 1 as index into block */
            for (int i = nobytesread + 1; i < 56; i++) {
                /* Set bytes to 0 */
                M->eight[i] = 0;
            }
            /* Set the final element to nobits (bits in initial message) 
            ** Then append the size of the file in bits as a unsigned 64bit int */
            M->sixfour[7] = *nobits;
            *status = FINISH;
        } 
        /* If theres 56 to 64 bytes read, need extra message block full of padding 
        ** Append 1 and add 64 bit integer to initial message block
        ** Otherwise check if padding can be inserted into this block */
        else if (nobytesread < 64) {
            /* Insert 1 bit into the current block */
            M->eight[nobytesread] = 0x80; // 00000001
            /* Pad the remainder of the message block with 0 bits */
            for (int i = nobytesread + 1; i < 64; i++) {
                M->eight[i] = 0;
            }
            *status = PAD0;
        }
        return 1;
    }
}

/* ----------------- Pass it a file, kick off hash ------------------- */
void preMd5(FILE *infile) {
    /* Block/chunk to be pre-processed */
    BLOCK M;
    uint64_t nobits = 0;
    /* Read status of the current chunk */
    PADFLAG status = READ;
    /* Will store the hash result, A,B,C,D will be changed and manipulated throughout the hashing rounds */
    WORD MD5_RES[] = {A, B, C, D};

    /* Read through all of the padded message blocks */
    while (nextblock(&M, infile, &nobits, &status)) {
        /* For each block, hash it */
        md5(&M, MD5_RES);
    }
    output(MD5_RES);
}

/* -------------------- Command Line Argument Outputs ------------------ 
* Very dirty to look at this method, exists to clean up the main method */
void cmd_line_display(int option) {
    /* Multi-dimensional array to clean up test suite input & output */
    const char* testFiles[5][3] = {
        {"test-input/TestOne.txt",   "*EMPTY FILE*",               "d41d8cd98f00b204e9800998ecf8427e"},
        {"test-input/TestTwo.txt",   "a",                          "0cc175b9c0f1b6a831c399e269772661"},
        {"test-input/TestThree.txt", "abc",                        "900150983cd24fb0d6963f7d28e17f72"},
        {"test-input/TestFour.txt",  "message digest",             "f96b697d7cb7938d525a2f31aaf161d0"},
        {"test-input/TestFive.txt",  "abcdefghijklmnopqrstuvwxyz", "c3fcd3d76192e4007dfb496cca67e13b"}
    };

    /* Switch statement to help clean up the main method a bit, solely for output */
    switch (option) {
    case 0: // Case 0 - No command line arguments were entered
        printf("\n*No command line argument specified, 'md5.exe --help' will list all valid command line arguments.\n");
        printf("\nInput - 1: Perform MD5 on a File            ");
        printf("\nInput - 2: Perform MD5 on a String        \n");
        printf("\nChoose an option: ");
        break;
    case 1: // Case 1 - The argument --test was entered, prompting a suite of tests
        printf("\n----------------- MD5 Test Suite ----------------\n");
        printf("The following tests are outlined in Page 21 of the\nRequest for Comments MD5 Document.\nhttps://tools.ietf.org/html/rfc1321\n");
        printf("-------------------------------------------------\n");
        /* Loop once for each test */
        for (int i = 0; i < 5; ++i) {
            /* Print relevant information about the i'th test being carried out */
            printf("Test Number: %d\nContent to Test: %s\nExpected Result: %s\n", i + 1, testFiles[i][1], testFiles[i][2]);
            /* Open the i'th file */
            FILE *infile = fopen(testFiles[i][0], "rb");
            printf("Actual Result  : ");
            /* Perform the MD5 hash on the content and close the file */
            preMd5(infile);
            fclose(infile);   
            printf("\n-------------------------------------------------\n");
        }
        break;
    case 2: // Case 2 - The argument --help was entered, prompting a helpful display
        printf("\n--------------- Valid Command Line Argument Inputs ---------------- ");
        printf("\n --help    | Displays helpful information for running the program.  ");
        printf("\n --test    | Runs the test suite to ensure the MD5 output is valid. ");
        printf("\n --explain | Brief high level overview of MD5, including a diagram. ");
        printf("\n --hashfile <path_to_file> | Hashes the specified file.             ");
        printf("\n --hashstring <string>     | Hashes a specified String.           \n");
        printf("--------------- Examples of Executing Arguments ------------------    ");
        printf("\n Hashing a String :     md5.exe --hashstring abc                    ");
        printf("\n Hashing a File   :     md5.exe --hashfile test-input/TestOne.txt \n");
        break;
    case 3: // Case 3 - The argument --explain was entered, display information about MD5
        printf("\n-------------------------------------------------------------------------\n");
        printf("The MD5 hashing algorithm is a one-way cryptographic function that \n");
        printf("accepts a message of any length as input and returns as output a \n");
        printf("fixed-length digest value to be used for authenticating the original message.\n");
        
        printf("\nX (X1, X2, X3, ..... Xn)                                           \n");
        printf("            +                                                        \n");
        printf("            |  448 bits                                              \n");
        printf("            |                                                        \n");
        printf("            v                                                        \n");
        printf("+-----------+----------+                    <-----------------------^\n");
        printf("|                      |                    |                       |\n");
        printf("|   Padding Process    |                    |                       |\n");
        printf("|                      |                    |                       |\n");
        printf("+-----------+----------+                    |                       ^\n");
        printf("            |                   +-----------v------------+          |\n");
        printf("            |       512 bits    |                        |          |\n");
        printf("            +------------------>+  Compression Function  |          |\n");
        printf("                                |                        |          |\n");
        printf("                                +-----------+------------+          |\n");
        printf("                                            |                       |\n");
        printf("                                            |                       |\n");
        printf("                                            |                       |\n");
        printf("                                            +----------------------->\n");
        printf("                                            |                        \n");
        printf("                                            |                        \n");
        printf("                                            |                        \n");
        printf("                                            v                        \n");
        printf("                                       128 bit hash                  \n");
        printf("\nThe MD5 message digest hashing algorithm processes data in 512-bit blocks,\n");
        printf("broken down into 16 words composed of 32 bits each. The output from MD5 is a \n");
        printf("128-bit message digest value.\n");
        printf("\nFor a more in depth overview see: https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms");
        break;
    default:
        break;
    }
}

/* -------------------------- Main Method ---------------------------- */
int main(int argc, char *argv[]) {
    printf("------------------------------------------------------------------ ");
    printf("\nAuthor :     Faris Nassif");
    printf("\nModule :     Theory Of Algorithms");
    printf("\nSummary:     A program that executes a MD5 Hash on a given input");
    printf("\nGithub :     https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms\n");

    /* Input vars */
    int option;
    /* Declaration of file/string inputs */
    char fileName[100];
    char inputString[50];
    /* Long getopt options */
    int c;
    /* File input */
    FILE *infile;

    /* User ran 'md5.exe' without any arguments, display menu */
    if (argv[1] == NULL) {
        /* List menu and provide some input options and information */
        cmd_line_display(0);
		scanf("%d", &option);

        /* User wants to input a file .. */
        if (option == 1) {
            printf("Enter a Filename: ");
			scanf("%s", fileName);    
            infile = fopen(fileName, "rb");

            /* If invalid & file couldn't be found */
            if (!infile) {
                printf("Error: couldn't open file %s.\n", argv[1]);
                return 1;
            } 
            /* Otherwise perform MD5 on the contents of the file */
            else {
                printf("Processing file contents ...\nMD5: ");
                preMd5(infile);
                fclose(infile);
            }
        } 
        /* They gave a String, write it to a file then read it */
        else if (option == 2) {
            printf("Enter a String: ");
            scanf("%s", inputString);

            /* Open new file */
            infile = fopen("test-input/StringInput.txt", "w");
            /* Write user input to the file */ 
            fprintf(infile, "%s", inputString);
            fclose(infile);

            /* Open the file to read */
            infile = fopen("test-input/StringInput.txt", "rb");
            printf("Processing String ...\nMD5: ");
            preMd5(infile);
            fclose(infile);
        } else {
            printf("\nInvalid Input\nExiting ...\n");
        }
    } 
    /* Else, a command line argument was detected */
    else {
        /* Long getopt() options, adapted from:
        *  https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html */
        static struct option long_options[] = {
            {"help"      , no_argument      , 0, 'h'},
            {"test"      , no_argument      , 0, 't'},
            {"explain"   , no_argument      , 0, 'e'},
            {"hashfile"  , required_argument, 0, 'f'},
            {"hashstring", required_argument, 0, 's'},
            {0           , 0                , 0,  0 }
        };

        /* getopt_long stores the option index here */
        int option_index = 0;

        c = getopt_long (argc, argv, "h:t:f:s", long_options, &option_index);
        switch (c) {
            case 'h':
                /* Display some helpful information to the user */
                cmd_line_display(2);
                break;
            case 't':
                /* Will perform a suite of tests to verify correct output */
                cmd_line_display(1);
                break;

            case 'e':
                /* Will print out some information about MD5 */
                cmd_line_display(3);
                break;
            case 'f':
                /* Attempt to open the file to be hashed */
                infile = fopen(optarg, "rb");    

                /* If invalid file input */
                if (!infile) {
                    printf("\nError: couldn't open file %s.\n", optarg);
                    return 1;
                } 
                /* Otherwise perform MD5 on the contents of the file */
                else {
                    printf("\nProcessing file contents ...\nMD5: ");
                    preMd5(infile);
                    fclose(infile);
                }                    
                break;
            case 's':
                /* Open new file */
                infile = fopen("test-input/StringInput.txt", "w");
                /* Write user input to the file */ 
                fprintf(infile, "%s", optarg);
                fclose(infile);

                /* Open the file to read */
                infile = fopen("test-input/StringInput.txt", "rb");
                printf("\nProcessing String ...\nMD5: ");
                preMd5(infile);
                fclose(infile);
                break;                   
            default:
                abort();   
        }
    }
    printf("\n");
    return 0;
}
