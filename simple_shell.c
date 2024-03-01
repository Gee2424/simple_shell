#include "shell.h"

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
printf("$ ");
nread = getline(&line, &len, stdin);
if (nread == -1)
break;
/* Remove newline character*/
line[strcspn(line, "\n")] = 0; 
argv[0] = line;
argv[1] = NULL;

child_pid = fork();
if (child_pid == 0) {
/* Child process */
if (execve(line, argv, NULL) == -1) {
perror("./shell");
}
/* Exit child process if execve fails */
exit(EXIT_FAILURE); 
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


