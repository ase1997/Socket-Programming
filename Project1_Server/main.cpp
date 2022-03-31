#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#pragma comment (lib, "ws2_32.lib")  // load ws2_32.dll

DWORD WINAPI Protocol(LPVOID IPParameter);

using namespace std;

int main()
{
	cout << "Server Connected!" << endl;


	// initialize winsock
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	// create a socket
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


	// bind the socket to IP_ADDRESS:PORT
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  // fill every byte with 0s
	sockAddr.sin_family = PF_INET;  // use IPv4 address
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // specify the IP address
	sockAddr.sin_port = htons(1234);  // choosing port
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));


	// start listening
	listen(servSock, 20);
	// connect to the client
	SOCKADDR_IN clntAddr;


	int nSize = sizeof(SOCKADDR);

		while (true)
		{
			SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
			char szIpAddress[16]; // name of the online host
			strcpy_s(szIpAddress, sizeof(szIpAddress), inet_ntoa(clntAddr.sin_addr));
			cout << szIpAddress << " is on the line." << endl;
			HANDLE hThread_1 = CreateThread(NULL, 0, Protocol, (LPVOID)&clntSock, 0, NULL);
			CloseHandle(hThread_1);
		}

	closesocket(servSock); // close the socket
	// clean up winsock
	WSACleanup();
	cout << "Server ended.\n" << endl;
	system("pause");
	return 0;
}



DWORD WINAPI Protocol(LPVOID IPParameter)
{
	SOCKET clntSock = *(SOCKET*)IPParameter;


	// data returned by the server from the client
	char szBuffer[MAXBYTE] = {0};
	recv(clntSock, szBuffer, MAXBYTE, NULL);
	cout << "Client's Message: " << szBuffer << endl; // output the message from the client


	// send data to the client
	char *str = szBuffer;
	send(clntSock, str, strlen(str) + sizeof(char), NULL);


	//closesocket(clntsock) // close the socket
	return 0;
}
