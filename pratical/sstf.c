#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, current, total = 0;
    int requests[100], done[100] = {0};

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk requests: ");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &current);

    printf("\nSSTF Disk Scheduling:\n");
    printf("Sequence: %d", current);

    for (int count = 0; count < n; count++) {

        int minDist = 9999, pos = -1;

        // Find the nearest request
        for (i = 0; i < n; i++) {
            if (!done[i]) {
                int distance = abs(current - requests[i]);
                if (distance < minDist) {
                    minDist = distance;
                    pos = i;
                }
            }
        }

        total += minDist;          // Add movement
        current = requests[pos];   // Move head
        done[pos] = 1;             // Mark request as completed

        printf(" -> %d", current);
    }

    printf("\nTotal head movement: %d\n", total);
    return 0;
}


//save file as sstf.c
// run commond gcc sstf.c
// ./a.out

