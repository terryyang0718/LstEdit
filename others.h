#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <direct.h>
//#include "D:\\tmp_0227\\c\\lib\\re_lib.h"
using namespace std;

void other_ip(string& loc_lst, string& ip, string& loc_ip){

	string line;
//	cin >> ip;
//	cin >> loc_ip;
	vector<string> loc_tbl = {"\\\\Nx3100\\design\\d700\\lib\\uhlib\\sym.tbl", "\\\\Nx3100\\design\\d700\\lib\\ullib\\sym.tbl", "\\\\CADNAS\\cadpublic\\ftclib\\uc025ee\\prim\\ht8core_cell\\sym.tbl", "\\\\CADNAS\\cadpublic\\ftclib\\uc025ee\\prim\\core\\sym.tbl", "\\\\Nx3100\\design\\d700\\lib\\ht93cee\\sym.tbl", "\\\\Nx3100\\design\\d700\\lib\\I-PlanLib\\sym.tbl", "\\\\Nx3100\\design\\d700\\lib\\tinylib\\sym.tbl", "\\\\Nx3100\\design\\d700\\lib\\uc05macro\\sym.tbl", "\\\\Nx3100\\design\\d700\\lib\\wvsym\\sym.tbl"};

//	string loc_lst = "D:\\tmp_0227\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";
	size_t pos_body = loc_lst.find("body");
	string dir_ip_tmp;
	dir_ip_tmp.assign(loc_lst, 0, pos_body);
	dir_ip_tmp.append("ip_tmp");
	char tmp[100];
	strcpy(tmp, dir_ip_tmp.c_str());
	_mkdir(tmp);

	string num_ip;
	bool exist_ip = false;
	int i_tbl = 0;
	for(int i = 0; i < loc_tbl.size(); i++){
		fstream f_tbl;
		f_tbl.open(loc_tbl[i_tbl], ios::in);
		if(!f_tbl)
			cout << "fail" <<	endl;
		else{
			do{	
				getline(f_tbl, line);
				num_ip = line;
				Lst(num_ip, ip, ip+".1 ", " ");
				if(!num_ip.empty())
					exist_ip = true;
			}while(!f_tbl.eof());
			f_tbl.close();
		}
		if(exist_ip == true)
			break;
		i_tbl++;
	}
	
//	system("pause");
if(exist_ip == true){
	fstream f_lib;
	fstream f_out;
	int num = str2int(num_ip);
	string loc_lib;
	loc_lib.assign(loc_tbl[i_tbl].begin(), loc_tbl[i_tbl].end()-3);
	loc_lib.append("lib");
	f_lib.open(loc_lib, ios::in);
	f_lib.seekg(num, ios::cur);

	string dir_ip_tmp_1 = dir_ip_tmp+"\\"+ip+".1";
	f_out.open(dir_ip_tmp_1, ios::out);
	if(!f_lib)
		cout << "fail" <<	endl;
	else{
		do{	
			getline(f_lib, line);
			if(!line.empty())
				f_out << line << endl;
		}while(!f_lib.eof());
		f_lib.close();
	}
	loc_ip = dir_ip_tmp_1;
		f_out.close();
}

//	return 0;
}
