#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const string FileName = "Clients.txt";

enum enMainMenuCommands
{
    ShowClients = 1,
    AddClient = 2,
    DeleteClient = 3,
    UpdateClient = 4,
    FindClient = 5,
    Transactions = 6,
    Exit = 7

};

enum enTransactionMenuCommands
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4
};

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkDelete = false;
};

void TransactionsMenuScreen();

short ReadCommand(short from, short to)
{
    short Num;
    cout << "Choose what you want to do? [" << from << " to " << to << "] ? ";
    cin >> Num;
    while (cin.fail() || Num > to || Num < from)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Wrong Command!  Please enter a valid Number\n";
        cin >> Num;
    }
    return Num;
}

vector<string> SplitWords(string Text, string Delim = "#//#")
{
    vector<string> vWords;
    int Pos = 0;
    string Word = "";
    while ((Pos = Text.find(Delim)) != std::string::npos)
    {
        Word = Text.substr(0, Pos);
        if (Word != "")
        {
            vWords.push_back(Word);
        }
        Text.erase(0, Pos + Delim.length());
    }
    if (Text != "")
    {
        vWords.push_back(Text);
    }
    return vWords;
}

stClientData LineToRecord(string Line)
{
    stClientData stClient;
    vector<string> SplittedData = SplitWords(Line);
    stClient.AccountNumber = SplittedData[0];
    stClient.PinCode = SplittedData[1];
    stClient.Name = SplittedData[2];
    stClient.Phone = SplittedData[3];
    stClient.AccountBalance = stod(SplittedData[4]);

    return stClient;
}

string RecordToLine(stClientData stClient, string Delim = "#//#")
{
    string Line = "";
    Line += stClient.AccountNumber + Delim;
    Line += stClient.PinCode + Delim;
    Line += stClient.Name + Delim;
    Line += stClient.Phone + Delim;
    Line += to_string(stClient.AccountBalance);

    return Line;
}

vector<stClientData> ReadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    string Line = "";
    stClientData Client;
    vector<stClientData> vClients;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            Client = LineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
        return vClients;
    }
    else
    {
        cout << "Failed Opening file !\n";
    }
}

void PrintAllClientsDataScreen(vector<stClientData> &vClients)
{
    system("cls");
    cout << "\n                                  Client List (" << vClients.size() << ") Client(s).\n";
    cout << "____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Nmuber";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(19) << "Client Name";
    cout << "| " << left << setw(13) << "Phone";
    cout << "| " << left << setw(6) << "Balance" << endl;
    cout << "____________________________________________________________________________________________\n\n";
    for (stClientData &Client : vClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(10) << Client.PinCode;
        cout << "| " << left << setw(19) << Client.Name;
        cout << "| " << left << setw(13) << Client.Phone;
        cout << "| " << left << setw(6) << Client.AccountBalance << endl;
    }
    cout << "\n____________________________________________________________________________________________\n\n";
}

void UpdateVectorToFile(vector<stClientData> &vClients, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (stClientData &Client : vClients)
        {
            if (Client.MarkDelete == false)
            {
                MyFile << RecordToLine(Client) << "\n";
            }
        }
        MyFile.close();
    }
    else
    {
        cout << "Failed Opening file !\n";
    }
}

void AddElementToFile(stClientData &Client, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::app);
    if (MyFile.is_open())
    {
        MyFile << RecordToLine(Client) << endl;
        MyFile.close();
    }
    else
    {
        cout << "Failed Opening file !\n";
    }
}

