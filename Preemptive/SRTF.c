#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;              // Process ID
    int arrival_time;     // Arrival Time
    int burst_time;       // Burst Time
    int remaining_time;   // Remaining Burst Time
    int completion_time;  // Completion Time
    int waiting_time;     // Waiting Time
    int turnaround_time;  // Turnaround Time
} Process;

void calculateTimes(Process processes[], int n) {
    int completed = 0, time = 0;
    int min_index, min_remaining_time;

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        min_index = -1;
        min_remaining_time = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_index = i;
                min_remaining_time = processes[i].remaining_time;
            }
        }

        if (min_index != -1) {
            printf(" P%d |", processes[min_index].pid);
            time++;
            processes[min_index].remaining_time--;

            // If the process is completed
            if (processes[min_index].remaining_time == 0) {
                processes[min_index].completion_time = time;
                processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
                processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
                completed++;
            }
        } else {
            // If no process is ready, increment the time
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
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
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
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    calculateTimes(processes, n);

    float avg_tat, avg_wt;
    calculateAverages(processes, n, &avg_tat, &avg_wt);

    displayResults(processes, n, avg_tat, avg_wt);

    return 0;
}