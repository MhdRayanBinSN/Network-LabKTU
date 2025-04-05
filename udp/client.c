#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main() {
    char buff[100], response[100];
    int sock_desc;
    struct sockaddr_in server;
    socklen_t len;
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1) {
        printf("Error in socket creation\n");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(3003);
    server.sin_addr.s_addr = INADDR_ANY;
    printf("Enter the data to be sent: ");
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = '\0';
    len = sizeof(server);
    int k = sendto(sock_desc, buff, strlen(buff), 0, (struct sockaddr*)&server, len);
    if (k == -1) {
        printf("Error in sending data\n");
        close(sock_desc);
        exit(1);
    }
    printf("Data sent to the server.\n");
    k = recvfrom(sock_desc, response, sizeof(response), 0, (struct sockaddr*)&server, &len);
    if (k == -1) {
        printf("Error in receiving response\n");
        close(sock_desc);
        exit(1);
    }
    response[k] = '\0';
    printf("Response from server: %s\n", response);
    close(sock_desc);
    return 0;
}

