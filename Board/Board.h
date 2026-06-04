#pragma once
#ifndef BOARD_H
#define BOARD_H
#include"Chess.h"
class Board {
public:
    Board();
    bool is_exist(pos)const;
    Chess get_chess(pos)const;
private:
    Chess pieces[32];
};
#endif