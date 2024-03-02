#include "shell.h"

/**
* search_path - Searches for a command 
* in the directories specified by the 
* PATH environment variable.
* @cmd: The command to search for.
* Return: The full path to the command if found, 
* or NULL if not found.
*/
char *search_path(char *cmd) {
char *PATH = getenv("PATH");
char *p = strtok(PATH, ":");
/* Allocate memory for the full path */
char *full_path = malloc(1024); 

while (p != NULL) {
sprintf(full_path, "%s/%s", p, cmd);
if (access(full_path, X_OK) == 0) {
/* Command found */
return full_path; 
}
p = strtok(NULL, ":");
}
/* Free memory if command not found */
free(full_path); 
return NULL;
}

