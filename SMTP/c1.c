#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
void check(char strr[],int value){
    if(value<0){
        printf("%s FAILED\n", strr);
    }
}
void main(){
    int sid;

    sid=socket(AF_INET,SOCK_STREAM,0)
}