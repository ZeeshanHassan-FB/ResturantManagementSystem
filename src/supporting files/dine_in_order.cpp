#include <iostream>
#include <fstream>
#include <limits>
#include "dine_in_order.h"
#include "tables.h"
#include "menu.h" 

using namespace std;

void takeDineInOrder() {
    loadTablesFromFile(); 
    viewTables();

    int tableNo;
    cout << "Enter Table Number: ";
    cin >> tableNo;

    // --- Table Validation Logic (Same as before) ---
    bool tableFound = false;
    for (size_t i = 0; i < tables.size(); i++) {
        if (tables[i].tableNo == tableNo) {
            tableFound = true;
            if (tables[i].status == "Free") {
                char choice;
                cout << "Table is Free. Mark as Busy? (y/n): ";
                cin >> choice;
                if(choice == 'y' || choice == 'Y') setTableStatus(tableNo, "Busy");
                else return;
            }
            break;
        }
    }
    if (!tableFound) { cout << "Table not found!\n"; return; }
    // -----------------------------------------------

    int orderID;
    cout << "Enter Order ID: ";
    cin >> orderID;
    
    viewMenuOnly(); // Show menu so they see Stock

    ofstream file("dine_in_order.csv", ios::app);
    int more;
    
    do {
        string item;
        int qty;
        int price;

        cout << "\n--- Add Item ---\n";
        cout << "Enter Item Name: ";
        cin >> item;

        // 1. Get Price
        price = getItemPrice(item);
        if(price == -1) {
            cout << "Item not found in menu.\n";
            more = 1; continue;
        }

        cout << "Price: " << price << endl;
        cout << "Quantity: ";
        cin >> qty;

        // 2. CHECK AND DEDUCT STOCK
        // This function handles the logic: checks if enough stock exists,
        // and if yes, updates the menu.csv file immediately.
        if(updateStock(item, qty)) {
            
            // Stock deduction successful, save order
            file << orderID << "," << tableNo << ","
                 << item << "," << qty << "," << price << endl;

            cout << "Item added and stock updated.\n";
        } 
        else {
            // Error message is printed inside updateStock
            cout << "Could not add item.\n";
        }

        cout << "Add more items? (1=Yes, 0=No): ";
        cin >> more;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            more = 0;
        }

    } while (more == 1);

    file.close();
    cout << "\nOrder Finalized!\n";
}