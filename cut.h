#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h> 
//#include "D:\\c\\lib\\re_lib.h"
//#include "D:\\c\\lib\\tmp_lib.h"

using namespace std;

void Detail2ip(string index_detail, vector<string>& ip){
//  string index_detail = detail[34];
  vector<int> ht = vector<int> ();
  size_t head, tail;

  vector<string> dai = {"\n#DIP:", "\n#AIP:", "\n#IO:"};
  for(int i = 0; i < 3; i++){
    bool state_ip = false;
    int cnt_head = 0;   
    while(size_t found = index_detail.find(dai[i], cnt_head) != string::npos){
      if(state_ip == false){
        head = index_detail.find(dai[i], cnt_head);
        ht.push_back(head+dai[i].length());
        cnt_head = head;
        state_ip = true;
      }
      else{
        tail = index_detail.find("([", cnt_head);
        ht.push_back(tail);
        cnt_head = tail;
        state_ip = false;
      }
    }
  }
  sort(ht.begin(), ht.end());
//  vector<string> ip = vector<string> ();
  string tmp_ip;
  int i_ht = 0;
  for(int i = 0; i < ht.size()/2; i++){
    tmp_ip.assign(index_detail, ht[i_ht], ht[i_ht+1]-ht[i_ht]);
    ip.push_back(tmp_ip);
    i_ht = i_ht+2;
  }
  ht.clear();
}





void Cut(string& loc_lst){

//  string loc_lst = "D:\\project\\uz0cuzhd14\\body\\lst\\sch_uz0cuzhd14.lst";
	string tmp_cid;
  size_t pos_body = loc_lst.find("body");
	string body_back;
	body_back.assign(loc_lst, pos_body, loc_lst.length()-pos_body);
//	cout << body_back << endl;
	int i_cid = 0;
	size_t found_cid;
	do{
		tmp_cid.assign(loc_lst, i_cid, pos_body-i_cid-1);
		i_cid++;
	}while((found_cid = body_back.find(tmp_cid)) == string::npos);
  string cid = tmp_cid;
  transform(cid.begin(), cid.end(), cid.begin(), ::toupper);


  fstream f_re;
	f_re.open(loc_lst, ios::in);
  string line, tmp_sch, tmp_detail0, tmp_detail1;
  int step = 0, num_sch = 0;
  vector<string> sch = vector<string> ();
  vector<string> detail = vector<string> ();

	if(!f_re)
		cout << "Fail!" << endl;
	else{
		do{
      getline(f_re, line);
      tmp_sch = line;
      tmp_detail0 = line;

      if(step == 0){
        if(size_t found = line.find("#SCH:") == 0){
          Lst_end(tmp_sch, "#SCH:", "#SCH:");
          sch.push_back(tmp_sch);
          step++;
        }          
      }
      else if(step == 1){
        if(size_t found = line.find("{") == 0){
          tmp_detail1 = "{\n";
          step++;
        }
      }
      else if(step == 2){
        Re(tmp_detail0, " ", " ", "");
        if(size_t found = line.find("}") == 0){
          tmp_detail1 = tmp_detail1+"}";

          detail.push_back(tmp_detail1);
          step = 0;
          tmp_detail1 = "";
          continue;
        }
        if(!tmp_detail0.empty())
          tmp_detail1 = tmp_detail1+tmp_detail0+"\n";
      }
    }while(!f_re.eof());
    f_re.close();
  }

//	sort(sch.begin(), sch.end());
//  vector<string>::iterator unque_iter  = unique(sch.begin(), sch.end());
//  sch.erase(unque_iter, sch.end());

	for(int i = 0; i < sch.size(); i++){
		for(int j = 0; j < sch.size(); j++){
			if(i != j){
				if(sch[i] == sch[j]){
					cout << "\"#SCH:"+sch[i]+"{...}\"" << " has been removed." << endl;
					sch[i] = "x";
					detail[i] = "y";
				}
			}		
		}
	}






  string tmp_print;
  vector<string> print_0 = vector<string> ();
  vector<string> ip = vector<string> ();
  for(int i = 0; i < sch.size(); i++){
    if(sch[i] == cid){
      tmp_print = "#SCH:"+sch[i]+"\n"+detail[i];
      print_0.push_back(tmp_print);
      Detail2ip(detail[i], ip);
      detail[i] = "y";
      sch[i] = "x";
    }
  }

  vector<string> ip_1 = vector<string> ();
  vector<string> print_1 = vector<string> ();
	for(int j = 0; j < ip.size(); j++){
    for(int i = 0; i < sch.size(); i++){
      if(sch[i] == ip[j]){
        tmp_print = "#SCH:"+sch[i]+"\n"+detail[i];
        print_1.push_back(tmp_print);
        Detail2ip(detail[i], ip_1);
        detail[i] = "y";
        sch[i] = "x";
      }
    }
  }

  vector<string> ip_2 = vector<string> ();
  vector<string> print_2 = vector<string> ();
  for(int j = 0; j < ip_1.size(); j++){
    for(int i = 0; i < sch.size(); i++){
      if(sch[i] == ip_1[j]){
        tmp_print = "#SCH:"+sch[i]+"\n"+detail[i];
        print_2.push_back(tmp_print);
        Detail2ip(detail[i], ip_2);
        detail[i] = "y";
        sch[i] = "x";
      }
    }
  }

  vector<string> ip_3 = vector<string> ();
  vector<string> print_3 = vector<string> ();
  for(int j = 0; j < ip_2.size(); j++){
    for(int i = 0; i < sch.size(); i++){
      if(sch[i] == ip_2[j]){
        tmp_print = "#SCH:"+sch[i]+"\n"+detail[i];
        print_3.push_back(tmp_print);
//        Detail2ip(detail[i], ip_3);
        detail[i] = "y";
        sch[i] = "x";
      }
    }
  }
	ip.clear();
	ip_1.clear();
	ip_2.clear();
	ip_3.clear();


  string dytm;
  int tmtm = whatTime();
	int dydy = whatDay();
	string tm_s = int2str(tmtm);
	string dy_s = int2str(dydy);
	dytm.assign("_");
	dytm.append(dy_s);
	dytm.append("_");
  if(tm_s.length() == 5)
    dytm.append("0");
	dytm.append(tm_s);

  string loc_new;
  size_t pos_lst = loc_lst.find("lst");
	loc_new.assign(loc_lst, 0, pos_lst);
//	cout << loc_new << endl;
	loc_new.append("lst\\sch_");
	loc_new.append(tmp_cid);	
  loc_new.append(dytm);  
	loc_new.append(".lst");
//  cout << loc_new << endl;  

  fstream f_pr;
  f_pr.open(loc_new, ios::out);
//  reverse(print.begin(), print.end());

  vector<string> print = vector<string> ();
	for(int i = 0; i < print_3.size(); i++)
		print.push_back(print_3[i]);
	for(int i = 0; i < print_2.size(); i++)
		print.push_back(print_2[i]);
	for(int i = 0; i < print_1.size(); i++)
		print.push_back(print_1[i]);
	for(int i = 0; i < print_0.size(); i++)
		print.push_back(print_0[i]);
	print_0.clear();
	print_1.clear();
	print_2.clear();
	print_3.clear();




	for(int i = 0; i < print.size(); i++){
    f_pr << print[i] << endl;
  }
	for(int i = 0; i < sch.size(); i++){
		if(sch[i] != "x")
			cout << "\"#SCH:"+sch[i]+"{...}\"" << " has been removed." << endl;
	}
	sch.clear();
	detail.clear();
	print.clear();
  loc_lst = loc_new;

//  return 0;
}
