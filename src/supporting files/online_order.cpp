#include "online_order.h"
#include "menu.h" // Include menu to access updateStock
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void takeOnlineOrder() {
    cout << "\n--- Online Order ---\n";
    viewMenuOnly(); // Show menu
    
    int id;
    string name, phone, item;
    int qty, price;

    cout << "Order ID: "; cin >> id;
    cout << "Customer Name: "; cin >> name;
    cout << "Phone: "; cin >> phone;
    
    cout << "Item Name: "; cin >> item;
    
    price = getItemPrice(item);
    if(price == -1) {
        cout << "Item not found.\n";
        return;
    }

    cout << "Quantity: "; cin >> qty;

    // Check Stock
    if(updateStock(item, qty)) {
        ofstream f("online_order.csv", ios::app);
        f << id << "," << name << "," << phone << "," << item << "," << qty << "," << price << endl;
        f.close();
        cout << "Online order saved and stock updated.\n";
    } else {
        cout << "Order failed: Not enough stock.\n";
    }
}