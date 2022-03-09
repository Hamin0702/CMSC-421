#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

// shell_loop()
// Loop of the shell that will read the commands, parse it, and execute the parsed command
void shell_loop(){

    char *command;
    char **tokens;
    int status;

    // Do-While loop to read, parse, and execute the command
    do{
        printf("> ");
        command = read();
        tokens = parse(command);
        status = execute(tokens);

        free(command);
        free(tokens);
    }while(status);
}

// read()
// Read in a command input of arbitrary length
char* read(){

    int bufSize = 256;
    int position = 0;
    int cha;

    // Initial allocation of the character array
    char *buffer = malloc(sizeof(char) * bufSize);

    // Loop to set up the char *buffer from user input
    while(1){

        // Read in the command input char by char
        cha = getchar();

        // If current command is the End of File or newline character
        if(cha == EOF || cha == '\n'){

            // Null terminate string and break loop
            buffer[position] = '\0';
            return buffer;
        
        // Else add the char to buffer in its proper position
        }else{
            buffer[position] = cha;
        }
        position++;

        // If size of string exceeds currently allocated space increase buffer size and reallocate
        if(position >= bufSize){
            bufSize += 256;
            buffer = realloc(buffer, bufSize);
        }
    }
}

// parse(char* command)
// Parse the command-line arguments
char** parse(char* command){

}

// execute(char** tokens)
// Execute the command
int execute(char** tokens){

}

// The main function that will be called to run the shell
int main(int argc, char *argv[]){

    // Exit with an error return code (1) if executed with any arguments
    if(argc > 1){
        fprintf(stderr, "ERROR: simple_shell.c does not accept any command line arguments \n");
        exit(1);
    }

    printf("#######################  \n");
    printf("Start of simple_shell.c  \n");
    printf("#######################  \n\n");

    shell_loop();
    
    return 0;
}