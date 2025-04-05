#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
int main() {
    FILE *fp;
    int sock;
    struct sockaddr_in client_address;
    int status;
    char name[100], rcvmsg[100], fname[100], rcv[100], temp[100];
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket creation failed.");
        exit(0);
    }
    client_address.sin_family = AF_INET;
    client_address.sin_port = 5000;
    client_address.sin_addr.s_addr = INADDR_ANY;
    status = connect(sock, (struct sockaddr*)&client_address, sizeof(client_address));
    if (status < 0) {
        printf("Connection failed.");
        exit(0);
    }
    printf("Enter the existing file name: ");
    scanf("%s", name);
    printf("Enter the new file name: ");
    scanf("%s", fname);
    send(sock, name, 100, 0);
    fp = fopen(fname, "w");
    while (recv(sock, temp, 100, 0)) {
        printf("%s", temp);
        fprintf(fp, "%s", temp);
    }
    close(sock);
    fclose(fp);
    return 0;
}

