#pragma once
#include<iostream>
#include"chess.h"
using namespace std;

class King :public Chess {
public:
	King(pos position,char c);
	bool is_legal(pos, pos, const Board&)const;
private:
};
