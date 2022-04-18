// Hamin Han, haminh1@umbc.edu
// CMSC 421 Project 3 Part 1 Spring 2022
// test_user.c
// Driver file of the circular buffer in kernel space

#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include "buffer.h"

#define __NR_init_buffer_421 442
#define __NR_insert_buffer_421 443
#define __NR_print_buffer_421 444
#define __NR_delete_buffer_421 445

void testSimpleInserting(void);
void testHalfInserting(void);
void testEdgeCases(void);

// Calls init_buffer_421 syscall
long init_syscall(void){
    syscall(__NR_init_buffer_421);
}

// Calls insert_buffer_421 syscall
long insert_syscall(int i){
    syscall(__NR_insert_buffer_421, i);
}

// Calls print_buffer_421 syscall
long print_syscall(void){
    syscall(__NR_print_buffer_421);
}

// Calls delete_buffer_421 syscall
long delete_syscall(void){
    syscall(__NR_delete_buffer_421);
}

int main(){
    
    printf("=========================================  \n");
    printf(" test.c for testing \n");
    printf("=========================================  \n\n");

    printf("Test case: Inserting 20 integers... \n");
    printf("Check output with sudo dmesg \n\n");
    testSimpleInserting();

    printf("Test case: Inserting 10 integers... \n");
    printf("Check output with sudo dmesg \n\n");
    testHalfInserting();

    printf("Test case: Testing all edge cases... \n");
    testEdgeCases();

    return 0;
}

// Tester function that does simple insertion
void testSimpleInserting(void){
    init_syscall();

    for(int i = 0; i < 20; i++){
        insert_syscall(i);
    }

    print_syscall();
    delete_syscall();
}

// Tester function that only fills up half of the buffer
void testHalfInserting(void){
    init_syscall();

    for(int i = 0; i < 10; i++){
        insert_syscall(i);
    }

    print_syscall();
    delete_syscall();
}

// Tester function that checks all edge cases
void testEdgeCases(void){
    
    // **BEFORE ININTIALIZING BUFFER** 
    // Check that it doesn't delete a non-existent buffer
    if(delete_syscall() != -1){
        printf("Test failed! (Deleting an uninitialized buffer) \n");
        return;
    
    // Check that it doesn't insert into an uninitialized buffer
    }else if(insert_syscall(0) != -1){
        printf("Test failed! (Inserting into an uninitialized buffer) \n");
        return;

    // Check that it doesn't print an uninitialized buffer
    }else if(print_syscall() != -1){
        printf("Test failed! (Printing an uninitialized buffer) \n");
        return;
    }
    
    // **AFTER ININTIALIZING BUFFER**
    init_syscall();

    // Check that it doesn't reinitialize an already existing buffer
    if(init_syscall() != -1){
        printf("Test failed! (Reinitializing an existing buffer) \n");
        return;
    
    // Check that print works with an empty buffer
    }else if(print_syscall() != 0){
        printf("Test failed! (Error with printing an empty buffer) \n");
        return;
    }

    // Making a full buffer
    for(int i = 0; i < 20; i++){
        insert_syscall(i);
    }

    // Check that it doesn't insert data into a full buffer
    if(insert_syscall(0) != -1){
        printf("Test failed! (Inserting data to a full buffer) \n");
        return;
    }

    // **AFTER DELETING BUFFER** 
    delete_syscall();

    // Check that it doesn't delete a deleted buffer
    if(delete_syscall() != -1){
        printf("Test failed! (Deleting a deleted buffer) \n");
        return;
    
    // Check that it doesn't insert into an deleted buffer
    }else if(insert_syscall(0) != -1){
        printf("Test failed! (Inserting data to a deleted buffer) \n");
        return;

    // Check that it doesn't print a deleted buffer
    }else if(print_syscall() != -1){
        printf("Test failed! (Printing a deleted buffer) \n");
        return;
    }

    printf("Test Passed! \n");
}