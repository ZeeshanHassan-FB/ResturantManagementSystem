#include "menu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//  This function is simply to convert data from Int datatype to string

string intToString(int v) {

    stringstream ss;
    ss << v;
    return ss.str();

}

void fileCheck() {

    ifstream fCheck("menu.csv");

    if(!fCheck) {
        fCheck.close();

        ofstream fCreate("menu.csv");
        fCreate << "ItemName,Price,Stock" << endl; 
        fCreate.close();
    } else {

        fCheck.close();
    }

}
void viewMenuOnly() {

    fileCheck(); 

    ifstream f("menu.csv");
    string line, fline;

    cout << "\n========== FOOD MENU ==========\n";

    cout << "  Item Name\tPrice\tStock\n";

    cout << "--------------------------------------\n";

   

    getline(f, fline); 



    while(getline(f, line)) {

        if(line.empty())
          continue;

        stringstream ss(line);
        string name, price, qty;

        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss, qty); 
        cout << name << "\t\t" << price << "\t" << qty << endl;

    }

    cout << "======================================\n";
    f.close();

}



void manageMenu() {

    fileCheck();
    int opt;
    cout << "\n1. View Menu\n2. Add Item\nChoice: ";

    cin >> opt;
    if(opt == 1) {

        viewMenuOnly();
    }

    else if(opt == 2) {

        string name;

        int price, qty;

        cout << "Enter Item Name (use_underscores): ";
        cin >> name;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Stock Quantity: ";
        cin >> qty;

        ofstream f("menu.csv", ios::app);
        f << name << "," << price << "," << qty << endl;
        f.close();

        cout << "Item added to menu.\n";

    }

}



int getItemPrice(string itemName) {

    fileCheck();
    ifstream f("menu.csv");
    if(!f) 
       return -1;

    string line, fline;
    getline(f, fline); 

    while(getline(f, line)) {

        if(line.empty())
            continue;
        stringstream ss(line);
        string name, priceStr, qtyStr;

        getline(ss, name, ',');
        getline(ss, priceStr, ',');

        if(name == itemName)
           return stoi(priceStr);

    }

    return -1;

}



bool updateStock(string itemName, int qtyOrdered) {

    fileCheck();

    vector<string> lines;
    ifstream f("menu.csv");

    string line, header;
    bool found = false;
    bool success = false;

    if(getline(f, header)) {
        lines.push_back(header);

    }

    while(getline(f, line)) {

        if(line.empty()) continue;
        stringstream ss(line);
        string name, priceStr, qtyStr;

        getline(ss, name, ',');
        getline(ss, priceStr, ',');
        getline(ss, qtyStr); 

        if(name == itemName) {

            int currentStock = stoi(qtyStr);
            if(currentStock >= qtyOrdered) {

                currentStock = currentStock - qtyOrdered;

              

                string newLine = name + "," + priceStr + "," + intToString(currentStock);

                lines.push_back(newLine);
                success = true;
                found = true;

            } else {

                cout << "Error: Not enough stock! Available: " << currentStock << endl;
                return false;

            }

        } else {

            lines.push_back(line);
        }

    }
    f.close();

    if(found && success) {

        ofstream out("menu.csv");
        for(size_t i = 0; i < lines.size(); i++) {

            out << lines[i] << endl;

        }
        out.close();
        return true;

    }


    if(!found)
       cout << "Error: Item not found in menu.\n";
       
    return false;
}