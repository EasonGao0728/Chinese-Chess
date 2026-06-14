#include "Move.h"
#include "../RuleChecker/RuleChecker.h"

Move::Move(pos start_pos, pos end_pos, const Board& chessBoard, int step)
{
    start=start_pos;
    end=end_pos;
    step_count=step;
    acting_piece=chessBoard.get_chess(start);
    char side_1=acting_piece.getside();
    check_eat=0;
    check_king=0;
    side=side_1;
    if(chessBoard.is_exist(end))
    {
      char side_2=chessBoard.get_chess(end).getside();
      if(side_2!=side_1)
    {
        check_eat=1;
        eaten_piece=chessBoard.get_chess(end);
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
const Chess* Move::get_acting_chess() const
{
    return &acting_piece;
}
const Chess* Move::get_eaten_chess() const
{
    if (!check_eat) {
        return nullptr;
    }
    return &eaten_piece;
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
    cout<<"Move "<<step_count<<":"<<get_side()<<" side "<<get_acting_chess()->gettype()<<" ";
    get_start().print_pos();
    cout<<" to ";
    get_end().print_pos();
    if(get_check_eat()==1)
    {
        cout<<" Eat the chess: "<<get_eaten_chess()->getside()<<" side "<<get_eaten_chess()->gettype();
    }
    if(get_check_king()==1)
    {
        cout<<" Check King!";
    }
    cout<<endl;
}
