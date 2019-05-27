#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h> 
#include <iomanip>
//#include "D:\\c\\lib\\re_lib.h"
//#include "D:\\c\\lib\\tmp_lib.h"
//#include "D:\\c\\lib\\getdir_silent.h"

void Net2sch(string loc_lst, string num, int x_net, int y_net, int& num_net, string& all){
//  string loc_lst = "D:\\project\\uz0cuzhd14\\body\\lst\\sch_uz0cuzhd14.lst";
//  string num = "845";

//Reading lst ...
  string iob;
  ifstream lstFile;
  lstFile.open(loc_lst);
  if(!lstFile)
    cout << "fail" << endl;
  else{
    string line, tmp_iob;
    int j = 1;
    do{
      getline(lstFile, line);
      if(j == str2int(num)){
        tmp_iob = line;
        Lst(tmp_iob, "(", "(", ")");
        if(!tmp_iob.empty())
          iob = tmp_iob;
      }
      j++;
    }while(!lstFile.eof());
    lstFile.close();
  }

  string pinnet = iob;
  string pintype;
  if(iob.find("[A]=$PIN_IN=") == 0){
    Lst_end(pinnet, "[A]=$PIN_IN=", "[A]=$PIN_IN=");
    pintype = "IN";
  }else if(iob.find("[A]=$PIN_OUT=") == 0){
    Lst_end(pinnet, "[A]=$PIN_OUT=", "[A]=$PIN_OUT=");
    pintype = "OUT";
  }else{
    Lst_end(pinnet, "[A]=$PIN_BI=", "[A]=$PIN_BI=");
    pintype = "BI";
  }
  bool bus = false;
  if(pinnet.find("[") != string::npos && pinnet.find("]") != string::npos && pinnet.find(":") != string::npos)
    bus = true;

//Inserting net ...
//  int x_net = 990, y_net = 1200;
//  int num_net = 1000;
//  string all = "";
  all.clear();
  vector<int> grp_int = vector<int> ();

  all = all+"N "+int2str(num_net)+"\n";
  string tmp_num_net = int2str(num_net);
  num_net++;


  if(pintype == "IN"){
    if(bus == false){
      grp_int = {x_net-10, y_net, x_net+150, y_net};
      all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 2"+"\n";
      all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 1"+"\n";
      all = all+"S 2 1"+"\n";
      grp_int.clear();
    }else{
      grp_int = {x_net-10, y_net, x_net+150, y_net};
      all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 8"+"\n";
      all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 7"+"\n";
      all = all+"B 2 1"+"\n";
      grp_int.clear();
    }
    all = all+"L "+int2str(x_net)+" "+int2str(y_net)+" 10 0 3 0 1 0 "+pinnet+"\n";
    grp_int = {num_net, x_net-40, y_net, x_net-30, y_net-10};  
    all = all+"I "+int2str(grp_int[0])+" builtin:"+pintype+" 1 "+int2str(grp_int[1])+" "+int2str(grp_int[2])+" 0 1 '"+"\n";
    string tmp_iob_part = iob.substr(4, iob.length()-4);
    all = all+"A "+int2str(grp_int[3])+" "+int2str(grp_int[4])+" 10 0 3 1 "+tmp_iob_part+"\n";
    all = all+"C "+tmp_num_net+" 1 1 0"+"\n";
    grp_int.clear();
  
  }else{
    if(bus == false){
      grp_int = {x_net+150, y_net, x_net-10, y_net};
      all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 2"+"\n";
      all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 1"+"\n";
      all = all+"S 2 1"+"\n";
      grp_int.clear();
    }else{
      grp_int = {x_net+150, y_net, x_net-10, y_net};
      all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 8"+"\n";
      all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 7"+"\n";
      all = all+"B 2 1"+"\n";
      grp_int.clear();
    }
    all = all+"L "+int2str(x_net)+" "+int2str(y_net)+" 10 0 3 0 1 0 "+pinnet+"\n";
    grp_int = {num_net, x_net+150, y_net, x_net+160, y_net-10};  
    all = all+"I "+int2str(grp_int[0])+" builtin:"+pintype+" 1 "+int2str(grp_int[1])+" "+int2str(grp_int[2])+" 0 1 '"+"\n";
    string tmp_iob_part = iob.substr(4, iob.length()-4);
    all = all+"A "+int2str(grp_int[3])+" "+int2str(grp_int[4])+" 10 0 3 1 "+tmp_iob_part+"\n";
    all = all+"C "+tmp_num_net+" 1 1 0"+"\n";
    grp_int.clear();


  }

//  cout << all << endl;
//  return 0;
}
/*
int main(){
  string loc_lst = "D:\\project\\uz0cuzhd14\\body\\lst\\sch_uz0cuzhd14.lst";
  int num_net = 1000;
  vector<string> all = {"", "", "", "", ""};

  string num = "845";
  int x_net = 990, y_net = 1200;
  Net2sch(loc_lst, num, x_net, y_net, num_net, all[0]);

  num = "846";
  x_net = 990, y_net = 1165;
  Net2sch(loc_lst, num, x_net, y_net, num_net, all[1]);

  num = "847";
  x_net = 990, y_net = 1085;
  Net2sch(loc_lst, num, x_net, y_net, num_net, all[2]);

  num = "848";
  x_net = 990, y_net = 1045;
  Net2sch(loc_lst, num, x_net, y_net, num_net, all[3]);

  num = "863";
  x_net = 960, y_net = 485;
  Net2sch(loc_lst, num, x_net, y_net, num_net, all[4]);

  ofstream tmpFile;
  tmpFile.open("sch.2");
  for(int i = 0; i < all.size(); i++)
    tmpFile << all[i] << endl;
  return 0;
}
*/
