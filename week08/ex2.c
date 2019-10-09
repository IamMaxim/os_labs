#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
    vmstat/vm_stat prints 0 in is and so (swapins/swapouts), because there
    is plenty of physical memory available and swapping is not needed.
*/

int main() {
    for (int i = 0; i < 10; i++) {
        void *newMem = malloc(10 * 1024 * 1024);
        memset(newMem, 0, 10 * 1024 * 1024);
        sleep(1);
    }

    return 0;
}
