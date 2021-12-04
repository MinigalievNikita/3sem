#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int truewinner(char *gameline, char* sign) {
    if(gameline[0] == sign[0] && gameline[3] == sign[0] && gameline[6] == sign[0]){
        return 1;
    }
    if(gameline[1] == sign[0] && gameline[4] == sign[0] && gameline[7] == sign[0]){
        return 1;
    }
    if(gameline[2] == sign[0] && gameline[5] == sign[0] && gameline[8] == sign[0]){
        return 1;
    }
    if(gameline[0] == sign[0] && gameline[1] == sign[0] && gameline[2] == sign[0]){
        return 1;
    }
    if(gameline[3] == sign[0] && gameline[4] == sign[0] && gameline[5] == sign[0]){
        return 1;
    }
    if(gameline[6] == sign[0] && gameline[7] == sign[0] && gameline[8] == sign[0]){
        return 1;
    }
    if(gameline[0] == sign[0] && gameline[4] == sign[0] && gameline[8] == sign[0]){
        return 1;
    }
    if(gameline[2] == sign[0] && gameline[4] == sign[0] && gameline[6] == sign[0]){
        return 1;
    }
    return 0;
}


int main()
{
    char sign[2];
    int error = 0;
    int x = 0; //кол-во крестиков
    int o = 0; //кол-во ноликов
    int sockfd; /* Дескриптор сокета */
    int clilen1, clilen2, n; /* Переменные для различных длин
        и количества символов */
    int placeofsymbl;
    char line[1000]; /* Массив для принятой и
        отсылаемой строки */
    char gameline[1000];
    for(int i = 0; i < 9; ++i) {
        gameline[i] = '.';
    }
    struct sockaddr_in servaddr, cliaddr1, cliaddr2;
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Создаем UDP сокет */
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        perror(NULL); /* Печатаем сообщение об ошибке */
        exit(1);
    }
    /* Настраиваем адрес сокета */
    if(bind(sockfd, (struct sockaddr *) &servaddr,
    sizeof(servaddr)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    
    
    clilen1 = sizeof(cliaddr1);
    clilen2 = sizeof(cliaddr2);
    
    if((n = recvfrom(sockfd, line, 999, 0,(struct sockaddr *) &cliaddr1, &clilen1)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    /* Печатаем принятый текст на экране */
    printf("%s\n", line);
    char trt[10];
    trt[0] = 'A';
    if(sendto(sockfd, trt, strlen(line), 0,(struct sockaddr *) &cliaddr1, clilen1) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    if((n = recvfrom(sockfd, line, 999, 0,(struct sockaddr *) &cliaddr2, &clilen2)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    /* Печатаем принятый текст на экране */
    printf("%s\n", line);
    
    while(1) {
        /* Основной цикл обслуживания*/
        /* В переменную clilen заносим максимальную длину
        для ожидаемого адреса клиента */
        clilen1 = sizeof(cliaddr1);
        clilen2 = sizeof(cliaddr2);
        /* Ожидаем прихода запроса от клиента и читаем его.
        Максимальная допустимая длина датаграммы – 999
        символов, адрес отправителя помещаем в структуру
        cliaddr, его реальная длина будет занесена в
        переменную clilen */
        
    
        
        
        error = 1;
        while(error != 0) {
        if((n = recvfrom(sockfd, line, 999, 0,(struct sockaddr *) &cliaddr1, &clilen1)) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        /* Печатаем принятый текст на экране */
        printf("%s\n", line);
        
        if(line[0] == 'A' || line[0] == 'a') {
            placeofsymbl = atoi(line + 1) - 1;
            
        } else if (line[0] == 'B' || line[0] == 'b') {
            placeofsymbl = atoi(line + 1) - 1 + 3;
        } else if (line[0] == 'C' || line[0] == 'c') {
            placeofsymbl = atoi(line + 1) - 1 + 6;
        } else {
            strcpy(line, gameline);
            line[9] = 'T'; //try again
            line[10] = 'A';
            error = 1;
            if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr1, clilen1) < 0){
                perror(NULL);
                close(sockfd);
                exit(1);
            }
            continue;
        }
          
        // вставка 0 или x
        if(gameline[placeofsymbl] == '.') {
            o++;
            gameline[placeofsymbl] = '0';
            strcpy(line, gameline);
        } else {
            strcpy(line, gameline);
            line[9] = 'T'; //try again
            line[10] = 'A';
            error = 1;
            if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr1, clilen1) < 0){
                perror(NULL);
                close(sockfd);
                exit(1);
            }
            continue;
        }
        
        // проверка на победу
        if(o >= 3) {
            sign[0] = '0';
            if(truewinner(gameline, sign)) {
                line[9] = 'E';
                line[10] = 'N';
                line[11] = 'D';
                line[12] = 'W';
            }
        }
        
        /* Принятый текст отправляем обратно по адресу
        отправителя */
            error = 0;
            if(line[9] == 'T' && line[10] == 'A') {
                error = 1;
            }
            if(o == 5 && line[9] != 'E' && line[10] != 'N' && line[11] != 'D') {
                line[9] = 'E';
                line[10] = 'N';
                line[11] = 'D';
                line[12] = 'D';
            }
        if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr1, clilen1) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        }
        
        if(line[9] == 'E' && line[10] == 'N' && line[11] == 'D' && line[12] != 'D') {
            line[12] = 'L';
        }
        
       if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr2, clilen2) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        error = 1;
        while(error != 0) {
        if((n = recvfrom(sockfd, line, 999, 0,(struct sockaddr *) &cliaddr2, &clilen2)) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        /* Печатаем принятый текст на экране */
        printf("%s\n", line);
        
        if(line[0] == 'A' || line[0] == 'a') {
            placeofsymbl = atoi(line + 1) - 1;
            
        } else if (line[0] == 'B' || line[0] == 'b') {
            placeofsymbl = atoi(line + 1) - 1 + 3;
        } else if (line[0] == 'C' || line[0] == 'c') {
            placeofsymbl = atoi(line + 1) - 1 + 6;
        } else {
            line[9] = 'T'; //try again
            line[10] = 'A';
            error = 1;
            if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr1, clilen1) < 0){
                perror(NULL);
                close(sockfd);
                exit(1);
            }
            continue;
        }
           
        // вставка 0 или x
        if(gameline[placeofsymbl] == '.') {
            x = x + 1;
            gameline[placeofsymbl] = 'x';
            strcpy(line, gameline);
            sign[0] = 'x';
            if(truewinner(gameline, sign)) {
                line[9] = 'E';
                line[10] = 'N';
                line[11] = 'D';
                line[12] = 'W';
            }
        } else {
            strcpy(line, gameline);
            line[9] = 'T'; //try again
            line[10] = 'A';
            error = 1;
            if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr1, clilen1) < 0){
                perror(NULL);
                close(sockfd);
                exit(1);
            }
            continue;
        }
        // проверка на победу
        if(x >= 3) {
            sign[0] = 'x';
            if(truewinner(gameline, sign)) {
                line[9] = 'E';
                line[10] = 'N';
                line[11] = 'D';
                line[12] = 'W';
            }
        }
        
        /* Принятый текст отправляем обратно по адресу
        отправителя */
            error = 0;
            if(line[9] == 'T' && line[10] == 'A') {
                error = 1;
            }

            
        if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr2, clilen2) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        }
        if(line[9] == 'E' && line[10] == 'N' && line[11] == 'D') {
            line[12] = 'L';
        }
        if(sendto(sockfd, line, strlen(line), 0,(struct sockaddr *) &cliaddr1, clilen1) < 0){
            perror(NULL);
            close(sockfd);
            exit(1);
        }
        
    }
    return 0;
}

