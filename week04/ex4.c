#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>


int is_empty(char *str) {
    while (*(str++) == ' ') {}
    return *(str - 1) == '\0';
}


/*  Runs the passed command with arguments.
 *  If run_in_bg is true, this function exits immediately after call.
 *  If not, it waits for child process to complete and then returns
 *  its return code.
 *
 *  Returns 0 if process is executed in background, return code
 *  of the child otherwise.
 * */
int run(char **argv, int run_in_bg) {
    pid_t pid;
    if ((pid = fork()) == 0) {
        printf("Gonna execute %s\n", argv[0]);
        execve(argv[0], argv, 0);
        perror("Spawning new process failed");
    } else {
        // Wait for the child process to complete execution
        int status;
        if (!run_in_bg) {
            waitpid(pid, &status, 0);
            return status;
        } else {
            return 0;
        }
    }
}

void strip_last_newline(char *str) {
    int len = strlen(str);
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int main() {
    int result_code = 0;

    while (1) {
        printf("[%d] > ", result_code);
        char input[1024];
        fgets(&input, 1024, stdin);
        strip_last_newline(input);

        printf("Passed \"%s\"\n", input);

        // Skip empty queries
        if (is_empty(input)) {
            continue;
        }

        // Exit if appropriate command is passed
        if (strcmp(input, "exit") == 0) {
            printf ("Exitting...\n");
            return 0;
        }

        char *token = strtok(input, " ");
        char *arr[128];
        int counter = 0;
        while (token != 0) {
            arr[counter++] = token;
            token = strtok(NULL, " ");
        }
        arr[counter] = 0;

        result_code = run(arr, 0);
    }

    return 0;
}



