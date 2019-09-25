#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <signal.h>

int parent_pid;

void handler_SIGCONT(int sig) {
    printf("Received SIGCONT\n");
    exit(0);
}


int main() {
    // Save the PID of the parent.
    parent_pid = getpid();

    // Create pipes for the first child <-> parent communication
    int FDs1[2];
    if (pipe(FDs1)) {
        printf("Failed to create pipe\n");
        exit(1);
    }
    
    int child1_pid;
    int child2_pid;
    if (child1_pid = fork()) {
        // Parent
       
        if (child2_pid = fork()) {
            // Parent
            printf("I'm the parent\n");

            write(FDs1[1], &child2_pid, sizeof(int));

            // Wait for the second child to die
            int status;
            waitpid(child2_pid, &status, 0);
            printf("The second child is dead; quitting parent\n");
        } else {
            // Child 2
            printf("I'm child number two\n");

            signal(SIGCONT, handler_SIGCONT);

            while (1) {
                sleep(1);
                printf("I'm running\n");
            }
        }
    } else {
        // Child 1
        printf("I'm child number one\n");
        
        // IDK why we should send the PID og the first child to the second
        // here, since it is already in the right variable, but let it be so.
        int pid;
        read(FDs1[0], &pid, sizeof(int));
        printf("The pid of the first fork is %i\n", pid);
        sleep(3);
        printf("Gonna stop the second child\n");
        kill(pid, SIGSTOP);
        sleep(1);
        printf("Gonna wake up the second child\n");
        kill(pid, SIGCONT);
        printf("Done.\n");
    }

    return 0;
}
