<p>
  <h2 align="center">MD5 Hash Digest Calculator</h2>
  <i><h3 align="center">A Program written in C that calculates the MD5 hash digest of an input</h3></i>
</p>

## Project Details

|Details  |    |
| --- | --- |
| **Project**  | [Project Spec](https://pdfhost.io/v/P7KuCLtXS_project_11pdf.pdf) 
| **Course** | BSc (Hons) in Software Development
| **Module** |  Theory of Algorithms |
| **Author** | [Faris Nassif](https://github.com/farisNassif) |
| **Lecturer** | Dr Ian McLoughlin |

## Contents
* [Assignment Overview](#md5-overview)
* [Running the Program](#running-the-program)
* [How it Works](#how-does-it-work) 
* [Project Implementation](#project-implementation) 
* [Research & Development Diary](#research-and-development-diary)
* [Testing](#testing)

## MD5 Overview
The MD5 hash works by taking a string of any length and encoding it into a 128-bit fingerprint. Encoding the same string over and over will always yield the same 128-bit hash output. 

An MD5 hash is <i>not</i> encryption, the hash is considered a <i>fingerprint</i>. However it is a one-way transaction, meaning it's <i>(almost)</i> impossible to reverse engineer an MD5 hash to obtain the original string.

For a detailed breakdown of the algorithm, [see below](#how-does-it-work).

## Running the Program
1. In your command line terminal: `git clone https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms`
2. Navigate to the <b> \program\ </b> directory: `cd program`
3. Compile the program: `gcc -o md5 md5.c` || `make md5`
4. Execute the program: `md5.exe --hashstring abc` || `md5.exe --hashfile path/to/file.txt` || `md5.exe` || `./md5`

#### The program may be executed in multiple ways
* Run the program without a command line argument
* Enter a file as a command line argument to be hashed at runtime 
* Enter a String as a command line argument to be hashed at runtime 

#### Hashing a String via a command line argument
```bash
  > ./md5 --hashstring abc
```
<p align="center">
  <img src = "https://i.imgur.com/0WbyNdr.gif" width="700" height="425">
</p>

#### Hashing a File via a command line argument
```bash
  > ./md5 --hashfile path-to/yourfile.txt
```
<p align="center">
  <img src = "https://i.imgur.com/eVUY9Fz.gif" width="700" height="425">
</p>

#### Hashing a String OR File via console menu
```bash
  > ./md5
```
<p align="center">
  <img src = "https://i.imgur.com/J4HNxfC.gif" width="700" height="425">
</p>

### Command Line Arguments
| Valid Arguments     | Input <br>Examples       | Output         | 
| :-------------: | :-------------: |:-------------:|
| --help | `./md5 --help`    | Will detail additional arguments and examples on how to execute them | 
| --test | `./md5 --test`    | Runs a suite of tests on local files adapted from the Request for Comments Document | 
| --hashstring | `./md5 --hashstring abc`    | Performs the MD5 hash on a String and returns the result | 
| --hashfile | `./md5 --hashfile path_to/yourfile.txt`    | Performs the MD5 hash on a file and returns the result | 

The arguments were implemented with help from the `GetOpt::Long` module. This allows quick definitions of Unix-like interfaces options into the program.

The Arguments could be declared and assigned to a character, in my case, after research [[24]](https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html) they were implemented as an array and associated with a single character meaning it could be utilized and delegated to a single Switch statement. Another benefit is that it could be specified whether to expect an additional argument, like in the case for both `--hashfile` and `--hashstring`.

```C
        static struct option long_options[] = {
            {"help"      , no_argument      , 0, 'h'},
            {"test"      , no_argument      , 0, 't'},
            {"hashfile"  , required_argument, 0, 'f'},
            {"hashstring", required_argument, 0, 's'}
        };
```

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
	* Add a byte and fill with 0's so that the length in bits of the padded message becomes congruent to 448 modulo 512
3. The message block is greater than 56 bytes and less than 64 bytes
	* Same as step two, add a byte and fill with 0's. A new block is added and fill 56 bytes with 0's

### Append Length
A 64 bit representation of the length of the message prior to bits being added is appended to the result of the previous step ensuring the message has a length that is an exact multiple of 16 (32-bit) words.

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
The other functions, G, H and I aren't too different from the F function. They function in bitwise parallel to produce their output in such a way that if the corresponding bits of X, Y and Z are independent and unbiased then as a result each bit of G(X,Y,Z), H(X,Y,Z) and I(X,Y,Z) will be independent and unbiased [[3]](https://tools.ietf.org/html/rfc1321).

Each 16-word block is processed, A is saved as AA, B as BB, C as CC, and D as DD then the following additions are performed
```C
     A = A + AA
     B = B + BB
     C = C + CC
     D = D + DD 
```
Each of the four registers are incremented by the value it had before the block was started.

### Output
The Message Digest should yield an output beginning at low-order byte of A and ending with the high-order byte of D [A,B,C,D].

## Project Implementation
If comments and constants were stripped out, the actual functional code would only consist of around less than one-hundred lines. In this brief summary of the implementation I plan to talk about how that chunk of functional code operates and interacts with other parts of the program. I'll be talking about declared constants and how they weave into the main chunks of code however since most of the low level operations were detailed [above](#how-does-it-work) this section will be more focused on giving a bit of a higher level overview of the overall implementation.

Upon launching the program, the ```main()``` method is executed initially, this method solely consists of a menu, allowing the user multiple [input options](#running-the-program). All input options lead down the same path, once an input is obtained it gets passed to the ```preMD5()``` function.
```C
void preMd5(FILE *infile) {
    BLOCK M;
    uint64_t nobits = 0;
    PADFLAG status = READ;
    WORD MD5_RES[] = {A, B, C, D};

    while (nextblock(&M, infile, &nobits, &status)) {
        md5(&M, MD5_RES);
    }
    output(MD5_RES);
}
```
The purpose of the ```preMD5()``` function is to handle the pre-processing of the message blocks and then delegate the processed blocks to the ```md5()``` method to perform the hashing rounds. ```WORD MD5_RES[] = {A, B, C, D}``` plays an important role in the program, the array consists of the four 32-bit register values that will be used and manipulated during the actual hashing rounds and will ultimately contain the final hash to be output to the user.

Before any of that happens the user defined input needs to be pre processed via the ```nextblock()``` function. This function processes and pads the message blocks based on the process outlined in the Request for Comments document [[3]](https://tools.ietf.org/html/rfc1321). A switch statement checks to see which of the three conditions outlined in the first section of [How does it work?](#how-does-it-work) is true, each message block that gets processed is passed into ```md5(&M, MD5_RES)``` as a parameter along with the array containing the four 32-bit register values needed to compute the hash.

The ```md5()``` function is the final processing step and is executed for each message individual message block.
```C
void md5(BLOCK *M, WORD *MD5_RES) {
    WORD a, b, c, d;
    a = MD5_RES[0];
    b = MD5_RES[1];
    c = MD5_RES[2];
    d = MD5_RES[3];

    for(int i = 0; i<64; i++) {
        if (i < 16) {
            FF(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]);
        } else if (i < 32) {
            GG(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]);
        } else if (i < 48) {
            HH(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]);
        } else {
            II(MD5_RES[AA[i]], MD5_RES[BB[i]], MD5_RES[CC[i]], MD5_RES[DD[i]], M->threetwo[MM[i]] , S[i] , T[i]);
        }
    }
    
    MD5_RES[0] += a;
    MD5_RES[1] += b;
    MD5_RES[2] += c;
    MD5_RES[3] += d;
}
```
Four temporary values (<i>a, b, c, d</i>) are initialized with the pre-hash values of each of the four 32-bit register values, this is so the old value can be accumulated with each new temporary value for each iteration. The four transformation rounds of hashing consisting of 64(16*4) steps were simplified into a for loop, this was accomplished by initializing the constant parameterized values into pre-defined constant arrays. Each of the four rounds consists of a transformation function that gets executed 16 times. All of the parameters are pre-defined constants with exception of the fifth parameter which contains the processed message block.

Once the four hashing rounds have concluded, the four temporary values that once contained the old 32-bit register values are now transformed, the next step is to add these transformed temporary values to the old 32-bit register values. This is repeated until all message blocks have undergone this process.

Once all the message blocks have been pre-processed and processed, the array ```WORD MD5_RES[] = {A, B, C, D}``` should now contain the final MD5 hash, however printing and outputting the current values won't yet yield the correct output, this is because the MD5 hash output should begin with the low-order byte of A, and end with the high-order byte of D (<i>little endian</i>). To ensure the output follows this rule, the output array must be processed via a function to correct this.
```C
void output(WORD MD5_RES[]) {
    printf("MD5 -> ");
    for (int i = 0; i < 4; ++i) {
        printf("%02x%02x%02x%02x", 
        (MD5_RES[i] >>  0) & 0xFF, 
        (MD5_RES[i] >>  8) & 0xFF, 
        (MD5_RES[i] >> 16) & 0xFF, 
        (MD5_RES[i] >> 24) & 0xFF);
    }
}
```
The ```output()``` function is called at the end of the program when the hashing rounds are complete. It's job is to display the result in little endian to ensure the output hash is correct. It works by using the bitwise operator ```>>``` which shifts the bits of each index of the array right by different amounts for each iteration of the loop for that index [[19]](https://stackoverflow.com/a/17913021). This ensures the output begins with the low-order byte of A and ends with the high-order byte D. Once all four final 32-bit register values are processed, the correct MD5 hash will be displayed to the user.

## Research and Development Diary
* <b>Week One</b>
	* The first week involved the setup of the repository and also getting setup on my Google cloud virtual machine. I also included a skeleton implementation of the program that just included some file readers and other basic functions. In preparation for the assignment I watched some related external videos that would help cement my understanding of the underlying concepts behind the project [[6]](https://www.youtube.com/watch?v=6h7_YAmtzGw) [[7]](https://www.youtube.com/watch?v=53O9J2J5i14).
* <b>Week Two</b>
	* During this week I completed the first video that discussed the SHA standard. I didn't fully understand everything in the video so I looked over the document in my own time [[2]](https://www.nist.gov/publications/secure-hash-standard) and watched a video [[9]](https://www.youtube.com/watch?v=DMtFhACPnTY) that helped provide a bit more insight. I also had a look at the main differences between MD5 and SHA [[8]](https://www.thesslstore.com/blog/difference-sha-1-sha-2-sha-256-hash-algorithms/) [[10]](https://stackoverflow.com/questions/2948156/algorithm-complexity-security-md5-or-sha1) which helped me get a handle on the main differences in terms of speed, amount of attacks required to find the original message, message digest length and security [[12]](https://stackoverflow.com/a/37235104).
* <b>Week Three</b>
	* I finished the [C bit operations](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/C_bit_operations/lookatbits.c) video and looked over the recommended document [[4]](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Expressions-and-Operators) and some examples and tutorials of bit manipulation in C [[5]](https://graphics.stanford.edu/~seander/bithacks.html) [[11]](https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm). I spent a good bit of time this week reading up on VI and learning some new editing and file commands [[13]](https://www.guru99.com/the-vi-editor.html).
* <b>Week Four</b>
	* This week I was a bit behind with videos so caught up on both [Functions and Constants in SHA](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Functions_and_constants_in_SHA/sha256.c) and [Padding](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Padding/padding.c). I attempted to code up some functions for MD5 by looking through the Request for Comments [[3]](https://tools.ietf.org/html/rfc1321) summary and began defining constants like the four auxiliary functions and constants for the transformation routine. Since I still wasn't fully sure of the fully process required for the MD5 algorithm I found an article [[14]](http://www.boblandstrom.com/the-md5-hashing-algorithm/) that helped simplify the whole process for me, I got a better understanding of the role of auxiliary functions in the block processing and how each sixteen operations of the four rounds work.
* <b>Week Five</b>
	* I coded up the [Unions in C](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Unions/unions.c) video but didn't fully understand what was meant by storing different data types in the same location. I looked at some tutorials [[15]](https://www.tutorialspoint.com/cprogramming/c_unions.htm) [[16]](https://www.programiz.com/c-programming/c-unions) and got a bit of a better understanding of how a unions members are accessed and the main differences between unions and structures, like for example how a union variable will always be the size of it's largest element unlike a struct where it's size is accumulative. Since big and little endian was mentioned in the video I did some reading on that also [[17]](https://www.geeksforgeeks.org/little-and-big-endian-mystery/) just to get a surface level understanding of byte order representation. I also included a union block in my MD5 project file and integrated it with code that was already written. 
* <b>Week Six & Week Seven</b>
	* I was behind a week so caught up on the [Hash Function](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Hash_function/Hash_implementation.c) video as well as [Finalizing Padding](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Finalizing_Padding/Finalizing_padding.c). With reference to both these videos and to the Request for Comments [[3]](https://tools.ietf.org/html/rfc1321) document I radically changed the contents of my main MD5 project file. My project file now contained all MD5 constants and a function that would perform the MD5 hash on an input albeit a rough implementation. The output wasn't correct and I suspect it to be an issue with how the message blocks are padded.
* <b>Week Eight</b>
	* During this week I completed the final video available to us, [Refactoring SHA256](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Video_Code/Refactoring_Sha256/sha.c). The video led me to look over the MD5 code I had written already and check every constant and function to ensure they were written correctly. I did find some errors with auxiliary functions and values that weren't initialized correctly however my hash output still wasn't correct.  
* <b>Week Nine</b>
	* Having completed the videos I focused solely on the MD5 implementation. I refactored and simplified the function that performs the hash rounds for each block into a single loop by defining the parameterized input values as constant arrays. I also fixed issues with block processing including the context not changing correctly and cases not executing correctly in the switch statement. I was still getting the wrong output so began looking at methods in C to ensure output will always be in little endian (<i>as required for MD5</i>) [[18]](https://stackoverflow.com/questions/54548061/c-little-and-big-endian-confusion).
* <b>Week Ten</b>
	* After multiple attempts and testing of different endian solutions one was found that successfully extracts individual bytes from each input value in little endian [[19]](https://stackoverflow.com/a/17913021). Following the implementation of the little endian solution and some changes to the 32 bit output value array the program successfully output correct MD5 values. Once it correctly worked I again began to refactor and comment as much code as I could, included a menu that allowed easy traversal and multiple input options and began to perform more [tests](#testing) against the project to verify results.
* <b>Week Thirteen</b>
	* Following the sudden societial change, the project scope has been revised. This revision includes additional command-line argument functionality, a document containing a report on the overall project with a fixed structure as well as amplified testing. This week I got to work on the command line functionality. After researching and learning about the ```getopt()``` function which is used to parse command line arguments [[22]](https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html) [[23]](https://www.youtube.com/watch?v=SjyR74lbZOc&t=). I attempted to implement some basic arguments and code, however after further resarch discovered the ```getopt() long``` option. Instead of, for example, declaring ```md5.exe -h``` for help, it would allow long arguments including ```md5.exe --help```, allowing for more possibilities including ```md5.exe --hashfile <path_to_file.txt>``` [[24]](https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html). I felt this to be a cleaner and more straight forward method of implementing the arguments.
* <b>Week Fourteen</b>
	* Finish this when most of the Overview is finished
	
## Testing
The project was tested on both Linux and Windows machines to ensure portability and accuracy. The results were also compared against external MD5 calculation sources [[20]](https://www.md5hashgenerator.com/) [[21]](http://www.md5.cz/).

The contents of the following tests are contained within the `Program/test-input` folder. The test data was obtained from page 21 of the the Request for Comments document [[3]](https://tools.ietf.org/html/rfc1321).

#### First Test

| Test | String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 1 | Empty<br>String    | d41d8cd98f00b204e9800998ecf8427e | d41d8cd98f00b204e9800998ecf8427e | :white_check_mark: |

#### Second Test

| Test |String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 2 | a    | 0cc175b9c0f1b6a831c399e269772661 | 0cc175b9c0f1b6a831c399e269772661 | :white_check_mark: |

#### Third Test

| Test | String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 3 | abc    | 900150983cd24fb0d6963f7d28e17f72 | 900150983cd24fb0d6963f7d28e17f72 | :white_check_mark: |

#### Fourth Test

| Test |String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 4 | message<br>digest    | f96b697d7cb7938d525a2f31aaf161d0 | f96b697d7cb7938d525a2f31aaf161d0 | :white_check_mark: |

#### Fifth Test

| Test |String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 5 | abcdefg<br>hijklm<br>nopqrst<br>uvwxyz    | c3fcd3d76192e4007dfb496cca67e13b | c3fcd3d76192e4007dfb496cca67e13b | :white_check_mark: |

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
[22] https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html <br>
[23] https://www.youtube.com/watch?v=SjyR74lbZOc&t= <br>
[24] https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
