#include "TCP-Client.h"

void TCP::initWinSock()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	
	if (WSAStartup(ver, &data) != 0)
	{
		cerr << "ERROR::INIT_WINSOCK#\n";
		return;
	}
}

void TCP::createSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		cerr << "ERROR::CREATE_SOCKET #" << WSAGetLastError() << "\n";
		WSACleanup();
		return;
	}
}

/*void TCP::getServerInfo()
{
	*host = gethostbyname(ipAddress);
	if(host == nullptr)
	{
		cerr << "ERROR::GET_SERVER_INFO\n";
		WSACleanup();
		return;
	}
}*/

void TCP::defineServerInfo()
{
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	//inet_pton(AF_INET, ipAddress.c_str(), &sin.sin_addr);
	memcpy(&sin.sin_addr.S_un.S_addr, host->h_addr_list[0], sizeof(sin.sin_addr.S_un.S_addr));
}

void TCP::connectToServer()
{
	if (connect(sock, (const sockaddr*)&sin, sizeof(sin)) != 0)
	{
		cerr << "ERROR::DEFINE_SERVER_INFO#" << WSAGetLastError() << "\n";
		closesocket(sock);
		WSACleanup();
		return;
	}
}

void TCP::receiveData()
{
	createSocket();
	defineServerInfo();
	connectToServer();

	char szBuffer[4096];
	char szTemp[4096];
	while(recv(sock, szTemp, 4096, 0))
		strcat(szBuffer, szTemp);

	closesocket(sock);
}

void TCP::sendData(char data[4096])
{
	createSocket();
	defineServerInfo();
	connectToServer();

	if(!send(sock, data, 4096, 0))
	{
		cerr << "ERROR::SEND_DATA#\n";
		closesocket(sock);
		WSACleanup();
		return;
	}
}