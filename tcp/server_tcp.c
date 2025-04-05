#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
int main() {
    char num1[100],num2[100];
    socklen_t len;
    int sock_desc, temp_sock_desc;
    struct sockaddr_in server, client;
    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
        printf("Error in socket creation");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;
    client.sin_family = AF_INET;
    client.sin_port = 3003;
    int k = bind(sock_desc, (struct sockaddr*)&server, sizeof(server));
    if (k == -1)
        printf("Error in binding");
    printf("Server is ready and waiting for messages...\n");

    
    k = listen(sock_desc, 5);
    if (k == -1)
        printf("Error in listening");
        
    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr*)&client, &len);
    if (temp_sock_desc == -1)
        printf("Error in temporary socket creation");
    k = recv(temp_sock_desc, num1, 100, 0);
    if (k == -1)
        printf("Error in receiving");
    printf("Message got from client: %s", num1);  
     k = recv(temp_sock_desc, num2, 100, 0);
    if (k == -1)
        printf("Error in receiving");
    printf("Message got from client: %s", num2);
	int sum = atoi(num1)+atoi(num2);
	printf("Sum : %d\n",sum);
	char suma[100];
	suma[0]=sum;
    	k = send(sock_desc, suma, 100, 0);
    	if (k == -1)
        	printf("Error in sending");
        
    close(temp_sock_desc);
    return 0;
}

