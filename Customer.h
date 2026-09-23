#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <vector>

    using namespace std;

class Customer : public User
{
private:
    vector<string> accountNumbers;
    vector<string> loanIDs;

public:
    Customer();

    Customer(
        string id,
        string name,
        string password,
        string phone,
        string email);

    void addAccount(const string &accountNumber);
    void addLoan(const string &loanID);

    const vector<string> &getAccounts() const;
    const vector<string> &getLoans() const;

    void displayAccounts() const;

    void displayProfile() const override;
};

#endif

