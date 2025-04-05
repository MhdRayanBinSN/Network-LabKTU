#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

// Function to check the return value of socket operations
void check(char strr[], int value) {
	if (value < 0)
		printf("%s FAILED\n", strr);
}

void main() {
	int sid, sbind, size, slisten, saccept, srec, ssend, i;
	char sendbuff[500], recbuff[500], fromaddress[500], toaddress[500], mailbody[1000];

	// Create socket
	sid = socket(AF_INET, SOCK_STREAM, 0);
	check("SOCKET CREATION", sid);

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8082);
	saddr.sin_addr.s_addr = INADDR_ANY;
	size = sizeof(saddr);

	// Bind socket
	sbind = bind(sid, (struct sockaddr*)&saddr, size);
	check("BINDING", sbind);

	// Listen for connections
	slisten = listen(sid, 5);
	check("LISTEN", slisten);

	// Accept connection
	saccept = accept(sid, (struct sockaddr*)&saddr, &size);
	check("ACCEPT", saccept);
	printf("\n.....\n");

	// Receive initial message from client
	srec = recv(saccept, recbuff, 500, 0);
	check("RECEIVE", srec);
	printf("MESSAGE FROM CLIENT: %s\n", recbuff);

	// Send response to client
	printf("SENDING RESPONSE FOR HI...\n");
	strcpy(sendbuff, "220 192.168.9.138");
	ssend = send(saccept, sendbuff, 500, 0);
	check("SENDING", ssend);

	// Wait for client response
	printf("WAITING FOR CLIENT RESPONSE...\n");
	srec = recv(saccept, recbuff, 500, 0);
	check("RECEIVE", srec);
	if (strncmp(recbuff, "HELLO", 5))
		printf("ERROR\n");
	else
		printf("MESSAGE FROM CLIENT: %s\n", recbuff);

	// Send response to HELLO
	printf("SENDING RESPONSE FOR HELLO...\n");
	strcpy(sendbuff, "250 OK");
	ssend = send(saccept, sendbuff, 500, 0);
	check("SENDING", ssend);

	// Wait for FROM address
	printf("WAITING FOR FROM ADDRESS\n");
	srec = recv(saccept, fromaddress, 500, 0);
	check("RECEIVE", srec);
	if (strncmp(fromaddress, "MAIL FROM:", 10))
		printf("From address Error\n");
	else
		printf("FROM ADDRESS: %s\n", fromaddress);

	// Send OK to FROM address
	printf("SENDING OK TO FROM ADDRESS\n");
	strcpy(sendbuff, "250 OK");
	ssend = send(saccept, sendbuff, 500, 0);
	check("SENDING", ssend);

	// Wait for TO address
	printf("WAITING FOR TO ADDRESS\n");
	srec = recv(saccept, toaddress, 500, 0);
	check("RECEIVE", srec);
	if (strncmp(toaddress, "MAIL TO:", 8))
		printf("To address Error\n");
	else
		printf("TO ADDRESS: %s\n", toaddress);

	// Send OK to TO address
	printf("SENDING OK TO TO ADDRESS\n");
	strcpy(sendbuff, "250 OK");
	ssend = send(saccept, sendbuff, 500, 0);
	check("SENDING", ssend);

	// Wait for DATA
	printf("WAITING FOR DATA...\n");
	srec = recv(saccept, recbuff, 500, 0);
	check("RECEIVE", srec);
	if (strncmp(recbuff, "DATA", 4))
		printf("DATA NOT RECEIVED\n");
	else
		printf("MESSAGE FROM CLIENT: %s\n", recbuff);

	// Send OK to DATA
	printf("SENDING OK TO CLIENT\n");
	strcpy(sendbuff, "354 GO AHEAD");
	ssend = send(saccept, sendbuff, 500, 0);
	check("SENDING", ssend);

	// Receive mail body
	printf("mail body\n");
	for (i = 0;; i++) {
		srec = recv(saccept, mailbody, 1000, 0);
		check("MAIL BODY RECEIVE", srec);
		if (strncmp(mailbody, "$", 1) == 0)
			break;
		else
			printf("%s", mailbody);
	}

	// Send final OK
	strcpy(sendbuff, "221 OK");
	ssend = send(saccept, sendbuff, 500, 0);
	printf("SENDING OK TO CLIENT\n");
	check("SENDING", ssend);

	// Wait for QUIT
	srec = recv(saccept, mailbody, 1000, 0);
	if (strncmp(mailbody, "QUIT", 4) == 0) {
		strcpy(sendbuff, "221 OK");
		ssend = send(saccept, sendbuff, 500, 0);
		printf("sending 221 ok...");
	}

	// Close connection
	printf("CONNECTION CLOSED\n");
	close(saccept);
	close(sid);
}