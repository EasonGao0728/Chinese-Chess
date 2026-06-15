#include "Move.h"
#include "../RuleChecker/RuleChecker.h"
#include <sstream>

Move::Move(pos start_pos, pos end_pos, const Board& chessBoard, int step)
{
    start=start_pos;
    end=end_pos;
    step_count=step;
    Chess* acting = chessBoard.get_chess(start);
    acting_type = acting->gettype();
    acting_side = acting->getside();
    side = acting_side;
    check_eat=0;
    check_king=0;
    if(chessBoard.is_exist(end))
    {
      Chess* target = chessBoard.get_chess(end);
      if(target->getside()!=acting_side)
      {
          check_eat=1;
          eaten_type = target->gettype();
          eaten_side = target->getside();
      }
    }

    Board next_board = chessBoard;
    if (next_board.move_chess(start, end)) {
        RuleChecker checker;
        char opponent = side == 'r' ? 'b' : 'r';
        check_king = checker.is_in_check(next_board, opponent);
    }
}
pos Move::get_start() const
{
    return start;
}
pos Move::get_end() const
{
    return end;
}
string Move::get_acting_type() const
{
    return acting_type;
}
char Move::get_acting_side() const
{
    return acting_side;
}
string Move::get_eaten_type() const
{
    return eaten_type;
}
char Move::get_eaten_side() const
{
    return eaten_side;
}
char Move::get_side() const
{
    return side;
}
bool Move::get_check_eat() const
{
    return check_eat;
}
bool Move::get_check_king() const
{
    return check_king;
}
int Move::get_step() const
{
    return step_count;
}
void Move::print_move() const
{
    cout << format_move();
}

std::string Move::format_move() const
{
    std::ostringstream oss;
    oss << "Move " << step_count << ": " << get_side() << " side " << get_acting_type()
        << " (" << get_start().x << "," << get_start().y << ")"
        << " -> (" << get_end().x << "," << get_end().y << ")";
    if (get_check_eat()) {
        oss << "  [Eat: " << get_eaten_side() << " side " << get_eaten_type() << "]";
    }
    if (get_check_king()) {
        oss << "  [Check!]";
    }
    oss << "\n";
    return oss.str();
}
