#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
#include<cctype>

using namespace std;

const string ClientsFileName = "Clients.txt";

struct sClient {
	string AccountNumber = "";
	string Pincode = "";
	string FullName = "";
	string PhneNumber = "";
	double AccountPalance;
	bool MarkForDelete = false;

};

vector<string> SplitString(string s1, string sepretur) {
	vector<string>vstring;
	short pos = 0;
	string sword = "";

	while ((pos = s1.find(sepretur)) != std::string::npos) {
		sword = s1.substr(0, pos);
		if (sword != "") {
			vstring.push_back(sword);
		}
		s1.erase(0, pos + sepretur.length());
	}
	if (s1 != "") {
		vstring.push_back(s1);
	}

	return vstring;
}

sClient ConvirdLineRecord(string stline, string seperatur = "#//#") {

	sClient lien;

	vector<string>vstring = SplitString(stline, seperatur);
	lien.AccountNumber = vstring[0];
	lien.Pincode = vstring[1];
	lien.FullName = vstring[2];
	lien.PhneNumber = vstring[3];
	lien.AccountPalance = stod(vstring[4]);

	return lien;
}

vector <sClient>LoadClientsDataFromFile(string FileName) {
	vector<sClient>vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		string line;
		sClient Client;

		while (getline(MyFile, line)) {

			Client = ConvirdLineRecord(line);

			vClient.push_back(Client);
		}
		MyFile.close();
	}

	return vClient;
}

enum enMinMinueOpshin {
	eListClients = 1, eAddNewClint = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5,TranseAction=6, eExit = 7
};

void ShawMainMinue();
void ShowTranseAction();
short ReadMainMinueOpshin(short from,short to) {
	short opshin = 0;
	do {

		cout << "Choose What Do You Want To Do   ["<<from<<" to " <<to <<"]  :";
		cin >> opshin;

	} while (opshin < from && opshin > to);

	return opshin;
}

void GoToBagMinueScreen() {

	cout << "\n\nPress Any Key To Go Back main minue...";
	system("pause>0");
	ShawMainMinue();
}

void GoToBagTransactionMinue() {

	cout << "\n\nPress Any Key To Go Back Transaction main minue...";
	system("pause>0");
	ShowTranseAction();
}


void PrintClientsRecord(sClient Client)
{
	cout << "|  " << setw(15) << left << Client.AccountNumber;
	cout << "|  " << setw(10) << left << Client.Pincode;
	cout << "|  " << setw(40) << left << Client.FullName;
	cout << "|  " << setw(12) << left << Client.PhneNumber;
	cout << "|  " << setw(12) << left << Client.AccountPalance;
}



void ShowAllClintsDataScreen() {

	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "=================================================\n"
		<< "Show All Clints Data Screen"
		<< "\n=================================================\n";

	cout << "\n\t\t\t\t\t Client List  (" << vClients.size() << ") Clients (S).";
	cout << "\n-------------------------------------------------------------";
	cout << "---------------------------------------\n" << endl;

	cout << "|  " << left << setw(15) << "Accont Number";
	cout << "|  " << left << setw(10) << "Pin Code";
	cout << "|  " << left << setw(40) << "Client Name";
	cout << "|  " << left << setw(12) << "Phone Number";
	cout << "|  " << left << setw(12) << "Accont Balance";

	cout << "\n-------------------------------------------------------------";
	cout << "---------------------------------------\n" << endl;

	if (vClients.size() == 0) {
		cout << "\t\t\tNo Clients Available In The System... !";
	}

	else {
		for (sClient Client : vClients) {
			PrintClientsRecord(Client);
			cout << endl;
		}
	}
	cout << "\n-------------------------------------------------------------";
	cout << "---------------------------------------\n" << endl;
}

bool ClientExistsByAccountNumber(string AccountNumber, string filename) {

	vector<sClient>vClients;
	fstream MyFile;
	MyFile.open(filename, ios::in);
	if (MyFile.is_open()) {
		string line;
		sClient client;

		while (getline(MyFile, line)) {
			client = ConvirdLineRecord(line);
			if (client.AccountNumber == AccountNumber) {
				
				MyFile.close();
				return true;
			}
			vClients.push_back(client);
		}
		MyFile.close();
	}
	return false;
}

