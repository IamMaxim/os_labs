#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <stdlib.h>


void handle_SIGINT(int sig) {
    printf("Gracefully shutting down because of SIGINT\n");
    exit(0);
}

int main() {
    signal(SIGINT, handle_SIGINT);

    printf("Press Ctrl+C to terminate me!\n");
    while (1) {
        sleep(1000);
    }

    return 0;
}