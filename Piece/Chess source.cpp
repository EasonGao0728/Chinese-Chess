#include<iostream>
#include"Chess.h"
Chess::Chess(pos position,bool a,char c,string str) :p(position), alive(a), side(c), type(str) {};
Chess::Chess()//必要的默认构造函数,但是构造出来的是无效的棋子！！
{
	p=pos(-1,-1);
	alive=0;
	side='X';
	type="Unknown";
}
void Chess::setpos(pos position) {
	p = position;
}
pos Chess::getpos()const {
	return p;
}
void Chess::setalive(bool a) {
	alive = a;
}
bool Chess::getalive()const {
	return alive;
}
char Chess::getside()const {
	return side;
}
string Chess::gettype()const {
	return type;
}
const Chess& Chess::operator=(const Chess& A)//必要的赋值运算符重载
{
	p=A.p;
	alive=A.alive;
	side=A.side;
	type=A.type;
}

