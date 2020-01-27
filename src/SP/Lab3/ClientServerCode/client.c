#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> 

#define PORT 5555

int main(int argc, char *argv[])
{
    int sock = 0,valread;
    struct sockaddr_in serv_addr; 

//
	char *hello = "Hello from client";
    char buffer[1024] = {0};
//
    if(argc != 2)
    {
        printf("\n Usage: %s <Server IP address>\n",argv[0]);
        return -1;
    } 

    
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) //convert IPv4 and IPv6 addresses from text to binary form
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    } 

    if( connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\nConnection Failed \n");
       return -1;
    } 
    
    int readbytes;
    char recvBuff[500];
    memset(recvBuff, '0',sizeof(recvBuff));


    printf("Server Time: ");
    while ( (readbytes=read(sock, recvBuff, sizeof(recvBuff))) > 0)
    {
        recvBuff[readbytes] = 0;
	    printf("%s",recvBuff);
    }

    if(readbytes < 0)
    {
        printf("\n Read error \n");
    }

	
//
	printf("%s-----------------\n",hello);
	//write(sock, hello, strlen(hello)); 
	send(sock , hello , strlen(hello) , 0 );
	printf("message sent\n");
	
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    
    while ( (valread=read(sock, buffer, 1024)) > 0)
    {
        buffer[valread] = 0;
	    printf("%s",buffer);
    }
    
    if(valread < 0)
    {
        printf("\n Read error \n");
    }
//
    return 0;
}
