#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
int sid,t;
void check(char str[], int k)
{
    if (k == -1)
    {
        printf("Error in %s", str);
    }
}
void recvPacket(int i){
    char buff[100],ack[100];
    int k = recv(t,buff,100,0);
    if(k==-1){
        printf("err");
    }
    for(;;){
        printf("packet %d recived or not ",i+1);
        scanf("%s",ack);
        ack[strlen(ack)]='\0';
        k=send(t,ack,100,0);
        if(strcmp(ack=="1")==0){
            break;
        }else{
            
        }
    }
}
void main()
{
    int  k;
    FILE *fp;
    struct sockaddr_in server, client;
    sid = socket(AF_INET, SOCK_STREAM, 0);
    check("socket creatopm", sid);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;
    client.sin_family = AF_INET;
    client.sin_port = htons(8080);

    bind(sid, (struct sockaddr *)&server, sizeof(server));
    printf("ready");
    listen(sid, 5);
    socklen_t len = sizeof(client);
    t = accept(sid, (struct sockaddr *)&client, &len);
    check("Erron in accepting",t);

    for(int i=0;i<3;i++)
	{
		recvPacket(i);
	}


    close(t);
    close(sid);
}
