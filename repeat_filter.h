#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void Repeat_filter(vector<string>& test){
  vector<string>::iterator it, it1;  
  for(it =++ test.begin(); it != test.end();){
    it1 = find(test.begin(), it, *it);
    if(it1 != it)
      it = test.erase(it);
		else
      it++;	
  }
  vector<string> test_out = vector<string> ();
  for(it = test.begin(); it < test.end(); it++)
    test_out.push_back(*it);
  test.clear();
  for(int i = 0; i < test_out.size(); i++)
    test.push_back(test_out[i]);
}
