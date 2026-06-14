#pragma once

#include <vector>

#include "../Board/Board.h"
#include "../Move/Move.h"
#include "../RuleChecker/RuleChecker.h"
#include "../Stack/Stack.h"

class Game {
public:
	Game();

	void run();
	bool try_move(pos, pos);
	bool undo_last_move();
	const Board& get_board() const;
	char get_current_side() const;
	bool is_game_over() const;
	char get_winner() const;
	const std::vector<Move>& get_history() const;

private:
	Board board;
	Stack<Board> board_history;
	Stack<char> side_history;
	RuleChecker rule_checker;
	std::vector<Move> history;
	char current_side;
	bool game_over;
	char winner;
	int step_count;

	void switch_side();
};
