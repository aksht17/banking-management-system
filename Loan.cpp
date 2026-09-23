#include "Loan.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

Loan::Loan()
{
    amount = 0;
    interestRate = 0;
    tenure = 0;
    remainingAmount = 0;
    status = "PENDING";
}

Loan::Loan(
    string loanID,
    string customerID,
    double amount,
    double interestRate,
    int tenure,
    string type)
{

    this->loanID = loanID;
    this->customerID = customerID;
    this->amount = amount;
    this->interestRate = interestRate;
    this->tenure = tenure;
    this->type = type;

    status = "PENDING";

    remainingAmount = amount;
}

double Loan::calculateEMI() const
{

    double monthlyRate =
        interestRate / 12.0 / 100.0;

    int months = tenure * 12;

    if (months <= 0)
    {
        return 0;
    }

    if (monthlyRate == 0)
    {
        return amount / months;
    }

    double factor =
        pow(
            1 + monthlyRate,
            months);

    return amount *
           monthlyRate *
           factor /
           (factor - 1);
}

void Loan::approve()
{
    status = "APPROVED";
}

void Loan::reject()
{
    status = "REJECTED";
}

void Loan::display() const
{

    cout << "\n========== LOAN ==========\n";

    cout << "Loan ID          : "
         << loanID << endl;

    cout << "Customer ID      : "
         << customerID << endl;

    cout << "Loan Type        : "
         << type << endl;

    cout << "Amount           : Rs. "
         << fixed << setprecision(2)
         << amount << endl;

    cout << "Interest Rate    : "
         << interestRate << "%" << endl;

    cout << "Tenure           : "
         << tenure << " years" << endl;

    cout << "Status           : "
         << status << endl;

    cout << "Remaining Amount : Rs. "
         << remainingAmount << endl;

    cout << "Monthly EMI      : Rs. "
         << calculateEMI()
         << endl;
}

string Loan::getLoanID() const
{
    return loanID;
}

string Loan::getCustomerID() const
{
    return customerID;
}

string Loan::getStatus() const
{
    return status;
}