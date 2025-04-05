#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

int sock_desc,temp_sock_desc;
void recvPacket(int i)
{
	char buf[100],ack[100];
	int k;
	k=recv(temp_sock_desc,buf,100,0);
	if(k==-1)
		printf("Error in receiving packet %d\n",i+1);
	for(;;)
	{
		printf("Packet %d received or not:",i+1);
		scanf("%s",ack);
		ack[strlen(ack)]='\0';
		k=send(temp_sock_desc,ack,100,0);
		if(strcmp(ack,"1")==0)
			break;
		else
		{
			k=recv(temp_sock_desc,buf,100,0);
		}
	}
}

int main()
{
	char buf[100];
	char ack[100];
	
	int k,m;
	socklen_t len;
	
	struct sockaddr_in server,client;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	if (sock_desc==-1)
		printf("Error in socket creation ");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=5651;
	
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=5656;
	k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	if(k==-1)
		printf("Error in binding\n");
	k=listen(sock_desc,5);
	if(k==-1)
		printf("Error in listening\n");
	
	len=sizeof(client);
	temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
	if(temp_sock_desc==-1)
		printf("Error in temperory socket creation");
	for(int i=0;i<3;i++)
	{
		recvPacket(i);
	}
	close(temp_sock_desc);
	return 0;
}

	
