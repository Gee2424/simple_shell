#include "shell.h"

#define MAX_CMD_LEN 1024
#define MAX_PATH_LEN 1024


extern char **environ;

/**
* execute_command - Executes a command.
* @cmd: The command to execute.
*
* This function forks a new process and executes the given command.
* If the command is not an absolute path, it prepends "/bin/" to it.
* If the command cannot be executed, it prints an error message.
*/
void execute_command(char *cmd) {
pid_t pid;
int status;
char *argv[2];
char path[MAX_PATH_LEN];

if (cmd[0] != '/') {
snprintf(path, MAX_PATH_LEN, "/bin/%s", cmd);
cmd = path;
}

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
* This function displays a prompt, reads a command from the user,
* and executes it. It handles the "end of file" condition (Ctrl+D)
* by exiting gracefully.
*
* Return: Always returns 0.
*/
int main(void) {
char *line = NULL;
size_t len = 0;
ssize_t read;

while (1) {
printf("#cisfun$ ");
fflush(stdout);

read = getline(&line, &len, stdin);
if (read == -1) {
if (feof(stdin)) {
printf("\n");
exit(EXIT_SUCCESS);
} else {
perror("readline");
exit(EXIT_FAILURE);
}
}

line[strcspn(line, "\n")] = '\0';

if (strcmp(line, "exit") == 0) {
printf("./shell: No such file or directory\n");
continue;
}

execute_command(line);
}

free(line);
return EXIT_SUCCESS;
}


