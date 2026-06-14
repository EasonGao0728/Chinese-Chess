#pragma once
#ifndef BOARD_H
#define BOARD_H
#include"Chess.h"
class Board {
public:
	Board();
	bool is_exist(pos)const;
	Chess* get_chess(pos)const;
	bool move_chess(pos start, pos end);
	pos find_king(char side)const;
	bool is_inside(pos position)const;
private:
	Chess*pieces[32];
};
#endif