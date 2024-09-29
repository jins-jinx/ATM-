#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <conio.h>
#define FLUSH fflush(stdin)
#define MAX 100
using namespace std;


typedef struct birthday{
    string Month;
    int Day;
    int Year;
}bday;

// Structure to represent an ATM account
typedef struct atmAccount{
    int accountNumber;
    string accountName;
    bday bd;
    string contactNumber;
    double balance;
    string pinCode;
}acc;

class MyATM{
private:
    acc nA;
    bday bd;
    void gotoxy(int x, int y);
public:
    void enrollNewAccount(acc accounts[]);
    void withdraw(acc accounts[], int accountNumber, double amount);
    void deposit(acc accounts[], int accountNumber, double amount);
    void FundTransfer(acc accounts[], int accountNumber);
    void balanceInquiry(acc nA[], int accountNumber, string accPIN);
    void saveAccountDataToFile(acc accounts[], int accountCount);
    void loadAccountDataFromFile(acc accounts[], int &accountCount);
    void changePin(acc nA[], int accountNumber);
    void insertCard();
    bool isEmpty();
    int accountCount = 0;
};

void MyATM::saveAccountDataToFile(acc accounts[], int accountCount) {
    ofstream outFile("D:\\pin.code.txt");
    if (!outFile.is_open()) {
        cout << "\033[31mError opening the file for writing." << endl;
        system("pause");
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        outFile << accounts[i].accountNumber << " ";
        outFile << accounts[i].accountName << " ";
        outFile << accounts[i].bd.Month << " ";
        outFile << accounts[i].bd.Day << " ";
        outFile << accounts[i].bd.Year << " ";
        outFile << accounts[i].contactNumber << " ";
        outFile << accounts[i].balance << " ";
        outFile << accounts[i].pinCode << endl;
    }

    outFile.close();
    cout << "\033[32mAccount data saved to file.\033[0m" << endl;
    system("pause");
}

void MyATM::loadAccountDataFromFile(acc accounts[], int &accountCount) {
    ifstream inFile("D:\\pin.code.txt");
    if (!inFile.is_open()) {
        cout << "\033[31mNo account data file found.\033[0m" << endl;
        system("pause");
        return;
    }

    accountCount = 0;  // Initialize accountCount to 0 before loading accounts
    while (inFile >> accounts[accountCount].accountNumber >>
           accounts[accountCount].accountName >>
           accounts[accountCount].bd.Month >>
           accounts[accountCount].bd.Day >>
           accounts[accountCount].bd.Year >>
           accounts[accountCount].contactNumber >>
           accounts[accountCount].balance >>
           accounts[accountCount].pinCode) {
        accountCount++;
    }

    inFile.close();
    cout << "Account data loaded from file. Total accounts: " << accountCount << endl;
    system("pause");
}

