#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;
    double minimumBalance;

public:
    SavingsAccount();

    SavingsAccount(
        string accountNumber,
        string customerID,
        double balance,
        double interestRate = 4.0
    );

    string getType() const override;

    double calculateInterest() const override;

    bool withdraw(double amount) override;
};

#endif