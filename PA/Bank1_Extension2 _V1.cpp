#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int UserLoginPermissions = 0;

const string ClientsFileName = "Clients.txt";
void ShowUsersMenue();
void Login();
void ShowMainMenue();
void ShowTransactionsMenue();
void AccessDenied();



struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAllClientsScreen()
{


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{


    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }

}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, 
    eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6, eUserManage = 7 , eLogout = 8 };

// Permissions
enum ePermissions
{
    Show = 1,
    Add = 2,
    Delete = 4,
    Update = 8,
    Find = 16,
    Transactions = 32,
    User = 64
};



void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();

}
void GoBackToUserMenue()
{
    cout << "\n\nPress any key to go back to Manage Users Menue...";
    system("pause>0");
    ShowUsersMenue();

}


short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue();

    }
    }

}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    // UserLoginPermissions
    // ePermissions
    // AccessDenied();
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        if (UserLoginPermissions == -1 || (UserLoginPermissions & ePermissions::Show) == ePermissions::Show)
        {
            system("cls");
            ShowAllClientsScreen();
            GoBackToMainMenue();
            break;
        }
        else
        {
            system("cls");
            AccessDenied();
            GoBackToMainMenue();

            break;

        }
    }
    case enMainMenueOptions::eAddNewClient:
    {
        if (UserLoginPermissions == -1 || (UserLoginPermissions & ePermissions::Add) == ePermissions::Add)
        {
            system("cls");
            ShowAddNewClientsScreen();
            GoBackToMainMenue();
            break;
        }
        else
        {
            system("cls");
            AccessDenied();
            GoBackToMainMenue();
            break;

        }

    }
    case enMainMenueOptions::eDeleteClient:
    {
        if (UserLoginPermissions == -1 || (UserLoginPermissions & ePermissions::Delete) == ePermissions::Delete)
        {
            system("cls");
            ShowDeleteClientScreen();
            GoBackToMainMenue();
            break;
        }
        else
        {
            system("cls");
            AccessDenied();
            GoBackToMainMenue();

            break;
        }

    }

    case enMainMenueOptions::eUpdateClient:
    {
        if (UserLoginPermissions == -1 || (UserLoginPermissions & ePermissions::Update) == ePermissions::Update)
        {
            system("cls");
            ShowUpdateClientScreen();
            GoBackToMainMenue();
            break;
        }
        else
        {
            system("cls");
            AccessDenied();
            GoBackToMainMenue();

            break;

        }

    }

    case enMainMenueOptions::eFindClient:
    {
        if (UserLoginPermissions == -1 || (UserLoginPermissions & ePermissions::Find) == ePermissions::Find)
        {
            system("cls");
            ShowFindClientScreen();
            GoBackToMainMenue();
            break;
        }
        else
        {
            system("cls");
            AccessDenied();
            GoBackToMainMenue();

            break;
        }

    }

    case enMainMenueOptions::eShowTransactionsMenue:
    {
        if (UserLoginPermissions == -1 || (UserLoginPermissions & ePermissions::Transactions) == ePermissions::Transactions)
        {
            system("cls");
            ShowTransactionsMenue();
            GoBackToMainMenue();
            break;
        }
        else
        {
            system("cls");
            AccessDenied();
            GoBackToMainMenue();

            break;
        }
    }

    case enMainMenueOptions::eUserManage:
    {
        if (UserLoginPermissions == -1 || (UserLoginPermissions & ePermissions::User) == ePermissions::User)
        {
            system("cls");
            ShowUsersMenue();
            GoBackToMainMenue();
            break;
        }
        else
        {
            system("cls");
            AccessDenied();
            GoBackToMainMenue();

            break;
        }

    }
    case enMainMenueOptions::eLogout:
        system("cls");
        Login();
        break;
    }

}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] User Management.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

//// V3
// Login


struct SUserNsme
{
    string UserName, Password;
    int UserPermissions;

};



