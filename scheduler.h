#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_PROCESSES 20

// process control block
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;        // lower = higher priority
    int remaining_time;  // for round robin
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void fcfs(Process proc[], int n);
void sjf(Process proc[], int n);
void round_robin(Process proc[], int n, int quantum);
void priority_scheduling(Process proc[], int n);
void print_results(Process proc[], int n, const char *algo_name);

#endif
