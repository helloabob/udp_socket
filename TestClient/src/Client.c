/*
 * Client.c
 *
 *  Created on: 2013-5-8
 *      Author: neu
 */

#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

#define SERVER_PORT 49949
#define SERVER_IP "127.0.0.1"

//#define SERVER_PORT 5683
//#define SERVER_IP "192.168.1.101"

int GetServerAddr(char * addrname) {
	printf("please input server addr:");
	scanf("%s",addrname);
	return 1;
}
int main(void) {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 0 );
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( 0 != err ) //检查Socket初始化是否成功
	{
	   printf("Socket2.0初始化失败，Exit!");
	   return 1;
	}
	//检查Socket库的版本是否为2.0
	if (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
	{
	   WSACleanup( );
	   return 1;
	}

	SOCKET cli_sockfd;
	int len;
	int addrlen;
//	char seraddr[14];
	struct sockaddr_in cli_addr;
	char buffer[256];
//	GetServerAddr(seraddr);
	/* 建立socket*/
	cli_sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(cli_sockfd<0)
	{
		printf("I cannot socket success/n");
		return 1;
	}
//	int opt = 1;
//	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char FAR *>(&opt), sizeof(opt));
	/* 填写sockaddr_in*/
	addrlen = sizeof(struct sockaddr_in);
	memset(&cli_addr,0,sizeof(struct sockaddr_in));
	cli_addr.sin_family=AF_INET;
	cli_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	//cli_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	cli_addr.sin_port = htons(SERVER_PORT);

	//put
	//char msg[] = {66,3,10,203,145,108,1,48,123,34,98,34,58,57,48,125};

	char msg[] = "i am coming.";
	//get
//	char msg[] = {66,1,178,190,155,46,119,101,108,108,45,107,110,111,119,110,4,99,111,114,101};

	memset(&buffer,0,sizeof(buffer));
	/* 从标准输入设备取得字符串*/
//	len=read(STDIN_FILENO,buffer,sizeof(buffer));
//	char *a = "aaaaaaaaa";
	/* 将字符串传送给server端*/
	printf("start to send...\n");
	Sleep(1000);
	int result = sendto(cli_sockfd,msg,strlen(msg),0,(struct sockaddr*)&cli_addr,addrlen);
	if (result < 0) {
		printf("error in sendto func :%d\n",WSAGetLastError());
	}
	/* 接收server端返回的字符串*/
	printf("it is over。。。\n");
	len = recvfrom(cli_sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cli_addr,&addrlen);
	//printf("receive from %s/n",inet_ntoa(cli_addr.sin_addr));
	printf("receive: %s",buffer);
	closesocket(cli_sockfd);
	return 1;
}