void MyATM::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to enroll a new ATM account
void MyATM::enrollNewAccount(acc accounts[]) {
    acc nA;
    int Suggested_AccNum = 0;
    bool AccNumValid = false;

    if (accountCount >= MAX) {
        cout << "Maximum account limit reached." << endl;
        return;
    }

    bday bd;

    // Input account details
        // BINAGO KO TO
        while (true) {
            system("cls");
            FLUSH;
            cout << "Notice: Account number is VERY important. Follow the given instructions to prevent an error." << endl << endl;
            cout << "IMPORTANT: Enter a 5-digit number STARTING FROM 10000." << endl;

            gotoxy(45, 15);
            cout << "Enter Account Number (5 digits): ";
            cin >> Suggested_AccNum;

            if (Suggested_AccNum < 10000 || Suggested_AccNum > 99999) {
                gotoxy(45, 16);
                cout << "\033[31mERROR: Input 5-digit number ONLY. Starting from 10000.\033[0m" << endl;
                gotoxy(45, 20);
                system("pause");
            } else {
                bool isDuplicate = false;

                for (int i = 0; i < accountCount; i++) {
                    if (accounts[i].accountNumber == Suggested_AccNum) {
                        isDuplicate = true;
                        break;
                    }
                }

                if (isDuplicate) {
                    gotoxy(45, 17);
                    cout << Suggested_AccNum << " is already used.";
                    gotoxy(45, 20);
                    system("pause");
                } else {
                    nA.accountNumber = Suggested_AccNum;
                    AccNumValid = true;
                    break; // Exit the loop when a valid account number is found.
                }
            }
        }


    cin.ignore(); // Clear newline from the buffer

    gotoxy(45, 16);
    cout << "\033[32mYou entered [" << nA.accountNumber << "] as your account number.\033[0m";

    gotoxy(0, 20);
    system("pause");

    system("cls");
    cout << "Enter Account Details" << endl << endl;

    cout << "Account Number: " << nA.accountNumber << endl;

    cout << "Enter Account Name: ";
    getline(cin, nA.accountName);


    cout << "Enter Birth Month: ";
    cin >> nA.bd.Month;

    while (true){
        cout << "[Example: 10]" << endl;
        cout << "Enter Birth Day: ";
        cin >> nA.bd.Day;

        if (nA.bd.Day <= 0 || nA.bd.Day >= 32){
            cout << endl << "\033[31mInvalid Birth Date. Please try again.\033[0m" << endl;
        } else {
            break;
        }
    }

    while (true){
        cout << "[Example: 2004]" << endl;
        cout << "Enter Birth Year: ";
        cin >> nA.bd.Year;

        if (nA.bd.Year <= 0 || nA.bd.Year >= 2024){
            cout << endl << "\033[31mInvalid Birth Year. Please try again.\033[0m" << endl;
        } else {
            break;
        }

    }

    cout << "Enter Contact Number: ";
    cin >> nA.contactNumber;

    while (true){
        cout << "Enter Initial Deposit (Min. 5000): ";
        cin >> nA.balance;
        // Validate initial deposit
        if (nA.balance < 5000) {
            cout << endl << "\033[31mERROR: Initial deposit must be at least 5000.\033[0m" << endl;
        } else {
            break;
        }
    }

        cout << "Set a 6-digit PIN Code: ";
        cin.ignore();
        char c;
        nA.pinCode = "";
        while (true) {
            c = _getch();
            if (c == 13)
                break;
            else if (c == 8) {
                if (!nA.pinCode.empty()) {
                    cout << "\b \b";
                    nA.pinCode.pop_back();
                }
            } else if (c >= '0' && c <= '9') {
                cout << '*';
                nA.pinCode += c;
            }
        }


    // Add the new account to the array
    accounts[accountCount] = nA;
    accountCount++;

    cout << endl << endl << "\033[32mAccount successfully enrolled.\033[0m" << endl;
}


// Function to withdraw from an account
void MyATM::withdraw(acc accounts[], int accountNumber, double amount) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            if (accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                cout << "\033[32mP" << amount <<" withdrawed successfully...\033[0m" << endl;

            } else {
                cout << "\033[31mInsufficient balance.\033[0m" << endl;
            }
        system("pause");
        }
    }
}

void MyATM::deposit(acc accounts[], int accountNumber, double amount) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            accounts[i].balance += amount;
            cout << "\033[32mP" << amount <<" deposited successfully...\033[0m" << endl;
            system("pause");
        }
    }
}

