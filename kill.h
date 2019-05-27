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

void Kill(string& loc_lst, string& tmp_pt){

//  int num_lst = 439;
//  string loc_lst = "D:\\project\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";
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
  vector<int> num_pt = vector<int> ();
  num_pt.clear();
  for(int i = 0; i < pt.size()-1; i++){
    tmp_pt1.assign(tmp_pt, pt[i]+1, pt[i+1]-pt[i]-1);
    num_pt.push_back(str2int(tmp_pt1));
  }
  pt.clear();




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

  fstream f_wr, f_re;

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
  string line, tmp_ip, tmp_people;

	if(!f_re)
		cout << "Fail!" << endl;
	else{
    int tmp_num_lst = 1;
		do{
      getline(f_re, line);
      for(int i = 0; i < num_pt.size(); i++){
        if(tmp_num_lst == num_pt[i]){
          tmp_people = line;
          Lst(tmp_people, "#", "#", "([");
          cout << "\"#"+tmp_people+"(...)\" has been deleted." << endl;
          line.erase(line.begin(), line.end());
        }
      }
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

