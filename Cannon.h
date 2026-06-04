#pragma once
#ifndef CANNON_H
#define CANNON_H
#include"Chess.h"
#include"Board.h"
class Cannon :public Chess {
public:
	Cannon(pos, char);
	bool is_legal(pos, pos, const Board&)const;
};
#endif
