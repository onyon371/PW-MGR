#include "include.h"

static Aes aes;
static InverseAes inverseAes;
static SHA256 sha;

void encodeData(string username, string& password)
{
	if(username.size() > password.size())
	{
		swap(password, username);
	}
	for (int i = 0; i < username.size(); i++)
	{
		password[i] = password[i] xor username[i];
	}
}

string requestData(string ashedPassword)
{
	return sendData("LOGIN/////:" + ashedPassword + "%" + "&");
}

bool insertData(string ashedPassword, string nonAshedPassword, string pwToSave, string infoToSave)
{
	aes.encodeText(pwToSave, nonAshedPassword, pwToSave);
	aes.encodeText(infoToSave, nonAshedPassword, infoToSave);
	string res = sendData(ashedPassword + "&%#" + pwToSave + "&%#" + infoToSave);
	if (res == "SUCCESS") return true;
	else	return false;
}

void decodeData(string encodedData, string decryptKey, vector<string>& vettorePW, vector<string>& vettoreInfo)
{
	/*
		&%# = SEQUENZA DI DIVISIONE
	*/
	if(encodedData != "EMPTY")
	{
		string temp;
		bool savingPW = true;
		for (int i = 0; i < encodedData.size(); i++)
		{
			if (encodedData[i] != '&' && encodedData[i + 1] != '%' && encodedData[i + 2] != '#')
			{
				temp += encodedData[i];
			}
			else if (savingPW == true)
			{
				//FOUND CRYPTED KEY TERMINATOR
				inverseAes.DECODE_TEXT(temp, decryptKey, temp);
				vettorePW.push_back(temp);
				savingPW = false;
				temp = "";
			}
			else
			{
				inverseAes.DECODE_TEXT(temp, decryptKey, temp);
				vettoreInfo.push_back(temp);
				savingPW = true;
				temp = "";
			}
		}
	}
}


void Login(vector<string>& vettorePW, vector<string>& vettoreInfo)
{
	string username, password, res;
	system("cls");
	cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	//ENCODE PW
	encodeData(username, password);

	//covert pw to sha
	sha.textString_to_SHA(password);

	//send request to server
	string SERVER_RES = requestData(password);

	//decode request
	decodeData(SERVER_RES, password, vettorePW, vettoreInfo);
}

void Register() 
{
	string username, password, res, pwToSave, infoToSave, nonAshedPW;
	system("cls");
	cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
	cout << "Add Username: ";
	cin >> username;
	cout << "Add Password: ";
	cin >> password;
	cout << "In order to create the account, enter the first password to save: ";
	cin >> pwToSave;
	cout << "Add some password info: ";
	cin >> infoToSave;
	encodeData(username, password);
	nonAshedPW = password;
	sha.textString_to_SHA(password);
	if (insertData(password, nonAshedPW, pwToSave, infoToSave)) cout << "\nAccount created successfully!";
	else cout << "\nSomething went wrong, unable to create account, please try again later";
}

void Quit()
{
	system("cls");
	cout << "\n\nClient Closing!\n\n";
	Sleep(2000);
}

void displayData(vector<string> vettorePW, vector<string> vettoreInfo)
{
	system("cls");
	cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";

	if (vettorePW.size() != 0)
	{
		for (int i = 0; i < vettorePW.size(); i++)
		{
			cout << "[" + to_string(i+1) + "]" + ":\nPassword:\n" + vettorePW[i] + "\nInfo:\n" + vettoreInfo[i] + "\n";
		}
	}
	else cout << "\nDATI NON TROVATI\n";
}

void modifyData(string nonAshedPassword,string newPW, string newPwInfo) 
{
	aes.encodeText(newPW, nonAshedPassword, newPW);
	aes.encodeText(newPwInfo, nonAshedPassword, newPwInfo);
	sha.textString_to_SHA(nonAshedPassword);
	if (sendData("UPDATE////:" + nonAshedPassword + "&%#" + newPW + "&%#" + newPwInfo) == "SUCCESS") cout << "\nPassword updated successfully!";
	else cout << "\nSomething went wrong, unable to create account, please try again later";
	
}

void modifyPassword(int index, string nonAshedPassword, vector<string> vettorePW, vector<string> vettoreInfo)
{
	if(index < vettorePW.size())
	{
		system("cls");
		cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
		cout << "Enter your new password: ";
		string newPW;
		cin >> newPW;
		vettorePW[index] = newPW;
		modifyData(nonAshedPassword, newPW, vettoreInfo[index]);
	}
}

void modifyPasswordInfo(int index, string nonAshedPassword, vector<string> vettorePW, vector<string> vettoreInfo)
{
	if (index < vettorePW.size())
	{
		system("cls");
		cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
		cout << "Enter your new info: ";
		string newPW;
		cin >> newPW;
		vettoreInfo[index] = newPW;
		modifyData(nonAshedPassword, vettorePW[index], newPW);
	}
}

void displayOptions(string nonAshedPassword, vector<string> vettorePW, vector<string> vettoreInfo)
{
	cout << "\n\n[1] Modify password\n[2] Modify password info\n[3]Quit\n";
	string option;
	do
	{
		cin >> option;
	} while (option[0] < '1' || option[0] > '4');

	cout << "Enter the index of the password you intend to change: ";
	cin >> option;
	int inputInt = stoi(option) - 1;
	switch(option[0])
	{
	case '1':
		modifyPassword(inputInt, nonAshedPassword, vettorePW, vettoreInfo);
		break;
	case '2':
		modifyPasswordInfo(inputInt, nonAshedPassword, vettorePW, vettoreInfo);
		break;
	case '3':
		Quit();
		break;
	}
}

void Menù()
{
	string scelta;
	do
	{
		system("cls");
		cout << "*******************\n*  ONYON MANAGER  *\n*******************\n\n";
		cout << "[1] Login\n[2] Register\n[3] Quit\n";
		cin >> scelta;
		system("cls");
	} while (scelta[0] < '1' || scelta[0] > '3');
	switch (scelta[0])
	{
	case '1':
		Login();
		displayData();
		break;
	case '2':
		Register();
		break;
	case '3':
		Quit();
		return 0;
		break;
	}
}

int main() 
{
	
	vector<string> cryptedPW;
	vector<string> cryptedInfo;
	string username, password, LOGINDATA;
	

	
	
	system("pause");
	return 0;
}