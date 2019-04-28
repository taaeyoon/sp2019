#include <unistd.h>
#include <stdio.h>

int new_cd(char **args);
int new_help(char **args);
int new_exit(char **args);

/*array for comparing whether input is for builtin function or not*/

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

/*function pointer array for builtin functions*/

int (*builtin_func[]) (char **) = {
    &new_cd,
    &new_help,
    &new_exit
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/*builtin functions*/

int new_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "no argument\n");
    } else {
        if (chdir(args[1]) != 0) {
	    perror("error");
	}
    }

    return 1;
}

int new_help(char **args) {
    int i;
    printf("builtin functions : \n");

    for (i = 0; i < num_builtins(); i++) {
        printf("    %s\n", builtin_str[i]);
    }

    printf("for information of other functions, use man command.\n");
}

int new_exit(char **args) {

    printf("program closed\n");

    return 0;
}
