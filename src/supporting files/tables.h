#ifndef TABLES_H
#define TABLES_H

#include <string>
#include <vector>
using namespace std;

struct Table {
    int tableNo;
    string status; // "Free" or "Busy"
};

// Global vector to hold tables in memory
extern vector<Table> tables;

// Function declarations
void loadTablesFromFile();
void saveTablesToFile();
void manageTables(); // For Admin (Add/Delete)
void viewTables();   // For everyone
void setTableStatus(int tableNo, string newStatus);

#endif