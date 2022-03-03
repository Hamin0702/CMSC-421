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
struct node *test = NULL;
int num = 0;

void add(char *name, int priority, int burst) {
	
	num = num + 1;
	if (head == NULL) {
 		head = malloc(sizeof(struct node)) ;
 		last = malloc(sizeof(struct node)) ;

 		// set the name of the task 
		head->task = malloc(sizeof(struct task));
		head->task->name = name;
		head->task->burst = burst;
		head->task->priority = priority;
		// set the next node to be null
		head->next = NULL;

		last = head;
	
	} else {
		new =  malloc(sizeof(struct node));	
		last->next = new ;
		new->task = malloc(sizeof(struct task));
		new->task->name = name;
		new->task->burst = burst;
		new->task->priority = priority;
		new->next = NULL;	
		last = new;
	}

}

// invoke the scheduler
void schedule() {

	struct node * current = head;
	struct node * ref = head;
	struct node * monitor = NULL;
	monitor = malloc(sizeof ( struct node) );
	monitor = head;
	int newburst = 0;
	int totburst = 0;
	float turnaroundtime = 0;
	float ResponseTime = 0;
	float WaitTime = 0;
	int check = 1;
	int number = 0;

	printf("****************************************************************************** \n");
    printf("Round-robin (RR) scheduling \n");
    printf("This algorithm runs each task for a time quantum (or for the remainder of its CPU burst) \n");
    printf("In this case, the length of a time quantum is 10 units so each task will get 10 time units at a time (or the remainder if less than 10) until the tasks are finished \n");
    printf("****************************************************************************** \n\n");

	while (ref !=NULL   ) {
		number = number + 1;

		if (ref->task->burst >= 10) {	
			newburst = ref->task->burst-10; // set newburst to 10
			
			if (current!=head) {
				
				while(monitor!=current) {
					if (strcmp(current->task->name ,monitor->task->name) == 0) {	
						check = 0;
						break;	
					}	
					monitor = monitor->next;
				}
			monitor = head;
			}	

			if (ref->task->burst >10 && ref!=head) {
				if (ref->next !=NULL) {
					if (check == 1){
						ResponseTime = ResponseTime + totburst;
					}
				}
			}

			if (ref->task->burst ==10 ) {
				if (check ==1){
					ResponseTime = ResponseTime + totburst;
				}
	
			}	

			totburst = totburst + 10; // totburst is 60
			if (ref->task->burst ==10) {
				turnaroundtime = totburst +  turnaroundtime; // turnaroundtime = 60
			}	

			ref->task->burst = 10;
			run(ref->task,10);	
		
		} else if (ref-> task-> burst  < 10 ) {
			newburst = 0;
			if (check ==1) {
				ResponseTime = ResponseTime + totburst;
			}
			totburst = totburst + ref->task->burst; 
			turnaroundtime = turnaroundtime + totburst ; 
			run(ref->task,ref->task->burst);	
		}	
 
		while(1) {	
			if (current->next !=NULL) { 
				current = current->next; // current = T4;
				if (current->next == NULL) { 
					if (newburst != 0) {
						struct node * newnode = malloc(sizeof(struct node));
						newnode->task = malloc(sizeof(struct task));	
						newnode->task->name = ref->task->name ;
						newnode->task->burst = newburst;
						newnode->task->priority = ref->task->priority;
						ref = ref->next ; // ref points to P2
						current->next = newnode;	// P4 points to New Node P1
						newnode->next = NULL; // P4 points to null
						current = ref;     // current points to P2
						break;	
					
					} else if (newburst == 0) {
						ref = ref->next;	 // ref points to T3
						current = ref; // current points to T3
						break;
					}	
				}
			
			} else { // if this is the last element
				if (newburst !=0) {
					struct node * new = malloc(sizeof(struct node));
					new->task = malloc(sizeof(struct task));	
					new->task->name = ref->task->name ;
					new->task->priority = ref->task->priority;
					new->task->burst = newburst;
					ref->next = new;
					ref = ref->next;
					new->next = NULL;
					current = new;
				
				} else {
					ref = ref->next;
				}
				break;	
			}	
		}
	
		if(number == 1){
            printf("  >> The CPU works on T1 for 10 time units (Remaining time: 10) \n");
        }else if(number == 2){
            printf("  >> Next, the CPU works on T2 for 10 time units (Remaining time: 15) \n");
        }else if(number == 3){
            printf("  >> Next, the CPU works on T3 for 10 time units (Remaining time: 15) \n");
        }else if(number == 4){
            printf("  >> Next, the CPU works on T4 for 10 time units (Remaining time: 5) \n");
        }else if(number == 5){
            printf("  >> Next, the CPU works on T5 for 10 time units (Remaining time: 10) \n");
        }else if(number == 6){
            printf("  >> Next, the CPU works on T6 for 10 time units and finishes it \n");
        }else if(number == 7){
            printf("  >> Next, the CPU works on T7 for 10 time units (Remaining time: 20) \n");
        }else if(number == 8){
            printf("  >> Next, the CPU works on T8 for 10 time units (Remaining time: 15) \n");
        }else if(number == 9){
            printf("  >> Next, the CPU works on T1 for 10 time units and finishes it \n");
        }else if(number == 10){
            printf("  >> Next, the CPU works on T2 for 10 time units (Remaining time: 5) \n");
        }else if(number == 11){
            printf("  >> Next, the CPU works on T3 for 10 time units (Remaining time: 5) \n");
        }else if(number == 12){
            printf("  >> Next, the CPU works on T4 for the remaining 5 time units and finishes it \n");
        }else if(number == 13){
            printf("  >> Next, the CPU works on T5 for 10 time units and finishes it \n");
        }else if(number == 14){
            printf("  >> Next, the CPU works on T7 for 10 time units (Remaining time: 10) \n");
        }else if(number == 15){
            printf("  >> Next, the CPU works on T8 for 10 time units (Remaining time: 5) \n");
        }else if(number == 16){
            printf("  >> Next, the CPU works on T2 for the remaining 5 time units and finishes it \n");
        }else if(number == 17){
            printf("  >> Next, the CPU works on T3 for the remaining 5 time units and finishes it \n");
        }else if(number == 18){
            printf("  >> Next, the CPU works on T7 for 10 time units and finishes it \n");
        }else if(number == 19){
			printf("  >> Next, the CPU works on T8 for the remaining 5 time units and finishes it \n");
		}
	
	}
	
	WaitTime = turnaroundtime - totburst;
	printf("The average turnaround time is : %f time units \n" , turnaroundtime/num);  	
	printf("The average response time is : %f time units \n" , ResponseTime/num);
	printf("The average Wait time is : %f time units \n" , WaitTime/num);
}



