// IPC using PIPE (unidirectional: parent sends, child receives)
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];           // fd[0] = read end, fd[1] = write end
    pipe(fd);            // Create pipe
    int pid = fork();    // Create child process

    if (pid > 0) {       // Parent Process
        close(fd[0]);    // Close read end
        char msg[] = "Hello from Parent!";
        write(fd[1], msg, sizeof(msg));
        close(fd[1]);
    } 
    else {               // Child Process
        close(fd[1]);    // Close write end
        char buffer[50];
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    }

    return 0;
}
/* output
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ gcc pipe.c
sagar@sagar-Lenovo-V15-IIL:~/Pictures/osl$ ./a.out
Child received: Hello from Parent!
*/
