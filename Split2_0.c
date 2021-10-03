// TODO: не хватает заголовочных файлов, чтобы программа компилировалась

void Split(char* input_string, char* delimiters, char **tokens, int* tokensCount);

int main() {
    int tokensCount = 0;
    // TODO: вместо магических чисел 50 и 10000 нужно объявить константы с понятными именами
    char *delimiters = calloc(50, sizeof(char));
    char *input_string = calloc(10000, sizeof(char));
    
    gets(input_string);
    gets(delimiters);
    long unsigned  len = strlen(input_string);
    char **words = calloc((len), sizeof(char));
    Split(input_string,  delimiters,  words, &tokensCount);
    printf("%d\n", tokensCount);
    
    for(int i = 0; i < tokensCount; ++i) {
        printf("%s\n", words[i]);
    }
    
    free(delimiters);
    free(input_string);
    free(words);
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

