#include"Elephant.h"
#include<algorithm>
Elephant::Elephant(pos position, char c) :Chess(position, true, c, "elephant") {};
Chess* Elephant::clone()const { return new Elephant(*this); }
bool Elephant::is_legal(pos pos1, pos pos2, const Board& board)const {
	if (pos2.x < 0 || pos2.x > 8 || pos2.y < 0 || pos2.y > 9) {
		return false;
	}
	char side1 = board.get_chess(pos1)->getside();
	if(side1=='r'&&pos2.y>4){//象不能过河
		return false;
	}
	if(side1=='b'&&pos2.y<5){
		return false;
	}
	if (board.is_exist(pos2)) {
		char side2 = board.get_chess(pos2)->getside();
		if (side1 == side2) {
			return false;
		}
	}
	if(abs(pos1.x-pos2.x)==2&&abs(pos1.y-pos2.y)==2){//象眼阻挡判断
		if(board.is_exist({(pos1.x+pos2.x)/2,(pos1.y+pos2.y)/2})){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}
