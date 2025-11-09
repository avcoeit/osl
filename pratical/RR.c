#include <stdio.h>

int main() {
    int n, i, tq, time = 0, completed = 0;
    int at[20], bt[20], rt[20], wt[20], tat[20], flag[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time of P%d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Remaining time initialized
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n");
    printf("0");

    while (completed != n) {
        int done = 1;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                done = 0;
                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    wt[i] = time - at[i] - bt[i];
                    rt[i] = 0;
                    completed++;
                }
                printf(" -- P%d -- %d", i+1, time);
            }
        }
        if(done) time++; // If no process arrived yet, move time forward
    }

    printf("\n\nProcess\tAT\tBT\tWT\tTAT\n");
    printf("----------------------------------------\n");

    float avgWT = 0, avgTAT = 0;
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avgWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);

    return 0;
}

