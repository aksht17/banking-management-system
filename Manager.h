#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager : public Employee {
public:
    Manager();

    Manager(
        string id,
        string name,
        string password,
        string phone,
        string email
    );

    void displayRole() const override;
};

#endif

