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