#include "SHA.h"

bool createMessageBlock(string inputText)
{
	bitset<8> temp;
	bitset<512>res;
	int counter = 511;
	for(int i = 0; i < inputText.size(); i++)
	{
		temp = inputText[i];
		for(int q = 7; q >= 0; q--)
		{
			res[counter] = temp[q];
			counter--;
		}
	}
	res.flip(counter);
	cout << temp<<"\n\n";
	cout << res;
	return true;
}