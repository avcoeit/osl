#include <stdio.h>

int main() {
    int frames, pages[100], frame[10], n, i, j, f = 0;
    int faults = 0, hits = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nPage\tFrames\t\tStatus\n");
    printf("----\t------\t\t------\n");

    for(i = 0; i < n; i++) {
        int hit = 0;

        for(j = 0; j < frames; j++)
            if(frame[j] == pages[i])
                hit = 1;

        if(!hit) {   // Page Fault
            frame[f] = pages[i];
            f = (f + 1) % frames;
            faults++;
        } else {
            hits++;
        }

        printf("%d\t", pages[i]);
        for(j = 0; j < frames; j++)
            printf("%s ", frame[j] == -1 ? "-" : (char [3]){frame[j]+'0',0});

        printf("\t\t%s", hit ? "Hit" : "Page Fault");
        if(hit) printf(" (%d)", pages[i]);
        printf("\n");
    }

    printf("\nTotal Page Faults: %d", faults);
    printf("\nTotal Page Hits: %d\n", hits);

    return 0;
}


/* ============================================================================
   ✅ LINE-BY-LINE EXPLANATION — FIFO PAGE REPLACEMENT PROGRAM
   ============================================================================

1.  frames → number of physical memory slots
2.  pages[] → page reference string entered by user
3.  frame[] → currently loaded pages in memory
4.  f → pointer used for FIFO replacement (circular index)
5.  faults, hits → counters

------------------------- INPUT SECTION ---------------------------------------

6.  scanf("%d", &frames);       → Read number of frames
7.  scanf("%d", &n);            → Read number of page references
8.  pages[i] inside loop        → Take each page number

------------------------- INITIALIZATION --------------------------------------

9.  for(i = 0; i < frames; i++)
        frame[i] = -1;          → -1 means empty frame

10. Printing table headings:
        Page   Frames   Status

------------------------- MAIN PAGE REPLACEMENT LOOP --------------------------

11. for(i = 0; i < n; i++)
        - Loop through each page reference

12. hit = 0 initially (not found)

13. Check if page already exists in frame[]
        if(frame[j] == pages[i]) → hit = 1

14. If NOT found → Page Fault
        frame[f] = pages[i];    → Replace old page using FIFO slot
        f = (f + 1) % frames;    → Move pointer in circular way
        faults++;

15. Else → Page Hit
        hits++;

------------------------- OUTPUT EACH STEP ------------------------------------

16. printf("%d\t", pages[i]);
        - Prints current page request

17. printf("%s ", frame[j] == -1 ? "-" : (char [3]){frame[j]+'0',0});
        - If frame is empty print "-", else print integer as char

18. printf("\t\t%s", hit ? "Hit" : "Page Fault");
        - Print status accordingly

-------------------------- FINAL OUTPUT ---------------------------------------

19. Print total page faults and hits

-------------------------- FIFO ALGORITHM SUMMARY -----------------------------

✔ FIFO = First In First Out  
✔ Oldest loaded page gets replaced first  
✔ Uses pointer f to track replacement index  
✔ Very easy but not optimal (can perform poorly)




 outputt
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ gcc pg_fcfs.c
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ ./a.out
Enter number of frames: 3
Enter number of pages: 10
Enter page reference string:
1 2 3 4 5 5 6 7 8 9

Page	Frames		Status
----	------		------
1	1 - - 		Page Fault
2	1 2 - 		Page Fault
3	1 2 3 		Page Fault
4	4 2 3 		Page Fault
5	4 5 3 		Page Fault
5	4 5 3 		Hit (5)
6	4 5 6 		Page Fault
7	7 5 6 		Page Fault
8	7 8 6 		Page Fault
9	7 8 9 		Page Fault

Total Page Faults: 9
Total Page Hits: 1
*/ 

