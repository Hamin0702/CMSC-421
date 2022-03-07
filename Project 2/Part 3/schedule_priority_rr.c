#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head = NULL;
struct node *last = NULL;
struct node *new = NULL;
struct node * current = NULL;

void add(char *name, int priority, int burst) {

	printf("** Calling add function for [%s] [%d] [%d] \n", name, priority, burst);

	if (head == NULL) {
		printf("  >> Adding the first task to the head node \n\n");
    	head = malloc(sizeof(struct node));

    	// set the name of the task 
		head -> task = malloc(sizeof(struct task));
		head -> task -> name = name;
		head -> task -> burst = burst;
		head -> task -> priority = priority;
		// set the next node to be null
		head -> next = NULL;
		current = head;
  
  	} else {

		new = malloc(sizeof(struct node));
		new -> task = malloc(sizeof(struct task));
		new -> task -> burst = burst;
		new -> task -> name = name;
		new -> task -> priority = priority;
		
		// if current->next is NULL
		if (!(current -> next)) {
			if (((new -> task -> priority) < (current -> task -> priority)) || ((new -> task -> priority) ==(current -> task -> priority))) {
				printf("  ** Head Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
				printf("  >> If there's only the head node, and the new task has equal or smaller priority value than the head, it's added to the end of the linked list \n\n");
				current -> next = new; // head points to second node 
				new -> next = NULL;
			
			// if the second node burst is smaller than the current burst  
			} else {
				printf("  ** Head Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
				printf("  >> If there's only the head node, and the new task has a greater priority value than the head, it's added to the linked list as the new head \n\n");
				// set new to point to head which is in the second position
				new->next = current; 	
				// head now holds the address of new which is in the first position
				head = new;
				// reset current to new
				current = new;	  
				// we still have the second node connected to null  
			}	   
		
		// T3 and on execute from here I think 
		} else {
    	  
	  		while(1) {
    			
				if ((new -> task -> priority > current -> next -> task -> priority) ) {
	  				if (new->task->priority < current->task->priority) {
						printf("  ** \"Current Node\": [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  ** Task after \"Current Node\": [%s] [%d] [%d] \n", current -> next -> task -> name, current -> next -> task -> priority, current -> next -> task -> burst);
						printf("  >> If the new task has a priority value less than the \"current node\" but greater than the task after, the new task is added to the linked list after the \"current node\" \n\n");
						new->next = current->next;
						current->next = new ;
						current = head; 
						break;
					
					} else if (new->task->priority > current->task->priority) {
						printf("  ** Head Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  >> If the new task has a priority value greater than the head node, the new task is added to the linked list as the new head \n\n");
						head = new;
						new->next = current;
						current = head;
						break;
					
					// if the new priority == the current priority
					} else if(new->task->priority == current->task->priority) {
						printf("  ** \"Current Node\": [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  ** Task after \"Current Node\": [%s] [%d] [%d] \n", current -> next -> task -> name, current -> next -> task -> priority, current -> next -> task -> burst);
						printf("  >> If the new task has a priority value equal to the \"current node\" but greater than the task after, the new task is added to the linked list after the \"current node\" \n\n");
						new->next = current->next;
						current->next = new;	
						break;		
		  			}  
	  			
				} else if (new -> task -> priority == current -> next -> task -> priority) {
	   				current = current -> next ;
	   
	  	 			if (current->next == NULL) {
						printf("  ** Last task: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  >> If the new task has a priority value equal to the last task of the linked list, the new task is added to the end of the linked list \n\n");
						new->next = NULL;
					
					} else if (new-> task-> priority == current->next->task->priority) {
						printf("  ** Second task after \"Current Node\": [%s] [%d] [%d] \n", current -> next -> task -> name, current -> next -> task -> priority, current -> next -> task -> burst);
						printf("  >> If the new task has a priority value equal to the two tasks after the \"current node\", the new task is added to the linked list after them \n\n");
						current = current -> next ;   
						new->next = current->next;   
		   			
					} else {
						printf("  ** Task after \"Current Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  >> If the new task has a priority value equal to the task after the \"current node\", the new task is added to the linked list after it \n\n");
		   				new->next = current->next;	   
					}   
	   
					current->next = new;
					current = head;		    
					break;  
	  			
				// if the new priority is less than the current priority  
				} else if ((new -> task -> priority) <(current -> next -> task -> priority)) {
	  				current = current -> next;
	  
	 				if ( current->next == NULL) {
						printf("  ** Task after \"Current Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  >> If the new task has a priority value less than the task after the \"current node\", the new task is added to the linked list after it \n\n");
						current->next = new;  
						new->next = NULL;
						current = head;
						break;
					}	  
	  			}	  
	   		}
		}
  	}
 
}

// invoke the scheduler
void schedule() {

	printf("** Calling schedule function \n\n");

	current = head;
	struct node * ref = head;	
	struct node *beginning = malloc(sizeof(struct node));
	int newburst = 0;
	int num = 1;

	printf("****************************************************************************** \n");
    printf("Priority with round-robin \n");
    printf("This algorithm schedules tasks in order of priority and uses round-robin scheduling for tasks with equal priority \n");
	printf("In this case, if there is only one task with the highest priority, it will complete that task, but if there are multiple tasks with the same priority, it will use round-robin scheduling for those tasks  \n");
    printf("Priorities range from 1 to 10, where a higher numeric value indicates a higher relative priority \n");
	printf("For round-roobin, the length of a time quantum is 10 units so each task will get 10 time units at a time (or the remainder if less than 10) until the tasks are finished \n");
    printf("****************************************************************************** \n\n");

	while (ref !=NULL) {
	
		// ref->next = 3 (this is the second 3rd) 
		if (ref->next ==NULL) {
			printf("  >> If the \"reference node\" is the last task of the list, run the task for the entire burst time \n");
			run(ref->task, ref->task->burst);
			printf("\n");
			num = num + 1;
			break;	
		
		} else {
			//	ref->task->priority = first 3
			// ref->next->task->priority = second 3
			if ((ref->task->priority != ref->next->task->priority)) {
				printf("  >> If the \"reference node\" is the only task with its priority value, run the task for the entire burst time \n");
				run(ref->task,ref->task->burst);
				num = num + 1;
				ref = ref->next; // ref = first 3
				printf("  >> Move along the linked list after finishing the task \n\n");
			
			} else {

				if (ref->next !=NULL) {
	
					// first 3 = second 3 priority
					if ((ref->task->priority == ref->next->task->priority)) {
	
						// set current to point to ref ( location of first 3)	
						printf("  ** Setting up round robin for tasks with the same priority value \n");
						current = ref ;  

						// current->next is 3
						while (current->next != NULL) {
							current = current->next; 	 // current is third 3 

							// the 3rd 3 priority != the 3rd 3 priority)
							if (current->task->priority != current->next->task->priority) {	
								beginning = current->next; // set the beginning 
								current->next = NULL;
								current = ref; // move current back to ref so we can do round robin
								break;
							
							//current = current->next;	// current = 2nd 3 priority
							} else {

							}
						}

						while (ref !=NULL   ) {
							
							if (ref->task->burst >= 10) {
								newburst = ref->task->burst-10; // set newburst to 0
								ref->task->burst = 10;
								printf("  >> If the \"reference node\" has a burst time of 10 or greater, call the run function 10 burst time  \n");
								run(ref->task,10);	
								num = num + 1;
							
							} else if (ref-> task-> burst  < 10) {
								newburst = 0;
								printf("  >> If the \"reference node\" has a burst time less than 10, call the run function for the remainding burst time \n");
								run(ref->task,ref->task->burst);	
								num = num + 1;
							}	
 
							while(1) {	
								if (current->next !=NULL) { 
									current = current->next;	// current points to newT3
										if (current->next == NULL) { // 
											if (newburst != 0) {
												printf("  >> If the \"reference node\" had a burst time greater than 10, update the node in the linked list with the new burst time \n\n");
												struct node * newnode = malloc(sizeof(struct node));
												newnode->task = malloc(sizeof(struct task));	
												newnode->task->name = ref->task->name ;
												newnode->task->burst = newburst;
												newnode->task->priority = ref->task->priority;
												ref = ref->next ;
												current->next = newnode;	
												newnode->next = NULL;
												current = ref;
												break;	
											
											} else if (newburst == 0) {
												printf("  >> If the \"reference node\" had a burst time of 10 or less, the task is removed from the linked list and the list is updated \n\n");
												ref = ref->next;	 // ref points to new T3
												current = ref; // current points to new T3 
												break;
											}	
										}
								
								} else { // if this is the last element
									printf("  >> Update the linked list after finishing the round robin \n\n");
									ref = ref->next; // ref == NULL after this
									current = beginning;
									break;	
								}	
							}	
						}

						ref = beginning;
					}	
				}
			}
		}
	} 
}


