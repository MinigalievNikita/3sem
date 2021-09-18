#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <split.h>

struct strings{
    char *s;
};




int main() {
    long unsigned  len;
    int tokensCount = 0;
    char *delimiters = calloc(50, sizeof(char));
    char *string = calloc(10000, sizeof(char));
    gets(string);
    gets(delimiters);
    len = strlen(string);
    struct strings *string_massive = calloc((len), sizeof(struct strings));
    Split(string,  delimiters,  string_massive, &tokensCount);
    printf("%d", tokensCount);
    for(int i = 0; i < tokensCount; ++i) {
        printf("%s\t", string_massive[i].s);
    }
    free(delimiters);
    free(string);
    free(string_massive);
}