void MyATM::FundTransfer(acc accounts[], int accountNumber) {
    if (accountCount < 2){
        gotoxy(45, 26); cout << "Insufficient number of accounts enrolled.";
        system("pause");
        return;
    }

    int SenderIndex, ReceiverIndex, receiverAccountNumber;
    bool accountFound = false;
    double amount;

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            SenderIndex = i;
        }
    }

    gotoxy(45, 26); cout << "Enter account number of the receiver: ";
                    cin >> receiverAccountNumber;

    for (int j = 0; j < accountCount; j++) {
        if (accounts[j].accountNumber == receiverAccountNumber) {
            ReceiverIndex = j;
            accountFound = true;
            gotoxy(45, 27); cout << "\033[32mAccount found. Receiver's Account Number: \033[0m" << receiverAccountNumber;
        }
    }

    if(!accountFound){
        gotoxy(45, 27); cout << "\033[31mInvalid Account Number.\033[0m";
        system("pause");
        return;
    }

    gotoxy(45, 28); cout << "Current Balance: P" << accounts[SenderIndex].balance;
    gotoxy(45, 29); cout << "Input fund transfer: P";
    cin >> amount;

    if (accounts[SenderIndex].balance >= amount) {
        accounts[SenderIndex].balance -= amount;
        accounts[ReceiverIndex].balance += amount;
        } else {
        gotoxy(45, 30); cout << "\033[31mInsufficient balance.\033[0m";
        system("pause");
        return;
    }

    gotoxy(45, 30); cout << "\033[32mP" << amount <<" transferred successfully...\033[0m";
    gotoxy(45, 31); system("pause");
}




// Function to perform balance inquiry
void MyATM::balanceInquiry(acc nA[], int accountNumber, string accPIN) {
    int choice;
    bday bd;
    bool accountFound = false;
    for (int i = 0; i < accountCount; i++) {
        if (nA[i].accountNumber == accountNumber && nA[i].pinCode == accPIN) {
            while (true){
                system("cls");
                accountFound = true;
                gotoxy(45, 3); cout << "      _     _________  ____    ____ ";
                gotoxy(45, 4); cout << "     / \\   |  _   _  ||_   \\  /   _|";
                gotoxy(45, 5); cout << "    / _ \\  |_/ | | \\_|  |   \\/   |  ";
                gotoxy(45, 6); cout << "   / ___ \\     | |      | |\\  /| |  ";
                gotoxy(45, 7); cout << " _/ /   \\ \\_  _| |_    _| |_\\/_| |_ ";
                gotoxy(45, 8); cout << "|____| |____||_____|  |_____||_____|";


                gotoxy(45, 11); cout << "Account Number: " << nA[i].accountNumber << endl;
                gotoxy(45, 12); cout << "Account Name: " << nA[i].accountName << endl;
                gotoxy(45, 13); cout << "Contact Number: " << nA[i].contactNumber << endl;
                gotoxy(45, 14); cout << "Birthday: " << nA[i].bd.Month << " " << nA[i].bd.Day << " " << nA[i].bd.Year << endl;
                gotoxy(45, 15); cout << "Balance: P" << nA[i].balance << endl << endl;
                gotoxy(45, 17); cout << "____________" << endl;
                gotoxy(45, 18); cout << "1 | Withdraw" << endl;
                gotoxy(45, 19); cout << "2 | Deposit" << endl;
                gotoxy(45, 20); cout << "3 | Fund Transfer" << endl;
                gotoxy(45, 21); cout << "4 | Change PIN" << endl;
                gotoxy(45, 22); cout << "5 | Exit" << endl << endl;
                gotoxy(45, 24); cout << "What would you like to do? ";
                                cin >> choice;

                    switch(choice){
                        case 1:
                            double withdrawAmount;
                            gotoxy(45, 26); cout << "Enter Withdrawal Amount: P";
                            cin >> withdrawAmount;
                            gotoxy(45, 27);withdraw(nA, accountNumber, withdrawAmount);
                            break;
                        case 2:
                            double depositAmount;
                            gotoxy(45, 26); cout << "How much are you going to deposit?" << endl;
                            gotoxy(45, 27); cout << "Enter Amount: P";
                            cin >> depositAmount;
                            gotoxy(45, 28); deposit(nA, accountNumber, depositAmount);
                            break;
                        case 3:
                            FundTransfer(nA, accountNumber);
                            break;
                        case 4:
                            changePin(nA, accountNumber);
                            break;
                        case 5:
                            return;
                        default:
                            cout << "\033[31mERROR: Input 1 - 5 ONLY.\033[0m";
                            system("pause");
                    }
            }
        }
    }
    if (!accountFound){
        cout << endl <<"\033[31mInvalid Account Number or Password.\033[0m" << endl;
        system("pause");
        return;
    }
}

