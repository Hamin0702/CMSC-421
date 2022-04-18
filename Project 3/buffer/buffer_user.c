// Hamin Han, haminh1@umbc.edu
// CMSC 421 Project 3 Part 1 Spring 2022
// buffer_user.c
// Implementation of the circular buffer in user space

#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

static ring_buffer_421_t buffer;
node_421_t *head = NULL;

// init_buffer_421
// Initialize a new circular buffer in memory with 20 nodes
long init_buffer_421(void){

    // Check if the buffer is already initialized
    if(head != NULL){
        return -1;
    }

    // Allocate memory for the head node
    head = (node_421_t *) malloc(sizeof(node_421_t));
    
    // Check for memory allocation error
    if(head == NULL){
        return -1;
    }
    head->data = 0;
    head->next = NULL;

    // Initialize the buffer variables
    buffer.length = 0;
    buffer.read = head;
    buffer.write = head;

    // Set up a pointer to create the circular buffer
    node_421_t *prev = head;

    // Loop and add the other 19 nodes
    for(int i = 1; i < SIZE_OF_BUFFER; i++){

        // Allocating memory for each node
        node_421_t *temp = (node_421_t *) malloc(sizeof(node_421_t));
        
        // Check for memory allocation error
        if(temp == NULL){
            return -1;
        }

        // Setting up the node and connecting it together
        temp->data = 0;
        prev->next = temp;
        prev = temp;
    }
    // Connecting the last node back to the head node
    prev->next = head;

    return 0;
}

// insert_buffer_421
// Insert the integer into the next available node (write)
long insert_buffer_421(int i){

    // Check if the buffer in uninitialized
    if(head == NULL){
        return -1;
    }

    // Check if the buffer is already full
    if(buffer.length == 20){
        return -1;
    }

    // Add the integer into the next available node and update the buffer values
    buffer.write->data = i;
    buffer.write = buffer.write->next;
    buffer.length++;

    return 0;
}

// print_buffer_421
// Print everynode in the buffer
long print_buffer_421(void){

    // Check if the buffer is uninitialized
    if(head == NULL){
        return -1;
    }
    
    // Loop and print every node in the buffer
    for(int i = 0; i < buffer.length; i++){
        printf("Buffer [%d] = %d \n", i, buffer.read->data);
        buffer.read = buffer.read->next;
    }

    // Reset the read pointer to the head
    buffer.read = head;

    return 0;
}

// delete_buffer_421
// Delete the buffer and free up all allocated memory
long delete_buffer_421(void){

    // Check if the buffer is uninitialized
    if(head == NULL){
        return -1;
    }

    node_421_t *current = head;
    node_421_t *next = NULL;
    // Loop and delete every node in the buffer
    for(int i = 0; i < SIZE_OF_BUFFER; i++){
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;

    return 0;
}