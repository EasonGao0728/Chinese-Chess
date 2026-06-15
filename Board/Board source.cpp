#include "Board.h"
#include"Rook.h"
#include"Cannon.h"
#include"Pawn.h"
#include"Elephant.h"
#include"Horse.h"
#include"Advisor.h"
#include"King.h"
#include<stdexcept>
Board::Board()
    : pieces{
        new Rook({0,0},'r'),
        new Rook({8,0}, 'r'),
        new Horse({1, 0},'r'),
        new Horse({7, 0}, 'r'),
        new Elephant({2, 0},'r'),
        new Elephant({6, 0}, 'r'),
        new Advisor({3, 0}, 'r'),
        new Advisor({5, 0}, 'r'),
        new King({4, 0}, 'r'),
        new Cannon({1, 2},  'r'),
        new Cannon({7, 2}, 'r'),
        new Pawn({0, 3}, 'r'),
        new Pawn({2, 3}, 'r'),
        new Pawn({4, 3}, 'r'),
        new Pawn({6, 3},  'r'),
        new Pawn({8, 3}, 'r'),
        new Rook({0, 9},  'b'),
        new Rook({8, 9}, 'b'),
       new  Horse({1, 9},'b'),
       new  Horse({7, 9}, 'b'),
        new Elephant({2, 9}, 'b'),
        new Elephant({6, 9},  'b'),
        new Advisor({3, 9}, 'b'),
        new Advisor({5, 9},'b'),
        new King({4, 9}, 'b'),
        new Cannon({1, 7}, 'b'),
        new Cannon({7, 7}, 'b'),
        new Pawn({0, 6}, 'b'),
        new Pawn({2, 6},  'b'),
        new Pawn({4, 6},  'b'),
        new Pawn({6, 6}, 'b'),
        new Pawn({8, 6}, 'b')
    }{}
Board::Board(const Board& other) {
    for (int i = 0; i < 32; ++i) {
        pieces[i] = other.pieces[i]->clone();
    }
}
Board::~Board() {
    for (int i = 0; i < 32; ++i) {
        delete pieces[i];
        pieces[i] = nullptr;
    }
}
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        for (int i = 0; i < 32; ++i) {
            delete pieces[i];
            pieces[i] = other.pieces[i]->clone();
        }
    }
    return *this;
}
bool Board::is_exist(pos position)const {
    for(int i=0;i<32;i++){
        if(pieces[i]->getalive()&&pieces[i]->getpos().x==position.x&&pieces[i]->getpos().y==position.y){
            return true;
        }
    }
    return false;
}
Chess* Board::get_chess(pos position) const {
    for (int i = 0; i < 32; i++) {
        if (pieces[i]->getalive() && pieces[i]->getpos().x == position.x && pieces[i]->getpos().y == position.y) {
            return pieces[i];
        }
    }
    return nullptr;
}
bool Board::move_chess(pos start, pos end) {
    if (!is_inside(start) || !is_inside(end) || (start.x == end.x && start.y == end.y)) {
        return false;
    }

    int moving_index = -1;
    int target_index = -1;
    for (int i = 0; i < 32; ++i) {
        if (!pieces[i]->getalive()) {
            continue;
        }

        if (pieces[i]->getpos().x == start.x && pieces[i]->getpos().y == start.y) {
            moving_index = i;
        }
        if (pieces[i]->getpos().x == end.x && pieces[i]->getpos().y == end.y) {
            target_index = i;
        }
    }

    if (moving_index == -1) {
        return false;
    }
    if (target_index != -1 && pieces[target_index]->getside() == pieces[moving_index]->getside()) {
        return false;
    }

    if (target_index != -1) {
        pieces[target_index]->setalive(false);
        pieces[target_index]->setpos({ -1, -1 });
    }

    pieces[moving_index]->setpos(end);
    return true;
}
pos Board::find_king(char side)const {
    for (int i = 0; i < 32; ++i) {
        if (pieces[i]->getalive() && pieces[i]->getside() == side &&
            (pieces[i]->gettype() == "King" || pieces[i]->gettype() == "king")) {
            return pieces[i]->getpos();
        }
    }
    return { -1, -1 };
}
bool Board::is_inside(pos position)const {
    return position.x >= 0 && position.x <= 8 && position.y >= 0 && position.y <= 9;
}
