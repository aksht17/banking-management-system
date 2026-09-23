#include "SavingsAccount.h"
#include <iostream>

using namespace std;

SavingsAccount::SavingsAccount()
    : Account()
{

    interestRate = 4.0;
    minimumBalance = 1000.0;
}

SavingsAccount::SavingsAccount(
    string accountNumber,
    string customerID,
    double balance,
    double interestRate)
    : Account(
          accountNumber,
          customerID,
          balance)
{

    this->interestRate = interestRate;
    minimumBalance = 1000.0;
}

string SavingsAccount::getType() const
{
    return "SAVINGS";
}

double SavingsAccount::calculateInterest() const
{
    return balance * interestRate / 100.0;
}

bool SavingsAccount::withdraw(double amount)
{

    if (!active)
    {
        cout << "Account is inactive.\n";
        return false;
    }

    if (amount <= 0)
    {
        cout << "Invalid amount.\n";
        return false;
    }

    if (balance - amount < minimumBalance)
    {

        cout << "Minimum balance of Rs. "
             << minimumBalance
             << " must be maintained.\n";

        return false;
    }

    return Account::withdraw(amount);
}