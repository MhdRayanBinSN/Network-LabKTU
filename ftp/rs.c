// FTP SERVER (with file content reversal)
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    FILE *fp;
    int sock, client;
    struct sockaddr_in server_address, client_address;
    int length;
    char name[100], temp[100], rev[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket creation failed.");
        exit(0);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = 5000;
    server_address.sin_addr.s_addr = INADDR_ANY;

    int status = bind(sock, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    if (status < 0) {
        printf("Binding failed.");
        exit(0);
    }

    status = listen(sock, 5);
    if (status < 0) {
        printf("Listening failed.");
        exit(0);
    }

    length = sizeof(client_address);
    client = accept(sock, (struct sockaddr*)&client_address, &length);
    if (client < 0) {
        printf("Couldn't establish connection.");
    }

    recv(client, rev, 100, 0);
    rev[100] = '\0';
    fp = fopen(rev, "r");

    if (fp == NULL) {
        printf("Failed to open file.\n");
        close(sock);
        close(client);
        exit(0);
    }

    while (fgets(temp, 100, fp) != NULL) {
        reverseString(temp);  // Reverse the content of the line
        send(client, temp, 100, 0);
    }
    
    printf("File copied and reversed content sent.\n");
    fclose(fp);
    close(sock);
    close(client);

    return 0;
}

