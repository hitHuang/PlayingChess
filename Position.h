/************************************************************************
    > File Name: Position.h
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月21日 星期日 08时52分59秒
************************************************************************/
#ifndef POSITION_H
#define POSITION_H

class Position {
friend std::ostream& operator<<(std::ostream& os, const Position& position);
public:
	Position(int x = -1, int y = -1) : x_(x), y_(y) {

	}
	Position(std::pair<int, int>& p) : x_(p.first), y_(p.second) {

	}
	Position(std::istream& is);
public:
	bool operator==(const Position& lhs) const {
		return (x_ == lhs.x_) && (y_ == lhs.y_);
	}
	std::string toStr() {
		std::string res;
		res += std::to_string(x_) + " " + std::to_string(y_);
		return res;
	} 
public:
	int x_;
	int y_;
};

struct PositionHashNode{
	size_t operator()(const Position& pos) const {
		return pos.x_ + pos.y_;
	}
};

std::ostream& operator<<(std::ostream& os, const Position& position);

#endif
