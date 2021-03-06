#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iomanip>
//#include "D:\\c\\lib_1\\getDir_silent.h"
//#include "D:\\c\\lib_1\\re_lib.h"
//#include "D:\\c\\lib_1\\others.h"
//#include "D:\\c\\lib_1\\tmp_lib.h"
//#include "D:\\c\\lib_1\\sch2sym.h"
#include "net2sch.h"
#include "sym2sch_01.h"

using namespace std;
class NodeLst{
  public:
    int num;
    string type;
    string sch;
    string ip;
    string label;

    string loc_ip;
    int len, len_col, delta;
    int x, y, z;
    string lv;
		string all;
    string next;
};
class NodeSch{
  public:
    string sch;
    string num_sch;
    string next;
    string lv;
};

void I2L(int len_ip, int& y){
  y = y+70+len_ip;
}
void L2I(int len_ip, int& y){
  y = y-70-len_ip;
}

void DateTime(string& datetime){
	time_t lt;
	struct tm *tp;
	lt = time(NULL);
	tp = localtime(&lt);
	vector<int> grp_tm = {tp->tm_mon+1, tp->tm_mday, tp->tm_year+1900, tp->tm_hour, tp->tm_min};
//	string datetime = "";
	for(int i = 0; i < 2-int2str(grp_tm[0]).length(); i++)
		datetime += "0";
	datetime = datetime+int2str(grp_tm[0])+"-";
	for(int i = 0; i < 2-int2str(grp_tm[1]).length(); i++)
		datetime += "0";
	datetime = datetime+int2str(grp_tm[1])+"-";
	for(int i = 0; i < 4-int2str(grp_tm[2]).length(); i++)
		datetime += "0";
	datetime = datetime+int2str(grp_tm[2])+"_";
	for(int i = 0; i < 2-int2str(grp_tm[3]).length(); i++)
		datetime += "0";
	datetime = datetime+int2str(grp_tm[3])+":";
	for(int i = 0; i < 2-int2str(grp_tm[4]).length(); i++)
		datetime += "0";
	datetime = datetime+int2str(grp_tm[4]);
	grp_tm.clear();
}


void LenIp(string loc_ip, int& len){
  vector<int> all_y = vector<int> ();
  ifstream ipFile;
  ipFile.open(loc_ip);
  if(!ipFile)
    cout << "fail" << endl;
  else{
    string line;
    int step = 0;
    vector<string> part = vector<string> (); 
    do{
      getline(ipFile, line);
      if(step == 0){
        if(line.find("P") == 0)
          step++;
//      }else if(step == 1){
//        if(line.find("L") == 0)
//          step++;
      }else{
        if(line.find("A") == 0){
          BlankParse(line, part);
          int tmp_part = str2int(part[2]);
          all_y.push_back(tmp_part);
          part.clear();
          step = 0;    
        }
      }
    }while(!ipFile.eof());
    ipFile.close();
  }
  if(!all_y.empty()){
    sort(all_y.begin(), all_y.end());
    len = all_y[all_y.size()-1]-all_y[0];
    all_y.clear();
  }
}

void LocateIp(string lvlv, string schsch, vector<NodeLst>& bagLst, NodeLst& candyLst){
//	string lvlv = "1", schsch = "UHBODY";
	for(int i = 0; i < bagLst.size(); i++)
    if(bagLst[i].lv == lvlv && bagLst[i].sch == schsch)
			bagLst[i].delta = bagLst[i].len+bagLst[i].len_col+90;
	

  int tmp_y = 0, tmp_delta = 0;
	for(int i = 0; i < bagLst.size(); i++){
		if(bagLst[i].lv == lvlv && bagLst[i].sch == schsch){
			if(tmp_y-tmp_delta-bagLst[i].delta < 250)
				bagLst[i].y = 1590;
			else
				bagLst[i].y = tmp_y-tmp_delta;
			tmp_y = bagLst[i].y;
			tmp_delta = bagLst[i].delta;
		}
	}
	vector<int> grp_x = {950, 280, 1620};
	int step_x = 2;
	for(int i = 0; i < bagLst.size(); i++){
		if(bagLst[i].lv == lvlv && bagLst[i].sch == schsch){
			if(bagLst[i].y == 1590)
				step_x++;
			bagLst[i].x = grp_x[step_x%3];
		}
	}
	grp_x.clear();
	int tmp_y_insert;
	for(int i = 0; i < bagLst.size(); i++){
		if(bagLst[i].lv == lvlv && bagLst[i].sch == schsch){
			tmp_y_insert = bagLst[i].y;
			L2I(bagLst[i].len, tmp_y_insert);
			bagLst[i].y = tmp_y_insert;
		}
	}
	int step_z = 0;
	bool flag_z = true;
	for(int i = 0; i < bagLst.size(); i++){
		if(bagLst[i].lv == lvlv && bagLst[i].sch == schsch){
			if(bagLst[i].x == 950 && flag_z == true){
				step_z++;
				flag_z = false;
			}
			if(bagLst[i].x == 280)
				flag_z = true;
			bagLst[i].z = step_z;
		}
	}
}

