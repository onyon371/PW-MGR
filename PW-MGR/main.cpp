#include "include.h"

int main() 
{
	keySchedulling key;
	key.keyGenerator("ciao, sono il miglior programmat");
	
	key.roundKeyShower();
	return 0;
}