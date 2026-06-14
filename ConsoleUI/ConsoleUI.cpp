#ifdef _WIN32
#include <windows.h>
#endif

#include "ConsoleUI.h"

#include <clocale>
#include <iostream>
#include <sstream>
#include <string>

namespace {
const char* kRedColor = "\x1b[31m";
const char* kBlueColor = "\x1b[34m";
const char* kResetColor = "\x1b[0m";
bool gUseColors = true;

#ifdef _WIN32
bool enable_virtual_terminal_colors()
{
	HANDLE output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (output_handle == INVALID_HANDLE_VALUE) {
		return false;
	}

	DWORD console_mode = 0;
	if (!GetConsoleMode(output_handle, &console_mode)) {
		return false;
	}

	return SetConsoleMode(output_handle, console_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}
#endif
}

void ConsoleUI::initialize_console()
{
	static bool initialized = false;
	if (initialized) {
		return;
	}

#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	if (std::setlocale(LC_ALL, ".UTF-8") == nullptr) {
		std::setlocale(LC_ALL, "");
	}
	gUseColors = enable_virtual_terminal_colors();
#else
	std::setlocale(LC_ALL, "");
#endif

	initialized = true;
}

void ConsoleUI::print_board(const Board& board)
{
	initialize_console();
	std::cout << std::endl;
	std::cout << "    0 1 2 3 4 5 6 7 8" << std::endl;
	std::cout << "   -------------------" << std::endl;
	for (int y = 9; y >= 0; --y) {
		std::cout << y << " | ";
		for (int x = 0; x <= 8; ++x) {
			if (board.is_exist({x, y})) {
				std::cout << get_piece_symbol(board.get_chess({x, y}));
			} else {
				std::cout << "十";
			}
			if (x != 8) {
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool ConsoleUI::read_move(pos& start, pos& end, bool& undo_request)
{
	initialize_console();
	undo_request = false;
	while (true) {
		std::cout << "Input move as: x1 y1 x2 y2, u to undo, or q to quit: ";
		std::string line;
		if (!std::getline(std::cin, line)) {
			return false;
		}

		size_t begin = line.find_first_not_of(" \t\r\n");
		if (begin == std::string::npos) {
			std::cout << "Invalid input format." << std::endl;
			continue;
		}
		size_t end_pos = line.find_last_not_of(" \t\r\n");
		line = line.substr(begin, end_pos - begin + 1);

		if (line == "q" || line == "Q" || line == "quit" || line == "QUIT") {
			return false;
		}

		if (line == "u" || line == "U" || line == "undo" || line == "UNDO") {
			undo_request = true;
			return true;
		}

		std::stringstream buffer(line);
		if (buffer >> start.x >> start.y >> end.x >> end.y) {
			return true;
		}

		std::cout << "Invalid input format." << std::endl;
	}
}

void ConsoleUI::show_turn(char side)
{
	initialize_console();
	std::cout << get_side_name(side) << " to move." << std::endl;
}

void ConsoleUI::show_invalid_move()
{
	std::cout << "Illegal move. Try again." << std::endl;
}

void ConsoleUI::show_check(char side)
{
	std::cout << get_side_name(side) << " is in check." << std::endl;
}

void ConsoleUI::show_checkmate(char side)
{
	std::cout << get_side_name(side) << " wins by checkmate." << std::endl;
}

void ConsoleUI::show_stalemate(char side)
{
	std::cout << get_side_name(side) << " wins by stalemate." << std::endl;
}

void ConsoleUI::show_winner(char side)
{
	initialize_console();
	if (side == '\0') {
		std::cout << "No winner." << std::endl;
		return;
	}
	std::cout << "Winner: " << get_side_name(side) << std::endl;
}

std::string ConsoleUI::get_piece_symbol(const Chess& piece)
{
	std::string symbol = "?";
	std::string type = piece.gettype();

	if (type == "rook") {
		symbol = "车";
	} else if (type == "horse") {
		symbol = "马";
	} else if (type == "elephant") {
		symbol = "象";
	} else if (type == "advisor") {
		symbol = "士";
	} else if (type == "King" || type == "king") {
		symbol = "将";
	} else if (type == "cannon") {
		symbol = "炮";
	} else if (type == "pawn") {
		symbol = "兵";
	}

	if (piece.getside() == 'r') {
		if (type == "elephant") {
			symbol = "相";
		} else if (type == "advisor") {
			symbol = "仕";
		} else if (type == "King" || type == "king") {
			symbol = "帅";
		}
	}

	if (piece.getside() != 'r' && type == "pawn") {
		symbol = "卒";
	}

	if (!gUseColors) {
		return symbol;
	}

	if (piece.getside() == 'r') {
		return std::string(kRedColor) + symbol + kResetColor;
	}

	return std::string(kBlueColor) + symbol + kResetColor;
}

const char* ConsoleUI::get_side_name(char side)
{
	return side == 'r' ? "Red side" : "Blue side";
}
