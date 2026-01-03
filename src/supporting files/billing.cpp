#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "billing.h"
#include "tables.h"

using namespace std;

// Helper: Check status in bills.csv
string checkBillStatus(int orderID) {
    ifstream f("bills.csv");
    if(!f) return "Pending"; // If file doesn't exist, assume Pending

    string line;
    while(getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, tot, stat;
        
        getline(ss, id, ',');
        getline(ss, tot, ',');
        getline(ss, stat, ',');

        if(!id.empty() && stoi(id) == orderID) {
            return stat; // Returns "Paid" or "Pending"
        }
    }
    return "Pending"; // Default if ID not found in bills.csv
}

// Helper: Update or Add status in bills.csv
void updateBillStatus(int orderID, int total, string status) {
    vector<string> lines;
    ifstream f("bills.csv");
    string line;
    bool found = false;

    // Read all existing lines
    while(getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, tot, stat;
        getline(ss, id, ',');
        
        // If we find the ID, we replace this line with the new status
        if(!id.empty() && stoi(id) == orderID) {
            stringstream newLine;
            newLine << orderID << "," << total << "," << status;
            lines.push_back(newLine.str());
            found = true;
        } else {
            lines.push_back(line);
        }
    }
    f.close();

    // If it was a new bill, add it to the list
    if(!found) {
        stringstream newLine;
        newLine << orderID << "," << total << "," << status;
        lines.push_back(newLine.str());
    }

    // Rewrite the file
    ofstream out("bills.csv");
    for(size_t i = 0; i < lines.size(); i++) {
        out << lines[i] << endl;
    }
    out.close();
}

void generateBill() {
    int opt;
    int searchId;
    string filename;
    
    cout << "\n1. Dine-In Bill\n2. Online Order Bill\nChoose: ";
    cin >> opt;

    if (opt == 1) filename = "dine_in_order.csv";
    else filename = "online_order.csv";

    cout << "Enter Order ID: ";
    cin >> searchId;

    ifstream f(filename);
    if (!f) {
        cout << "Order file not found.\n";
        return;
    }

    string line;
    int total = 0;
    bool found = false;
    int tableNoToFree = -1;

    cout << "\n\n**************** BILL RECEIPT ****************\n";
    cout << "Item\t\tQty\tPrice\tTotal\n";
    cout << "----------------------------------------------\n";

    // 1. Calculate Total from Order File
    while (getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string fid, f2, f3, fItem, fQty, fPrice;

        getline(ss, fid, ',');
        
        if(opt == 1) {
            // Dine In Format: ID, Table, Item, Qty, Price
            getline(ss, f2, ','); // Table Number
            getline(ss, fItem, ',');
            getline(ss, fQty, ',');
            getline(ss, fPrice, ',');
            
            if(stoi(fid) == searchId) tableNoToFree = stoi(f2);
        } else {
            // Online Format: ID, Name, Phone, Item, Qty, Price
            getline(ss, f2, ','); 
            getline(ss, f3, ','); 
            getline(ss, fItem, ',');
            getline(ss, fQty, ',');
            getline(ss, fPrice, ',');
        }

        if(stoi(fid) == searchId) {
            int q = stoi(fQty);
            int p = stoi(fPrice);
            int t = q * p;
            cout << fItem << "\t\t" << q << "\t" << p << "\t" << t << endl;
            total += t;
            found = true;
        }
    }
    f.close();

    if(!found) {
        cout << "Order ID not found.\n";
        return;
    }

    cout << "----------------------------------------------\n";
    cout << "GRAND TOTAL: " << total << endl;

    // 2. Check Payment Status
    string currentStatus = checkBillStatus(searchId);
    cout << "BILL STATUS: " << currentStatus << endl;
    cout << "**********************************************\n";

    // 3. Payment Logic
    if(currentStatus == "Paid") {
        cout << "\nThis bill is already paid. No action needed.\n";
    } 
    else {
        char pay;
        cout << "\nWould you like to pay now? (y/n): ";
        cin >> pay;
        
        if(pay == 'y' || pay == 'Y') {
            // Update Bills.csv to "Paid"
            updateBillStatus(searchId, total, "Paid");
            cout << "\n>> Payment Successful! Status updated to PAID.\n";
            
            // Only ask to free table if it's Dine-In
            if(opt == 1 && tableNoToFree != -1) {
                cout << "Releasing Table " << tableNoToFree << "...\n";
                setTableStatus(tableNoToFree, "Free");
            }
        } else {
            // Save as Pending if they viewed it but didn't pay
            updateBillStatus(searchId, total, "Pending");
            cout << "\nBill saved as Pending.\n";
        }
    }
}