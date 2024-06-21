#include <iostream>
#include <unordered_map>
#include <string>


#define ll long long
using namespace std;

/*

In bank mnagement part :
New User
Alredy Use
Deposite Option
Withdraw Option
Transfer Option
Payment Option
Search User Record
Edit User Record
Delete User Record
Show All Record
Payemnt All Record
GO Back


*/
/*

In ATM MAnagement : User Login & Check Banalnce
Wihdraw Amount
Account Details
GO Back
*/
class Account {
private:
    int accountNumber;
    string accountHolderName;
    string email;
    string password;
    int pin;
    double balance;

public:
    // Default constructor
    Account() : accountNumber(0), accountHolderName(""), email(""), password(""), pin(0), balance(0.0) {}

    // Parameterized constructor
    Account(int accNum, string name, string mail, string pwd, int pinCode)
        : accountNumber(accNum), accountHolderName(name), email(mail), password(pwd), pin(pinCode), balance(0.0) {}


    int getAccountNumber() const {

        return accountNumber;

    }

    string getAccountHolderName() const {

        return accountHolderName;

    }

    string getEmail() const {

        return email;

    }

    double getBalance() const {

        return balance;

    }

    bool verifyCredentials(string mail, string pwd, int pinCode) const {

        return email == mail && password == pwd && pin == pinCode;

    }


    void deposit(double amount) {

        balance += amount;

        cout << "Deposited $" << amount << " to account number " << accountNumber << endl;

    }

    bool withdraw(double amount) {

        if (amount > balance) {

            cout << "Insufficient balance!" << endl;

            return false;

        }
        balance -= amount;

        cout << "Withdrew $" << amount << " from account number " << accountNumber << endl;

        return true;
    }

    void printDetails() const {

        cout << "Account Number: " << accountNumber << endl;

        cout << "Account Holder: " << accountHolderName << endl;

        cout << "Email: " << email << endl;

        cout << "Balance: $" << balance << endl;

    }

    void setAccountHolderName(string name) {

        accountHolderName = name;

    }

    void setEmail(string mail) {

        email = mail;

    }

    void setPassword(string pwd) {

        password = pwd;

    }

    void setPin(int pinCode) {

        pin = pinCode;

    }


};

class Bank {

private:

    unordered_map<int, Account> accounts;

    int nextAccountNumber;


public:

    Bank() : nextAccountNumber(1) {}

    int createAccount(string name, string email, string password, int pin) {
        Account newAccount(nextAccountNumber, name, email, password, pin);
        accounts[nextAccountNumber] = newAccount;
        cout << "Account created with account number: " << nextAccountNumber << endl;
        return nextAccountNumber++;
    }

    Account* getAccount(int accountNumber) {
        if (accounts.find(accountNumber) != accounts.end()) {
            return &accounts[accountNumber];
        }
        cout << "Account not found!" << endl;
        return nullptr;
    }

    void deposit(int accountNumber, double amount) {
        Account* acc = getAccount(accountNumber);
        if (acc) {
            acc->deposit(amount);
        }
    }

    bool withdraw(int accountNumber, double amount) {
        Account* acc = getAccount(accountNumber);
        if (acc) {
            return acc->withdraw(amount);
        }
        return false;
    }

    void transfer(int fromAccount, int toAccount, double amount) {
        Account* fromAcc = getAccount(fromAccount);
        Account* toAcc = getAccount(toAccount);
        if (fromAcc && toAcc) {
            if (fromAcc->withdraw(amount)) {
                toAcc->deposit(amount);
                cout << "Transferred $" << amount << " from account number " << fromAccount << " to account number " << toAccount << endl;
            }
        }
    }

    void searchUserRecord(int accountNumber) {
        Account* acc = getAccount(accountNumber);
        if (acc) {
            acc->printDetails();
        }
    }

    void editUserRecord(int accountNumber, string name, string email, string password, int pin) {

        Account* acc = getAccount(accountNumber);

        if (acc) {

            acc->setAccountHolderName(name);

            acc->setEmail(email);

            acc->setPassword(password);

            acc->setPin(pin);

            cout << "Account details updated for account number " << accountNumber << endl;
        }
    }

    void deleteUserRecord(int accountNumber) {

        if (accounts.erase(accountNumber)) {

            cout << "Account number " << accountNumber << " deleted successfully!" << endl;

        } 
        else {

            cout << "Account not found!" << endl;
        }
    }

