#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h> 
#include <iomanip>
//#include "D:\\tmp_0315\\c\\lib\\re_lib.h"
//#include "D:\\tmp_0315\\c\\lib\\tmp_lib.h"

using namespace std;


void Sch(string& loc_lst){

//  string loc_lst = "D:\\tmp_0315\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";
	string tmp_cid;
  size_t pos_body = loc_lst.find("body");
	string body_back;
	body_back.assign(loc_lst, pos_body, loc_lst.length()-pos_body);
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
  int step = 0, num_sch;
  vector<string> sch = vector<string> ();
  vector<int> detail = vector<int> ();

  vector<string> sch_begin = vector<string> ();
  vector<int> detail_begin = vector<int> ();
	if(!f_re)
		cout << "Fail!" << endl;
	else{
		int num = 1;
//		vector<int> num_lst = vector<int> ();
		do{
      getline(f_re, line);
      if(step == 0){
        if(size_t found = line.find("#SCH:") == 0){
      		tmp_sch = line;
          Lst_end(tmp_sch, "#SCH:", "#SCH:");
          sch.push_back(tmp_sch);
					detail.push_back(num);
          sch_begin.push_back(tmp_sch);
					detail_begin.push_back(num);
          step++;
        }          
      }
      else if(step == 1){
        if(size_t found = line.find("{") == 0){
          sch.push_back(tmp_sch);
					detail.push_back(num);
          step++;
        }
      }
      else if(step == 2){
        sch.push_back(tmp_sch);
				detail.push_back(num);
        if(size_t found = line.find("}") == 0){
          step = 0;
					tmp_sch = "";
				}
      }
			num++;
    }while(!f_re.eof());
    f_re.close();
  }

	cout << left << setw(5) << "Num" << setw(15) << "SCH" << endl;
	cout << "--------------------" << endl;
	for(int i = 0; i < detail_begin.size(); i++)
		cout << left << setw(5) << detail_begin[i] << setw(15) << sch_begin[i] << endl;
	cout << "Num:";
//	cin >> num_sch;

  bool ok = false;
  do{
    cin >> num_sch;
    for(int i = 0; i < detail_begin.size(); i++){
		  if(detail_begin[i] == num_sch)
        ok = true;
    }
    if(ok == false){
      cout << "Non-existent input, try again!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }while(ok == false);

  if(!cin){
		cin.clear();
		cin.sync();
	}
	
	int tmp_num;
	for(int i = 0; i < detail_begin.size(); i++){
		if(detail_begin[i] == num_sch)
			tmp_num = i;
	}

	vector<int> want = vector<int> ();
	for(int i = 0; i < sch.size(); i++){
		if(sch[i] == sch_begin[tmp_num])
			want.push_back(detail[i]);
	}


	f_re.open(loc_lst, ios::in);
  fstream f_key;
	f_key.open("key.txt", ios::out);
	if(!f_re)
		cout << "Fail!" << endl;
	else{
    int num = 1;
		do{
      getline(f_re, line);
			for(int i = 0; i < want.size(); i++){
      	if(num == want[i])
					f_key << line << endl;
			}
    	num++;
    }while(!f_re.eof());
    f_re.close();
		f_key.close();
  }

	for(int i = 0; i < detail.size(); i++){
		for(int j = 0; j < want.size(); j++){
			if(detail[i] == want[j])
				detail.erase(detail.begin()+i);
		}
	}

	system("start key.txt");	
	system("pause");

  fstream f_key_in;
	f_key_in.open("key.txt", ios::in);
	string tmp_key_txt;
	if(!f_key_in)
		cout << "Fail!" << endl;
	else{
		do{
      getline(f_key_in, line);
      if(!line.empty())
        tmp_key_txt.append(line+"\n");
    }while(!f_key_in.eof());
    f_key_in.close();
  }
  system("Del key.txt");

//	cout << tmp_key_txt << endl;


//	for(int i = 0; i < detail.size(); i++)
//		cout << detail[i] << endl;

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
/*
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
*/
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
			for(int i = 0; i < detail.size(); i++){
      	if(tmp_num_lst == detail[i])
					f_wr << line << endl;
			}
			if(tmp_num_lst == num_sch)
				f_wr << tmp_key_txt;
      tmp_num_lst++;
    }while(!f_re.eof());
    f_re.close();
    f_wr.close();
  }
	detail.clear();
	sch.clear();
	detail_begin.clear();
	sch_begin.clear();
	want.clear();
	loc_lst = loc_new;
		




	

//	return 0;
}