sClient ReadNewClient() {
	sClient client;

	cout << "\n please enter AccountNumber  :?";
	getline(cin >> ws, client.AccountNumber);
	while (ClientExistsByAccountNumber(client.AccountNumber, ClientsFileName))
	{
		cout << "\nclient with [" << client.AccountNumber << "] alridy exists , Enter another account number....\n";
		getline(cin >> ws, client.AccountNumber);
	}
	cout << "\n please enter Pincode  :";
	getline(cin, client.Pincode);
	cout << "\n please enter FullName  :";
	getline(cin, client.FullName);
	cout << "\n please enter PhneNumber  :";
	getline(cin, client.PhneNumber);
	cout << "\n please enter AccountPalance  :";
	cin >> client.AccountPalance;

	return client;

}

void AddDataLineToFile(string FileName, string StClient) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << StClient << endl;
		MyFile.close();

	}
}

string ConvirtRecordToLine(sClient Client, string seperater = "#//#") {
	string stClintRecord = "";

	stClintRecord += Client.AccountNumber + seperater;
	stClintRecord += Client.Pincode + seperater;
	stClintRecord += Client.FullName + seperater;
	stClintRecord += Client.PhneNumber + seperater;
	stClintRecord += to_string(Client.AccountPalance);

	return stClintRecord;
}

void AddNewClient() {

	sClient Clients;
	Clients = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvirtRecordToLine(Clients));
}

void AddNewClients() {
	char AddMore = 'y';
	do {

		cout << "\n\tAdding New Client ...\n\n";
		AddNewClient();
		cout << "\nAdded Client saccessfuly , do you want add more clients :.y/n ? ";
		cin >> AddMore;

	} while (tolower(AddMore) == 'y');

}

void ShowAddClintsDataScreen() {

	

	cout << "=================================================\n"
		<< "Show Add Clints Data Screen"
		<< "\n=================================================\n";
	
	AddNewClients();

}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>vClient, sClient& Client) {

	//vector<SClient>vClient = LoadClientsDataFromFile("Clients.txt");

	for (sClient &C : vClient) {

		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	
	}
	return false;
}


bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClient) {

	for (sClient& C : vClient) {
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;

		}
		
	}
	return false;
}

vector<sClient> SaveClientDataToFile(string FileName, vector<sClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		string DataLine;

		for (sClient c : vClients) {

			if (c.MarkForDelete == false) {
				DataLine = ConvirtRecordToLine(c);

				MyFile << DataLine << endl;

			}
		}

		MyFile.close();

	}
	return vClients;

}

void PrintClientsWhoFind(sClient Client) {
	cout << "\nThe folowing  are client detalis is   :\n";

	cout << "\nAccount Number   :" << Client.AccountNumber;
	cout << "\nPincode          :" << Client.Pincode;
	cout << "\nFull Name        :" << Client.FullName;
	cout << "\nPhne Number      :" << Client.PhneNumber;
	cout << "\nAccount Palance  :" << Client.AccountPalance;



}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClient) {
	sClient Client;
	char Answere = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {

		PrintClientsWhoFind(Client);

		cout << "\n\n are sure you Want Delete This Client ?vy/n ? ";
		cin >> Answere;
		if (tolower(Answere) == 'y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
			SaveClientDataToFile(ClientsFileName, vClient);

			vClient = LoadClientsDataFromFile("Clients.txt");

			return true;
		}
	}
	else
	{
		cout << "\n Client With Account Number  (" << AccountNumber << ") is Not Found!";

		return false;
	}

}

string ReadAccountNumber() {
	string accountnumber = "";
	cout << "enter account number please :";
	cin >> accountnumber;
	return accountnumber;
}

