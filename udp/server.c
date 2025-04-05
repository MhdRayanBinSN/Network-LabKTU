#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main() {
    char buff[100];
    socklen_t len;
    int sock_desc;
    struct sockaddr_in server, client;
    sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_desc == -1) {
        printf("Error in socket creation\n");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);
    if (bind(sock_desc, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Error in binding\n");
        exit(1);
    }
    printf("Server is ready and waiting for messages...\n");
    len = sizeof(client);
    int k = recvfrom(sock_desc, buff, sizeof(buff), 0, (struct sockaddr*)&client, &len);
    if (k == -1) {
        printf("Error in receiving\n");
        exit(1);
    }
    buff[k] = '\0';
    printf("Message received from client: %s\n", buff);
    printf("Enter the data to be sent: ");
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = '\0'; 
    k = sendto(sock_desc, buff, strlen(buff), 0, (struct sockaddr*)&client, len);
    if (k == -1) {
        printf("Error in sending response\n");
        exit(1);
    }
    printf("Response sent to client: %s\n", buff);
    close(sock_desc);
    return 0;
}

