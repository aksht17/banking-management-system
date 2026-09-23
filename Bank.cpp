#include "Bank.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <algorithm>

using namespace std;

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

namespace
{

    void clearInput()
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string getInput(const string &prompt)
    {
        cout << prompt;

        string value;
        getline(cin, value);

        return value;
    }

    double getPositiveAmount(const string &prompt)
    {

        double amount;

        while (true)
        {

            cout << prompt;

            if (cin >> amount && amount > 0)
            {
                clearInput();
                return amount;
            }

            cout << "Invalid amount. Please enter a positive value.\n";
            clearInput();
        }
    }

    int getInteger(const string &prompt)
    {

        int value;

        while (true)
        {

            cout << prompt;

            if (cin >> value)
            {
                clearInput();
                return value;
            }

            cout << "Invalid input. Please enter a number.\n";
            clearInput();
        }
    }

    string currentDate()
    {

        time_t now = time(nullptr);

        tm *localTime = localtime(&now);

        stringstream ss;

        ss << setfill('0')
           << setw(2) << localTime->tm_mday
           << "-"
           << setw(2) << localTime->tm_mon + 1
           << "-"
           << localTime->tm_year + 1900;

        return ss.str();
    }

}

// ============================================================
// CONSTRUCTOR
// ============================================================

Bank::Bank()
{

    nextCustomerID = 1;
    nextAccountID = 1001;
    nextTransactionID = 1;
    nextLoanID = 1;
}

// ============================================================
// DESTRUCTOR
// ============================================================

Bank::~Bank()
{

    saveData();

    for (Account *account : accounts)
    {
        delete account;
    }

    accounts.clear();
}

// ============================================================
// LOAD ALL DATA
// ============================================================

void Bank::loadData()
{

    loadCustomers();
    loadEmployees();
    loadAccounts();
    loadTransactions();
    loadLoans();
}

// ============================================================
// INITIALIZATION
// ============================================================

void Bank::initialize()
{

    loadData();

    // --------------------------------------------------------
    // DEFAULT CUSTOMER
    // --------------------------------------------------------

    if (customers.empty())
    {

        customers.push_back(
            Customer(
                "C1",
                "Krish",
                "1234",
                "9876543210",
                "krish@example.com"));

        nextCustomerID = 2;

        cout << "Default customer created.\n";
    }

    // --------------------------------------------------------
    // DEFAULT EMPLOYEE
    // --------------------------------------------------------

    if (employees.empty())
    {

        employees.push_back(
            Employee(
                "E1",
                "Bank Employee",
                "1234",
                "9876543211",
                "employee@bank.com",
                "EMPLOYEE"));

        cout << "Default employee created.\n";
    }

    // --------------------------------------------------------
    // DEFAULT MANAGER
    // --------------------------------------------------------

    if (managers.empty())
    {

        managers.push_back(
            Manager(
                "M1",
                "Bank Manager",
                "1234",
                "9876543212",
                "manager@bank.com"));

        cout << "Default manager created.\n";
    }

    cout << "\n========================================\n";
    cout << "        DEFAULT LOGIN CREDENTIALS\n";
    cout << "========================================\n";

    cout << "Customer : C1 / 1234\n";
    cout << "Employee : E1 / 1234\n";
    cout << "Manager  : M1 / 1234\n";

    cout << "========================================\n";
}

// ============================================================
// FIND CUSTOMER
// ============================================================

Customer *Bank::findCustomer(
    const string &id)
{

    for (auto &customer : customers)
    {

        if (customer.getID() == id)
        {
            return &customer;
        }
    }

    return nullptr;
}

// ============================================================
// FIND ACCOUNT
// ============================================================

Account *Bank::findAccount(
    const string &accountNumber)
{

    for (Account *account : accounts)
    {

        if (account->getAccountNumber() == accountNumber)
        {

            return account;
        }
    }

    return nullptr;
}

// ============================================================
// CREATE CUSTOMER
// ============================================================

void Bank::createCustomer()
{

    cout << "\n========== CREATE CUSTOMER ==========\n";

    string id =
        "C" + to_string(nextCustomerID++);

    string name =
        getInput("Enter customer name: ");

    string password =
        getInput("Enter password: ");

    string phone =
        getInput("Enter phone number: ");

    string email =
        getInput("Enter email: ");

    customers.push_back(
        Customer(
            id,
            name,
            password,
            phone,
            email));

    cout << "\nCustomer created successfully.\n";
    cout << "Customer ID: " << id << endl;

    saveCustomers();
}

