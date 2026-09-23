#ifndef BANK_H
#define BANK_H

#include "Customer.h"
#include "Employee.h"
#include "Manager.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "Transaction.h"
#include "Loan.h"

#include <vector>
#include <string>

using namespace std;

class Bank {
private:
    vector<Customer> customers;
    vector<Employee> employees;
    vector<Manager> managers;

    vector<Account*> accounts;

    vector<Transaction> transactions;
    vector<Loan> loans;

    int nextCustomerID;
    int nextAccountID;
    int nextTransactionID;
    int nextLoanID;

public:
    Bank();

    ~Bank();

    void initialize();

    // Customer
    void createCustomer();

    // Account
    void createAccount();

    // Transactions
    void deposit();
    void withdraw();
    void transfer();

    void addTransaction(
        string accountNumber,
        string type,
        double amount,
        string description
    );

    void showTransactions();

    // Account
    void showAccount();
    void freezeAccount();

    // Loans
    void applyLoan();
    void showLoans();

    // Statistics
    void statistics();

    // Search
    Customer* findCustomer(
        const string& id
    );

    Account* findAccount(
        const string& accountNumber
    );

    // Login
    Customer* customerLogin();
    Employee* employeeLogin();
    Manager* managerLogin();

    // Menus
    void customerMenu(
        Customer* customer
    );

    void employeeMenu();

    void managerMenu();

    // Main
    void run();

    // File handling
    void loadData();
    void saveData();

    void saveCustomers();
    void saveEmployees();
    void saveAccounts();
    void saveTransactions();
    void saveLoans();

    void loadCustomers();
    void loadEmployees();
    void loadAccounts();
    void loadTransactions();
    void loadLoans();
};

#endif