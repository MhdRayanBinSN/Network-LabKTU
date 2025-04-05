#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
int main(int argc, char *argv[])
{
    struct sockaddr_in server, client;
    if (argc != 3)
        printf("Input format not correct");
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
        printf("Error in socket();");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[2]));
    socklen_t server_len = sizeof(server);
    char buffer[100];
    printf("Enter the message to send to server");
    fgets(buffer, 100, stdin);
    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
        printf("error in sending");
    printf("Enter the second number to be sent to server");
    fgets(buffer, 100, stdin);
    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
        printf("error in sending");
    if (recvfrom(sockfd, buffer, 100, 0, (struct sockaddr *)&server, &server_len) < 0)
        printf("Error in recufrom()!");
    printf("sum is %s", buffer);
    return 0;
}