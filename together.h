#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iomanip>
//#include "re_lib.h"
//#include "getDir_silent.h"
#include "combine_net.h"
#include "net_ip.h"

using namespace std;

void Together(string loc_lst, vector<int> nums, vector<string> loc_ips){
//  vector<int> nums = {439, 444, 448};
//  vector<string> loc_ips = {"D:\\project\\uz0huzhn11\\dip\\sym\\uhcoreirv3.1", "D:\\project\\uz0huzhn11\\dip\\sym\\uhhircc3v2.1", "D:\\project\\uz0huzhn11\\dip\\sym\\uhlirccbv3.1"};
//  string loc_lst = "D:\\project\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";

	vector<string> in = vector<string> ();
  vector<string> out = vector<string> ();
  vector<string> bi = vector<string> ();

  vector<string> name = vector<string> ();
  vector<string> type = vector<string> ();  
  for(int i = 0; i < nums.size(); i++){
    Net_ip(loc_lst, nums[i], loc_ips[i], name, type);
    for(int j = 0; j < name.size(); j++){
      if(type[j] == "IN")
        in.push_back(name[j]);
      else if(type[j] == "OUT")
        out.push_back(name[j]);
      else
        bi.push_back(name[j]);
    }
    name.clear();
    type.clear();
  }
  for(int i = 0; i < in.size(); i++){
    if(in[i].find("{") != string::npos && in[i].find("}") != string::npos)
      Lst(in[i], "{", "{", "}");
  }
  for(int i = 0; i < out.size(); i++){
    if(out[i].find("{") != string::npos && out[i].find("}") != string::npos)
      Lst(out[i], "{", "{", "}");
  }
  for(int i = 0; i < bi.size(); i++){
    if(bi[i].find("{") != string::npos && bi[i].find("}") != string::npos)
      Lst(bi[i], "{", "{", "}");
  }

  Repeat_filter(in);
  Repeat_filter(out);
  Repeat_filter(bi);

  vector<string> in_c = vector<string> ();
  vector<string> out_c = vector<string> ();
  vector<string> bi_c = vector<string> ();

  Combine_net(in, in_c);
  Combine_net(out, out_c);
  Combine_net(bi, bi_c);

  in.clear();
  out.clear();
  bi.clear();

  int num_in = in_c.size();
  int num_out = out_c.size();
  int num_bi = bi_c.size();

  vector<int> three = {num_in, num_out, num_bi};
	sort(three.begin(), three.end());
  for(int i = 0; i < three[2]-num_in; i++)
    in_c.push_back("-");
  for(int i = 0; i < three[2]-num_out; i++)
    out_c.push_back("-");
  for(int i = 0; i < three[2]-num_bi; i++)
    bi_c.push_back("-");

  cout << left << setw(20) << "in" << setw(20) << "out" << setw(20) << "bi" << endl;
	cout << "--------------------------------------------------" << endl;
	for(int i = 0; i < three[2]; i++)
  	cout << left << setw(20) << in_c[i] << setw(20) << out_c[i] << setw(20) << bi_c[i] << endl;

  in_c.clear();
  out_c.clear();
  bi_c.clear();  
  three.clear();

//  return 0;
}