bool MyATM::isEmpty(){
    return accountCount == 0;
}

void MyATM::changePin(acc nA[], int accountNumber){
    int accIndex;
    string currentPIN, newPIN;
    for (int i = 0; i < accountCount; i++) {
        if (nA[i].accountNumber == accountNumber) {
            accIndex = i;
        }
    }

    gotoxy(45, 26); cout << "Enter Current PIN: ";
    cin.ignore();
        char c;
        currentPIN = "";
        while (true) {
            c = _getch();
            if (c == 13)
                break;
            else if (c == 8) {
                if (!currentPIN.empty()) {
                    cout << "\b \b";
                    currentPIN.pop_back();
                }
            } else if (c >= '0' && c <= '9') {
                cout << '*';
                currentPIN += c;
            }
        }

    if (nA[accIndex].pinCode != currentPIN){
        gotoxy(45, 27); cout <<"\033[31mERROR: Invalid PIN.\033[0m";
        system("pause");
        return;
    }

    gotoxy(45, 27); cout << "Enter New PIN: ";
    newPIN = "";
    while (true) {
        c = _getch();
        if (c == 13)
            break;
        else if (c == 8) {
            if (!newPIN.empty()) {
                cout << "\b \b";
                newPIN.pop_back();
            }
        } else if (c >= '0' && c <= '9') {
            cout << '*';
            newPIN += c;
        }
    }

    if (currentPIN == newPIN){
        gotoxy(45, 28); cout << "\033[31mERROR: Enter a different PIN.\033[0m";
        system("pause");
        return;
    }

    nA[accIndex].pinCode = newPIN;
    gotoxy(45, 28); cout << "\033[32mPIN successfully updated.\033[0m";
    system("pause");
}

void MyATM::insertCard(){
    ifstream inFile;
    bool fileFound = false;
    do {
        inFile.open("D:\\pin.code.txt");
        if (!inFile.is_open()) {
            gotoxy(45, 15);
            cout << "PLEASE ENTER ATM CARD" << endl;
        } else {
            gotoxy(45, 15);
            cout << "Card inserted successfully.";
            fileFound = true;
            gotoxy(45, 20);
            system("pause");
        }
    inFile.close();
    } while(!fileFound);
}


// You can similarly implement deposit, fund transfer, and change PIN functions
int main() {
    acc accounts[MAX]; // Array to store ATM accounts
    MyATM MA;

    //MA.insertCard();
    system("cls");
    MA.loadAccountDataFromFile(accounts, MA.accountCount);
    string accountPIN;

    while (true) {
        system("cls");
        cout << "ATM System Menu:" << endl;
        cout << "1. Enroll New Account" << endl;
        cout << "2. Balance Inquiry" << endl;
        cout << "3. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                MA.enrollNewAccount(accounts);
                system("pause");
                break;
            case 2:
                if (MA.isEmpty()){
                    cout << "\033[31mNo account has been created.\033[0m" << endl;
                    system("pause");
                    break;
                }
                int accountNumber;
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter PIN: ";
                cin.ignore();
                char c;
                accountPIN = "";
                while (true) {
                    c = _getch();
                    if (c == 13)
                        break;
                    else if (c == 8) {
                        if (!accountPIN.empty()) {
                            cout << "\b \b";
                            accountPIN.pop_back();
                        }
                    } else if (c >= '0' && c <= '9') {
                        cout << '*';
                        accountPIN += c;
                    }
                }
                MA.balanceInquiry(accounts, accountNumber, accountPIN);
                break;
            case 3:
                system("cls");
                cout << "Exiting the ATM System. Goodbye!" << endl;
                MA.saveAccountDataToFile(accounts, MA.accountCount);
                return 0;
            default:
                cout << endl << "\033[31mInvalid choice. Please try again.\033[0m" << endl;
                system("pause");
        }
    }

    return 0;
}

