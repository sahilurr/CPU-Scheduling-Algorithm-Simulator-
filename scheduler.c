// scheduler.c - CPU scheduling algorithms implementation

#include <stdio.h>
#include "scheduler.h"

// prints the result table and avg times
void print_results(Process proc[], int n, const char *algo_name) {
    int i;
    float total_wt = 0, total_tat = 0;

    printf("\n===== %s =====\n", algo_name);
    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].waiting_time,
               proc[i].turnaround_time);

        total_wt  += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

    printf("Average Waiting Time    = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

// FCFS - just run them in order of arrival
void fcfs(Process proc[], int n) {
    int i;
    int current_time = 0;

    for (i = 0; i < n; i++) {
        // cpu idle, skip to arrival
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }

        current_time += proc[i].burst_time;
        proc[i].completion_time = current_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time    = proc[i].turnaround_time - proc[i].burst_time;
    }

    print_results(proc, n, "FCFS (First-Come, First-Served)");
}

// SJF non-preemptive - pick shortest burst among arrived processes
void sjf(Process proc[], int n) {
    int done[MAX_PROCESSES] = {0};
    int completed = 0;
    int current_time = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = 2147483647;
        int i;

        // find shortest burst that has arrived
        for (i = 0; i < n; i++) {
            if (!done[i] && proc[i].arrival_time <= current_time) {
                if (proc[i].burst_time < min_burst) {
                    min_burst = proc[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;  // no process arrived yet
            continue;
        }

        current_time += proc[idx].burst_time;
        proc[idx].completion_time = current_time;
        proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
        proc[idx].waiting_time    = proc[idx].turnaround_time - proc[idx].burst_time;

        done[idx] = 1;
        completed++;
    }

    print_results(proc, n, "SJF (Shortest Job First)");
}

// Round Robin - each process gets 'quantum' time, then goes back in queue
void round_robin(Process proc[], int n, int quantum) {
    int i;
    int queue[100];
    int front = 0, rear = 0;
    int in_queue[MAX_PROCESSES] = {0};
    int current_time = 0;
    int remaining_processes = n;

    for (i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    // add processes that arrive at t=0
    for (i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && !in_queue[i]) {
            queue[rear++] = i;
            in_queue[i] = 1;
        }
    }

    while (remaining_processes > 0) {
        if (front == rear) {
            // queue empty, advance time
            current_time++;
            for (i = 0; i < n; i++) {
                if (proc[i].arrival_time <= current_time &&
                    !in_queue[i] && proc[i].remaining_time > 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        int run_time = (proc[idx].remaining_time < quantum)
                            ? proc[idx].remaining_time
                            : quantum;

        current_time += run_time;
        proc[idx].remaining_time -= run_time;

        // add newly arrived processes before re-queuing current one
        for (i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time &&
                !in_queue[i] && proc[i].remaining_time > 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        if (proc[idx].remaining_time > 0) {
            queue[rear++] = idx;  // not done, send to back
        } else {
            proc[idx].completion_time = current_time;
            proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
            proc[idx].waiting_time    = proc[idx].turnaround_time - proc[idx].burst_time;
            remaining_processes--;
        }
    }

    print_results(proc, n, "Round Robin");
}

// Priority Scheduling (non-preemptive) - lower priority number = higher priority
void priority_scheduling(Process proc[], int n) {
    int done[MAX_PROCESSES] = {0};
    int completed = 0;
    int current_time = 0;

    while (completed < n) {
        int idx = -1;
        int best_priority = 2147483647;
        int i;

        for (i = 0; i < n; i++) {
            if (!done[i] && proc[i].arrival_time <= current_time) {
                if (proc[i].priority < best_priority) {
                    best_priority = proc[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
            continue;
        }

        current_time += proc[idx].burst_time;
        proc[idx].completion_time = current_time;
        proc[idx].turnaround_time = proc[idx].completion_time - proc[idx].arrival_time;
        proc[idx].waiting_time    = proc[idx].turnaround_time - proc[idx].burst_time;

        done[idx] = 1;
        completed++;
    }

    print_results(proc, n, "Priority Scheduling");
}
