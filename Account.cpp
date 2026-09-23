#include "Account.h"
#include <iostream>
#include <iomanip>

using namespace std;

Account::Account() {
    balance = 0;
    active = true;
}

Account::Account(
    string accountNumber,
    string customerID,
    double balance
) {
    this->accountNumber = accountNumber;
    this->customerID = customerID;
    this->balance = balance;
    active = true;
}

Account::~Account() {}

bool Account::deposit(double amount) {

    if (!active) {
        cout << "Account is inactive.\n";
        return false;
    }

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return false;
    }

    balance += amount;

    return true;
}

bool Account::withdraw(double amount) {

    if (!active) {
        cout << "Account is inactive.\n";
        return false;
    }

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return false;
    }

    if (amount > balance) {
        cout << "Insufficient balance.\n";
        return false;
    }

    balance -= amount;

    return true;
}

void Account::display() const {

    cout << "\n========== ACCOUNT ==========\n";

    cout << "Account Number : "
         << accountNumber << endl;

    cout << "Customer ID    : "
         << customerID << endl;

    cout << "Account Type   : "
         << getType() << endl;

    cout << "Balance        : Rs. "
         << fixed << setprecision(2)
         << balance << endl;

    cout << "Status         : "
         << (active ? "ACTIVE" : "INACTIVE")
         << endl;
}

string Account::getAccountNumber() const {
    return accountNumber;
}

string Account::getCustomerID() const {
    return customerID;
}

double Account::getBalance() const {
    return balance;
}

bool Account::isActive() const {
    return active;
}

void Account::setActive(bool status) {
    active = status;
}