#include "shell.h"

extern char **environ;

/**
* execute_command - Executes a command.
* @cmd: The command to execute.
*
* Return: Nothing.
*/
void execute_command(char *cmd) {
pid_t pid;
int status;
char *argv[2];

pid = fork();
if (pid == -1) {
perror("fork");
} else if (pid == 0) {
argv[0] = cmd;
argv[1] = NULL;
if (execve(cmd, argv, environ) == -1) {
perror(cmd);
exit(EXIT_FAILURE);
}
} else {
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
}

/**
* main - Entry point for the simple shell.
*
* Return: Always returns 0.
*/
int main(void) {
char *line = NULL;
size_t len = 0;
ssize_t read;

while (1) {
printf("$ ");
read = getline(&line, &len, stdin);
if (read == -1) {
if (feof(stdin)) {
exit(EXIT_SUCCESS);
} else {
perror("readline");
exit(EXIT_FAILURE);
}
}

/* Remove the newline character at the end of the line */
if (line[read - 1] == '\n') {
line[read - 1] = '\0';
}

/* Directly execute the command without parsing for arguments */
execute_command(line);
free(line);
line = NULL;
}

return EXIT_SUCCESS;
}

