#include"Rook.h"
#include"Board.h"
#include<algorithm>
Rook::Rook(pos position, char c) :Chess(position, true, c, "rook") {};
bool Rook::is_legal(pos pos1, pos pos2, const Board& board)const {
	if(pos2.x<0||pos2.x>8||pos2.y<0||pos2.y>9){
		return false;
	}
	char side1 = board.get_chess(pos1)->getside();
	if (board.is_exist(pos2)) {
	char side2 = board.get_chess(pos2)->getside();
	if(side1==side2){
		return false;
	}
	
	}
		if (pos1.x == pos2.x && pos1.y != pos2.y) {
			for (int i = std::min(pos1.y, pos2.y);i < max(pos1.y, pos2.y);++i)
			{
				if (board.is_exist({ pos1.x,i })) {
					return false;
				}
			}
			return true;
		}
		else if (pos1.x != pos2.x && pos1.y == pos2.y) {
			for (int i = std::min(pos1.x, pos2.x);i < max(pos1.x, pos2.x);++i)
			{
				if (board.is_exist({ i,pos1.y })) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}