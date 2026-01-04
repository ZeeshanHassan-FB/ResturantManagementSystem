# resturantmanagmentsystem
# Restaurant Management System (C++)

## Group Members
- Zeeshan Hassan | 25021519-018
- Muhammad Usaman Shafique | 25021519-053
- Hazrat Amin | 25021519-110

## Project Description
This project is a menu-driven Restaurant Management System developed in C++.  
It handles login, menu management, dine-in orders, online orders, delivery, and billing.

## Features
- User login system
- Menu management using CSV files
- Dine-in and online order handling
- Automatic bill generation
- File handling for data storage
- Modular code structure

## Technologies Used
- C++
- File Handling (CSV, TXT)
- GitHub for version control

##Contribution Summary

Hazrat Amin: Online order module, delivery system, billing system
Zeeshan: Menu management and menu.csv
Usman: Dine-in order system and dine_in_orders.csv

Each member contributed independently with meaningful GitHub commits.
This project applies fundamental programming concepts to build a modular restaurant management system with file handling and team collaboration using GitHub.

## How to Run
```bash

g++ -I"src/supporting files" "src/main file/main.cpp" "src/supporting files/billing.cpp" "src/supporting files/dine_in_order.cpp" "src/supporting files/login.cpp" "src/supporting files/menu.cpp" "src/supporting files/online_order.cpp" "src/supporting files/tables.cpp" "src/supporting files/utils.cpp" -o restaurant
./restaurant
