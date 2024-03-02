#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define ARG_MAX 64 

extern char **environ;

void simple_shell(void);
void parse_input(char *line, char **argv);
char *search_path(char *cmd);

#endif /* SHELL_H */


