#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int is_empty(char *str) {
    while (*(str++) == ' ') {}
    return *(str - 1) == '\0';
}

int main() {
    int return_code = 0;

    while (1) {
        printf("[%d] > ", return_code);
        char input[1024];
        fgets(&input, 1024, stdin);
        scanf("%s", &input);

        if (is_empty(input)) {
            continue;
        }

        if (strcmp(input, "exit") == 0) {
            return 0;
        }

        return_code = system(input);
    }

    return 0;
}



