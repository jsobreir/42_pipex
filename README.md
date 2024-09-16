# Pipex
My own very first library.

The goal of this project is to write a program that replicates the ` | ` (pipe) object in Shell.

## Documentation

## Installing and Using
To download, clone the repository into your device and navigate inside using `cd pipex`, then typing  `make` to compile all the functions and generate the executable pipex, which you can run as follows:

```
./pipex infile.txt "command_1" "command 2" outfile.txt
```
where, the infile.txt and outfile.txt are the files that will serve as input to the first command and output for the second command, respectively, and the two commands are the commands that will be piped.

## Project Implementation
This project implements the pipe (3) and fork (3) functions in C to replicate the shell command `< infile.txt command_1 | command_2 > outfile.txt`  where the content of the infile serves as input for command_1, whose output will then be passed to command_2's input. The output of the program will be redirected to the outfile.txt file.

## Disclaimer
At 42 School our projects have to adhere to the 42 Norm of coding standards and good practices. These include:
- Maximum 25 lines per function and 5 functions per file;
- No variable declarations and assignments in the same line;
- Forbiden structures: `for`, `switch`, `goto` and `case`;
- No more than 5 variables per function.

All of my projects strictly adhere to this Norm, that promotes code simplicity and readability.
