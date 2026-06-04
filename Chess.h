#pragma once
#ifndef CHESS_H
#define CHESS_H
#include<string>
using namespace std;
struct pos {
    int x, y;
    pos(int a, int b) :x(a), y(b) {};
    pos() :x(0), y(0) {};
    friend class Chess;
};
class Chess {
public:
    Chess(pos,bool,char,string);
    void setalive(bool);
    bool getalive()const;
    char getside()const;
    void setpos(pos);
    pos getpos()const;
    string gettype()const;
private:
    pos p;
    bool alive;
    const char side;
    const string type;

};
#endif
