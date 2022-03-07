#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node * head = NULL;
struct node * current = NULL;
struct node * new = NULL;
struct node * final = NULL;
int num = 0;

void add(char * name, int priority, int burst) {

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

      		if (((new -> task -> burst) > (current -> task -> burst)) || ((new -> task -> burst) ==(current -> task -> burst))) {
				printf("  ** Head Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
				printf("  >> If there's only a head node and the new task has greater or equal burst time, add the task as the next node  \n\n");
        		current -> next = new; // head points to second node 
        		new -> next = NULL;
			
			// if the second node burst is smaller than the current burst 
			} else {
				printf("  ** Head Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
				printf("  >> If there's only a head node and the new task is shorter, the new task becomes the head node \n\n");
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
    	  
			//printf("  >> Start of the loop to place the new task in the linked list \n");
			while(1) {
    		
				if ((new -> task -> burst < current -> next -> task -> burst) ) {
					
	  				if (new->task->burst > current->task->burst) {
						printf("  ** \"Current Node\": [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  ** Task after \"Current Node\": [%s] [%d] [%d] \n", current -> next -> task -> name, current -> next -> task -> priority, current -> next -> task -> burst);
						printf("  >> If the new task is longer than the \"current node\" and shorter than the task after, place new task after the current node \n\n");
					  	new->next = current->next;
	  					current->next = new ;
	  					current = head; // do  i need this
	  					break;

					} else if (new->task->burst < current->task->burst) {
						printf("  ** Head Node: [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  >> If the new task is shorter than the head node, the new task is placed as the head node \n\n");
						head = new;
      					new->next = current;
	  					current = head;
	  					break;
					}	  

      			} else if (new -> task -> burst == current -> next -> task -> burst) {
					printf("  ** Task after \"Current Node\": [%s] [%d] [%d] \n", current -> next -> task -> name, current -> next -> task -> priority, current -> next -> task -> burst);
					printf("  >> If the new task has the same burst time as the task after the \"current node\", add the new task after the task with the same burst time \n\n");
	   				current = current -> next ;

	   				if (current->next == NULL) {
	  					new->next = NULL;

					} else if (new-> task-> burst == current->next->task->burst) {
		   				current = current -> next ;   
						new->next = current->next;   

					} else {
		   				new->next = current->next;	   
		   			}   
	   
	    			current->next = new;
	  	   			current = head;		    
					break;  
	  		
					// if the new burst is greater than the current burst 
				} else if ((new -> task -> burst) > (current -> next -> task -> burst)) {
	  				current = current -> next;

	  				if ( current->next == NULL) {
						printf("  ** \"Current Node\": [%s] [%d] [%d] \n", current -> task -> name, current -> task -> priority, current -> task -> burst);
						printf("  >> If the new task has a larger burst time than the last task, add to the end of the linked list \n\n"); 
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
	
	printf("** Calling schedule function \n");

	float turnaroundtime = 0;
 	float ResponseTime = 0;
	float WaitTime = 0;
 	int burst = 0;
  	struct node * ref = head;
  	
	printf("****************************************************************************** \n");
    printf("Shortest-job-first (SJF) \n");
    printf("This algorithm schedules tasks in the order of the length of the tasks' next CPU burst \n");
    printf("In this case, the CPU will start with the task with the shortest CPU burst and move on to the one with the next shortest CPU burst length\n");
    printf("****************************************************************************** \n\n");

	printf(">> Traverse through the linked list and run the tasks in order\n");
	while (ref != NULL) {
		num = num + 1;
    	run(ref -> task, ref -> task -> burst);
   		burst = burst + ref->task->burst;
		turnaroundtime = turnaroundtime + burst ; //5 (5+10+5)20  50      (5 + 5+10 + 5+10+15)
		
		if (ref->next !=NULL) {
			ResponseTime = ResponseTime + burst;
		}
		ref = ref -> next;
	}
	WaitTime = turnaroundtime - burst;

	printf("\n");
	printf("The average turnaround time is : %f time units \n" , (turnaroundtime)/num);    
	printf("The average ResponseTime is : %f time units \n" , (ResponseTime)/num);
	printf("The average WaitTime is : %f time units\n " , (WaitTime)/num);
}