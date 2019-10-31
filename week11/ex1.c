#include <stdio.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define SIZE 1024


int main() {
    // Allocate some space on the heap to map the file here
    // void *someSpace = malloc(SIZE);
    int fd = open("ex1.txt", O_RDWR);
    if (fd == -1) {
        printf("Error opening file\n");
        return -1;
    }
    printf("Opened file %i\n", fd);

    // Map the file to the virtual address space
    void *mem = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("Mapped file to %p\n", mem);
    
    printf("%s\n", mem);

    char *newData = "This is a nice day\0";
    memcpy(mem, newData, strlen(newData) + 1);

    printf("%s\n", mem);

    close(fd);
    return 0;
}


