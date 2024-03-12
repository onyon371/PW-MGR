#pragma once
#include "include.h"

class keySchedulling
{
	BYTE Key[4][8];

	BYTE roundKey[15][4][8];

	keySchedulling(string key);

protected:
	//utils function
	void keySeparator(string key);

	void rotWord(BYTE W[4]);

	void subWord(BYTE W[4]);

	void S_TABLE(BYTE& B);

	BYTE recursiveFunction(BYTE i);
};

class Aes : keySchedulling
{


};


