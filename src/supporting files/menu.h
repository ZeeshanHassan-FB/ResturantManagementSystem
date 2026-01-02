#ifndef MENU_H
#define MENU_H
#include <string>
using namespace std;

void manageMenu();    // For Admin (Add items with Quantity)
void viewMenuOnly(); 
int getItemPrice(string itemName); 
bool updateStock(string itemName, int qtyOrdered); 

#endif