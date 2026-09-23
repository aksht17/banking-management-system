#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

using namespace std;

class Transaction {
private:
    string transactionID;
    string accountNumber;
    string type;
    double amount;
    string date;
    string description;

public:
    Transaction();

    Transaction(
        string transactionID,
        string accountNumber,
        string type,
        double amount,
        string date,
        string description
    );

    void display() const;

    string getAccountNumber() const;

    string serialize() const;

    static Transaction deserialize(
        const string& line
    );
};

#endif