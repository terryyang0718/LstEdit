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
//#include "D:\\c\\lib\\getdir_silent.h"

using namespace std;
class NodeComb{
  public:
    string num, name, pintype, pin, pinnet;
    int x0, y0, x1, y1, num_net;
    bool bus;
};

void Sym2sch(string loc_lst, string num, string loc_ip, int x_ip, int y_ip, int& num_net, string& all){
//  string loc_lst = "D:\\project\\uz0cuzhd14\\body\\lst\\sch_uz0cuzhd14.lst";
//  string num = "614";
//  string loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhcoreirv2.1";

//Reading sym_pla ... 
  vector<string> pla = vector<string> ();
  pla.clear();
  ifstream ipFile;
  ipFile.open(loc_ip);
  if(!ipFile)
    cout << "fail" << endl;
  else{
    string line, p, l, a;
    int step = 0;
    vector<string> part = vector<string> ();
    part.clear();
    do{
      getline(ipFile, line);
      if(step == 0){
        if(line.find("P") == 0){
          BlankParse(line, part);
          p = part[1]+"@";
          part.clear();
          step++;
        }
      }else{
//      else if(step == 1){
        if(line.find("L") == 0){
          BlankParse(line, part);
          l = part[part.size()-1]+"@";
          part.clear();
          step++;
        }
//      }
//      else{
        if(line.find("A") == 0){
          BlankParse(line, part);
          a = part[1]+"@"+part[2]+"@"+part[part.size()-1];
          part.clear();
          step++;    
        }
        if(step == 3){
          step = 0;
          pla.push_back(p+l+a);
          p.clear(); l.clear(); a.clear();
        }
//      }
      }
    }while(!ipFile.eof());
    ipFile.close();
  }




//Reading lst ...
  vector<string> detail = vector<string> ();
  detail.clear();
  string detail_all;
  ifstream lstFile;
  lstFile.open(loc_lst);
  if(!lstFile)
    cout << "fail" << endl;
  else{
    string line, tmp_detail;
    int j = 1;
    do{
      getline(lstFile, line);
      if(j == str2int(num)){
        tmp_detail = line;
        Lst(tmp_detail, "(", "(", ")");
        if(!tmp_detail.empty()){
//          Comma(tmp_detail, detail);
          Sprt(tmp_detail, ",[", detail);
          detail_all = line;
        }
      }
      j++;
    }while(!lstFile.eof());
    lstFile.close();
  }
//===========================================
  if(pla.empty()){
  all.clear();
  vector<int> grp_int = vector<int> ();
  grp_int.clear();

  string tmp_name_ip = detail_all;
  Lst(tmp_name_ip, ":", ":", "([");
  all = all+"I "+int2str(num_net)+" "+tmp_name_ip+" 1 "+int2str(x_ip)+" "+int2str(y_ip)+" 0 1 '"+"\n";
  num_net++;

  if(detail[0].find("[L]=") == 0){
//    vector<int> grp_y = {0, 0, 0};
//    grp_y.clear();
    string tmp_label = detail[0].substr(4, detail[0].length()-4);
//    cout << tmp_label << endl;
//    for(int i = 0; i < bagComb.size(); i++)
//      grp_y.push_back(bagComb[i].y0);
//    sort(grp_y.begin(), grp_y.end());
    grp_int = {x_ip+10, y_ip+50};
    all = all+"L "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 10 0 3 0 1 0 "+tmp_label+"\n";
    grp_int.clear();
//    grp_y.clear();
  }

  int num_a = 1;
  for(int i = 0; i < detail.size(); i++){
    if(detail[i].find("[A]=") == 0){
      string tmp_a = detail[i].substr(4, detail[i].length()-4);
//      cout << tmp_a << endl;
      grp_int = {x_ip+10, y_ip-10*num_a};
      all = all+"A "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 10 0 3 1 "+tmp_a+"\n";
      grp_int.clear();
      num_a++;
    }
  }

  }else{
//============================================
//combining lst & sym ...
  NodeComb candyComb;
  vector<NodeComb> bagComb = vector<NodeComb> ();
  bagComb.clear();
  vector<string> grp_pla = vector<string> ();
  grp_pla.clear();

  for(int i = 0; i < pla.size(); i++){
//    Comma(pla[i], grp_pla);
    Sprt(pla[i], "@", grp_pla);
    candyComb.num = grp_pla[0];
    candyComb.name = grp_pla[1];
    candyComb.pin = grp_pla[1];
    candyComb.x0 = str2int(grp_pla[2]);
    candyComb.y0 = str2int(grp_pla[3]);
    if(grp_pla[2] == "0")
      candyComb.x1 = -160;
    else
      candyComb.x1 = str2int(grp_pla[2])+160;
    candyComb.y1 = str2int(grp_pla[3]);
    candyComb.pintype = grp_pla[4];
    bagComb.push_back(candyComb);
    grp_pla.clear();
  }
  

  string tmp_pin, tmp_pinnet;
  for(int j = 0; j < detail.size(); j++){
    for(int i = 0; i < bagComb.size(); i++){
      if(detail[j].find("[A]=$PIN_"+bagComb[i].name+"=") == 0){
        tmp_pin = detail[j].substr(10+bagComb[i].name.length(), detail[j].length()-bagComb[i].name.length()-10);
        bagComb[i].pin = tmp_pin;
        break;
      }
      else if(detail[j].find("[A]=$PINNET_"+bagComb[i].name+"=") == 0){
        tmp_pinnet = detail[j].substr(13+bagComb[i].name.length(), detail[j].length()-bagComb[i].name.length()-13);
        bagComb[i].pinnet = tmp_pinnet;
        break;
      }
      else
        continue;
    }
  }

  for(int i = 0; i < bagComb.size(); i++){
    if(!bagComb[i].pin.empty()){
      if(bagComb[i].pin.find("[") != string::npos && bagComb[i].pin.find("]") != string::npos && bagComb[i].pin.find(":") != string::npos)
        bagComb[i].bus = true;
      else
        bagComb[i].bus = false;
    }
  }

//Inserting ip ...
//  int x_ip = 950, y_ip = 860;    
//  int num_ip = 100, num_net;
//  num_net = 1000;
//  string all = "";
  all.clear();
  vector<int> grp_int = vector<int> ();
  grp_int.clear();

  string tmp_name_ip = detail_all;
  Lst(tmp_name_ip, ":", ":", "([");
  all = all+"I "+int2str(num_net)+" "+tmp_name_ip+" 1 "+int2str(x_ip)+" "+int2str(y_ip)+" 0 1 '"+"\n";
  num_net++;

  if(detail[0].find("[L]=") == 0){
    vector<int> grp_y = vector<int> ();
    grp_y.clear();
    string tmp_label = detail[0].substr(4, detail[0].length()-4);
//    cout << tmp_label << endl;
    for(int i = 0; i < bagComb.size(); i++)
      grp_y.push_back(bagComb[i].y0);
    sort(grp_y.begin(), grp_y.end());
    grp_int = {x_ip+10, y_ip+40+grp_y[grp_y.size()-1]};
    all = all+"L "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 10 0 3 0 1 0 "+tmp_label+"\n";
    grp_int.clear();
    grp_y.clear();
  }

  int num_a = 1;
  for(int i = 0; i < detail.size(); i++){
    if(detail[i].find("[A]=") == 0){
      string tmp_a = detail[i].substr(4, detail[i].length()-4);
//      cout << tmp_a << endl;
      grp_int = {x_ip+10, y_ip-10*num_a};
      all = all+"A "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 10 0 3 1 "+tmp_a+"\n";
      grp_int.clear();
      num_a++;
    }
  }





  for(int i = 0; i < bagComb.size(); i++){
    all = all+"C "+int2str(num_net)+" 1 "+bagComb[i].num+" 0"+"\n";
    bagComb[i].num_net = num_net;
    num_net++;
  }

  for(int i = 0; i < bagComb.size(); i++){
    all = all+"N "+int2str(bagComb[i].num_net)+"\n";
    if(bagComb[i].bus == true){
      if(!bagComb[i].pinnet.empty()){
        grp_int = {bagComb[i].x0+x_ip, bagComb[i].y0+y_ip, bagComb[i].x1+x_ip, bagComb[i].y1+y_ip};
        all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 8"+"\n";
        all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 8"+"\n";
        all = all+"B 2 1"+"\n";
        grp_int.clear();
      }
      else{
        grp_int = {bagComb[i].x0+x_ip, bagComb[i].y0+y_ip, bagComb[i].x1+x_ip, bagComb[i].y1+y_ip};
        all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 8"+"\n";
        all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 7"+"\n";
        all = all+"B 2 1"+"\n";
        grp_int.clear();
      }
    }
    else{
      if(!bagComb[i].pinnet.empty()){
        grp_int = {bagComb[i].x0+x_ip, bagComb[i].y0+y_ip, bagComb[i].x1+x_ip, bagComb[i].y1+y_ip};
        all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 2"+"\n";
        all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 2"+"\n";
        all = all+"S 2 1"+"\n";
        grp_int.clear();
      }
      else{
        grp_int = {bagComb[i].x0+x_ip, bagComb[i].y0+y_ip, bagComb[i].x1+x_ip, bagComb[i].y1+y_ip};
        all = all+"J "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 2"+"\n";
        all = all+"J "+int2str(grp_int[2])+" "+int2str(grp_int[3])+" 1"+"\n";
        all = all+"S 2 1"+"\n";
        grp_int.clear();
      }
    }
    if(bagComb[i].x0 == 0){
      grp_int = {bagComb[i].x0+x_ip-150, bagComb[i].y0+y_ip};
      all = all+"L "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 10 0 3 0 1 0 "+bagComb[i].pin+"\n";
      grp_int.clear();
    }
    else{
      grp_int = {bagComb[i].x0+x_ip+10, bagComb[i].y0+y_ip};
      all = all+"L "+int2str(grp_int[0])+" "+int2str(grp_int[1])+" 10 0 3 0 1 0 "+bagComb[i].pin+"\n";
      grp_int.clear();
    }
    if(!bagComb[i].pinnet.empty()){
      if(bagComb[i].x0 == 0){
        grp_int = {num_net, bagComb[i].x1+x_ip-30, bagComb[i].y1+y_ip};
        all = all+"I "+int2str(grp_int[0])+" builtin:"+bagComb[i].pinnet+" 1 "+int2str(grp_int[1])+" "+int2str(grp_int[2])+" 0 1 '"+"\n";
        grp_int.clear();
      }
      else{
        grp_int = {num_net, bagComb[i].x1+x_ip, bagComb[i].y1+y_ip};
        all = all+"I "+int2str(grp_int[0])+" builtin:"+bagComb[i].pinnet+" 1 "+int2str(grp_int[1])+" "+int2str(grp_int[2])+" 0 1 '"+"\n";
        grp_int.clear();
      }
      num_net++;
      all = all+"C "+int2str(bagComb[i].num_net)+" 2 1 0"+"\n";
    }
  }
  }
}
/*
int main(){
  string loc_lst = "D:\\project\\uz0cuzhd14\\body\\lst\\sch_uz0cuzhd14.lst";
  int num_net = 100;
  vector<string> all = {"", "", "", "", "", "", "", "", ""};

  string num = "614";
  string loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhcoreirv2.1";  
  int x_ip = 950, y_ip = 860;    
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[0]);

  num = "615";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhtimetg.1";  
  x_ip = 950;
  y_ip = 540;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[1]);

  num = "616";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhroml64.1";  
  x_ip = 950;
  y_ip = 240;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[2]);

  num = "617";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhmduwv1.1";  
  x_ip = 280;
  y_ip = 1280;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[3]);

  num = "618";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhrg17fh.1";  
  x_ip = 280;
  y_ip = 620;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[4]);

  num = "620";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhra128m24.1";  
  x_ip = 280;
  y_ip = 420;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[5]);

  num = "621";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhhircc3v1.1";  
  x_ip = 1620;
  y_ip = 1260;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[6]);

  num = "622";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhhxtcv1.1";  
  x_ip = 1620;
  y_ip = 770;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[7]);

  num = "623";
  loc_ip = "D:\\project\\uz0cuzhd14\\dip\\sym\\uhlxtcbv1.1";  
  x_ip = 1620;
  y_ip = 330;
  Sym2sch(loc_lst, num, loc_ip, x_ip, y_ip, num_net, all[8]);

  ofstream tmpFile;
  tmpFile.open("sch.1");
  for(int i = 0; i < all.size(); i++)
    tmpFile << all[i] << endl;

  
  



  return 0;
}
*/
