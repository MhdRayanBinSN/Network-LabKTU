#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
int sid,k;
void check(char str[],int k){
    if(k==-1){
        printf("Error in %s",str);
    }
}
void sendPacket(char packet[],int i){
    int k = send(sid,packet,100,0);
    if(k==-1){
        printf("eer in sending");
    }else{
        printf("Sending packet %d",i+1);
    }
    for(;;){
        recv(sid,ack,100,0);
        printf("%s",ack)
        if(strcmp(ack,"1")==0){
            break;
        }else{
            
        }
    }
}
void main(){
    struct sockaddr_in server,client;
    sid = socket(AF_INET,SOCK_STREAM,0);
    check("socket creatopm",sid);

    client.sin_addr.s_addr=INADDR_ANY;
    client.sin_family=AF_INET;
    client.sin_port=htons(8080);

    k=connect(sid,(struct sockaddr*)&client,sizeof(client));
   if(k==-1){
    printf("errin conecting")
   }
   char packet[3][100]={"hujkjdkf","jdfj","sdra"}
   for(int i =0;i<3;i++){
    sendPacket(packet[i],i);
   }
    close(sid);

    



}


