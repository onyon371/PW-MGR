#include "TCP-Client.h"

string sendData(string messageToSend)
{
	std::string messageReceived;
	const int DEFAULT_BUFLEN = 256;

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cout << "WSAStartup Failed with error: " << iResult << std::endl;
		return "";
	}

	SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return "";
	}

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &addrServer.sin_addr.s_addr);

	addrServer.sin_port = htons(6666);
	memset(&(addrServer.sin_zero), '\0', 8);

	std::cout << "Connecting..." << std::endl;
	iResult = connect(ConnectSocket, (SOCKADDR*)&addrServer, sizeof(addrServer));
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		std::cout << "Unable to connect to server: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return "";
	}

	char messageSended[DEFAULT_BUFLEN] = { 0 };
	for(int i = 0; i < messageToSend.size(); i++)
	{
		messageSended[i] = messageToSend[i];
	}

	const char* sendbuf = messageSended;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << "Send failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return "";
	}

	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {

			
			for (int i = 0; i < iResult; i++) messageReceived += recvbuf[i];
		}
		else if (iResult == 0)
			std::cout << "Connection closed\n" << std::endl;
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return "";
	}

	closesocket(ConnectSocket);
	WSACleanup();
	return messageReceived;
}
