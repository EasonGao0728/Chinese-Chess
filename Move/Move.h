#pragma once

#include <iostream>
#include "../Piece/Chess.h"
#include"../Board/Board.h"
class Move
{
public:
  Move(pos start_pos, pos end_pos,const Board& chessBoard,int step);
  pos get_start();
  pos get_end();
  Chess* get_acting_chess();
  Chess* get_eaten_chess();
  char get_side();
  bool get_check_eat();
  bool get_check_king();
  int get_step();
private:
  pos start;
  pos end;
  Chess* eaten_piece;
  Chess* acting_piece;
  char side;
  bool check_eat;
  bool check_king;
  int step_count;
  void print_move();
};