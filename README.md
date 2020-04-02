<p>
  <h2 align="center">MD5 Hash Digest Calculator</h2>
  <i><h3 align="center">A Program written in C that calculates the MD5 hash digest of an input</h3></i>
</p>

## Project Details

|Details  |    |
| --- | --- |
| **Project**  | [Project Spec](https://pdfhost.io/v/lgILkbKAl_project_8pdf.pdf) 
| **GIF** | [TODO](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithims)
| **Course** | BSc (Hons) in Software Development
| **Module** |  Theory of Algorithims |
| **Author** | [Faris Nassif](https://github.com/farisNassif) |
| **Lecturer** | Dr Ian McLoughlin |

## MD5 Overview
The MD5 hash works by taking a string of any length and encoding it into a 128-bit fingerprint. Encoding the same string over and over will always yielf the same 128-bit hash output. 

An MD5 hash is <i>not</i> encryption, the hash is considered a <i>fingerprint</i>. However it is a one-way transaction, meaning it's <i>(almost)</i> impossible to reverse engineer an MD5 hash to obtain the original string.

For a detailed breakdown of the algorithim, [see below](#MD5-how-does-it-work)

## Running the Project
1. In your command line terminal: `git clone https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms`
2. Navigate to the <b> \program\ </b> directory: `cd program`
3. Compile the program: `gcc -o md5 md5.c`
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

## MD5 how does it work
The MD5 Message-Digest Algorithm was designed as a strengthened version of MD4, prior to MD4 collisions being found [[1]](http://cacr.uwaterloo.ca/hac/about/chap9.pdf). It consists of five major steps [[3]](https://tools.ietf.org/html/rfc1321),

1. <b>Append Padding Bits</b>
2. <b>Append Length</b>
3. <b>Initialize MD Buffer</b>
4. <b>Process Message in 16-Word Blocks</b>
5. <b>Output</b>

### Appending Padding Bits
The first step consists of padding (or <i>extending</i>) the message so that the length of the message in bits is equal to 448 modulo 512. The point is to extend the message so that it's just 64 bits shy of being a multiple of 512 bits long.

There are three possible i'll finish writing this tomorrow i'm wrecked

## References
[1] http://cacr.uwaterloo.ca/hac/about/chap9.pdf <br>
[2] https://www.nist.gov/publications/secure-hash-standard <br>
[3] https://tools.ietf.org/html/rfc1321 <br>
[3] https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Expressions-and-Operators <br>
[4] https://graphics.stanford.edu/~seander/bithacks.html <br>
[5] https://www.youtube.com/watch?v=53O9J2J5i14 <br>
