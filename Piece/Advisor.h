#pragma once
#ifndef ADVISOR_H
#define ADVISOR_H
#include"Chess.h"
#include"../Board/Board.h"
class Advisor :public Chess {
public:
	Advisor(pos, char);
	bool is_legal(pos, pos, const Board&)const;
	Chess* clone()const override;
};
#endif