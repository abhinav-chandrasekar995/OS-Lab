
#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, queue;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int remaining[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT, BT, Queue (1/2) for P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].queue);
        remaining[i] = p[i].bt;
    }

    int time = 0, completed = 0, tq = 2;

    while (completed < n) {
        int executed = 0;


        for (int i = 0; i < n; i++) {
            if (p[i].queue == 1 && remaining[i] > 0 && p[i].at <= time) {
                executed = 1;

                if (remaining[i] > tq) {
                    time += tq;
                    remaining[i] -= tq;
                } else {
                    time += remaining[i];
                    remaining[i] = 0;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }


        if (!executed) {
            int idx = -1;


            for (int i = 0; i < n; i++) {
                if (p[i].queue == 2 && remaining[i] > 0 && p[i].at <= time) {
                    idx = i;
                    break;
                }
            }

            if (idx != -1) {
                time += remaining[idx];
                remaining[idx] = 0;

                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            } else {

                time++;
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tQueue\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].queue);
    }

    return 0;
}