vector <string> LoadUsersFromFile(string FileName = "User.txt")
{
    vector <string> StLogin;

    fstream Myfile;
    Myfile.open(FileName, ios::in);

    if (Myfile.is_open())
    {
        string line;
        while (getline(Myfile, line))
        {
            StLogin.push_back(line);
        }
        Myfile.close();
    }

    return StLogin;
}


SUserNsme SplitStringToUserName(string Login)
{
    SUserNsme User;
    int pos;

    pos = Login.find("#//#");
    User.UserName = Login.substr(0, pos);
    Login.erase(0, pos + 4);

    pos = Login.find("#//#");
    User.Password = Login.substr(0, pos);
    Login.erase(0, pos + 4);

    User.UserPermissions = stoi(Login);

    return User;

}
vector<SUserNsme> LoadUserToUserNameStruct()
{
    vector <string> Login = LoadUsersFromFile();
    vector<SUserNsme> Users;
    for (string U : Login)
    {
        Users.push_back(SplitStringToUserName(U));
    }
    return Users;
}


bool ISCorrectLogin(SUserNsme UserLogin)
{
    vector <SUserNsme> Users = LoadUserToUserNameStruct();

    for (SUserNsme U : Users)
    {
        if (UserLogin.UserName == U.UserName)
        {
            if (UserLogin.Password == U.Password)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}



void LoginScreen()
{
    cout << "\n---------------------------------------\n";
    cout << "\t\t Login Screen .\n";
    cout << "---------------------------------------\n";


}


// Show User List

void PrintUser(SUserNsme user)
{
    cout << endl << "| " << left << setw(18) << user.UserName;
    cout << "| " << left << setw(18) << user.Password;
    cout << "| " << left << setw(18) << user.UserPermissions << endl;
}
void ShowUserList()
{
    vector <SUserNsme> Users = LoadUserToUserNameStruct();
    cout << "\n\t\t\t\t\t\ User List (" << Users.size() << ") Users. \n";
    cout << "_____________________________________________________________________________________________________\n" << endl;
    cout << left << setw(20) << "| User Name ";
    cout << left << setw(20) << "| Passord";
    cout << left << setw(20) << "| User Permissions\n";
    cout << "\n_____________________________________________________________________________________________________" << endl;
    for (SUserNsme User : Users)
        PrintUser(User);
    cout << "\n_____________________________________________________________________________________________________" << endl;
}

// Find User
string ReadFindUseer()
{
    string User;
    cout << "Please Enter User Name : ";
    cin >> User;

    return User;
}
void PrintUserFound(SUserNsme User)
{
    cout << endl  << "the following user details : \n" << endl;
    cout << "User Name         : " << User.UserName << endl;
    cout << "Password          : " << User.Password << endl;
    cout << "User Permissions  : " << User.UserPermissions << endl;
}
bool IsFoundUser(SUserNsme& FoundUser, string UserName)
{
    vector <SUserNsme> Users = LoadUserToUserNameStruct();

    for (SUserNsme U : Users)
    {
        if (U.UserName == UserName)
        {
            FoundUser = U;
            return true;
        }
    }
    return false;
}

void FindUserScreen()
{
    SUserNsme User;
    cout << "\n_______________________________________________________" << endl;
    cout  << "\t\t\t\t Find User Screen . " << endl;
    cout << "_______________________________________________________" << endl;

    string UserName = ReadFindUseer();
    while (!IsFoundUser(User, UserName))
    {
        cout << "\nThis user does not exist, please enter another user . " << endl;
        UserName = ReadFindUseer();
    }
    PrintUserFound(User);
}

//User Management"
SUserNsme ReadUser()
{
    SUserNsme UserName;
    cout << "Enter UserName : ";
    getline(cin >> ws, UserName.UserName);

    cout << "Enter Password : ";
    getline(cin >> ws, UserName.Password);

    return UserName;
}


void Login()
{
    LoginScreen();
    SUserNsme UserLogin = ReadUser();
    while (!ISCorrectLogin(UserLogin))
    {
        system("CLS");
        LoginScreen();
        cout << "invalid Username or password \n";

        UserLogin = ReadUser();

    }

    IsFoundUser(UserLogin, UserLogin.UserName);
    UserLoginPermissions = UserLogin.UserPermissions;
    ShowMainMenue();

}


void AccessDenied()
{
    cout << endl << "------------------------------------------------" << endl;
    cout << "Access denied" << endl;
    cout << "You do not have permission to do this." << endl;
    cout << "Contact admin." << endl;
    cout << endl << "------------------------------------------------" << endl;
}
enum  eUserMenueOpitions
{
    eListUser = 1,
    eAddtUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFineUser = 5,
    eMainUser = 6,
};
short ReadMainUserption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}


/*
        [1] Show Client List.
        [2] Add New Client.
        [3] Delete Client.
        [4] Update Client Info.
        [5] Find Client.
        [6] Transactions.
        [7] User Management.
        [8] Logout.
*/


// Add New User.
void ReadPermissions(SUserNsme& UserName)
{
    char FullAccess;
    cout << "Do You Want Give To Full Access?  y/n ? :";
    cin >> FullAccess;

    UserName.UserPermissions = 0;
    if (FullAccess == 'Y' || FullAccess == 'y')
    {
        UserName.UserPermissions = -1;
    }
    else
    {
        cout << "Do You Want Give To Access : " << endl;;

        cout << "Show Client List y/n?  ";
        cin >> FullAccess;
        if (FullAccess == 'Y' || FullAccess == 'y')
            UserName.UserPermissions |= ePermissions::Show;

        cout << "Add New Client. y/n?  ";
        cin >> FullAccess;
        if (FullAccess == 'Y' || FullAccess == 'y')
            UserName.UserPermissions |= ePermissions::Add;

        cout << "Delete Client. y/n?  ";
        cin >> FullAccess;
        if (FullAccess == 'Y' || FullAccess == 'y')
            UserName.UserPermissions |= ePermissions::Delete;


        cout << "Update Client. y/n?  ";
        cin >> FullAccess;
        if (FullAccess == 'Y' || FullAccess == 'y')
            UserName.UserPermissions |= ePermissions::Update;

        cout << "Find Client. y/n?  ";
        cin >> FullAccess;
        if (FullAccess == 'Y' || FullAccess == 'y')
            UserName.UserPermissions |= ePermissions::Find;

        cout << "Transactions Client. y/n?  ";
        cin >> FullAccess;
        if (FullAccess == 'Y' || FullAccess == 'y')
            UserName.UserPermissions |= ePermissions::Transactions;

        cout << "Mange  User. y/n?  ";
        cin >> FullAccess;
        if (FullAccess == 'Y' || FullAccess == 'y')
            UserName.UserPermissions |= ePermissions::User;

    }
}

SUserNsme ReadNewUserName()
{
    SUserNsme UserName;
    cout << "Enter UserName : ";
    getline(cin >> ws, UserName.UserName);

    while (IsFoundUser(UserName, UserName.UserName))
    {
        cout << endl << "\a";
        cout << "{ " << UserName.UserName << " } user already exists" << endl;
        cout << "Enter Another UserName : ";
        getline(cin, UserName.UserName);
    }
    cout << "Enter Password : ";
    getline(cin >> ws, UserName.Password);

    return UserName;
}
string ConvertRecordToLine(SUserNsme User)
{
    string Line;
    Line = User.UserName + "#//#";
    Line += User.Password + "#//#";
    Line += to_string(User.UserPermissions);

    return Line;
}
void ShowAddUserScreen()
{
    cout << "\n_____________________________________________\n";
    cout << "\t\t Add New User Screen . " << endl;
    cout << "\n_____________________________________________\n";

    SUserNsme User = ReadNewUserName();
    ReadPermissions(User);

    string line = ConvertRecordToLine(User);
    AddDataLineToFile("User.txt", line);

    cout << endl << "\a\nUser has been added successfully" << endl;
}

// Delete User
void SaveUsersToFile(vector<SUserNsme> Users, string FileName = "User.txt")
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (SUserNsme U : Users)
        {
            MyFile << ConvertRecordToLine(U) << endl;
        }

        MyFile.close();
    }

}

