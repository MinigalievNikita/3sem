#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <split.h>

// TODO: непонятно, почему структура называется stringS (мн. число), хотя char* - это всего лишь одна строка
struct String{
    char *s;
};

int main() {
    long unsigned  len;
    int tokensCount = 0;
    char *delimiters = calloc(50, sizeof(char));
    char *input_string = calloc(10000, sizeof(char));
    gets(input_string);
    gets(delimiters);
    len = strlen(input_string);
    // видимо вы имели ввиду array, а не massive. но кажется вот такая запись итак вполне понятна: struct String* strings = ...;
    struct String *words = calloc((len), sizeof(struct String));
    Split(input_string,  delimiters,  words, &tokensCount);
    printf("%d\n", tokensCount);
    for(int i = 0; i < tokensCount; ++i) {
        printf("%s\n", words[i].s);
    }
    free(delimiters);
    free(input_string);
    free(words);
}
