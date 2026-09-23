#include "Employee.h"
#include <iostream>

using namespace std;

Employee::Employee() : User() {}

Employee::Employee(
    string id,
    string name,
    string password,
    string phone,
    string email,
    string designation
)
    : User(id, name, password, phone, email) {

    this->designation = designation;
}

string Employee::getDesignation() const {
    return designation;
}

void Employee::displayRole() const {
    cout << "Role : " << designation << endl;
}

void Employee::displayProfile() const {
    User::displayProfile();
    displayRole();
}
