#pragma once

#include <string>

#include "../Board/Board.h"

class ConsoleUI {
public:
	static void print_board(const Board&);
	static bool read_move(pos&, pos&, bool& undo_request);
	static void show_turn(char);
	static void show_self_check_warning();
	static void show_invalid_move();
	static void show_check(char);
	static void show_checkmate(char);
	static void show_stalemate(char);
	static void show_winner(char);

	static void clear_screen();

private:
	static void initialize_console();
	static std::string get_piece_symbol(const Chess*);
	static const char* get_side_name(char);
};
