<p>
  <h2 align="center">MD5 Hash Digest Calculator</h2>
  <i><h3 align="center">A Program written in C that calculates the MD5 hash digest of an input</h3></i>
</p>

## Project Details

|Details  |    |
| --- | --- |
| **Project**  | [Project Spec](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithims) 
| **GIF** | [TODO](https://github.com/farisNassif/FourthYear_TheoryOfAlgorithims)
| **Course** | BSc (Hons) in Software Development
| **Module** |  Theory of Algorithims |
| **Author** | [Faris Nassif](https://github.com/farisNassif) |
| **Lecturer** | Dr Ian McLoughlin |

## Project Outline
1. Write a program in C that can calculate the MD5 hash of an input.

2. Provide input in the form of user input or a file.

3. The program should successfully perform the hashing algorithim on the given input and proof of it's success should be evident.

## Running the Project
1. In your command line terminal: `git clone https://github.com/farisNassif/FourthYear_TheoryOfAlgorithms`
2. Navigate to the <b> \program\ </b> directory: `cd program`
3. Compile the program: `gcc -o md5 md5.c`
4. Execute the program: `md5.exe TestFile.txt` || `md5.exe`

The program may be executed in three different ways 
* Enter a file name as a command line argument 
* Enter a file name as a string to be hashed at runtime 
* Enter a String to be hashed at runtime 

#### Execution via command line argument
```bash
  > md5.exe TestFile.txt
```
<p align="center">
  <img src = "https://i.imgur.com/7905Y1g.png">
</p>

#### Execution via console menu (File Input)
```bash
  > md5.exe
```
<p align="center">
  <img src = "https://i.imgur.com/9Q8FH6m.png">
</p>

#### Execution via console menu (String Input)
```bash
  > md5.exe
```
<p align="center">
  <img src = "https://i.imgur.com/7asbIwp.png">
</p>

## References
[1] http://cacr.uwaterloo.ca/hac/about/chap9.pdf <br>
[2] https://www.nist.gov/publications/secure-hash-standard <br>
[3] https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Expressions-and-Operators <br>
[4] https://graphics.stanford.edu/~seander/bithacks.html <br>
[5] https://www.youtube.com/watch?v=53O9J2J5i14 <br>
