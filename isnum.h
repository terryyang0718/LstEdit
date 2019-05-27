#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iomanip>
//#include "/home/terry/tmp_0316/c/re_lib.h"
//#include "D:\c\lib\re_lib.h"
//#include "D:\c\lib\tmp_lib.h"
//#include "combine_net.h"
//#include "net_ip.h"


using namespace std;
bool Isnum(string str)  
{  
    stringstream sin(str);  
    double d;  
    char c;  
    if(!(sin >> d))  
    {
        return false;
    }
    if (sin >> c) 
    {
        return false;
    }  
    return true;  
}
/*
int main( void )  
{
    string str1 = "wolaiqiao23r";  
    string str2 = "1990";  
    if(isNum(str1))  
    {  
        cout << "str1 is a num" << endl;  
    }  
    else
    {  
        cout << "str1 is not a num" << endl;  

    }  
    if(isNum(str2))  
    {  
        cout<<"str2 is a num"<<endl;  
    }  
    else
    {  
        cout<<"str2 is not a num"<<endl;  

    }  

    cin.get();
    return 0;  
}  
*/

