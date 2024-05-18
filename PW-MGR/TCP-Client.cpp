#include "TCP-Client.h"

void initWinSock()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	
	if (WSAStartup(ver, &data) != 0)
	{
		cerr << "ERROR::INIT_WINSOCK# " << wsResult << "\n";
		return;
	}
}

void createSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		cerr << "ERROR::CREATE_SOCKET #" << WSAGetLastError() << "\n";
		return
	}
}

void getServerInfo()
{
	host = gethostbyname(szHost);
	if(host == nullptr)
	{
		cerr << "ERROR::GET_SERVER_INFO\n";
		return;
	}
}

void defineServerInfo()
{
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;
	inet_pton(AF_INET, ipAddress.c_str(), &sin.sin_addr);
}

void connectToServer()
{
	if (connect(sock, (sockaddr*)&hint, sizeof(hint)) != 0)
	{
		cerr << "ERROR::DEFINE_SERVER_INFO#" << WSAGetLastError() << "\n";
		closesocket(sock);
		WSACleanup();
		return;
	}
}

void receiveData()
{
	char szBuffer[4096];
	char szTemp[4096];
	while(recv(sock, szTemp, 4096, 0))
		strcat(szBuffer, szTemp);

	closesocket(sock);
}

void sendData(string data)
{
	if(!send(sock, data, strlen(data), 0))
	{
		cerr << "ERROR::SEND_DATA#\n";
		closesocket(sock);
		WSACleanup();
		return;
	}
}