void ShowDeleteClintsDataScreen() {

	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "=================================================\n"
		<< "Show Delete Clints Data Screen"
		<< "\n=================================================\n";
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

sClient ChangeClientRecord(string AccountNumber) {

	sClient client;
	client.AccountNumber = AccountNumber;

	cout << "\n please enter Pincode  :";
	getline(cin >> ws, client.Pincode);
	cout << "\n please enter FullName  :";
	getline(cin, client.FullName);
	cout << "\n please enter PhneNumber  :";
	getline(cin, client.PhneNumber);
	cout << "\n please enter AccountPalance  :";
	cin >> client.AccountPalance;

	return client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClient) {
	sClient Client;
	char Answere = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {

		PrintClientsWhoFind(Client);

		cout << "\n\n are sure you Want Update This Client ?vy/n ? ";
		cin >> Answere;
		if (tolower(Answere) == 'y') {

			for (sClient& C : vClient) {

				if (C.AccountNumber == AccountNumber) {

					C = ChangeClientRecord(AccountNumber);
					break;

				}

			}
			SaveClientDataToFile(ClientsFileName, vClient);

			cout << "\n\n Client Updated Successfully. ";
			return true;
		}
	}
	else
	{
		cout << "\n Client With Account Number  (" << AccountNumber << ") is Not Found!";

		return false;
	}

}

void ShowUpdateClintsDataScreen() {
	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "=================================================\n"
		<< "Show Update Clints Data Screen"
		<< "\n=================================================\n";
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClintsDataScreen() {

	cout << "=================================================\n"
		<< "Show Find Clints Data Screen"
		<< "\n=================================================\n";

	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
    sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {

		PrintClientsWhoFind(Client);
	}
	else
	{
		cout << "\n Client With Account Number  (" << AccountNumber << ") is Not Found!";

	}

}

void GoToEndMinueScreen() {
	cout << "=================================================\n"
		<< "Programe End -)................."
		<< "\n=================================================\n";
}
enum enTransaction {
    Deposit= 1,Withdrow=2,
	TotalBalance=3,MainMinue=4

};

double ReadClientntBalance() {
	double balance = 0;

	cout << "\n\nplease enter palance   :";
	cin >> balance;

	return balance;
}

bool BisinaseTransactionDeposit(string AccountNumber, vector<sClient>& vClient) {

	sClient Client;
	char Answere = 'n';
	double balance;

	if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {

		PrintClientsWhoFind(Client);

		balance = ReadClientntBalance();


		/*if (balance > Client.AccountPalance)
		{
			cout << "your balance is not enough to complete this process.... \n";
			balance = ReadClientntBalance();

		}*/


		cout << "\n\n are sure you Want Update This Client ?y/n ? ";
		cin >> Answere;
		if (tolower(Answere) == 'y') {

			for (sClient& C : vClient) {

				if (C.AccountNumber == AccountNumber) {

					C.AccountPalance += balance;

				}

			}
			SaveClientDataToFile(ClientsFileName, vClient);

			cout << "\n\n the operation was successful (-: ";
			return true;
		}
	}
	else
	{
		cout << "\n Client With Account Number  (" << AccountNumber << ") is Not Found!";

		return false;
	}
}

void DepositScreen() {

	cout << "=================================================\n"
		<< "\t Deposit Screen "
		<< "\n=================================================\n";

	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	sClient Client;

		BisinaseTransactionDeposit(AccountNumber, vClients);



}

bool BisinaseTransactionWithDrow(string AccountNumber, vector<sClient>& vClient) {

	sClient Client;
	char Answere = 'n';
	double balance;

	if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {

		PrintClientsWhoFind(Client);

		do {
			balance = ReadClientntBalance();

			if (balance > Client.AccountPalance) {

				cout << "your balance is not enough to complete this process.... \n";

				balance = ReadClientntBalance();
			}

		} while (balance > Client.AccountPalance);
		
			
		cout << "\n\n are sure you Want Update This Client ?y/n ? ";
		cin >> Answere;
		if (tolower(Answere) == 'y') {

			for (sClient& C : vClient) {

				if (C.AccountNumber == AccountNumber) {

					C.AccountPalance -= balance;

				}

			}
			SaveClientDataToFile(ClientsFileName, vClient);

			cout << "\n\n the operation was successful (-: ";
			return true;
		}
	}
	else
	{
		cout << "\n Client With Account Number  (" << AccountNumber << ") is Not Found!";

		return false;
	}
}

void WithDrowScreen()
{
	cout << "=================================================\n"
		<< "\t WithDrow Screen "
		<< "\n=================================================\n";

	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();
	sClient Client;

		BisinaseTransactionWithDrow(AccountNumber, vClients);
	
}

void PrintTotalBalanceClientsRecord(sClient Client)
{
	cout << "|  " << setw(15) << left << Client.AccountNumber;
	
	cout << "|  " << setw(40) << left << Client.FullName;
	
	cout << "|  " << setw(12) << left << Client.AccountPalance;
}

double SumTotalBalance(vector<sClient>vClient)
{
	double Sum = 0;
	sClient C;
	for (sClient C:vClient) {
		Sum += C.AccountPalance;
	}
	return Sum;
}

void TotalBalanceScreen() {

	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);

	cout << "=================================================\n"
		<< "Show Total Balance Data Screen"
		<< "\n=================================================\n";

	cout << "\n\t\t\t\t\t Client List  (" << vClients.size() << ") Clients (S).";
	cout << "\n-------------------------------------------------------------";
	cout << "---------------------------------------\n" << endl;

	cout << "|  " << left << setw(15) << "Accont Number";
	
	cout << "|  " << left << setw(40) << "Client Name";
	
	cout << "|  " << left << setw(12) << "Accont Balance";

	cout << "\n-------------------------------------------------------------";
	cout << "---------------------------------------\n" << endl;

	if (vClients.size() == 0) {
		cout << "\t\t\tNo Clients Available In The System... !";
	}

	else {
		for (sClient &Client : vClients) {
			PrintTotalBalanceClientsRecord(Client);
			cout << endl;
		}
	}
	cout << "\n-------------------------------------------------------------";
	cout << "---------------------------------------\n" << endl;

	cout << "\n\t\t\t\t\t Total Balance  = " << SumTotalBalance(vClients);
}

void PerformTransactionMainMenueOpshin(enTransaction transaction) {
	switch (transaction)
	{
	case enTransaction::Deposit:
	{
		system("cls");

		DepositScreen();

		GoToBagTransactionMinue();

		break;
	}
	case enTransaction::Withdrow:
	{
		system("cls");

		WithDrowScreen();

		GoToBagTransactionMinue();

		break;
	}
	case enTransaction::TotalBalance:
	{
		system("cls");

		TotalBalanceScreen();

		GoToBagTransactionMinue();

		break;
	}
	case enTransaction::MainMinue:
	{

		system("cls");

		GoToBagMinueScreen();

		break;
	}
	default:
		break;
	}
}

void ShowTranseAction() {
	system("cls");
	cout << "================================================\n"
		<< "\t\t TRANSACTION MINUE SCREEN      "
		<< "\n================================================\n"
		<< "Deposit : [1] \n"
		<< "WithDrow : [2] \n"
		<< "Total Balance: [3] \n"
		<< "Main Minue Screen : [4] \n"
		<< "---------------------------------------------------------------------\n";

	PerformTransactionMainMenueOpshin((enTransaction)ReadMainMinueOpshin(1,4));
}
void PerformMainMenueOpshin(enMinMinueOpshin mainminueopshin) {

	switch (mainminueopshin)
	{
	case enMinMinueOpshin::eListClients:
	{
		system("cls");
		ShowAllClintsDataScreen();
		GoToBagMinueScreen();
		break;
	}
	case enMinMinueOpshin::eAddNewClint:
	{
		system("cls");
		ShowAddClintsDataScreen();
		GoToBagMinueScreen();

		break;
	}
	case enMinMinueOpshin::eDeleteClient:
	{
		system("cls");
		ShowDeleteClintsDataScreen();
		GoToBagMinueScreen();
		break;
	}
	case enMinMinueOpshin::eUpdateClient:
	{
		system("cls");
		ShowUpdateClintsDataScreen();
		GoToBagMinueScreen();
		break;
	}
	case enMinMinueOpshin::eFindClient:
	{
		system("cls");
		ShowFindClintsDataScreen();
		GoToBagMinueScreen();
		break;
	}
	case enMinMinueOpshin::TranseAction:
	{
		system("cls");
		ShowTranseAction();
		GoToBagMinueScreen();
		break;
	}
	case enMinMinueOpshin::eExit:
		{
		system("cls");
		GoToEndMinueScreen();
		break;
	}
	default:
		break;
	}

}

void ShawMainMinue() {

	system("cls");
	cout << "================================================\n"
		<< "\t\t MIN MINUE SCREEN      "
		<< "\n================================================\n"
		<< "Show All Clints Data Screen : [1] \n"
		<< "Show Add Clints Data Screen : [2] \n"
		<< "Show Delete Clints Data Screen : [3] \n"
		<< "Show Update Clints Data Screen : [4] \n"
		<< "Show Find Clints Data Screen : [5] \n"
		<<"Trans Action : [6] \n"
		<< "Exit Screen : [7] \n"
		<< "---------------------------------------------------------------------\n";

	PerformMainMenueOpshin((enMinMinueOpshin)ReadMainMinueOpshin(1,7));
}

int main() {
	ShawMainMinue();

	system("pause>0");

	return 0;
}