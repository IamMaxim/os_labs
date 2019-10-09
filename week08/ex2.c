#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 10; i++) {
        void *newMem = malloc(10 * 1024 * 1024);
        memset(newMem, 0, 10 * 1024 * 1024);
        sleep(1);
    }

    return 0;
}
