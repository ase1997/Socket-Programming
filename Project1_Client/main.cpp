#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#pragma comment (lib, "ws2_32.lib")  // load ws2_32.dll

using namespace std;
int main()
{
	// initialize winsock
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sock = NULL;

	while (true)
	{
		// create a socket
			sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


		// bind socket to IP_ADDRESS:PORT
		sockaddr_in sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = PF_INET;
		sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
		sockAddr.sin_port = htons(1234);


		// connect to the server
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		cout << "Send a message: ";
		char sendString[500]; // max of 500 characters, this number can be changed
		cin >> sendString;
		strcat(sendString, "\n");


		// send data to the server
		char *sendStr = sendString;
		send(sock, sendStr, strlen(sendStr) + sizeof(char), NULL);
		cout << sendString << endl;


		// receive message from the server
		char szBuffer[MAXBYTE] = { 0 };
		recv(sock, szBuffer, MAXBYTE, NULL);


		// output data received from the server
		cout << "Server's Message: " << szBuffer <<endl;

		closesocket(sock); // close the socket
	}


	cout << "Server ended." << endl;
	// clean up the winsock
	WSACleanup();
	system("pause");
	return 0;
}
