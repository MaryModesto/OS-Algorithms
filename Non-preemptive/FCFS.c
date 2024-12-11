#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char process_ID;
    int arrival_Time;
    int priority_Num;
}process_info;

typedef struct Node {
    int burst_Time;
    process_info info;
    struct Node *prev;
    struct Node *next;
}nodeType, *nodePtr;

typedef struct {
    nodePtr FRONT;
    nodePtr BACK;
}QUEUE;

void DisplayTable(nodePtr L);
void AddInQueue(QUEUE *Q, nodeType elem);
void Reset(QUEUE *Q);

int main()
{
    QUEUE queue = {NULL, NULL};
    int input = 1, x;
    char pID = 'A';

    nodeType elem;
    elem.info.priority_Num = 0;
    elem.info.process_ID = pID;
    elem.next = elem.prev = NULL;

    while (input != 5) {
        printf("FIRST COME FIRST SERVE\n\n");
        printf("Hello there! What would you like to do?...\n");
        printf("[1] - Display Process Table\n");
        printf("[2] - Display Gantt Chart\n");
        printf("[3] - Add a Process\n");
        printf("[4] - Reset Processes\n");
        printf("[5] - Exit Program\n\n");
        
        printf("Input a number: ");
        scanf("%d", &input);
        printf("\n\n");

        if (input > 5 || input < 1) {
            printf("Out of bounds! Please input another number...");
        }

        switch (input) {
            case 1:
                DisplayTable(queue.FRONT);
                break;
            case 3:
                printf("Please input an answer for the following fields...\n\n");
                printf("What is the burst time of this process? ");
                scanf("%d", &x);
                elem.burst_Time = x;

                printf("What is the arrival time of the process? ");
                scanf("%d", &x);
                elem.info.arrival_Time = x;

                elem.info.process_ID = pID;

                AddInQueue(&queue, elem);
                pID++;
                break;
            case 4:
                Reset(&queue);
                printf("\n= All Processes Reset =\n");
                break;

            default:
                printf("= End of Program =");
        }

        printf("\n\n");
    }
    return 0;
}

void DisplayTable(nodePtr L) {
    printf("+------------+--------------+------------+\n");
    printf("| Process ID | Arrival Time | Burst Time |\n");
    printf("+------------+--------------+------------+\n");

    while (L != NULL) {
        printf("| %-10c | %-12d | %-10d |\n",
               L->info.process_ID,
               L->info.arrival_Time,
               L->burst_Time);
        L = L->prev;
    }

    printf("+------------+--------------+------------+\n");
}

void AddInQueue(QUEUE *Q, nodeType elem) {
    nodePtr newProcess = (nodePtr)malloc(sizeof(struct Node));

    if (newProcess != NULL) {
        newProcess->burst_Time = elem.burst_Time;
        newProcess->info = elem.info;
        newProcess->next = newProcess->prev = NULL;

        if (Q->BACK == NULL) {
            Q->FRONT = newProcess;
            Q->BACK = newProcess;
            newProcess->prev = NULL;
        } else {
            nodePtr *trav, temp;

            for (trav = &(Q->BACK); (*trav)->next != NULL && (*trav)->info.arrival_Time > elem.info.arrival_Time; trav = &(*trav)->next) {}
            
            if ((*trav)->info.arrival_Time > elem.info.arrival_Time) {
                temp = *trav;
                newProcess->next = temp->next;
                temp->next = newProcess;
                newProcess->prev = *trav;
                
                if (newProcess->next != NULL) {
                    newProcess->next->prev = newProcess;
                }
            } else {
                newProcess->next = *trav;
                *trav = newProcess;
                newProcess->prev = newProcess->next->prev;
                newProcess->next->prev = newProcess;
            }

            if (newProcess->next == NULL) {
                Q->FRONT = newProcess;
            }

        }
    }
    //printf("yes");
}

void Reset(QUEUE *Q) {
    nodePtr temp;

    while (Q->FRONT != NULL) {
        temp = Q->FRONT;
        Q->FRONT = Q->FRONT->prev;
        free(temp);
    }
}