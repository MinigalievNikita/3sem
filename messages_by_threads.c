#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>

const int SIZE_OF_BUFFER = 1000;

void *writer(void *arg){
    int index;
    char *fifo = (char*) arg;
    char *buffer = calloc(SIZE_OF_BUFFER, sizeof(char));
    index = open(fifo, O_WRONLY);
    
    while(1) {
        gets(buffer);
        write(index, buffer, SIZE_OF_BUFFER);
    }
    free (buffer);
}

void reader(char *fifo, char *buffer) {
    int index;
    index = open(fifo, O_RDONLY);
    while(1) {
    read(index, buffer , SIZE_OF_BUFFER);
    printf("%s\n", buffer);
    }
}

int main() {
    char* fifo12 = "FIFO1.txt";
    char* fifo21 = "FIFO2.txt";
    mknod(fifo12, S_IFIFO | 0666,0);
    mknod(fifo21, S_IFIFO | 0666,0);
    pthread_t thid;
    char *buffer = calloc(SIZE_OF_BUFFER, sizeof(char));
    int arg;
    printf("ENTER USER's NUMBER (1 or 2):");
    scanf("%d", &arg);
    int result;
    
    if(arg == 1) {

        result = pthread_create( &thid, (pthread_attr_t *)NULL, writer, fifo12);

        if(result != 0) {
            printf("ERROR");
        }

        reader(fifo21, buffer);

    } else {

        result = pthread_create( &thid, (pthread_attr_t *)NULL, writer, fifo21);

        if(result != 0) {
            printf("ERROR");
        }

        reader(fifo12, buffer);

    }
    free (buffer);
    return 0;
}

