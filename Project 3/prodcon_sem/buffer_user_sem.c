// Hamin Han, haminh1@umbc.edu
// CMSC 421 Project 3 Part 2 Spring 2022
// buffer_user_sem.c
// Implementation of the circular buffer with semaphores in user space

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;
bb_node_421_t *head = NULL;

// init_buffer_421
// Initialize a new circular buffer in memory and initialize semaphores
long init_buffer_421(void) {
	
	// Check if tthe buffer is already initialized
	if(head != NULL){
		return -1;
	}

	// Allocate memory for the head node
	head = (bb_node_421_t *) malloc(sizeof(bb_node_421_t));

	// Check for memory allocation error
	if (head == NULL){
		return -1;
	}
	head->next = NULL;

	// Initialize the buffer variables
	buffer.length = 0;
	buffer.read = head;
	buffer.write = head;

	// Set up the pointer to create the circular buffer
	bb_node_421_t *prev = head;

	// Loop and add the other 19 nodes
    for(int i = 1; i < SIZE_OF_BUFFER; i++){

        // Allocating memory for each node
        bb_node_421_t *temp = (bb_node_421_t *) malloc(sizeof(bb_node_421_t));
        
        // Check for memory allocation error
        if(temp == NULL){
            return -1;
        }

        // Setting up the node and connecting it together
		prev->next = temp;
		prev = temp;
    }
    // Connecting the last node back to the head node
    prev->next = head;


	// Initialize your semaphores here.
	sem_init(&mutex, 0, 1); 
	sem_init(&fill_count, 0, 0); 
	sem_init(&empty_count, 0, SIZE_OF_BUFFER);

	return 0;
}

// enqueue_buffer_421
// Enqueue data into the next available node (write)
long enqueue_buffer_421(char * data) {

	// Check if the buffer in uninitialized
    if(head == NULL){
        return -1;
    }

	// Enqueue
	sem_wait(&empty_count);
	sem_wait(&mutex);
	memcpy(buffer.write->data, data, 1024);
    buffer.write = buffer.write->next;
    buffer.length++;
	sem_post(&mutex);
	sem_post(&fill_count);

	return 0;
}


// dequeue_buffer_421
// Dequeue data from the first available node (read)
long dequeue_buffer_421(char * data) {

	// Check if the buffer in uninitialized
    if(head == NULL){
        return -1;
    }

	// Dequeue
	sem_wait(&fill_count);
	sem_wait(&mutex);
	memcpy(data, buffer.read->data, 1024);
	buffer.read = buffer.read->next;
	buffer.length--;
	sem_post(&mutex);
	sem_post(&empty_count);
	
	return 0;
}

// delete_buffer_421
// Delete the buffer and free up all allocated memory
long delete_buffer_421(void) {

	// Check if the buffer is uninitialized
    if(head == NULL){
        return -1;
    }

    bb_node_421_t *current = head;
    bb_node_421_t *next = NULL;
    // Loop and delete every node in the buffer
    for(int i = 0; i < SIZE_OF_BUFFER; i++){
        next = current->next;
        free(current);
        current = next;
    }
    head = NULL;

	//Destroy semaphores
	sem_destroy(&mutex);
	sem_destroy(&fill_count);
	sem_destroy(&empty_count);

	return 0;
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
