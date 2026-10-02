<div align="center">

# ⚙️ CPU Scheduling Algorithm Simulator

![C](https://img.shields.io/badge/Language-C-blue?logo=c&logoColor=white)

A lightweight C-based simulator that implements and compares **4 classic CPU scheduling algorithms** on the same process set.

</div>

---

## 📌 About

This project simulates how an operating system schedules processes on a single CPU. It runs all four algorithms on identical input so we can directly compare metrics like average waiting time and turnaround time.

## 🧠 Algorithms Implemented

| Algorithm | Type | Description |
|-----------|------|-------------|
| **FCFS** | Non-preemptive | First Come First Served — processes run in arrival order |
| **SJF** | Non-preemptive | Shortest Job First — picks the process with the smallest burst time |
| **Round Robin** | Preemptive | Each process gets a fixed time quantum, then cycles back |
| **Priority** | Non-preemptive | Lower priority number = higher priority |

### Metrics Calculated

For each process under every algorithm:
- **Completion Time (CT)** — when the process finishes execution
- **Turnaround Time (TAT)** = CT − Arrival Time
- **Waiting Time (WT)** = TAT − Burst Time
- **Average WT & TAT** across all processes

## 🛠️ Build & Run

### Using Make
```bash
make run
```

### Manual Compilation
```bash
gcc -Wall -Wextra -std=c11 -o scheduler_sim scheduler.c main.c
./scheduler_sim
```

## 📂 Project Structure

```
CPU-Scheduling-Algorithm-Simulator/
├── scheduler.h    # Process struct and function prototypes
├── scheduler.c    # All 4 scheduling algorithm implementations
├── main.c         # Driver code with sample process set
├── Makefile       # Build automation
└── README.md
```

## 📸 Sample Output

```
Sample Process Set
PID     Arrival Burst   Priority
1       0       5       2
2       1       3       1
3       2       8       4
4       3       6       3
5       4       4       5

===== FCFS (First-Come, First-Served) =====
PID     AT      BT      CT      WT      TAT
1       0       5       5       0       5
2       1       3       8       4       7
3       2       8       16      6       14
4       3       6       22      13      19
5       4       4       26      18      22
Average Waiting Time    = 8.20
Average Turnaround Time = 13.40

===== SJF (Shortest Job First) =====
...
```

## 💡 Key Takeaways

- **FCFS** is the simplest but suffers from the convoy effect — one long process blocks everything behind it
- **SJF** gives the best average waiting time theoretically, but needs burst times known in advance
- **Round Robin** prevents starvation but quantum size is critical — too small causes excessive context switches
- **Priority Scheduling** can starve low-priority processes; real OSes use aging to fix this
- <3
