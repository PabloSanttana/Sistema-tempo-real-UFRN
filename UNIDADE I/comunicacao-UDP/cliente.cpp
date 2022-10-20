//
//  cliente7.cpp
//  str
//
//  Created by Affonso on 16/05/16.
//  Copyright © 2016 Affonso. All rights reserved.
//

// #include "cliente7.hpp"

// programa cliente7.cpp --> ler um vetor de caracter. Protocolo UDP

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    struct timeval timer_initial, timer_end;

    int sockfd;
    int len;
    socklen_t len_recv;
    struct sockaddr_in address;

    // microSegundos
    int timerVetor_us[30];
    float media_us = 0;
    float dp_us = 0;
    int timer_us = 0;
    // milissegundos
    int timerVetor_ms[30];
    float media_ms = 0;
    float dp_ms = 0;
    int timer_ms;

    int count = 0;
    int selectByte = 0;
    int bytes[] = {64, 128, 256, 512, 1024};

    unsigned short porta = 9734;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // criacao do socket

    address.sin_family = AF_INET;
    // address.sin_addr.s_addr = inet_addr("192.168.1.5"); // rede
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // local
    address.sin_port = htons(porta);

    len = sizeof(address);
    len_recv = sizeof(address);
    printf("O cliente vai enviar a mensagem para o servidor \n\n\n");

    while (selectByte < 5)
    {

        char vetor_ch[bytes[selectByte]];
        for (int i = 0; i < bytes[selectByte]; i++)
        {
            vetor_ch[i] = 'A';
        }
        gettimeofday(&timer_initial, NULL); // início é uma struct com dois campos:tv_sec e tv_usec.
        sendto(sockfd, vetor_ch, sizeof(vetor_ch), 0, (struct sockaddr *)&address, len);
        if (recvfrom(sockfd, vetor_ch, sizeof(vetor_ch), 0, (struct sockaddr *)&address, &len_recv) < 0)
        {
            perror(" erro no RECVFROM( )");
            exit(1);
        }
        gettimeofday(&timer_end, NULL); // apontando o ponteiro para null.
        // microSegundos
        timer_us = (int)((timer_end.tv_usec - timer_initial.tv_usec));
        timerVetor_us[count] = timer_us / 4;
        media_us += timerVetor_us[count];
        // milissegundos
        timer_ms = (int)(1000 * (timer_end.tv_sec - timer_initial.tv_sec) + (timer_end.tv_usec - timer_initial.tv_usec) / 1000);
        timerVetor_ms[count] = timer_ms / 4;
        media_ms += timerVetor_ms[count];
        count++;

        if (count == 30)
        {
            printf("Caracter vindo do servidor = %c %c %c\n", vetor_ch[0], vetor_ch[(bytes[selectByte] / 2)], vetor_ch[bytes[selectByte] - 1]);
            printf("Bytes utilizados = %i \n", bytes[selectByte]);
            media_us = media_us / 30;
            media_ms = media_ms / 30;
            for (int i = 0; i < 30; i++)
            {
                dp_us += pow((timerVetor_us[i] - media_us), 2);
                dp_ms += pow((timerVetor_ms[i] - media_ms), 2);
            }
            dp_us = dp_us / 30;
            dp_us = sqrt(dp_us);

            dp_ms = dp_ms / 30;
            dp_ms = sqrt(dp_ms);
            printf("Media µs = %f \n", media_us);
            printf("desvio padrão µs = %f \n", dp_us);
            printf("Media ms = %f \n", media_ms);
            printf("desvio padrão ms = %f \n\n\n\n", dp_ms);
            count = 0;
            selectByte++;
            media_us = 0;
            dp_us = 0;
            media_ms = 0;
            dp_ms = 0;
        }
    }

    close(sockfd);
    exit(0);
}
