#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

// TODO: вместо использования числа 1000 нужно завести константу, из имени которой понятно её назвачение

void talk_to_consol(char *fifo1, char *fifo2, char *buffer);

int main() {
    char *buffer = calloc(1000, sizeof(char));
    char* fifo12 = "FIFO1.txt";
    char* fifo21 = "FIFO2.txt";
    
    mknod(fifo12, S_IFIFO | 0666,0);
    mknod(fifo21, S_IFIFO | 0666,0);
    
    int arg;
    printf("ENTER USER's NUMBER (1 or 2):");
    scanf("%d", &arg);
    
    if(arg == 1) {
        talk_to_consol(fifo12, fifo21, buffer);
    } else {
        talk_to_consol(fifo21, fifo12, buffer);
    }
    
    free (buffer);
    return 0;
}

void talk_to_consol(char *fifo1, char *fifo2, char *buffer ) {
    int index;
    int p = fork();
    
    if(p == 0) {
        index = open(fifo2, O_WRONLY);
        while(1) {
            gets(buffer);
            write(index, buffer, 1000);
        }
    }
    
    if(p > 0) {
        index = open(fifo1, O_RDONLY);
        while(1) {
            read(index, buffer , 1000);
            printf("%s\n", buffer);
        }
    }
}

