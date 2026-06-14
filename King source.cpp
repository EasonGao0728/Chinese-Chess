#include<iostream>
#include"King.h"
#include"Board.h"
using namespace std;

King::King(pos position, char c)
    :Chess(position, true, c, "King")
{
};

bool King::is_legal(pos start, pos end, const Board& chessBoard)const
{
    bool check_legal_a = false;
    bool check_legal_b = false;
    bool check_legal_c = false;
    if (Chess::gettype() == "r")//根据棋子所在阵营判断走棋范围是否合法
    {
        if (end.x < 3 || end.x>5 || end.y > 2)
        {
            cout << "Invalid end position for" << Chess::gettype() << endl;
            return check_legal_a;
        }
    }
    else if (Chess::gettype() == "b")
    {
        if (end.x < 3 || end.x>5 || end.y < 7)
        {
            cout << "Invalid end position for" << Chess::gettype() << endl;
            return check_legal_a;
        }
    }
    if (chessBoard.is_exist(end) == 1)//判断是否遇到棋子
    {
        if (chessBoard.get_chess(end)->gettype() != Chess::gettype())
        {
            check_legal_a = true;
        }
    }
    if ((end.y - start.y) * (end.y - start.y) + (end.x - start.x) * (end.x - start.x) == 1)//判断是否一次走一格
    {
        check_legal_b = true;
    }
    bool is_direct = false;
    for (int i = 2;i >= 0;--i)
    {
        pos temp(end.x, abs(9 - end.y - i));
        if (chessBoard.is_exist(temp) == 1)
        {
            if (chessBoard.get_chess(temp)->gettype() == "King")
            {
                if (is_direct == 0)
                {
                    is_direct = 1;
                }

            }
            else
            {
                break;
            }
        }
    }
    return check_legal_a && check_legal_b;
}