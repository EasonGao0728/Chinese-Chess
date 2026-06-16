#include "RuleChecker.h"

#include <cstdlib>
#include <string>

using namespace std;

bool RuleChecker::is_move_legal(const Board& board, pos start, pos end, char current_side)const
{//全局意义上的move合法性判断，不涉及到具体棋子走法的实现
	if (!board.is_inside(start) || !board.is_inside(end)) {//终点在棋盘内
		return false;
	}
	if (start.x == end.x && start.y == end.y) {//起终点不能重合
		return false;
	}
	if (!board.is_exist(start)) {//起点非空
		return false;
	}

	Chess* moving_piece = board.get_chess(start);
	if (current_side != '\0' && moving_piece->getside() != current_side) {//起点棋子要是己方
		return false;
	}
	if (!is_piece_move_legal(moving_piece, start, end, board)) {
		return false;
	}

	Board next_board = board;
	if (!next_board.move_chess(start, end)) {
		return false;
	}
	if (are_kings_facing(next_board)) {//模拟走一次后，判断是否照将
		return false;
	}
	if (is_in_check(next_board, moving_piece->getside())) {//模拟走一次后，判断是否被将军
		return false;
	}
	return true;
}

bool RuleChecker::is_in_check(const Board& board, char side)const
{//被将军判断
	pos king_pos = board.find_king(side);
	if (!board.is_inside(king_pos)) {
		return false;
	}

	for (int y = 0; y <= 9; ++y) {
		for (int x = 0; x <= 8; ++x) {
			pos current(x, y);
			if (!board.is_exist(current)) {
				continue;
			}

			Chess* piece = board.get_chess(current);
			if (piece->getside() == side) {
				continue;
			}
			if (can_piece_attack(piece, current, king_pos, board)) {
				return true;
			}
		}
	}
	return false;
}

bool RuleChecker::would_cause_self_check(const Board& board, pos start, pos end)const
{
	if (!board.is_exist(start)) {
		return true;
	}

	Chess* moving_piece = board.get_chess(start);
	Board next_board = board;
	if (!next_board.move_chess(start, end)) {//模拟走一步
		return true;
	}
	return are_kings_facing(next_board) || is_in_check(next_board, moving_piece->getside());
}

bool RuleChecker::are_kings_facing(const Board& board)const
{
	pos red_king = board.find_king('r');
	pos black_king = board.find_king('b');
	if (!board.is_inside(red_king) || !board.is_inside(black_king)) {
		return false;
	}
	if (red_king.x != black_king.x) {
		return false;
	}
	return count_pieces_between(board, red_king, black_king) == 0;
}

bool RuleChecker::has_any_legal_move(const Board& board, char side)const
{
	for (int y = 0; y <= 9; ++y) {
		for (int x = 0; x <= 8; ++x) {
			pos start(x, y);
			if (!board.is_exist(start)) {
				continue;
			}

			Chess* piece = board.get_chess(start);
			if (piece->getside() != side) {
				continue;
			}

			for (int target_y = 0; target_y <= 9; ++target_y) {
				for (int target_x = 0; target_x <= 8; ++target_x) {
					if (is_move_legal(board, start, {target_x, target_y}, side)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool RuleChecker::is_checkmate(const Board& board, char side)const
{
	return is_in_check(board, side) && !has_any_legal_move(board, side);
}

bool RuleChecker::is_stalemate(const Board& board, char side)const
{
	return !is_in_check(board, side) && !has_any_legal_move(board, side);
}

bool RuleChecker::is_piece_move_legal(const Chess* piece, pos start, pos end, const Board& board)const
{
	return piece->is_legal(start, end, board);
}

bool RuleChecker::can_piece_attack(const Chess* piece, pos start, pos end, const Board& board)const
{
	return piece->is_legal(start, end, board);
}

bool RuleChecker::is_in_palace(char side, pos position)const
{
	if (position.x < 3 || position.x > 5) {
		return false;
	}
	if (side == 'r') {
		return position.y >= 0 && position.y <= 2;
	}
	return position.y >= 7 && position.y <= 9;
}

int RuleChecker::count_pieces_between(const Board& board, pos start, pos end)const
{
	if (start.x == end.x) {
		int count = 0;
		int step = end.y > start.y ? 1 : -1;
		for (int y = start.y + step; y != end.y; y += step) {
			if (board.is_exist({start.x, y})) {
				++count;
			}
		}
		return count;
	}
	if (start.y == end.y) {
		int count = 0;
		int step = end.x > start.x ? 1 : -1;
		for (int x = start.x + step; x != end.x; x += step) {
			if (board.is_exist({x, start.y})) {
				++count;
			}
		}
		return count;
	}
	return -1;
}
