#pragma once

#include <iostream>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

//typedef bitset<8> BYTE;
typedef uint8_t BYTE;

#include "SHA.h"
#include "AES.h"
#include "TCP-Client.h"
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
