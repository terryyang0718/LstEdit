#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
string int2str(int &i){
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

int str2int(const string &str) {
  stringstream ss(str);
  int num;
  ss >> num;
  return num;
}

void Re(string& str, const string& key, const string& from, const string& to){
	if(from.empty())
		return;
	size_t start_pos = 0;
	size_t found = str.find(key);
	if(found == string::npos)
		return;
	else{
		while((start_pos = str.find(from, start_pos)) != string::npos){
  		str.replace(start_pos, from.length(), to);
    	start_pos += to.length();
		}
	}
}

void DelAll(string& str, const string& key){
	size_t found = str.find(key);
	if(found == string::npos)
		return;
	else{
		str.erase(str.begin(),str.end());
	}
}

void AddE(string& str, const string& key, const string& aWord){
	size_t found = str.find(key);
	if(found == string::npos)
		return;
	else{
		str.append(aWord);
	}
}

void AddPos(string& str, const string& key, const int pos, const string& aWord){
	size_t found = str.find(key);
	if(found == string::npos)
		return;
	else{
		str.insert(pos, aWord);
	}
}
void ReRe(string& str, const string& key, const string& f0, const string& f1, const string& to){
	size_t found = str.find(key);
	size_t ff = str.find(f0);

	if(found == string::npos)
		return;
	else{
		
		str.erase(str.find(f0), str.find(f1)-str.find(f0)+1);
		str.insert(ff, to); 
	}
}

void rebuild1(string& str, const string& key, const string& f0, const string& f1){
	size_t found = str.find(key);
	if(found == string::npos)
		return;
	else{
		int end = str.find(f1)-str.find(f0);
		int pos = str.find(f0);
		string tmp0, tmp1;
		for(int i = 0; i <= end; i++){
			tmp0 = str.at(pos);
			tmp1.append(tmp0);
			pos++;
		}
		str = tmp1;
	}
}

void rebuild(string& str, const string& key, const string& f0, const string& f1, const string& g0, const string& g1, const string& h0, const string& h1){
	size_t found = str.find(key);
	if(found == string::npos)
		return;
	else{
		int end0 = str.find(f1)-str.find(f0);
		int pos0 = str.find(f0);
		string s0, s1;
		for(int i = 0; i <= end0; i++){
			s0 = str.at(pos0);
			s1.append(s0);
			pos0++;
		}
		int end1 = str.find(g1)-str.find(g0);
		int pos1 = str.find(g0);
		string t0, t1;
		for(int j = 0; j <= end1; j++){
			t0 = str.at(pos1);
			t1.append(t0);
			pos1++;
		}
		int end2 = str.find(h1)-str.find(h0);
		int pos2 = str.find(h0);
		string u0, u1;
		for(int k = 0; k <= end2; k++){
			u0 = str.at(pos2);
			u1.append(u0);
			pos2++;
		}
		
		s1.append(t1);
		s1.append(u1);
		str = s1;
		
	}
}

void Re1(string& str, const string& key, const string& from, const string& to){
		size_t found = str.find(key);
		if(found == string::npos)
			return;
		else{
			size_t start_pos = str.find(from);
    	if(start_pos == std::string::npos)
        return;
			else{
    		str.replace(start_pos, from.length(), to);
    	}
		}
}

bool wr0(string& str, const string& f0, bool flag) {
    size_t start_pos = str.find(f0);
    if(start_pos != string::npos)
		return !flag;
    else
		return flag;
}

bool wr1(string& str, const string& f1, bool flag) {
	size_t end_pos = str.find(f1);
    if(end_pos != string::npos)
		return !flag;
	else
		return flag;
}

void findKey(string& str, const string& key){
	size_t found = str.find(key);
	if(found == string::npos)
		str.erase(str.begin(),str.end());
	else{
		return;
	}
}

bool Del(string& str, const string& key, bool flag) {
    size_t start_pos = str.find(key);
    if(start_pos == string::npos)
			return flag;
    else
			return !flag;
}

void lst(string& str, const string& key, const string& f0, const string& f1){
	size_t found = str.find(key);
	if(found == string::npos){
		str.erase(str.begin(),str.end());
		return;
	}
	else{
		int pos = str.find(f0)+f0.length();
		int end = str.find(f1)-pos-1;
		string tmp0, tmp1;
		for(int i = 0; i <= end; i++){
			tmp0 = str.at(pos);
			tmp1.append(tmp0);
			pos++;
		}
		str = tmp1;
	}
}
void Lst(string& str, const string& key, const string& f0, const string& f1){
	if(size_t found = str.find(key) == string::npos){
		str.erase(str.begin(),str.end());
		return;
	}
	else{
		int pos = str.find(f0)+f0.length();
		int l = str.find(f1, pos)-pos;
    string tmp_str = str;
		str.assign(tmp_str, pos, l);
	}
}
void Lst_end(string& str, const string& key, const string& f0){
	if(size_t found = str.find(key) == string::npos){
		str.erase(str.begin(),str.end());
		return;
	}
	else{
    string tmp_str = str;
		str.assign(tmp_str.begin()+tmp_str.find(f0)+f0.length(), tmp_str.end());
	}
}


bool key_flag(string& str, const string& key, bool flag){
    size_t found = str.find(key);
    if(found != string::npos)
		  return !flag;
    else
		  return flag;
}

void lst_end(string& str, const string& key, const string& f0){
	size_t found = str.find(key);
	if(found == string::npos){
		str.erase(str.begin(),str.end());
		return;
	}
	else{
		int pos = str.find(f0)+f0.length();
		int end = str.length()-pos-1;
		string tmp0, tmp1;
		for(int i = 0; i <= end; i++){
			tmp0 = str.at(pos);
			tmp1.append(tmp0);
			pos++;
		}
		str = tmp1;
	}
}

bool YesNo(string& str, const string& key, bool flag){
    size_t found = str.find(key);
    if(found != string::npos)
		  return flag = true;
    else
		  return flag = false;
}
