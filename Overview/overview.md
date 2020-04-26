<p>
  <h2 align="center">Theory of Algorithms</h2>
  <i><h4 align="center">An In-Depth Report of the Overall Project</h4></i>
</p>

## Contents of the Report
* [Introduction](#introduction)
* [Running the Program](#running-the-program)
* [How MD5 Works](#how-md5-works) 
* [Complexity of MD5](#complexity-of-md5)
* [Command Line Arguments](#command-line-arguments)
* [Testing the Program](#testing-the-program)
* [Conclusion](#conclusion)
* [References](#references)

## Introduction
This section will serve as a brief overview of the repository, it's contents and the functionality of the code contained within it.

### Repository Structure
```
FourthYear_TheoryOfAlgorithms
├── README.md 
├── Program               
│   ├── md5.c  
|   | 
│   ├── test-input    
|   |   └── files_for_testing.txt
|   | 
│   └── libraries
|       └── getopt.h
|
├── Video_Code
|   └── module_videos   
|       └──...
|
└── Overview
    └── Overview.md
```
#### Repository Design
The repository is construted to be as simplistic as possible, contents were seperated into their relevant directories and irrelevant files and documents were excluded, leaving only files relevant to the compilation, research and testing of the program.

* Program
    * All code relevant to the running of the actual program will be contained within this folder. The `md5.c` file is contained here along with test files which are required for running the test suite within the program. <br><br>Additionally, a single library (getopt.h) is present here. After testing the program on different platforms I made the decision to manually include it within the project. I had no problems running the program on a Linux machine, however on Windows I experienced compatibility problems. After investigating, I found including the library manually here would mean anyone with a compiler could clone the project and execute it without experiencing any compatibility issues [[1]](https://stackoverflow.com/a/10404524/12314065). <i>For an overview on what the code does [see](#https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/README.md#project-implementation) which provides a detailed breakdown of the implementation</i>.
    
* Video Code
    * Instructional and educational videos were provided over the course of the module. These videos were written up and served as a helpful foundation and reference point during the development process. I chose to keep the videos within the project but within their own directory for both referencial and development reasons.  
    
* Overview
    * Following undesireable external circumstances, the scope of the project shifted. This shift in scope meant a thorougly documented report of the project and it's related material was to be included in the repository along with previously included items. 

## Running the Program
Prerequisite steps may be required before running the program and these steps vary depending on Platform. This section will be divided into instructions for Windows and Debian-based Linux systems.

<h3 align="center">
  Running on Debian-based Linux Systems
</h3>

<p align="center">
  The following prerequisite steps are required to clone and execute the program on <b>Debian-based</b> machines<b><i><br>You may skip the following two steps if they don't apply</i></b>, 
</p>

##### 1. Installing the GCC Compiler
1. <b>Open a Command Prompt</b>
2. <b>Type:</b> ```$ sudo apt install gcc```
3. <b>Confirm installation:</b> ```$ gcc --version```  

##### 2. Installing Git
1. <b>Open a Command Prompt</b>
2. <b>Type:</b> ```$ sudo apt install git```
3. <b>Confirm installation:</b> ```$ git --version```  

#### Cloning and Executing the Program
1. <b>Open a Command Prompt</b>
2. <b>Type:</b> ```$ git clone https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms```
3. <b>Navigate to ```/Program```:</b> ```$ cd FourthYear_TheoryOfAlgorithms/Program```
4. <b>Compile the Program:</b> ```$ gcc md5.c -o md5```
5. <b>Execute the Program:</b> ```$ ./md5```

<p align="center">
    <i><b>See the <a href="https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Overview/overview.md#command-line-arguments">Command Line Arguments</a> section for alternative approaches to executing the program</b></i>
</p>

<h3 align="center">
  Running on Windows-based Systems
</h3>
  
<p align="center">
  The following prerequisite steps are required to clone and execute the program on <b>Windows-based</b> machines<b><i><br>You may skip  the following two steps if they don't apply</i></b>,  
</p>

##### 1. Installing the GCC Compiler
1. <b>Download and Install [MinGW](https://sourceforge.net/projects/mingw/) for Windows</b>
2. <b>Open a Command Prompt</b>
3. <b>Type:</b> ```mingw-get install gcc``` 
3. <b>Confirm Instillation:</b> ```gcc --version``` 
  
##### 2. Installing Git
1. <b>Download and Install [Git](https://git-scm.com/download/win)</b>
2. <b>Open a Command Prompt</b>
3. <b>Confirm Instillation:</b> ```git --version```

#### Cloning and Executing the Program
1. <b>Open a Command Prompt</b>
2. <b>Type:</b> ```git clone https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms```
3. <b>Navigate to ```/Program```:</b> ```$ cd FourthYear_TheoryOfAlgorithms/Program```
4. <b>Compile the Program:</b> ```$ gcc md5.c -o md5```
5. <b>Execute the Program:</b> ```md5.exe```

<p align="center">
    <i><b>See the <a href="https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Overview/overview.md#command-line-arguments">Command Line Arguments</a> section for alternative approaches to executing the program</b></i>
</p>

## How MD5 Works
The MD5 hash function was initially developed as a stronger alternative to the [MD4](https://en.wikipedia.org/wiki/MD4) hash function. MD5 consists of five major steps [[6]](https://tools.ietf.org/html/rfc1321).

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
A four word buffer is required to generate the message digest. A 'word' is essentially defined as a 32 bit register [[6]](https://tools.ietf.org/html/rfc1321), these four words are initialized with the following values

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
The other functions, G, H and I aren't too different from the F function. They function in bitwise parallel to produce their output in such a way that if the corresponding bits of X, Y and Z are independent and unbiased then as a result each bit of G(X,Y,Z), H(X,Y,Z) and I(X,Y,Z) will be independent and unbiased [[6]](https://tools.ietf.org/html/rfc1321).

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

#### <i>What does One-Way mean?</i>
In relation to [Cryptographic Hash Functions](https://en.wikipedia.org/wiki/Cryptographic_hash_function) <b>one-way</b> essentially means there is no way to knowingly reverse the hash. It's important to note a hash is not encryption as it <b>cannot</b> be decrypted back to the original text [[4]](https://www.sciencedirect.com/topics/computer-science/one-way-hash-function).

#### <i>What is MD5 Used For?</i>
In regards to [collisions](https://en.wikipedia.org/wiki/Collision_attack), MD5 is already broken, meaning it is still a valid hashing algorithm, however it is not a <b>secure</b> hashing algorithm. A major function of MD5 was validating the integrity of files. Consider the following image, 

<p align="center">
  <img src = "https://i.imgur.com/YbJOSWL.png" width="400" height="400">
   <br>
  <b>Illustrating the transmission use for MD5</b><br><i>Made with <a href="http://asciiflow.com/">Asciiflow</a></i>
</p>

Assume that the file hash value that was sent to the downloader didn't match the hash value performed by the downloader on the file. This would indicate there was interferrence with the file being sent during transmission since the digital fingerprints don't match.

Unfortunately, with MD5 this is possible since it's not a <b>secure</b> hash algorithm. <b>Collisions</b> may occur, meaning different inputs may yield the same output. Now consider if the file being sent by the distributor is intercepted and tampered with during transmission, but the downloader when hashing the file still receives a valid MD5 hash that should indicate that it's safe even though the file was interfered with. This is possible because MD5 is <b>not secure</b>, meaning an output (hash), may have multiple inputs (content to be hashed) [[5]](https://ad-pdf.s3.amazonaws.com/papers/wp.MD5_Collisions.en_us.pdf).

## Complexity of MD5

## Command Line Arguments
The C programming language, like most others, allow for the use of command-line arguments. Command-line arguments allow data to be provded to the program at runtime. Arguments can be passed to the main method if the main method is declared as follows

```C
int main(int argc, char *argv[]) {

}
```
The program in this case can take two arguments, an integer called `argc` and a character array called `*argv[]`.

* `argc`
    * Conventially, `argc`, which stands for argument count, retrieves the amount of arguments the program has just taken. For example, if the following was ran `./md5 one two three`, argc would be equal to four, since it includes the actual program declaration [[3]](http://117.3.71.125:8080/dspace/bitstream/DHKTDN/6554/1/The%20C%20Programming%20Language4603.pdf).
    
* `*argv[]`
    * Meaning 'argument vector', `argv[]` is an array containing the command line arguments. Looking at the previous example, if the input was `./md5 one two three`, `argv[]` would be of size four, the first index being `md5`, the second being `one` and so on [[3]](http://117.3.71.125:8080/dspace/bitstream/DHKTDN/6554/1/The%20C%20Programming%20Language4603.pdf).

### Functinal Command Line Arguments
The table below contains a list of valid command-line arguments specific to the program, an example of how to input them and also their output.
<p align="center">
    <b><i><br>The input examples are written for Debian-based Linux machines, for Windows, simply replace './md5' with 'md5.exe', assuming you have followed the compilation steps outlined in the <a href="https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Overview/overview.md#running-the-program">above section</a></i></b>
</p>

| Valid Arguments     | Input <br>Examples       | Output         | 
| :-------------: | :-------------: |:-------------:|
| --help | `./md5 --help`    | Will detail additional arguments and examples on how to execute them | 
| --test    | `./md5 --test`    | Runs a suite of tests on local files adapted from the Request for Comments Document | 
| --explain | `./md5 --explain`    | Displays a brief explaination of MD5 including an ASCII high-level diagram | 
| --hashstring | `./md5 --hashstring abc`    | Performs the MD5 hash on a String and returns the result | 
| --hashfile | `./md5 --hashfile path_to/yourfile.txt`    | Performs the MD5 hash on a file and returns the result | 

The arguments were implemented with help from the `GetOpt::Long` module. This allows quick definitions of Unix-like interface options into the program.

The Arguments can be declared and assigned to a character, in my case, after reading about the topic [[2]](https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html), I implemented them as an array and associated the argument with a single character, meaning it could be utilized and delegated to a single Switch statement. Another benefit is that it could be specified whether to expect an additional argument, like in the case for both `--hashfile` and `--hashstring`.

```C
        static struct option long_options[] = {
            {"help"      , no_argument      , 0, 'h'},
            {"test"      , no_argument      , 0, 't'},
            {"explain"   , no_argument      , 0, 'e'},
            {"hashfile"  , required_argument, 0, 'f'},
            {"hashstring", required_argument, 0, 's'}
        };    
```
## Testing the Program
The project was tested on both Linux and Windows machines to ensure portability and accuracy. The results were also compared against external MD5 calculation sources [[7]](https://www.md5hashgenerator.com/) [[8]](http://www.md5.cz/).

The contents of the following tests are contained within the `Program/test-input` folder. The test data was obtained from page 21 of the the Request for Comments document [[6]](https://tools.ietf.org/html/rfc1321) and the same tests are runnable via the ```--test``` command-line operator, expected results are hardcoded and actual results are generated at runtime, ensuring validility.

#### First Test

| Test | File/String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 1 | Empty<br>String    | d41d8cd98f00b204e9800998ecf8427e | d41d8cd98f00b204e9800998ecf8427e | :white_check_mark: |

#### Second Test

| Test | File/String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 2 | a    | 0cc175b9c0f1b6a831c399e269772661 | 0cc175b9c0f1b6a831c399e269772661 | :white_check_mark: |

#### Third Test

| Test | File/String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 3 | abc    | 900150983cd24fb0d6963f7d28e17f72 | 900150983cd24fb0d6963f7d28e17f72 | :white_check_mark: |

#### Fourth Test

| Test | File/String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 4 | message<br>digest    | f96b697d7cb7938d525a2f31aaf161d0 | f96b697d7cb7938d525a2f31aaf161d0 | :white_check_mark: |

#### Fifth Test

| Test | File/String Input       | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Test 5 | abcdefg<br>hijklm<br>nopqrst<br>uvwxyz    | c3fcd3d76192e4007dfb496cca67e13b | c3fcd3d76192e4007dfb496cca67e13b | :white_check_mark: |

### Testing Conclusion
Testing small strings and files turned out to be fully successful, however there were issues encountered when testing large files, included below (<i>Expected result was chosen to be the Windows generated result since it was the first system to generate the hash for that file on and I needed something to compare the VM hash against</i>).

| Test | File/String        | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Windows | ```md5.c```    | 44b8553838796fc0d7540a5b36362640 | 44b8553838796fc0d7540a5b36362640 | :white_check_mark: |

<p align="center">
	
	<i><b>When testing the exact same file with the exact same contents..</b></i>
</p>

| Test | File/String        | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Debian VM | ```md5.c```    | 44b8553838796fc0d7540a5b36362640 | 59a382706592547690fda03d49b515ae | :x: |

Following searches and attempts to find the answer I discovered this [post](https://stackoverflow.com/a/24031902/12314065) which explained this is likely due to different line endings depending on the system.

* Windows
     * Both CR(\r) and LF(\n) can be used to terminate lines
* MAC
     * CR(\r) is alone used to temrinate lines
* UNIX
     * LF(\n) is alone used to terminate lines

```C
    const char *remove_any_of = "\n\r";
    int c;
    while((c = getchar()) != EOF) {
        if (!strchr(remove_any_of, c)) putchar(c);
    }
    return EXIT_SUCCESS;
```
Following research [[9]](https://www.codeproject.com/Questions/1107228/Delete-carriage-return-and-line-feed-on-file-using), the best way I gathered to address the issue would be to remove line endings completely. This would mean reading the file byte-by-byte and checking for line endings. This won't be a feature I'll be able to implement before the project submission date however it will be something I'd like to fix up at some point in the future.

## Conclusion

## References
[1] https://stackoverflow.com/a/10404524/12314065 <br>
[2] https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html <br>
[3] http://117.3.71.125:8080/dspace/bitstream/DHKTDN/6554/1/The%20C%20Programming%20Language4603.pdf <i>(Page 102 - 105)</i><br>
[4] https://www.sciencedirect.com/topics/computer-science/one-way-hash-function <br>
[5] https://ad-pdf.s3.amazonaws.com/papers/wp.MD5_Collisions.en_us.pdf <br>
[6] https://tools.ietf.org/html/rfc1321 <br>
[7] https://www.md5hashgenerator.com/ <br>
[8] http://www.md5.cz/ <br>
