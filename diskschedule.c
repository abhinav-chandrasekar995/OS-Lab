#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sort(int arr[], int n)
{
    int i, j, temp;

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    int req[100], tempReq[100], used[100];
    int n, head, ch, i, j, seek, diskSize;

    while(1)
    {
        printf("1.FCFS 2.SCAN 3.SSTF 4.C-LOOK 5.Exit \n");

        printf("\nEnter choice: ");
        scanf("%d", &ch);

        if(ch == 5)
        {
            printf("Exiting...\n");
            break;
        }

        printf("Enter number of requests: ");
        scanf("%d", &n);

        printf("Enter requests: ");
        for(i = 0; i < n; i++)
            scanf("%d", &req[i]);

        printf("Enter initial head position: ");
        scanf("%d", &head);

        seek = 0;

        switch(ch)
        {
            case 1: // FCFS
            {
                for(i = 0; i < n; i++)
                {
                    seek += abs(req[i] - head);
                    head = req[i];
                }

                printf("FCFS Seek Time = %d\n", seek);
                break;
            }

            case 2: // SSTF
            {
                for(i = 0; i < n; i++)
                    used[i] = 0;

                for(i = 0; i < n; i++)
                {
                    int min = 100000;
                    int idx = -1;

                    for(j = 0; j < n; j++)
                    {
                        int d = abs(req[j] - head);

                        if(!used[j] && d < min)
                        {
                            min = d;
                            idx = j;
                        }
                    }

                    if(idx != -1)
                    {
                        used[idx] = 1;
                        seek += min;
                        head = req[idx];
                    }
                }

                printf("SSTF Seek Time = %d\n", seek);
                break;
            }

            case 3: // SCAN
            {
                printf("Enter disk size: ");
                scanf("%d", &diskSize);

                for(i = 0; i < n; i++)
                    tempReq[i] = req[i];

                sort(tempReq, n);

                int pos;

                for(i = 0; i < n; i++)
                {
                    if(tempReq[i] >= head)
                    {
                        pos = i;
                        break;
                    }
                }

                for(i = pos; i < n; i++)
                {
                    seek += abs(tempReq[i] - head);
                    head = tempReq[i];
                }

                seek += abs((diskSize - 1) - head);
                head = diskSize - 1;

                for(i = pos - 1; i >= 0; i--)
                {
                    seek += abs(tempReq[i] - head);
                    head = tempReq[i];
                }

                printf("SCAN Seek Time = %d\n", seek);
                break;
            }

            case 4: // C-LOOK
            {
                for(i = 0; i < n; i++)
                    tempReq[i] = req[i];

                sort(tempReq, n);

                int pos;

                for(i = 0; i < n; i++)
                {
                    if(tempReq[i] >= head)
                    {
                        pos = i;
                        break;
                    }
                }

                for(i = pos; i < n; i++)
                {
                    seek += abs(tempReq[i] - head);
                    head = tempReq[i];
                }

                if(pos > 0)
                {
                    seek += abs(head - tempReq[0]);
                    head = tempReq[0];

                    for(i = 0; i < pos; i++)
                    {
                        seek += abs(tempReq[i] - head);
                        head = tempReq[i];
                    }
                }

                printf("C-LOOK Seek Time = %d\n", seek);
                break;
            }

            default:
                printf("Invalid Choice\n");
        }
        printf("\n");
    }

    return 0;
}