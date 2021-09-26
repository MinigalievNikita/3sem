#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <split.h>

void Split(char* input_string, char* delimiters, struct String* tokens, int* tokensCount) {
    long unsigned slen = strlen(input_string);
    long unsigned len;
    char *temp = calloc(slen, sizeof(char));
    temp = strtok(input_string, delimiters);
    len = strlen(temp);
    tokens[*tokensCount].s = calloc(len, sizeof(char));
    tokens[*tokensCount].s = temp;
    // можно чуть лаконичнее написать: (*tokensCount)++;
    (*tokensCount)++;
    for( ; ;) {
        temp = strtok(NULL, delimiters);
        if(temp == NULL)
            break;
        len = strlen(temp);
        // TODO: у вас не на каждый calloc в программе зовётся free.
        tokens[*tokensCount].s = calloc(len, sizeof(char));
        tokens[*tokensCount].s = temp;
        *tokensCount = *tokensCount + 1;
    }
    free(temp);
}
