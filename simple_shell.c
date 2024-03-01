#include "shell.h"

/* Declare environ as an external variable to access the environment strings */
extern char **environ;

/**
 * simple_shell - A simple shell that can execute commands
 */
void simple_shell(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[2];
    pid_t child_pid;
    int status;

    while (1) {
        printf("#cisfun$ ");
        /* Ensure the prompt is displayed immediately */
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1) {
            /* Print a new line for EOF (Ctrl+D) condition */
            printf("\n");
            /* Exit the loop on EOF */
            break;
        }

        /* Remove newline character */
        line[strcspn(line, "\n")] = 0;
        /* Check if the command is empty (only enter was pressed) */
        if (strcmp(line, "") == 0) {
            /* Skip the rest of the loop and display prompt again */
            continue;
        }

        argv[0] = line;
        argv[1] = NULL;

        /* Check if the executable exists and is accessible */
        if (access(line, X_OK) != 0) {
            /* Use the shell's name in the error message */
            fprintf(stderr, "./shell: %s: No such file or directory\n", line);
            /* Skip trying to execute and display the prompt again */
            continue;
        }

        child_pid = fork();
        if (child_pid == 0) {
            /* Child process */
            if (execve(line, argv, environ) == -1) {
                /* Use the shell's name in the error message from child process */
                fprintf(stderr, "./shell: %s: No such file or directory\n", line);
                /* Exit child process if execve fails */
                exit(EXIT_FAILURE);
            }
        } else if (child_pid > 0) {
            /* Parent process */
            waitpid(child_pid, &status, 0);
        } else {
            /* Fork failed */
            perror("Error");
        }
    }
    free(line);
}


