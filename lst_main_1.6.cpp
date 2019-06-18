#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iomanip>
#include "re_lib.h"
#include "tmp_lib.h"
#include "getDir_silent.h"
#include "print_ip_0.0.h"
#include "edit.h"
#include "others.h"
#include "sch2sym.h"
#include "kill.h"
#include "cut.h"
#include "sch.h"
#include "together.h" 
#include "str2nums.h" 
#include "lst2sch.h" 


using namespace std;
class node{
	public:
    int num_line;
		string sch;
    string ip;
    string label;
		string detail;
    string loc_ip;
    int length_ip;
    int x;
    int y;
    bool z;
};

int main(){
  cout << endl;
  cout << "     _/                    _/         _/_/_/_/          _/      _/      _/" << endl;  
  cout << "    _/          _/_/_/  _/_/_/_/     _/            _/_/_/            _/_/_/_/" << endl;  
  cout << "   _/        _/_/        _/         _/_/_/       _/   _/      _/      _/" << endl;  
  cout << "  _/            _/_/    _/         _/           _/   _/      _/      _/" << endl;  
  cout << " _/_/_/_/  _/_/_/        _/_/     _/_/_/_/      _/_/_/      _/        _/_/" << endl;  
  cout << endl;
    
  string loc_lst;// = "/home/terry/c/tmp_0222/uz09uzh412/body/lst/sch_uz09uzh412.lst";
  cout << "File path: ";
	cin >> loc_lst;

string key;
bool na;
int key_num_lst;
string tmp_num_kill, tmp_num_together;
vector<int> tmp_vec_nums = vector<int> ();
vector<string> ips = vector<string> ();
//vector<int> num_kill = vector<int> ();
char choice;
do{

	string dir_dip = loc_lst;
  size_t pos_body = loc_lst.find("body");
	dir_dip.assign(loc_lst, 0, pos_body);
  dir_dip.append("\\dip\\sym");    
  vector<string> loc_dip = vector<string>();
  getdir(dir_dip, loc_dip);

  string dir_aip = loc_lst;
	dir_aip.assign(loc_lst, 0, pos_body);
  dir_aip.append("\\aip\\sym");    
  vector<string> loc_aip = vector<string>();
  getdir(dir_aip, loc_aip);

  string dir_cid = loc_lst;
	dir_cid.assign(loc_lst, 0, pos_body);
  dir_cid.append("\\sym");    
  vector<string> loc_cid = vector<string>();
  getdir(dir_cid, loc_cid);

  string dir_disweb = "\\\\usernt\\disweb\\";
  string tmp_cid, body_back;
	body_back.assign(loc_lst, pos_body, loc_lst.length()-pos_body);
	int i_cid = 0;
	size_t found_cid;
	do{
		tmp_cid.assign(loc_lst, i_cid, pos_body-i_cid-1);
		i_cid++;
	}while((found_cid = body_back.find(tmp_cid)) == string::npos);
  transform(tmp_cid.begin(), tmp_cid.end(), tmp_cid.begin(), ::toupper);
  dir_disweb.append(tmp_cid);    
  vector<string> loc_disweb = vector<string>();
  getdir(dir_disweb, loc_disweb);

  
  node candy_lst;
  vector<node> bag_lst;
  bag_lst.clear();
  
  fstream f_lst;
//	char tmp[100];
//	strcpy(tmp, loc_lst.c_str());
	f_lst.open(loc_lst, ios::in);
  string line, tmp_sch, tmp_sch_0, tmp_ip, tmp_label, tmp_ip_pin, tmp_detail;

	if(!f_lst)
		cout << "Fail!" << endl;
	else{
    int tmp_num_line = 1;
		do{
      getline(f_lst, line);
     	if(size_t found = line.find("|") != 0){ 
      tmp_sch_0 = line;
      lst_end(tmp_sch_0, "#SCH:", "#SCH:");
      if(!tmp_sch_0.empty())
        tmp_sch = tmp_sch_0;
      tmp_ip = line;
      lst(tmp_ip, "IP:", "IP:", "([");
			tmp_ip_pin = line;
			lst(tmp_ip_pin, "#PIN:", "#PIN:", "([");
      if(size_t found = line.find("#IO:") != string::npos){
				tmp_ip = line;
				Lst(tmp_ip, "#IO:", "#IO:", "([");
			}
			tmp_detail = line;
			Lst(tmp_detail, "#", "(", ")");
      Re(tmp_detail, ",[A]", ",[A]", ",\n                                   [A]");

			tmp_label = line;
      if(size_t found = line.find("[A]") == string::npos)
				lst(tmp_label, "([L]=", "([L]=", ")");
			else
        lst(tmp_label, "([L]=", "([L]=", ",[A]=");
      if(!tmp_ip.empty()){
        candy_lst.num_line = tmp_num_line;
        candy_lst.sch = tmp_sch;
        candy_lst.ip = tmp_ip;
        candy_lst.label = tmp_label;
				candy_lst.detail = tmp_detail;
        bag_lst.push_back(candy_lst);
			}
      if(!tmp_ip_pin.empty()){
        candy_lst.num_line = tmp_num_line;
        candy_lst.sch = tmp_sch;
        candy_lst.ip = tmp_ip_pin;
//				tmp_ip_pin_a = line;
//				Lst(tmp_ip_pin_a, "#PIN", "([A]=$", ")");
//				Lst_end(tmp_ip_pin_a, "=", "=");
        candy_lst.label = "";
				candy_lst.detail = tmp_detail;
        bag_lst.push_back(candy_lst);   
      }
			}
      tmp_num_line++;   
    }while(!f_lst.eof());
		f_lst.close();
  }

  string tmp_ip_lower;
  for(int i = 0; i < bag_lst.size(); i++){
    for(int d = 0; d < loc_dip.size(); d++){
      tmp_ip_lower = bag_lst[i].ip;
      transform(tmp_ip_lower.begin(), tmp_ip_lower.end(), tmp_ip_lower.begin(), ::tolower);
      if(loc_dip[d] == tmp_ip_lower+".1")
        bag_lst[i].loc_ip = dir_dip+"\\"+loc_dip[d];
    }
    for(int a = 0; a < loc_aip.size(); a++){
      tmp_ip_lower = bag_lst[i].ip;
      transform(tmp_ip_lower.begin(), tmp_ip_lower.end(), tmp_ip_lower.begin(), ::tolower);
      if(loc_aip[a] == tmp_ip_lower+".1")
        bag_lst[i].loc_ip = dir_aip+"\\"+loc_aip[a];
    }
    for(int c = 0; c < loc_cid.size(); c++){
      tmp_ip_lower = bag_lst[i].ip;
//      transform(tmp_ip_lower.begin(), tmp_ip_lower.end(), tmp_ip_lower.begin(), ::tolower);
      if(loc_cid[c] == tmp_ip_lower+".1")
        bag_lst[i].loc_ip = dir_cid+"\\"+loc_cid[c];
    }
  }
//  for(int i = 0; i < bag_lst.size(); i++){
//    if(!bag_lst[i].loc_ip.empty())
//      Ip_length(bag_lst[i].loc_ip, bag_lst[i].length_ip);
//  }

  for(int i = 0; i < bag_lst.size(); i++){
		if(bag_lst[i].loc_ip.empty()){
			if(bag_lst[i].ip != "IN" && bag_lst[i].ip != "OUT" && bag_lst[i].ip != "BI"){
				tmp_ip_lower = bag_lst[i].ip;
				transform(tmp_ip_lower.begin(), tmp_ip_lower.end(), tmp_ip_lower.begin(), ::tolower);
				other_ip(loc_lst, tmp_ip_lower, bag_lst[i].loc_ip);
			}
		}
	}

  for(int i = 0; i < bag_lst.size(); i++){
		if(bag_lst[i].loc_ip.empty()){
			if(bag_lst[i].ip != "IN" && bag_lst[i].ip != "OUT" && bag_lst[i].ip != "BI"){
        for(int w = 0; w < loc_disweb.size(); w++){
          tmp_ip_lower = bag_lst[i].ip;
				  transform(tmp_ip_lower.begin(), tmp_ip_lower.end(), tmp_ip_lower.begin(), ::tolower);
          if(loc_disweb[w] == tmp_ip_lower)
            bag_lst[i].loc_ip = dir_disweb+"\\"+loc_disweb[w]+"\\sym\\"+loc_disweb[w]+".1";
			  }
		  }
	  }
  }

  cout << endl;
  cout << "Options" << endl;
  cout << "==========" << endl;
	cout << endl;
  cout << "  1. Search #IP/#PIN" << "     6. Edit #SCH" << endl;
  cout << "  2. Show #IP/#PIN" << "       7. Format sch_cid_*.lst" << endl;
  cout << "  3. Edit #IP/#PIN" << "       8. Transform sch_cid_*.lst to sch.1 & sym.1" << endl;
  cout << "  4. Delete #IP/#PIN" << "     9. Load sch_cid_*.lst" << endl;
  cout << "  5. Combine #IP/#PIN" << endl;
  cout << endl;
	cout << "Target: " << loc_lst << endl;
	cout << "Enter a choice: ";
//  cout << "Options(Find/Component/Edit/Delete/Sch/Trim/Link):";
	cin >> choice;
//  cin.get(choice, 1);
  cin.get();
	switch(choice){
		case '1':
//			string key = "-a";
			cout << "Keyword: ";
			cin >> key;
			transform(key.begin(), key.end(), key.begin(), ::toupper);
			if(key == "-A"){
				cout << left << setw(5) << "Num" << setw(15) << "SCH" << setw(15) << "DIP/AIP/PIN" << setw(25) << "[L]/[A]" << endl;
        cout << "------------------------------------------------------------" << endl;
				for(int i = 0; i < bag_lst.size(); i++){
					if(!bag_lst[i].label.empty())
						cout << left << setw(5) << bag_lst[i].num_line << setw(15) << bag_lst[i].sch << setw(15) << bag_lst[i].ip << setw(25) << bag_lst[i].label << endl;
					else
						cout << left << setw(5) << bag_lst[i].num_line << setw(15) << bag_lst[i].sch << setw(15) << bag_lst[i].ip << setw(25) << bag_lst[i].detail << endl;
				}
			}
			else{
				na = false;
				cout << left << setw(5) << "Num" << setw(15) << "SCH" << setw(15) << "DIP/AIP/PIN" << setw(25) << "[L]/[A]" << endl;
			 	cout << "------------------------------------------------------------" << endl;	
				for(int i = 0; i < bag_lst.size(); i++){
					if(size_t found = bag_lst[i].ip.find(key) != string::npos){
						if(!bag_lst[i].label.empty())
						cout << left << setw(5) << bag_lst[i].num_line << setw(15) << bag_lst[i].sch << setw(15) << bag_lst[i].ip << setw(25) << bag_lst[i].label << endl;
						else
							cout << left << setw(5) << bag_lst[i].num_line << setw(15) << bag_lst[i].sch << setw(15) << bag_lst[i].ip << setw(25) << bag_lst[i].detail << endl;
						na = true;
					}
				}
				if(na == false)
					cout << left << setw(5) << "N/A" << setw(15) << "N/A" << setw(15) << "N/A" << setw(25) << "N/A" << endl;
			}
			break;
		case '2':
			cout << "Num: ";
      cin >> key_num_lst;
      if(!cin){
        cin.clear();
        cin.sync();
      }
      else{
			na = false;
      for(int i = 0; i < bag_lst.size(); i++){
        if(bag_lst[i].num_line == key_num_lst && !bag_lst[i].loc_ip.empty())        
          print_ip(bag_lst[i].ip, bag_lst[i].label, bag_lst[i].loc_ip, loc_lst, key_num_lst);
      }
				
//			  fstream f_detail;
	f_lst.open(loc_lst, ios::in);
//  string line, tmp_ip;
	

	if(!f_lst)
		cout << "Fail!" << endl;
	else{
    int tmp_num_lst = 1;
		do{
      getline(f_lst, line);
      if(tmp_num_lst == key_num_lst && !line.empty()){
        Re(line, ",", ",[A]", ",\n                    [A]");
				cout << setw(20) << "                   " << line << endl;
				na = true;
			}
      tmp_num_lst++;
    }while(!f_lst.eof());
    f_lst.close();
		if(na == false)
			cout << "N/A" << endl;
  }
      }
			break;
    case '4':
			cout << "Nums: ";
      cin >> tmp_num_kill;
      if(!cin){
        cin.clear();
        cin.sync();
      }
      else
        Kill(loc_lst, tmp_num_kill);
      
  		break;
    case '3':
			cout << "Num: ";
      cin >> key_num_lst;
      if(!cin){
        cin.clear();
        cin.sync();
      }
      else
        Edit(loc_lst, key_num_lst);
			break;

    case '5':
			cout << "Nums: ";
      cin >> tmp_num_together;
      
      if(!cin){
        cin.clear();
        cin.sync();
      }
      else{
        Str2nums(tmp_num_together, tmp_vec_nums);
        for(int j = 0; j < tmp_vec_nums.size(); j++){
          for(int i = 0; i < bag_lst.size(); i++){
            if(tmp_vec_nums[j] == bag_lst[i].num_line){
              ips.push_back(bag_lst[i].loc_ip);
              break;
            }
          }
        }
        Together(loc_lst, tmp_vec_nums, ips);
        tmp_vec_nums.clear();
        ips.clear();     
      }
      break;
    case '6':
//			cout << "Num:";
//      cin >> key_num_lst;
//      if(!cin){
//        cin.clear();
//        cin.sync();
//      }
//      else
        Sch(loc_lst);
			break;
    case '7':
			Cut(loc_lst);
			break;
    case '8':
			Lst2sch(loc_lst);
			break;
		case '9':
			bag_lst.clear();
			cout << "File path: ";
			cin >> loc_lst;
			break;
		default:
			cout << "Invalid menu choice." << endl;
			break;
	}
}while(1);

  return 0;
}
