#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
//int getdir(string dir, vector<string> &files);
/*
int main(){
    string dir;// = string(".");//資料夾路徑(絕對位址or相對位址)
    cin >> dir;
    vector<string> files = vector<string>();
    getdir(dir, files);
    //輸出資料夾和檔案名稱於螢幕
    for(int i=0; i<files.size(); i++){
        cout << files[i] << endl;
    }
    system("pause");
    return 0;
}

int getdir(string dir, vector<string> &files){
    DIR *dp;//創立資料夾指標
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while((dirp = readdir(dp)) != NULL){//如果dirent指標非空
        files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
    }
    closedir(dp);//關閉資料夾指標
    return 0;
}

int whatTime(){
	time_t t; 
	struct tm *tm; 
	int hour, minute, sec; 
	time(&t); 
	tm = localtime(&t); 
	hour = tm->tm_hour; 
	minute = tm->tm_min; 
	sec = tm->tm_sec; 
	return hour*1e4+minute*1e2+sec;
}

int whatDay(){
	time_t t; 
	struct tm *tm; 
	int year, month, day; 
	time(&t); 
	tm = localtime(&t); 
	year = tm->tm_year + 1900; 
	month = tm->tm_mon + 1; 
	day = tm->tm_mday; 
	return year*1e4+month*1e2+day;
}
*/
void Lst2cid(string loc_lst, string& cid){
  string tmp_cid, body_back;
  size_t pos_body = loc_lst.find("body");
	body_back.assign(loc_lst, pos_body, loc_lst.length()-pos_body);
	int i_cid = 0;
	do{
		tmp_cid.assign(loc_lst, i_cid, pos_body-i_cid-1);
		i_cid++;
	}while(body_back.find(tmp_cid) == string::npos);
  cid = tmp_cid;
  transform(cid.begin(), cid.end(), cid.begin(), ::toupper);
}



void Comma(string tmp_pt, vector<string>& num_pt){
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
//  vector<int> num_pt = vector<int> ();
  num_pt.clear();
  if(!tmp_pt.empty())
    for(int i = 0; i < pt.size()-1; i++){
      tmp_pt1.assign(tmp_pt, pt[i]+1, pt[i+1]-pt[i]-1);
      num_pt.push_back(tmp_pt1);
    }
  pt.clear();
}

void Sprt(string tmp_pt, string comma, vector<string>& num_pt){
//  string tmp_pt = "439, 444, 448, 540, 542";
//  string comma = ",";
  size_t f_pt = -1;
  vector<int> pt = vector<int> ();
  pt.clear();
  pt.push_back(f_pt);
  f_pt++;
  while((f_pt = tmp_pt.find(comma, f_pt)) != string::npos){
 //   cout << f_pt << endl;
    pt.push_back(f_pt);
    f_pt++;
  }
  pt.push_back(tmp_pt.length()+1);
  string tmp_pt1;
//  vector<int> num_pt = vector<int> ();
  num_pt.clear();
  if(!tmp_pt.empty())
    for(int i = 0; i < pt.size()-1; i++){
      tmp_pt1.assign(tmp_pt, pt[i]+1, pt[i+1]-pt[i]-1);
      num_pt.push_back(tmp_pt1);
    }
  pt.clear();
}








bool White(char x){
  if(x == ' ' || x == '\t')
    return true;
  return false;
}
void Part(string line, int& index, bool& status, string& data){
  data = "";
  status = true;
  while(index < line.length() && !White(line[index])){//If no whitespace then data
    data += line[index];
    index++;
  }
  if(data == "")
    status = false;
  while(index < line.length() && White(line[index]))//Increase index to pass all whitespace
    index++;
}

void BlankParse(string line, vector<string>& part){
  bool status = true;
  int index = 0;
  string data;
  do{
    data.clear();
    while(index < line.length() && !White(line[index])){//If no whitespace then data
      data += line[index];
      index++;
    }
    if(data.empty())
      status = false;
    while(index < line.length() && White(line[index]))//Increase index to pass all whitespace
      index++;
    part.push_back(data);
  }while(status == true && index < line.length());
}

