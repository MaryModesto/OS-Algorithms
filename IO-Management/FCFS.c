#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate total head movement and display the order of requests served
void calculateFCFS(int initial_position, int requests[], int n) {
    int total_head_movement = 0;
    int current_position = initial_position;

    printf("\nOrder of requests served:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", requests[i]);
        total_head_movement += abs(requests[i] - current_position);
        current_position = requests[i];
    }
    printf("END\n");

    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

int main() {
    int initial_position;
    int n;

    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &initial_position);

    printf("Enter the number of track requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the track requests:\n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Calculate and display results using FCFS
    calculateFCFS(initial_position, requests, n);

    return 0;
}
