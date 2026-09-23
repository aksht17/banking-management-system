#ifndef CURRENTACCOUNT_H
#define CURRENTACCOUNT_H

#include "Account.h"

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount();

    CurrentAccount(
        string accountNumber,
        string customerID,
        double balance,
        double overdraftLimit = 10000.0
    );

    string getType() const override;

    double calculateInterest() const override;

    bool withdraw(double amount) override;
};

#endif