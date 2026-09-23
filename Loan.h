#ifndef LOAN_H
#define LOAN_H

#include <string>

using namespace std;

class Loan {
private:
    string loanID;
    string customerID;

    double amount;
    double interestRate;

    int tenure;

    string type;
    string status;

    double remainingAmount;

public:
    Loan();

    Loan(
        string loanID,
        string customerID,
        double amount,
        double interestRate,
        int tenure,
        string type
    );

    double calculateEMI() const;

    void approve();
    void reject();

    void display() const;

    string getLoanID() const;
    string getCustomerID() const;
    string getStatus() const;
};

#endif