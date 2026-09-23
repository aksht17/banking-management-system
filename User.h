#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string userID;
    string name;
    string password;
    string phone;
    string email;
    bool active;

public:
    User();
    User(string id, string name, string password,
         string phone, string email);

    virtual ~User();

    bool login(const string& id, const string& password) const;

    virtual void displayProfile() const;

    void changePassword();

    string getID() const;
    string getName() const;

    bool isActive() const;
    void setActive(bool status);

    string getPassword() const;
    string getPhone() const;
    string getEmail() const;
};

#endif