void DeleteUser(string UserDeleted)
{
    vector<SUserNsme> Users = LoadUserToUserNameStruct();

    for (int i = 0; i < Users.size(); i++)
    {
        if (Users[i].UserName == UserDeleted)
        {
            Users.erase(Users.begin() + i);
            SaveUsersToFile(Users);
        }
    }
}
void ShowScreenDelete()
{
    cout << "\n_____________________________________________\n";
    cout << "\t\t \t  Delte User Screen . " << endl;
    cout << "\n_____________________________________________\n";

    string UserNnam = ReadFindUseer();
    SUserNsme User;


    while (!IsFoundUser(User, UserNnam) || UserNnam == "Admin")
    {
        if (UserNnam == "Admin")
        {
            cout << "I Don't Can't Delete Admin, Enter Antoter User : " << endl;
            UserNnam = ReadFindUseer();
        }
        else
        {
            cout << "{" << UserNnam << "}" << "User is not available." << endl;
            UserNnam = ReadFindUseer();
        }
    }
    PrintUserFound(User);

    char YN;
    cout << "Are You Sure Delete This User Y/N ? ";
    cin >> YN;

    if (YN == 'y' || YN == 'Y')
    {
        DeleteUser(UserNnam);
        cout << "{" << UserNnam << "} " << " has been deleted successfully" << endl;
    }
}


