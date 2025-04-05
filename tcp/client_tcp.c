#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main() {
    char num1[100],num2[100];
    int k;
    int sock_desc, temp_sock_desc;
    struct sockaddr_in client;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
        printf("Error in socket creation");

    client.sin_family = AF_INET;
    client.sin_port = 3003;
    client.sin_addr.s_addr = INADDR_ANY;
    k = connect(sock_desc, (struct sockaddr*)&client, sizeof(client));
    if (k == -1)
        printf("Error in connecting to server");

    printf("\nEnter the num1 to be sent: ");
    fgets(num1, 100, stdin);
    k = send(sock_desc, num1, 100, 0);
    if (k == -1)
        printf("Error in sending");
        
    printf("\nEnter the num2 to be sent: ");
    fgets(num2, 100, stdin);
    k = send(sock_desc, num2, 100, 0);
    if (k == -1)
        printf("Error in sending");

	char suma[100];

	k = recv(temp_sock_desc, suma, 100, 0);
    	if (k == -1)
        	printf("Error in receiving");
int len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr*)&client, &len);
    if (temp_sock_desc == -1)
        printf("Error in temporary socket creation");

    printf("Message got from client SUM: %s\n", suma);
    close(sock_desc);
    return 0;
}


