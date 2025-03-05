#include <iostream>
using namespace std;

class Bank
{
private:
    string accno, ifsc;
    string name, surname, fname, fsurname, branch;
    int pin, mindeposite, reg;
    double bal;

public:
    Bank()
    {
        mindeposite = 500;
        bal = mindeposite;
    }

    void createAccount()
    {
        cout << "Enter registration number: ";
        cin >> reg;

        cout << "Enter account number: ";
        cin >> accno;

        cout << "Enter full name: ";
        cin >> name >> surname;

        cout << "Enter father’s name: ";
        cin >> fname >> fsurname;

        cout << "Enter bank branch: ";
        cin >> branch;

        cout << "Enter IFSC code: ";
        cin >> ifsc;

        cout << "Set PIN for transactions: ";
        cin >> pin;

        cout << "Account created successfully!\n";
        displayAccountDetails();
    }

    void displayAccountDetails()
    {
        cout << "\n------ Account Details ------\n";
        cout << "Reg No: " << reg << "\n";
        cout << "Account No: " << accno << "\n";
        cout << "Holder: " << name << " " << surname << "\n";
        cout << "Father's Name: " << fname << " " << fsurname << "\n";
        cout << "Branch: " << branch << "\n";
        cout << "IFSC: " << ifsc << "\n";
        cout << "Current Balance: " << bal << "\n";
    }

    bool authenticate()
    {
        string enteredAccNo;
        int enteredPin;

        cout << "Enter account number: ";
        cin >> enteredAccNo;

        if (enteredAccNo != accno)
        {
            cout << "Error: Account not found.\n";
            return false;
        }

        cout << "Enter PIN: ";
        cin >> enteredPin;

        if (enteredPin != pin)
        {
            cout << "Error: Incorrect PIN.\n";
            return false;
        }

        return true;
    }

    void checkBalance()
    {
        if (authenticate())
        {
            cout << "Current balance: " << bal << "\n";
        }
    }

    void depositMoney()
    {
        double amount;
        cout << "Enter deposit amount: ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Error: Invalid amount.\n";
            return;
        }

        bal += amount;
        cout << "Deposited successfully! New balance: " << bal << "\n";
    }

    void withdrawMoney()
    {
        if (!authenticate())
            return;

        double amount;
        cout << "Enter withdrawal amount: ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Error: Invalid amount.\n";
            return;
        }

        if (amount > bal)
        {
            cout << "Error: Insufficient balance.\n";
            return;
        }

        bal -= amount;
        cout << "Withdrawal successful! New balance: " << bal << "\n";
    }

    string getAccNo() { return accno; }
    string getIFSC() { return ifsc; }
    int getReg() { return reg; }
    double getBalance() { return bal; }

    void setBalance(double amount) { bal = amount; }
};

class Transfer : public Bank
{
public:
    void transferMoney(Transfer &from, Transfer &to)
    {
        if (!from.authenticate())
            return;

        if (from.getReg() == to.getReg())
        {
            cout << "Error: Cannot transfer to the same account.\n";
            return;
        }

        double amount;
        cout << "Enter transfer amount: ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Error: Invalid amount.\n";
            return;
        }

        if (amount > from.getBalance())
        {
            cout << "Error: Insufficient balance.\n";
            return;
        }

        double tax = (amount >= 100000) ? (0.02 * amount) : 0;
        from.setBalance(from.getBalance() - amount - tax);
        to.setBalance(to.getBalance() + amount);

        cout << "Transfer successful! New balance: " << from.getBalance() << "\n";
    }
};

int main()
{
    Transfer accounts[20];
    int numAccounts, choice, i, j;

    cout << "Enter the number of accounts to be created: ";
    cin >> numAccounts;

    for (i = 0; i < numAccounts; i++)
    {
        accounts[i].createAccount();
        cout << endl;
    }

    do
    {
        cout << "\n------ Bank Management System ------\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Account Info\n";
        cout << "5. Transfer Money\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter account index (0 to " << numAccounts - 1 << "): ";
            cin >> i;
            if (i >= 0 && i < numAccounts)
                accounts[i].depositMoney();
            else
                cout << "Error: Invalid account index.\n";
            break;

        case 2:
            cout << "Enter account index: ";
            cin >> i;
            if (i >= 0 && i < numAccounts)
                accounts[i].withdrawMoney();
            else
                cout << "Error: Invalid account index.\n";
            break;

        case 3:
            cout << "Enter account index: ";
            cin >> i;
            if (i >= 0 && i < numAccounts)
                accounts[i].checkBalance();
            else
                cout << "Error: Invalid account index.\n";
            break;

        case 4:
            cout << "Enter account index: ";
            cin >> i;
            if (i >= 0 && i < numAccounts)
                accounts[i].displayAccountDetails();
            else
                cout << "Error: Invalid account index.\n";
            break;

        case 5:
            cout << "Enter sender account index: ";
            cin >> i;
            cout << "Enter receiver account index: ";
            cin >> j;
            if (i >= 0 && i < numAccounts && j >= 0 && j < numAccounts)
                accounts[i].transferMoney(accounts[i], accounts[j]);
            else
                cout << "Error: Invalid account index.\n";
            break;

        case 6:
            cout << "Thank you for using our system!\n";
            break;

        default:
            cout << "Error: Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
