#include<iostream>
#include"King.h"
#include"../Board/Board.h"
using namespace std;

King::King(pos position,char c,bool a,string str)
:Chess(position,a,c,str)
{};
Chess* King::clone()const { return new King(*this); }

bool King::is_legal(pos start,pos end,const Board& chessBoard)const
{
    bool check_legal_a=false;
    bool check_legal_b=false;
    bool is_direct=false;
    if(Chess::getside()=='r')//根据棋子所在阵营判断走棋范围是否合法
    {
        if(end.x<3||end.x>5||end.y>2)
        {
            cout<<"Invalid end position for"<<Chess::gettype()<<endl;
            return check_legal_a;
        }
    }
    else if(Chess::getside()=='b')
    {
        if(end.x<3||end.x>5||end.y<7)
        {
            cout<<"Invalid end position for"<<Chess::gettype()<<endl;
            return check_legal_a;
        }
    }
    if(chessBoard.is_exist(end)==1)//判断是否遇到敌方棋子
        {
            if(chessBoard.get_chess(end)->getside()!=Chess::getside())
            {
                check_legal_a=true;
            }
        }
        else
        {
            check_legal_a=true;
        }
    if((end.y-start.y)*(end.y-start.y)+(end.x-start.x)*(end.x-start.x)==1)//判断是否一次走一格
    {
        check_legal_b=true;
    }
    if(Chess::getside()=='r')//照将判断
    {
        for(int i=end.y+1;i<=9;++i)
        {
            pos temp(end.x,i);
            if(chessBoard.is_exist(temp))
            {
                if(chessBoard.get_chess(temp)->gettype()=="King")
                {
                    is_direct=1;
                }
                else
                {
                    break;
                }
            }
        }
    }
    else if(Chess::getside()=='b')
    {
        for(int i=end.y-1;i>=0;--i)
        {
            pos temp(end.x,i);
            if(chessBoard.is_exist(temp))
            {
                if(chessBoard.get_chess(temp)->gettype()=="King")
                {
                    is_direct=1;
                }
                else
                {
                    break;
                }
            }
        }
    }
    return check_legal_a&&check_legal_b&&!is_direct;
}