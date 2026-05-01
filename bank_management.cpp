#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class BankAccount{
protected:
    string name;
    string accountNumber;
    int age;
    double balance;

public:
    BankAccount(string name, string accountNumber, int age):name(name), accountNumber(accountNumber), age(age), balance(0.0){}

    virtual void deposit(double amount)=0;
    virtual void withdraw(double amount)=0;
    virtual void displayBalance(){
        cout<<"Account Holder: "<<name<<endl;
        cout<<"Account Number: "<<accountNumber<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Current Balance: $"<< balance<<"\n";
    }
    void saveToFile(){
        ofstream outFile(accountNumber+".txt");
        if (outFile.is_open()){
            outFile<<"Name: "<<name<<endl;
            outFile<<"Account Number: "<<accountNumber<<endl;
            outFile<<"Age: "<<age<<endl;
            outFile<<"Balance: $"<<balance<<"\n";
            outFile.close();
            cout<<"Account details saved to file.\n";
        } else{
            cout<<"Error: Unable to open file for writing.\n";
        }
    }

    bool sendMoney(double amount, const string& recipientAccountNumber){
        if (amount>balance){
            cout<<"Insufficient funds\n";
            return false;
        } else{
            balance-=amount;
            cout<<"Money sent successfully to account number: "<<recipientAccountNumber<<"\n";
            return true;
        }
    }
};

class CurrentAccount:public BankAccount{
public:
    CurrentAccount(string name, string accountNumber, int age):BankAccount(name, accountNumber, age){}

    void deposit(double amount) override{
        balance += amount;
        cout<<"Deposit to Current Account of $"<<amount<<" successful.\n";
    }

    void withdraw(double amount) override{
        if (amount>balance){
            cout<<"Insufficient funds\n";
        } else {
            balance-=amount;
            cout<<"Withdrawal from Current Account of $"<<amount<<" successful.\n";
        }
    }
};

class SavingsAccount:public BankAccount{
public:
    SavingsAccount(string name, string accountNumber, int age):BankAccount(name, accountNumber, age){}

    void deposit(double amount) override{
        balance+=amount;
        cout<<"Deposit to Savings Account of $"<<amount<<" successful.\n";
    }

    void withdraw(double amount) override{
        if (amount > balance){
            cout << "Insufficient funds\n";
        } else {
            balance-=amount;
            cout<<"Withdrawal from Savings Account of $"<<amount<<" successful.\n";
        }
    }
};

int main(){
    string name, accountNumber;
    int age, accountType;
    double amount;
    cout<<"Enter details to create account / Log in:"<<endl;
    cout<<"Enter name: ";
    getline(cin, name);
    cout<<"Enter account number: ";
    getline(cin, accountNumber);
    cout<<"Enter age: ";
    cin>>age;
    cout<<"Choose Account Type:\n";
    cout<<"1. Current Account\n";
    cout<<"2. Savings Account\n";
    cout<<"Enter your choice: ";
    cin>>accountType;

    BankAccount *account;
    if (accountType == 1){
        account=new CurrentAccount(name, accountNumber, age);
    } else if (accountType==2){
        account=new SavingsAccount(name, accountNumber, age);
    } else {
        cout<<"Invalid choice. Exiting...\n";
        return 1;
    }

    account->saveToFile();

    int choice;

    do {
        cout<<"1. Deposit\n";
        cout<<"2. Withdraw\n";
        cout<<"3. Display Balance\n";
        cout<<"4. Send Money\n";
        cout<<"5. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice){
            case 1:
                cout<<"Enter amount to deposit: $";
                cin>>amount;
                account->deposit(amount);
                break;
            case 2:
                cout<<"Enter amount to withdraw: $";
                cin>>amount;
                account->withdraw(amount);
                break;
            case 3:
                account->displayBalance();
                break;
            case 4: {
                string recipientAccountNumber;
                cout<<"Enter beneficiary's' account number: ";
                cin>>recipientAccountNumber;
                cout<<"Enter amount to send: $";
                cin>>amount;
                account->sendMoney(amount, recipientAccountNumber);
                break;
            }
            case 5:
                cout<<"Exiting...\n";
                break;
            default:
                cout<<"Invalid choice. Please try again.\n";
        }
    } while (choice!=5);

    delete account;

    return 0;
}