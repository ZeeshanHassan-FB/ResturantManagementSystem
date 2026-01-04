#include "login.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// This function is simply to check file exist or not and to write header in csv file. 
void usersheader()
{
    ifstream fCheck("users.csv");
    if(!fCheck) { 
        fCheck.close();
        ofstream fCreate("users.csv");
        fCreate << "username,password,role" << endl; 
        fCreate.close();
    } else {
        fCheck.close();
    }
}

string login()
{
    // Using this function first to check file exist or not.

    usersheader(); 
    string u, p;
    cin.ignore();
    cout << "Enter username: ";
    cin >> u;
    cout << "Enter password: ";
    cin >> p;

    ifstream f("users.csv");
    string line, fline;
    getline(f, fline); 

    while(getline(f, line))
    {
        if(line.empty())
            continue;

        stringstream ss(line);
        string user, pass, role;

        getline(ss, user, ',');
        getline(ss, pass, ',' );
        getline(ss, role); 

        if(u == user && p == pass)
        {
            if(role == "admin" || role == "Admin"){
                role = "admin";
            }
            if(role == "worker" || role == "Worker"){
                role = "worker";
            }

            writeLog("Login success: " + u);
            writeloginsignup(u + " logged in successfully \t Role: " + role);
            return role; 
        }
    }

    writeLog("Login failed: " + u);
    writeloginsignup(u + " login failed");
    return "";
}

void signup()
{
    usersheader();
    string u, p, role;
    int roleChoice;
    
    cin.ignore();
    cout << "Enter new username: ";
    getline(cin,u);

    ifstream f("users.csv");
    string line, fline;
    
    getline(f, fline); 

    while(getline(f, line)) {
        if(line.empty())
           continue;

        stringstream ss(line);
        string user;
        getline(ss, user, ',');
        if(user == u) {
            cout << "Username already exists.\n";
            return;
        }
    }
    f.close();

    cout << "Enter password: ";
    getline(cin,p);
    
    cout << "Select Role:\n1. Admin (Manager)\n2. Worker (Staff/Waiter)\nChoose Your role: ";
    cin >> roleChoice;

//   It is to check the condition either it is admin or worker

    if(roleChoice == 1){ 
        role = "admin";
    }
    else if (roleChoice==2){ 
        role = "worker";
}
    else{
        cout<<"Invalid role selected."<<endl;
    }
   
    ofstream out("users.csv", ios::app);
    
    out << u << "," << p << "," << role << endl;
    out.close();

    writeLog("Signup: " + u);
    writeloginsignup(u + " signed up successfully \t Role: " + role);
    cout << "Signup successful! You are registered as " << role << ".\n";
}

void forgotPassword()
{
    usersheader();
    string u;
    cin.ignore();
    cout << "Enter username: ";
    getline(cin,u);

    ifstream f("users.csv");
    string line, fline;
    getline(f, fline); 

    while(getline(f, line))
    {
        if(line.empty())
           continue;

        stringstream ss(line);
        string user, pass;
        getline(ss, user, ',');
        getline(ss, pass, ',');

        if(user == u) {
            cout << "Your password is: " << pass << endl;
            return;
        }
    }
    cout << "Username not found.\n";
}
