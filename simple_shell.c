#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/**
* execute_command - Tries to execute a given command
* @cmd: The command to execute
*/
void execute_command(char *cmd) {
pid_t pid;
int status;
char *argv[3]; 

argv[0] = cmd;
argv[1] = NULL; 

pid = fork();
if (pid == -1) {
perror("Error: fork failed");
return;
}
if (pid == 0) {
/* Child process*/
if (execve(cmd, argv, environ) == -1) {
fprintf(stderr, "./shell: %s: No such file or directory\n", cmd);
exit(EXIT_FAILURE);
}
} else {
/*Parent process*/
waitpid(pid, &status, 0);
}
}


/**
* main - Entry point for the simple shell
* Return: Always 0 (Success)
*/
int main(void) {
char *line = NULL;
size_t bufsize = 0;
ssize_t nread;

while (1) {
printf("#cisfun$ ");
fflush(stdout);

nread = getline(&line, &bufsize, stdin);
if (nread == -1) {
if (feof(stdin)) { 
printf("\n");
free(line);
exit(EXIT_SUCCESS);
} else { 
perror("getline");
continue;
}
}

/* Remove the newline at the end*/
line[strcspn(line, "\n")] = 0;

if (strlen(line) == 0) { 
continue;
}

execute_command(line);
}

free(line); 
return 0;
}
