#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int error = 0;
    int end = 0;
    int sockfd; /* Дескриптор сокета */
    int n, len; /* Переменные для различных длин и
        количества символов */
    char sendline[1000], recvline[1000]; /* Массивы
        для отсылаемой и принятой строки */
    struct sockaddr_in servaddr, cliaddr;
    
    if(argc != 2){
        printf("Usage: a.out <IP address>\n");
        return -1;
    }
    /* Создаем UDP сокет */
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        perror(NULL); /* Печатаем сообщение об ошибке */
        return -1;
    }
    
         bzero(&cliaddr, sizeof(cliaddr));
         cliaddr.sin_family = AF_INET;
         cliaddr.sin_port = htons(0);
         cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
         /* Настраиваем адрес сокета */
         if(bind(sockfd, (struct sockaddr *) &cliaddr,
         sizeof(cliaddr)) < 0){
             perror(NULL);
             close(sockfd); /* По окончании работы закрываем
             дескриптор сокета */
             return -1;
         }
         /* Заполняем структуру для адреса сервера:
     семейство протоколов TCP/IP, сетевой интерфейс – из аргумента
     командной строки, номер порта 7. Поскольку в
     структуре содержится дополнительное не нужное нам
     поле, которое должно быть нулевым, перед заполнением
     обнуляем ее всю */
         bzero(&servaddr, sizeof(servaddr));
         servaddr.sin_family = AF_INET;
         servaddr.sin_port = htons(51000);
         if(inet_aton(argv[1], &servaddr.sin_addr) == 0){
             printf("Invalid IP address\n");
             close(sockfd); /* По окончании работы закрываем
                 дескриптор сокета */
             return -1;
         }
    
    printf("Say hello:");
    fgets(sendline, 1000, stdin);
    /* Отсылаем датаграмму */
    if(sendto(sockfd, sendline, strlen(sendline)+1, 0, (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    if((n = recvfrom(sockfd, recvline, 1000, 0,
    (struct sockaddr *) NULL, NULL)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    if(recvline[0] == 'A'){
        printf("You are first with 0\n\n");
        printf("Chose the square:\n");
        printf("  | 1 | 2 | 3 |\n");
        printf("  _____________\n");
        printf("A |  |  |  |\n");
        printf("  _____________\n");
        printf("B |  |  |  |\n");
        printf("  _____________\n");
        printf("C |  |  |  |\n");
        printf("  _____________\n");
    } else {
        printf("You are second with x\n\n");
     //Печатаем пришедший ответ
   printf("  | 1 | 2 | 3 |\n");
   printf("  _____________\n");
   printf("A | %c | %c | %c |\n", recvline[0], recvline[1], recvline[2]);
   printf("  _____________\n");
   printf("B | %c | %c | %c |\n", recvline[3], recvline[4], recvline[5]);
   printf("  _____________\n");
   printf("C | %c | %c | %c |\n", recvline[6], recvline[7], recvline[8]);
   printf("  _____________\n");
    
    }
    while (end != 1) {
        error = 1;
         /* Вводим строку, которую отошлем серверу */
        while(error != 0) {
         printf("Your turn =>");
         fgets(sendline, 1000, stdin);
         /* Отсылаем датаграмму */
         if(sendto(sockfd, sendline, strlen(sendline)+1, 0, (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0){
             perror(NULL);
             close(sockfd);
             exit(1);
         }
        
         /* Ожидаем ответа и читаем его. Максимальная
     допустимая длина датаграммы – 1000 символов,
     адрес отправителя нам не нужен */
         if((n = recvfrom(sockfd, recvline, 1000, 0,
         (struct sockaddr *) NULL, NULL)) < 0){
             perror(NULL);
             close(sockfd);
             exit(1);
         }
            error = 0;
            if (recvline[9] == 'T' && recvline[10] == 'A') {
                error = 1;
                printf("TRY AGAIN\n");
            }
        }
         /* Печатаем пришедший ответ */
        system("clear");
        printf("  | 1 | 2 | 3 |\n");
        printf("  _____________\n");
        printf("A | %c | %c | %c |\n", recvline[0], recvline[1], recvline[2]);
        printf("  _____________\n");
        printf("B | %c | %c | %c |\n", recvline[3], recvline[4], recvline[5]);
        printf("  _____________\n");
        printf("C | %c | %c | %c |\n", recvline[6], recvline[7], recvline[8]);
        printf("  _____________\n");
        if(recvline[9] == 'E' && recvline[10] == 'N' && recvline[11] == 'D') {
            if(recvline[12] == 'W') {
                printf("You  won");
            }
            if(recvline[12] == 'D') {
                printf("Draw");
            }
            if(recvline[12] == 'L') {
                printf("You  lost");
            }
            end = 1;
            break;
        }
        //получаем таблицу после хода оппонента
        if((n = recvfrom(sockfd, recvline, 1000, 0,
        (struct sockaddr *) NULL, NULL)) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        system("clear");
        printf("Wait for an opponent's move>>");
         //Печатаем пришедший ответ
       printf("  | 1 | 2 | 3 |\n");
       printf("  _____________\n");
       printf("A | %c | %c | %c |\n", recvline[0], recvline[1], recvline[2]);
       printf("  _____________\n");
       printf("B | %c | %c | %c |\n", recvline[3], recvline[4], recvline[5]);
       printf("  _____________\n");
       printf("C | %c | %c | %c |\n", recvline[6], recvline[7], recvline[8]);
       printf("  _____________\n");
       if(recvline[9] == 'E' && recvline[10] == 'N' && recvline[11] == 'D') {
           
           if(recvline[12] == 'W') {
               printf("You  won");
           }
           if(recvline[12] == 'D') {
               printf("Draw");
           }
           if(recvline[12] == 'L') {
               printf("You  lost");
           }
           end = 1;
       }
    }
    
         close(sockfd);
         return 0;
}

