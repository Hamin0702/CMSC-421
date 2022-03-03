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
    
    int final = 0;
    float turnaroundtime = 0;
    float WaitTime = 0;
    float ResponseTime = 0;
    struct node * ref = head;

    printf("****************************************************************************** \n");
    printf("First-come, first-served (FCFS) \n");
    printf("This algorithm schedules tasks in the order in which they request the CPU \n");
    printf("In this case, the CPU will start with T1 since it is the first task and continue chronologically until ending with T8 \n");
    printf("****************************************************************************** \n\n");

    while (ref !=NULL) {
        num = num +1;
        run(ref->task,ref->task->burst);  

        if(num == 1){
            printf("  >> T1 is the first task so the CPU finishes T1 first \n");
        }else if(num == 2){
            printf("  >> The CPU works on the next task T2 and finishes it \n");
        }else if(num == 3){
            printf("  >> The CPU works on the next task T3 and finishes it \n");
        }else if(num == 4){
            printf("  >> The CPU works on the next task T4 and finishes it \n");
        }else if(num == 5){
            printf("  >> The CPU works on the next task T5 and finishes it \n");
        }else if(num == 6){
            printf("  >> The CPU works on the next task T6 and finishes it \n");
        }else if(num == 7){
            printf("  >> The CPU works on the next task T7 and finishes it \n");
        }else if(num == 8){
            printf("  >> The CPU works on the next task T8 and finishes it \n\n");
        }

        final =  final + ref->task->burst; // 5 15 30
        turnaroundtime = turnaroundtime + final ; //5 (5+10+5)20  50      (5 + 5+10 + 5+10+15)

        if (ref->next !=NULL) {
            ResponseTime = ResponseTime + final;
        }
        ref = ref->next;    
    }
    WaitTime = turnaroundtime - final;

    printf("The average turnaround time is : %f time units \n" , turnaroundtime/num);    
    printf("The average ResponseTime is : %f time units \n" , ResponseTime/num);
    printf("The average WaitTime is : %f time units\n " , WaitTime/num);
}






