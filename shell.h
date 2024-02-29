#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Function Prototypes */
void execute_command(char *cmd);
void type_prompt(void);
char *read_command(void);

#endif /* SHELL_H */


