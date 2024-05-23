#include "include.h"

static Aes aes;
static InverseAes inverseAes;
static SHA256 sha;

void textToSha(string& input)
{
	int index = 0;
	char temp;
	std::array<uint8_t, 32> textArray;
	for (int i = 0; i < input.size(); i++)
	{
		temp = input[i];
		textArray[i] = uint8_t(temp);
		index++;
	}
	input = sha.toString(textArray);
}

void getDataFromAnswer(string incomingText, string& passwordDecrypted, string& infoDecrypted)
{

}

int main() 
{
	string text = "hello";
	string pw = "pw";
	aes.encodeText(text, pw, text);
	inverseAes.DECODE_TEXT(text, pw, text);
	cout << text<<"\n";
	vector<string> cryptedPW;
	vector<string> cryptedInfo;
	string username, password, LOGINDATA;
	bool fetchData;
	char scelta;

	do
	{
		cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
		cout << "[1] Login\n[2] Register\n[3] Quit\n";
		cin >> scelta;
		system("cls");
	} while (scelta < '1' || scelta > '3');
	switch (scelta)
	{
	case '1':
		cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
		break;
	case '2':
		cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
		cout << "Crea Username: ";
		cin >> username;
		cout << "Crea Password: ";
		cin >> password;
		break;
	case '3':
		return 0;
	}
	LOGINDATA = username + password;
	textToSha(LOGINDATA);
	string res;

	res = sendData("LOGIN/////:"+LOGINDATA+"%"+"&");
	
	if(scelta == '1')
	{
		//account non trovato
		if(res == "NODATA")
		{
			do
			{
				system("cls");
				cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
				cout << "Account not found, do you want to create a new one? Y/N";
				cin >> scelta;
			} while (scelta != 'N' && scelta != 'Y');
			if(scelta == 'N')
			{
				return 0;
			}
			if(scelta == 'Y')
			{
				system("cls");
				cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
				cout << "Account created succesfully, add your first password to save the account!";
				//ADD FIRST PW
			}
		}else
		{
			//FETCH PW
			fetchData = true;
		}
	}else if(scelta == '2')
	{
		system("cls");
		cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
		if(res == "NODATA")
		{
			cout << "Account created succesfully, add your first password to save the account!";
			//ADD FIRST PW
		}else
		{
			cout << "Existing account found! Logging in!";
			fetchData = true;
		}
	}

	if(fetchData == true)
	{
		
	}

	
	
	system("pause");
	return 0;
}