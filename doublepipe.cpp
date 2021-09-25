#include <unistd.h>
#include <stdio.h>

int main() {
        int result, fd[2], fd1[2];
        int a, b, sum;
        a = 2;
        b = 3;
        pipe(fd);
        pipe(fd1);
        result = fork();
        if(result > 0) {
                close(fd[0]);
                close(fd1[1]);
                write(fd[1], &a, sizeof(a));
                write(fd[1], &b, sizeof(b));
                read(fd1[0], &sum, sizeof(sum));
                printf("%d\n", sum);
        } else {
                close(fd1[0]);
                close(fd[1]);
                read(fd[0], &a, sizeof(a));
                read(fd[0], &b, sizeof(a));
                sum = a + b;
                write(fd1[1], &sum ,sizeof(sum));
        }
        return 0;
}
