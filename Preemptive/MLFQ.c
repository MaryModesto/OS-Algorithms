#include <stdio.h>
#include <stdbool.h>

#define TIME_QUANTUM 3  // Time Quantum for the highest-priority queue

// Structure for processes
typedef struct {
    int pid;              // Process ID
    int arrival_time;     // Arrival Time
    int burst_time;       // Burst Time
    int remaining_time;   // Remaining Time (for RR)
    int completion_time;  // Completion Time
    int waiting_time;     // Waiting Time
    int turnaround_time;  // Turnaround Time
    int priority;         // Priority level (higher number = lower priority)
} Process;

void scheduleMLFQ(Process processes[], int n) {
    int time = 0;
    int completed = 0;
    bool queue1_active = true; // High-priority queue active

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        bool progress = false;

        // High-priority queue (Round Robin)
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= time && processes[i].priority == 1) {
                progress = true;
                printf(" P%d |", processes[i].pid);

                if (processes[i].remaining_time <= TIME_QUANTUM) {
                    time += processes[i].remaining_time;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    completed++;
                } else {
                    time += TIME_QUANTUM;
                    processes[i].remaining_time -= TIME_QUANTUM;
                    // Demote to lower-priority queue
                    processes[i].priority = 2;
                }
            }
        }

        // Low-priority queue (FCFS)
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= time && processes[i].priority == 2) {
                progress = true;
                printf(" P%d |", processes[i].pid);
                time += processes[i].remaining_time;
                processes[i].completion_time = time;
                processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                processes[i].remaining_time = 0;
                completed++;
            }
        }

        // If no progress was made, increment time
        if (!progress) {
            time++;
        }
    }

    printf("\n\n");
}

void calculateAverages(Process processes[], int n, float *avg_tat, float *avg_wt) {
    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
    }
    *avg_tat = total_tat / n;
    *avg_wt = total_wt / n;
}

void displayResults(Process processes[], int n, float avg_tat, float avg_wt) {
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                processes[i].pid, 
                processes[i].arrival_time, 
                processes[i].burst_time, 
                processes[i].priority,
                processes[i].completion_time, 
                processes[i].turnaround_time, 
                processes[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].priority = 1; // All processes start in the highest priority queue
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    scheduleMLFQ(processes, n);

    float avg_tat, avg_wt;
    calculateAverages(processes, n, &avg_tat, &avg_wt);

    displayResults(processes, n, avg_tat, avg_wt);

    return 0;
}
