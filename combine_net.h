#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iomanip>
//#include "/home/terry/tmp_0316/c/lib/re_lib.h"
//#include "/home/terry/tmp_0316/c/lib/tmp_lib.h"
#include "repeat_filter.h"
#include "isnum.h"
using namespace std;


void Print(vector<int> num, string up, string down, vector<string>& pr){
    sort(num.begin(), num.end());
    vector<int> group = vector<int> ();
    int i_num = 0;
    group.push_back(i_num);
    for(int i = 0; i < num.size()-1; i++){
      if(num[i+1]-num[i] != 1)
        i_num++;
      group.push_back(i_num);
    }
//    vector<string> pr = vector<string> ();
    while(i_num != -1){
      vector<int> tmp_group = vector<int> ();
      for(int i = 0; i < num.size(); i++){
        if(group[i] == i_num)
          tmp_group.push_back(num[i]);
      }
      int myMax, myMin;
      sort(tmp_group.begin(), tmp_group.end());
      myMin = tmp_group[0];
      myMax = tmp_group[tmp_group.size()-1];
      if(myMax == myMin)
        pr.push_back(up+int2str(myMax)+down);
      else
        pr.push_back(up+"["+int2str(myMax)+":"+int2str(myMin)+"]"+down);
      tmp_group.clear();
      i_num--;
    }
    
//    for(int i = 0; i < print.size(); i++)
//      cout << print[i] << endl;
    group.clear();
//    print.clear();
}


void Combine_net(vector<string> net, vector<string>& shrink_net){
//  net.clear();
//	net = {"PA7PG_[3:0]", "PA6PG_[3:0]", "PA5PG_[3:0]", "PA3PG_[3:0]", "PA2_NG", "PA3_NG", "pa"};
  Repeat_filter(net); 
  vector<string> up = vector<string> ();
  vector<string> down = vector<string> ();
  string tmp_up, tmp_down, tmp_middle;
  int chk = 1;
  for(int i = 0; i < net.size(); i++){
    for(int j = 0; j < net.size(); j++){
      if(i != j){
        if(net[i].size() == net[j].size()){
          int i_str = 1;
          while(net[i].compare(0, i_str, net[j], 0, i_str) == 0)
            i_str++;  
          int left = i_str;
          i_str = 1;
          while(net[i].compare(net[i].size()-i_str, i_str, net[j], net[j].size()-i_str, i_str) == 0)
            i_str++;  
          int right = i_str;
          tmp_middle = tmp_middle.assign(net[i], left-1, net[i].size()-left-right+2);
//          	cout << tmp_middle+"  "+net[i]+"  "<< left << "  " << right << "  " << net[i].size()  << endl;
          if(left+right-1 == net[i].size() && Isnum(tmp_middle) == true){
            tmp_up = tmp_up.assign(net[i], 0, left-1);
            tmp_down = tmp_down.assign(net[i], left, right-1);
            up.push_back(tmp_up);
            down.push_back(tmp_down);
          }
        }
      }
    }
  }
/*  
  for(int i = 0; i < up.size(); i++){
    for(int j = 0; j < down.size(); j++){
      if(i != j && up[i]+down[i] == up[j]+down[j]){    
        up[j] = "x";
        down[j] = "x";
      }
    }
  }
*/

	if(!up.empty()){
	vector<string> ud = vector<string> ();
  for(int i = 0; i < up.size(); i++)
    ud.push_back(up[i]+down[i]);
	Repeat_filter(ud);

 
  vector<string> pat_up = vector<string> ();
  vector<string> pat_down = vector<string> ();

  for(int i = 0; i < ud.size(); i++){
    for(int j = 0; j < up.size(); j++){
      if(ud[i] == up[j]+down[j]){
        pat_up.push_back(up[j]);
        pat_down.push_back(down[j]);
				break;
      }
    }
  }
  up.clear();
  down.clear();

//  for(int i = 0; i < pat_up.size(); i++)
//    cout << pat_up[i] << "   " << pat_down[i] << endl;

  vector<string> up_pr = vector<string> ();
  vector<string> down_pr = vector<string> ();
  vector<int> num = vector<int> ();
  vector<int> type = vector<int> ();
  string tmp_num;
  int ty = 0;
  for(int j = 0; j < pat_up.size(); j++){
      for(int i = 0; i < net.size(); i++){
        if(net[i].find(pat_up[j]) == 0 && net[i].find(pat_down[j]) != string::npos){
          tmp_middle = tmp_middle.assign(net[i], pat_up[j].size(), net[i].size()-pat_up[j].size()-pat_down[j].size());
//          cout << tmp_middle << endl;
          if(Isnum(tmp_middle) == true){
            type.push_back(ty);
//            tmp_num = tmp_num.assign(net[i], pat_up[j].size(), 1);
            num.push_back(str2int(tmp_middle));
            up_pr.push_back(pat_up[j]);
            down_pr.push_back(pat_down[j]);
          }
        }
      }
      ty++;
  }

	
	bool flag = false;
  for(int i = 0; i < net.size(); i++){
		flag = true;
    for(int j = 0; j < pat_up.size(); j++){
        if(net[i].find(pat_up[j]) != string::npos && net[i].find(pat_down[j]) != string::npos){
					flag = false;	
					break;
				}
	  }
		if(flag == true){
			shrink_net.push_back(net[i]);
//			cout << net[i] << endl;
		}
  }
//  system("pause");	
//  Repeat_filter(shrink_net);
	if(!up_pr.empty()){
	  vector<int>::iterator myMax = max_element(type.begin(), type.end());
	  int cnt = 0;
	  while(cnt <= *myMax){ 
	    vector<int> tmp = vector<int> ();
	    vector<string> tmp_print = vector<string> ();
	    for(int i = 0 ; i < num.size(); i++){
  	    if(type[i] == cnt){
    	    tmp.push_back(num[i]);
      	  tmp_up = up_pr[i];
       	 tmp_down = down_pr[i];
      	}
    	}
    	Print(tmp, tmp_up, tmp_down, tmp_print);
    	for(int k = 0; k < tmp_print.size(); k++)
      	shrink_net.push_back(tmp_print[k]);
    	tmp_print.clear();
    	tmp.clear();
    	cnt++;
  	}
	}
  pat_up.clear();
  pat_down.clear();  
  up_pr.clear();
  down_pr.clear();
  num.clear();
  type.clear(); 
	}
	else{
		for(int i = 0; i < net.size(); i++)
			shrink_net.push_back(net[i]);
	
	}
//  net.clear(); 
//  return 0;
}
