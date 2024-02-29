#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "
#define ERROR_MESSAGE "./shell: No such file or directory\n"

void execute_command(const char *command) {
pid_t pid = fork();
if (pid == 0) { 
execlp(command, command, NULL);
write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
exit(EXIT_FAILURE);
} else if (pid < 0) { 
perror("Error forking");
exit(EXIT_FAILURE);
} else { 
wait(NULL);
}
}

int main(void) {
char *line = NULL;
size_t len = 0;
ssize_t read;
char *token;

while (1) {
printf(PROMPT);
fflush(stdout);

read = getline(&line, &len, stdin);
if (read == -1) {
printf("\n");
break;
}

if (line[read - 1] == '\n') {
line[read - 1] = '\0';
}

if (strlen(line) == 0) {
continue;
}

token = strtok(line, " ");
if (token != NULL && strtok(NULL, " ") == NULL) {
execute_command(token);
} else {
write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
}
}

free(line);
return 0;
}

