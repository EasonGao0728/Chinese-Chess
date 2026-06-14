#include "Board.h"
#include "../Piece/Rook.h"
#include "../Piece/Cannon.h"
#include "../Piece/Pawn.h"
#include "../Piece/Elephant.h"
#include "../Piece/horse.h"
#include "../Piece/King.h"
#include "../Piece/Advisor.h"

Board::Board()
    : pieces{
        Rook({0,0},'r'),
        Rook({8,0}, 'r'),
        Horse({1, 0},'r'),
        Horse({7, 0}, 'r'),
        Elephant({2, 0},'r'),
        Elephant({6, 0}, 'r'),
        Advisor({3, 0}, 'r'),
        Advisor({5, 0}, 'r'),
        King({4, 0}, 'r'),
        Cannon({1, 2},  'r'),
        Cannon({7, 2}, 'r'),
        Pawn({0, 3}, 'r'),
        Pawn({2, 3}, 'r'),
        Pawn({4, 3}, 'r'),
        Pawn({6, 3},  'r'),
        Pawn({8, 3}, 'r'),
        Rook({0, 9},  'b'),
        Rook({8, 9}, 'b'),
        Horse({1, 9},'b'),
        Horse({7, 9}, 'b'),
        Elephant({2, 9}, 'b'),
        Elephant({6, 9},  'b'),
        Advisor({3, 9}, 'b'),
        Advisor({5, 9},'b'),
        King({4, 9}, 'b'),
        Cannon({1, 7}, 'b'),
        Cannon({7, 7}, 'b'),
        Pawn({0, 6}, 'b'),
        Pawn({2, 6},  'b'),
        Pawn({4, 6},  'b'),
        Pawn({6, 6}, 'b'),
        Pawn({8, 6}, 'b')
    }{}
bool Board::is_inside(pos position)const {
    return position.x >= 0 && position.x <= 8 && position.y >= 0 && position.y <= 9;
}
bool Board::is_exist(pos position)const {
    for(int i=0;i<32;i++){
        if(pieces[i].getalive()&&pieces[i].getpos().x==position.x&&pieces[i].getpos().y==position.y){
            return true;
        }
    }
    return false;
}
Chess Board::get_chess(pos position)const {
    for (int i = 0;i < 32;i++) {
        if (pieces[i].getalive() && pieces[i].getpos().x == position.x && pieces[i].getpos().y == position.y) {
            return pieces[i];
        }
    }
    return Chess({0,0},false,'x',"null");
}
bool Board::move_chess(pos start, pos end) {
    if (!is_inside(start) || !is_inside(end) || (start.x == end.x && start.y == end.y)) {
        return false;
    }

    int moving_index = -1;
    int target_index = -1;
    for (int i = 0; i < 32; ++i) {
        if (!pieces[i].getalive()) {
            continue;
        }

        if (pieces[i].getpos().x == start.x && pieces[i].getpos().y == start.y) {
            moving_index = i;
        }
        if (pieces[i].getpos().x == end.x && pieces[i].getpos().y == end.y) {
            target_index = i;
        }
    }

    if (moving_index == -1) {
        return false;
    }
    if (target_index != -1 && pieces[target_index].getside() == pieces[moving_index].getside()) {
        return false;
    }

    if (target_index != -1) {
        pieces[target_index].setalive(false);
        pieces[target_index].setpos({-1, -1});
    }

    pieces[moving_index].setpos(end);
    return true;
}
pos Board::find_king(char side)const {
    for (int i = 0; i < 32; ++i) {
        if (pieces[i].getalive() && pieces[i].getside() == side &&
            (pieces[i].gettype() == "King" || pieces[i].gettype() == "king")) {
            return pieces[i].getpos();
        }
    }
    return {-1, -1};
}