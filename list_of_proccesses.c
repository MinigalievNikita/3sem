
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
        int N;
        int i;
        pid_t pid = -1;
    
        scanf("%d", &N);
    
        for(i = 0; i < N; ++i) {
            pid = fork();
            if(pid == -1) {
                printf("Error");
            }
            if(pid == 0) {
                printf("I was born and my id is %d,", getpid());
                printf("Parent id is, %d i = %d\n", getppid(), i);
            }
            if(pid > 0) {
                wait(NULL);
                    
                printf("I am father. My id is %d My child ended tasks\n", getpid());
                    
                exit(i);
                }
        }
    exit(i);
}

