#pragma once
#ifndef CHESS_H
#define CHESS_H
#include<iostream>
#include<string>
using namespace std;

// Forward declaration to break circular dependency with Board.h
class Board;

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
    Chess(const Chess&) = default;
    virtual ~Chess() = default;
    void setalive(bool);
    bool getalive()const;
    char getside()const;
    void setpos(pos);
    virtual bool is_legal(pos,pos,const Board&)const = 0;
    virtual Chess* clone()const = 0;
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
