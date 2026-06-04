#pragma once
#ifndef PAWN_H
#define PAWN_H
#include"Chess.h"
#include"../Board/Board.h"
class Pawn :public Chess {
public:
	Pawn(pos, char);
	bool is_legal(pos, pos, const Board&)const;
};

#endif