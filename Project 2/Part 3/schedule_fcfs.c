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
int num = 0;

void add(char *name, int priority, int burst) {
    
    printf("** Calling add function for [%s] [%d] [%d] \n", name, priority, burst);

    if (head == NULL) {
        printf("  >> Adding the first task to the head node \n\n");
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
        printf("  >> Add the new task to the end of the linked list \n\n");
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
    
    printf("** Calling schedule function \n\n");

    int final = 0;
    float turnaroundtime = 0;
    float WaitTime = 0;
    float ResponseTime = 0;
    struct node * ref = head;

    printf("****************************************************************************** \n");
    printf("First-come, first-served (FCFS) \n");
    printf("This algorithm schedules tasks in the order in which they request the CPU \n");
    printf("In this case, the add function will add tasks to the linked list in the order they came in and the CPU will traverse through the list and run the tasks \n");
    printf("****************************************************************************** \n\n");
    
    printf(">> Traverse through the linked list and run the tasks in order\n");
    while (ref !=NULL) {
        num = num +1;
        run(ref->task,ref->task->burst);  

        final =  final + ref->task->burst; // 5 15 30
        turnaroundtime = turnaroundtime + final ; //5 (5+10+5)20  50      (5 + 5+10 + 5+10+15)

        if (ref->next !=NULL) {
            ResponseTime = ResponseTime + final;
        }
        ref = ref->next;    
    }
    WaitTime = turnaroundtime - final;

    printf("\n");
    printf("The average turnaround time is : %f time units \n" , turnaroundtime/num);    
    printf("The average ResponseTime is : %f time units \n" , ResponseTime/num);
    printf("The average WaitTime is : %f time units\n " , WaitTime/num);
}






