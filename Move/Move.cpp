#include "Move.h"

Move::Move(pos start_pos, pos end_pos, const Board& chessBoard, int step)
{
    start=start_pos;
    end=end_pos;
    step_count=step;
    acting_piece=chessBoard.get_chess(start);
    char side_1=chessBoard.get_chess(start).getside();
    char side_2=chessBoard.get_chess(end).getside();
    check_eat=0;
    check_king=0;
    side=side_1;
    if(side_2!=side_1)
    {
        check_eat=1;
        eaten_piece=chessBoard.get_chess(end);
    }
    else
    {
        eaten_piece=Chess();
    }
    //TO DO: 调用Game或者RuleChecker等其他类的一些辅助函数实现将军的判断
    //check_king=
}
