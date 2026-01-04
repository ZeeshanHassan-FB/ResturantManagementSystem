#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "billing.h"
#include "tables.h"

using namespace std;


string checkBillStatus(int orderID) {
    ifstream f("bills.csv");
    if(!f) return "Pending"; 
    string line;
    while(getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, tot, stat;
        
        getline(ss, id, ',');
        getline(ss, tot, ',');
        getline(ss, stat, ',');

        if(!id.empty() && stoi(id) == orderID) {
            return stat; 
        }
    }
    return "Pending"; 
}


void updateBillStatus(int orderID, int total, string status) {
    vector<string> lines;
    ifstream f("bills.csv");
    string line;
    bool found = false;

    
    while(getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, tot, stat;
        getline(ss, id, ',');
        
        
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

    
    if(!found) {
        stringstream newLine;
        newLine << orderID << "," << total << "," << status;
        lines.push_back(newLine.str());
    }

    
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

    
    while (getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string fid, f2, f3, fItem, fQty, fPrice;

        getline(ss, fid, ',');
        
        if(opt == 1) {
            
            getline(ss, f2, ','); 
            getline(ss, fItem, ',');
            getline(ss, fQty, ',');
            getline(ss, fPrice, ',');
            
            if(stoi(fid) == searchId) tableNoToFree = stoi(f2);
        } else {
            
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

    
    string currentStatus = checkBillStatus(searchId);
    cout << "BILL STATUS: " << currentStatus << endl;
    cout << "**********************************************\n";

   
    if(currentStatus == "Paid") {
        cout << "\nThis bill is already paid. No action needed.\n";
    } 
    else {
        char pay;
        cout << "\nWould you like to pay now? (y/n): ";
        cin >> pay;
        
        if(pay == 'y' || pay == 'Y') {
            
            updateBillStatus(searchId, total, "Paid");
            cout << "\n>> Payment Successful! Status updated to PAID.\n";
            
            
            if(opt == 1 && tableNoToFree != -1) {
                cout << "Releasing Table " << tableNoToFree << "...\n";
                setTableStatus(tableNoToFree, "Free");
            }
        } else {
            
            updateBillStatus(searchId, total, "Pending");
            cout << "\nBill saved as Pending.\n";
        }
    }
}