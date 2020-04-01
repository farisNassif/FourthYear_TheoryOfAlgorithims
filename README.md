<p>
  <h2 align="center">MD5 Hash Digest Calculator</h2>
  <i><h3 align="center">A Program written in C that calculates the MD5 hash digest of an input</h3></i>
</p>

## Project Details

|Details  |    |
| --- | --- |
| **Project**  | [Project Spec](https://pdfhost.io/v/lgILkbKAl_project_8pdf.pdf) 
| **GIF** | [Project Running](https://i.imgur.com/HTlEDIJ.gif)
| **Course** | BSc (Hons) in Software Development
| **Module** |  Theory of Algorithims |
| **Author** | [Faris Nassif](https://github.com/farisNassif) |
| **Lecturer** | Dr Ian McLoughlin |

## Contents
* [Assignment Overview](#md5-overview)
* [Running the Program](#running-the-program)
* [How it Works](#how-does-it-work) 
* [Research & Development Diary](#research-and-development-diary)
* [Testing](#testing)

## MD5 Overview
The MD5 hash works by taking a string of any length and encoding it into a 128-bit fingerprint. Encoding the same string over and over will always yielf the same 128-bit hash output. 

An MD5 hash is <i>not</i> encryption, the hash is considered a <i>fingerprint</i>. However it is a one-way transaction, meaning it's <i>(almost)</i> impossible to reverse engineer an MD5 hash to obtain the original string.

For a detailed breakdown of the algorithim, [see below](#how-does-it-work).

## Running the Program
1. In your command line terminal: `git clone https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms`
2. Navigate to the <b> \program\ </b> directory: `cd program`
3. Compile the program: `gcc -o md5 md5.c` || `make md5`
4. Execute the program: `md5.exe TestFile.txt` || `md5.exe` || `./md5`

#### The program may be executed in three different ways 
* Enter a file name as a command line argument 
* Enter a file name as a string to be hashed at runtime 
* Enter a String to be hashed at runtime 

#### Define input via a command line argument
```bash
  > md5.exe TestFile.txt
```
<p align="center">
  <img src = "https://i.imgur.com/PACkAXO.png">
</p>

#### Define input via console menu (File Input)
```bash
  > md5.exe
```
<p align="center">
  <img src = "https://i.imgur.com/DeAUPx8.png">
</p>

#### Define input via console menu (String Input)
```bash
  > md5.exe
```
<p align="center">
  <img src = "https://i.imgur.com/YCWn3RI.png">
</p>

## How does it work?
The MD5 Message-Digest Algorithm was designed as a strengthened version of MD4, prior to MD4 collisions being found [[1]](http://cacr.uwaterloo.ca/hac/about/chap9.pdf). It consists of five major steps [[3]](https://tools.ietf.org/html/rfc1321),

1. <b>Append Padding Bits</b>
2. <b>Append Length</b>
3. <b>Initialize MD Buffer</b>
4. <b>Process Message in 16-Word Blocks</b>
5. <b>Output</b>

### Appending Padding Bits
The first step consists of padding (or <i>extending</i>) the message so that the length of the message in bits is equal to 448 modulo 512. The point is to extend the message so that it's just 64 bits shy of being a multiple of 512 bits.

There are three possible cases that may be executed when a message is about to be padded

1. The message block is fortunately 64 bytes (<i>512 bits</i>) already
	* No need to perform any padding on this block, return
2. The message block is less than 56 bytes (<i>448 bits</i>
	* Add a byte and fill with 0's so that that the length in bits of the padded message becomes congruent to 448 modulo 512
3. The message block is greater than 56 bytes and less than 64 bytes
	* Same as step two, add a byte and fill with 0's. A new block is added and fill 56 bytes with 0's

### Append Length
A 64 bit representation of the length of the message prior to bits being added is appended to the result of the previous step

### Initialize Message Digest Buffer
A four word buffer is required to generate the message digest. A 'word' is essentially defined as a 32 bit register [[3]](https://tools.ietf.org/html/rfc1321), these four words are initialized with the following values

```C
WORD A = 0x67452301;
WORD B = 0xefcdab89;
WORD C = 0x98badcfe;
WORD D = 0x10325476;
```

The value of these four 'words' will be changed and manipulated throughout the four hashing rounds, each previous value being used to generate a new value and so on.

### Process Message in 16-Word Blocks
Four auxiliary functions are defined that each receive three 'words' as input, and output a single 'word' 

```C
#define F(x,y,z) ((x & y) | (~x & z)) 
#define G(x,y,z) ((x & z) | (y & ~z)) 
#define H(x,y,z) (x ^ y ^ z)          
#define I(x,y,z) (y ^ (x | ~z))       
```

In each bit position F acts as a conditional: if X then Y else Z.
The other functions, G, H and I aren't too different from the F function. They function in bitwise parallell to produce their output in such a way that if the corresponding bits of X, Y and Z are independent and unbiased then as a result each bit of G(X,Y,Z), H(X,Y,Z) and I(X,Y,Z) will be independent and unbiased [[3]](https://tools.ietf.org/html/rfc1321).

Each 16-word block is processed, A is saved as AA, B as BB, C as CC, and D as DD then the following additions are performed
```C
     A = A + AA
     B = B + BB
     C = C + CC
     D = D + DD 
```
Each of the four registered are incremented by the value it had before the block was started.

### Output
The Message Digest should yield an output beginning at low-order byte of A and ending with the high-order byte of D [A,B,C,D].

## Research and Development Diary
* <b>Week One</b>
	* The first week involved the setup of the repository and also getting setup on my Google cloud virtual machine. I also included a skeleton implementation of the program that just included some file readers and other basic functions. In preperation for the assignment I watched some related external videos that would help cement my understanding of the underlying concepts behind the project [[6]](https://www.youtube.com/watch?v=6h7_YAmtzGw) [[7]](https://www.youtube.com/watch?v=53O9J2J5i14).
* <b>Week Two</b>
	* During this week I completed the first video that discussed the SHA standard. I didn't fully understand everything in the video so I looked over the document in my own time [[2]](https://www.nist.gov/publications/secure-hash-standard) and watched a video [[9]](https://www.youtube.com/watch?v=DMtFhACPnTY) that helped provide a bit more insight. I also had a look at the main differences between MD5 and SHA [[8]](https://www.thesslstore.com/blog/difference-sha-1-sha-2-sha-256-hash-algorithms/) [[10]](https://stackoverflow.com/questions/2948156/algorithm-complexity-security-md5-or-sha1) which helped me get a handle on the main differences in terms of speed, amount of attacks required to find the original message, message digest length and security [[12]](https://stackoverflow.com/a/37235104).
* <b>Week Three</b>
	* I finished the [C bit operations](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/C_bit_operations/lookatbits.c) video and looked over the reccomended document [[4]](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Expressions-and-Operators) and some examples and tutorials of bit manipulation in C [[5]](https://graphics.stanford.edu/~seander/bithacks.html) [[11]](https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm). I spent a good bit of time this week reading up on VI and learning some new editing and file commands [[13]](https://www.guru99.com/the-vi-editor.html).
* <b>Week Four</b>
	* This week I was a bit behind with videos so caught up on both [Functions and Constants in SHA](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Functions_and_constants_in_SHA/sha256.c) and [Padding](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Padding/padding.c). I attempted to code up some functions for MD5 by looking through the Request for Comments [[3]](https://tools.ietf.org/html/rfc1321) summary and began defining constants like the four auxillary functions and constants for the transformation routine. Since I still wasn't fully sure of the fully process required for the MD5 algorithim I found an article [[14]](http://www.boblandstrom.com/the-md5-hashing-algorithm/) that helped simplify the whole process for me, I got a better understanding of the role of auxillary functions in the block processing and how each sixteen oprations of the four rounds work.
* <b>Week Five</b>
	* I coded up the [Unions in C](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Unions/unions.c) video but didn't fully understand what was meant by storing different data types in the same location. I looked at some tutorials [[15]](https://www.tutorialspoint.com/cprogramming/c_unions.htm) [[16]](https://www.programiz.com/c-programming/c-unions) and got a bit of a better understanding of how a unions members are accessed and the main differences between unions and structures, like for example how a union variable will always be the size of it's largest element unlike a struct where it's size is accumulative. Since big and little endian was mentioned in the video I did some reading on that also [[17]](https://www.geeksforgeeks.org/little-and-big-endian-mystery/) just to get a surface level understanding of byte order representation. I also included a union block in my MD5 project file and integrated it with code that was already written. 
* <b>Week Six & Week Seven</b>
	* I was behind a week so caught up on the [Hash Function](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Hash_function/Hash_implementation.c) video as well as [Finalizing Padding](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Finalizing_Padding/Finalizing_padding.c). With reference to both these videos and to the Request for Comments [[3]](https://tools.ietf.org/html/rfc1321) document I radically changed the contents of my main MD5 project file. My project file now contained all MD5 constants and a function that would perform the MD5 hash on an input albeit a rough implementation. The output wasn't correct and I suspect it to be an issue with how the message blocks are padded.
* <b>Week Eight</b>
	* During this week I completed the final video available to us, [Refactoring SHA256](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Refactoring_Sha256/sha.c). The video led me to look over the MD5 code I had written already and check every constant and function to ensure they were written correctly. I did find some errors with auxillary functions and values that weren't initialized correctly however my hash output still wasn't correct.  
* <b>Week Nine</b>
	* Having completed the videos I focused solely on the MD5 implementation. I refactored and simplified the function that performs the hash rounds for each block into a single loop by defining the parameterized input values as constant arrays. I also fixed issues with block processing including the context not changing correctly and cases not executing correctly in the switch statement. I was still getting the wrong output so began looking at methods in C to ensure output will always be in little endian (<i>as required for MD5</i>) [[18]](https://stackoverflow.com/questions/54548061/c-little-and-big-endian-confusion).
* <b>Week Ten</b>
	* After multiple attempts and testing of different endian solutions one was found that successfuly extracts individual bytes from each input value in little endian [[19]](https://stackoverflow.com/a/17913021). Following the implementation of the little endian solution and some changes to the 32 bit output value array the program successfully output correct MD5 values. Once it correctly worked I again began to refactor and comment as much code as I could, included a menu that allowed easy traversal and multiple input options and began to perform more [[tests]](#testing) against the project to verify results.

## Testing
The project was tested on both Linux and Windows machines to ensure portability and accuracy. The results were also compared against external MD5 calculation sources [[20]](https://www.md5hashgenerator.com/) [[21]](http://www.md5.cz/).

The contents of the following tests are contained within the `Program/test-input` folder. The test data was obtained from page 21 of the the Request for Comments document [[3]](https://tools.ietf.org/html/rfc1321).



## References	
[1] http://cacr.uwaterloo.ca/hac/about/chap9.pdf <br>
[2] https://www.nist.gov/publications/secure-hash-standard <br>
[3] https://tools.ietf.org/html/rfc1321 <br>
[4] https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Expressions-and-Operators <br>
[5] https://graphics.stanford.edu/~seander/bithacks.html <br>
[6] https://www.youtube.com/watch?v=6h7_YAmtzGw <br>
[7] https://www.youtube.com/watch?v=53O9J2J5i14 <br>
[8] https://www.thesslstore.com/blog/difference-sha-1-sha-2-sha-256-hash-algorithms/ <br>
[9] https://www.youtube.com/watch?v=DMtFhACPnTY <br>
[10] https://stackoverflow.com/questions/2948156/algorithm-complexity-security-md5-or-sha1 <br>
[11] https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm <br>
[12] https://stackoverflow.com/a/37235104 <br>
[13] https://www.guru99.com/the-vi-editor.html <br>
[14] http://www.boblandstrom.com/the-md5-hashing-algorithm/ <br>
[15] https://www.tutorialspoint.com/cprogramming/c_unions.htm <br>
[16] https://www.programiz.com/c-programming/c-unions <br>
[17] https://www.geeksforgeeks.org/little-and-big-endian-mystery/ <br>
[18] https://stackoverflow.com/questions/54548061/c-little-and-big-endian-confusion <br>
[19] https://stackoverflow.com/a/17913021 <br>
[20] https://www.md5hashgenerator.com/ <br>
[21] http://www.md5.cz/ <br>