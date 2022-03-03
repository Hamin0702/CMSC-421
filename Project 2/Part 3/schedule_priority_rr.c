#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

void explainStep(int number);

struct node *head = NULL;
struct node *last = NULL;
struct node *new = NULL;
struct node * current = NULL;

void add(char *name, int priority, int burst) {
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
			run(ref->task, ref->task->burst);
			explainStep(num);
			num = num + 1;
			break;	
		
		} else {
			//	ref->task->priority = first 3
			// ref->next->task->priority = second 3
			if ((ref->task->priority != ref->next->task->priority)) {	
				run(ref->task,ref->task->burst);
				explainStep(num);
				num = num + 1;
				ref = ref->next; // ref = first 3
			
			} else {

				if (ref->next !=NULL) {
	
					// first 3 = second 3 priority
					if ((ref->task->priority == ref->next->task->priority)) {
	
						// set current to point to ref ( location of first 3)	
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
								run(ref->task,10);	
								explainStep(num);
								num = num + 1;
							
							} else if (ref-> task-> burst  < 10) {
								newburst = 0;
								run(ref->task,ref->task->burst);	
								explainStep(num);
								num = num + 1;
							}	
 
							while(1) {	
								if (current->next !=NULL) { 
									current = current->next;	// current points to newT3
										if (current->next == NULL) { // 
											if (newburst != 0) {
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
												ref = ref->next;	 // ref points to new T3
												current = ref; // current points to new T3 
												break;
											}	
										}
								
								} else { // if this is the last element
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

void explainStep(int number){

	if(number == 1){
		printf("  >> The CPU starts with T8 because it has the highest priority of 10 and spends 25 time units to finish the task \n");
	}else if(number == 2){
		printf("  >> T4 and T5 has the next highest priority of 5 and the CPU uses round-robin to complete these tasks \n");
		printf("  >> The CPU works on T4 for 10 time units (Remaining time: 5) \n");
	}else if(number == 3){
		printf("  >> Next, the CPU works on T5 for 10 time units (Remaining time: 10) \n");
	}else if(number == 4){
		printf("  >> Next, the CPU works on T4 for the remaining 5 time units and finishes it \n");
	}else if(number == 5){
		printf("  >> Next, the CPU works on T5 for 10 time units and finishes it \n");
	}else if(number == 6){
		printf("  >> T1 has the next highest priority of 4 and the CPU spends 20 time units to finish the task \n");
	}else if(number == 7){
		printf("  >> T2, T3, and T7 has the next highest priority of 3 and the CPU uses round-robin to complete these tasks \n");
		printf("  >> The CPU works on T2 for 10 time units (Remaining time: 15) \n");
	}else if(number == 8){
		printf("  >> Next, the CPU works on T3 for 10 time units (Remaining time: 15) \n");
	}else if(number == 9){
		printf("  >> Next, the CPU works on T7 for 10 time units (Remaining time: 20) \n");
	}else if(number == 10){
		printf("  >> Next, the CPU works on T2 for 10 time units (Remaining time: 5) \n");
	}else if(number == 11){
		printf("  >> Next, the CPU works on T3 for 10 time units (Remaining time: 5) \n");
	}else if(number == 12){
		printf("  >> Next, the CPU works on T7 for 10 time units (Remaining time: 10) \n");
	}else if(number == 13){
		printf("  >> Next, the CPU works on T2 for the remaining 5 time units and finishes it \n");
	}else if(number == 14){
		printf("  >> Next, the CPU works on T3 for the remaining 5 time units and finishes it \n");
	}else if(number == 15){
		printf("  >> Next, the CPU works on T7 for 10 time units and finishes it \n");
	}else if(number == 16){
		printf("  >> Finally, the CPU works on T6 which has the lowest priority and spends 10 time units to finish the task \n");
	}
}

