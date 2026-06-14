#pragma once
#include <vector>

#include "Board.h"
#include "Move.h"
#include "RuleChecker.h"

class Game {
public:
	Game();

	void run();
	bool try_move(pos, pos);
	const Board& get_board() const;
	char get_current_side() const;
	bool is_game_over() const;
	char get_winner() const;
	const std::vector<Move>& get_history() const;

private:
	Board board;
	RuleChecker rule_checker;
	std::vector<Move> history;
	char current_side;
	bool game_over;
	char winner;
	int step_count;

	void switch_side();
};
