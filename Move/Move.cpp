#include "Move.h"

Move::Move(pos start_pos, pos end_pos, const Board& chessBoard, int step)
{
    start=start_pos;
    end=end_pos;
    step_count=step;
    acting_piece=&chessBoard.get_chess(start);
    char side_1=chessBoard.get_chess(start).getside();
    check_eat=0;
    check_king=0;
    side=side_1;
    if(chessBoard.is_exist(end))
    {
      char side_2=chessBoard.get_chess(end).getside();
      if(side_2!=side_1)
    {
        check_eat=1;
        eaten_piece=&chessBoard.get_chess(end);
    }
      else
    {
        eaten_piece=nullptr;
    }
    }
    else{
        eaten_piece=nullptr;
    }

    //TO DO: 调用Game或者RuleChecker等其他类的一些辅助函数实现将军的判断
    //check_king=
}
pos Move::get_start()
{
    return start;
}
pos Move::get_end()
{
    return end;
}
Chess* Move::get_acting_chess()
{
    return acting_piece;
}
Chess* Move::get_eaten_chess()
{
    return eaten_piece;
}
char Move::get_side()
{
    return side;
}
bool Move::get_check_eat()
{
    return check_eat;
}
bool Move::get_check_king()
{
    return check_king;
}
int Move::get_step()
{
    return step_count;
}
void Move::print_move()
{
    cout<<"Move "<<step_count<<":"<<get_side()<<" side "<<get_acting_chess()->gettype()<<" ";
    get_start().print_pos();
    cout<<" to ";
    get_end().print_pos();
    if(get_check_eat()==1)
    {
        cout<<"Eat the chess: "<<get_eaten_chess()->getside()<<" side "<<get_eaten_chess()->gettype();
    }
    if(get_check_king()==1)
    {
        cout<<"Check King!"<<endl;
    }
}
