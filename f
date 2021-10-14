#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>



void *writer(void *arg){
    int index;
    char *fifo2 = (char*) arg;
    char *buffer2 = calloc(1000, sizeof(char));
    index = open(fifo2, O_WRONLY);
    while(1) {
        gets(buffer2);
        write(index, buffer2, 1000);
    }
    free (buffer2);
}



int main() {
        char* fifo12 = "FIFO1.txt";
    char* fifo21 = "FIFO2.txt";
    mknod(fifo12, S_IFIFO | 0666,0);
    mknod(fifo21, S_IFIFO | 0666,0);
    pthread_t thid;
    char *buffer = calloc(1000, sizeof(char));
    int arg;
    printf("ENTER USER's NUMBER (1 or 2):");
    scanf("%d", &arg);
    int result;
    if(arg == 1) {
        int index;

        result = pthread_create( &thid, (pthread_attr_t *)NULL, writer, fifo12);

        if(result != 0) {
            printf("ERROR");
        }

        index = open(fifo21, O_RDONLY);
        while(1) {
        read(index, buffer , 1000);
        printf("%s\n", buffer);
        }


    } else {
        int index;

        result = pthread_create( &thid, (pthread_attr_t *)NULL, writer, fifo21);

        if(result != 0) {
            printf("ERROR");
        }

        index = open(fifo12, O_RDONLY);
        while(1) {
        read(index, buffer , 1000);
        printf("%s\n", buffer);
        }


    }
    free (buffer);
    return 0;
}


