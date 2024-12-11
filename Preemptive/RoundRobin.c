#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid;           // Process ID
    int arrival_time;  // Arrival Time
    int burst_time;    // Burst Time
    int remaining_time; // Remaining Burst Time
    int completion_time; // Completion Time
    int waiting_time;  // Waiting Time
    int turnaround_time; // Turnaround Time
} Process;

void calculateTimes(Process processes[], int n, int time_quantum) {
    int time = 0;
    int completed = 0;
    bool in_queue[n];
    for (int i = 0; i < n; i++) in_queue[i] = false;

    printf("\nGantt Chart:\n");
    printf("|");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                printf(" P%d |", processes[i].pid);
                if (processes[i].remaining_time > time_quantum) {
                    time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed++;
                }
            }
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
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                processes[i].pid, 
                processes[i].arrival_time, 
                processes[i].burst_time, 
                processes[i].completion_time, 
                processes[i].turnaround_time, 
                processes[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f", avg_tat);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    calculateTimes(processes, n, time_quantum);

    float avg_tat, avg_wt;
    calculateAverages(processes, n, &avg_tat, &avg_wt);

    displayResults(processes, n, avg_tat, avg_wt);

    return 0;
}
