#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

void check(char strr[], int value) {
	if (value < 0)
		printf("%s FAILED\n", strr);
}

void main() {
	int cid, con, size, csend, crec, i;
	char sendbuff[500], recbuff[500], fromaddress[500], toaddress[500], mailbody[1000];
	
	// Create socket
	cid = socket(AF_INET, SOCK_STREAM, 0);
	check("SOCKET CREATION", cid);
	
	struct sockaddr_in caddr;
	caddr.sin_family = AF_INET;
	caddr.sin_port = htons(8082);
	caddr.sin_addr.s_addr = INADDR_ANY;
	size = sizeof(caddr);
	
	// Connect to server
	con = connect(cid, (struct sockaddr *)&caddr, size);
	check("CONNECTION", con);
	
	// Send initial message to server
	printf("\n<-->\n");
	printf("SENDING HI TO SERVER\n");
	strcpy(sendbuff, "HI");
	csend = send(cid, sendbuff, 500, 0);
	check("SENDING", csend);
	
	// Receive response from server
	printf("WAITING FOR SERVER RESPONSE\n");
	crec = recv(cid, recbuff, 500, 0);
	check("RECEIVE", crec);
	printf("MESSAGE FROM SERVER:%s\n", recbuff);
	
	// Send HELLO to server
	printf("SENDING HELLO TO SERVER\n");
	strcpy(sendbuff, "HELLO");
	csend = send(cid, sendbuff, 500, 0);
	check("SENDING", csend);
	
	// Wait for OK message
	printf("WAITING FOR OK MESSAGE\n");
	crec = recv(cid, recbuff, 500, 0);
	check("RECEIVE", crec);
	if (strncmp(recbuff, "250", 3))
		printf("OK NOT RECEIVED\n");
	else
		printf("MESSAGE FROM SERVER:%s\n", recbuff);
	
	// Get FROM address and send to server
	printf("ENTER THE FROM ADDRESS:");
	scanf("%s", fromaddress);
	strcpy(sendbuff, "MAIL FROM:");
	strcat(sendbuff, fromaddress);
	csend = send(cid, sendbuff, 500, 0);
	check("SENDING", csend);
	
	// Wait for OK message
	printf("WAITING OK FROM MESSAGE\n");
	crec = recv(cid, recbuff, 500, 0);
	check("RECEIVE", crec);
	if (strncmp(recbuff, "250", 3))
		printf("OK NOT RECEIVED\n");
	else
		printf("MESSAGE FROM SERVER:%s\n", recbuff);
	
	// Get TO address and send to server
	printf("ENTER TO ADDRESS:");
	scanf("%s", toaddress);
	strcpy(sendbuff, "MAIL TO:");
	strcat(sendbuff, toaddress);
	csend = send(cid, sendbuff, 500, 0);
	check("SENDING", csend);
	
	// Wait for OK message
	printf("WAITING OK FROM SERVER\n");
	crec = recv(cid, recbuff, 500, 0);
	check("RECEIVE", crec);
	if (strncmp(recbuff, "250", 3))
		printf("OK RECEIVED\n");
	else
		printf("MESSAGE FROM SERVER:%s\n", recbuff);
	
	// Send DATA command to server
	printf("SENDING DATA TO THE SERVER...\n");
	strcpy(sendbuff, "DATA");
	csend = send(cid, sendbuff, 500, 0);
	check("SENDING", csend);
	
	// Wait for OK message
	printf("WAITING OK FROM SERVER\n");
	crec = recv(cid, recbuff, 500, 0);
	check("RECEIVE", crec);
	if (strncmp(recbuff, "354", 3))
		printf("OK NOT RECEIVED\n");
	else
		printf("MESSAGE FROM SERVER:%s\n", recbuff);
	
	// Send mail body to server
	printf("Enter the mail body\n");
	for (i = 0;; i++) {
		fgets(mailbody, sizeof(mailbody), stdin);
		csend = send(cid, mailbody, 1000, 0);
		if (strncmp(mailbody, "$", 1) == 0)
			break;
		check("SENDING", csend);
	}
	
	// Wait for OK message
	printf("SENDING MAILBODY TO SERVER\n");
	printf("WAITING OK FROM SERVER\n");
	crec = recv(cid, recbuff, 500, 0);
	check("RECEIVE", crec);
	if (strncmp(recbuff, "221", 3))
		printf("OK NOT RECEIVED\n");
	else
		printf("MESSAGE FROM SERVER:%s\n", recbuff);
	
	// Send QUIT command to server
	strcpy(sendbuff, "QUIT");
	csend = send(cid, sendbuff, 1000, 0);
	printf("SENDING %s...\n", sendbuff);
	
	// Receive final response from server
	strcpy(recbuff, "");
	crec = recv(cid, recbuff, 500, 0);
	if (strncmp(recbuff, "221 OK", 6) == 0) {
		printf("Exiting....");
	}
	
	// Close connection
	printf("CONNECTION CLOSED\n");
	close(cid);
}