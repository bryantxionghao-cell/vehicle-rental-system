#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
using namespace std;

// ===================================================================
// Class: Customer
// Demonstrates: Encapsulation (private data, public accessors)
// ===================================================================
class Customer {
private:
    int customerID;
    string name;
    string icNumber;
    string phoneNumber;

public:
    Customer() {
        this->customerID = 0;
        this->name = "";
        this->icNumber = "";
        this->phoneNumber = "";
    }

    Customer(int customerID, string name, string icNumber, string phoneNumber) {
        this->customerID = customerID;
        this->name = name;
        this->icNumber = icNumber;
        this->phoneNumber = phoneNumber;
    }

    // Encapsulation: controlled access via getters
    int getCustomerID() const { return customerID; }
    string getName() const { return name; }
    string getICNumber() const { return icNumber; }
    string getPhoneNumber() const { return phoneNumber; }

    void setPhoneNumber(string phoneNumber) { this->phoneNumber = phoneNumber; }

    void displayDetails() const {
        cout << "Customer ID  : " << customerID << endl;
        cout << "Name         : " << name << endl;
        cout << "IC Number    : " << icNumber << endl;
        cout << "Phone Number : " << phoneNumber << endl;
    }
};

#endif
