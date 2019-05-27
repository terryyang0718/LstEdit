#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h> 
//#include "D:\\c\\lib\\re_lib.h"
//#include "D:\\c\\lib\\tmp_lib.h"
//#include "D:\\c\\lib\\sym2sch_1.0.h"
using namespace std;
class net_0{
	public:
		string pin_sym;
		string pin;
		string pinnet;
    int start;
    bool sb;
};

class net_1{
  public:
    bool lr;
    int x;
    int y;
    
    string pin_sym;
    string pin;
		string pinnet;
    int start;
    bool sb;
};

class net_2{
  public:
    int idy;
    string pin_sym_l;
    string pin_l;
		string pinnet_l;
    string pin_sym_r;
    string pin_r;
		string pinnet_r;
};

void blank(int cycle){
  cout << setw(20) << "                   |" << "";
  for(int i = 0; i < cycle; i++)
    cout << " ";
  cout << "" << "|" << endl;
}
void space(string& sp, const int& num_space){
//  string space;
//  int num_space;
  for(int i = 0; i < num_space ; i++)
    sp.append(" ");
}

void print_ip(string& name_ip, string& name_label, string& loc_ip, string& loc_lst, int& num_lst_line){
/*
  string sch_1 = "sch.1";
  string name_ip = "UHCOREIRV2";
  string name_label = "COREIR";
  string loc_ip = "D:\\project\\uz09uzh412\\dip\\sym\\uhcoreirv2.1";
  int length_ip = 660;  
  
  string loc_lst = "D:\\project\\uz09uzh412\\body\\lst\\sch_uz09uzh412.lst";
  int num_lst_line = 322;

  int num_net = 1;
  int num_ip = 1;
  int x_ip = 950;
  int y_ip = 860;
*/

  net_1 candy_pin1;
  vector<net_1> bag_pin1;
  bag_pin1.clear();

//sym
//  cout << loc_ip << endl;
  fstream f_sym;
	f_sym.open(loc_ip, ios::in);
  string line, tmp_pin, tmp_pin_sym, tmp_pinnet, tmp_pos, tmp_x, tmp_y;
	if(!f_sym)
		cout << "Fail!" << endl;
	else{
		do{
      getline(f_sym, line);
      bool tmp_lr = false;
      tmp_pin_sym = line;
      Lst_end(tmp_pin_sym, "L ", "0 1 0 ");
      tmp_pos = line;
      Lst(tmp_pos, "L ", "L ", " 10 0 ");
      if(!tmp_pin_sym.empty() && !tmp_pos.empty()){
        size_t blank = tmp_pos.find(" ");
        tmp_x.assign(tmp_pos, 0, blank);
        tmp_y.assign(tmp_pos.begin()+blank+1, tmp_pos.end());
        candy_pin1.x = str2int(tmp_x);
        candy_pin1.y = str2int(tmp_y);
        candy_pin1.pin_sym = tmp_pin_sym;
        candy_pin1.lr = YesNo(line, "10 0 2 0 1 0 ", tmp_lr);
        bag_pin1.push_back(candy_pin1); 
      }
    }while(!f_sym.eof());
  }
  f_sym.close();
	for(int i = 0; i < bag_pin1.size(); i++){
		bag_pin1[i].sb = false;
		if(size_t found = bag_pin1[i].pin_sym.find(":") != string::npos)
			bag_pin1[i].sb = true;
  }

//lst
  net_0 candy_pin0;
  vector<net_0> bag_pin0;
  bag_pin0.clear();
  fstream f_lst;
	f_lst.open(loc_lst, ios::in);
//  string tmp_pin, tmp_pin_sym, tmp_pinnet;
  int num = 1;
	if(!f_lst)
		cout << "Fail!" << endl;
	else{
		do{
      getline(f_lst, line);
      tmp_pin = line;
      tmp_pin_sym = line;
      tmp_pinnet = line;
      if(num == num_lst_line){
				if(size_t found = line.find("[A]") != string::npos){
        size_t start_pos = 0;
        while((start_pos = line.find("[A]=", start_pos)) != string::npos){
          start_pos = line.find("[A]=", start_pos);
	        candy_pin0.start = start_pos;		
	        bag_pin0.push_back(candy_pin0);
	        start_pos += 2;
        }
        if(bag_pin0.size() > 1){
          for(int i = 0; i < bag_pin0.size()-1; i++)
	          bag_pin0[i].pin_sym.assign(tmp_pin_sym, bag_pin0[i].start, bag_pin0[i+1].start-bag_pin0[i].start-1);
        }
        bag_pin0[bag_pin0.size()-1].pin_sym.assign(tmp_pin_sym.begin()+bag_pin0[bag_pin0.size()-1].start, tmp_pin_sym.end()-1);
      }
			}
      num++;
    }while(!f_lst.eof());
  }

	for(int i = 0; i < bag_pin0.size(); i++){
		if(size_t pinnet_pos = bag_pin0[i].pin_sym.find("PINNET") == string::npos){
      tmp_pin = bag_pin0[i].pin_sym;
      tmp_pin_sym = bag_pin0[i].pin_sym;
      Lst(tmp_pin_sym, "[A]=$PIN_", "[A]=$PIN_", "=");
      bag_pin0[i].pin_sym = tmp_pin_sym;
      bag_pin0[i].pin.assign(tmp_pin, tmp_pin.rfind("=")+1, tmp_pin.length()-tmp_pin.rfind("="));
		}
		else{
      tmp_pinnet = bag_pin0[i].pin_sym;
      tmp_pin_sym = bag_pin0[i].pin_sym;
      Lst(tmp_pin_sym, "[A]=$PINNET_", "[A]=$PINNET_", "=");
      bag_pin0[i].pin_sym = tmp_pin_sym;
      if(size_t found = tmp_pinnet.find(")") != string::npos){
        string tmp_tmp;
        tmp_tmp.assign(tmp_pinnet.begin(), tmp_pinnet.end()-1);
        tmp_pinnet = tmp_tmp;
      }
      bag_pin0[i].pinnet.assign(tmp_pinnet, tmp_pinnet.rfind("=")+1, tmp_pinnet.length()-tmp_pinnet.rfind("="));
		}
	}
//combine
  for(int i = 0; i < bag_pin1.size(); i++){
    for(int j = 0; j < bag_pin0.size(); j++){
      if(bag_pin1[i].pin_sym == bag_pin0[j].pin_sym){
//        bag_pin1[i].pin_sym = bag_pin0[j].pin_sym;
        if(!bag_pin0[j].pin.empty())
          bag_pin1[i].pin = bag_pin0[j].pin;
        if(!bag_pin0[j].pinnet.empty())
          bag_pin1[i].pinnet = bag_pin0[j].pinnet;
      }
    }
  }
  bag_pin0.clear();

  net_2 candy_pin2;
  vector<net_2> bag_pin2;
  bag_pin2.clear();

  int num_l = 0;
  for(int i = 0; i < bag_pin1.size(); i++){
      if(bag_pin1[i].lr == true)
        num_l = num_l+1;
  }
  if(num_l >= bag_pin1.size()-num_l){

  for(int i = 0; i < bag_pin1.size(); i++){
      if(bag_pin1[i].lr == true){
        candy_pin2.pin_sym_l = bag_pin1[i].pin_sym;
        candy_pin2.pin_l = bag_pin1[i].pin;
        candy_pin2.pinnet_l = bag_pin1[i].pinnet;
        candy_pin2.idy = (bag_pin1[i].y/10);
        bag_pin2.push_back(candy_pin2); 
      }
  }
  for(int i = 0; i < bag_pin2.size(); i++){
    if(!bag_pin2[i].pinnet_l.empty())
      bag_pin2[i].pinnet_l = ">--";
  }
  for(int i = 0; i < bag_pin2.size(); i++){
      for(int j = 0; j < bag_pin1.size(); j++){
        if(bag_pin2[i].idy == (bag_pin1[j].y/10) && bag_pin1[j].lr == false){
          if(!bag_pin1[j].pin_sym.empty())
            bag_pin2[i].pin_sym_r = bag_pin1[j].pin_sym;
          if(!bag_pin1[j].pin.empty())
            bag_pin2[i].pin_r = bag_pin1[j].pin;
          if(!bag_pin1[j].pinnet.empty()){
            if(bag_pin1[j].pinnet == "OUT")
              bag_pin2[i].pinnet_r = "-->";
            else
              bag_pin2[i].pinnet_r = "<->";
          }
        }
      }
  }
  bag_pin1.clear();

  }
  else{
  
    for(int i = 0; i < bag_pin1.size(); i++){
      if(bag_pin1[i].lr == false){
        candy_pin2.pin_sym_r = bag_pin1[i].pin_sym;
        candy_pin2.pin_r = bag_pin1[i].pin;
        candy_pin2.pinnet_r = bag_pin1[i].pinnet;
        candy_pin2.idy = (bag_pin1[i].y/10);
        bag_pin2.push_back(candy_pin2); 
      }
  }
  for(int i = 0; i < bag_pin2.size(); i++){
    if(!bag_pin2[i].pinnet_r.empty()){
      if(bag_pin2[i].pinnet_r == "OUT")
        bag_pin2[i].pinnet_r = "-->";
      else
        bag_pin2[i].pinnet_r = "<->";
    }
  }
  for(int i = 0; i < bag_pin2.size(); i++){
      for(int j = 0; j < bag_pin1.size(); j++){
        if(bag_pin2[i].idy == (bag_pin1[j].y/10) && bag_pin1[j].lr == true){
          if(!bag_pin1[j].pin_sym.empty())
            bag_pin2[i].pin_sym_l = bag_pin1[j].pin_sym;
          if(!bag_pin1[j].pin.empty())
            bag_pin2[i].pin_l = bag_pin1[j].pin;
          if(!bag_pin1[j].pinnet.empty()){
            if(bag_pin1[j].pinnet == "IN")
              bag_pin2[i].pinnet_l = ">--";
          }
        }
      }
  }
  bag_pin1.clear();
  
  
  
  
  
  
  
  }











//print
  cout << endl;
  cout << setw(20) << "                    " << name_label << endl;
  
  cout << setw(20) << "                   +" << "------------------------------+" << endl;
  cout << setw(20) << "                   |" << "";

  int ll = (30-name_ip.length())/2;

  for(int i = 0; i < ll; i++)
    cout << " ";
  cout << name_ip;
  for(int i = 0; i < 30-ll-name_ip.length(); i++)
    cout << " ";
  
  cout << "|" << endl;
  blank(30);
  for(int i = bag_pin2.size()-1; i >= 0; i--){
    string tmp_space = "";
    space(tmp_space, 20-bag_pin2[i].pin_l.length()-bag_pin2[i].pinnet_l.length()-3);
    int bb = 30-(bag_pin2[i].pin_sym_l.length()+bag_pin2[i].pin_sym_r.length());
    cout << setw(20) << tmp_space+bag_pin2[i].pinnet_l+bag_pin2[i].pin_l+"--|" << bag_pin2[i].pin_sym_l; 
    for(int i = 0; i < bb; i++)
      cout << " ";
    cout << bag_pin2[i].pin_sym_r << "|--"+bag_pin2[i].pin_r+bag_pin2[i].pinnet_r << endl;   
    blank(30);

 }

  cout << setw(20) << "                   +" << "------------------------------+" << endl;
  cout << endl;








//    return 0;
}

/*
    string pin_sym_l;
    string pin_l;
		string pinnet_l;
    string pin_sym_r;
    string pin_r;
		string pinnet_r;
    */
