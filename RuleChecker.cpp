#include "RuleChecker.h"
#include"Board.h"
#include <cstdlib>
#include <string>

using namespace std;

bool RuleChecker::is_move_legal(const Board& board, pos start, pos end, char current_side)const
{
	if (!board.is_inside(start) || !board.is_inside(end)) {
		return false;
	}
	if (start.x == end.x && start.y == end.y) {
		return false;
	}
	if (!board.is_exist(start)) {
		return false;
	}

	Chess*moving_piece = board.get_chess(start);
	if (current_side != '\0' && moving_piece->getside() != current_side) {
		return false;
	}
	if (!is_piece_move_legal(moving_piece, start, end, board)) {
		return false;
	}

	Board next_board = board;
	if (!next_board.move_chess(start, end)) {
		return false;
	}
	if (are_kings_facing(next_board)) {
		return false;
	}
	if (is_in_check(next_board, moving_piece->getside())) {
		return false;
	}
	return true;
}

bool RuleChecker::is_in_check(const Board& board, char side)const
{
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

			Chess*piece = board.get_chess(current);
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

	Chess*moving_piece = board.get_chess(start);
	Board next_board = board;
	if (!next_board.move_chess(start, end)) {
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

			Chess*piece = board.get_chess(start);
			if (piece->getside() != side) {
				continue;
			}

			for (int target_y = 0; target_y <= 9; ++target_y) {
				for (int target_x = 0; target_x <= 8; ++target_x) {
					if (is_move_legal(board, start, { target_x, target_y }, side)) {
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
	if (!board.is_inside(end)) {
		return false;
	}
	if (board.is_exist(end) && board.get_chess(end)->getside() == piece->getside()) {
		return false;
	}

	string type = piece->gettype();
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int abs_dx = abs(dx);
	int abs_dy = abs(dy);

	if (type == "rook") {
		return (start.x == end.x || start.y == end.y) && count_pieces_between(board, start, end) == 0;
	}

	if (type == "cannon") {
		if (start.x != end.x && start.y != end.y) {
			return false;
		}
		int pieces_between = count_pieces_between(board, start, end);
		if (board.is_exist(end)) {
			return pieces_between == 1;
		}
		return pieces_between == 0;
	}

	if (type == "horse") {
		if (abs_dx == 2 && abs_dy == 1) {
			return !board.is_exist({ start.x + dx / 2, start.y });
		}
		if (abs_dx == 1 && abs_dy == 2) {
			return !board.is_exist({ start.x, start.y + dy / 2 });
		}
		return false;
	}

	if (type == "elephant") {
		if (abs_dx != 2 || abs_dy != 2) {
			return false;
		}
		if (piece->getside() == 'r' && end.y > 4) {
			return false;
		}
		if (piece->getside() == 'b' && end.y < 5) {
			return false;
		}
		return !board.is_exist({ start.x + dx / 2, start.y + dy / 2 });
	}

	if (type == "advisor") {
		return abs_dx == 1 && abs_dy == 1 && is_in_palace(piece->getside(), end);
	}

	if (type == "King" || type == "king") {
		if (board.is_exist(end)) {
			Chess*target_piece = board.get_chess(end);
			if ((target_piece->gettype() == "King" || target_piece->gettype() == "king") &&
				target_piece->getside() != piece->getside() && start.x == end.x) {
				return count_pieces_between(board, start, end) == 0;
			}
		}
		return is_in_palace(piece->getside(), end) && ((abs_dx == 1 && abs_dy == 0) || (abs_dx == 0 && abs_dy == 1));
	}

	if (type == "pawn") {
		if (piece->getside() == 'r') {
			if (dx == 0 && dy == 1) {
				return true;
			}
			return start.y >= 5 && dy == 0 && abs_dx == 1;
		}
		if (dx == 0 && dy == -1) {
			return true;
		}
		return start.y <= 4 && dy == 0 && abs_dx == 1;
	}

	return false;
}

bool RuleChecker::can_piece_attack(const Chess* piece, pos start, pos end, const Board& board)const
{
	return is_piece_move_legal(piece, start, end, board);
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
			if (board.is_exist({ start.x, y })) {
				++count;
			}
		}
		return count;
	}
	if (start.y == end.y) {
		int count = 0;
		int step = end.x > start.x ? 1 : -1;
		for (int x = start.x + step; x != end.x; x += step) {
			if (board.is_exist({ x, start.y })) {
				++count;
			}
		}
		return count;
	}
	return -1;
}