// ============================================================
// CREATE ACCOUNT
// ============================================================

void Bank::createAccount()
{

    cout << "\n========== CREATE ACCOUNT ==========\n";

    string customerID =
        getInput("Enter customer ID: ");

    Customer *customer =
        findCustomer(customerID);

    if (customer == nullptr)
    {

        cout << "Customer not found.\n";
        return;
    }

    cout << "\n1. Savings Account\n";
    cout << "2. Current Account\n";

    int choice =
        getInteger("Enter account type: ");

    if (choice != 1 && choice != 2)
    {

        cout << "Invalid account type.\n";
        return;
    }

    double initialBalance =
        getPositiveAmount(
            "Enter initial deposit: ");

    if (choice == 1 &&
        initialBalance < 1000)
    {

        cout << "Savings account requires "
                "minimum balance of Rs.1000.\n";

        return;
    }

    string accountNumber =
        "ACC" + to_string(nextAccountID++);

    Account *account = nullptr;

    if (choice == 1)
    {

        account =
            new SavingsAccount(
                accountNumber,
                customerID,
                initialBalance);
    }
    else
    {

        account =
            new CurrentAccount(
                accountNumber,
                customerID,
                initialBalance);
    }

    accounts.push_back(account);

    customer->addAccount(accountNumber);

    addTransaction(
        accountNumber,
        "DEPOSIT",
        initialBalance,
        "Initial Deposit");

    cout << "\nAccount created successfully.\n";
    cout << "Account Number: "
         << accountNumber << endl;

    saveAccounts();
    saveCustomers();
    saveTransactions();
}

// ============================================================
// ADD TRANSACTION
// ============================================================

void Bank::addTransaction(
    string accountNumber,
    string type,
    double amount,
    string description)
{

    string transactionID =
        "TXN" + to_string(nextTransactionID++);

    transactions.push_back(
        Transaction(
            transactionID,
            accountNumber,
            type,
            amount,
            currentDate(),
            description));
}

// ============================================================
// DEPOSIT
// ============================================================

void Bank::deposit()
{

    cout << "\n========== DEPOSIT ==========\n";

    string accountNumber =
        getInput("Enter account number: ");

    Account *account =
        findAccount(accountNumber);

    if (account == nullptr)
    {

        cout << "Account not found.\n";
        return;
    }

    double amount =
        getPositiveAmount(
            "Enter amount to deposit: ");

    if (account->deposit(amount))
    {

        addTransaction(
            accountNumber,
            "DEPOSIT",
            amount,
            "Cash Deposit");

        cout << "Deposit successful.\n";

        saveAccounts();
        saveTransactions();
    }
}

// ============================================================
// WITHDRAW
// ============================================================

void Bank::withdraw()
{

    cout << "\n========== WITHDRAW ==========\n";

    string accountNumber =
        getInput("Enter account number: ");

    Account *account =
        findAccount(accountNumber);

    if (account == nullptr)
    {

        cout << "Account not found.\n";
        return;
    }

    double amount =
        getPositiveAmount(
            "Enter amount to withdraw: ");

    if (account->withdraw(amount))
    {

        addTransaction(
            accountNumber,
            "WITHDRAWAL",
            amount,
            "Cash Withdrawal");

        cout << "Withdrawal successful.\n";

        saveAccounts();
        saveTransactions();
    }
}

// ============================================================
// TRANSFER
// ============================================================

