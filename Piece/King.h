#include<iostream>
#include"Chess.h"
using namespace std;

class King:public Chess {
public:
King(pos position,bool a=1,char c,string str="King");
bool is_legal(pos, pos,const Board&)const;
private:
};
