#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

char* readIn(void);

int main(int argc, char *argv[]){

    // Exit with an error return code (1) if executed with any arguments
    if(argc > 1){
        fprintf(stderr, "ERROR: simple_shell.c does not accept any command line arguments \n");
        exit(1);
    }

    printf("==========================  \n");
    printf(" Driver.c for testing \n");
    printf("==========================  \n");

    //testExit();
    testRead();
    
    return 0;
}

void testExit(void){
    char* a[] = {"exit","256",NULL};
    printf("Exit code is %d \n", shell_exit(a));
}

void testRead(void){
    printf("> ");
    char* command = readIn();
    printf("%s\n", command);  
}

// read()
// Read in a command input of arbitrary length
char* readIn(void){

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