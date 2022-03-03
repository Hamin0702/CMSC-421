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
	
	if (head == NULL) {
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
        		current -> next = new; // head points to second node 
       		 	new -> next = NULL;
			
			// if the second node burst is smaller than the current burst 
			} else {
		 
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
	  					new->next = current->next;
	  					current->next = new ;
	  					current = head; 
	  					break;
	  			
					} else if (new->task->priority > current->task->priority) {
						head = new;
      					new->next = current;
	  					current = head;
	  					break;
	  			
					// if the new priority == the current priority  
					} else if(new->task->priority == current->task->priority) {
						new->next = current->next;
       			 		current->next = new;	
        				break;		
		  			}  
	  		
				} else if (new -> task -> priority == current -> next -> task -> priority) {
	   				current = current -> next ;
	   
	   				if (current->next == NULL) {
						new->next = NULL;
				
					} else if (new-> task-> priority == current->next->task->priority) {
		   				current = current -> next ;   
						new->next = current->next;   
					
					} else {
		   				new->next = current->next;	   
		   			}   
	   
	    			current->next = new;
	  	   			current = head;		    
					break;  
	  		
				// if the new priority is less than the current priority  
				} else if ((new -> task -> priority) <(current -> next -> task -> priority)) {
	  				current = current -> next;
	  
	  				if ( current->next == NULL) {
						//printf("testing"); 
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
	
	int num = 0;
	float ResponseTime = 0;
	float turnaroundtime = 0;
	float WaitTime = 0;
	int burst = 0;
	struct node * ref = head;
  	
	printf("****************************************************************************** \n");
    printf("Priority scheduling \n");
    printf("This algorithm schedules tasks based on priority \n");
    printf("In this case, priorities range from 1 to 10, where a higher numeric value indicates a higher relative priority \n");
    printf("****************************************************************************** \n\n");

	while (ref != NULL) {
    	num = num + 1;
    	run(ref -> task, ref -> task -> burst);
    	burst = burst + ref->task->burst;
		turnaroundtime = turnaroundtime + burst ; //5 (5+10+5)20  50      (5 + 5+10 + 5+10+15)
		
		if(num == 1){
            printf("  >> T8 has the highest relative priority with 10, so the CPU starts with T8 \n");
        }else if(num == 2){
            printf("  >> T4 and T5 has the next highest relative priority with 5, so the CPU works on T4  \n");
        }else if(num == 3){
            printf("  >> and then finishes up with T5 after \n");
        }else if(num == 4){
            printf("  >> T1 has the next highest relative priority with 4, so the CPU works on T1 \n");
        }else if(num == 5){
            printf("  >> T2, T3, and T7  has the next highest relative priority with 3, so the CPU works on T2 \n");
        }else if(num == 6){
            printf("  >> and the finishes up with T3 after \n");
        }else if(num == 7){
            printf("  >> and then finishes up T7 \n");
        }else if(num == 8){
            printf("  >> Finally, the CPU works on T8, which has the lowest priority with 1 \n\n");
        }

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