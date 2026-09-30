#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <cstdlib>
#include "Vehicle.h"
#include "Car.h"
#include "Motorbike.h"
#include "Customer.h"
#include "RentalTransaction.h"
using namespace std;

// ===================================================================
// Class: RentalSystem
// Demonstrates: Encapsulation, management of polymorphic Vehicle objects,
// overall program control (menu-driven)
// ===================================================================
class RentalSystem {
private:
    vector<Vehicle*> vehicles;                 // stores Car and Motorbike objects polymorphically
    vector<Customer> customers;
    vector<RentalTransaction> transactions;
    int nextCustomerID;
    int nextTransactionID;

    // ---------- Helper: input validation ----------
    int getValidIntInput(const string &prompt, int minValue = 0) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= minValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            if (cin.eof()) {
                cout << "\nNo more input available. Exiting program." << endl;
                exit(0);
            }
            cout << "Invalid input. Please enter a number >= " << minValue << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double getValidDoubleInput(const string &prompt, double minValue = 0.0) {
        double value;
        while (true) {
            cout << prompt;
            if (cin >> value && value >= minValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            if (cin.eof()) {
                cout << "\nNo more input available. Exiting program." << endl;
                exit(0);
            }
            cout << "Invalid input. Please enter a number >= " << minValue << "." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string getValidStringInput(const string &prompt) {
        string value;
        while (true) {
            cout << prompt;
            getline(cin, value);
            if (cin.eof() && value.empty()) {
                cout << "\nNo more input available. Exiting program." << endl;
                exit(0);
            }
            if (!value.empty()) {
                return value;
            }
            cout << "Input cannot be empty. Please try again." << endl;
        }
    }

    // Returns true if the string is a valid YYYY-MM-DD date
    bool isValidDate(const string &date) {
        if (date.length() != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;
        for (int i = 0; i < 10; i++) {
            if (i == 4 || i == 7) continue;
            if (!isdigit((unsigned char)date[i])) return false;
        }
        int year, month, day;
        sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
        if (month < 1 || month > 12) return false;
        if (day   < 1 || day   > 31) return false;
        return true;
    }

    // Prompts for a YYYY-MM-DD date and keeps asking until a valid one is entered
    string getValidDateInput(const string &prompt) {
        string value;
        while (true) {
            cout << prompt;
            getline(cin, value);
            if (cin.eof() && value.empty()) {
                cout << "\nNo more input available. Exiting program." << endl;
                exit(0);
            }
            if (isValidDate(value)) return value;
            cout << "Invalid date. Please enter in YYYY-MM-DD format (e.g. 2025-07-01)." << endl;
        }
    }

    // Finds an available vehicle by its plate number; returns nullptr if not found/unavailable
    Vehicle* findAvailableVehicle(const string &plateNumber) {
        for (Vehicle* v : vehicles) {
            if (v->getPlateNumber() == plateNumber && v->getAvailability()) {
                return v;
            }
        }
        return nullptr;
    }

    Vehicle* findVehicleByPlate(const string &plateNumber) {
        for (Vehicle* v : vehicles) {
            if (v->getPlateNumber() == plateNumber) {
                return v;
            }
        }
        return nullptr;
    }

public:
    RentalSystem() {
        nextCustomerID = 1;
        nextTransactionID = 1;
    }

    // Destructor: clean up dynamically allocated Vehicle objects
    ~RentalSystem() {
        for (Vehicle* v : vehicles) {
            delete v;
        }
    }

    // Preload a few sample vehicles so the menu is usable without manual setup
    void loadSampleData() {
        vehicles.push_back(new Car("ABC1234", "Toyota", "Vios", 120.0, 5, true));
        vehicles.push_back(new Car("DEF5678", "Honda", "Civic", 150.0, 5, true));
        vehicles.push_back(new Motorbike("WXY9988", "Yamaha", "Y15ZR", 40.0, 150, true));
        vehicles.push_back(new Motorbike("KLM4455", "Honda", "EX5", 30.0, 110, false));
    }

    // ---------- Menu option 1: Add a new vehicle ----------
    void addVehicle() {
        cout << "\nSelect vehicle type to add:" << endl;
        cout << "1. Car" << endl;
        cout << "2. Motorbike" << endl;
        int choice = getValidIntInput("Enter choice: ", 1);

        string plate = getValidStringInput("Enter plate number: ");
        if (findVehicleByPlate(plate) != nullptr) {
            cout << "A vehicle with this plate number already exists." << endl;
            return;
        }
        string brand = getValidStringInput("Enter brand: ");
        string model = getValidStringInput("Enter model: ");
        double rate = getValidDoubleInput("Enter base rate per day (RM): ", 0.0);

        if (choice == 1) {
            int seats = getValidIntInput("Enter number of seats: ", 1);
            int aircon = getValidIntInput("Has air-con? (1 = Yes, 0 = No): ", 0);
            vehicles.push_back(new Car(plate, brand, model, rate, seats, aircon == 1));
            cout << "Car added successfully." << endl;
        } else {
            int cc = getValidIntInput("Enter engine capacity (CC): ", 1);
            int helmet = getValidIntInput("Requires helmet rental? (1 = Yes, 0 = No): ", 0);
            vehicles.push_back(new Motorbike(plate, brand, model, rate, cc, helmet == 1));
            cout << "Motorbike added successfully." << endl;
        }
    }

    // ---------- Menu option 2: Display all vehicles ----------
    // Demonstrates polymorphism: each vehicle's displayDetails() resolves
    // to the correct overridden version (Car or Motorbike) at runtime.
    void displayAllVehicles() const {
        if (vehicles.empty()) {
            cout << "\nNo vehicles in the system." << endl;
            return;
        }
        cout << "\n========== VEHICLE LIST ==========" << endl;
        for (Vehicle* v : vehicles) {
            v->displayDetails(); // polymorphic call
        }
    }

    // ---------- Menu option 3: Rent a vehicle ----------
    void rentVehicle() {
        string plate = getValidStringInput("\nEnter plate number of vehicle to rent: ");
        Vehicle* v = findAvailableVehicle(plate);
        if (v == nullptr) {
            cout << "Vehicle not found or currently unavailable." << endl;
            return;
        }

        int custID = getValidIntInput("Enter customer ID (0 if new customer): ", 0);
        Customer* selectedCustomer = nullptr;
        for (auto &c : customers) {
            if (c.getCustomerID() == custID) {
                selectedCustomer = &c;
                break;
            }
        }

        Customer newCustomer(0, "", "", "");
        if (selectedCustomer == nullptr) {
            string name = getValidStringInput("Enter customer name: ");
            string ic = getValidStringInput("Enter IC number: ");
            string phone = getValidStringInput("Enter phone number: ");
            newCustomer = Customer(nextCustomerID++, name, ic, phone);
            customers.push_back(newCustomer);
            selectedCustomer = &customers.back();
        }

        string startDate = getValidDateInput("Enter rental start date (YYYY-MM-DD): ");
        string endDate;
        while (true) {
            endDate = getValidDateInput("Enter rental end date   (YYYY-MM-DD): ");
            tm t1 = {}, t2 = {};
            sscanf(startDate.c_str(), "%d-%d-%d", &t1.tm_year, &t1.tm_mon, &t1.tm_mday);
            t1.tm_year -= 1900; t1.tm_mon -= 1; t1.tm_isdst = -1;
            sscanf(endDate.c_str(),   "%d-%d-%d", &t2.tm_year, &t2.tm_mon, &t2.tm_mday);
            t2.tm_year -= 1900; t2.tm_mon -= 1; t2.tm_isdst = -1;
            int days = (int)(difftime(mktime(&t2), mktime(&t1)) / 86400.0);
            if (days >= 1) break;
            cout << "End date must be at least 1 day after start date. Please try again." << endl;
        }

        RentalTransaction transaction(nextTransactionID++, *selectedCustomer, v, startDate, endDate);
        v->setAvailability(false); // mark vehicle as rented out
        transactions.push_back(transaction);

        cout << "\nRental successful! Receipt below:" << endl;
        transaction.displayReceipt();
    }

    // ---------- Menu option 4: Return a vehicle ----------
    void returnVehicle() {
        string plate = getValidStringInput("\nEnter plate number of vehicle being returned: ");
        Vehicle* v = findVehicleByPlate(plate);
        if (v == nullptr) {
            cout << "Vehicle not found." << endl;
            return;
        }
        if (v->getAvailability()) {
            cout << "This vehicle is not currently rented out." << endl;
            return;
        }

        for (auto &t : transactions) {
            if (t.getVehicle()->getPlateNumber() == plate && !t.getIsReturned()) {
                t.markAsReturned();
                v->setAvailability(true);
                cout << "Vehicle " << plate << " has been returned successfully." << endl;
                cout << "Total amount due: RM " << t.getTotalCost() << endl;
                return;
            }
        }
        cout << "No active rental transaction found for this vehicle." << endl;
    }

    // ---------- Menu option 5: Search for a vehicle ----------
    void searchVehicle() {
        string plate = getValidStringInput("\nEnter plate number to search: ");
        for (Vehicle* v : vehicles) {
            if (v->getPlateNumber() == plate) {
                cout << "\nVehicle found:" << endl;
                v->displayDetails(); // polymorphic call
                return;
            }
        }
        cout << "Vehicle with plate number \"" << plate << "\" not found." << endl;
    }

    // ---------- Menu option 6: Display all transactions ----------
    void displayAllTransactions() const {
        if (transactions.empty()) {
            cout << "\nNo transactions recorded yet." << endl;
            return;
        }
        cout << "\n========== TRANSACTION HISTORY ==========" << endl;
        for (const auto &t : transactions) {
            t.displayReceipt();
        }
    }

    // ---------- Menu option 7: Delete a vehicle ----------
    void deleteVehicle() {
        string plate = getValidStringInput("\nEnter plate number of vehicle to delete: ");
        for (size_t i = 0; i < vehicles.size(); i++) {
            if (vehicles[i]->getPlateNumber() == plate) {
                if (!vehicles[i]->getAvailability()) {
                    cout << "Cannot delete a vehicle that is currently rented out." << endl;
                    return;
                }
                delete vehicles[i];
                vehicles.erase(vehicles.begin() + i);
                cout << "Vehicle deleted successfully." << endl;
                return;
            }
        }
        cout << "Vehicle not found." << endl;
    }

    // ---------- Main menu loop ----------
    void run() {
        int choice;
        do {
            cout << "\n=================================================" << endl;
            cout << "      VEHICLE RENTAL SYSTEM - MAIN MENU" << endl;
            cout << "=================================================" << endl;
            cout << "1. Add Vehicle" << endl;
            cout << "2. Display All Vehicles" << endl;
            cout << "3. Rent a Vehicle" << endl;
            cout << "4. Return a Vehicle" << endl;
            cout << "5. Search Vehicle" << endl;
            cout << "6. Display All Transactions" << endl;
            cout << "7. Delete Vehicle" << endl;
            cout << "8. Exit" << endl;
            cout << "=================================================" << endl;

            choice = getValidIntInput("Enter your choice (1-8): ", 1);

            switch (choice) {
                case 1: addVehicle(); break;
                case 2: displayAllVehicles(); break;
                case 3: rentVehicle(); break;
                case 4: returnVehicle(); break;
                case 5: searchVehicle(); break;
                case 6: displayAllTransactions(); break;
                case 7: deleteVehicle(); break;
                case 8: cout << "\nThank you for using the Vehicle Rental System. Goodbye!" << endl; break;
                default: cout << "Invalid choice. Please select 1-8." << endl;
            }
        } while (choice != 8);
    }
};

#endif
