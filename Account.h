#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account {
protected:
    string accountNumber;
    string customerID;
    double balance;
    bool active;

public:
    Account();

    Account(
        string accountNumber,
        string customerID,
        double balance
    );

    virtual ~Account();

    virtual string getType() const = 0;

    virtual double calculateInterest() const = 0;

    virtual bool withdraw(double amount);

    bool deposit(double amount);

    virtual void display() const;

    string getAccountNumber() const;
    string getCustomerID() const;

    double getBalance() const;

    bool isActive() const;
    void setActive(bool status);
};

#endif
