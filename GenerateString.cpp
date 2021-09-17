#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
void GenerateString(int n, char* string);

int main() {
    int n;
    scanf("%d", &n);
    char *string = calloc(((1<<(n+1)) - 1), sizeof(char));
    GenerateString(n, string);
    printf("%s\n", string);
    free(string);
}


void GenerateString(int n, char* string) {
    int a = 'a';
    int len = ((1<<(n+1)) - 1);
    char *temp = calloc(((1<<(n+1)) - 1), sizeof(char));
    for(int i = 0; i < n; ++i) {
        strncpy(temp, string, ((1<<(n+1)) - 1));
        string[(1<<i) - 1] = (char*) (a + i);
        if(i != 0) {
            strncat(string, temp, len);
        }
    }
    free(temp);
}
