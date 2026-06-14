#pragma once
#ifndef BOARD_H
#define BOARD_H
#include"../Piece/Chess.h"
class Board {
public:
    Board();
    bool is_inside(pos)const;
    bool is_exist(pos)const;
    Chess get_chess(pos)const;
    bool move_chess(pos, pos);
    pos find_king(char)const;
private:
    Chess pieces[32];
};
#endif