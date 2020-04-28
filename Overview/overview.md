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
The repository is constructed to be as simplistic as possible, contents were separated into their relevant directories and irrelevant files and documents were excluded, leaving only files relevant to the compilation, research and testing of the program.

* Program
    * All code relevant to the running of the actual program will be contained within this folder. The `md5.c` file is contained here along with test files which are required for running the test suite within the program. The program processes an input file or string of any length and yields a fixed-length 128 bit '<b><i>fingerprint</i></b>'. The program may be ran in [more than one way](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Overview/overview.md#command-line-arguments). For a lower-level explanation of the overall implementation see the [coding section](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/README.md#project-implementation) of the README, which provides a detailed breakdown of the code aspect of the project</i>. <br><br>Additionally, a single library (getopt.h) is present in this directory. After testing the program on different platforms I made the decision to manually include it within the project. I had no problems running the program on a Linux machine, however on Windows I experienced compatibility problems. After investigating, I found including the library manually here would mean anyone with a compiler could clone the project and execute it without experiencing any compatibility issues [[1]](https://stackoverflow.com/a/10404524/12314065). 
    
* Video Code
    * Instructional and educational videos were provided over the course of the module. These videos were written up and served as a helpful foundation and reference point during the development process. I chose to keep the videos within the project but within their own directory for both referential and development reasons.  
    
* Overview
    * Following undesirable external circumstances, the scope of the project shifted. This shift in scope meant a thoroughly documented report of the project and it's related material was to be included in the repository along with previously included items. 

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
3. <b>Navigate to ```/Program```:</b> ```cd FourthYear_TheoryOfAlgorithms/Program```
4. <b>Compile the Program:</b> ```gcc md5.c -o md5```
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

<p align="center">
  <img src = "https://i.imgur.com/CYz7hPV.png" width="400" height="500">
   <br>
  <b>Visual Representation of the Compression Function (64 Rounds)</b><br><i>Made with <a href="http://asciiflow.com/">Asciiflow</a></i>
</p>

### Output
The Message Digest should yield an output beginning at low-order byte of A and ending with the high-order byte of D [A,B,C,D].

#### <i>What does One-Way mean?</i>
In relation to [Cryptographic Hash Functions](https://en.wikipedia.org/wiki/Cryptographic_hash_function) <b>one-way</b> essentially means there is no way to knowingly reverse the hash. It's important to note a hash is not encryption as it <b>cannot</b> be decrypted back to the original text [[4]](https://www.sciencedirect.com/topics/computer-science/one-way-hash-function). This will be discussed further in the [Complexity](#complexity-of-md5) section.

#### <i>What is MD5 Used For?</i>
In regards to [collisions](https://en.wikipedia.org/wiki/Collision_attack), MD5 is already long broken, meaning it is still a valid hashing algorithm, however it is not a <b>secure</b> hashing algorithm and should absolutely <b>not</b> be used for any delicate information. However, MD5 is still used widely today to validate the integrity of files. Consider the following image, 

<p align="center">
  <img src = "https://i.imgur.com/YbJOSWL.png" width="400" height="400">
   <br>
  <b>Illustrating the transmission use for MD5</b><br><i>Made with <a href="http://asciiflow.com/">Asciiflow</a></i>
</p>

Assume that the file hash sent to the downloader didn't match the hash value performed by the downloader on the file. This would indicate there was interference with the file being sent during transmission since the digital fingerprints don't match.

Unfortunately, with MD5 this is possible since it's not a <b>secure</b> hash algorithm. <b>Collisions</b> may occur, meaning different inputs may yield the same output. Now consider if the file being sent by the distributor is intercepted and tampered with during transmission, but the downloader when hashing the file still receives a valid matching MD5 hash, which indicates that the downloaded file is safe even though the file was interfered with, this is possible because MD5 is <b>not secure</b>, meaning an output (hash), may have multiple inputs (content to be hashed).

However, the chance of collisions occurring is still incredibly small, standing at (1/2<i><sup>128</sup></i>), a colossally small chance. With that said, if all the hashes are kept as they're hashed, the chance of a collision is increased massively due to the Birthday Principle [[10]](https://en.wikipedia.org/wiki/Birthday_problem), which will be discussed in a further section along with similar concepts.

## Complexity of MD5
MD5 is a relatively fast hashing algorithm which runs in <i>O(N)</i> time, just like SHA-256 <i>(one of many other hashing algorithms)</i>. Hash function implementations generally hold linear run times in relation to their input, which is somewhat the point of the functions. With that said, MD5 computes its hash in just over a quarter of the time it takes SHA-256.

<p align="center">
  <img src = "https://i.imgur.com/KvBiTJI.png" width="345" height="225">
   <br>
  <i><b>Comparison of Running Time between MD5 Algorithm and SHA256 Algorithm <a href="https://iopscience.iop.org/article/10.1088/1742-6596/978/1/012116/pdf"></b></i>[15]</a>
</p>

Being faster does not mean better in this case, ideally hashing algorithms shouldn't be aiming for speed for security reasons, being too fast would make the algorithm weaker against most forms of attack, allowing attackers an easier route to generate collisions. Being able to calculate 1,000,000,000 hashes per second instead of 10,000 increases the speed and penetrability of [Brute-Force Attacks](https://en.wikipedia.org/wiki/Brute-force_attack) significantly. 

<p align="center">
  <img src = "https://i.imgur.com/bI5O5oN.png" width="345" height="225">
   <br>
  <i><b>Computational Complexity of MD5 <a href="https://daoyuan.li/exploring-the-performance-of-md5-efficiency-and-security/"></b></i>[18]</a>
</p>

Algorithms like SHA-256 don't necessarily have to worry about this as much, in 2015, [Bitcoin](https://bitcoin.org/en/) was at one point computing 300 quadrillion (300 x 10<sup>15</sup>) SHA-256 hashes a second [[11]](https://en.bitcoin.it/wiki/Hash_per_second). If you were to attempt a collision attack and needed to calculate 2<sup>128</sup> hashes at 300 quadrillion hashes a second it would take 10<sup>13</sup> years to find a collision. Brute forcing would not be a viable option. Naturally this would bring up the question,<i> “Is there a way to reverse a calculated hash back to it's original state reliably?”</i> This is where the [P versus NP](https://en.wikipedia.org/wiki/P_versus_NP_problem) problem becomes relevant.

### P versus NP
P versus NP is a controversial problem in computer science, it asks whether every problem whose solution can be quickly verified can also be solved by an algorithm running in <b>polynomial</b> time, such that the time to complete the task varies as a <b>polynomial</b> function on the size of the input to the algorithm [[12]](https://en.wikipedia.org/wiki/P_versus_NP_problem). 

#### <i>Polynomial-time Algorithm</i>
A Polynomial-time Algorithm is defined by the [Handbook of Applied Cryptography](http://cacr.uwaterloo.ca/hac/) as: <b><i>“ An algorithm whose worst-case running time function is of the form O(n<sup>k</sup>), where n is the input size and k is a constant”</i></b><br><br> Any algorithm whose running time cannot be so bounded is called an exponential-time algorithm [[17]](http://cacr.uwaterloo.ca/hac/about/chap2.pdf).

### P versus NP <i>(Continued)</i>
Over the years there have been a colossal list of papers and claims that attempt to 'settle' the question, with none being able to provide a concrete answer [[16]](https://www.win.tue.nl/~gwoegi/P-versus-NP.htm)<br><br> As mentioned in previous sections, MD5 is a <b>one-way</b> function, there is no known algorithm for reliably converting an output hash into it's original pre-hash value in <b>polynomial time</b> <i>(O(n<sup>k</sup>))</i>, brute-forcing is currently the best alternative, with methods and principles employed including [The Birthday Principle] which is one of the more well known of many.

#### The Birthday Principle
To briefly demonstrate this principle, assume a teacher has a class of 30(n) students. The teacher asks all students their birthday to determine if any students have the same birthday (<i>Liken this to checking 30 hashes individually for a collision</i>).
<br><br>Now assume the teacher picked the date `June 25th`, the chance any of her 30 students were born on that specific day is <i>7.9%</i> (1 - (364/365)<sup>30</sup>). On the same token, if she once again asked individual students for their birthday, assume the first student she asks has their birthday occur on `April 3rd`, the chance one of the remaining 29 students shares their birthday goes up to <i>70%</i> (1 - 365!/(365 - n)!∙365<sup>n</sup>) [[11]](https://en.wikipedia.org/wiki/Birthday_attack).

A [Birthday Attack](https://en.wikipedia.org/wiki/Birthday_attack) is based on this principle. A Birthday Attack is one of many cryptographic attacks that belongs to a class of brute force attacks [[5]](https://ad-pdf.s3.amazonaws.com/papers/wp.MD5_Collisions.en_us.pdf). The success of the attack almost completely depends on the increased likelihood of collisions matching between random attack attempts and a constant degree of permutations. [[12]](https://www.geeksforgeeks.org/birthday-attack-in-cryptography/)

### P versus NP <i>(Continued)</i>
Many hash functions can be reversed in polynomial time, for example the function <b><i>f(x)=(5x+7) mod 2<sup>32</sup></i></b>, however, <b>cryptographic</b> hashes are all (<i>as mentioned previously</i>) <b>one-way</b> functions, and these types of functions are closely tied to the <b>NP</b> <i>(nondeterministic polynomial time)</i> complexity class.<br><br>These functions are considered to be, “<b><i>functions</i></b> (over binary strings) <b><i>which can be computed in polynomial-time, but for which any randomized polynomial-time inverse succeeds with only negligible probability</i></b>” [[13]](https://en.wikipedia.org/wiki/One-way_function). The class of NP problems doesn't conform fully with this, both because randomized approaches aren't compatible with the NP class (<i><b>RP being more applicable</b></i> [[14]](https://people.eecs.berkeley.edu/~luca/cs278-04/notes/lecture08.pdf)) and because NP is reliant on worst-case behavior, while one-way functions must have good average-case behavior [[12]](https://arxiv.org/pdf/cs/0606037.pdf).

As well as both complexity classes <b>P</b> and <b>NP</b>, there exist other sets of decisional problems including <b>co-NP</b> and <b>NPC</b>.

* <b>co-NP</b>
	* The set of all decision problems for which a NO answer can be verified in polynomial time using an appropriate certificate [[17]](http://cacr.uwaterloo.ca/hac/about/chap2.pdf).
* <b>NPC</b>
	* NP-complete problems, problems within <b>NP</b> that are considered the hardest contained within the complexity class in the sense that they are at least as difficult as every other problem in NP.
	
<p align="center">
  <img src = "https://i.imgur.com/6ENl8zw.png" width="490" height="225">
   <br>
  <i><b>Conjectured relationship between the complexity classes P, NP, co-NP, and NPC. <a href="http://cacr.uwaterloo.ca/hac/about/chap2.pdf"></b></i>[17]</a>
</p>

It's not known whether one-way functions <i>truly</i> exist, if they do then it would show P <b>!=</b> NP, on the same token it is also not known if the reverse is true, whether P <b>!=</b> NP proves that one-way functions exist.

#### Grover's Algorithm

## Command Line Arguments
The C programming language allows for the use of command-line arguments. Command-line arguments allow data to be provided to the program at runtime. Arguments can be passed to the main method if the main method is declared as follows

```C
int main(int argc, char *argv[]) {

}
```

The program in this case can take two arguments, an integer called `argc` and a character array called `*argv[]`.

* `argc`
    * Conventionally, `argc`, which stands for argument count, retrieves the amount of arguments the program has just taken. For example, if the following was ran `./md5 one two three`, argc would be equal to four, since it includes the actual program declaration [[3]](http://117.3.71.125:8080/dspace/bitstream/DHKTDN/6554/1/The%20C%20Programming%20Language4603.pdf).
    
* `*argv[]`
    * Meaning 'argument vector', `argv[]` is an array containing the command line arguments. Looking at the previous example, if the input was `./md5 one two three`, `argv[]` would be of size four, the first index being `md5`, the second being `one` and so on [[3]](http://117.3.71.125:8080/dspace/bitstream/DHKTDN/6554/1/The%20C%20Programming%20Language4603.pdf).

### Functional Command Line Arguments
The table below contains a list of valid command-line arguments specific to the program, an example of how to input them and also their output.
<p align="center">
    <b><i><br>The input examples are written for Debian-based Linux machines, for Windows, simply replace './md5' with 'md5.exe', assuming you have followed the compilation steps outlined in the <a href="https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms/blob/master/Overview/overview.md#running-the-program">above section</a></i></b>
</p>

| Valid Arguments     | Input <br>Examples       | Output         | 
| :-------------: | :-------------: |:-------------:|
| --help | `./md5 --help`    | Will detail additional arguments and examples on how to execute them | 
| --test    | `./md5 --test`    | Runs a suite of tests on local files adapted from the Request for Comments Document | 
| --explain | `./md5 --explain`    | Displays a brief explanation of MD5 including an ASCII high-level diagram | 
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

The contents of the following tests are contained within the `Program/test-input` folder. The test data was obtained from page 21 of the Request for Comments document [[6]](https://tools.ietf.org/html/rfc1321) and the same tests may be ran via the ```--test``` command-line operator, expected results are hardcoded and actual results are generated at runtime, ensuring validity.

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
	<i><b>When testing the exact same file with the exact same contents on the VM ..</b></i>
</p>

| Test | File/String        | Expected Result           | Actual Result  | Pass or Fail     |
| :-------------: | :-------------: |:-------------:| :-------------:|:-------------:|
| Debian VM | ```md5.c```    | 44b8553838796fc0d7540a5b36362640 | 59a382706592547690fda03d49b515ae | :x: |

Following searches and attempts to find the answer I discovered this [post](https://stackoverflow.com/a/24031902/12314065) which explained this is likely due to different line endings depending on the system.

* Windows
     * Both CR(<b><i>\r</i></b>) and LF(<b><i>\n</i></b>) can be used to terminate lines
* MAC
     * CR(<b><i>\r</i></b>) is alone used to terminate lines
* UNIX
     * LF(<b><i>\n</i></b>) is alone used to terminate lines
	 
Following research [[9]](https://www.codeproject.com/Answers/1107399/Delete-carriage-return-and-line-feed-on-file-using#answer2), the best way I gathered to address the issue would be to remove line endings completely. 
```C
    const char *remove_any_of = "\n\r";
    int c;
    while((c = getchar()) != EOF) {
        if (!strchr(remove_any_of, c)) putchar(c);
    }
    return EXIT_SUCCESS;
```
This would mean reading the file byte-by-byte and checking for line endings. This won't be a feature I'll be able to implement before the project submission date however it will be something I'd like to fix up at some point in the future.


## Conclusion

## References
* [1] https://stackoverflow.com/a/10404524/12314065 
	* Lead me to include the Getopt library in the repository so those cloning wouldn't experience portability issues. <br>
* [2] https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Options.html#Getopt-Long-Options
	* How to parse options with getopt_long, helped a lot when trying to implement long command-line arguments. <br>
* [3] http://117.3.71.125:8080/dspace/bitstream/DHKTDN/6554/1/The%20C%20Programming%20Language4603.pdf
	* Some reading I did on command-line arguments, how they work, what they're used for and how to implement them. (<b>Pages 102 - 105</b>) <br>
* [4] https://www.sciencedirect.com/topics/computer-science/one-way-hash-function
	* Helped with polishing off my knowledge of hash functions / cryptographic hash functions. Also talks about MD5 under the headlines of one-way hashing and vunerabilities. <br>
* [5] https://ad-pdf.s3.amazonaws.com/papers/wp.MD5_Collisions.en_us.pdf
	* Great source for how collisions impact MD5 and other hash algorithms generally. I decided to include the section about the Birthday Problem after reading this since I felt it'd be a good addition to explaining, or at least helping explain collisions. <br>
* [6] https://tools.ietf.org/html/rfc1321
	* Request for Comments document outlining the processes involved and required for the MD5 algorithm. The code implementation was almost entirely based on this document give or take some sections. <br>
* [7] https://www.md5hashgenerator.com/
	* Website that was used to generate MD5 hashes for testing. <br> 
* [8] http://www.md5.cz/ 
	* Same as above, the second website that was used to generate MD5 hashes for testing just to be 100% safe.<br>
* [9] https://www.codeproject.com/Answers/1107399/Delete-carriage-return-and-line-feed-on-file-using#answer2
	* Found this solution when looking for answers on how to deal with the line-breaks on different systems. <br>
* [10] https://devhints.io/vim
	* Great cheatsheet that was used for getting the hang of different commands and miscellaneous functions in [Vim](https://www.vim.org/). <br>
* [11] https://en.bitcoin.it/wiki/Hash_per_second
	* A little bit of trivia I found that I thought was interesting enough to be included in the complexity section about the rate at which Bitcoin's hashes were being performed. <br>
* [12] https://arxiv.org/pdf/cs/0606037.pdf
	*  TODO (pg 5)  <br>
* [13] https://en.wikipedia.org/wiki/One-way_function
	* TODO <br>
* [14] https://people.eecs.berkeley.edu/~luca/cs278-04/notes/lecture08.pdf
	* TODO <br>
* [15] https://iopscience.iop.org/article/10.1088/1742-6596/978/1/012116/pdf
	* TODO <br>
* [16] https://www.win.tue.nl/~gwoegi/P-versus-NP.htm
	* TODO <br>
* [17] http://cacr.uwaterloo.ca/hac/about/chap2.pdf
	* TODO <br>
* [18] https://daoyuan.li/exploring-the-performance-of-md5-efficiency-and-security/
	* Isn't a whole lot to this link, found while researching MD5 & complexity, had a nice graph that I felt would be a nice inclusion to the complexity section.
