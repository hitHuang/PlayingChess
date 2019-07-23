/************************************************************************
    > File Name: Operation.h
    > Author: huang
    > Mail: moon7921@163.com 
    > Created Time: 2019年07月22日 星期一 16时00分21秒
************************************************************************/

#ifndef OPERATION_H
#define OPERATION_H
#include <iostream>
#include "types.h"
#include "Position.h"
struct Operation {
friend std::ostream& operator<<(std::ostream& os, Operation& op);
	Operation() : type_(INVALID) { }
	void setType(OpType type) { type_ = type; }
	void setPosition1(Position& position) { position1 = position; }
	void setPosition2(Position& position) { position2 = position; }
	OpType getType() const { return type_; }
	Position getPosition1() const { return position1; }
	Position getPosition2() const { return position2; }

	void readCommand();
	std::string toStr();

	OpType type_;
	Position position1;
	Position position2;
};

std::ostream& operator<<(std::ostream& os, Operation& op);
#endif
