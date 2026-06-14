#pragma once

#include <iostream>
#include "../Piece/Chess.h"
#include"../Board/Board.h"
class Move
{
public:
  Move(pos start_pos, pos end_pos,const Board& chessBoard,int step);
  pos get_start() const;
  pos get_end() const;
  const Chess* get_acting_chess() const;
  const Chess* get_eaten_chess() const;
  char get_side() const;
  bool get_check_eat() const;
  bool get_check_king() const;
  int get_step() const;
  void print_move() const;
private:
  pos start;
  pos end;
  Chess eaten_piece;
  Chess acting_piece;
  char side;
  bool check_eat;
  bool check_king;
  int step_count;
};