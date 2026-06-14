#pragma once
#ifndef CHESS_H
#define CHESS_H
#include<string>
#include<iostream>
class Board;
using namespace std;
struct pos {
	int x, y;
	pos(int a, int b) :x(a), y(b) {};
	pos() :x(0), y(0) {};
	void print_pos()const
	{
		cout << " (" << x << "," << y << ") ";
	}
	friend class Chess;
	friend class Board;
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
	virtual bool is_legal(pos,pos,const Board&)const = 0;
private:
	pos p;
	bool alive;
	const char side;
	const string type;

};
#endif
