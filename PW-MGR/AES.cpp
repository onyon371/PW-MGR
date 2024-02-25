#include "AES.h"

bitset<256> mainKeyConverter(string value)
{
	bitset<8> temp;
	bitset<256>res; // 55 CHAR MAX
	int counter = 255;
	for (int i = 0; i < 32; i++)
	{
		if (i < value.size()) temp = value[i];
		else temp = 0;
		for (int q = 7; q >= 0; q--)
		{
			res[counter] = temp[q];
			counter--;
		}
	}
	return res;
}

void firstFourKeyGenerator(bitset<32> dest[4], bitset<256> mainKey)
{
	int counterDest = 31;
	int counterArray = 0;
	for(int i = 255; i >= 128; i--)
	{
		if (counterArray >= 4) break; // pe esse sicuri
		if (counterDest < 0) { counterDest = 31; counterArray++; }
		dest[counterArray][counterDest] = mainKey[i];
		counterDest--;
	}
}

void keyExpansion(string userName, string passWord)
{
	//32 caratteri chiave principale
	//pw < 32 aggiungi char dal usr
	//pw > 32 tronchi la pw a 32
	
	passWord += userName;
	bitset<256> mainKey = mainKeyConverter(passWord);

	bitset<32> firstFourKey[4];
	firstFourKeyGenerator(firstFourKey, mainKey);
	

	cout << "MainKey:\n" << mainKey << "\nFIRST:\n" << firstFourKey[0] << "\nSEC:\n" << firstFourKey[1] << "\nTHIRD:\n" << firstFourKey[2] << "\nFOURTH:\n" << firstFourKey[3];
}