void Bank::transfer()
{

    cout << "\n========== MONEY TRANSFER ==========\n";

    string senderNumber =
        getInput("Enter sender account: ");

    string receiverNumber =
        getInput("Enter receiver account: ");

    if (senderNumber == receiverNumber)
    {

        cout << "Sender and receiver cannot "
                "be the same account.\n";

        return;
    }

    Account *sender =
        findAccount(senderNumber);

    Account *receiver =
        findAccount(receiverNumber);

    if (sender == nullptr ||
        receiver == nullptr)
    {

        cout << "Sender or receiver account "
                "not found.\n";

        return;
    }

    double amount =
        getPositiveAmount(
            "Enter transfer amount: ");

    if (!sender->withdraw(amount))
    {
        return;
    }

    if (!receiver->deposit(amount))
    {

        sender->deposit(amount);

        cout << "Transfer failed. "
                "Amount restored to sender.\n";

        return;
    }

    addTransaction(
        senderNumber,
        "TRANSFER_OUT",
        amount,
        "Transfer to " + receiverNumber);

    addTransaction(
        receiverNumber,
        "TRANSFER_IN",
        amount,
        "Transfer from " + senderNumber);

    cout << "\nTransfer successful.\n";

    saveAccounts();
    saveTransactions();
}

// ============================================================
// SHOW ACCOUNT
// ============================================================

void Bank::showAccount()
{

    cout << "\n========== ACCOUNT DETAILS ==========\n";

    string accountNumber =
        getInput("Enter account number: ");

    Account *account =
        findAccount(accountNumber);

    if (account == nullptr)
    {

        cout << "Account not found.\n";
        return;
    }

    account->display();

    cout << "\nCalculated Interest: Rs. "
         << fixed << setprecision(2)
         << account->calculateInterest()
         << endl;
}

// ============================================================
// SHOW TRANSACTIONS
// ============================================================

void Bank::showTransactions()
{

    cout << "\n========== TRANSACTION HISTORY ==========\n";

    string accountNumber =
        getInput("Enter account number: ");

    cout << "\n";

    cout << left
         << setw(12) << "ID"
         << setw(12) << "Account"
         << setw(18) << "Type"
         << setw(12) << "Amount"
         << setw(15) << "Date"
         << "Description"
         << endl;

    cout << string(95, '-') << endl;

    bool found = false;

    for (const Transaction &transaction :
         transactions)
    {

        if (transaction.getAccountNumber() == accountNumber)
        {

            transaction.display();

            found = true;
        }
    }

    if (!found)
    {

        cout << "No transactions found "
                "for this account.\n";
    }
}

// ============================================================
// FREEZE ACCOUNT
// ============================================================

void Bank::freezeAccount()
{

    cout << "\n========== FREEZE ACCOUNT ==========\n";

    string accountNumber =
        getInput("Enter account number: ");

    Account *account =
        findAccount(accountNumber);

    if (account == nullptr)
    {

        cout << "Account not found.\n";
        return;
    }

    if (!account->isActive())
    {

        cout << "Account is already inactive.\n";
        return;
    }

    account->setActive(false);

    cout << "Account frozen successfully.\n";

    saveAccounts();
}

// ============================================================
// APPLY FOR LOAN
// ============================================================

void Bank::applyLoan()
{

    cout << "\n========== LOAN APPLICATION ==========\n";

    string customerID =
        getInput("Enter customer ID: ");

    Customer *customer =
        findCustomer(customerID);

    if (customer == nullptr)
    {

        cout << "Customer not found.\n";
        return;
    }

    cout << "\nLoan Types:\n";
    cout << "1. Personal Loan\n";
    cout << "2. Home Loan\n";
    cout << "3. Education Loan\n";
    cout << "4. Vehicle Loan\n";

    int choice =
        getInteger("Enter choice: ");

    string type;

    switch (choice)
    {

    case 1:
        type = "PERSONAL";
        break;

    case 2:
        type = "HOME";
        break;

    case 3:
        type = "EDUCATION";
        break;

    case 4:
        type = "VEHICLE";
        break;

    default:
        cout << "Invalid loan type.\n";
        return;
    }

    double amount =
        getPositiveAmount(
            "Enter loan amount: ");

    double interestRate;

    while (true)
    {

        cout << "Enter annual interest rate (%): ";

        if (cin >> interestRate &&
            interestRate > 0)
        {

            clearInput();
            break;
        }

        cout << "Invalid interest rate.\n";
        clearInput();
    }

    int tenure =
        getInteger(
            "Enter tenure in years: ");

    if (tenure <= 0)
    {

        cout << "Invalid tenure.\n";
        return;
    }

    string loanID =
        "LOAN" + to_string(nextLoanID++);

    Loan loan(
        loanID,
        customerID,
        amount,
        interestRate,
        tenure,
        type);

    loans.push_back(loan);

    customer->addLoan(loanID);

    cout << "\nLoan application submitted.\n";

    cout << "Loan ID: "
         << loanID << endl;

    cout << "Estimated Monthly EMI: Rs. "
         << fixed << setprecision(2)
         << loan.calculateEMI()
         << endl;

    saveLoans();
    saveCustomers();
}

