#pragma once
#include "include.h"

class keySchedulling
{
protected:
	void S_TABLE(BYTE& B);
	BYTE roundKey[15][8][4];
	void keyGenerator(string key);

	void STRING_TO_HEX(BYTE MATRIX[8][4], string text);
	void HEX_TO_STRING(BYTE MATRIX[8][4], string& text);

private:
	//utils function
	void keySeparator(string key);

	void rotWord(BYTE W[4]);

	void subWord(BYTE W[4]);

	

	BYTE recursiveFunction(BYTE i);

public:
	//void roundKeyShower();
};

class Aes: keySchedulling
{
private:
	string plainText;
	BYTE textArray[8][4];
	string encodedText;

	void textSubBytes();

	void textShiftRows();

	void textMixColumns();

	void addRoundKey(int nKey);
public:
	void encodeText(string textToEncode, string key, string& res);
};

class InverseAes: keySchedulling
{
private:
	BYTE TEXT_MATRIX[8][4];

	void INVERSE_S_TABLE(BYTE& B);

	void INVERSE_SHIFT_ROWS();

	void INVERSE_SUB_BYTES();

	void INVERSE_MIX_COLUMNS();

	void INVERSE_ADD_ROUND_KEY(int nKey);

	void HEXSTRING_TO_MATRIX(string hexString);

public:

	void DECODE_TEXT(string textToDecode, string key, string& res);
};