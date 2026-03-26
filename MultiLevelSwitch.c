    #include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int queue;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, Queue (1/2) for P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].queue);
    }

    int time = 0;
    int tq = 2;

    int remaining[n];
    for (int i = 0; i < n; i++) remaining[i] = p[i].bt;

    int done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].queue == 1 && remaining[i] > 0) {
                done = 0;

                if (time < p[i].at) time = p[i].at;

                if (remaining[i] > tq) {
                    time += tq;
                    remaining[i] -= tq;
                } else {
                    time += remaining[i];
                    remaining[i] = 0;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }
    } while (!done);
    for (int i = 0; i < n; i++) {
        if (p[i].queue == 2) {
            if (time < p[i].at) time = p[i].at;

            time += p[i].bt;
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tQueue\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct,
               p[i].tat, p[i].wt, p[i].queue);
    }

    return 0;
}
