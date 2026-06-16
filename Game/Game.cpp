#include "Game.h"

#include <iostream>

#include "../ConsoleUI/ConsoleUI.h"

Game::Game()
	: current_side('r'), game_over(false), winner('\0'), step_count(0) {}

void Game::run()
{
	//缓存上一步的日志
	std::string pending_message;

	while (!game_over) {
		ConsoleUI::clear_screen();

		// 输出上一步的日志
		if (!pending_message.empty()) {
			std::cout << pending_message;
			pending_message.clear();
		}

		ConsoleUI::print_board(board);//输出棋盘
		ConsoleUI::show_turn(current_side);

		pos start;
		pos end;
		bool undo_request = false;
		if (!ConsoleUI::read_move(start, end, undo_request)) {
			std::cout << "Game terminated." << std::endl;
			return;
		}

		if (undo_request) {
			if (!undo_last_move()) {
				pending_message = "No move to undo.\n";
			} else {
				pending_message = "Last move undone.\n";
			}
			continue;
		}

		bool caused_self_check = false;
		std::string move_msg;
		if (!try_move(start, end, caused_self_check, move_msg)) {
			if (caused_self_check) {//评价为User Friendly
				pending_message = "That move would leave your own king in check.\nIllegal move. Try again.\n";
			} else {
				pending_message = "Illegal move. Try again.\n";
			}
		} else {
			pending_message = move_msg;
		}
	}

	// Game over: show final board and result
	ConsoleUI::clear_screen();
	ConsoleUI::print_board(board);
	ConsoleUI::show_winner(winner);
}

static const char* side_name(char s) { return s == 'r' ? "Red side" : "Blue side"; }

bool Game::try_move(pos start, pos end, bool& caused_self_check, std::string& move_msg)
{
	caused_self_check = false;
	move_msg.clear();

	if (!rule_checker.is_move_legal(board, start, end, current_side)) {
		if (board.is_inside(start) && board.is_inside(end) &&
		    board.is_exist(start) &&
		    board.get_chess(start)->getside() == current_side &&
		    (start.x != end.x || start.y != end.y))
		{
			caused_self_check = rule_checker.would_cause_self_check(board, start, end);
		}
		return false;
	}

	//把当前棋盘状态压入stack
	board_history.push(board);
	side_history.push(current_side);

	Move move(start, end, board, step_count + 1);//模拟走一步
	if (!board.move_chess(start, end)) {
		board_history.pop();
		side_history.pop();
		return false;
	}

	history.push_back(move);
	++step_count;
	move_msg = history.back().format_move();

	char opponent = current_side == 'r' ? 'b' : 'r';
	if (history.back().get_check_king()) {
		move_msg += std::string(side_name(opponent)) + " is in check.\n";
	}

	if (rule_checker.is_checkmate(board, opponent)) {
		game_over = true;
		winner = current_side;
		move_msg += std::string(side_name(winner)) + " wins by checkmate.\n";
		return true;
	}

	if (rule_checker.is_stalemate(board, opponent)) {
		game_over = true;
		winner = current_side;
		move_msg += std::string(side_name(winner)) + " wins by stalemate.\n";
		return true;
	}

	switch_side();
	return true;
}

bool Game::undo_last_move()//悔棋功能
{
	if (step_count == 0) {
		return false;
	}
	//从stack里pop出上一步完成后的棋盘状态
	board = board_history.pop();
	current_side = side_history.pop();
	game_over = false;
	winner = '\0';

	if (!history.empty()) {
		history.pop_back();
	}
	if (step_count > 0) {
		--step_count;
	}

	return true;
}

const Board& Game::get_board() const
{
	return board;
}

char Game::get_current_side() const
{
	return current_side;
}

bool Game::is_game_over() const
{
	return game_over;
}

char Game::get_winner() const
{
	return winner;
}

const std::vector<Move>& Game::get_history() const
{
	return history;
}

void Game::switch_side()
{
	current_side = current_side == 'r' ? 'b' : 'r';
}
