# Banking Management System

A simple console-based Banking Management System implemented in **C++** using Object-Oriented Programming (OOP) concepts and file-based persistence.

---

## Features

- **Role-Based Access**:
  - **Customer**: View balance, deposit, withdraw, transfer money, apply for loans, and view transaction history.
  - **Employee**: Create customer accounts, view account lists, and process basic operations.
  - **Manager**: Manage bank operations, view bank statistics, freeze accounts, and view all loans & transactions.
- **Account Types**:
  - **Savings Account**: Supports minimum balance and interest calculations.
  - **Current Account**: Supports overdraft limits.
- **Transactions & Loans**:
  - Track deposit, withdrawal, and transfer history.
  - Apply for and track loans.
- **Data Persistence**:
  - Saves and loads data from plain text files (`customers.txt`, `employees.txt`, `accounts.txt`, `transactions.txt`, `loans.txt`).

---

## Project Structure

- `main.cpp` - Application entry point
- `Bank.h` / `Bank.cpp` - Core banking operations and menus
- `User.h` / `User.cpp` - Base user class
- `Customer.h` / `Customer.cpp` - Customer model
- `Employee.h` / `Employee.cpp` - Employee model
- `Manager.h` / `Manager.cpp` - Manager model
- `Account.h` / `Account.cpp` - Abstract base account class
- `SavingsAccount.h` / `SavingsAccount.cpp` - Savings account implementation
- `CurrentAccount.h` / `CurrentAccount.cpp` - Current account implementation
- `Transaction.h` / `Transaction.cpp` - Transaction tracking model
- `Loan.h` / `Loan.cpp` - Loan management model

---

## How to Compile and Run

### Prerequisites
- A C++ compiler (such as **g++** / MinGW)

### Compilation
Open your terminal in the project directory and run:

```bash
g++ -std=c++11 *.cpp -o BankingManagementSystem
```

### Execution
Run the executable:

- **Windows**:
  ```powershell
  .\BankingManagementSystem.exe
  ```
- **Linux / macOS**:
  ```bash
  ./BankingManagementSystem
  ```

---

## Default Login Credentials

You can use the following pre-configured credentials to test:

| Role | User ID | Password |
|---|---|---|
| **Manager** | `M1` | `1234` |
| **Customer** | `C1` | `1234` |
| **Employee** | `EMPLOYEE` | `1234` |