    void showAllRecords() {
        for (const auto& pair : accounts) {

            pair.second.printDetails();

        }
    }
};

class ATM {
private:
    Bank& bank;

public:
    ATM(Bank& bankRef) : bank(bankRef) {}

    void userLogin() {


        int accountNumber;

        string email, password;


        int pin;

        cout << "Enter account number: ";

        cin >> accountNumber;

        cout << "Enter email: ";

        cin >> email;

        cout << "Enter password: ";

        cin >> password;

        cout << "Enter PIN: ";

        cin >> pin;

        Account* acc = bank.getAccount(accountNumber);

        if (acc && acc->verifyCredentials(email, password, pin))
        {
            int choice;

            do {
                cout << "\n1. Check Balance\n2. Withdraw Amount\n3. View Account Details\n4. Go Back\n";
                cout << "Enter your choice: ";

                cin >> choice;


                switch (choice) {
                    case 1:

                        cout << "Current balance: $" << acc->getBalance() << endl;

                        break;
                    case 2: {

                        double amount;

                        cout << "Enter amount to withdraw: ";


                        cin >> amount;

                        bank.withdraw(accountNumber, amount);

                        break;

                    }
                    case 3:
                        acc->printDetails();

                        break;

                    case 4:
                        cout << "Logging out..." << endl;

                        break;

                    default:
                        cout << "Invalid choice, please try again." << endl;

                }
            } while (choice != 4);

        } else {
            cout << "Invalid account number, email, password, or PIN!" << endl;

        }
    }
};

int main() {
    Bank myBank;

    ATM myATM(myBank);


    int choice;

    do {
        cout << "\n1. New User\n2. Already User\n3. Deposit Option\n4. Withdraw Option\n5. Transfer Option\n6. Payment Option\n7. Search User Record\n8. Edit User Record\n9. Delete User Record\n10. Show All Record\n11. Go Back\n";

        cout << "Enter your choice: ";

        cin >> choice;


        switch (choice) {

            case 1: {
                string name, email, password;

                int pin;
                cout << "Enter account holder name: ";

                cin >> name;
                cout << "Enter email: ";

                cin >> email;

                cout << "Enter password: ";

                cin >> password;
                cout << "Enter PIN: ";

                cin >> pin;
                myBank.createAccount(name, email, password, pin);

                break;
            }
            case 2:
                myATM.userLogin();
                break;
            case 3: {

                int accountNumber;
                double amount;

                cout << "Enter account number: ";
                cin >> accountNumber;

                cout << "Enter amount to deposit: ";
                cin >> amount;

                myBank.deposit(accountNumber, amount);

                break;
            }
            case 4: {
                int accountNumber;
                double amount;

                cout << "Enter account number: ";
                cin >> accountNumber;

                cout << "Enter amount to withdraw: ";
                cin >> amount;

                myBank.withdraw(accountNumber, amount);
                break;
            }
            case 5: {
                int fromAccount, toAccount;
                double amount;

                cout << "Enter your account number: ";
                cin >> fromAccount;

                cout << "Enter recipient account number: ";
                cin >> toAccount;

                cout << "Enter amount to transfer: ";
                cin >> amount;

                myBank.transfer(fromAccount, toAccount, amount);
                break;
            }
            case 6: {

                cout << "Payment option is currently not implemented." << endl;

                break;
            }
            case 7: {
                int accountNumber;

                cout << "Enter account number to search: ";

                cin >> accountNumber;

                myBank.searchUserRecord(accountNumber);

                break;
            }
            case 8: {
                int accountNumber;

                string name, email, password;

                int pin;

                cout << "Enter account number to edit: ";

                cin >> accountNumber;
                cout << "Enter new account holder name: ";

                cin >> name;
                cout << "Enter new email: ";

                cin >> email;
                cout << "Enter new password: ";

                cin >> password;
                cout << "Enter new PIN: ";

                cin >> pin;
                myBank.editUserRecord(accountNumber, name, email, password, pin);
                break;
            }
            case 9: {
                int accountNumber;
                cout << "Enter account number to delete: ";
                cin >> accountNumber;
                // deleting user record bang bang 
                myBank.deleteUserRecord(accountNumber);
                break;
            }
            case 10:
                myBank.showAllRecords();
                break;
            case 11:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }  while (choice != 11);

    return 0;
}
