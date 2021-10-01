#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

void Split(char* input_string, char* delimiters, char** tokens, int* tokensCount);

void execution_of_cmnd(const char* name_of_cmnd);

int main() {
    int N = 100;
    int index = 0;
    long int r_status = 0;
    int tokens = 0;
    int num_of_cmnds = 0;
    char delimiter = '  '; //разделитель в файле
    char** words = calloc(N, sizeof(char));
    char* buffer = calloc(N, sizeof(char));
    
    index = open("file",O_RDONLY);
    
    while ((r_status = read(index, buffer, N)) != 0) {
                write(1, buffer, r_status);
        }
    
    Split(buffer, &delimiter, words, &tokens);
    
    
    num_of_cmnds = atoi(words[0]);
    for(int i = 1; i <= num_of_cmnds; ++i) {
        sleep( atoi(words[i + num_of_cmnds]) );
        execution_of_cmnd(words[i]);
    }
        
    close(index);
    free(words);
    free(buffer);
    return 0;
}

void execution_of_cmnd(const char* name_of_cmnd) {
    unsigned timeout = 5;
    long int start_time = 0;
    long int ttime;
    int fd[2];
    pipe(fd);
    int p = fork();
    if (p == 0) {
        close(fd[0]);
        start_time = time(NULL);
        write(fd[1], &start_time, 1);
        execlp("name_of_cmnd",NULL);
    }
    if (p == 1) {
        close(fd[1]);
        read(fd[0], &start_time, 1);
        ttime = time(NULL);
        while(ttime - start_time < 5) {
            ttime = time(NULL);
        }
        kill(0, 1);
    }
    
}

void Split(char* input_string, char* delimiters, char** tokens, int* tokensCount) {
    long unsigned slen = strlen(input_string);
    long unsigned len = 0;
    char *temp = (char*) calloc(slen, sizeof(char));
    
    temp = strtok(input_string, delimiters);
    len = strlen(temp);
    
    tokens[*tokensCount] = temp;
    (*tokensCount)++;
    for( ; ;) {
        temp = strtok(NULL, delimiters);
        if(temp == NULL)
            break;
        tokens[*tokensCount] = temp;
        (*tokensCount)++;
    }
    free(temp);
}

