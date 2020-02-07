#include <stdio.h>
#include <stdint.h> // Provides new types
#include <inttypes.h> // Provides formatters for printf 

void printbits(uint64_t s) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", ((1 << i) & s) ? 1 : 0); // Ternary operator in C
    }
    printf("\n");
    for (int i = 63; i >= 0; i--) {
        printf("%d", ((1ULL << i) & s) ? 1 : 0); // ULL 
    }
    printf("\n");
}

void printeightbits(uint8_t s) {
    for (int i = (8 - 1); i >= 0; i--) {
        printf("%d", ((1 << i) & s) ? 1 : 0); // Ternary operator in C
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    char c = 65;
    int i = 65;
    long int l = 65;
    long long int b = 65;

    uint8_t w = 73; // Guranteed to be an 8bit unsigned int
    uint8_t x = 99; // Guranteed to be an 8bit unsigned int
    uint8_t y = (w & x); // And
    uint8_t z = (w | x); // Or

    uint64_t p = 65; // Guranteed to be a 64bit unsigned int

    printf("%x\t%c\t%d\t%d\n", c, c, c, sizeof(c));

    printf("%x\t%c\t%d\t%d\n", i, i, i, sizeof(i));

    printf("%x\t%c\t%d\t%d\n", l, l, l, sizeof(l));

    printf("%x\t%c\t%d\t%d\n", b, b, b, sizeof(b)); 

    //printbits(p); // Print each of the bits of p one at a time
    printf("w = "); printeightbits(w);
    printf("x = "); printeightbits(x);
    printf("& = "); printeightbits(y); // A = 0100 B = 0110   C(&) = 0100
    printf("| = "); printeightbits(z); // A = 0100 B = 0110   C(|) = 0110
    printf("~ = "); printeightbits(~w); // Inverse of w

    printf(" 99              = "); printeightbits(99); // Outputs to 00000001
    printf("(1ULL << 3) & 99 = "); printeightbits((((uint8_t)99) << 3)); // Shifts above by 3 to 00001000


    printf("%llx\t%lld\n", p, p); // ll between % and x denotes long long

    return 0;
}