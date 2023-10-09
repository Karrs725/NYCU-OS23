#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void osh_loop();
char *osh_read_line();
char **osh_tokenize(char *line);
int token_recognize(char **tokens);

int main() {

    osh_loop();

    return 0;
}

void osh_loop(){
    char *line;
    char **tokens;
    int end_flag = 0;
    
    do{
        line = osh_read_line();
        tokens = osh_tokenize(line);
        printf("%s\n", tokens[0]);
        end_flag = token_recognize(tokens);
    } while (!end_flag);

    free(line);
    free(tokens);

}

char *osh_read_line(){
    char *l = (char *)malloc(sizeof(char) * 20);
    printf("osh> ");
    scanf("%[^\n]%*c", l);
    return l;
}

char **osh_tokenize(char *line){
    char **ts = (char **)malloc(sizeof(char *) * 20);
    char *t;
    int i = 0;
    t = strtok(line, " ");
    while(t != NULL){
        ts[i++] = t;
        t = strtok(NULL, " ");
    }
    ts[i] = NULL;
    return ts;
}

int token_recognize(char **tokens){
    if (tokens[0] == NULL){
        return 0;
    }


    return 1;
    
}