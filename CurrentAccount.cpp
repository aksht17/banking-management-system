#include "CurrentAccount.h"
#include <iostream>

using namespace std;

CurrentAccount::CurrentAccount()
    : Account() {

    overdraftLimit = 10000.0;
}

CurrentAccount::CurrentAccount(
    string accountNumber,
    string customerID,
    double balance,
    double overdraftLimit
)
    : Account(
        accountNumber,
        customerID,
        balance
    ) {

    this->overdraftLimit = overdraftLimit;
}

string CurrentAccount::getType() const {
    return "CURRENT";
}

double CurrentAccount::calculateInterest() const {
    return 0.0;
}

bool CurrentAccount::withdraw(double amount) {

    if (!active) {
        cout << "Account is inactive.\n";
        return false;
    }

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return false;
    }

    if (amount > balance + overdraftLimit) {

        cout << "Withdrawal exceeds overdraft limit.\n";

        return false;
    }

    balance -= amount;

    return true;
}