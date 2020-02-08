<p>
  <h2 align="center">MD5 Hash Digest Calculator</h2>
  <i><h3 align="center">A Program written in C that calculates the MD5 hash digest of an input</h3></i>
</p>

## Project Details

|Details  |    |
| --- | --- |
| **Project**  | [Project Spec](https://pdfhost.io/v/lgILkbKAl_project_8pdf.pdf) 
| **GIF** | [Project Running](https://i.imgur.com/fWZhbrR.gif)
| **Course** | BSc (Hons) in Software Development
| **Module** |  Theory of Algorithims |
| **Author** | [Faris Nassif](https://github.com/farisNassif) |
| **Lecturer** | Dr Ian McLoughlin |

## Contents
* [Assignment Overview](#md5-overview)
* [Running the Program](#running-the-program)
* [How it Works](#how-does-it-work) 
* [Research & Development Diary](#research-and-development-diary)

## MD5 Overview
The MD5 hash works by taking a string of any length and encoding it into a 128-bit fingerprint. Encoding the same string over and over will always yielf the same 128-bit hash output. 

An MD5 hash is <i>not</i> encryption, the hash is considered a <i>fingerprint</i>. However it is a one-way transaction, meaning it's <i>(almost)</i> impossible to reverse engineer an MD5 hash to obtain the original string.

For a detailed breakdown of the algorithim, [see below](#How-does-it-work?)

## Running the Program
1. In your command line terminal: `git clone https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms`
2. Navigate to the <b> \program\ </b> directory: `cd program`
3. Compile the program: `gcc -o md5 md5.c` || `make md5`
4. Execute the program: `md5.exe TestFile.txt` || `md5.exe`

#### The program may be executed in three different ways 
* Enter a file name as a command line argument 
* Enter a file name as a string to be hashed at runtime 
* Enter a String to be hashed at runtime 

#### Define input via a command line argument
```bash
  > md5.exe TestFile.txt
```
<p align="center">
  <img src = "https://i.imgur.com/DueplYH.png">
</p>

#### Define input via console menu (File Input)
```bash
  > md5.exe
```
<p align="center">
  <img src = "https://i.imgur.com/77sy6jl.png">
</p>

#### Define input via console menu (String Input)
```bash
  > md5.exe
```
<p align="center">
  <img src = "https://i.imgur.com/m79eWdc.png">
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
No need to perform any padding on this block, return
2. The message block is less than 56 bytes (<i>448 bits</i>
Add a byte and fill with 0's so that that the length in bits of the padded message becomes congruent to 448 modulo 512
3. The message block is greater than 56 bytes and less than 64 bytes
Same as step two, add a byte and fill with 0's. A new block is added and fill 56 bytes with 0's

### Append Length
A 64 bit representation of the length of the message prior to bits being added is appended to the result of the previous step

### Initialize Message Digest Buffer
A four word buffer is required to generate the message digest. A 'word' is essentially defined as a 32 bit register[[3]](https://tools.ietf.org/html/rfc1321), these four words are initialized with the following values

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
The other functions, G, H and I aren't too different from the F function. They function in bitwise parallell to produce their output in such a way that if the corresponding bits of X, Y and Z are independent and unbiased then as a result each bit of G(X,Y,Z), H(X,Y,Z) and I(X,Y,Z) will be independent and unbiased[[3]](https://tools.ietf.org/html/rfc1321).

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
* Week One
	* The first week involved the setup of the repository and also getting setup on my Google cloud virtual machine. I also included a skeleton implementation of the program that just included some file readers and other basic functions. In preperation for the assignment I watched some related external videos that would help cement my understanding of the underlying concepts behind the project [[6]](https://www.youtube.com/watch?v=6h7_YAmtzGw) [[7]](https://www.youtube.com/watch?v=53O9J2J5i14).
	
## References
[1] http://cacr.uwaterloo.ca/hac/about/chap9.pdf <br>
[2] https://www.nist.gov/publications/secure-hash-standard <br>
[3] https://tools.ietf.org/html/rfc1321 <br>
[4] https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Expressions-and-Operators <br>
[5] https://graphics.stanford.edu/~seander/bithacks.html <br>
[6] https://www.youtube.com/watch?v=6h7_YAmtzGw <br>
[7] https://www.youtube.com/watch?v=53O9J2J5i14 <br>
