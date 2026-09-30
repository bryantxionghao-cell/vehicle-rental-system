#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
using namespace std;

// ===================================================================
// Abstract Base Class: Vehicle
// Demonstrates: Abstraction, Encapsulation, base for Inheritance
// ===================================================================
class Vehicle {
protected:
    string plateNumber;     // protected so derived classes can access directly
    string brand;
    string model;
    double baseRatePerDay;  // base rental rate before vehicle-specific adjustments
    bool isAvailable;

public:
    // Constructor
    Vehicle(string plateNumber, string brand, string model, double baseRatePerDay) {
        this->plateNumber = plateNumber;
        this->brand = brand;
        this->model = model;
        this->baseRatePerDay = baseRatePerDay;
        this->isAvailable = true;
    }

    // Virtual destructor - important for proper cleanup of derived objects
    virtual ~Vehicle() {}

    // ---------- Encapsulation: public getters/setters for private/protected data ----------
    string getPlateNumber() const { return plateNumber; }
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    double getBaseRate() const { return baseRatePerDay; }
    bool getAvailability() const { return isAvailable; }

    void setAvailability(bool status) { isAvailable = status; }

    // ---------- Pure virtual functions: force derived classes to implement ----------
    virtual double calculateRentalCost(int days) const = 0; // pure virtual -> makes class abstract
    virtual string getVehicleType() const = 0;

    // ---------- Virtual function: can be overridden (Polymorphism) ----------
    virtual void displayDetails() const {
        cout << "Plate Number : " << plateNumber << endl;
        cout << "Brand/Model  : " << brand << " " << model << endl;
        cout << "Base Rate    : RM " << baseRatePerDay << " / day" << endl;
        cout << "Availability : " << (isAvailable ? "Available" : "Rented Out") << endl;
    }
};

#endif
