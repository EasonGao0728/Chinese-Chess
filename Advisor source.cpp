#include"Advisor.h"
#include<algorithm>
Advisor::Advisor(pos position, char c) :Chess(position, true, c, "advisor") {};
bool Advisor::is_legal(pos pos1, pos pos2, const Board& board)const {
	char side1 = board.get_chess(pos1).getside();
	if(side1=='r'&&(pos2.x<3||pos2.x>5||pos2.y>2||pos2.y<0)){
		return false;
	}
	if (side1 == 'b' && (pos2.x < 3 || pos2.x>5 || pos2.y < 7 || pos2.y>9)) {
		return false;
	}
	if(board.is_exist(pos2)){
		char side2 = board.get_chess(pos2).getside();
		if (side1 == side2) {
			return false;
		}
	}
	if (abs(pos1.x - pos2.x) == 1 && abs(pos1.y - pos2.y) == 1) {
		return true;
	}
	else {
		return false;
	}
}