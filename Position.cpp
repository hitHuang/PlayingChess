/************************************************************************
    > File Name: position.cpp
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月22日 星期一 13时50分19秒
************************************************************************/
#include <iostream>
#include "Position.h"
Position::Position(std::istream& is) {
	is >> x_ >> y_;
}

std::ostream& operator<<(std::ostream& os, const Position& position) {
	os << position.x_ << " " << position.y_;
	return os;
}
