#pragma once
#include "include.h"

class keySchedulling
{
private:
	

protected:
	BYTE roundKey[15][8][4]; //RENDERE PRIVATA

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

class Aes: keySchedulling
{
private:
	string plainText;
	BYTE textArray[8][4];
	string encodedText;

	void stringToHex();

	void hexToString();

	void textSubBytes();

	void textShiftRows();

	void textMixColumns();

	void addRoundKey(int nKey);
public:
	void encodeText(string textToEncode, string key);
};

class InverseAes: keySchedulling
{
private:

public:

};