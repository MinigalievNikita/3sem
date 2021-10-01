
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
    int r_status = 0;
    int tokens = 0;
    int num_of_cmnds = 0;
    char a = '  ';
    char** words = calloc(N, sizeof(char));
    
    index = open("file",O_RDONLY);
    
    char* buffer = calloc(N, sizeof(char));
    while ((r_status = read(index, buffer, N)) != 0) {
                write(1, buffer, r_status);
        }
    
    Split(buffer, &a, words, &tokens);
    
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
    long int ttime0 = 0, ttime = 6;
    int p = fork();
    if (p == 0) {
        execlp("name_of_cmnd",NULL);
    }
    if (p == 1) {
        ttime0 = time(NULL);
        ttime = ttime0;
        while(ttime - ttime0 < timeout) {
            ttime = time(NULL);
        }
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
