#include "tables.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<Table> tables; // Define in tables.h

void loadTablesFromFile() {
    tables.clear(); // Clear old data before loading
    ifstream f("tables.csv");
    if(!f) return; // If file doesn't exist, just return

    string line;
    while(getline(f, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string tNo, stat;
        
        getline(ss, tNo, ',');
        getline(ss, stat, ',');

        if(!tNo.empty()) {
            Table t;
            t.tableNo = stoi(tNo);
            t.status = stat;
            tables.push_back(t);
        }
    }
    f.close();
}

void saveTablesToFile() {
    ofstream f("tables.csv");
    for(size_t i = 0; i < tables.size(); i++) {
        f << tables[i].tableNo << "," << tables[i].status << endl;
    }
    f.close();
}

void setTableStatus(int tableNo, string newStatus) {
    bool found = false;
    for(size_t i = 0; i < tables.size(); i++) {
        if(tables[i].tableNo == tableNo) {
            tables[i].status = newStatus;
            found = true;
            break;
        }
    }
    if(found) {
        saveTablesToFile(); 
    }
}

void viewTables() {
    cout << "\n--- Current Table Status ---\n";
    cout << "Table No\tStatus\n";
    cout << "----------------------------\n";
    for(size_t i = 0; i < tables.size(); i++) {
        cout << tables[i].tableNo << "\t\t" << tables[i].status << endl;
    }
    cout << "----------------------------\n";
}

// Admin function to add new tables
void manageTables() {
    int choice;
    cout << "\n1. View Tables\n2. Add New Table\n3. Reset a Table to Free\nChoice: ";
    cin >> choice;

    if(choice == 1) {
        viewTables();
    }
    else if(choice == 2) {
        int newNo;
        cout << "Enter new Table Number: ";
        cin >> newNo;
        
        // Check duplicate
        for(size_t i = 0; i < tables.size(); i++) {
            if(tables[i].tableNo == newNo) {
                cout << "Table already exists!\n";
                return;
            }
        }

        Table t;
        t.tableNo = newNo;
        t.status = "Free"; // New tables are always Free
        tables.push_back(t);
        saveTablesToFile();
        cout << "Table added successfully.\n";
    }
    else if(choice == 3) {
        int tNo;
        cout << "Enter Table Number to reset: ";
        cin >> tNo;
        setTableStatus(tNo, "Free");
        cout << "Table reset.\n";
    }
}
