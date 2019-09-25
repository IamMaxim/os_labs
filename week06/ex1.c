#include <stdio.h>
#include <unistd.h>


int main() {
    char str1[128] = "I'm the string you are going to receive";
    char str2[128];

    int descriptors[2];
    if (pipe(descriptors) == 0) {
        printf("Pipe successfully created: %d for read end, %d for write end\n",
               descriptors[0],
               descriptors[1]);

        // Write string to the pipe
        write(descriptors[1], str1, 128);

        // Read string from the pipe
        read(descriptors[0], str2, 128);

        // Print the result
        printf("Read string: %s\n", str2);
    }

    return 0;
}