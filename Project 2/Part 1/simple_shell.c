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

        // Call the built-in exit function if the command is "exit"
        if(strcmp(tokens[0],"exit") == 0){
            int exitCode = shell_exit(tokens);
            
            // If the exit was valid, free up the pointers and then exit with the proper exit code
            if(exitCode != -1){
                free(command);
                free(tokens);
                exit(exitCode);
            }
        }

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

    // Check for allocation error
    if(!buffer){
        fprintf(stderr, "ERROR: Allocation error in read \n");
        exit(1);
    }

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

            // Check for allocation error
            if(!buffer){
                fprintf(stderr, "ERROR: Allocation error in read \n");
                exit(1);
            }
        }
    }
}

// parse(char* command)
// Parse the command-line arguments
char** parse(char* command){

    int bufSize = 64;
    int position = 0;
    char *token;

    // Initial allocation of the char** array
    char **tokens = malloc(bufSize * sizeof(char*));

    // Check for allocation error
    if(!tokens){
        fprintf(stderr, "ERROR: Allocation error in parse \n");
        exit(1);
    }

    // If there's no spaces and only the command, put the command in the array
    if(count_spaces(command) == 0){
        tokens[0] = command;
        tokens[1] = NULL;
        return tokens;
    }


}

// execute(char** tokens)
// Execute the command
int execute(char** tokens){

}

// shell_exit(char **command)
//Built-in exit command that returns the exit code from the argument or -1 is exit fails
int shell_exit(char **command){

    int exitStatus;
    char* temp;

    // If provided with zero arguments, the shell exits with a normal exit status 0
    if(command[1] == NULL){
        return 0;
    
    // If there's an argument
    }else{

        // Convert the argument to a number
        exitStatus = strtol(command[1], &temp, 10);
        
        // If strtol failed/argument wasn't a proper number, return -1
        if(*temp != NULL){
            return -1;
        }else if(exitStatus < 0 || exitStatus > 255){
            return -1;

        // Else return the exit status number
        }else{
            return exitStatus;
        }
    }
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