#pragma once
#ifndef ROOK_H
#define ROOK_H
#include"Chess.h"
class Rook :public Chess {
public:
	Rook(pos, char);
	bool is_legal(pos, pos, const Board&)const;
};
#endif