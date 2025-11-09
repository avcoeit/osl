#include <stdio.h>

int main() {
    int p, r, i, j, k, count = 0;
    int alloc[10][10], max[10][10], need[10][10], avail[10], done[10] = {0}, safe[10];

    printf("Enter number of processes: ");
    scanf("%d", &p);
    printf("Enter number of resources: ");
    scanf("%d", &r);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    // Calculate Need Matrix
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Find Safe Sequence
    while (count < p) {
        int found = 0;
        for (i = 0; i < p; i++) {
            if (!done[i]) {
                for (j = 0; j < r; j++)
                    if (need[i][j] > avail[j]) break;

                if (j == r) {   // All needs satisfied
                    for (k = 0; k < r; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    done[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break;
    }

    if (count == p) {
        printf("\nSystem is in SAFE state.\nSafe Sequence: ");
        for (i = 0; i < p; i++)
            printf("P%d ", safe[i]);
    } else {
        printf("\nSystem is NOT in SAFE state!\n");
    }

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

/* ======================================================================
   ✅ LINE-BY-LINE EXPLANATION — SIMPLE BANKER'S ALGORITHM PROGRAM
   ======================================================================

1.  alloc[][]  → Allocation matrix (resources currently allocated to each process)
2.  max[][]    → Maximum resources each process may request
3.  need[][]   → Remaining need (calculated as max - alloc)
4.  avail[]    → Currently available resources in the system
5.  done[]     → Marks if a process has completed execution (0 = not done, 1 = completed)
6.  safe[]     → Stores safe execution order (safe sequence)

---------------------------- INPUT SECTION -----------------------------

7.  scanf("%d", &p); → number of processes
8.  scanf("%d", &r); → number of resources

9.  Read Allocation Matrix (current allocation of resources)
10. Read Maximum Matrix (maximum required resources per process)
11. Read Available Vector (free resources left in the system)

------------------------ NEED MATRIX FORMULA ---------------------------

12. need[i][j] = max[i][j] - alloc[i][j]
    Example: max = 7, alloc = 3 → need = 4

----------------------- SAFETY ALGORITHM LOGIC -------------------------

13. while(count < p)
    - Keep finding processes that can safely execute

14. for each process i:
        if (!done[i]): (not completed yet)
            check if need <= available for all resources

15. if all needs are <= available (j == r):
        - Process can finish execution
        - Add its allocated resources back to available
        - Mark as done
        - Add process index to safe sequence

16. If no process found in an iteration → UNSAFE system

------------------------- FINAL CHECK & OUTPUT -------------------------

17. If all processes got executed (count == p):
        → System is SAFE
        → Print safe sequence: P1 P3 P2...

18. Else:
        → System is NOT SAFE (deadlock possible)

------------------------------ SAMPLE OUTPUT ---------------------------

Enter number of processes: 5
Enter number of resources: 3
...
System is in SAFE state.
Safe Sequence: P1 P3 P4 P0 P2

------------------------- REAL WORLD MEANING ---------------------------

✔ Processes = different running programs  
✔ Resources = CPU cores, memory blocks, I/O devices  
✔ Banker's Algorithm prevents DEADLOCK by denying unsafe allocation  

=======================================================================
   END OF EXPLANATION
=======================================================================
*/





