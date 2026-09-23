#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"

using namespace std;

class Employee : public User {
protected:
    string designation;

public:
    Employee();

    Employee(
        string id,
        string name,
        string password,
        string phone,
        string email,
        string designation
    );

    string getDesignation() const;

    virtual void displayRole() const;

    void displayProfile() const override;
};

#endif
