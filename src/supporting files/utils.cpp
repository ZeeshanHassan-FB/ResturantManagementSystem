#include "utils.h"
#include <fstream>

using namespace std;

// This function will track the whole working of tasks that will happen  

void writeLog(string msg)
{
    ofstream f("system_log.txt", ios::app);
    if(f.is_open())
    {
        f << msg << endl;
        f.close();
    }
}

// This function will only track login and signups

void writeloginsignup(string msg){

    ofstream f("login_log.txt",ios::app);
    if(f.is_open()){
        f<<msg<<endl;
        f.close();

    }
}