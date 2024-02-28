#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * execute_command - Executes a command in a child process.
 * @buffer: The command to execute.
 * 
 * This function forks a new process and executes the command
 * provided in the buffer. If the command execution fails, it
 * prints an error message.
 */
void execute_command(char *buffer)
{
    char *args[2]; /* Array to hold the command and the NULL terminator*/
    pid_t child_pid;
    int status;

    args[0] = buffer; /*The command to execute*/
    args[1] = NULL; /*NULL terminator for the execve function*/

    child_pid = fork(); /*Fork a child process*/
    if (child_pid == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0)
    {
        /*Child process attempts to execute the command*/
        if (execve(args[0], args, NULL) == -1)
        {
            perror("simple_shell");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /*Parent process waits for the child to complete*/
        wait(&status);
    }
}

/**
 * main - Entry point for the simple shell.
 * 
 * This function continuously displays a prompt, waits for user input,
 * and executes the entered command. It handles EOF (Ctrl+D) and ensures
 * that memory is properly managed by freeing allocated buffers.
 * 
 * Return: EXIT_SUCCESS on normal exit, EXIT_FAILURE on error.
 */
int main(void)
{
    char *buffer = NULL;
    size_t bufsize = BUFFER_SIZE;
    ssize_t characters;

    while (1)
    {
        printf("#cisfun$ "); /*Display the prompt*/
        characters = getline(&buffer, &bufsize, stdin); /*Read input*/

        if (characters == -1)
        {
            if (feof(stdin)) /*Handle EOF*/
            {
                free(buffer);
                printf("\n"); /*Print a new line for a clean exit*/
                return (EXIT_SUCCESS);
            }
            else
            {
                perror("simple_shell");
                free(buffer);
                return (EXIT_FAILURE);
            }
        }

        buffer[characters - 1] = '\0'; /*Replace newline with null terminator*/

        execute_command(buffer); /*Execute the command*/
    }

    free(buffer); /* Free allocated memory (just in case)*/

    return (0);
}

