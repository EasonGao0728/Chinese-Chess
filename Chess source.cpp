#include<iostream>
#include"Chess.h"
Chess::Chess(pos position,bool a,char c,string str) :p(position), alive(a), side(c), type(str) {};
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

