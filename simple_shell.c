#include "shell.h"

/* Declare environ as an external variable to access the environment strings */
extern char **environ;

/**
* simple_shell - A simple shell that can
* execute commands with arguments,
* and handles the PATH environment variable to find commands.
*/
void simple_shell(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
/* Use ARG_MAX for maximum number of arguments */
char *argv[ARG_MAX];
/* Moved declaration to the top */
char *command_path = NULL;
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

if (argv[0][0] != '/') {
/* Command does not start with '/', so search PATH */
command_path = search_path(argv[0]);
/* Command not found in PATH */
if (command_path == NULL) {
fprintf(stderr, "./shell: %s: Command not found\n", argv[0]);
/* Skip trying to execute and display the prompt again */
continue;
}

/* Update command to full path */
argv[0] = command_path;
/* Check if the given absolute path is accessible */
} else if (access(argv[0], X_OK) != 0) {
fprintf(stderr, "./shell: %s: No such file or directory\n", argv[0]);
/* Skip trying to execute and display the prompt again */
continue;
}

child_pid = fork();
/* Child process */
if (child_pid == 0) {
if (execve(argv[0], argv, environ) == -1) {
/* Use the shell's name in the error message from child process */
fprintf(stderr, "./shell: %s: No such file or directory\n", argv[0]);
/* Exit child process if execve fails */
exit(EXIT_FAILURE);
}
/* Parent process */
} else if (child_pid > 0) {
waitpid(child_pid, &status, 0);
/* Free allocated memory for command path if not NULL */
if (command_path != NULL) {
free(command_path);
command_path = NULL; 
/* Reset pointer after free */
}
/* Fork failed */
} else {
perror("Error");
}
}
/* Free allocated memory for line */
free(line);
}

