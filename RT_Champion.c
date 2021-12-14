#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int pid = 0;

void funk1(int nsig){
        printf("RT\n");
        kill(pid, SIGUSR2);
}
void funk2(int nsig){
        printf("Champion\n");
        kill(getppid(), SIGUSR1);
}


int main(){
        pid = fork();
        (void)signal(SIGUSR1, funk1);
        (void)signal(SIGUSR2, funk2);

        if(pid == 0) {
                kill(getppid(), SIGUSR1);
                while(1);
        } else {
                while(1);
        }
}
