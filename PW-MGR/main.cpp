#include "include.h"

int main() 
{

	Aes aes;
	BYTE t = 0x01;

	for(int i = 0; i < 20; i++)
	{
		printf("%.2X", i);
		cout << " : ";
		printf("%.2X", aes.recursiveFunction(i));
		cout << "\n";
		i += 0x00;
	}
	
	return 0;
}