#include<iostream>
#include"chess.h"
using namespace std;

class King:public Chess {
public:
King(pos position,bool a,char c,string str);
bool is_legal(pos, pos,const Board&)const;
private:
};
