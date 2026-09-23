#include "Manager.h"
#include <iostream>

using namespace std;

Manager::Manager() : Employee() {}

Manager::Manager(
    string id,
    string name,
    string password,
    string phone,
    string email
)
    : Employee(
        id,
        name,
        password,
        phone,
        email,
        "MANAGER"
    ) {}

void Manager::displayRole() const {
    cout << "Role : MANAGER\n";
    cout << "Access Level : ADMINISTRATOR\n";
}
