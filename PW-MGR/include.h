#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include "WinSock2.h"
#include <Ws2tcpip.h>

#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>


using namespace std;

//typedef bitset<8> BYTE;
typedef uint8_t BYTE;

#include "SHA.h"
#include "AES.h"
#include "TCP-Client.h"

#pragma comment(lib, "ws2_32.lib")



#include <chrono>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>

#include <string>
#include <array>
#include <cstdint>