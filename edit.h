#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h> 
//#include "D:\\tmp_0222\\c\\lib\\re_lib.h"
//#include "D:\\tmp_0222\\c\\lib\\tmp_lib.h"

using namespace std;

void Edit(string& loc_lst, int& num_lst){

//  int num_lst = 439;
//  string loc_lst = "D:\\project\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";
  fstream f_re;
	f_re.open(loc_lst, ios::in);
  string line, tmp_ip;

	if(!f_re)
		cout << "Fail!" << endl;
	else{
    int tmp_num_lst = 1;
		do{
      getline(f_re, line);
      if(tmp_num_lst == num_lst)
        tmp_ip = line;
      tmp_num_lst++;
    }while(!f_re.eof());
    f_re.close();
  }

  fstream f_key;
	f_key.open("key.txt", ios::out);
	if(!tmp_ip.empty()){
	  Re(tmp_ip, ",", ",[A]", ",\n[A]");
    f_key << tmp_ip << endl;
  }
  f_key.close();

	system("start key.txt");	
	system("pause");

  fstream f_key_in;
	f_key_in.open("key.txt", ios::in);
//  string line, tmp_ip;
  tmp_ip = "";  

	if(!f_key_in)
		cout << "Fail!" << endl;
	else{
//    int tmp_num_lst = 1;
		do{
      getline(f_key_in, line);
      if(!line.empty())
        tmp_ip.append(line);
    }while(!f_key_in.eof());
    f_key_in.close();
//    cout << tmp_ip << endl;
    Re(tmp_ip, ")#", ")#", ")\n#");
  }
  system("Del key.txt");

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

  fstream f_wr;

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

  string loc_new;
  size_t pos_lst = loc_lst.find("lst");
	loc_new.assign(loc_lst, 0, pos_lst);
//	cout << loc_new << endl;
	loc_new.append("lst\\sch_");
	loc_new.append(tmp_cid);	
  loc_new.append(dytm);  
	loc_new.append(".lst");
//  cout << loc_new << endl;  
  f_wr.open(loc_new, ios::out);
	f_re.open(loc_lst, ios::in);
//  string line, tmp_ip;

	if(!f_re)
		cout << "Fail!" << endl;
	else{
    int tmp_num_lst = 1;
		do{
      getline(f_re, line);
      if(tmp_num_lst == num_lst)
        line = tmp_ip;
			if(!line.empty())
      	f_wr << line << endl;
      tmp_num_lst++;
    }while(!f_re.eof());
    f_re.close();
    f_wr.close();
  }
	loc_lst = loc_new;	

//  return 0;
}
