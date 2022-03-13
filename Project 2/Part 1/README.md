# CMSC 421 Project 2 Part 1 & 2 - Hamin Han
## Simple Shell, /proc directory </br> 

### <ins> Part 1: Simple Shell </ins> </br>

In part 1 of the assignment, we were required to write a C program that works as a simple *nix shell. </br>

This part of the assignment only requires a few basic features of a shell and leaves out much of the functionality that more advanced shells such as Bash include. </br>
* The main function is set up as int main(int argc, char *argv[]), and checks the value of argc upon the start of the program to make sure no argument is passed.
* The main function calls a function that present the user with a prompt where they can enter commands and continues to loop until exit of the shell is called.
* The function the loops asks for user input, parses the input into multiple tokens, and executes the command.
* The program reads in user input and dynamically allocates memory for the needed length.
* The user input is then divided by the spaces and placed in an array of char* (This is where the functions from utils.c are used to help parsing).
* The array of char* is then used to execute commands ("exit" and "proc" call the built-in function).
* For the built-in exit command, it will exit normally for "exit" or "exit [0-255]" but it will prompt for another command if the exit failed.

### <ins> Part 2: /proc directory </ins> </br>

In part 1 of the assignment, we were required to add functionality to explore information from the /proc filesystem on Linux and to organize it in a way to present it to the user. </br>

"You are required to add functionality to your shell program that reads information from the /proc filesystem and displays it on the normal stdout of the shell. This command shall accept a single command line argument that will be the name of the file from the /proc filesystem that the user wishes to read information from. Only a small subset of all of the files in /proc shall be available for use with this command, as detailed below." </br>

These files in the /proc filesystem are supported:

* cpuinfo
* loadavg
* filesystems
* pid/status
* pid/environ
* pid/ched

This part of the project was implemented by utilizing the user input and strcat/strncat for concatenation to get the appropriate filepath. The file was then opened and read with fgetc to display the output for the user.

### Included files:
* This README.md
* utils.h (Given)
* utils.c (Given)
* Makefile (Given)
* simple_shell.c

### *Important Note:

There seems to be a warning from the given utils.c file.

> utils.c: In function ‘unescape’: </br>
  utils.c:62:31: warning: unused variable ‘i’ [-Wunused-variable] </br>
   62 |     size_t len = strlen(str), i; </br>
