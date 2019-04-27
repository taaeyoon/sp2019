#include<stdio.h>
#include<stdlib.h> 

char *read_line(void);
char **split_line(char *line);
int execute(char **args);

void loop(void) {
    char *line;
    char **args;
    int status;

    printf("this is kimtaeyoon shell.\n");

    do {
        printf("kimtaeyoon > ");
	line = read_line();
	args = split_line(line);
	status = execute(args);

	free(line);
	free(args);

    } while (status);
}
