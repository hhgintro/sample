// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include < winsock2.h >
#include < stdio.h >

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
	SOCKADDR_IN ClientAddr;
	int ClientAddrSize;
	char *servPort = "9190";
	char msg[BUFSIZE];
	int StrLen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)ErrorMessage("WSAStartup() Error");

	hSerSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (hSerSock == INVALID_SOCKET)   ErrorMessage("hSerscok Error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(servPort));

	if (bind(hSerSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) ErrorMessage("Bind Error");

	//printf("%d 포트로 주소 할당이 되었습니다.\n", ntohs(servAddr.sin_port));
	//printf("IP 주소 : %s\n", inet_ntoa(servAddr.sin_addr));
	printf("서버 대기중입니다.\n");

	while (1)
	{
		ClientAddrSize = sizeof(ClientAddr);
		StrLen = recvfrom(hSerSock, msg, BUFSIZE, 0, (SOCKADDR*)&ClientAddr, &ClientAddrSize);
		msg[StrLen] = 0;

		sendto(hSerSock, msg, StrLen, 0, (SOCKADDR*)&ClientAddr, sizeof(ClientAddr));
	}

	closesocket(hSerSock);
	WSACleanup();
    return 0;
}