// ============================================================
// SHOW LOANS
// ============================================================

void Bank::showLoans()
{

    cout << "\n========== LOANS ==========\n";

    string customerID =
        getInput("Enter customer ID: ");

    bool found = false;

    for (const Loan &loan :
         loans)
    {

        if (loan.getCustomerID() ==
            customerID)
        {

            loan.display();

            found = true;
        }
    }

    if (!found)
    {

        cout << "No loans found.\n";
    }
}

// ============================================================
// BANK STATISTICS
// ============================================================

void Bank::statistics()
{

    cout << "\n========== BANK STATISTICS ==========\n";

    double totalBalance = 0;

    int activeAccounts = 0;

    for (Account *account :
         accounts)
    {

        totalBalance += account->getBalance();

        if (account->isActive())
        {
            activeAccounts++;
        }
    }

    cout << "Total Customers      : "
         << customers.size() << endl;

    cout << "Total Employees      : "
         << employees.size() << endl;

    cout << "Total Managers       : "
         << managers.size() << endl;

    cout << "Total Accounts       : "
         << accounts.size() << endl;

    cout << "Active Accounts      : "
         << activeAccounts << endl;

    cout << "Total Transactions   : "
         << transactions.size() << endl;

    cout << "Total Loans          : "
         << loans.size() << endl;

    cout << "Total Bank Balance   : Rs. "
         << fixed << setprecision(2)
         << totalBalance
         << endl;
}

// ============================================================
// CUSTOMER LOGIN
// ============================================================

Customer *Bank::customerLogin()
{

    cout << "\n========== CUSTOMER LOGIN ==========\n";

    string id =
        getInput("Customer ID: ");

    string password =
        getInput("Password: ");

    for (auto &customer :
         customers)
    {

        if (customer.login(id, password))
        {

            cout << "\nLogin successful.\n";

            return &customer;
        }
    }

    cout << "Invalid credentials.\n";

    return nullptr;
}

// ============================================================
// EMPLOYEE LOGIN
// ============================================================

Employee *Bank::employeeLogin()
{

    cout << "\n========== EMPLOYEE LOGIN ==========\n";

    string id =
        getInput("Employee ID: ");

    string password =
        getInput("Password: ");

    for (auto &employee :
         employees)
    {

        if (employee.login(id, password))
        {

            cout << "\nLogin successful.\n";

            return &employee;
        }
    }

    cout << "Invalid credentials.\n";

    return nullptr;
}

// ============================================================
// MANAGER LOGIN
// ============================================================

Manager *Bank::managerLogin()
{

    cout << "\n========== MANAGER LOGIN ==========\n";

    string id =
        getInput("Manager ID: ");

    string password =
        getInput("Password: ");

    // --------------------------------------------------------
    // DEFAULT MANAGER LOGIN
    // --------------------------------------------------------

    if (id == "M1" && password == "1234")
    {

        // Check if M1 already exists
        for (auto &manager : managers)
        {

            if (manager.getID() == "M1")
            {

                cout << "\nLogin successful.\n";

                return &manager;
            }
        }

        // If M1 is not loaded, create it
        managers.push_back(
            Manager(
                "M1",
                "Bank Manager",
                "1234",
                "9876543212",
                "manager@bank.com"));

        cout << "\nLogin successful.\n";

        return &managers.back();
    }

    // --------------------------------------------------------
    // OTHER MANAGERS
    // --------------------------------------------------------

    for (auto &manager :
         managers)
    {

        if (manager.login(id, password))
        {

            cout << "\nLogin successful.\n";

            return &manager;
        }
    }

    cout << "Invalid credentials.\n";

    return nullptr;
}

// ============================================================
// CUSTOMER MENU
// ============================================================

