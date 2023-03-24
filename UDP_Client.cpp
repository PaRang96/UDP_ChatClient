#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN ClientSocketAddress;
	ZeroMemory(&ClientSocketAddress, sizeof(ClientSocketAddress));
	ClientSocketAddress.sin_addr.s_addr = inet_addr("49.174.219.3");
	ClientSocketAddress.sin_port = htons(3000);
	ClientSocketAddress.sin_family = PF_INET;

	int ClientSocketAddressLen = sizeof(ClientSocketAddress);

	char Buffer[1024] = { 0, };
	string ActualMessage;

	while (true)
	{
		cin >> ActualMessage;

		strcpy_s(Buffer, ActualMessage.c_str());

		sendto(ClientSocket, Buffer, sizeof(Buffer) - 1, 0,
			(SOCKADDR*)&ClientSocketAddress, ClientSocketAddressLen);
	}

	closesocket(ClientSocket);

	WSACleanup();

	return 0;
}