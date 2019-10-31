#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

char *data = "hello";

int main() {
    char buf[BUFSIZE];
    setvbuf(stdout, buf, _IOLBF, BUFSIZE);
    
    for (int i = 0; i < strlen(data); i++) {
        printf("%c", data[i]);
        sleep(1);
    }
    printf("\n");


    return 0;
}
