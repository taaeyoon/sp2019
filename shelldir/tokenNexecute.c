#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*for execute builtin function*/

char *builtin_str[];
int (*builtin_func[]) (char **);
int num_builtins();

/*define buffersize and delimiter for tokenizing input line*/

#define LINE_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/*execute command*/

int execute(char **args) {
    int i;

    /*when there's no input*/

    if (args[0]  == NULL) {
        return 1;
    }

    /*execute builtin function if command is builtin function's*/

    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
	    return (*builtin_func[i])(args);
	}
    }

    /*produce process for command*/

    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0],args) == -1) {
	    perror("error");
	}       	
	exit(1);
    } else if (pid < 0) {
        perror("error");
    } else {
        do {
	    wpid = waitpid(pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/*return input line when user hit enter key*/

char *read_line(void) {
    int bufsize = LINE_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int a;

    while(1) {
        a = getchar();
        
        /*check text if it is end of the line or not*/

	if (a == EOF || a == '\n') {

	    /*changing end of the line to end of the string and return it*/

	    buffer[position] = '\0';
	    return buffer;
	} else {
	    buffer[position] = a;
	}
        position++;

        /*when input is bigger than defined buffersize*/

	if (position >= bufsize) {
	    bufsize += LINE_BUFSIZE;
	    buffer = realloc(buffer, bufsize);
	    if (!buffer) {
	        fprintf(stderr, "allocation error\n");
		exit(1);
	    }
	}
    }
}

/*split input line to tokens*/

char **split_line(char *line) {
    int bufsize = TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    /*find nearest index where delimters appeared from start on the input line*/

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
	position++;

        /*when the number of splitted stuffs from input line is bigger than buffersize*/

	if (position >= bufsize) {
	    bufsize += TOK_BUFSIZE;
	    tokens = realloc(tokens, bufsize * sizeof(char*));
	    if (!tokens) {
	        fprintf(stderr, "allocation error\n");
		exit(1);
	    }
	}

        /*find nearest index where delimiters appeared from the recent index*/

	token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
