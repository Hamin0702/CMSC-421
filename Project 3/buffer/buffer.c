// Hamin Han, haminh1@umbc.edu
// CMSC 421 Project 3 Part 1 Spring 2022
// buffer.c
// Implementation of the circular buffer in kernel space

#include "buffer.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

static ring_buffer_421_t buffer;
node_421_t *head = NULL;

// init_buffer_421
// Initialize a new circular buffer in memory with 20 nodes
SYSCALL_DEFINE0(init_buffer_421){

    // Check if the buffer is already initialized
    if(head != NULL){
        return -1;
    }

    // Allocate memory for the head node;
    head = (node_421_t *) kmalloc(sizeof(node_421_t), GFP_KERNEL);
    
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
        node_421_t *temp = (node_421_t *) kmalloc(sizeof(node_421_t), GFP_KERNEL);
        
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
// Insert he integer into the next available node (write)
SYSCALL_DEFINE1(insert_buffer_421, int, i){

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
SYSCALL_DEFINE0(print_buffer_421){

    // Check if the buffer is uninitialized
    if(head == NULL){
        return -1;
    }
    
    // Loop and print every node in the buffer
    for(int i = 0; i < buffer.length; i++){
        printk("Buffer [%d] = %d \n", i, buffer.read->data);
        buffer.read = buffer.read->next;
    }

    // Reset the read pointer to the head
    buffer.read = head;

    return 0;
}

// delete_buffer_421
// Delete the buffer and free up all allocated memory
SYSCALL_DEFINE0(delete_buffer_421){

    // Check if the buffer is uninitialized
    if(head == NULL){
        return -1;
    }

    node_421_t *temp = head;
    node_421_t *next = NULL;
    // Loop and delete every node in the buffer
    for(int i = 0; i < SIZE_OF_BUFFER; i++){
        next = temp->next;
        kfree(temp);
        temp = next;
    }
    head = NULL;

    return 0;
}