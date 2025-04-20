#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

enum enMainMenuCommands
{
    ShowClients = 1,
    AddClient = 2,
    DeleteClient = 3,
    UpdateClient = 4,
    FindClient = 5,
    Transactions = 6,
    ManageUsers = 7,
    Logout = 8

};

enum enTransactionMenuCommands
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalances = 3,
    MainMenu = 4
};

enum enManageUsersMenuCommands
{
    ListUsers = 1,
    AddNewUser = 2,
    DeleteUser = 3,
    UpdateUser = 4,
    FindUser = 5,
    Main_Menu = 6
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

struct stPermissions
{
    bool ShowClients = false;
    bool AddClient = false;
    bool DeleteClient = false;
    bool UpdateClient = false;
    bool FindClient = false;
    bool Transactions = false;
    bool ManageUsers = false;
};

struct stUserData
{
    string Username;
    string Password;
    short PermissionsCode;
    stPermissions Permissions;
    bool MarkDelete = false;
};

void TransactionsMenuScreen(stUserData &User, vector<stUserData> &vUsers);

void MainMenuScreen(vector<stClientData> &vClients, vector<stUserData> &vUsers, stUserData &User);

void LoginScreen(vector<stClientData> &vClients, vector<stUserData> &vUsers);

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

stClientData ClientLineToRecord(string Line)
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

string ClientRecordToLine(stClientData stClient, string Delim = "#//#")
{
    string Line = "";
    Line += stClient.AccountNumber + Delim;
    Line += stClient.PinCode + Delim;
    Line += stClient.Name + Delim;
    Line += stClient.Phone + Delim;
    Line += to_string(stClient.AccountBalance);

    return Line;
}

vector<stClientData> ReadClientsDataFromFile(string ClientsFileName)
{
    fstream MyFile;
    string Line = "";
    stClientData Client;
    vector<stClientData> vClients;
    MyFile.open(ClientsFileName, ios::in);
    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            Client = ClientLineToRecord(Line);
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

void UpdateVectorToFile(vector<stClientData> &vClients, string ClientsFileName)
{
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::out);
    if (MyFile.is_open())
    {
        for (stClientData &Client : vClients)
        {
            if (Client.MarkDelete == false)
            {
                MyFile << ClientRecordToLine(Client) << "\n";
            }
        }
        MyFile.close();
    }
    else
    {
        cout << "Failed Opening file !\n";
    }
}

void AddElementToClientsFile(stClientData &Client, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::app);
    if (MyFile.is_open())
    {
        MyFile << ClientRecordToLine(Client) << endl;
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
        AddElementToClientsFile(NewClient, ClientsFileName);
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
    UpdateVectorToFile(vClients, ClientsFileName);
    vClients = ReadClientsDataFromFile(ClientsFileName);
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
    UpdateVectorToFile(vClients, ClientsFileName);
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
    UpdateVectorToFile(vClients, ClientsFileName);
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
    UpdateVectorToFile(vClients, ClientsFileName);
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
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "========================================\n";
}

void EndScreen()
{
    system("cls");
    cout << "========================================\n";
    cout << "Program ends :-)\n";
    cout << "========================================\n";
}

void AccessDeniedScreen()
{
    system("cls");
    cout << "\n------------------------------------------\n";
    cout << "Access Denied.\n";
    cout << "You don't have permission to do this!\n";
    cout << "Please contact your Admin.\n";
    cout << "------------------------------------------\n\n";
}

void PrintAllUsersDataScreen(vector<stUserData> &vUsers)
{
    system("cls");
    cout << "\n                                  User List (" << vUsers.size() << ") User(s).\n";
    cout << "____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(15) << "Password";
    cout << "| " << left << setw(18) << "Permissions" << endl;
    cout << "____________________________________________________________________________________________\n\n";
    for (stUserData &User : vUsers)
    {
        cout << "| " << left << setw(15) << User.Username;
        cout << "| " << left << setw(15) << User.Password;
        cout << "| " << left << setw(18) << User.PermissionsCode << endl;
    }
    cout << "\n____________________________________________________________________________________________\n\n";
}

bool DoesUserExist(vector<stUserData> &vUsers, stUserData &User)
{
    for (stUserData U : vUsers)
    {
        if (U.Username == User.Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

bool YNQuestion(string Question)
{
    char Reply;
    cout << Question << "  [Y/N]      ";
    cin >> Reply;
    return (toupper(Reply) == ('Y')) ? true : false;
}

stPermissions GiveFullAccess()
{
    stPermissions Permission;
    Permission.AddClient = true;
    Permission.DeleteClient = true;
    Permission.FindClient = true;
    Permission.ManageUsers = true;
    Permission.ShowClients = true;
    Permission.Transactions = true;
    Permission.UpdateClient = true;
    return Permission;
}

bool DoesUserHaveFullAccess(stPermissions &Permissions)
{
    if (Permissions.AddClient && Permissions.DeleteClient && Permissions.FindClient && Permissions.ManageUsers && Permissions.ShowClients && Permissions.Transactions && Permissions.UpdateClient)
    {
        return true;
    }
    return false;
}

short PermissionsStructToPermissionsCode(stPermissions &Permissions)
{
    short PermissionsCode = 0;
    if (DoesUserHaveFullAccess(Permissions))
    {
        return -1;
    }
    if (Permissions.ShowClients == true)
    {
        PermissionsCode += 1;
    }
    if (Permissions.AddClient == true)
    {
        PermissionsCode += 2;
    }
    if (Permissions.DeleteClient == true)
    {
        PermissionsCode += 4;
    }
    if (Permissions.UpdateClient == true)
    {
        PermissionsCode += 8;
    }
    if (Permissions.FindClient == true)
    {
        PermissionsCode += 16;
    }
    if (Permissions.Transactions == true)
    {
        PermissionsCode += 32;
    }
    if (Permissions.ManageUsers == true)
    {
        PermissionsCode += 64;
    }
    return PermissionsCode;
}

stPermissions ReadPermissions()
{
    stPermissions Permissions;
    if (YNQuestion("Do you want to give full access?"))
    {
        Permissions = GiveFullAccess();
    }
    else
    {
        cout << "\nDo you want to give access to : \n\n";
        if (YNQuestion("Show client list?"))
        {
            Permissions.ShowClients = true;
        }
        if (YNQuestion("Add new client?"))
        {
            Permissions.AddClient = true;
        }
        if (YNQuestion("Delete client?"))
        {
            Permissions.DeleteClient = true;
        }
        if (YNQuestion("Update client?"))
        {
            Permissions.UpdateClient = true;
        }
        if (YNQuestion("Find client?"))
        {
            Permissions.FindClient = true;
        }
        if (YNQuestion("Trancsaction?"))
        {
            Permissions.Transactions = true;
        }
        if (YNQuestion("Manage Users?"))
        {
            Permissions.ManageUsers = true;
        }
    }
    return Permissions;
}

stUserData ReadNewUserData(vector<stUserData> &vUsers)
{
    stUserData User;
    cout << "Enter UserName? ";
    getline(cin >> ws, User.Username);
    while (DoesUserExist(vUsers, User))
    {
        cout << "User with [" << User.Username << "] already exists, ";
        cout << "Enter UserName? ";
        getline(cin >> ws, User.Username);
    }
    cout << "Enter Password? ";
    getline(cin, User.Password);
    User.Permissions = ReadPermissions();
    User.PermissionsCode = PermissionsStructToPermissionsCode(User.Permissions);
    return User;
}

string UserRecordToLine(stUserData &User, string Delim = "#//#")
{
    string Line = "";
    Line += User.Username + Delim;
    Line += User.Password + Delim;
    Line += to_string(User.PermissionsCode);
    return Line;
}

void AddElementToUsersFile(stUserData &User, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::app);
    if (MyFile.is_open())
    {
        MyFile << UserRecordToLine(User) << endl;
        MyFile.close();
    }
    else
    {
        cout << "Failed Opening file !\n";
    }
}

void AddNewUserScreen(vector<stUserData> &vUsers)
{
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Add New Users Screen\n";
    cout << "------------------------------------\n";
    do
    {
        stUserData NewUser = ReadNewUserData(vUsers);
        vUsers.push_back(NewUser);
        AddElementToUsersFile(NewUser, UsersFileName);
        cout << "New User Added Successfully!  Do you want to add one more?[Y/N]    ";
    } while (Again() == true);
}

void PrintUserData(stUserData User)
{
    cout << "\n\nThe following are the User details: \n";
    cout << "-----------------------------------------------\n";
    cout << left << setw(18) << "Username: " << User.Username << "\n";
    cout << left << setw(18) << "Password: " << User.Password << "\n";
    cout << left << setw(18) << "Permissions: " << User.PermissionsCode << "\n\n";
    cout << "-----------------------------------------------\n\n";
}

stPermissions PermissionsCodeToPermissionsStruct(short PermissionsCode)
{
    stPermissions UserPermission;
    if (PermissionsCode == -1)
    {
        UserPermission.ShowClients = true;
        UserPermission.AddClient = true;
        UserPermission.DeleteClient = true;
        UserPermission.UpdateClient = true;
        UserPermission.FindClient = true;
        UserPermission.Transactions = true;
        UserPermission.ManageUsers = true;
    }
    else
    {
        if ((PermissionsCode & 1) == 1)
        {
            UserPermission.ShowClients = true;
        }
        if ((PermissionsCode & 2) == 2)
        {
            UserPermission.AddClient = true;
        }
        if ((PermissionsCode & 4) == 4)
        {
            UserPermission.DeleteClient = true;
        }
        if ((PermissionsCode & 8) == 8)
        {
            UserPermission.UpdateClient = true;
        }
        if ((PermissionsCode & 16) == 16)
        {
            UserPermission.FindClient = true;
        }
        if ((PermissionsCode & 32) == 32)
        {
            UserPermission.Transactions = true;
        }
        if ((PermissionsCode & 64) == 64)
        {
            UserPermission.ManageUsers = true;
        }
    }
    return UserPermission;
}

stUserData UserLineToRecord(string Line)
{
    vector<string> vUserData = SplitWords(Line);
    stUserData UserData;
    UserData.Username = vUserData[0];
    UserData.Password = vUserData[1];
    UserData.PermissionsCode = stoi(vUserData[2]);
    UserData.Permissions = PermissionsCodeToPermissionsStruct(UserData.PermissionsCode);

    return UserData;
}

vector<stUserData> ReadUsersDataFromFile(string UsersFileName)
{
    fstream MyFile;
    string Line = "";
    stUserData User;
    vector<stUserData> vUsers;
    MyFile.open(UsersFileName, ios::in);
    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            User = UserLineToRecord(Line);
            vUsers.push_back(User);
        }
        MyFile.close();
        return vUsers;
    }
    else
    {
        cout << "Failed Opening file !\n";
    }
}

void UpdateVectorToUsersFile(vector<stUserData> vUsers)
{
    fstream MyFile;
    MyFile.open(UsersFileName, ios::out);
    if (MyFile.is_open())
    {
        for (stUserData &User : vUsers)
        {
            if (User.MarkDelete == false)
            {
                MyFile << UserRecordToLine(User) << "\n";
            }
        }
        MyFile.close();
    }
    else
    {
        cout << "Failed Opening file !\n";
    }
}

void DeleteUserDataByUsername(vector<stUserData> &vUsers, string EnteredUsername)
{

    for (stUserData &User : vUsers)
    {
        if (User.Username == EnteredUsername)
        {
            User.MarkDelete = true;
            break;
        }
    }
    UpdateVectorToUsersFile(vUsers);
    vUsers = ReadUsersDataFromFile(UsersFileName);
}

void DeleteUserScreen(vector<stUserData> &vUsers)
{
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Delete User Screen\n";
    cout << "------------------------------------\n\n";
    stUserData User;
    cout << "Please enter Username?  ";
    getline(cin >> ws, User.Username);
    if (User.Username == "Admin")
    {
        cout << "Admin can't be deleted!!\n";
        return;
    }
    if (DoesUserExist(vUsers, User))
    {
        PrintUserData(User);
        cout << "Are you sure you want to delete this user?[Y/N]   ";
        if (Sure())
        {
            DeleteUserDataByUsername(vUsers, User.Username);
            cout << "\nUser Deleted Successfully!\n\n";
        }
    }
    else
    {
        cout << "Error!  [" << User.Username << "] Not Found!    \n";
    }
}

stUserData ReadUpdatedUserData(stUserData &User)
{
    cout << "Enter Password? ";
    getline(cin >> ws, User.Password);
    if (User.Username == "Admin")
        return User;
    User.Permissions = ReadPermissions();
    User.PermissionsCode = PermissionsStructToPermissionsCode(User.Permissions);
    return User;
}

void UpdateUserDataByUsername(vector<stUserData> &vUsers, string EnteredUsername)
{
    for (stUserData &User : vUsers)
    {
        if (User.Username == EnteredUsername)
        {
            User = ReadUpdatedUserData(User);
            break;
        }
    }
    UpdateVectorToUsersFile(vUsers);
}

void UpdateUserScreen(vector<stUserData> &vUsers)
{
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Update User Screen\n";
    cout << "------------------------------------\n\n";
    stUserData User;
    cout << "Please enter Username?  ";
    getline(cin >> ws, User.Username);
    if (DoesUserExist(vUsers, User))
    {
        PrintUserData(User);
        cout << "Are you sure you want to update this user?[Y/N]   ";
        if (Sure())
        {
            UpdateUserDataByUsername(vUsers, User.Username);
            cout << "\nUser Updated Successfully!\n\n";
        }
    }
    else
    {
        cout << "Error!  [" << User.Username << "] Not Found!    \n";
    }
}

void FindUserScreen(vector<stUserData> &vUsers)
{
    system("cls");
    cout << "\n------------------------------------\n";
    cout << "       Find User Screen\n";
    cout << "------------------------------------\n\n";
    stUserData User;
    cout << "Please enter Username?  ";
    getline(cin >> ws, User.Username);
    if (DoesUserExist(vUsers, User))
    {
        PrintUserData(User);
    }
    else
    {
        cout << "Error!  [" << User.Username << "] Not Found!    \n";
    }
}

void ManageUsersScreenInterface()
{
    cout << "\n=============================================\n";
    cout << "           Manage Users Menu Screen\n";
    cout << "=============================================\n";
    cout << "\t[1]List users.\n";
    cout << "\t[2]Add new user.\n";
    cout << "\t[3]Delete user.\n";
    cout << "\t[4]Update user.\n";
    cout << "\t[5]Find user.\n";
    cout << "\t[6]Main menu.\n";
    cout << "=============================================\n";
}

void ManageUsersScreen(vector<stClientData> &vClients, vector<stUserData> &vUsers, stUserData User)
{
    system("cls");
    ManageUsersScreenInterface();
    enManageUsersMenuCommands Command = enManageUsersMenuCommands(ReadCommand(1, 6));
    switch (Command)
    {
    case enManageUsersMenuCommands::ListUsers:
        PrintAllUsersDataScreen(vUsers);
        break;
    case enManageUsersMenuCommands::AddNewUser:
        AddNewUserScreen(vUsers);
        break;
    case enManageUsersMenuCommands::DeleteUser:
        DeleteUserScreen(vUsers);
        break;
    case enManageUsersMenuCommands::UpdateUser:
        UpdateUserScreen(vUsers);
        break;
    case enManageUsersMenuCommands::FindUser:
        FindUserScreen(vUsers);
        break;
    case enManageUsersMenuCommands::Main_Menu:
        MainMenuScreen(vClients, vUsers, User);
        break;
    }
    cout << "\n\nPress any key to go back to Manage Users Menu....\n";
    system("pause>0");
    ManageUsersScreen(vClients, vUsers, User);
}

void MainMenuScreen(vector<stClientData> &vClients, vector<stUserData> &vUsers, stUserData &User)
{
    system("cls");
    MainMenuInterface();
    enMainMenuCommands Command = enMainMenuCommands(ReadCommand(1, 8));
    switch (Command)
    {
    case enMainMenuCommands::ShowClients:
        if (User.Permissions.ShowClients == true)
        {
            PrintAllClientsDataScreen(vClients);
        }
        else
        {
            AccessDeniedScreen();
        }
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients, vUsers, User);
        break;
    case enMainMenuCommands::AddClient:
        if (User.Permissions.AddClient == true)
        {
            AddNewClientScreen(vClients);
        }
        else
        {
            AccessDeniedScreen();
        }
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients, vUsers, User);
        break;
    case enMainMenuCommands::DeleteClient:
        if (User.Permissions.DeleteClient == true)
        {
            DeleteClientScreen(vClients);
        }
        else
        {
            AccessDeniedScreen();
        }
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients, vUsers, User);
        break;
    case enMainMenuCommands::UpdateClient:
        if (User.Permissions.UpdateClient == true)
        {
            UpdateClientInfoScreen(vClients);
        }
        else
        {
            AccessDeniedScreen();
        }
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients, vUsers, User);
        break;
    case enMainMenuCommands::FindClient:
        if (User.Permissions.FindClient == true)
        {
            FindClientScreen(vClients);
        }
        else
        {
            AccessDeniedScreen();
        }
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients, vUsers, User);
        break;
    case enMainMenuCommands::Transactions:
        if (User.Permissions.Transactions == true)
        {
            TransactionsMenuScreen(User, vUsers);
        }
        else
        {
            AccessDeniedScreen();
        }
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients, vUsers, User);
        break;
    case enMainMenuCommands::ManageUsers:
        if (User.Permissions.ManageUsers)
        {
            ManageUsersScreen(vClients, vUsers, User);
        }
        else
        {
            AccessDeniedScreen();
        }
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        MainMenuScreen(vClients, vUsers, User);
        break;
    case enMainMenuCommands::Logout:
        LoginScreen(vClients, vUsers);
        break;
    }
}

