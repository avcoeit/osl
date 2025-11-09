#include <stdio.h>
#include <unistd.h>

void sortAsc(int a[], int n) {
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(a[i] > a[j]) { int t=a[i]; a[i]=a[j]; a[j]=t; }

    printf("\n[Child | PID %d] Sorted in Ascending Order: ", getpid());
    for(int i=0;i<n;i++) printf("%d ", a[i]);
    printf("\n");
}

void sortDesc(int a[], int n) {
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(a[i] < a[j]) { int t=a[i]; a[i]=a[j]; a[j]=t; }

    printf("\n[Parent | PID %d] Sorted in Descending Order: ", getpid());
    for(int i=0;i<n;i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int n, a[50];
    printf("Enter size: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for(int i=0;i<n;i++) scanf("%d", &a[i]);

    pid_t pid = fork();

    if(pid == 0) {          // Child
        sortAsc(a, n);
    } else {                // Parent
        sortDesc(a, n);
    }
    return 0;
}

/* output
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ gcc fork2a.c
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ ./a.out
Enter size: 5
Enter elements: 4 5 2 1 9

[Parent | PID 7914] Sorted in Descending Order: 9 5 4 2 1 

[Child | PID 7917] Sorted in Ascending Order: 1 2 4 5 9 
*/

