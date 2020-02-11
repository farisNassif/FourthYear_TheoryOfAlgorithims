// Padding for SHA256
#include <stdio.h> // I/O Stuff
#include <inttypes.h> // Also includes formatters for printf

uint64_t nozerobytes(uint64_t nobits) {

    uint64_t result = 512ULL - (nobits % 512ULL); // How many bits did you have?

    if (result < 65) { // If it's less than 65.. (65 => Num of bits thats definitely needed to pad)
        result += 512; // Add an extra block, full of 0's
    }

    result -= 72; // Take those 72 bits away from res

    return (result / 8ULL); // Divide res by 8 to get the num of bytes to add on
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Error: expected single filename as argument. \n");
        return 1;
    }
    
    FILE *infile = fopen(argv[1], "rb");
    if (!infile) {
        printf("Error: couldn't open file %s. \n", argv[1]);
    }

    uint8_t b;
    uint64_t nobits; // 64 bits limitation for SHA

    for (nobits = 0;fread(&b, 1, 1, infile) == 1; nobits += 8) { // & => Sends the address of b, fread can use to override whats stored at b
        printf("%02" PRIx8, b); // PRIx8 correct format specifier for an unsigned 8 bit int 
    }

    printf("%02" PRIx8 , 0x80); // Bits: 1000 0000

    // How much padding in terms of 0 bits are needed to add on?
    for (uint64_t i = nozerobytes(nobits); i > 0; i--) {
        printf("%02" PRIx8, 0x00);
    }

    printf("%016" PRIx64 "  \n", nobits);

    fclose(infile);

    return 0;
}