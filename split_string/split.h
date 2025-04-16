#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct strings{
    char *s;
};

void Split(char* string, char* delimiters, struct strings* tokens, int* tokensCount);
