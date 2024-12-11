#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACKS 1000

// Function to calculate total head movement and process requests using C-SCAN
void cscan(int initial_position, int requests[], int num_requests, int disk_size) {
    int total_head_movement = 0;
    int current_position = initial_position;

    // Sort the requests array
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = i + 1; j < num_requests; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Separate requests into those greater and less than the initial position
    int greater[MAX_TRACKS], greater_count = 0;
    int lesser[MAX_TRACKS], lesser_count = 0;

    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= initial_position) {
            greater[greater_count++] = requests[i];
        } else {
            lesser[lesser_count++] = requests[i];
        }
    }

    printf("Order of access: ");

    // Move towards the end of the disk (higher tracks)
    for (int i = 0; i < greater_count; i++) {
        printf("%d ", greater[i]);
        total_head_movement += abs(current_position - greater[i]);
        current_position = greater[i];
    }

    // Jump to the start of the disk (wrap-around)
    if (greater_count > 0) {
        total_head_movement += abs(current_position - (disk_size - 1)); // Move to end
        current_position = 0; // Jump to start
        total_head_movement += abs(disk_size - 1); // Jump distance
    }

    // Process the remaining lower tracks
    for (int i = 0; i < lesser_count; i++) {
        printf("%d ", lesser[i]);
        total_head_movement += abs(current_position - lesser[i]);
        current_position = lesser[i];
    }

    printf("\nTotal head movement: %d\n", total_head_movement);
}

int main() {
    int initial_position, num_requests, disk_size;

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &initial_position);

    printf("Enter the number of I/O requests: ");
    scanf("%d", &num_requests);

    int requests[MAX_TRACKS];

    printf("Enter the track requests: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    cscan(initial_position, requests, num_requests, disk_size);

    return 0;
}