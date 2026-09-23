#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Transaction::Transaction() {
    amount = 0;
}

Transaction::Transaction(
    string transactionID,
    string accountNumber,
    string type,
    double amount,
    string date,
    string description
) {
    this->transactionID = transactionID;
    this->accountNumber = accountNumber;
    this->type = type;
    this->amount = amount;
    this->date = date;
    this->description = description;
}

void Transaction::display() const {

    cout << left
         << setw(12) << transactionID
         << setw(12) << accountNumber
         << setw(18) << type
         << setw(12)
         << fixed << setprecision(2)
         << amount
         << setw(15) << date
         << description
         << endl;
}

string Transaction::getAccountNumber() const {
    return accountNumber;
}

string Transaction::serialize() const {

    stringstream ss;

    ss << transactionID << "|"
       << accountNumber << "|"
       << type << "|"
       << amount << "|"
       << date << "|"
       << description;

    return ss.str();
}

Transaction Transaction::deserialize(
    const string& line
) {

    stringstream ss(line);

    string id;
    string account;
    string type;
    string amount;
    string date;
    string description;

    getline(ss, id, '|');
    getline(ss, account, '|');
    getline(ss, type, '|');
    getline(ss, amount, '|');
    getline(ss, date, '|');
    getline(ss, description, '|');

    return Transaction(
        id,
        account,
        type,
        stod(amount),
        date,
        description
    );
}