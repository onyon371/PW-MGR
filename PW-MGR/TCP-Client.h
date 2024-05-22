#pragma once
#include "include.h"

class TCP
{
private:
	int port;
	string ipAddress;

	SOCKET sock;

	HOSTENT* host;

	sockaddr_in sin;

	void initWinSock();
	void createSocket();
	//void getServerInfo();
	void defineServerInfo();
	void connectToServer();

public:
	TCP() 
	{
		port = 54000;
		ipAddress = "127.0.0.1";
		initWinSock();
	};
	void receiveData();
	void sendData(char data[4096]);
};
