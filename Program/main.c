// Author :     Faris Nassif
// Module :     Theory Of Algorithms
// Summary:     A program that executes a MD5 Hash on a given input 

#include <stdio.h> // Input/Output
#include <stdlib.h> // TODO
#include <string.h>
#include <stdint.h> // Req for uint(x) unsigned int

/*
    [Majority Function]
    =>  Produces a 1 if and ONLY if the majority of inputs are 1's, otherwise output a 0.
    =>  Section 4.1.2
*/
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

/*
    [Choose Function]
    =>  The (x) input will always choose if the output is from (y) or (z).
    =>  Section 4.1.2
*/
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);

/*
    [Shift Function]
    =>  Shift the bit (x) by (n) places.
    =>  Section 3.2
*/
uint32_t SHR(uint32_t x, int n);

/*
    [Rotate Function]
    =>  Rotates the bit (x) by (n) places and rewrite hanging bits at the start
    =>  Section 3.2
*/
uint32_t ROTR(uint32_t x, int n);

/*
    [Sig0 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t Sig0(uint32_t x);

/*
    [Sig0 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t Sig1(uint32_t x);

/*
    [SIG1 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t sig_zero(uint32_t x);

/*
    [SIG0 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t sig_one(uint32_t x);

/*
    Status controller when reading the pad file

    READ: Still reading file, not EOF
    PAD0: Already started padding some 0's
    PAD1: Read all the way to the end, and fill a block
    Finish: Finished all padding
*/
enum flag {
    READ, 
    PAD0, 
    PAD1, 
    FINISH 
};

/*

*/
union block { 
    uint64_t sixfour[8];
    uint32_t threetwo[16];
    uint8_t eight[64];
};

void md5();
void writeToFile();

char filename[100], c; // Temp for storing the name of file read

/*
    Executor of the program

    argc: The num of paramaters that are used
    argv[]: Array of paramater names
*/
int main(int argc, char *argv[]) {
    // Pointer for file
    FILE *fptr; 
  
  	// Only runs if an argument was passed as a param
	if (argv[1] == NULL)
	{
		printf("no file specified as an input\n");
	} else {
        fptr = fopen(argv[1], "rb");
        strcpy(filename, argv[1]);

        // If there was no file or an issue with opening it
	    if (fptr == NULL) { 
		    printf("Can't open it :(\n");
	    } else {
		    printf("It worked yay\n");
		    printf("Filename: %s\n", filename);           
            
            c = fgetc(fptr); // Initial read of the file
            while (c != EOF) { // Keep reading the file until there's nothing left
                printf ("%c", c); // Prints out the contents of the file one character at a time
                c = fgetc(fptr); 
            }
            md5();
            writeToFile();
        }
    }

    fclose(fptr); // Close the file ..
    return 0; 
}

// --------------------- MD5 Implementation ----------------------- 
void md5() {
    printf("\nIn md5()");
}

// --------------------------- File Writer ---------------------------- 
void writeToFile() {
    printf("\nIn writeToFile()");
}
// ----------------- Bit Operations (Implementation) ------------------ // https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
    return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
    return ((x & y) ^ (~x & z));
}

uint32_t SHR(uint32_t x, int n) {
    return x >> n;
}

uint32_t ROTR(uint32_t x, int n) {
    return (x >> n) | (x << (32 - n));
}

uint32_t Sig0(uint32_t x) {
    return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x,22); 
}

uint32_t Sig1(uint32_t x) {
    return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x,25); 
}

uint32_t sig_zero(uint32_t x) {
    return ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x,3); 
}

uint32_t sig_one(uint32_t x) {
    return ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x,10); 
}