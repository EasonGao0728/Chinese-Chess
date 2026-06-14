#pragma once
#ifndef CHESS_H
#define CHESS_H
#include<string>
using namespace std;
struct pos {
    int x, y;
    pos(int a, int b) :x(a), y(b) {};
    pos() :x(0), y(0) {};
    void print_pos()
    {
        cout<<" ("<<x<<","<<y<<") ";
    }
    friend class Chess;
};
class Chess {
public:
    Chess(pos,bool,char,string);
    Chess();
    void setalive(bool);
    bool getalive()const;
    char getside()const;
    void setpos(pos);
    pos getpos()const;
    string gettype()const;
    const Chess& operator=(const Chess&);
private:
    pos p;
    bool alive;
    char side;
    string type;

};
#endif
