#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt, rt;
};

int main() {
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("Arrival Time of P%d: ", p[i].id);
        scanf("%d", &p[i].at);

        printf("Burst Time of P%d: ", p[i].id);
        scanf("%d", &p[i].bt);

        // initialize values
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
        p[i].rt = 0;
    }

    int completed = 0;
    int time = 0;
    int sumTAT = 0, sumWT = 0, sumRT = 0;

    int isComplete[n];
    for(int i = 0; i < n; i++)
        isComplete[i] = 0;

    while(completed < n) {

        int idx = -1;

        for(int i = 0; i < n; i++) {

            if(p[i].at <= time && isComplete[i] == 0) {

                if(idx == -1 || p[i].bt < p[idx].bt) {
                    idx = i;
                }
            }
        }

        if(idx != -1) {

            p[idx].rt = time - p[idx].at;

            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            sumTAT += p[idx].tat;
            sumWT += p[idx].wt;
            sumRT += p[idx].rt;

            time += p[idx].bt;

            isComplete[idx] = 1;
            completed++;
        }
        else {
            time++;  // CPU idle
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage TAT: %.2f\n", (float)sumTAT/n);
    printf("Average WT: %.2f\n", (float)sumWT/n);
    printf("Average RT: %.2f\n", (float)sumRT/n);

    return 0;
}
