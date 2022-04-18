// Hamin Han, haminh1@umbc.edu
// CMSC 421 Project 3 Part 2 Spring 2022
// test_user_sem.c
// Driver file of the circular buffer with semaphores in user space

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "buffer_sem.h"

int bufSize = 0;
sem_t mutex;

void *producer();
void *consumer();                                                                                                              

// Producer function
void *producer(){

    int increment = 0;
    char data[DATA_LENGTH];
    char c[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};  
    srand(time(NULL));  
    
    for(int i = 0; i < 1000; i++){

        // Filling up the char array of 1024 bytes that will be enqueued
        for(int j = 0; j < 1024; j++){
            data[j] = c[increment];
        } 

        // Randomly waiting between 0-10 milliseconds
        int randomNum = rand() % 11;
        usleep(randomNum * 1000);

        // Enqueing
        enqueue_buffer_421(data);
        //print_semaphores();
       
        // Printing enqueue message
        sem_wait(&mutex);
        bufSize++;
        printf(":: Enqueueing element into buffer ::\n", data);
        printf("%.1024s\n", data);
        printf("%d items in buffer \n\n", bufSize);
        sem_post(&mutex);
        

        // Incrementing
        increment++;
        if(increment > 9){
            increment = 0;
        }
    }

    return NULL;
}

// Consumer function
void *consumer(){

    char data[DATA_LENGTH];
    srand(rand());
    
    for(int i = 0; i < 1000; i++){

        // Randomly waiting between 0-10 milliseconds
        int randomNum = rand() % 11;
        usleep(randomNum * 1000);

        // Dequeing
        dequeue_buffer_421(data);
        //print_semaphores();

        // Printing dequeuue message
        sem_wait(&mutex);
        bufSize--;
        printf(":: Dequeueing element into buffer ::\n", data);
        printf("%.1024s\n", data);
        printf("%d items in buffer \n\n", bufSize);
        sem_post(&mutex);

    }

    return NULL;
}

// Main function that creates a producer and consumer thread and run them concurrently
int main(){
    
    // Initializations
    sem_init(&mutex, 0, 1);
    pthread_t con, pro;

    init_buffer_421();
    
    // Creating threads
    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);

    // Joining threads
    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    delete_buffer_421();
    sem_destroy(&mutex);

    return 0;
}