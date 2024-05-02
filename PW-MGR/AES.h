#pragma once
#include "include.h"

class keySchedulling
{
private:
	//BYTE Key[4][8];

	BYTE roundKey[15][8][4];

protected:
	//utils function
	void keySeparator(string key);

	void rotWord(BYTE W[4]);

	void subWord(BYTE W[4]);

	void S_TABLE(BYTE& B);

	BYTE recursiveFunction(BYTE i);

public:
	void keyGenerator(string key);

	void roundKeyShower();
};