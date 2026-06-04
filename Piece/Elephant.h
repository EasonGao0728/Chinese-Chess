#pragma once
#ifndef ELEPHANT_H
#define ELEPHANT_H
#include"Chess.h"
#include"../Board/Board.h"
class Elephant :public Chess {
public:
	Elephant(pos, char);
	bool is_legal(pos, pos, const Board&)const;
};
#endif
