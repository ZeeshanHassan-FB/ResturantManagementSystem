#include <iostream>
#include <cstdlib> 
#include "../supporting files/login.h"
#include "../supporting files/menu.h"
#include "../supporting files/dine_in_order.h"
#include "../supporting files/tables.h"
#include "billing.h"
#include "online_order.h"
using namespace std;

// ================= This is Code block of workers (waiters) =================
void workerPanel() {
    int opt;
    do {
        system("cls"); 
        cout << "\n================================\n";
        cout << "       WORKER DASHBOARD         \n";
        cout << "================================\n";
        cout << "1. Manage Tables (Free/Busy)\n";
        cout << "2. Take New Order\n";
        cout << "3. Generate Bill\n";
        cout << "4. Logout\n";
        cout << "================================\n";
        cout << "Enter Choice: ";
        cin >> opt;

        switch (opt) {
            case 1:
                manageTables();
                break;
            case 2:
               takeDineInOrder();
                break;
            case 3:
                
                cout << "\n[Coming Soon: Generate Bill]\n";
                break;
            case 4:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
        if(opt != 4) system("pause");

    } while (opt != 4);
}

// ================= This is codeblock of Admin(Owner) =================
void adminPanel() {
    int opt;
    do {
        system("cls");
        cout << "\n================================\n";
        cout << "        ADMIN DASHBOARD         \n";
        cout << "================================\n";
        cout << "1. Manage Food Menu (Add/Edit)\n";
        cout << "2. Manage Tables\n";
        cout << "3. Take Dine-In Order\n";
        cout << "4. Take Online/Phone Order\n";
        cout << "5. Generate Bill\n";
        cout << "6. Logout\n";
        cout << "================================\n";
        cout << "Enter Choice: ";
        cin >> opt;

        switch (opt) {
            case 1: 
                manageMenu(); 
                break;
            case 2: 
               
                manageTables();
                break;
            case 3: 
               
                takeDineInOrder();
                break;
            case 4: 
                cout << "\n[Coming Soon: Online Order]\n"; 
                break;
            case 5: 
               
                cout << "\n[Coming Soon: Generate Bill]\n";
                break;
            case 6: 
                cout << "Logging out...\n"; 
                break;
            default: cout << "Invalid choice!\n";
        }
        if(opt != 6) system("pause");

    } while (opt != 6);
}

// ================= This is The Main Function  =================
int main() {
   
       loadTablesFromFile();
    int choice;
    do {
        system("cls");
        cout << "\n************************************\n";
        cout << "   RESTAURANT MANAGEMENT SYSTEM     \n";
        cout << "************************************\n";
        cout << "1. Login (Admin/Worker)\n";
        cout << "2. Register New Staff\n";
        cout << "3. Recover Password\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
    
            string role = login(); 

            if (role == "admin") {
                adminPanel(); 
            } 
            else if (role == "worker") {
                workerPanel(); 
            } 
        } 
        else if (choice == 2) {
            signup();
            system("pause");
        } 
        else if (choice == 3) {
            forgotPassword(); 
            system("pause");
        }
        else if (choice == 4) {
            generateBill();
            system("pause");
        }
        else if (choice == 5) {
            takeOnlineOrder();
            system("pause");
        }

    } while (choice != 6);

    cout << "\nSystem Shutdown.\n";
    return 0;
}