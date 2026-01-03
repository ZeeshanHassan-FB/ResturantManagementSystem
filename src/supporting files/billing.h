#ifndef BILLING_H
#define BILLING_H
#include <string>
using namespace std;

// Main function to show the bill UI
void generateBill();

// Checks if a bill is "Paid" or "Pending" (Returns string)
string checkBillStatus(int orderID);

// Updates the status in bills.csv
void updateBillStatus(int orderID, int total, string status);

#endif