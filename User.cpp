#include "User.h"
#include <iostream>

using namespace std;

User::User() {
    active = true;
}

User::User(
    string id,
    string name,
    string password,
    string phone,
    string email
) {
    userID = id;
    this->name = name;
    this->password = password;
    this->phone = phone;
    this->email = email;
    active = true;
}

User::~User() {}

bool User::login(
    const string& id,
    const string& pass
) const {
    return active &&
           userID == id &&
           password == pass;
}

void User::displayProfile() const {
    cout << "\n========== PROFILE ==========\n";
    cout << "ID      : " << userID << endl;
    cout << "Name    : " << name << endl;
    cout << "Phone   : " << phone << endl;
    cout << "Email   : " << email << endl;
    cout << "Status  : "
         << (active ? "ACTIVE" : "INACTIVE")
         << endl;
}

void User::changePassword() {
    string oldPassword;
    string newPassword;

    cout << "Enter old password: ";
    cin >> oldPassword;

    if (oldPassword != password) {
        cout << "Incorrect password.\n";
        return;
    }

    cout << "Enter new password: ";
    cin >> newPassword;

    password = newPassword;

    cout << "Password changed successfully.\n";
}

string User::getID() const {
    return userID;
}

string User::getName() const {
    return name;
}

bool User::isActive() const {
    return active;
}

void User::setActive(bool status) {
    active = status;
}

string User::getPassword() const {
    return password;
}

string User::getPhone() const {
    return phone;
}

string User::getEmail() const {
    return email;
}