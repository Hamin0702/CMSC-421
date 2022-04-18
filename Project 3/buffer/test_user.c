// Hamin Han, haminh1@umbc.edu
// CMSC 421 Project 3 Part 1 Spring 2022
// test_user.c
// Driver file of the circular buffer in user space

#include <stdio.h>
#include "buffer.h"

void testSimpleInserting(void);
void testHalfInserting(void);
void testEdgeCases(void);

int main(){
    
    printf("=========================================  \n");
    printf(" test_user.c for testing \n");
    printf("=========================================  \n\n");

    printf("Test case: Inserting 20 integers... \n\n");
    testSimpleInserting();

    printf("\nTest case: Inserting 10 integers... \n\n");
    testHalfInserting();

    printf("\nTest case: Testing all edge cases... \n");
    testEdgeCases();

    return 0;
}

// Tester function that does simple insertion
void testSimpleInserting(void){
    init_buffer_421();

    for(int i = 0; i < 20; i++){
        insert_buffer_421(i);
    }

    print_buffer_421();
    delete_buffer_421();
}

// Tester function that only fills up half of the buffer
void testHalfInserting(void){
    init_buffer_421();

    for(int i = 0; i < 10; i++){
        insert_buffer_421(i);
    }

    print_buffer_421();
    delete_buffer_421();
}

// Tester function that checks all edge cases
void testEdgeCases(void){
    
    // **BEFORE ININTIALIZING BUFFER** 
    // Check that it doesn't delete a non-existent buffer
    if(delete_buffer_421() != -1){
        printf("Test failed! (Deleting an uninitialized buffer) \n");
        return;
    
    // Check that it doesn't insert into an uninitialized buffer
    }else if(insert_buffer_421(0) != -1){
        printf("Test failed! (Inserting into an uninitialized buffer) \n");
        return;

    // Check that it doesn't print an uninitialized buffer
    }else if(print_buffer_421() != -1){
        printf("Test failed! (Printing an uninitialized buffer) \n");
        return;
    }
    
    // **AFTER ININTIALIZING BUFFER**
    init_buffer_421();

    // Check that it doesn't reinitialize an already existing buffer
    if(init_buffer_421() != -1){
        printf("Test failed! (Reinitializing an existing buffer) \n");
        return;
    
    // Check that print works with an empty buffer
    }else if(print_buffer_421() != 0){
        printf("Test failed! (Error with printing an empty buffer) \n");
        return;
    }

    // Making a full buffer
    for(int i = 0; i < 20; i++){
        insert_buffer_421(i);
    }

    // Check that it doesn't insert data into a full buffer
    if(insert_buffer_421(0) != -1){
        printf("Test failed! (Inserting data to a full buffer) \n");
        return;
    }

    // **AFTER DELETING BUFFER** 
    delete_buffer_421();

    // Check that it doesn't delete a deleted buffer
    if(delete_buffer_421() != -1){
        printf("Test failed! (Deleting a deleted buffer) \n");
        return;
    
    // Check that it doesn't insert into an deleted buffer
    }else if(insert_buffer_421(0) != -1){
        printf("Test failed! (Inserting data to a deleted buffer) \n");
        return;

    // Check that it doesn't print a deleted buffer
    }else if(print_buffer_421() != -1){
        printf("Test failed! (Printing a deleted buffer) \n");
        return;
    }

    printf("Test Passed! \n");
}