/*
 * Server.c
 *
 *  Created on: 2013-5-8
 *      Author: neu
 */

#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>

#define SERVER_PORT 49949
#define SERVER_IP "127.0.0.1"

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
	SOCKET ser_sockfd;
	int len;
	int addrlen;
	//int addrlen;
	char buffer[100];
	struct sockaddr_in ser_addr;
	/*建立socket*/
	ser_sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(ser_sockfd<0) {
		printf("I cannot socket success/n");
		return 1;
	}
	/*填写sockaddr_in 结构*/
	addrlen=sizeof(struct sockaddr_in);
	memset(&ser_addr,0,sizeof(struct sockaddr_in));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
	ser_addr.sin_port=htons(SERVER_PORT);
	//绑定客户端
	int result = bind(ser_sockfd,(struct sockaddr *)&ser_addr,addrlen);
	printf("result:%d",result);
	if (result < 0)
	{
		printf("bind error");
		printf("error in sendto func :%d\n",WSAGetLastError());
		return 1;
	}
//	while(1) {
//		Sleep(1000);
		memset(&buffer,0,sizeof(buffer));
		len=recvfrom(ser_sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&ser_addr,&addrlen);
//		if (len == -1) {
//			continue;
//		}
		/*显示client端的网络地址*/
		printf("receive from %s \r\n",inet_ntoa(ser_addr.sin_addr));
		/*显示客户端发来的字串*/
		printf("recevce:%s \r\n",buffer);
		/*将字串返回给client端*/
		sendto(ser_sockfd,buffer,len,0,(struct sockaddr*)&ser_addr,addrlen);
//	}
}
