#include "include.h"

int main() 
{
	Aes aes;
	SHA256 sha;
	string username, password, textToConvertSHA, shaConverted;
	


	cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	textToConvertSHA = username + password;

	
	int index = 0;
	char temp;
	std::array<uint8_t, 32> textArray;
	for (int i = 0; i < textToConvertSHA.size(); i++)
	{
		temp = textToConvertSHA[i];
		textArray[i] = uint8_t(temp);
		index++;
	}
	shaConverted = sha.toString(textArray);
	
	cout << sendData("ADD///////:f%password&info password");
	system("pause");
	return 0;
}