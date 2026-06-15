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
  string get_acting_type() const;
  char get_acting_side() const;
  string get_eaten_type() const;
  char get_eaten_side() const;
  char get_side() const;
  bool get_check_eat() const;
  bool get_check_king() const;
  int get_step() const;
  void print_move() const;
  std::string format_move() const;
private:
  pos start;
  pos end;
  string acting_type;
  char acting_side;
  string eaten_type;
  char eaten_side;
  char side;
  bool check_eat;
  bool check_king;
  int step_count;
};
