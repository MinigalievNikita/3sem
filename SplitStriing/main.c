#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <split.h>

// TODO: непонятно, почему структура называется stringS (мн. число), хотя char* - это всего лишь одна строка
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
    // видимо вы имели ввиду array, а не massive. но кажется вот такая запись итак вполне понятна: struct String* strings = ...;
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
