#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include "Vehicle.h"

// ===================================================================
// Derived Class: Motorbike (inherits from Vehicle)
// Demonstrates: Inheritance, Polymorphism (overriding), Encapsulation
// ===================================================================
class Motorbike : public Vehicle {
private:
    int engineCapacityCC;
    bool requiresHelmetRental;

public:
    Motorbike(string plateNumber, string brand, string model, double baseRatePerDay,
               int engineCapacityCC, bool requiresHelmetRental)
        : Vehicle(plateNumber, brand, model, baseRatePerDay) {
        this->engineCapacityCC = engineCapacityCC;
        this->requiresHelmetRental = requiresHelmetRental;
    }

    int getEngineCapacity() const { return engineCapacityCC; }
    bool getRequiresHelmet() const { return requiresHelmetRental; }

    // Overriding pure virtual function from Vehicle (Polymorphism)
    double calculateRentalCost(int days) const override {
        double cost = baseRatePerDay * days;
        if (requiresHelmetRental) {
            cost += 5.0 * days; // helmet rental surcharge
        }
        return cost;
    }

    string getVehicleType() const override {
        return "Motorbike";
    }

    // Overriding virtual function from Vehicle (Polymorphism)
    void displayDetails() const override {
        cout << "---------------------------------------" << endl;
        cout << "Vehicle Type : Motorbike" << endl;
        Vehicle::displayDetails(); // reuse base class implementation
        cout << "Engine (CC)  : " << engineCapacityCC << endl;
        cout << "Helmet Rental: " << (requiresHelmetRental ? "Required (extra fee)" : "Not Required") << endl;
    }
};

#endif
