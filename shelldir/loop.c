#include<stdio.h>
#include<stdlib.h> 

/*for read and execute input line*/

char *read_line(void);
char **split_line(char *line);
int execute(char **args);

void loop(void) {
    char *line;
    char **args;
    int status;

    printf("this is kimtaeyoon shell.\n");
    printf("for checking builtin functions, enter \"help\".\n");

    /*repeat getting input and execute*/

    do {
        printf("kimtaeyoon > ");
	line = read_line();
	args = split_line(line);
	status = execute(args);

	free(line);
	free(args);

    } while (status);
}
