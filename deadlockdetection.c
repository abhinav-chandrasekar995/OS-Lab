#include <stdio.h>
#include <stdbool.h>

#define N 5  // Number of processes
#define M 3  // Number of resource types

void deadlockDetection(int avail[], int alloc[][M], int request[][M]) {
    int work[M];
    bool finish[N];
    
    // Initialize Work = Available
    for (int i = 0; i < M; i++)
        work[i] = avail[i];
    
    // Initialize Finish[i] = false if Request[i] != 0, else true
    for (int i = 0; i < N; i++) {
        bool hasRequest = false;
        for (int j = 0; j < M; j++) {
            if (request[i][j] != 0) {
                hasRequest = true;
                break;
            }
        }
        finish[i] = !hasRequest;
    }
    
    int count = 0;
    while (count < N) {
        bool found = false;
        for (int i = 0; i < N; i++) {
            if (finish[i] == false) {
                bool canAllocate = true;
                for (int j = 0; j < M; j++) {
                    if (request[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                
                if (canAllocate) {
                    // Work = Work + Allocation[i]
                    for (int j = 0; j < M; j++)
                        work[j] += alloc[i][j];
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        
        if (!found)
            break;
    }
    
    // Check if there's any process with Finish[i] == false
    bool deadlock = false;
    printf("\nDeadlock Detection Results:\n");
    printf("===========================\n");
    for (int i = 0; i < N; i++) {
        if (finish[i] == false) {
            printf("Process P%d is deadlocked\n", i);
            deadlock = true;
        } else {
            printf("Process P%d is not deadlocked\n", i);
        }
    }
    
    if (deadlock)
        printf("\nSystem is in DEADLOCKED state!\n");
    else
        printf("\nSystem is NOT deadlocked.\n");
}

int main() {
    int avail[] = {0, 0, 0};
    
    int alloc[N][M] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1},
        {0, 0, 2}
    };
    
    int request[N][M] = {
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
    };
    
    printf("Deadlock Detection - Multiple Instance Resources\n");
    printf("================================================\n");
    printf("Available resources: ");
    for (int i = 0; i < M; i++)
        printf("%d ", avail[i]);
    printf("\n");
    
    deadlockDetection(avail, alloc, request);
    
    return 0;
}