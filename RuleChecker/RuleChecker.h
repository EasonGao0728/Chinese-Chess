#pragma once

#include<iostream>
#include "../Piece/Chess.h"
#include"../Board/Board.h"

class RuleChecker
{
public:
	bool is_move_legal(const Board&, pos, pos, char current_side = '\0')const;
	bool is_in_check(const Board&, char)const;
	bool would_cause_self_check(const Board&, pos, pos)const;
	bool are_kings_facing(const Board&)const;
	bool has_any_legal_move(const Board&, char)const;
	bool is_checkmate(const Board&, char)const;
	bool is_stalemate(const Board&, char)const;

private:
	bool is_piece_move_legal(const Chess&, pos, pos, const Board&)const;
	bool can_piece_attack(const Chess&, pos, pos, const Board&)const;
	bool is_in_palace(char, pos)const;
	int count_pieces_between(const Board&, pos, pos)const;
};