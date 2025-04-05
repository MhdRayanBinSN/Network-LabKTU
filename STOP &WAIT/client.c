#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
int sock_desc;
void sendPacket(char packet[],int i)
{
	int k,m;
	char ack[100];
	k=send(sock_desc,packet,100,0);
	if(k==-1)
		printf("Error in sending\n");
	else
		printf("sending packet %d\n",i+1);
	for(;;)
	{
		m=recv(sock_desc,ack,100,0);
		printf("%s\n",ack);
		if(strcmp(ack,"1")==0)
			break;
		else
		{
			k=send(sock_desc,packet,100,0);
			printf("Resending packet %d\n",i+1);
		}
	}
}
int main()
{
	char buf[100];
	int k;
	struct sockaddr_in client;
	char packet[3][100]={"IAM BATMANNN.....","IAM THE SAVIOR OF GOTHAM","IAM WALTER WHITE"};
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	if (sock_desc==-1)
		printf("Error in socket creation ");
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=5651;
	k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
	if(k==-1)
		printf("Error in connecting to server \n");
	for(int i=0;i<3;i++)
	{
		sendPacket(packet[i],i);
	}
	printf("packets transmitted successfully\n");
	close (sock_desc);
	return 0;
}
