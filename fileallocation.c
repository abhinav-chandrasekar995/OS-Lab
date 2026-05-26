
#include <stdio.h>

int main() {
    int ch, i, n, start, len, idx;
    int disk[100] = {0}, block[50], next[100];
    while(1)
    {
    printf("\n1.Sequential Allocation");
    printf("\n2.Indexed Allocation");
    printf("\n3.Linked Allocation");
    printf("\nEnter choice: ");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            printf("Enter starting block and length: ");
            scanf("%d%d", &start, &len);
            {
                int ok = 1;
                if (start < 0 || start + len > 100 || len <= 0)
                    ok = 0;
                for (i = start; i < start + len && ok; i++) {
                    if (disk[i])
                        ok = 0;
                }
                if (ok) {
                    printf("Allocated Blocks: ");
                    for (i = start; i < start + len; i++) {
                        disk[i] = 1;
                        printf("%d ", i);
                    }
                } else {
                    printf("Allocation Failed");
                }
            }
            break;

        case 2:
            printf("Enter index block: ");
            scanf("%d", &idx);
            if (idx < 0 || idx >= 100 || disk[idx]) {
                printf("Invalid or Busy Index Block");
                return 0;
            }
            printf("Enter number of blocks: ");
            scanf("%d", &n);
            printf("Enter blocks: ");
            for (i = 0; i < n; i++) {
                scanf("%d", &block[i]);
                if (block[i] < 0 || block[i] >= 100 || disk[block[i]]) {
                    printf("Invalid or Busy Block");
                    return 0;
                }
            }
            disk[idx] = 1;
            printf("Index Block %d -> ", idx);
            for (i = 0; i < n; i++) {
                disk[block[i]] = 1;
                printf("%d ", block[i]);
            }
            break;

        case 3:
            for (i = 0; i < 100; i++)
                next[i] = -1;
            printf("Enter number of blocks: ");
            scanf("%d", &n);
            printf("Enter blocks: ");
            for (i = 0; i < n; i++) {
                scanf("%d", &block[i]);
                if (block[i] < 0 || block[i] >= 100) {
                    printf("Invalid Block");
                    return 0;
                }
            }
            for (i = 0; i < n - 1; i++)
                next[block[i]] = block[i + 1];
            printf("Linked File Allocation: ");
            {
                int cur = block[0];
                while (cur != -1) {
                    printf("%d ", cur);
                    cur = next[cur];
                }
            }
            break;

        default:
            printf("Invalid Choice");
    }
    printf("\n");
}

    return 0;
}