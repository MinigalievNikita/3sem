#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>

struct matrices {
    int N0;
    int N;
    int N_summ;
    int ok;
    double **Matric_1;
    double **Matric_2;
    double **res;
};

void clever_multiplication(struct matrices *array) {
    int N0 = array->N0, N = array->N, N_summ = array->N_summ;
    array->ok = 1;
    int sum = 0;
    for(int i = N0; i < N; i++) {
        for(int j = 0; j < N_summ; j++) {
            for(int k = 0; k < N_summ; ++k) {
                sum = sum + array->Matric_1[i][k] * array->Matric_2[k][j];
            }
            array->res[i][j] = sum;
            sum = 0;
        }
    }
}


void simple_multiplication(double **Matric_1, double **Matric_2, double **res, int N) {
    int sum = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; ++k) {
                sum = sum + Matric_1[i][k] * Matric_2[k][j];
            }
            res[i][j] = sum;
            sum = 0;
        }
    }
    
}


int main() {
    srand(1);
    int N = 10, n, num_thread_elements;
    double **Matric_1 = calloc(N, sizeof(double*));
    double **Matric_2 = calloc(N, sizeof(double*));
    double **Mult = calloc(N, sizeof(double*));
    for(int i = 0; i < N; ++i) {
        Matric_1[i] = calloc(N, sizeof(double));
        Matric_2[i] = calloc(N, sizeof(double));
        Mult[i] = calloc(N, sizeof(double));
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            Matric_1[i][j] = rand() % 100;
            Matric_2[i][j] = rand() % 100;
            Mult[i][j] = 0;
        }
    }
    printf("First:\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%lg ", Matric_1[i][j]);
        }
        printf("\n");
    }
    printf("Second\n");
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%lg ", Matric_2[i][j]);
        }
        printf("\n");
    }
    
    scanf("%d", &n);
    if(N % n != 0) {
        printf("ERROR");
        return -1;
    }
    struct matrices array;
    array.Matric_1 = Matric_1;
    array.Matric_2 = Matric_2;
    array.res = Mult;
    simple_multiplication(Matric_1, Matric_2, Mult, N);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%lg.2 ", Mult[i][j]);
        }
        printf("\n");
    }
    printf ("\n clever:\n\n");

    array.N_summ = N;
    num_thread_elements = N / n;
    pthread_t *thid = calloc(n, sizeof(pthread_t));
    for(int i = 0; i < n; ++i) {
        array.ok = 0;
        array.N0 =num_thread_elements * i;
        array.N = num_thread_elements * (i + 1);
        int result = pthread_create( thid+i, (pthread_attr_t *)NULL, clever_multiplication, &array);

        if(result != 0) {
            printf("ERROR");
        }
        while (array.ok != 1) {
            
        }
        
    }
    
    for(int i = 0; i < n; i++){
        pthread_join(thid[i], (void **)NULL);
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%lg.2 ", Mult[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}


