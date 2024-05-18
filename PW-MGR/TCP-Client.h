#include "include.h"

static int port = 54000;
static string = "127.0.0.1";

static SOCKET sock;

static HOSTENT *host;

static sockaddr_in sin;

void initWinSock();
void createSocket();
void getServerInfo();
void defineServerInfo();
void connectToServer();
void receiveData();
void sendData(string data);