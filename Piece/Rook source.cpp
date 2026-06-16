#include"Rook.h"
#include"../Board/Board.h"
#include<algorithm>
Rook::Rook(pos position, char c) :Chess(position, true, c, "rook") {};
Chess* Rook::clone()const { return new Rook(*this); }
bool Rook::is_legal(pos pos1, pos pos2, const Board& board)const {
	if(pos2.x<0||pos2.x>8||pos2.y<0||pos2.y>9){
		return false;
	}
	char side1 = board.get_chess(pos1)->getside();
	if (board.is_exist(pos2)) {
	char side2 = board.get_chess(pos2)->getside();
	if(side1==side2){//防止吃己方棋子
		return false;
	}
	
	}//车的路线上的阻挡判断
		if (pos1.x == pos2.x && pos1.y != pos2.y) {
			for (int i = std::min(pos1.y, pos2.y) + 1; i < max(pos1.y, pos2.y); ++i)
			{
				if (board.is_exist({ pos1.x,i })) {
					return false;
				}
			}
			return true;
		}
		else if (pos1.x != pos2.x && pos1.y == pos2.y) {
			for (int i = std::min(pos1.x, pos2.x) + 1; i < max(pos1.x, pos2.x); ++i)
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
