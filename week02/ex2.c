#include <stdio.h>
#include <string.h>

int main() {
    printf("Enter a string to reverse:\n> ");

    char input[1024];
    scanf("%s", input);

    for (int i = strlen(input); i >= 0; i--) {
        printf("%c", input[i]);
    }
    printf("\n");

    return 0;
}
