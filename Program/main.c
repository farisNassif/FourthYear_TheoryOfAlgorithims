/*
 * Author: 		Faris Nassif
 * Module: 	    Theory Of Algorithms
 * Summary:     A program that executes the Secure Hash Algorithim(SHA-256) on an input 
*/

#include <stdio.h> // Input/Output
#include <stdlib.h> // TODO
#include <string.h>

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