void Parse(int& num, string& data, vector<NodeLst>& bagLst, NodeLst& candyLst, string tmp_now_sch){
  string ip = data;
  string label = "";
  string part = data;
  vector<string> part_comma = vector<string> ();
  part_comma.clear();
  if(data.find("#AIP:") != string::npos){
    Lst(ip, "#AIP:", "#AIP:", "([");
    Lst(part, "#AIP:", "(", ")");
//    Comma(part, part_comma);
    Sprt(part, ",[", part_comma);
    for(int i = 0; i < part_comma.size(); i++)
      if(part_comma[i].find("[L]=") == 0){
        Lst_end(part_comma[i], "[L]=", "[L]=");
        label = part_comma[i];
      }
    if(label.empty())
      label = "-";
    candyLst.sch = tmp_now_sch;
    candyLst.num = num;
    candyLst.type = "IP";
    candyLst.ip = ip;
    candyLst.label = label;
    bagLst.push_back(candyLst);
  }
  else if(data.find("#DIP:") != string::npos){
    Lst(ip, "#DIP:", "#DIP:", "([");
    Lst(part, "#DIP:", "(", ")");
//    Comma(part, part_comma);
    Sprt(part, ",[", part_comma);
    for(int i = 0; i < part_comma.size(); i++)
      if(part_comma[i].find("[L]=") == 0){
        Lst_end(part_comma[i], "[L]=", "[L]=");
        label = part_comma[i];
      }
    if(label.empty())
      label = "-";
    candyLst.sch = tmp_now_sch;
    candyLst.num = num;
    candyLst.type = "IP";
    candyLst.ip = ip;
    candyLst.label = label;
    bagLst.push_back(candyLst);
  }
  else if(data.find("#PIN:") != string::npos){
    Lst(ip, "#PIN:", "#PIN:", "([");
    Lst(part, "#PIN:", "(", ")");
//    Comma(part, part_comma);
    Sprt(part, ",[", part_comma);
    for(int i = 0; i < part_comma.size(); i++)
      if(part_comma[i].find("[L]=") == 0){
        Lst_end(part_comma[i], "[L]=", "[L]=");
        label = part_comma[i];
      }
    if(label.empty())
      label = "-";
    candyLst.sch = tmp_now_sch;
    candyLst.num = num;
    candyLst.type = "PIN";
    candyLst.ip = ip;
    candyLst.label = label;
    bagLst.push_back(candyLst);
  }
  else if(data.find("#IO:") != string::npos){
    Lst(ip, "#IO:", "#IO:", "([");
    Lst(part, "#IO:", "(", ")");
//    Comma(part, part_comma);
    Sprt(part, ",[", part_comma);
    for(int i = 0; i < part_comma.size(); i++)
      if(part_comma[i].find("[L]=") == 0){
        Lst_end(part_comma[i], "[L]=", "[L]=");
        label = part_comma[i];
      }
    if(label.empty())
      label = "-";
    candyLst.sch = tmp_now_sch;
    candyLst.num = num;
    candyLst.type = "IP";
    candyLst.ip = ip;
    candyLst.label = label;
    bagLst.push_back(candyLst);
  }
  else{
    candyLst.num = num;
    candyLst.type = "TEXT";
    candyLst.ip = data;
    candyLst.label = "-";
    bagLst.push_back(candyLst);
  }
} 




