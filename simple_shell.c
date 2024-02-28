#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
* execute_command - For command Execution.
* @buffer: A buffer for the command.
* Return: Returns nothing Nothing.
*/
void execute_command(char *buffer)
{
char *args[3];
pid_t child_pid;
int status;

/* Tokenize the input */
args[0] = strtok(buffer, " ");
args[1] = NULL;

/* Create a child process */
child_pid = fork();
if (child_pid == -1)
{
perror("Error");
free(buffer);
exit(EXIT_FAILURE);
}
if (child_pid == 0)
{
/* Child process */
if (execve(args[0], args, NULL) == -1)
{
perror("simple_shell");
exit(EXIT_FAILURE);
}
}
else
{
/* Parent process */
wait(&status);
}
}

/**
* main - Entry point for the simple shell.
* Return: 0 on success, 1 on failure.
*/
int main(void)
{
char *buffer = NULL;
size_t bufsize = BUFFER_SIZE;
ssize_t characters;

while (1)
{
printf("#cisfun$ ");
characters = getline(&buffer, &bufsize, stdin);

if (characters == -1)
{
if (feof(stdin))
{
free(buffer);
return (EXIT_SUCCESS);
}
else
{
perror("simple_shell");
free(buffer);
return (EXIT_FAILURE);
}
}

/* Remove newline character */
buffer[characters - 1] = '\0';

execute_command(buffer);
}

/* Free allocated memory */
free(buffer);

return (0);
}


