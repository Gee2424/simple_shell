#include "shell.h"

/* Declare environ as an external variable to access the environment strings */
extern char **environ;

/**
* simple_shell - A simple shell that can execute commands with arguments
*/
void simple_shell(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
/* Use ARG_MAX for maximum number of arguments */
char *argv[ARG_MAX]; 
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

/* Parse the input line into command and arguments */
parse_input(line, argv);

/* Check if no command was entered (e.g., empty line) */
if (argv[0] == NULL) {
/* Skip the rest of the loop and display the prompt again */
continue;
}

/* Check if the executable exists and is accessible */
if (access(argv[0], X_OK) != 0) {
/* Use the shell's name in the error message */
fprintf(stderr, "./shell: %s: No such file or directory\n", argv[0]);
/* Skip trying to execute and display the prompt again */
continue;
}

child_pid = fork();
if (child_pid == 0) {
/* Child process */
if (execve(argv[0], argv, environ) == -1) {
/* Use the shell's name in the error message from child process */
fprintf(stderr, "./shell: %s: No such file or directory\n", argv[0]);
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


