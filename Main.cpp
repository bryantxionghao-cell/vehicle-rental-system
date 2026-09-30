// =====================================================================
// Vehicle Rental System
// PFD1423: Object-Oriented Programming - Group Assignment
//
// A console-based Vehicle Rental System demonstrating the four
// pillars of Object-Oriented Programming:
//   - Encapsulation : private/protected attributes with public
//                      getters/setters across all classes
//   - Inheritance   : Car and Motorbike inherit from Vehicle
//   - Polymorphism  : calculateRentalCost() and displayDetails()
//                      behave differently depending on the actual
//                      object type (Car vs Motorbike) at runtime
//   - Abstraction   : Vehicle is an abstract class with pure virtual
//                      functions, hiding implementation detail from
//                      the rest of the system
// =====================================================================

#include <iostream>
#include "RentalSystem.h"
using namespace std;

int main() {
    RentalSystem system;
    system.loadSampleData();

    cout << "=================================================" << endl;
    cout << "   WELCOME TO THE VEHICLE RENTAL SYSTEM (C++)" << endl;
    cout << "=================================================" << endl;

    system.run();

    return 0;
}
