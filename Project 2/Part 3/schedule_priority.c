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

	int num = 0;
	float ResponseTime = 0;
	float turnaroundtime = 0;
	float WaitTime = 0;
	int burst = 0;
	struct node * ref = head;
  	
	printf("****************************************************************************** \n");
    printf("Priority scheduling \n");
    printf("This algorithm schedules tasks based on priority \n");
	printf("The tasks are added to a linked list in order based on priority and the schedule function runs each task in order \n");
    printf("In this case, priorities range from 1 to 10, where a higher numeric value indicates a higher relative priority \n");
    printf("****************************************************************************** \n\n");

	printf(">> Traverse through the linked list and run the tasks in order \n");
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

	printf("The average turnaround time is : %f time units \n" , (float)turnaroundtime/num);    
	printf("The average ResponseTime is : %f time units \n" , (float)ResponseTime/num);
	printf("The average WaitTime is : %f time units\n " , (float)WaitTime/num);
}