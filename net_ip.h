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
class netIp_0{
	public:
		string pin_sym;
		string pin;
		string pinnet;
    int start;
    bool sb;
};

class netIp_1{
  public:
    string pin_sym;
    string pin;
    string pintype;
		string pinnet;
    int start;
    bool sb;
};

void Net_ip(string loc_lst, int num_lst_line, string loc_ip, vector<string>& name_net, vector<string>& type_net){
//  string name_ip = "UHCOREIRV2";
//  string name_label = "COREIR";

//  string loc_ip = "D:\\project\\uz0huzhn11\\dip\\sym\\uhcoreirv3.1";
//  string loc_lst = "D:\\project\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";
//  int num_lst_line = 439;
//  string num_lst = int2str(num_lst_line);


  netIp_1 candy_pin1;
  vector<netIp_1> bag_pin1;
  bag_pin1.clear();

//sym
//  cout << loc_ip << endl;
  fstream f_sym;
	f_sym.open(loc_ip, ios::in);
  string line, tmp_pin, tmp_pin_sym, tmp_pinnet, tmp_pintype;
  
  bool la = false;
	if(!f_sym)
		cout << "Fail!" << endl;
	else{
    int i_la = 0;
		do{
      getline(f_sym, line);
      if(la == false){
        tmp_pin_sym = line;
        Lst_end(tmp_pin_sym, "L ", "0 1 0 ");
        if(!tmp_pin_sym.empty()){
          candy_pin1.pin_sym = tmp_pin_sym;
          bag_pin1.push_back(candy_pin1);
          la = true;
        } 
      }
      else{
        tmp_pintype = line;
        Lst_end(tmp_pintype, "A ", " PINTYPE=");
        if(!tmp_pintype.empty()){
          bag_pin1[i_la].pintype = tmp_pintype;
          la = false;
          i_la++;
        }        
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
  netIp_0 candy_pin0;
  vector<netIp_0> bag_pin0;
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


//  for(int i = 0; i < bag_pin1.size(); i++)
//    cout << bag_pin1[i].pin_sym << "  " << bag_pin1[i].pin << "  " << bag_pin1[i].pintype << endl;

//  vector<string> name_net = vector<string> (); 
//  vector<string> type_net = vector<string> (); 
  for(int i = 0; i < bag_pin1.size(); i++){
    if(bag_pin1[i].pin.empty())
      name_net.push_back(bag_pin1[i].pin_sym);
    else
      name_net.push_back(bag_pin1[i].pin);
      type_net.push_back(bag_pin1[i].pintype);
  }
  bag_pin1.clear();  
  
//  for(int i = 0; i < type_net.size(); i++)
//    cout << name_net[i] << "  " << type_net[i] << endl;





//    return 0;
}

