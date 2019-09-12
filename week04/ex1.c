#include <stdio.h>
#include <sys/types.h>


int main() {
    // Fork returns 0 to the child and positive int to the 
    // parent (the PID of child).
    // Negative values are thrown on unsuccessful creation of a process.
    if (fork()) {
        printf("Hello from parent [PID - %d]\n", getpid());
    } else {
        printf("Hello from child [PID - %d]\n", getpid());
    }

    return 0;
}



