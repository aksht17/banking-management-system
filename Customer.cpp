#include "Customer.h"
#include <iostream>

using namespace std;

Customer::Customer() : User() {}

Customer::Customer(
    string id,
    string name,
    string password,
    string phone,
    string email
)
    : User(id, name, password, phone, email) {}

void Customer::addAccount(
    const string& accountNumber
) {
    accountNumbers.push_back(accountNumber);
}

void Customer::addLoan(
    const string& loanID
) {
    loanIDs.push_back(loanID);
}

const vector<string>& Customer::getAccounts() const {
    return accountNumbers;
}

const vector<string>& Customer::getLoans() const {
    return loanIDs;
}

void Customer::displayAccounts() const {
    cout << "\n========== MY ACCOUNTS ==========\n";

    if (accountNumbers.empty()) {
        cout << "No accounts found.\n";
        return;
    }

    for (const string& account : accountNumbers) {
        cout << "- " << account << endl;
    }
}

void Customer::displayProfile() const {
    User::displayProfile();

    cout << "Number of Accounts : "
         << accountNumbers.size() << endl;

    cout << "Number of Loans    : "
         << loanIDs.size() << endl;
}

