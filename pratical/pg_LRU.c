#include <stdio.h>

int main() {
    int frames, pages[100], frame[10], used[10], n, i, j, k;
    int faults = 0, hits = 0, time = 0;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    for(i = 0; i < frames; i++)
        frame[i] = -1, used[i] = -1;

    printf("\nPage\tFrames\t\tStatus\n");
    printf("----\t------\t\t------\n");

    for(i = 0; i < n; i++) {
        int page = pages[i], hit = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == page) {
                hit = 1;
                used[j] = time++;
                hits++;
            }
        }

        if(!hit) {
            int pos = 0;
            for(j = 0; j < frames; j++)
                if(frame[j] == -1 || used[j] < used[pos])
                    pos = j;

            frame[pos] = page;
            used[pos] = time++;
            faults++;
        }

        printf("%d\t", page);
        for(k = 0; k < frames; k++)
            printf("%s ", frame[k] == -1 ? "-" : (char [3]){frame[k]+'0',0});

        if(hit)
            printf("\t\tHit (%d)\n", page);
        else
            printf("\t\tPage Fault\n");
    }

    printf("\nTotal Page Faults: %d", faults);
    printf("\nTotal Page Hits: %d\n", hits);

    return 0;
}

/* output
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ gcc pg_LRU.c
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ ./a.out
Enter number of frames: 3
Enter number of pages: 10
Enter page reference string:
1 2 3 3 4 5 2 1 9 8

Page	Frames		Status
----	------		------
1	- - 1 		Page Fault
2	- 2 1 		Page Fault
3	3 2 1 		Page Fault
3	3 2 1 		Hit (3)
4	3 2 4 		Page Fault
5	3 5 4 		Page Fault
2	2 5 4 		Page Fault
1	2 5 1 		Page Fault
9	2 9 1 		Page Fault
8	8 9 1 		Page Fault

Total Page Faults: 9
Total Page Hits: 1
*/

