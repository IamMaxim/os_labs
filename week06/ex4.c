#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <stdlib.h>

void handle_SIGINT(int sig) {
    printf("Gracefully shutting down because of SIGINT\n");
    exit(0);
}

void handle_SIGSTOP(int sig) {
    printf("Gracefully shutting down because of SIGSTOP\n");
    exit(0);
}

void handle_SIGUSR1(int sig) {
    printf("Gracefully shutting down because of SIGUSR1\n");
    exit(0);
}


int main() {
    signal(SIGINT, handle_SIGINT);

    printf("Press Ctrl+C to terminate me!\n"
           "Or send some some interesting signals: SIGSTOP or SIGUSR1!\n");
    while (1) {
        sleep(1000);
    }

    return 0;
}