bool DoesClientExist(vector<stClientData> &vClients, string EnteredAccountNumber, stClientData &Client)
{
    for (stClientData &C : vClients)
    {
        if (C.AccountNumber == EnteredAccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

stClientData ReadNewClientData(vector<stClientData> &vClients)
{
    stClientData Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    while (DoesClientExist(vClients, Client.AccountNumber, Client))
    {
        cout << "Client with [" << Client.AccountNumber << "] already exists, ";
        cout << "Enter Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter Pin Code? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool Again()
{
    char Reply;
    cin >> Reply;
    return (toupper(Reply) == ('Y')) ? true : false;
}

void AddNewClientScreen(vector<stClientData> &vClients)
{
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Add New Clients Screen\n";
    cout << "------------------------------------\n";
    do
    {
        stClientData NewClient = ReadNewClientData(vClients);
        vClients.push_back(NewClient);
        AddElementToFile(NewClient, FileName);
        cout << "New Client Added Successfully!  Do you want to add one more?[Y/N]    ";
    } while (Again() == true);
}

void PrintClientData(stClientData &Client)
{
    cout << "The following are the client details: \n";
    cout << "-----------------------------------------------\n";
    cout << left << setw(18) << "Account Number: " << Client.AccountNumber << "\n";
    cout << left << setw(18) << "Pin Code: " << Client.PinCode << "\n";
    cout << left << setw(18) << "Client Name: " << Client.Name << "\n";
    cout << left << setw(18) << "Phone Number: " << Client.Phone << "\n";
    cout << left << setw(18) << "Account Balance: " << Client.AccountBalance << "\n";
    cout << "-----------------------------------------------\n\n";
}

void DeleteClientDataByAccountNumber(vector<stClientData> &vClients, string EnteredAccountNumber)
{

    for (stClientData &Client : vClients)
    {
        if (Client.AccountNumber == EnteredAccountNumber)
        {
            Client.MarkDelete = true;
            break;
        }
    }
    UpdateVectorToFile(vClients, FileName);
    vClients = ReadClientsDataFromFile(FileName);
}

bool Sure()
{
    return Again();
}

void DeleteClientScreen(vector<stClientData> &vClients)
{
    stClientData Client;
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Delete Client Screen\n";
    cout << "------------------------------------\n\n";
    string EnteredAccountNumber;
    cout << "Please enter Account Number?  ";
    getline(cin >> ws, EnteredAccountNumber);
    if (DoesClientExist(vClients, EnteredAccountNumber, Client))
    {
        PrintClientData(Client);
        cout << "Are you sure you want to delete this client?[Y/N]   ";
        if (Sure())
        {
            DeleteClientDataByAccountNumber(vClients, EnteredAccountNumber);
            cout << "\nClient Deleted Successfully!\n\n";
        }
    }
    else
    {
        cout << "Error!  [" << EnteredAccountNumber << "] Not Found!    \n";
    }
}

stClientData ReadUpdatedClientData(stClientData &Client)
{
    cout << "Enter Pin Code? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void UpdateClientData(vector<stClientData> &vClients, string EnteredAccountNumber)
{
    for (stClientData &Client : vClients)
    {
        if (Client.AccountNumber == EnteredAccountNumber)
        {
            Client = ReadUpdatedClientData(Client);
            break;
        }
    }
    UpdateVectorToFile(vClients, FileName);
}

void UpdateClientInfoScreen(vector<stClientData> &vClients)
{
    stClientData Client;
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Update Client Info Screen\n";
    cout << "------------------------------------\n\n";
    string EnteredAccountNumber;
    cout << "Please enter Account Number?  ";
    getline(cin >> ws, EnteredAccountNumber);
    if (DoesClientExist(vClients, EnteredAccountNumber, Client))
    {
        PrintClientData(Client);
        cout << "Are you sure you want to update this client?[Y/N]   ";
        if (Sure())
        {
            UpdateClientData(vClients, EnteredAccountNumber);
            cout << "\nClient Updated Successfully!\n\n";
        }
    }
    else
    {
        cout << "Error!  [" << EnteredAccountNumber << "] Not Found!      ";
    }
}

void FindClientScreen(vector<stClientData> &vClients)
{
    stClientData Client;
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Find Client Screen\n";
    cout << "------------------------------------\n\n";
    string EnteredAccountNumber;
    cout << "Please enter Account Number?  ";
    getline(cin >> ws, EnteredAccountNumber);
    if (DoesClientExist(vClients, EnteredAccountNumber, Client))
    {
        PrintClientData(Client);
    }
    else
    {
        cout << "Error!  [" << EnteredAccountNumber << "] Not Found!     ";
    }
}

void PrintTransactionsMenuScreen()
{
    cout << "========================================\n";
    cout << "             Transaction Menu Screen         \n";
    cout << "========================================\n";
    cout << "\t[1]Deposit.\n";
    cout << "\t[2]Withdraw.\n";
    cout << "\t[3]Total Balances\n";
    cout << "\t[4]Main Menu\n";
    cout << "========================================\n";
}

void PerformDeposit(vector<stClientData> &vClients, string AccountNumber, double Deposit, stClientData Client)
{
    for (stClientData &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance += Deposit;
            Client = C;
            break;
        }
    }
    UpdateVectorToFile(vClients, FileName);
    cout << "\nDeposit Performed Successfully!  your balance now = " << Client.AccountBalance << endl;
}

void DepositScreen(vector<stClientData> &vClients)
{

    system("cls");
    stClientData Client;
    cout << "\n------------------------------------\n";
    cout << "            Deposit Screen\n";
    cout << "------------------------------------\n\n";
    string AccountNumber;
    cout << "Please enter account number?  ";
    getline(cin >> ws, AccountNumber);
    while (DoesClientExist(vClients, AccountNumber, Client) == false)
    {
        cout << "\nClient with [" << AccountNumber << "] doesn't exist.\n\n";
        cout << "Please enter account number?  ";
        getline(cin >> ws, AccountNumber);
    }
    PrintClientData(Client);
    double Deposit;
    cout << "\nPlease enter deposit amount?   ";
    cin >> Deposit;
    cout << "Are you sure you want to perform this transaction? [Y/N]    ";
    if (Sure())
    {
        PerformDeposit(vClients, AccountNumber, Deposit, Client);
    }
}

void PerformWithdraw(vector<stClientData> &vClients, string AccountNumber, double Withdraw, stClientData Client)
{
    for (stClientData &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance -= Withdraw;
            Client = C;
            break;
        }
    }
    UpdateVectorToFile(vClients, FileName);
    cout << "Withdraw Performed Successfully!  your balance now = " << Client.AccountBalance << endl;
}

void WithdrawScreen(vector<stClientData> &vClients)
{

    system("cls");
    stClientData Client;
    cout << "\n------------------------------------\n";
    cout << "            Withdraw Screen\n";
    cout << "------------------------------------\n\n";
    string AccountNumber;
    cout << "Please enter account number?  ";
    getline(cin >> ws, AccountNumber);
    while (DoesClientExist(vClients, AccountNumber, Client) == false)
    {
        cout << "\nClient with [" << AccountNumber << "] doesn't exist.\n\n";
        cout << "Please enter account number?  ";
        getline(cin >> ws, AccountNumber);
    }
    PrintClientData(Client);
    double Withdraw;
    cout << "\nPlease enter withdraw amount?   ";
    cin >> Withdraw;
    while (Withdraw > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can only withdraw " << Client.AccountBalance << " or less\n";
        cout << "\nPlease enter withdraw amount?   ";
        cin >> Withdraw;
    }
    cout << "Are you sure you want to perform this transaction? [Y/N]    ";
    if (Sure())
    {
        PerformWithdraw(vClients, AccountNumber, Withdraw, Client);
    }
}

double SumTotalBalances(vector<stClientData> &vClients)
{
    double Sum = 0;
    for (stClientData &Client : vClients)
    {
        Sum += Client.AccountBalance;
    }
    return Sum;
}

void PrintAllClientsBalances(vector<stClientData> &vClients)
{
    system("cls");
    cout << "\n                                  Client List (" << vClients.size() << ") Client(s).\n";
    cout << "____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Nmuber";
    cout << "| " << left << setw(19) << "Client Name";
    cout << "| " << left << setw(6) << "Balance" << endl;
    cout << "____________________________________________________________________________________________\n\n";
    for (stClientData &Client : vClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(19) << Client.Name;
        cout << "| " << left << setw(6) << Client.AccountBalance << endl;
    }
    cout << "\n____________________________________________________________________________________________\n\n";

    cout << "\t\t\t\t Total Balances = " << SumTotalBalances(vClients) << "\n\n";
}

void MainMenuInterface()
{

    cout << "========================================\n";
    cout << "             Main Menu Screen         \n";
    cout << "========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "========================================\n";
}

void EndScreen()
{
    system("cls");
    cout << "========================================\n";
    cout << "Program ends :-)\n";
    cout << "========================================\n";
}

void MainMenuScreen(vector<stClientData> &vClients)
{
    system("cls");
    MainMenuInterface();
    enMainMenuCommands Command = enMainMenuCommands(ReadCommand(1, 7));
    switch (Command)
    {
    case enMainMenuCommands::ShowClients:
        PrintAllClientsDataScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients);
        break;
    case enMainMenuCommands::AddClient:
        AddNewClientScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients);
        break;
    case enMainMenuCommands::DeleteClient:
        DeleteClientScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients);
        break;
    case enMainMenuCommands::UpdateClient:
        UpdateClientInfoScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients);
        break;
    case enMainMenuCommands::FindClient:
        FindClientScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients);
        break;
    case enMainMenuCommands::Transactions:
        TransactionsMenuScreen();
        break;
    case enMainMenuCommands::Exit:
        EndScreen();
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        return;
        break;
    }
}

void TransactionsMenuScreen()
{
    vector<stClientData> vClients = ReadClientsDataFromFile(FileName);
    system("cls");
    PrintTransactionsMenuScreen();
    enTransactionMenuCommands Command = enTransactionMenuCommands(ReadCommand(1, 4));
    switch (Command)
    {
    case enTransactionMenuCommands::Deposit:
        DepositScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        TransactionsMenuScreen();
        break;
    case enTransactionMenuCommands::Withdraw:
        WithdrawScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        TransactionsMenuScreen();
        break;
    case enTransactionMenuCommands::TotalBalances:
        PrintAllClientsBalances(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        TransactionsMenuScreen();
        break;
    case enTransactionMenuCommands::MainMenu:
        MainMenuScreen(vClients);
        break;
    }
}

int main()
{
    vector<stClientData> vClients = ReadClientsDataFromFile(FileName);
    MainMenuScreen(vClients);
}
