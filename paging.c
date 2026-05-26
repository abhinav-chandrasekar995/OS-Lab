#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int frames, pages;
int pageRef[100];
int frame[10];
int hit = 0, miss = 0;

void fifo() {
    int stack[10] = {0}, top = 0;
    int pageNo[10] = {0};
    int flag, count = 0;
    
    printf("\n=== FIFO PAGE REPLACEMENT ===\n");
    printf("Page\tFrame Array\n");
    
    for (int i = 0; i < pages; i++) {
        flag = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pageRef[i]) {
                flag = 1;
                hit++;
                break;
            }
        }
        
        if (flag == 0) {
            if (count < frames) {
                frame[count] = pageRef[i];
                pageNo[top] = pageRef[i];
                stack[top++] = count;
                count++;
                miss++;
            } else {
                int pos = stack[0];
                for (int j = 0; j < top - 1; j++) {
                    stack[j] = stack[j + 1];
                    pageNo[j] = pageNo[j + 1];
                }
                top--;
                frame[pos] = pageRef[i];
                pageNo[top] = pageRef[i];
                stack[top++] = pos;
                miss++;
            }
        }
        
        printf("%d\t", pageRef[i]);
        for (int j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
}

void lru() {
    int frameAge[10];
    
    printf("\n=== LRU PAGE REPLACEMENT ===\n");
    printf("Page\tFrame Array\n");
    
    for (int i = 0; i < frames; i++)
        frame[i] = -1;
    
    for (int i = 0; i < pages; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pageRef[i]) {
                found = 1;
                frameAge[j] = i;
                hit++;
                break;
            }
        }
        
        if (!found) {
            int minAge = 999999, pos = 0, emptyPos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    emptyPos = j;
                    break;
                }
                if (frameAge[j] < minAge) {
                    minAge = frameAge[j];
                    pos = j;
                }
            }
            
            if (emptyPos != -1) {
                frame[emptyPos] = pageRef[i];
                frameAge[emptyPos] = i;
            } else {
                frame[pos] = pageRef[i];
                frameAge[pos] = i;
            }
            miss++;
        }
        
        printf("%d\t", pageRef[i]);
        for (int j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
}

void optimal() {
    int future[100];
    
    printf("\n=== OPTIMAL PAGE REPLACEMENT ===\n");
    printf("Page\tFrame Array\n");
    
    for (int i = 0; i < frames; i++)
        frame[i] = -1;
    
    for (int i = 0; i < pages; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pageRef[i]) {
                found = 1;
                hit++;
                break;
            }
        }
        
        if (!found) {
            int farthest = i, pos = 0, emptyPos = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    emptyPos = j;
                    break;
                }
                int k;
                for (k = i + 1; k < pages; k++) {
                    if (frame[j] == pageRef[k])
                        break;
                }
                if (k == pages && farthest == i) {
                    farthest = k;
                    pos = j;
                } else if (k > farthest) {
                    farthest = k;
                    pos = j;
                }
            }
            
            if (emptyPos != -1)
                frame[emptyPos] = pageRef[i];
            else
                frame[pos] = pageRef[i];
            miss++;
        }
        
        printf("%d\t", pageRef[i]);
        for (int j = 0; j < frames; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }
}

int main() {
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    
    printf("Enter number of page references: ");
    scanf("%d", &pages);
    
    printf("Enter page reference string:\n");
    for (int i = 0; i < pages; i++)
        scanf("%d", &pageRef[i]);
    
    fifo();
    
    hit = miss = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    lru();
    
    hit = miss = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    optimal();
    
    printf("\n=== SUMMARY ===\n");
    printf("Total Hits: %d\n", hit);
    printf("Total Misses: %d\n", miss);
    printf("Hit Rate: %.2f%%\n", (float)hit / (hit + miss) * 100);
    printf("Miss Rate: %.2f%%\n", (float)miss / (hit + miss) * 100);
    
    return 0;
}