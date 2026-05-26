#include <stdio.h>
#include <stdlib.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    printf("\n=== FIRST FIT ===\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
        if (allocation[i] != -1)
            printf("P%d\t\t%d\t\t%d\n", i, processSize[i], allocation[i] + 1);
        else
            printf("P%d\t\t%d\t\tNot Allocated\n", i, processSize[i]);
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    printf("\n=== BEST FIT ===\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
            printf("P%d\t\t%d\t\t%d\n", i, processSize[i], bestIdx + 1);
        } else
            printf("P%d\t\t%d\t\tNot Allocated\n", i, processSize[i]);
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    
    printf("\n=== WORST FIT ===\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
            printf("P%d\t\t%d\t\t%d\n", i, processSize[i], worstIdx + 1);
        } else
            printf("P%d\t\t%d\t\tNot Allocated\n", i, processSize[i]);
    }
}

int main() {
    int m, n;
    
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    
    int *blockSize = (int*)malloc(m * sizeof(int));
    int *originalBlockSize = (int*)malloc(m * sizeof(int));
    
    printf("Enter size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        originalBlockSize[i] = blockSize[i];
    }
    
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    
    int *processSize = (int*)malloc(n * sizeof(int));
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    
    // First Fit
    for (int i = 0; i < m; i++) blockSize[i] = originalBlockSize[i];
    firstFit(blockSize, m, processSize, n);
    
    // Best Fit
    for (int i = 0; i < m; i++) blockSize[i] = originalBlockSize[i];
    bestFit(blockSize, m, processSize, n);
    
    // Worst Fit
    for (int i = 0; i < m; i++) blockSize[i] = originalBlockSize[i];
    worstFit(blockSize, m, processSize, n);
    
    free(blockSize);
    free(originalBlockSize);
    free(processSize);
    
    return 0;
}