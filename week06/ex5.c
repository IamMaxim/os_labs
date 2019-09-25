#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <signal.h>

int main() {
    int child_pid;

    if (child_pid = fork()) {
        // Parent
        sleep(10);
        kill(child_pid, SIGTERM);
    } else {
        // Child
        while (1) {
            printf("I'm alive!\n");
            sleep(1);
        }
    }

    return 0;
}