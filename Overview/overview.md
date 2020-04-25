<p>
  <h2 align="center">Theory of Algorithms</h2>
  <i><h4 align="center">An In-Depth Report of the Overall Project</h4></i>
</p>

## Contents of the Report
* [Introduction](#introduction)
* [Running the Program](#running-the-program)
* [Command Line Arguments](#command-line-arguments)
* [Code Overview](#code-overview)
* [Testing the Program](#testing-the-program)
* [MD5 Overview](#md5-overview) 
* [Complexity of MD5](#complexity-of-md5)
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
The repository is intended to be as simplistic as possible, contents were seperated into their relevant directories and irrelevant files and documents were excluded, leaving only files relevant to the compilation, research and testing of the program.

* Program
    * All code relevant to the running of the actual program will be contained within this folder. The `md5.c` file is contained here along with test files which are required for running the test suite within the program. <br><br>Additionally, a single library (getopt.h) is present here. After testing the program on different platforms I made the decision to manually include it within the project. I had no problems running the program on a Linux machine, however on Windows I experienced compatibility problems. After investigating, I found including the library manually here would mean anyone with a compiler could clone the project and execute it without experiencing any compatibility issues [[1]](https://stackoverflow.com/a/10404524/12314065). <i>For an overview on what the code does [see](#code-overview)</i>.
    
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

<i><b>See the [Command Line Arguments](https://gcc.gnu.org/) section for alternative approaches to executing the program</b></i>

<h3 align="center">
  Running on Windows-based Systems
</h3>
  
<p align="center">
  The following prerequisite steps are required to clone and execute the program on <b>Windows-based</b> machines<b><i><br>You may skip the following two steps if they don't apply</i></b>,  
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

<i><b>See the [Command Line Arguments](https://gcc.gnu.org/) section for alternative approaches to executing the program</b></i>

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

## References
[1] https://stackoverflow.com/a/10404524/12314065 <br>
[2] https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html <br>
[3] http://117.3.71.125:8080/dspace/bitstream/DHKTDN/6554/1/The%20C%20Programming%20Language4603.pdf <i>(Page 102 - 105)</i><br>