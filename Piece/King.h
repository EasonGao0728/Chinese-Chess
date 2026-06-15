#pragma once

#include<iostream>
#include"Chess.h"
#include"../Board/Board.h"
using namespace std;

class King:public Chess {
public:
	King(pos position,char c='r',bool a=true,string str="King");
	bool is_legal(pos, pos,const Board&)const;
	Chess* clone()const override;
private:
};