void TransactionsMenuScreen(stUserData &User, vector<stUserData> &vUsers)
{
    vector<stClientData> vClients = ReadClientsDataFromFile(ClientsFileName);
    system("cls");
    PrintTransactionsMenuScreen();
    enTransactionMenuCommands Command = enTransactionMenuCommands(ReadCommand(1, 4));
    switch (Command)
    {
    case enTransactionMenuCommands::Deposit:
        DepositScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        TransactionsMenuScreen(User, vUsers);
        break;
    case enTransactionMenuCommands::Withdraw:
        WithdrawScreen(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        TransactionsMenuScreen(User, vUsers);
        break;
    case enTransactionMenuCommands::TotalBalances:
        PrintAllClientsBalances(vClients);
        cout << "Press any key to back to the main menu.....  ";
        system("pause>0");
        TransactionsMenuScreen(User, vUsers);
        break;
    case enTransactionMenuCommands::MainMenu:
        MainMenuScreen(vClients, vUsers, User);
        break;
    }
}

bool IsUserValid(vector<stUserData> &vUsers, string EnteredUsername, string EnteredPassword, stUserData &User)
{

    for (stUserData &C : vUsers)
    {
        if (C.Username == EnteredUsername)
        {
            if (C.Password == EnteredPassword)
            {
                User = C;
                return true;
            }
        }
    }
    return false;
}

void LoginHeadInterface()
{
    cout << "\n--------------------------------\n";
    cout << "          Login Screen\n";
    cout << "--------------------------------\n";
}

void LoginScreen(vector<stClientData> &vClients, vector<stUserData> &vUsers)
{
    system("cls");
    stUserData User;
    string UserName = "", Password = "";
    LoginHeadInterface();
    cout << "Enter Username?  ";
    cin >> UserName;
    cout << "Enter Password?  ";
    cin >> Password;
    while (!IsUserValid(vUsers, UserName, Password, User))
    {
        system("cls");
        LoginHeadInterface();
        cout << "Invalid Username/Password!\n";
        cout << "Entter Username?  ";
        cin >> UserName;
        cout << "Enter Password?  ";
        cin >> Password;
    }
    MainMenuScreen(vClients, vUsers, User);
}

int main()
{
    vector<stClientData> vClients = ReadClientsDataFromFile(ClientsFileName);
    vector<stUserData> vUsers = ReadUsersDataFromFile(UsersFileName);

    LoginScreen(vClients, vUsers);

    return 0;
}