#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iomanip>
//#include "D:\c\lib\re_lib.h"
//#include "D:\c\lib\tmp_lib.h"



using namespace std;

void Str2nums(string tmp_pt, vector<int>& num_pt){

//  string tmp_pt = "439";
//  string tmp_pt = "439, 444, 448, 540, 542";
  size_t f_pt = -1;
  vector<int> pt = vector<int> ();
  pt.clear();
  pt.push_back(f_pt);
  f_pt++;
  while((f_pt = tmp_pt.find(",", f_pt)) != string::npos){
 //   cout << f_pt << endl;
    pt.push_back(f_pt);
    f_pt++;
  }
  pt.push_back(tmp_pt.length()+1);
  
  string tmp_pt1;
//  vector<int> num_pt = vector<int> ();
  num_pt.clear();
  for(int i = 0; i < pt.size()-1; i++){
    tmp_pt1.assign(tmp_pt, pt[i]+1, pt[i+1]-pt[i]-1);
    num_pt.push_back(str2int(tmp_pt1));
  }
  pt.clear();
//  return 0;
}


