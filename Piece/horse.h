#pragma once
#ifndef HORSE_H
#define HORSE_H
#include"Chess.h"
#include"../Board/Board.h"
class Horse :public Chess {
public:
	Horse(pos, char);
	bool is_legal(pos, pos, const Board&)const;
	Chess* clone()const override;
};
#endif
