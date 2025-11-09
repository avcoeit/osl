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


/* --------------------------------------------------------------
   LINE-BY-LINE EXPLANATION (SSTF Disk Scheduling Program)
   --------------------------------------------------------------

1.  #include <stdio.h>    → For input/output
2.  #include <stdlib.h>   → For abs() function (absolute value)

3.  int n, i, current, total = 0;
    - n = number of disk requests
    - current = current head position
    - total = total head movement
    - i = loop variable

4.  int requests[100], done[100] = {0};
    - requests[] stores disk request sequence
    - done[] marks which requests are already serviced (0 = not done, 1 = done)

5.  scanf("%d", &n); → Read number of requests

6.  Read each disk request inside loop: requests[i]

7.  scanf("%d", &current); → Read starting head position

8.  Print initial head position: printf("Sequence: %d", current);

9.  for (int count = 0; count < n; count++)
    - Loop runs until all requests are serviced

10. int minDist = 9999, pos = -1;
    - minDist stores minimum distance found
    - pos stores index of nearest request

11. Inner loop: for (i = 0; i < n; i++)
    - Scan entire request list to find nearest unserved request

12. if (!done[i])
    - Process only requests not completed yet

13. int distance = abs(current - requests[i]);
    - Calculate absolute distance from current head to request

14. if (distance < minDist)
    - Update minimum distance and index

15. After inner loop:
    - total += minDist;       → Add movement to total
    - current = requests[pos] → Move head to that request
    - done[pos] = 1           → Mark request as completed

16. Print serviced order: printf(" -> %d", current);

17. After servicing all requests, print:
    printf("\nTotal head movement: %d\n", total);

18. return 0; → End program

--------------------------------------------------------------
ABOUT SSTF (Shortest Seek Time First):
--------------------------------------------------------------
✔ SSTF always selects the request closest to the current head position  
✔ Reduces total head movement compared to FCFS  
✔ But may cause starvation if far-away requests are never chosen  

Example:
Requests: 82, 170, 43, 140, 24, 16, 190  
Head = 50  
Nearest request = 43 → next nearest → 24 → 16 → etc.

--------------------------------------------------------------
END OF EXPLANATION
--------------------------------------------------------------
*/

