# CMSC 421 Project 3 Part 2 - Hamin Han </br>

### <ins> Part 2: Webb Telescope Video and Bounded Buffer using Semaphores </ins> <br>

In this part of the projext, we implement a set of system calls to provide a circular buffer available to concurrent consumer and producer threads in kernel space. </br>

This part presents a concrete example of the bounded buffer problem, the following is implemented:

1. The circular buffer from Part 1.
2. A producer that inserts data into the buffer. The producer will insert entries consisting of 1024 
characters starting with zeros, then 1s, then 2s, and so on.
3. A consumer will then take each entry out of the buffer and display the characters to the screen.

### The Producer
* Comprises a single thread or process that writes sequential blocks of characters. Each 
block contains 1024 char bytes. The first block will be the "0" character and incrementing 
with each iteration. The second block will contain 1024 “1” chars, and so on. After the 
character “9”, start over with “0”.
* The producer should randomly wait between 0-10 milliseconds prior to each enqueue. 
* The producer must execute concurrently with the consumer.

### The Consumer
* Comprises a single thread or process that retrieves sequential blocks of characters from the 
buffer and then displays them on the screen.
* The consumer should randomly wait between 0-10 milliseconds prior to each dequeue.
* The consumer must execute concurrently with the producer

## Included files:
* ### buffer_sem.h (provided)
* ### buffer_sem.c (kernel_space file)
* ### test_sem.c (to test kernel-space)
* ### buffer_user_sem.c (user-space)
* ### test_user_sem.c (to test user-space)
* ### README.MD

### The test files tests simple insertions, inserting 20 nodes and 10 nodes. And also tests all other edge cases for before initializing the buffer, after initializing the buffer, and after deleting the buffer. </br> </br>

## To compile:
### gcc buffer_user.c test_user.c -o test
### gcc test.c -o test (and use sudo dmesg to check output)