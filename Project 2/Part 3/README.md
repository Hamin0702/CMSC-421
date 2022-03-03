# CMSC 421 Project 2 Part 3 - Hamin Han
## Scheduling Algorithms

This part of the project involves implementing several different CPU process scheduling
algorithms. The scheduler will be assigned a predefined set of tasks and will schedule the tasks
based on the selected scheduling algorithm. Each task is assigned a priority and CPU burst. The
following scheduling algorithms will be implemented:

1. First-come, first-served (FCFS), which schedules tasks in the order in which they
request the CPU.
2. Shortest-job-first (SJF), which schedules tasks in order of the length of the tasks' next
CPU burst.
3. Priority* scheduling, which schedules tasks based on priority.
4. Round-robin** (RR) scheduling, where each task is run for a time quantum (or for the
remainder of its CPU burst).
5. Priority* with round-robin**, which schedules tasks in order of priority and uses
round-robin scheduling for tasks with equal priority.

### The code solution was inspired from a user named BY98 on Github
#### Github Link: https://github.com/BY98/Scheduling-Algorithms