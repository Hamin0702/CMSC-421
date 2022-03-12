#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

void shell_loop();
char* readIn();
char** parse(char* command);
int execute(char** tokens);
int shell_exit(char **command);
void shell_proc(char **path);

// shell_loop()
// Loop of the shell that will read the commands, parse it, and execute the parsed command
void shell_loop(){

    char *command;
    char **tokens;
    int status;

    // Do-While loop to read, parse, and execute the command
    do{   
        prompt_start:
        printf("> ");
        command = readIn();
        tokens = parse(command);

        // Call the built-in exit function if the command is "exit"
        if(strcmp(tokens[0],"exit") == 0){
            int exitCode = shell_exit(tokens);
            
                free(command);
                free(tokens);

            // If the exit was valid, free up the pointers and then exit with the proper exit code
            if(exitCode != -1){
                exit(exitCode);

            // Else if the exit fails, prompt the user again
            }else{
                goto prompt_start;
            }
        }

        // Call the built-in proc function if the command is "proc"
        if(strcmp(tokens[0],"proc") == 0){
            shell_proc(tokens);
            free(command);
            free(tokens);
            goto prompt_start;
        }

        status = execute(tokens);

        free(command);
        free(tokens);
    }while(status);
}

// read()
// Read in a command input of arbitrary length
char* readIn(){

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

    int bufSize = 64;
    int position = 0;
    char *token;

    // Initial allocation of the char** array
    char **tokens = malloc(bufSize * sizeof(char*));

    // If there's no spaces and only the command, put the command in the array
    if(count_spaces(command) == 0){
        tokens[0] = command;
        tokens[1] = NULL;
        return tokens;
    }

    // Loop to parse the command char* and place it in the tokens array properly
    token = strtok(command, " ");
    while(token != NULL){
        tokens[position] = unescape(token,stderr);
        position++;

        if(position >= bufSize){
            bufSize += 64;
            tokens = realloc(tokens, bufSize * sizeof(char*));
        }

        token = strtok(NULL, " ");
    }

    tokens[position] = NULL;
    return tokens;
}

// execute(char** tokens)
// Execute the command
int execute(char** tokens){

    // If there's no command, return 1 to continue loop
    if(tokens[0] == NULL){
        return 1;
    }

    // Forking a child
    pid_t pid = fork();

    // Fork failed
    if(pid == -1){
        fprintf(stderr, "ERROR: Failed forking child \n");
        exit(1);
    
    // Child process
    }else if(pid == 0){
        if(execvp(tokens[0],tokens) == -1){
            fprintf(stderr, "ERROR: Failed execvp \n");
            exit(1);
        }
        return 1;
    
    // Parent process
    }else{
        wait(NULL);
    }

    return 1;
}

// shell_exit(char **command)
// Built-in exit command that returns the exit code from the argument or -1 is exit fails
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
        if(*temp != '\0'){
            fprintf(stderr, "ERROR: Exit code not a number \n");
            return -1;
        }else if(exitStatus < 0 || exitStatus > 255){
            fprintf(stderr, "ERROR: Invalid exit code \n");
            return -1;

        // Else return the exit status number
        }else{
            return exitStatus;
        }
    }
}

// shell_proc(char **path)
// Built-in proc command that opens the file within the /proc filesystem, and prints all the information
void shell_proc(char **path){

    char* file;
    FILE *fp;
    int c;

    // If there's nothing after "proc", return an error
    if(path[1] == NULL){
        fprintf(stderr, "ERROR: Invalid command (No command) \n");
        return;
    
    // Navigate to the appropriate path and display it
    }else{

        // Concatenate the arguments to get the file path
        file = malloc(sizeof(char) * 100);
        file[0] = '\0';
        strcat(file, "/proc/");
        strncat(file, path[1], 100);

        // Open the file
        fp = fopen(file, "r");

        // If there's an error opening a file
        if(fp == NULL){
            fprintf(stderr, "ERROR: Failed to open the file \n");
            free(file);
            return;
        }

        // Loop to display the file
        while(1) {
            c = fgetc(fp);
            
            // The entries are separated by null bytes ('\0'), and there may be a null byte at the end.
            if(c == '\0'){
                c = '\n';
            }

            if(feof(fp)){ 
                break;
            }
            printf("%c", c);
        }

        // Clean up after the loop
        free(file);
        fclose(fp);
    }
}

// The main function that will be called to run the shell
int main(int argc, __attribute__ ((unused)) char *argv[]){

    // Exit with an error return code (1) if executed with any arguments
    if(argc > 1){
        fprintf(stderr, "ERROR: simple_shell.c does not accept any command line arguments \n");
        exit(1);
    }

    printf("Hamin's simple_shell.c  \n\n");

    shell_loop();
    
    return 0;
}