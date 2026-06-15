#include"Pawn.h"
#include"../Board/Board.h"
#include<algorithm>
Pawn::Pawn(pos position, char c) :Chess(position, true, c, "pawn") {};
Chess* Pawn::clone()const { return new Pawn(*this); }
bool Pawn::is_legal(pos pos1, pos pos2, const Board& board)const {
	if (pos2.x < 0 || pos2.x>8 || pos2.y < 0 || pos2.y>9) {
		return false;
	}
	char side1 = board.get_chess(pos1)->getside();
	if(board.is_exist(pos2)){
		char side2 = board.get_chess(pos2)->getside();
		if(side1==side2){
			return false;
		}
	}
	if (side1 == 'r') {
		if (pos1.y >= 4) {
			if (pos2.x == pos1.x && pos2.y == pos1.y + 1) {
				return true;
			}
			else if (pos2.y == pos1.y && abs(pos2.x - pos1.x) == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (pos2.x == pos1.x && pos2.y == pos1.y + 1) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		if (pos1.y <4) {
			if (pos2.x == pos1.x && pos2.y == pos1.y + 1) {
				return true;
			}
			else if (pos2.y == pos1.y && abs(pos2.x - pos1.x) == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (pos2.x == pos1.x && pos2.y == pos1.y + 1) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}
