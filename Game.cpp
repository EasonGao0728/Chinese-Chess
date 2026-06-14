#include "Game.h"

#include <iostream>

#include "ConsoleUI.h"

Game::Game()
	: current_side('r'), game_over(false), winner('\0'), step_count(0) {
}

void Game::run()
{
	while (!game_over) {
		ConsoleUI::print_board(board);
		ConsoleUI::show_turn(current_side);

		pos start;
		pos end;
		if (!ConsoleUI::read_move(start, end)) {
			std::cout << "Game terminated." << std::endl;
			return;
		}

		if (!try_move(start, end)) {
			ConsoleUI::show_invalid_move();
		}
	}

	ConsoleUI::print_board(board);
	ConsoleUI::show_winner(winner);
}

bool Game::try_move(pos start, pos end)
{
	if (!rule_checker.is_move_legal(board, start, end, current_side)) {
		return false;
	}

	Move move(start, end, board, step_count + 1);
	if (!board.move_chess(start, end)) {
		return false;
	}

	history.push_back(move);
	++step_count;
	history.back().print_move();

	char opponent = current_side == 'r' ? 'b' : 'r';
	if (history.back().get_check_king()) {
		ConsoleUI::show_check(opponent);
	}

	if (rule_checker.is_checkmate(board, opponent)) {
		game_over = true;
		winner = current_side;
		ConsoleUI::show_checkmate(winner);
		return true;
	}

	if (rule_checker.is_stalemate(board, opponent)) {
		game_over = true;
		winner = current_side;
		ConsoleUI::show_stalemate(winner);
		return true;
	}

	switch_side();
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