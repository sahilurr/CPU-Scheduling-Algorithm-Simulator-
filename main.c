// main.c - runs all 4 scheduling algorithms on same process set

#include <stdio.h>
#include <string.h>
#include "scheduler.h"

#define NUM_PROCESSES 5
#define TIME_QUANTUM  2

int main(void) {
    // sample processes: {pid, arrival, burst, priority, remaining, ct, wt, tat}
    Process original[NUM_PROCESSES] = {
        {1, 0, 5, 2, 0, 0, 0, 0},
        {2, 1, 3, 1, 0, 0, 0, 0},
        {3, 2, 8, 4, 0, 0, 0, 0},
        {4, 3, 6, 3, 0, 0, 0, 0},
        {5, 4, 4, 5, 0, 0, 0, 0}
    };

    Process proc[NUM_PROCESSES];
    int i;

    printf("Sample Process Set\n");
    printf("PID\tArrival\tBurst\tPriority\n");
    for (i = 0; i < NUM_PROCESSES; i++) {
        printf("%d\t%d\t%d\t%d\n",
               original[i].pid,
               original[i].arrival_time,
               original[i].burst_time,
               original[i].priority);
    }

    // run each algo on a fresh copy so results dont interfere
    memcpy(proc, original, sizeof(original));
    fcfs(proc, NUM_PROCESSES);

    memcpy(proc, original, sizeof(original));
    sjf(proc, NUM_PROCESSES);

    memcpy(proc, original, sizeof(original));
    round_robin(proc, NUM_PROCESSES, TIME_QUANTUM);

    memcpy(proc, original, sizeof(original));
    priority_scheduling(proc, NUM_PROCESSES);

    return 0;
}
