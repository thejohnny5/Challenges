#include "stdlib.h"
#include "stdbool.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"

#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void){
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    // Initialize buffer of lsh_rl_buffsize
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;
    
    // Cause failure if couldn't allocate enough space
    if (!buffer){
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    // parse line
    while (true){
        // Read a character
        c = getchar();

        // If we hit EOF, replace with null char and return
        if (c==EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
        
        // if we exceed buffer, reallocate
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer){
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens){
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            // reallocate space when exceeding bufsize
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens){
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL; // end array with null pointer
    return tokens;
}

int lsh_launch(char **args){
    pid_t pid, wpid;
    int status;
    pid = fork();
    if (pid==0){
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid<0){
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

char *lsh_read_line_n(void){
    char *line = NULL;
    size_t bufsize = 0; // getline allocates buffer for us

    if (getline(&line, &bufsize, stdin)==-1){
        if (feof(stdin)){
            exit(EXIT_SUCCESS); // Received EOF
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

// Built in shell commands
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

// Build in commands following by corresponding functions
char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins(){
    return sizeof(builtin_str) / sizeof(char*);
}

// Built in function implementations
int lsh_cd(char **args){
    if (args[1] == NULL){
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args){
    int i;
    printf("LSH\n");
    printf("Type program names and argument, and hit ender.\n");
    printf("The following are built in :\n");
    for (i=0; i<lsh_num_builtins(); i++){
        printf("  %s\n", builtin_str[i]);
    }
    printf("Use the man command for information on other programs.\n");
    return 1;
}

int lsh_exit(char **args){return 0;}

int lsh_execute(char **args){
    int i;
    if (args[0] == NULL){
        // empty command entered
        return 1;
    }
    for (i=0; i<lsh_num_builtins(); i++){
        if (strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    return lsh_launch(args);
}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}


int main(int argc, char **argv){
    lsh_loop();    
    return EXIT_SUCCESS;
}
