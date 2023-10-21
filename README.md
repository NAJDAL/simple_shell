# Simple Shell Project

## Overview
This is a simple Unix shell implementation created as part of the C - Simple Shell project for Holberton School. This project aims to understand and implement the fundamental concepts behind Unix shell operations.

## Learning Objectives
At the end of this project, we aim to have a clear understanding of the following concepts:
- The history and design of the original Unix operating system.
- The development of the first version of the UNIX shell.
- The invention of the B programming language, which directly influenced the creation of the C programming language.
- An introduction to Ken Thompson and his contributions to Unix.
- The inner workings of a shell and how it processes commands.
- Understanding what PID (Process ID) and PPID (Parent Process ID) mean in Unix.
- How to manipulate the environment variables of the current process.
- Distinguishing between a function and a system call in Unix.
- How to create new processes in Unix.
- Understanding the three prototypes of the `main` function.
- How the shell uses the `PATH` environment variable to locate executable programs.
- Executing other programs using the `execve` system call.
- Suspending the execution of a process until one of its children terminates.
- Understanding EOF (End-of-File) and its significance.

## Requirements
### General
- Editors allowed: vi, vim, emacs.
- All source code files will be compiled on Ubuntu 20.04 LTS using the following options: `-Wall -Werror -Wextra -pedantic -std=gnu89`.
- Each source code file should end with a new line.
- A `README.md` file at the root of the project folder is mandatory.
- The code should adhere to the Betty style and will be validated using `betty-style.pl` and `betty-doc.pl`.
- The shell should be free of memory leaks.
- Each source file should have no more than 5 functions.
- All header files should be protected against double inclusion (using include guards).
- Use system calls only when necessary.

## GitHub
- There should be one project repository per group, and collaborators should be added.
- Avoid creating repositories with the same name in both partners' accounts to prevent scoring issues.

## Output
- The program's output should match that of the standard `/bin/sh` shell, including error output.
- The name of the program in error messages must be equivalent to `argv[0]`.

## List of Allowed Functions and System Calls
- [List of allowed functions and system calls](#list-of-allowed-functions-and-system-calls).

## Compilation
To compile your shell, use the following command:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

