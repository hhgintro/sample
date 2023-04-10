// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include < winsock2.h >
#include < stdio.h >
#include <ws2tcpip.h>	//inet_ntop

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "Winmm.lib")

#define BUFSIZE 1024

void ErrorMessage(char *str)
{
	printf("%s\n", str);
}


int main()
{
	WSADATA wsaData;
	SOCKET hSerSock;
	SOCKADDR_IN servAddr;
	int ServAddrSize;
	char addr1[100];
	char servPort[100];
	char msg[BUFSIZE];
	int StrLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) ErrorMessage("WSAStartup() Error");

	hSerSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (hSerSock == INVALID_SOCKET)   ErrorMessage("hTCPscok Error");

	//printf("연결할 주소(IP)를 입력하세요 :");
	//fgets(addr1);

	//printf("연결할 포트를 입력하세요 :");
	//fgets(servPort);
	sprintf_s(addr1, "127.0.0.1");
	sprintf_s(servPort, "9190");
	DWORD ip = 0;
	inet_pton(AF_INET, addr1, (void*)&ip);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = ip;// inet_addr(addr1);
	servAddr.sin_port = ntohs(atoi(servPort));

	//printf("접속된 클라이언트 : %s\n", inet_ntoa(servAddr.sin_addr));

	while (1)
	{
		ServAddrSize = sizeof(servAddr);

		printf("SEND : ");
		fgets(msg, sizeof(msg), stdin);

		if (strcmp(msg, "q\n") == 0) break;

		sendto(hSerSock, msg, strlen(msg), 0, (SOCKADDR*)&servAddr, sizeof(servAddr));
		StrLen = recvfrom(hSerSock, msg, BUFSIZE, 0, (SOCKADDR*)&servAddr, &ServAddrSize);

		msg[StrLen] = 0;
		printf("RECV : %s\n", msg);
	}


	WSACleanup();
	return 0;
}

