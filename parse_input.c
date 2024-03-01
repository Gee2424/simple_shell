#include "shell.h"

/**
* parse_input - Parses the input string into a program and arguments
* @line: The input string to parse
* @argv: The argument vector to populate
*/
void parse_input(char *line, char **argv)
{
int i = 0;
argv[i] = strtok(line, " \n");

while (argv[i] != NULL && i < ARG_MAX - 1)
{
argv[++i] = strtok(NULL, " \n");
}
}