void Bank::customerMenu(
    Customer *customer)
{

    while (true)
    {

        cout << "\n";
        cout << "=====================================\n";
        cout << "           CUSTOMER MENU\n";
        cout << "=====================================\n";

        cout << "Welcome, "
             << customer->getName()
             << "!\n\n";

        cout << "1.  View Profile\n";
        cout << "2.  View My Accounts\n";
        cout << "3.  View Account Details\n";
        cout << "4.  Deposit Money\n";
        cout << "5.  Withdraw Money\n";
        cout << "6.  Transfer Money\n";
        cout << "7.  Transaction History\n";
        cout << "8.  Apply for Loan\n";
        cout << "9.  View Loans\n";
        cout << "10. Change Password\n";
        cout << "0.  Logout\n";

        int choice =
            getInteger("\nEnter choice: ");

        switch (choice)
        {

        case 1:
            customer->displayProfile();
            break;

        case 2:
            customer->displayAccounts();
            break;

        case 3:
            showAccount();
            break;

        case 4:
            deposit();
            break;

        case 5:
            withdraw();
            break;

        case 6:
            transfer();
            break;

        case 7:
            showTransactions();
            break;

        case 8:
            applyLoan();
            break;

        case 9:
            showLoans();
            break;

        case 10:
            customer->changePassword();
            break;

        case 0:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}

// ============================================================
// EMPLOYEE MENU
// ============================================================

void Bank::employeeMenu()
{

    while (true)
    {

        cout << "\n";
        cout << "=====================================\n";
        cout << "           EMPLOYEE MENU\n";
        cout << "=====================================\n";

        cout << "1.  Create Customer\n";
        cout << "2.  Create Account\n";
        cout << "3.  View Account\n";
        cout << "4.  Deposit Money\n";
        cout << "5.  Withdraw Money\n";
        cout << "6.  Transfer Money\n";
        cout << "7.  Transaction History\n";
        cout << "8.  Apply Loan\n";
        cout << "9.  View Loans\n";
        cout << "10. Freeze Account\n";
        cout << "0.  Logout\n";

        int choice =
            getInteger("\nEnter choice: ");

        switch (choice)
        {

        case 1:
            createCustomer();
            break;

        case 2:
            createAccount();
            break;

        case 3:
            showAccount();
            break;

        case 4:
            deposit();
            break;

        case 5:
            withdraw();
            break;

        case 6:
            transfer();
            break;

        case 7:
            showTransactions();
            break;

        case 8:
            applyLoan();
            break;

        case 9:
            showLoans();
            break;

        case 10:
            freezeAccount();
            break;

        case 0:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}

// ============================================================
// MANAGER MENU
// ============================================================

void Bank::managerMenu()
{

    while (true)
    {

        cout << "\n";
        cout << "=====================================\n";
        cout << "           MANAGER MENU\n";
        cout << "=====================================\n";

        cout << "1.  Create Customer\n";
        cout << "2.  Create Account\n";
        cout << "3.  View Account\n";
        cout << "4.  Deposit Money\n";
        cout << "5.  Withdraw Money\n";
        cout << "6.  Transfer Money\n";
        cout << "7.  Transaction History\n";
        cout << "8.  Apply Loan\n";
        cout << "9.  View Loans\n";
        cout << "10. Freeze Account\n";
        cout << "11. Bank Statistics\n";
        cout << "0.  Logout\n";

        int choice =
            getInteger("\nEnter choice: ");

        switch (choice)
        {

        case 1:
            createCustomer();
            break;

        case 2:
            createAccount();
            break;

        case 3:
            showAccount();
            break;

        case 4:
            deposit();
            break;

        case 5:
            withdraw();
            break;

        case 6:
            transfer();
            break;

        case 7:
            showTransactions();
            break;

        case 8:
            applyLoan();
            break;

        case 9:
            showLoans();
            break;

        case 10:
            freezeAccount();
            break;

        case 11:
            statistics();
            break;

        case 0:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice.\n";
        }
    }
}

// ============================================================
// RUN APPLICATION
// ============================================================

void Bank::run()
{

    initialize();

    while (true)
    {

        cout << "\n";
        cout << "============================================\n";
        cout << "       BANKING MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Customer Login\n";
        cout << "2. Employee Login\n";
        cout << "3. Manager Login\n";
        cout << "0. Exit\n";

        int choice =
            getInteger("\nEnter choice: ");

        switch (choice)
        {

        case 1:
        {

            Customer *customer =
                customerLogin();

            if (customer != nullptr)
            {
                customerMenu(customer);
            }

            break;
        }

        case 2:
        {

            Employee *employee =
                employeeLogin();

            if (employee != nullptr)
            {
                employeeMenu();
            }

            break;
        }

        case 3:
        {

            Manager *manager =
                managerLogin();

            if (manager != nullptr)
            {
                managerMenu();
            }

            break;
        }

        case 0:

            cout << "\nThank you for using "
                    "Banking Management System.\n";

            return;

        default:

            cout << "Invalid choice.\n";
        }
    }
}

// ============================================================
// SAVE ALL DATA
// ============================================================

void Bank::saveData()
{

    saveCustomers();
    saveEmployees();
    saveAccounts();
    saveTransactions();
    saveLoans();
}

// ============================================================
// SAVE CUSTOMERS
// ============================================================

void Bank::saveCustomers()
{

    ofstream file("customers.txt");

    if (!file)
    {
        return;
    }

    for (const Customer &customer :
         customers)
    {

        file
            << customer.getID() << "|"
            << customer.getName() << "|"
            << customer.getPassword() << "|"
            << customer.getPhone() << "|"
            << customer.getEmail() << "|"
            << customer.isActive()
            << "|";

        const vector<string> &accountList =
            customer.getAccounts();

        for (size_t i = 0;
             i < accountList.size();
             i++)
        {

            file << accountList[i];

            if (i + 1 < accountList.size())
            {
                file << ";";
            }
        }

        file << "|";

        const vector<string> &loanList =
            customer.getLoans();

        for (size_t i = 0;
             i < loanList.size();
             i++)
        {

            file << loanList[i];

            if (i + 1 < loanList.size())
            {
                file << ";";
            }
        }

        file << "\n";
    }

    file.close();
}

// ============================================================
// SAVE EMPLOYEES + MANAGERS
// ============================================================

void Bank::saveEmployees()
{

    ofstream file("employees.txt");

    if (!file)
    {
        return;
    }

    // Save employees
    for (const Employee &employee :
         employees)
    {

        file
            << "EMPLOYEE" << "|"
            << employee.getID() << "|"
            << employee.getName() << "|"
            << employee.getPassword() << "|"
            << employee.getPhone() << "|"
            << employee.getEmail() << "|"
            << employee.getDesignation() << "|"
            << employee.isActive()
            << "\n";
    }

    // Save managers
    for (const Manager &manager :
         managers)
    {

        file
            << "MANAGER" << "|"
            << manager.getID() << "|"
            << manager.getName() << "|"
            << manager.getPassword() << "|"
            << manager.getPhone() << "|"
            << manager.getEmail() << "|"
            << manager.getDesignation() << "|"
            << manager.isActive()
            << "\n";
    }

    file.close();
}

// ============================================================
// SAVE ACCOUNTS
// ============================================================

void Bank::saveAccounts()
{

    ofstream file("accounts.txt");

    if (!file)
    {
        return;
    }

    for (Account *account :
         accounts)
    {

        file
            << account->getAccountNumber()
            << "|"
            << account->getCustomerID()
            << "|"
            << account->getType()
            << "|"
            << fixed
            << setprecision(2)
            << account->getBalance()
            << "|"
            << account->isActive()
            << "\n";
    }

    file.close();
}

// ============================================================
// SAVE TRANSACTIONS
// ============================================================

void Bank::saveTransactions()
{

    ofstream file("transactions.txt");

    if (!file)
    {
        return;
    }

    for (const Transaction &transaction :
         transactions)
    {

        file
            << transaction.serialize()
            << "\n";
    }

    file.close();
}

// ============================================================
// SAVE LOANS
// ============================================================

void Bank::saveLoans()
{

    ofstream file("loans.txt");

    if (!file)
    {
        return;
    }

    for (const Loan &loan :
         loans)
    {

        file
            << loan.getLoanID()
            << "|"
            << loan.getCustomerID()
            << "|"
            << loan.getStatus()
            << "\n";
    }

    file.close();
}

// ============================================================
// LOAD CUSTOMERS
// ============================================================

void Bank::loadCustomers()
{

    ifstream file("customers.txt");

    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {

        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string id;
        string name;
        string password;
        string phone;
        string email;
        string active;
        string accountList;
        string loanList;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, email, '|');
        getline(ss, active, '|');
        getline(ss, accountList, '|');
        getline(ss, loanList, '|');

        Customer customer(
            id,
            name,
            password,
            phone,
            email);

        customer.setActive(
            active == "1");

        if (!accountList.empty())
        {

            stringstream accountStream(
                accountList);

            string accountNumber;

            while (
                getline(
                    accountStream,
                    accountNumber,
                    ';'))
            {

                customer.addAccount(
                    accountNumber);
            }
        }

        if (!loanList.empty())
        {

            stringstream loanStream(
                loanList);

            string loanID;

            while (
                getline(
                    loanStream,
                    loanID,
                    ';'))
            {

                customer.addLoan(loanID);
            }
        }

        customers.push_back(customer);

        if (id.size() > 1)
        {

            try
            {

                int number =
                    stoi(id.substr(1));

                nextCustomerID =
                    max(
                        nextCustomerID,
                        number + 1);
            }
            catch (...)
            {
            }
        }
    }

    file.close();
}

// ============================================================
// LOAD EMPLOYEES + MANAGERS
// ============================================================

void Bank::loadEmployees()
{

    ifstream file("employees.txt");

    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {

        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string role;
        string id;
        string name;
        string password;
        string phone;
        string email;
        string designation;
        string active;

        getline(ss, role, '|');
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, password, '|');
        getline(ss, phone, '|');
        getline(ss, email, '|');
        getline(ss, designation, '|');
        getline(ss, active, '|');

        if (role == "MANAGER")
        {

            Manager manager(
                id,
                name,
                password,
                phone,
                email);

            manager.setActive(
                active == "1");

            managers.push_back(manager);
        }
        else
        {

            Employee employee(
                id,
                name,
                password,
                phone,
                email,
                designation);

            employee.setActive(
                active == "1");

            employees.push_back(employee);
        }
    }

    file.close();
}

// ============================================================
// LOAD ACCOUNTS
// ============================================================

void Bank::loadAccounts()
{

    ifstream file("accounts.txt");

    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {

        if (line.empty())
        {
            continue;
        }

        stringstream ss(line);

        string accountNumber;
        string customerID;
        string type;
        string balanceString;
        string activeString;

        getline(ss, accountNumber, '|');
        getline(ss, customerID, '|');
        getline(ss, type, '|');
        getline(ss, balanceString, '|');
        getline(ss, activeString, '|');

        try
        {

            double balance =
                stod(balanceString);

            Account *account = nullptr;

            if (type == "SAVINGS")
            {

                account =
                    new SavingsAccount(
                        accountNumber,
                        customerID,
                        balance);
            }
            else if (type == "CURRENT")
            {

                account =
                    new CurrentAccount(
                        accountNumber,
                        customerID,
                        balance);
            }

            if (account != nullptr)
            {

                account->setActive(
                    activeString == "1");

                accounts.push_back(account);
            }

            if (accountNumber.size() > 3)
            {

                int number =
                    stoi(
                        accountNumber.substr(3));

                nextAccountID =
                    max(
                        nextAccountID,
                        number + 1);
            }
        }
        catch (...)
        {

            cout << "Warning: Invalid account record.\n";
        }
    }

    file.close();
}

// ============================================================
// LOAD TRANSACTIONS
// ============================================================

void Bank::loadTransactions()
{

    ifstream file("transactions.txt");

    if (!file)
    {
        return;
    }

    string line;

    while (getline(file, line))
    {

        if (line.empty())
        {
            continue;
        }

        try
        {

            Transaction transaction =
                Transaction::deserialize(line);

            transactions.push_back(transaction);

            stringstream ss(line);

            string id;

            getline(ss, id, '|');

            if (id.size() > 3)
            {

                int number =
                    stoi(id.substr(3));

                nextTransactionID =
                    max(
                        nextTransactionID,
                        number + 1);
            }
        }
        catch (...)
        {

            cout << "Warning: Invalid transaction record.\n";
        }
    }

    file.close();
}

// ============================================================
// LOAD LOANS
// ============================================================

void Bank::loadLoans()
{

    /*
       Full loan persistence will be implemented
       after adding complete Loan serialization.
    */

    ifstream file("loans.txt");

    if (!file)
    {
        return;
    }

    file.close();
}