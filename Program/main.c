// Author :     Faris Nassif
// Module :     Theory Of Algorithms
// Summary:     A program that executes the Secure Hash Algorithim(SHA-256) on an input 

#include <stdio.h> // Input/Output
#include <stdlib.h> // TODO
#include <string.h>
#include <stdint.h> // Req for uint(x) unsigned int

char filename[100], c; // Temp for storing the name of file read

/*
 * Acts as the Runner of the program.
 * 
 * @Paramaters
 * ------------------------------------
 * *argc: The num of paramaters that are used
 * *argv[]: Array of paramater names
 * 
 * @Returns
 * ------------------------------------
 * TODO ? Returns 0
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
            // Do SHA ..
            
            c = fgetc(fptr); // Gets next char from parameterized stream 
            while (c != EOF) {
                printf ("%c", c); 
                c = fgetc(fptr); 
            }
        }
    }

    fclose(fptr); // Close the file ..
    return 0; 
}

// ------------------------ Bit Operations ------------------------ 
// https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf

/*
    [Majority Function]
    =>  Produces a 1 if and ONLY if the majority of inputs are 1's, otherwise output a 0.
    =>  Section 4.1.2
*/
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
    return ((x & y) ^ (x & z) ^ (y & z));
}

/*
    [Choose Function]
    =>  The (x) input will always choose if the output is from (y) or (z).
    =>  Section 4.1.2
*/
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
    return ((x & y) ^ (~x & z));
}

/*
    [Shift Function]
    =>  Shift the bit (x) by (n) places.
    =>  Section 3.2
*/
uint32_t SHR(uint32_t x, int n) {
    return x >> n;
}

/*
    [Rotate Function]
    =>  Rotates the bit (x) by (n) places and rewrite hanging bits at the start
    =>  Section 3.2
*/
uint32_t ROTR(uint32_t x, int n) {
    return (x >> n) | (x << (32 - n));
}

/*
    [Sig0 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t Sig0(uint32_t x) {
    return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x,22); 
}

/*
    [Sig0 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t Sig1(uint32_t x) {
    return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x,25); 
}

/*
    [SIG1 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t sig_zero(uint32_t x) {
    return ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x,3); 
}

/*
    [SIG0 Function]
    =>  TODO
    =>  Section 4.1.2
*/
uint32_t sig_one(uint32_t x) {
    return ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x,10); 
}