//int main(){
void Lst2sch(string loc_lst){
//  string loc_lst;// = "D:\\lst_edit_1.2\\tmp_0227\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";
//  cin >> loc_lst;
  NodeLst candyLst;
  vector<NodeLst> bagLst;
  bagLst.clear();
  NodeSch candySch;
  vector<NodeSch> bagSch;
  bagSch.clear();

//  vector<string> content_sch = vector<string> ();
//  content_sch.clear(); 

  ifstream f_lst;
  f_lst.open(loc_lst);
  if(!f_lst)
    cout << "Fail!" << endl;
  else{
    string line, tmp_sch, tmp_now_sch;
    int num = 1, step = 0;
    do{
      getline(f_lst, line);
      tmp_sch = line;
      if(line.find("|") != string::npos){
        size_t pos_comment = line.find("|");
        line.assign(line, 0, pos_comment);
      }
      
      if(step == 0){
        if(line.find("#SCH:") == 0){
          Lst_end(tmp_sch, "#SCH:", "#SCH:");
          tmp_now_sch = tmp_sch;
          candySch.sch = tmp_sch;
          bagSch.push_back(candySch);
          step++;
        }
      }
      else if(step == 1){
        if(line.find("{") == 0)
          step++;
      }
      else{
        if(line.find("}") == 0){
//          content_sch.push_back(tmp_content_sch);
          tmp_now_sch.clear();
          step = 0; 
        }
        else
          if(!line.empty()){
//            tmp_content_sch = tmp_content_sch+line+"\n";
            Parse(num, line, bagLst, candyLst, tmp_now_sch);
          }
      }
      num++;
    }while(!f_lst.eof());
  }

  string dir_ip = loc_lst;
  vector<string> ips = vector<string> ();
  size_t pos_body = loc_lst.find("body");
  dir_ip.assign(loc_lst, 0, pos_body);
  vector<string> dir_part = {dir_ip+"aip\\sym\\", dir_ip+"dip\\sym\\", dir_ip+"sym\\", dir_ip+"macro\\sym\\"};
  for(int i = 0; i < dir_part.size(); i++){
    ips.clear();
    getdir(dir_part[i], ips);
		for(int m = 0; m < ips.size(); m++)
			transform(ips[m].begin(), ips[m].end(), ips[m].begin(), ::tolower);
    for(int j = 0; j < bagLst.size(); j++){
      string lstIp_lower = bagLst[j].ip;
      transform(lstIp_lower.begin(), lstIp_lower.end(), lstIp_lower.begin(), ::tolower);
      for(int k = 0; k < ips.size(); k++)
        if(ips[k] == lstIp_lower+".1"){
          bagLst[j].loc_ip = dir_part[i]+ips[k];
          break;
        }
    }
  }
  dir_part.clear(); ips.clear();


  
  for(int i = 0; i < bagLst.size(); i++)  
    if(bagLst[i].loc_ip.empty()){
      string lstIp_lower = bagLst[i].ip;
      transform(lstIp_lower.begin(), lstIp_lower.end(), lstIp_lower.begin(), ::tolower);
      other_ip(loc_lst, lstIp_lower, bagLst[i].loc_ip);
    }
  

  for(int i = 0; i < bagSch.size(); i++)
    for(int j = 0; j < bagLst.size(); j++)
      if(bagLst[j].sch == bagSch[i].sch){
        if(bagSch[i].next.empty())
          bagSch[i].next = int2str(bagLst[j].num);
        else
          bagSch[i].next = bagSch[i].next+"@"+int2str(bagLst[j].num);
      }


  for(int i = 0; i < bagSch.size(); i++)
    for(int j = 0; j < bagLst.size(); j++)
      if(bagLst[j].ip == bagSch[i].sch){
        bagSch[i].num_sch = int2str(bagLst[j].num);
        break;
      } 
  string cid, tmp_next_cid;
  Lst2cid(loc_lst, cid);
  vector<string> tmp_next = vector<string> (); 
  int tmp_lv = 0;
  for(int i = 0; i < bagSch.size(); i++)
    if(bagSch[i].sch == cid){
      bagSch[i].lv = int2str(tmp_lv);
      tmp_next_cid = bagSch[i].next;
      break;
    }
  tmp_next.clear();
//  Comma(tmp_next_cid, tmp_next);
  Sprt(tmp_next_cid, "@", tmp_next);
  tmp_next_cid.clear();
  tmp_lv++;


  do{
    for(int i = 0; i < tmp_next.size(); i++)
      for(int j = 0; j < bagSch.size(); j++)
        if(bagSch[j].lv.empty())
          if(tmp_next[i] == bagSch[j].num_sch){
            bagSch[j].lv = int2str(tmp_lv);
            if(tmp_next_cid.empty())
              tmp_next_cid = bagSch[j].next;
            else
              tmp_next_cid = tmp_next_cid+"@"+bagSch[j].next;
            break;
          }
    tmp_next.clear();
//    Comma(tmp_next_cid, tmp_next);
    Sprt(tmp_next_cid, "@", tmp_next);
    tmp_next_cid.clear();
    tmp_lv++;        
  }while(!tmp_next.empty());  

//Can't find loc_ip ...  
  bool flag_ip = false;
  for(int i = 0; i < bagLst.size(); i++){
    if(bagLst[i].loc_ip.empty() && bagLst[i].type != "PIN" && bagLst[i].type != "TEXT"){
      bool flag_sch = false;
      for(int j = 0; j < bagSch.size(); j++){
        if(bagSch[j].sch == bagLst[i].ip){
          flag_sch = true;
          break;
        }
        else
          flag_sch = false;
      }
      if(flag_sch == false){  
        cout << "[Error] Cannot find the IP \""+bagLst[i].ip+"\"." << endl;
        flag_ip = true;
      }
    }
  }
  if(flag_ip == true)
    return;

//Combining bagLst[i].lv & bagSch[i] ...
  for(int i = 0; i < bagLst.size(); i++){
    for(int j = 0; j < bagSch.size(); j++){
      if(bagLst[i].sch == bagSch[j].sch){
        bagLst[i].lv = bagSch[j].lv;
        break;
      }
    }
  }

	int num_net = 100;
	vector<string> lv_draw = {"3", "2", "1", "0"};
	for(int m = 0; m < 4; m++){
//Measuring the length of ip ...
  for(int i = 0; i < bagLst.size(); i++){
    if(bagLst[i].lv == lv_draw[m] && !bagLst[i].loc_ip.empty() && bagLst[i].type == "IP"){
      int tmp_len;
      LenIp(bagLst[i].loc_ip, tmp_len);
      bagLst[i].len = tmp_len;

      string detail_all;
      int tmp_len_col;
      ifstream lstFile;
      lstFile.open(loc_lst);
      if(!lstFile)
        cout << "fail" << endl;
      else{
        string line, tmp_detail;
        int j = 1;
        do{
          vector<string> detail = vector<string> ();
          getline(lstFile, line);
          if(j == bagLst[i].num){
            tmp_detail = line;
            Lst(tmp_detail, "(", "(", ")");
            if(!tmp_detail.empty()){
//              Comma(tmp_detail, detail);
              Sprt(tmp_detail, ",[", detail);
              tmp_len_col = 10*detail.size();
              detail.clear();
            }
          }
          j++;
        }while(!lstFile.eof());
        lstFile.close();
      }
      bagLst[i].len = tmp_len;
      bagLst[i].len_col = tmp_len_col;
    }else{
      bagLst[i].len = 0;
      bagLst[i].len_col = 0;
    }
  }

  
//deciding the location of ip ...
	for(int i = 0; i < bagSch.size(); i++)
		if(bagSch[i].lv == lv_draw[m])
			LocateIp(lv_draw[m], bagSch[i].sch, bagLst, candyLst);
/*
  for(int i = 0; i < bagLst.size(); i++)
		if(bagLst[i].lv == lv_draw[m] && !bagLst[i].loc_ip.empty())
      cout << bagLst[i].ip+" "+bagLst[i].type << bagLst[i].x << " " << bagLst[i].y << " " << endl;
*/


//	int num_net = 100;
	for(int i = 0; i < bagLst.size(); i++){
		if(bagLst[i].lv == lv_draw[m] && !bagLst[i].loc_ip.empty()){
			if(bagLst[i].type == "IP"){
				Sym2sch(loc_lst, int2str(bagLst[i].num), bagLst[i].loc_ip, bagLst[i].x, bagLst[i].y, num_net, bagLst[i].all);
//        cout << bagLst[i].ip << endl;
      }
      else if(bagLst[i].type == "PIN")
				Net2sch(loc_lst, int2str(bagLst[i].num), bagLst[i].x, bagLst[i].y, num_net, bagLst[i].all);
			else 
				continue;
		}
	}
//  system("pause");

//drawing the picture
	string tmp_datetime;
	DateTime(tmp_datetime);
	string dir_sch;
	dir_sch.assign(loc_lst, 0, pos_body);
	dir_sch = dir_sch+"sch\\";
	fstream drawFile;
	for(int i = 0; i < bagLst.size(); i++){
		if(bagLst[i].lv == lv_draw[m]){
			string title = "V 51\nK 197679529000 "+bagLst[i].sch+"\nY 0\nD 0 0 2200 1700\nZ 10\nI 1 CSIZE 1 0 0 0 1 '\nA 1993 148 17 0 5 3 @NAME="+bagLst[i].sch+"\nA 1993 107 17 0 5 3 @SHEET="+int2str(bagLst[i].z)+"\nA 2003 68 17 0 5 3 @DATETIME=";
			ofstream drawFile;
			drawFile.open(dir_sch+bagLst[i].sch+"."+int2str(bagLst[i].z));
			drawFile << title+tmp_datetime << endl;
		}
		drawFile.close();
	}
	
	for(int i = 0; i < bagSch.size(); i++){
		for(int j = 0; j < bagLst.size(); j++){
			if(bagLst[j].lv == lv_draw[m] && bagLst[j].sch == bagSch[i].sch){
				drawFile.open(dir_sch+bagLst[j].sch+"."+int2str(bagLst[j].z), ios::out|ios::app);
				drawFile << bagLst[j].all;
				drawFile.close();
			}
		}
	}

//making the sym
	for(int i = 0; i < bagSch.size(); i++)
		if(bagSch[i].lv == lv_draw[m])
			Sch2sym(loc_lst, bagSch[i].sch);	

//updating the sym
  dir_ip.assign(loc_lst, 0, pos_body);
  dir_part = {dir_ip+"aip\\sym\\", dir_ip+"dip\\sym\\", dir_ip+"sym\\", dir_ip+"ip_tmp\\", dir_ip+"macro\\sym\\"};
  for(int i = 0; i < dir_part.size(); i++){
    ips.clear();
    getdir(dir_part[i], ips);
		for(int m = 0; m < ips.size(); m++)
			transform(ips[m].begin(), ips[m].end(), ips[m].begin(), ::tolower);
    for(int j = 0; j < bagLst.size(); j++){
      if(bagLst[j].loc_ip.empty()){
        string lstIp_lower = bagLst[j].ip;
        transform(lstIp_lower.begin(), lstIp_lower.end(), lstIp_lower.begin(), ::tolower);
        for(int k = 0; k < ips.size(); k++)
          if(ips[k] == lstIp_lower+".1"){
            bagLst[j].loc_ip = dir_part[i]+ips[k];
            break;
          }
      }
    }
  }
  dir_part.clear(); ips.clear();


	}
	lv_draw.clear();




/*

	for(int i = 0; i < bagLst.size(); i++){
		if(bagLst[i].lv == "2" && !bagLst[i].all.empty()){
				cout << bagLst[i].all << endl;
		}
	}
*/


/*
  for(int i = 0; i < bagLst.size(); i++){
    if(bagLst[i].lv == "2")
      cout << bagLst[i].ip+" "+bagLst[i].sch+" " << bagLst[i].x << " " << bagLst[i].y << " " << bagLst[i].z << endl;
  }

*/


/*
	for(int i = 0; i < bagLst.size(); i++)
		if(bagLst[i].ip == "UHIOPWRBLK")
			cout << bagLst[i].loc_ip << endl;
*/














//  cout << dir_ip <<endl;
//  getdir();
//  for(int i = 0; i < bagLst.size(); i++)
//    if(bagLst[i].loc_ip.empty())
//     cout << bagLst[i].num << "  " << bagLst[i].ip << " " << bagLst[i].loc_ip << endl;
/*lv parse
  for(int i = 0; i < bagSch.size(); i++)
    cout << left << setw(20) << bagSch[i].sch << setw(20) << bagSch[i].lv << endl;
*/
//  cout << cid << endl;
  
//  return 0;
}
