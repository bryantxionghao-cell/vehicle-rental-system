#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

// ===================================================================
// Derived Class: Car (inherits from Vehicle)
// Demonstrates: Inheritance, Polymorphism (overriding), Encapsulation
// ===================================================================
class Car : public Vehicle {
private:
    int numberOfSeats;
    bool hasAirCon;

public:
    Car(string plateNumber, string brand, string model, double baseRatePerDay,
        int numberOfSeats, bool hasAirCon)
        : Vehicle(plateNumber, brand, model, baseRatePerDay) {
        this->numberOfSeats = numberOfSeats;
        this->hasAirCon = hasAirCon;
    }

    int getNumberOfSeats() const { return numberOfSeats; }
    bool getHasAirCon() const { return hasAirCon; }

    // Overriding pure virtual function from Vehicle (Polymorphism)
    double calculateRentalCost(int days) const override {
        double cost = baseRatePerDay * days;
        if (hasAirCon) {
            cost += 10.0 * days; // surcharge for air-conditioned car
        }
        return cost;
    }

    string getVehicleType() const override {
        return "Car";
    }

    // Overriding virtual function from Vehicle (Polymorphism)
    void displayDetails() const override {
        cout << "---------------------------------------" << endl;
        cout << "Vehicle Type : Car" << endl;
        Vehicle::displayDetails(); // reuse base class implementation
        cout << "Seats        : " << numberOfSeats << endl;
        cout << "Air-Con      : " << (hasAirCon ? "Yes" : "No") << endl;
    }
};

#endif
