#ifndef RENTALTRANSACTION_H
#define RENTALTRANSACTION_H

#include <string>
#include <iostream>
#include <ctime>
#include <cstdio>
#include "Vehicle.h"
#include "Customer.h"
using namespace std;

// ===================================================================
// Class: RentalTransaction
// Demonstrates: Encapsulation, composition/association with
// Vehicle (polymorphic pointer) and Customer
// ===================================================================
class RentalTransaction {
private:
    int transactionID;
    Customer customer;
    Vehicle* vehicle;       // pointer to base class -> enables polymorphism
    string startDate;       // format: YYYY-MM-DD
    string endDate;         // format: YYYY-MM-DD
    int rentalDays;         // computed automatically from startDate and endDate
    double totalCost;
    bool isReturned;

    // Helper: compute number of days between two YYYY-MM-DD date strings
    static int computeRentalDays(const string& start, const string& end) {
        tm t1 = {}, t2 = {};
        sscanf(start.c_str(), "%d-%d-%d", &t1.tm_year, &t1.tm_mon, &t1.tm_mday);
        t1.tm_year -= 1900; t1.tm_mon -= 1; t1.tm_isdst = -1;
        sscanf(end.c_str(),   "%d-%d-%d", &t2.tm_year, &t2.tm_mon, &t2.tm_mday);
        t2.tm_year -= 1900; t2.tm_mon -= 1; t2.tm_isdst = -1;
        time_t time1 = mktime(&t1);
        time_t time2 = mktime(&t2);
        return (int)(difftime(time2, time1) / 86400.0);
    }

public:
    RentalTransaction(int transactionID, Customer customer, Vehicle* vehicle,
                      string startDate, string endDate) {
        this->transactionID = transactionID;
        this->customer      = customer;
        this->vehicle       = vehicle;
        this->startDate     = startDate;
        this->endDate       = endDate;
        // Automatically compute rental duration from the two dates
        this->rentalDays    = computeRentalDays(startDate, endDate);
        // Polymorphic call: actual cost formula depends on the real object type
        // (Car or Motorbike) even though we only have a Vehicle* here.
        this->totalCost     = vehicle->calculateRentalCost(this->rentalDays);
        this->isReturned    = false;
    }

    int     getTransactionID() const { return transactionID; }
    Vehicle* getVehicle()      const { return vehicle; }
    string  getStartDate()     const { return startDate; }
    string  getEndDate()       const { return endDate; }
    int     getRentalDays()    const { return rentalDays; }
    double  getTotalCost()     const { return totalCost; }
    bool    getIsReturned()    const { return isReturned; }

    void markAsReturned() { isReturned = true; }

    void displayReceipt() const {
        cout << "=========================================" << endl;
        cout << "        RENTAL TRANSACTION RECEIPT        " << endl;
        cout << "=========================================" << endl;
        cout << "Transaction ID : " << transactionID << endl;
        cout << "-----------------------------------------" << endl;
        customer.displayDetails();
        cout << "-----------------------------------------" << endl;
        cout << "Vehicle Type   : " << vehicle->getVehicleType() << endl;
        cout << "Plate Number   : " << vehicle->getPlateNumber() << endl;
        cout << "Brand/Model    : " << vehicle->getBrand() << " " << vehicle->getModel() << endl;
        cout << "Start Date     : " << startDate << endl;
        cout << "End Date       : " << endDate << endl;
        cout << "Rental Days    : " << rentalDays << " day(s)" << endl;
        cout << "Total Cost     : RM " << totalCost << endl;
        cout << "Status         : " << (isReturned ? "Returned" : "Ongoing") << endl;
        cout << "=========================================" << endl;
    }
};

#endif
