# CMSC 421 Project 3 Part 1 - Hamin Han </br>

### <ins> Part 1: Circular Buffer </ins> <br>

In this part of the projext, we implement a set of four system calls in the Linux kernel that enables a user to perform the following tasks: </br>

1. Create a circular buffer in user space and kernel space.
2. Fill the buffer with integers.
3. Print the buffer's contents to the stdout/kernel log.
4. Delete the buffer and free any allocated memory.

Our circular buffer comprises a singly linked list consisting of twenty nodes, each holding an integer 
and a pointer to the next node, that form a circular structure in kernel memory. The buffer accepts a 
maximum of 20 values, after which it should notify the sender that there is no additional space. In 
this part of the project, we do not require a function for removing items from the buffer. </br>

### The following functions are implemented: 

long init_buffer_421(void)
* Initializes a new circular buffer in memory(kernel memory for kernel space), allocating 
memory for each node. (Use malloc in user space, kmalloc in kernel space.)
* There should be 20 nodes total.
* The final node's next pointer should point to the first node to create a circle.
* Each node should store an initial integer value of 0. 
* Return 0 if we successfully initialize, -1 if we fail for any reason, including our buffer already 
being initialized. Do not reinitialize the buffer if it already exists.

long insert_buffer_421(int i)
* Inserts the integer i into the next available node.
* Note: Increment the buffer length when you insert.
* Note: We cannot insert data into an uninitialized buffer.
* Inserting fails if the buffer is already full.
* Returns 0 if the insert is successful, -1 if it fails.

long print_buffer_421
* Writes a string representation of every node in the buffer, along with the data in each node, 
to the kernel log. If in user-space, print to stdout instead.
* Begins at the buffer's read pointer.
* Note: We cannot print an uninitialized buffer.
* Returns 0 if successful, -1 if not.

long delete_buffer_421
* If it exists, delete the buffer.
* Free any memory (free in user-space, kfree in kernel-space) that you allocated in 
init_buffer_421.
* Returns 0 if successful, -1 if not

## Included files:
* ### buffer.h (provided)
* ### buffer.c (kernel_space file)
* ### test.c (to test kernel-space)
* ### buffer_user.c (user-space)
* ### test_user.c (to test user-space)
* ### README.MD

### The test files tests simple insertions, inserting 20 nodes and 10 nodes. And also tests all other edge cases for before initializing the buffer, after initializing the buffer, and after deleting the buffer. </br> </br>

## To compile:
### gcc buffer_user.c test_user.c -o test
### gcc test.c -o test (and use sudo dmesg to check output)