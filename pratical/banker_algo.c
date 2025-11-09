#include <stdio.h>

#define MAX 10

int alloc[MAX][MAX], maxNeed[MAX][MAX], need[MAX][MAX];
int avail[MAX];
int pCount, rCount;

int isSafe() {
    int work[MAX], finish[MAX] = {0}, safeSeq[MAX];
    int i, j, count = 0;

    // Copy available to work
    for (i = 0; i < rCount; i++)
        work[i] = avail[i];

    while (count < pCount) {
        int found = 0;
        for (i = 0; i < pCount; i++) {
            if (!finish[i]) {
                int canRun = 1;
                for (j = 0; j < rCount; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    for (j = 0; j < rCount; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("\nSystem is NOT in SAFE state!\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE state.\nSafe Sequence: ");
    for (i = 0; i < pCount; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 1;
}

void request(int p, int req[]) {
    int i;

    // Check if request is valid
    for (i = 0; i < rCount; i++) {
        if (req[i] > need[p][i]) {
            printf("Error: Request exceeds process maximum need.\n");
            return;
        }
        if (req[i] > avail[i]) {
            printf("Process P%d must wait. Resources not available.\n", p);
            return;
        }
    }

    // Assume request is granted temporarily
    for (i = 0; i < rCount; i++) {
        avail[i] -= req[i];
        alloc[p][i] += req[i];
        need[p][i] -= req[i];
    }

    // Check if system remains safe
    if (isSafe()) {
        printf("Request can be granted to P%d.\n", p);
    } else {
        // Rollback
        for (i = 0; i < rCount; i++) {
            avail[i] += req[i];
            alloc[p][i] -= req[i];
            need[p][i] += req[i];
        }
        printf("Request CANNOT be granted as it leads to UNSAFE state.\n");
    }
}

int main() {
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &pCount);

    printf("Enter number of resources: ");
    scanf("%d", &rCount);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < pCount; i++)
        for (j = 0; j < rCount; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < pCount; i++)
        for (j = 0; j < rCount; j++)
            scanf("%d", &maxNeed[i][j]);

    printf("Enter Available Resources:\n");
    for (i = 0; i < rCount; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix
    for (i = 0; i < pCount; i++)
        for (j = 0; j < rCount; j++)
            need[i][j] = maxNeed[i][j] - alloc[i][j];

    isSafe(); // Initial safety check

    int p, req[MAX];
    printf("\nEnter process number making request: ");
    scanf("%d", &p);

    printf("Enter request for resources: ");
    for (i = 0; i < rCount; i++)
        scanf("%d", &req[i]);

    request(p, req);

    return 0;
}

/* output 
//Unsafe State
sagar@sagar-Lenovo-V15-IIL:~/Downloads$ gcc ba.c
sagar@sagar-Lenovo-V15-IIL:~/Downloads$ ./a.out
Enter number of processes: 3
Enter number of resources: 3
Enter Allocation Matrix:
0 1 0
2 0 0
3 0 3
Enter Maximum Matrix:
7 5 3
3 2 2
9 0 4
Enter Available Resources:
2 3 2
System is NOT in a safe state!
Enter process number making request: 0
Enter request for resources: 0 2 0
System is NOT in a safe state!
Request cannot be granted as it leads to UNSAFE state.

// Safe State
sagar@sagar-Lenovo-V15-IIL:~/Downloads$ gcc ba.c
sagar@sagar-Lenovo-V15-IIL:~/Downloads$ ./a.out
Enter number of processes: 5
Enter number of resources: 3
Enter Allocation Matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter Maximum Matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter Available Resources:
3 3 2
System is in a SAFE state.
Safe Sequence: P1 P3 P4 P0 P2
Enter process number making request: 1
Enter request for resources: 1 0 2
System is in a SAFE state.
Safe Sequence: P1 P3 P4 P0 P2
Request granted to P1.
*/
