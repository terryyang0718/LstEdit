#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iomanip>
//#include "D:\\c\\lib\\re_lib.h"
//#include "D:\\c\\lib\\tmp_lib.h"
//#include "D:\\tmp_0222\\c\\lib\\remake_0.2.h"

using namespace std;

class node8{
	public:
    string builtin;
    string label;
    string i_N;
    string sch;
};

class node9{
  public:
    int num_p;
    int x_L;
    int x_A;
    int y_L;
    string l;
    string a;
};

void Sch2sym(string loc_lst, string sch){
//  string loc_lst = "D:\\project\\uz0huzhn11\\body\\lst\\sch_uz0huzhn11.lst";
//  string sch = "IOBLK";
  size_t pos_body = loc_lst.find("body");
  string dir_sch;
  dir_sch.assign(loc_lst, 0, pos_body);
  dir_sch.append("sch");
  vector<string> files_sch = vector<string>();
  getdir(dir_sch, files_sch);
  
  bool f;
  int page = 1;
  string sch_1;
  vector<string> loc_sch = vector<string>();
  do{
    sch_1 = sch+"."+int2str(page);
    f = false;
    for(int i = 0; i < files_sch.size(); i++)
      if(sch_1 == files_sch[i]){
        f = true;
        loc_sch.push_back(files_sch[i]);
      }
    page++;
  }while(f == true);
  files_sch.clear();

  node8 candy_sch;
  vector<node8> bag_sch;
  bag_sch.clear();
  fstream f_sch;
  string line, tmp_builtin, tmp_c;
  bool ic;
  int num_I = 0;
  for(int i = 0; i < loc_sch.size(); i++){
    f_sch.open(dir_sch+"\\"+loc_sch[i], ios::in);
//    cout << loc_sch[i] << endl;
    if(!f_sch)
      cout << "fail" << endl;
    else{
      int num = 1;
      ic = false;

      do{
        getline(f_sch, line);
        tmp_builtin = line;
        tmp_c = line;
        if(ic == false){
          Lst(tmp_builtin, "builtin:", " builtin:", " 1");
          if(!tmp_builtin.empty()){
            candy_sch.builtin = tmp_builtin;
            candy_sch.sch = dir_sch+"\\"+loc_sch[i];
            bag_sch.push_back(candy_sch);
            ic = true;
            num_I++;
          }
        }
        else{
          Lst(tmp_c, "C ", "C ", " ");
          if(!tmp_c.empty()){
            bag_sch[num_I-1].i_N = tmp_c;
            ic = false;
          }
        }
        num++;
      }while(!f_sch.eof());      
      f_sch.close();
    }
  }


  bool nl = false;
  string tmp_label;
  for(int i = 0; i < bag_sch.size(); i++){
    f_sch.open(bag_sch[i].sch, ios::in);
    if(!f_sch)
      cout << "fail" << endl;
    else{
      do{
        getline(f_sch, line);
        tmp_label = line;

        if(nl == false){
          if(size_t found = line.find("N "+bag_sch[i].i_N) != string::npos)
            nl = true;  
        }
        else{
          Lst_end(tmp_label, "L ", " 10 0 3 0 1 0 ");
          if(!tmp_label.empty()){
            bag_sch[i].label = tmp_label;
            nl = false;
          }
        
        }
      }while(!f_sch.eof());
      f_sch.close();
    }
  }

  vector<string> in = vector<string> ();
  vector<string> out = vector<string> ();
  vector<string> bi = vector<string> ();

  for(int i = 0; i < bag_sch.size(); i++){
    if(bag_sch[i].builtin == "IN")
      in.push_back(bag_sch[i].label);
    else if(bag_sch[i].builtin == "OUT")
      out.push_back(bag_sch[i].label);
    else
      bi.push_back(bag_sch[i].label);
  }
  bag_sch.clear();

  int ii = 20+in.size()+out.size()+bi.size();
  int max;
  if(in.size()>(out.size()+bi.size()))
    max = 30+20*(in.size()-1);
  else
    max = 30+20*((out.size()+bi.size())-1);
  node9 candy_pla;
  vector<node9> bag_pla;
  bag_pla.clear();

  int yy = 30;
  for(int i = 0; i < in.size(); i++){
    candy_pla.num_p = ii;
    ii--;
    candy_pla.x_L = 10;
    candy_pla.x_A = 0;
    candy_pla.y_L = yy;
    yy += 20;
    candy_pla.l = " 10 0 2 0 1 0 "+in[i];
    candy_pla.a = " 10 0 8 0 PINTYPE=IN";
    bag_pla.push_back(candy_pla);
  }

  yy = 30;
  for(int i = 0; i < out.size(); i++){
    candy_pla.num_p = ii;
    ii--;
    candy_pla.x_L = 250;
    candy_pla.x_A = 260;
    candy_pla.y_L = yy;
    yy += 20;
    candy_pla.l = " 10 0 8 0 1 0 "+out[i];
    candy_pla.a = " 10 0 8 0 PINTYPE=OUT";
    bag_pla.push_back(candy_pla);
  }

  yy = max;
  for(int i = 0; i < bi.size(); i++){
    candy_pla.num_p = ii;
    ii--;
    candy_pla.x_L = 250;
    candy_pla.x_A = 260;
    candy_pla.y_L = yy;
    yy -= 20;
    candy_pla.l = " 10 0 8 0 1 0 "+bi[i];
    candy_pla.a = " 10 0 8 0 PINTYPE=BI";
    bag_pla.push_back(candy_pla);
  }
  in.clear();
  out.clear();
  bi.clear();


  string dir_sym;
  dir_sym.assign(loc_lst, 0, pos_body);
  dir_sym.append("sym\\"+sch+".1");
  fstream f_sym;
  f_sym.open(dir_sym, ios::out);
  if(!f_sym)
    cout << "fail" << endl;
  else{
    int tmp_max = max+50;
    int tmp_max1 = max+40;
    int tmp_ii = 20+bag_pla.size();
    f_sym << "V 51\nK 417803538100 "+sch+"\nY 0\nD 0 0 260 "+int2str(tmp_max)+"\nZ 10\ni "+int2str(tmp_ii)+"\nU 130 "+int2str(tmp_max1)+" 20 0 4 3 @Name="+sch << endl;
    for(int i = 0; i < bag_pla.size(); i++){
      f_sym << "P "+int2str(bag_pla[i].num_p)+" "+int2str(bag_pla[i].x_A)+" "+int2str(bag_pla[i].y_L)+" "+int2str(bag_pla[i].x_L)+" "+int2str(bag_pla[i].y_L)+" 0 2 0" << endl;
      f_sym << "L "+int2str(bag_pla[i].x_L)+" "+int2str(bag_pla[i].y_L)+bag_pla[i].l << endl;
      f_sym << "A "+int2str(bag_pla[i].x_A)+" "+int2str(bag_pla[i].y_L)+bag_pla[i].a << endl;
    }
    f_sym << "T 10 0 10 0 3 USED_OK=0\nQ 12 0 0\nb 10 10 250 "+int2str(tmp_max1)+"\nE" << endl; 

  }
  bag_pla.clear();

//  return 0;
}