// Update User
void UpdateUser(string UserUpdate)
{
    vector<SUserNsme> Users = LoadUserToUserNameStruct();
    SUserNsme *Updat = NULL;
    for (int i = 0; i < Users.size(); i++)
    {
        if (Users[i].UserName == UserUpdate)
        {
            Updat = & Users[i];
            break;
        }
    }

    cout << "Please Enter Password : ";
    cin >> Updat->Password;

    ReadPermissions(*Updat);
    SaveUsersToFile(Users);
}


void ShowScreenUpdate()
{
    cout << "\n_____________________________________________\n";
    cout << "\t\t \t  Update User Screen . " << endl;
    cout << "\n_____________________________________________\n";

    string UserNnam = ReadFindUseer();
    SUserNsme User;


    while (!IsFoundUser(User, UserNnam))
    {
          cout << "{" << UserNnam << "}" << "User is not available." << endl;
          UserNnam = ReadFindUseer();
    }
    PrintUserFound(User);

    char YN;
    cout << "Are You Sure Want Update This User Y/N ? ";
    cin >> YN;

    if (YN == 'y' || YN == 'Y')
    {
        UpdateUser(UserNnam);
        cout << "{" << UserNnam << "} " << " has been Update successfully" << endl;
    }
}



void ActionOfUsersOption(eUserMenueOpitions UserMenueOpitions)
{
    switch (UserMenueOpitions)
    {
    case eUserMenueOpitions::eListUser:
    {
        system("cls");    
        ShowUserList();
        GoBackToUserMenue();
        break;
    }

    case eUserMenueOpitions::eAddtUser:
    {
        system("cls");
        ShowAddUserScreen();
        GoBackToUserMenue();
        break;
    }


    case eUserMenueOpitions::eDeleteUser:
    {
        system("cls");
        ShowScreenDelete();
        GoBackToUserMenue();
        break;
    }


    case eUserMenueOpitions::eUpdateUser:
    {

        system("cls");
        ShowScreenUpdate();
        GoBackToUserMenue();
        break;
    }

    case eUserMenueOpitions::eFineUser:
    {
        system("cls");
        FindUserScreen();
        GoBackToUserMenue();
        break;
    }

    case eUserMenueOpitions::eMainUser:
    {
        system("cls");
        ShowMainMenue();
        break;
    }
    }

}

void ShowUsersMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\Manage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List User.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    short reaad = ReadMainUserption();
    ActionOfUsersOption(eUserMenueOpitions(reaad));
}



int main()
{

    Login();
   // ShowUserList();

    system("pause>0");
    return 0;
}