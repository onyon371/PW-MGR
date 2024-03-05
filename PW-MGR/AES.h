#pragma once
#include "include.h"

class Aes
{
private:
	string inputKey;

	BYTE hexFullKey[4][8];
	
	void rotWord(BYTE W[4]);

	void subWord(BYTE W[4]);

	void S_TABLE(BYTE& B);
public:

};


