#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;
// These Two functions are basically for storing data of login attempts and tracking what is happening in system

void writeLog(string msg); 
// This function is only for login and signup data
void writeloginsignup(string msg);

#endif