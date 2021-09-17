#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void Split(char* string, char* delimiters, struct strings* tokens, int* tokensCount) {
    long unsigned slen = strlen(string);
    long unsigned len, sumlen = 0;
    char *temp = calloc(slen, sizeof(char));
    for( ; ;) {
        temp = strtok(&string[sumlen], delimiters);
        if(temp == NULL)
            break;
        len = strlen(temp);
        tokens[*tokensCount].s = calloc(len, sizeof(char));
        tokens[*tokensCount].s = temp;
        *tokensCount = *tokensCount + 1;
        sumlen = sumlen + len + 1;
    }
    free(temp);
    
}
